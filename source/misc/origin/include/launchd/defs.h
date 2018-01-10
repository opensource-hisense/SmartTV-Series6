#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdio.h>
#include <stdarg.h>

typedef int             boolean_t;
typedef int             integer_t;
typedef char            uuid_string_t[100];
typedef unsigned char   Boolean;

//kqueue kevent
#define NOTE_SECONDS    0x00000001 

//BSD queuue macros
#define	SLIST_FOREACH_SAFE(var, head, field, tvar)			\
	for ((var) = SLIST_FIRST((head));				\
	    (var) && ((tvar) = SLIST_NEXT((var), field), 1);		\
	    (var) = (tvar))

#define SLIST_FOREACH_SAFE(var, head, field, tvar)          \
    for ((var) = SLIST_FIRST((head));               \
        (var) && ((tvar) = SLIST_NEXT((var), field), 1);        \
        (var) = (tvar))
#define LIST_FOREACH_SAFE(var, head, field, tvar)           \
     for ((var) = LIST_FIRST((head));                \
         (var) && ((tvar) = LIST_NEXT((var), field), 1);     \
         (var) = (tvar))



#define KERN_PROC_ALL         0       /* everything */

/*
*      Return values from the VM routines.
*/
#define KERN_SUCCESS            0
#define KERN_INVALID_ADDRESS    1
#define KERN_PROTECTION_FAILURE 2
#define KERN_NO_SPACE           3
#define KERN_INVALID_ARGUMENT   4
#define KERN_FAILURE            5
#define KERN_RESOURCE_SHORTAGE  6
#define KERN_NOT_RECEIVER       7
#define KERN_NO_ACCESS          8


#define SZOMB           5               /* Awaiting collection by parent. */
#define P_SUGID         0x00000100      /* Has set privileges since last exec */
#define P_EXEC          0x00004000      /* Process called exec. */
#define MAXCOMLEN       16              /* max command name remembered */
#define ENEEDAUTH       81              /* Need authenticator */


#define NSEC_PER_SEC    1000000000ull
#define NSEC_PER_USEC   1000ull
#define USEC_PER_SEC    1000000ul

#define BIG_PIPE_SIZE   (64*1024)


#define NOTE_NSECONDS   0x00000004


//************************************************
#if 0

/* Exported fields for kern sysctls */
struct extern_proc {
    union {
        struct {
            struct  proc *__p_forw; /* Doubly-linked run/sleep queue. */
            struct  proc *__p_back;
        } p_st1;
        struct timeval __p_starttime;   /* process start time */
    } p_un;
#define p_forw p_un.p_st1.__p_forw
#define p_back p_un.p_st1.__p_back
#define p_starttime p_un.__p_starttime
    struct  vmspace *p_vmspace; /* Address space. */
    struct  sigacts *p_sigacts; /* Signal actions, state (PROC ONLY). */
    int p_flag;         /* P_* flags. */
    char    p_stat;         /* S* process status. */
    pid_t   p_pid;          /* Process identifier. */
    pid_t   p_oppid;     /* Save parent pid during ptrace. XXX */
    int p_dupfd;     /* Sideways return value from fdopen. XXX */
    /* Mach related  */
    caddr_t user_stack; /* where user stack was allocated */
    void    *exit_thread;   /* XXX Which thread is exiting? */
    int     p_debugger;     /* allow to debug */
    boolean_t   sigwait;    /* indication to suspend */
    /* scheduling */
    u_int   p_estcpu;    /* Time averaged value of p_cpticks. */
    int p_cpticks;   /* Ticks of cpu time. */
    fixpt_t p_pctcpu;    /* %cpu for this process during p_swtime */
    void    *p_wchan;    /* Sleep address. */
    char    *p_wmesg;    /* Reason for sleep. */
    u_int   p_swtime;    /* Time swapped in or out. */
    u_int   p_slptime;   /* Time since last blocked. */
    struct  itimerval p_realtimer;  /* Alarm timer. */
    struct  timeval p_rtime;    /* Real time. */
    u_quad_t p_uticks;      /* Statclock hits in user mode. */
    u_quad_t p_sticks;      /* Statclock hits in system mode. */
    u_quad_t p_iticks;      /* Statclock hits processing intr. */
    int p_traceflag;        /* Kernel trace points. */
    struct  vnode *p_tracep;    /* Trace to vnode. */
    int p_siglist;      /* DEPRECATED. */
    struct  vnode *p_textvp;    /* Vnode of executable. */
    int p_holdcnt;      /* If non-zero, don't swap. */
    sigset_t p_sigmask; /* DEPRECATED. */
    sigset_t p_sigignore;   /* Signals being ignored. */
    sigset_t p_sigcatch;    /* Signals being caught by user. */
    u_char  p_priority; /* Process priority. */
    u_char  p_usrpri;   /* User-priority based on p_cpu and p_nice. */
    char    p_nice;     /* Process "nice" value. */
    char    p_comm[MAXCOMLEN+1];
    struct  pgrp *p_pgrp;   /* Pointer to process group. */
    struct  user *p_addr;   /* Kernel virtual addr of u-area (PROC ONLY). */
    u_short p_xstat;    /* Exit status for wait; also stop signal. */
    u_short p_acflag;   /* Accounting flags. */
    struct  rusage *p_ru;   /* Exit information. XXX */
};


#endif

//************************************************
#if 0
//struct
struct kinfo_proc {
    struct  extern_proc kp_proc;            /* proc structure */
    struct  eproc {
        struct  proc *e_paddr;      /* address of proc */
        struct  session *e_sess;    /* session pointer */
        struct  _pcred e_pcred;     /* process credentials */
        struct  _ucred e_ucred;     /* current credentials */
        struct   vmspace e_vm;      /* address space */
        pid_t   e_ppid;         /* parent process id */
        pid_t   e_pgid;         /* process group id */
        short   e_jobc;         /* job control counter */
        dev_t   e_tdev;         /* controlling tty dev */
        pid_t   e_tpgid;        /* tty process group id */
        struct  session *e_tsess;   /* tty session pointer */
#define WMESGLEN    7
        char    e_wmesg[WMESGLEN+1];    /* wchan message */
        segsz_t e_xsize;        /* text size */
        short   e_xrssize;      /* text rss */
        short   e_xccount;      /* text references */
        short   e_xswrss;
        int32_t e_flag;
#define EPROC_CTTY  0x01    /* controlling tty vnode active */
#define EPROC_SLEADER   0x02    /* session leader */
#define COMAPT_MAXLOGNAME   12
        char    e_login[COMAPT_MAXLOGNAME]; /* short setlogin() name */
#if CONFIG_LCTX
        pid_t   e_lcid;
        int32_t e_spare[3];
#else
        int32_t e_spare[4];
#endif
    } kp_eproc;
};
#endif

#endif

