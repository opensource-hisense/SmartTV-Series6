// Simple IPv4 Link-Local addressing (see <http://www.zeroconf.org/>)
// @(#)llip.c, 1.5, Copyright 2003 by Arthur van Hoff (avh@strangeberry.com)
// Pid file, signal handling and support for virtual interfaces added
// by Christian Vogt (cvogt@loewe-komp.de)
// Original code available at http://www.zeroconf.org/AVH-IPv4LL.c
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// See <http://www.gnu.org/copyleft/lesser.html>
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/poll.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <linux/if_packet.h>
#include <linux/sockios.h>

#define LINKLOCAL_ADDR          0xa9fe0000
#define LINKLOCAL_MASK          0xFFFF0000
#define NPROBES                 3
#define PROBE_INTERVAL          200
#define NCLAIMS                 3
#define CLAIM_INTERVAL          200
#define FAILURE_INTERVAL        14000
#define DEFAULT_INTERFACE       "eth0"
#define DEFAULT_SCRIPT          "/etc/network.script"

// we always want the possibility to get some verbose output.
#ifndef DEBUG
    #define DEBUG
#endif    

static char *prog;
#ifdef DEBUG
static int verbose = 0;
#endif

static struct in_addr null_ip = {0};
static struct ether_addr null_addr = {{0, 0, 0, 0, 0, 0}};
static struct ether_addr broadcast_addr = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
static int s_terminate = 0;

/**
 * ARP packet.
 */
struct arp_packet {
    struct ether_header hdr;
    struct arphdr arp;
    struct ether_addr source_addr;
    struct in_addr source_ip;
    struct ether_addr target_addr; 
    struct in_addr target_ip;
    unsigned char pad[18];
} __attribute__ ((__packed__));

#ifdef DEBUG
/**
 * Convert an ethernet address to a printable string.
 */
static char *ether2str(const struct ether_addr *addr)
{
    static char str[32];
    snprintf(str, sizeof(str), "%02X:%02X:%02X:%02X:%02X:%02X",
             addr->ether_addr_octet[0], addr->ether_addr_octet[1],
             addr->ether_addr_octet[2], addr->ether_addr_octet[3],
             addr->ether_addr_octet[4], addr->ether_addr_octet[5]);
    return str;
}
#endif

/**
 * Pick a random link local IP address.
 */
static void pick(struct in_addr *ip)
{
    ip->s_addr = htonl(LINKLOCAL_ADDR | ((abs(random()) % 0xFD00) + 0x0100));
}

/**
 * Send out an ARP packet.
 */
static void arp(int fd, struct sockaddr *saddr, int op,
                struct ether_addr *source_addr, struct in_addr source_ip,
                struct ether_addr *target_addr, struct in_addr target_ip)
{
    struct arp_packet p;
    memset(&p, 0, sizeof(p));

    // ether header
    p.hdr.ether_type = htons(ETHERTYPE_ARP);
    memcpy(p.hdr.ether_shost, source_addr, ETH_ALEN);
    memcpy(p.hdr.ether_dhost, &broadcast_addr, ETH_ALEN);

    // arp request
    p.arp.ar_hrd = htons(ARPHRD_ETHER);
    p.arp.ar_pro = htons(ETHERTYPE_IP);
    p.arp.ar_hln = ETH_ALEN;
    p.arp.ar_pln = 4;
    p.arp.ar_op = htons(op);
    memcpy(&p.source_addr, source_addr, ETH_ALEN);
    memcpy(&p.source_ip, &source_ip, sizeof(p.source_ip));
    memcpy(&p.target_addr, target_addr, ETH_ALEN);
    memcpy(&p.target_ip, &target_ip, sizeof(p.target_ip));

    // send it
    if (sendto(fd, &p, sizeof(p), 0, saddr, sizeof(*saddr)) < 0) {
        perror("sendto failed");
        exit(1);
    }
}

/**
 * Run a script.
 */
void run(char *script, char *arg, char *intf, struct in_addr *ip)
{
    int pid, status;

    if (script != NULL) {
#ifdef DEBUG
        if (verbose) {
            fprintf(stderr, "%s %s: run %s %s\n", prog, intf, script, arg);
        }
#endif
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        if (pid == 0) {
            // child process
            setenv("interface", intf, 1);
            if (ip != NULL) {
                setenv("ip", inet_ntoa(*ip), 1);
            }

            execl(script, script, arg, NULL);
            perror("execl failed");
            exit(1);
        }
        if (waitpid(pid, &status, 0) <= 0) {
            perror("waitpid failed");
            exit(1);
        }
        if (WEXITSTATUS(status) != 0) {
            fprintf(stderr, "%s: script %s failed, exit=%d\n", prog, script, WEXITSTATUS(status));
            exit(1);
        }
    }
}

/**
 * Print usage information.
 */
