#ifndef _MACH_MACH_H
#define _MACH_MACH_H

#include <stddef.h>
#include <stdint.h>
#include "../defs.h"
/*
 *  An alternative specification of the notification interface
 *  may be found in mach/notify.defs.
 */

#define MACH_NOTIFY_FIRST               0100
#define MACH_NOTIFY_PORT_DELETED        (MACH_NOTIFY_FIRST + 001 )
                        /* A send or send-once right was deleted. */
#define MACH_NOTIFY_MSG_ACCEPTED        (MACH_NOTIFY_FIRST + 002)
                        /* A MACH_SEND_NOTIFY msg was accepted */
#define MACH_NOTIFY_PORT_DESTROYED      (MACH_NOTIFY_FIRST + 005)
                        /* A receive right was (would have been) deallocated */
#define MACH_NOTIFY_NO_SENDERS          (MACH_NOTIFY_FIRST + 006)
                        /* Receive right has no extant send rights */
#define MACH_NOTIFY_SEND_ONCE           (MACH_NOTIFY_FIRST + 007)
                        /* An extant send-once right died */
#define MACH_NOTIFY_DEAD_NAME           (MACH_NOTIFY_FIRST + 010)
                        /* Send or send-once right died, leaving a dead-name */
#define MACH_NOTIFY_LAST                (MACH_NOTIFY_FIRST + 015)

#define MIG_TYPE_ERROR          -300    /* client type check failure */
#define MIG_REPLY_MISMATCH      -301    /* wrong reply message ID */
#define MIG_REMOTE_ERROR        -302    /* server detected error */
#define MIG_BAD_ID              -303    /* bad request message ID */
#define MIG_BAD_ARGUMENTS       -304    /* server type check failure */
#define MIG_NO_REPLY            -305    /* no reply should be sent */
#define MIG_EXCEPTION           -306    /* server raised exception */
#define MIG_ARRAY_TOO_LARGE     -307    /* array not large enough */
#define MIG_SERVER_DIED         -308    /* server died */
#define MIG_DESTROY_REQUEST     -309    /* destroy request with no reply */

#define KERN_PROC               14      /* struct: process entries */
#define KERN_PROC_PID           1       /* by process id */

#if 0
 /*
 * CTL_KERN identifiers
 */

#define KERN_OSTYPE              1      /* string: system version */
#define KERN_OSRELEASE           2      /* string: system release */
#define KERN_OSREV               3      /* int: system revision */
#define KERN_VERSION             4      /* string: compile time info */
#define KERN_MAXVNODES           5      /* int: max vnodes */
#define KERN_MAXPROC             6      /* int: max processes */
#define KERN_MAXFILES            7      /* int: max open files */
#define KERN_ARGMAX              8      /* int: max arguments to exec */
#define KERN_SECURELVL           9      /* int: system security level */
#define KERN_HOSTNAME           10      /* string: hostname */
#define KERN_HOSTID             11      /* int: host identifier */
#define KERN_CLOCKRATE          12      /* struct: struct clockrate */
#define KERN_VNODE              13      /* struct: vnode structures */
//#define KERN_PROC               14      /* struct: process entries */
#define KERN_FILE               15      /* struct: file entries */
#define KERN_PROF               16      /* node: kernel profiling info */
#define KERN_POSIX1             17      /* int: POSIX.1 version */
#define KERN_NGROUPS            18      /* int: # of supplemental group ids */
#define KERN_JOB_CONTROL        19      /* int: is job control available */
#define KERN_SAVED_IDS          20      /* int: saved set-user/group-ID */
#define KERN_BOOTTIME           21      /* struct: time kernel was booted */
#define KERN_NISDOMAINNAME      22      /* string: YP domain name */
#define KERN_UPDATEINTERVAL     23      /* int: update process sleep time */
#define KERN_OSRELDATE          24      /* int: kernel release date */
#define KERN_NTP_PLL            25      /* node: NTP PLL control */
#define KERN_BOOTFILE           26      /* string: name of booted kernel */
#define KERN_MAXFILESPERPROC    27      /* int: max open files per proc */
#define KERN_MAXPROCPERUID      28      /* int: max processes per uid */
#define KERN_DUMPDEV            29      /* struct cdev *: device to dump on */
#define KERN_IPC                30      /* node: anything related to IPC */
#define KERN_DUMMY              31      /* unused */
#define KERN_PS_STRINGS         32      /* int: address of PS_STRINGS */
#define KERN_USRSTACK           33      /* int: address of USRSTACK */
#define KERN_LOGSIGEXIT         34      /* int: do we log sigexit procs? */
#define KERN_IOV_MAX            35      /* int: value of UIO_MAXIOV */
#define KERN_HOSTUUID           36      /* string: host UUID identifier */
#define KERN_ARND               37      /* int: from arc4rand() */
#define KERN_MAXID              38      /* number of valid kern ids */
#endif


//typedef types
typedef int             mach_port_t;
typedef mach_port_t     *mach_port_array_t;
typedef int             kern_return_t;  
typedef int             mach_msg_return_t;
typedef int             mach_error_t;
typedef int             mig_reply_error_t;
typedef size_t          mach_msg_timeout_t;

typedef size_t          vm_offset_t;

typedef size_t          mach_msg_type_number_t;
typedef size_t          mach_msg_id_t;
typedef size_t          mach_port_rights_t;
typedef size_t          mach_port_seqno_t;
typedef size_t          mach_port_mscount_t; 
typedef size_t          mach_port_msgcount_t;
typedef size_t          *mach_port_info_t;        /* varying array of natural_t */

//typedef structs
typedef struct {
    void *stub;


} mach_msg_header_t;

typedef struct mach_port_status {
    mach_port_rights_t  mps_pset;   /* count of containing port sets */
    mach_port_seqno_t   mps_seqno;  /* sequence number */
    mach_port_mscount_t mps_mscount;    /* make-send count */
    mach_port_msgcount_t    mps_qlimit; /* queue limit */
    mach_port_msgcount_t    mps_msgcount;   /* number in the queue */
    mach_port_rights_t  mps_sorights;   /* how many send-once rights */
    boolean_t       mps_srights;    /* do send rights exist? */
    boolean_t       mps_pdrequest;  /* port-deleted requested? */
    boolean_t       mps_nsrequest;  /* no-senders requested? */
    size_t          mps_flags;      /* port flags */
} mach_port_status_t;

struct mach_timebase_info {
    uint32_t    numer;
    uint32_t    denom;
};

typedef struct mach_timebase_info   *mach_timebase_info_t;
typedef struct mach_timebase_info   mach_timebase_info_data_t;

typedef int                         mach_port_name_t;
typedef mach_port_name_t            *mach_port_name_array_t;

typedef int                         exception_type_t;
typedef int                         exception_data_type_t;
typedef int64_t                     mach_exception_data_type_t;
typedef exception_data_type_t       *exception_data_t;
typedef mach_exception_data_type_t  *mach_exception_data_t;

typedef int                         *thread_state_t;    /* Variable-length array */


typedef size_t                      mach_msg_size_t;

typedef int                         cpu_type_t;
typedef int                         ipc_space_t;
typedef mach_port_t                 task_t;

//funcs
mach_port_t mach_task_self(void);
kern_return_t mach_port_deallocate(ipc_space_t space, mach_port_name_t name);




#endif