static void usage(char *msg)
{
    fprintf(stderr, "%s: %s\n\n", prog, msg);
    fprintf(stderr, "Usage: %s [OPTIONS]\n", prog);
#ifdef DEBUG 
    fprintf(stderr, " -v                verbose\n");
#endif
    fprintf(stderr, " -q                quit after obtaining address\n");
    fprintf(stderr, " -f                do not fork a daemon\n");
    fprintf(stderr, " -n                exit with failure if no address can be obtained\n");
    fprintf(stderr, " -p <pid-file>     after fork, write current pid to that file\n");
    fprintf(stderr, " -i <interface>    network interface (default %s)\n", DEFAULT_INTERFACE);
    fprintf(stderr, " -s <script>       network script (default %s)\n", DEFAULT_SCRIPT);
    fprintf(stderr, " -ip 169.254.x.x   try this address first\n");
    exit(1);
}


/** function that creates a PID file
 */
static int writepid( const char* filename, pid_t pid )
{
    int file;
    int res;

    do // no loop
    {
        char buf[16];
        ssize_t bytes_written;

        // open the file
        file = open( filename,
                     O_WRONLY | O_CREAT | O_TRUNC,
                     S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
        if( file < 0 ) {
            res = errno;
            break;
        }

        // format and write the pid
        sprintf( buf, "%d\n", (int)pid );
        bytes_written = write( file, buf, strlen(buf) );
        if( bytes_written < 0 ) {
            res = errno;
            break;
        }

        // success.
        res = 0;
    } while(0);

    if( file >= 0 )
    {
        close( file );
        if( res ) {
            (void)unlink( filename );
        }
    }
    return res;
}


/** turn ourselfes into a daemon or die
 */
static void daemonize( const char* pidfile )
{
	pid_t pid, sid;
	int res;

	// Fork off the parent process
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "failed to fork. %s (%d)\n", 
				strerror(errno), errno);
		exit(EXIT_FAILURE);
	}
	// If we got a good PID, then we can (silently) exit the parent process.
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	// Change the file mode mask
	umask(0);

	// Create a new SID for the child process
	sid = setsid();
	if (sid < 0) {
		fprintf( stderr, "failed creating new session. exiting.\n" );
		exit(EXIT_FAILURE);
	}

	// create pid file
	if( pidfile ) {
		res = writepid( pidfile, sid );
		if( res ) {
			fprintf( stderr, "failed creating pid file %s, %s (%d). exiting.\n",
					pidfile, strerror(res), res );
			exit(EXIT_FAILURE);
		}
	}
}	


/** SIGINT signal handler function
 */
static void sig_handler( int signal )
{
    // output seems to be a bad idea inside a signal handler!
    s_terminate = 1;
}


/**
 * main program
 */
int main(int argc, char *argv[])
{
    struct sigaction act;
    char *intf = DEFAULT_INTERFACE;
    char *script = NULL;
    char *pidfile = NULL;
    struct sockaddr saddr;
    struct pollfd fds[1];
    struct arp_packet p;
    struct ifreq ifr;
    struct ether_addr addr;
    struct timeval tv;
    struct in_addr ip = {0};
    int fd;
    int quit = 0;
    int ready = 0;
    int foreground = 0;
    int timeout = 0;
    int nprobes = 0;
    int nclaims = 0;
    int failby = 0;
    int i = 1;
    int failure = 0;

    // init
    gettimeofday(&tv, NULL);
    prog = argv[0];

    // Register SIGINT handler
    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction( SIGTERM, &act, NULL );

    // parse arguments
    while (i < argc) {
        char *arg = argv[i++];
        if (strcmp(arg, "-q") == 0) {
            quit = 1;
        } else if (strcmp(arg, "-f") == 0) {
            foreground = 1;
        } else if (strcmp(arg, "-v") == 0) {
#ifdef DEBUG
            verbose = 1;
#endif
        } else if (strcmp(arg, "-n") == 0) {
            failby = time(0) + FAILURE_INTERVAL / 1000;
        } else if (strcmp(arg, "-i") == 0) {
            if ((intf = argv[i++]) == NULL) {
                usage("interface name missing");
            }
        } else if (strcmp(arg, "-s") == 0) {
            if ((script = argv[i++]) == NULL) {
                usage("script missing");
            }
        } else if (strcmp(arg, "-p") == 0) {
            if ((pidfile = argv[i++]) == NULL) {
                usage("pid-file missing");
            }
        } else if (strcmp(arg, "-ip") == 0) {
            char *ipstr = argv[i++];
            if (ipstr == NULL) {
                usage("ip address missing");
            }
            if (inet_aton(ipstr, &ip) == 0) {
                usage("invalid ip address");
            }
            if ((ntohl(ip.s_addr) & LINKLOCAL_MASK) != LINKLOCAL_ADDR) {
                usage("invalid linklocal address");
            }
        } else {
            usage("invald argument");
        }
    }

    // initialize saddr
    // for virtual interfaces, use the parent one. 
    {
        #define BUFSIZE 32
        char buffer[BUFSIZE];
        char* colon;
        memset( buffer, 0, BUFSIZE );
        strncpy( buffer, intf, BUFSIZE-1 );
        colon = strchr( buffer, ':' );
        if( colon ) {
            *colon = '\0';
        }    
        memset(&saddr, 0, sizeof(saddr));
        strncpy(saddr.sa_data, buffer, sizeof(saddr.sa_data));
    }

    // open an ARP socket
    if ((fd = socket(PF_PACKET, SOCK_PACKET, htons(ETH_P_ARP))) < 0) {
        perror("open failed");
        exit(1);
    }

    // bind to the ARP socket
    if (bind(fd, &saddr, sizeof(saddr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // get the ethernet address of the interface
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, intf, sizeof(ifr.ifr_name));
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl failed");
        exit(1);
    }
    memcpy(&addr, &ifr.ifr_hwaddr.sa_data, ETHER_ADDR_LEN);

    // initialize the interface
    run(script, "init", intf, NULL);

    // initialize pseudo random selection of IP addresses
    srandom((addr.ether_addr_octet[ETHER_ADDR_LEN-4] << 24) |
            (addr.ether_addr_octet[ETHER_ADDR_LEN-3] << 16) |
            (addr.ether_addr_octet[ETHER_ADDR_LEN-2] <<  8) |
            (addr.ether_addr_octet[ETHER_ADDR_LEN-1] <<  0));
    
    // pick an ip address
    if (ip.s_addr == 0) {
        pick(&ip);
    }

    // prepare for polling
    fds[0].fd = fd;
    fds[0].events = POLLIN | POLLERR;

    while(  ( 0 == s_terminate )
          &&( 0 == failure ))
    {
#ifdef DEBUG
        if (verbose) {
            printf("%s %s: polling %d, nprobes=%d, nclaims=%d\n", prog, intf, timeout, nprobes, nclaims);
        }
#endif
        fds[0].revents = 0;
        switch (poll(fds, 1, timeout)) {
            case 0:
                // timeout
                if ((failby != 0) && (failby < time(0))) {
                    fprintf(stderr, "%s %s: failed to obtain address\n", prog, intf);
                    failure = 1;
                    break;
                }
                if (nprobes < NPROBES) {
                    // ARP probe
#ifdef DEBUG
                    if (verbose) {
                        fprintf(stderr, "%s %s: ARP probe %s\n", prog, intf, inet_ntoa(ip));
                    }
#endif
                    arp(fd, &saddr, ARPOP_REQUEST, &addr, null_ip, &null_addr, ip);
                    nprobes++;
                    timeout = PROBE_INTERVAL;
                } else if (nclaims < NCLAIMS) {
                    // ARP claim
#ifdef DEBUG
                    if (verbose) {
                        fprintf(stderr, "%s %s: ARP claim %s\n", prog, intf, inet_ntoa(ip));
                    }
#endif
                    arp(fd, &saddr, ARPOP_REQUEST, &addr, ip, &addr, ip);
                    nclaims++;
                    timeout = CLAIM_INTERVAL;
                } else {
#ifdef DEBUG
                    // ARP take
                    if (verbose) {
                        fprintf(stderr, "%s %s: use %s\n", prog, intf, inet_ntoa(ip));
                    }
#endif
                    ready = 1;
                    timeout = -1;
                    failby = 0;
                    run(script, "config", intf, &ip);

                    if (quit) {
                        exit(0);
                    }
                    if (!foreground) {
						daemonize( pidfile );
                    }
                }
                break;

            case 1:
                // i/o event
                if ((fds[0].revents & POLLIN) == 0) {
                    if (fds[0].revents & POLLERR) {
                        fprintf(stderr, "%s %s: I/O error\n", prog, intf);
						failure = 1;
						break;
                    }
                    continue;
                }

                // read ARP packet
                if (recv(fd, &p, sizeof(p), 0) < 0) {
                    perror("recv failed");
					failure = 1;
					break;
                }
#ifdef DEBUG
                if (verbose) {
                    printf("%s %s: recv arp type=%d, op=%d, ", prog, intf, ntohs(p.hdr.ether_type), ntohs(p.arp.ar_op));
                    printf("source=%s %s,", ether2str(&p.source_addr), inet_ntoa(p.source_ip));
                    printf("target=%s %s\n", ether2str(&p.target_addr), inet_ntoa(p.target_ip));
                }
#endif
                if ((ntohs(p.hdr.ether_type) == ETHERTYPE_ARP) && (ntohs(p.arp.ar_op) == ARPOP_REPLY) &&
                    (p.target_ip.s_addr == ip.s_addr) && (memcmp(&addr, &p.target_addr, ETH_ALEN) != 0)) {

#ifdef DEBUG
                    if (verbose) {
                        fprintf(stderr, "%s %s: ARP conflict %s\n", prog, intf, inet_ntoa(ip));
                    }
#endif
                    pick(&ip);
                    timeout = 0;
                    nprobes = 0;
                    nclaims = 0;
                    if (ready) {
                        ready = 0;
                        run(script, "deconfig", intf, 0);
                    }
                }
                break;

            default:
                perror("poll failed");
				failure = 1;
				break;
        } // switch                
    } // while
    
	if( pidfile ) {
        (void)unlink(pidfile);
	}
#ifdef DEBUG
	if (verbose) {
		fprintf( stderr, "%s %s: exiting.\n", prog, intf );
	}
#endif
    
    exit( failure );
}
