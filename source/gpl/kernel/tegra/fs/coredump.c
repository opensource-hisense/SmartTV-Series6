#include <linux/slab.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/mm.h>
#include <linux/stat.h>
#include <linux/fcntl.h>
#include <linux/swap.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/pagemap.h>
#include <linux/perf_event.h>
#include <linux/highmem.h>
#include <linux/spinlock.h>
#include <linux/key.h>
#include <linux/personality.h>
#include <linux/binfmts.h>
#include <linux/coredump.h>
#include <linux/utsname.h>
#include <linux/pid_namespace.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/mount.h>
#include <linux/security.h>
#include <linux/syscalls.h>
#include <linux/tsacct_kern.h>
#include <linux/cn_proc.h>
#include <linux/audit.h>
#include <linux/tracehook.h>
#include <linux/kmod.h>
#include <linux/fsnotify.h>
#include <linux/fs_struct.h>
#include <linux/pipe_fs_i.h>
#include <linux/oom.h>
#include <linux/compat.h>

#include <asm/uaccess.h>
#include <asm/mmu_context.h>
#include <asm/tlb.h>
#include <mstar/mpatch_macro.h>

#if (MP_DEBUG_TOOL_COREDUMP == 1)
#include <linux/delay.h>

#if (MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT == 1)
#define QUERY_MOUNT_PATH        "/proc/mounts"
#define QUERY_MOUNT_SIZE         4000
#define QUERY_PARTITIONS_PATH        "/proc/partitions"
#define QUERY_PARTITIONS_SIZE         4000
#endif /* MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT  */

#endif /* CONFIG_MP_DEBUG_TOOL_COREDUMP */
#include <asm/exec.h>

#include <trace/events/task.h>
#include "internal.h"
#include "coredump.h"

#include <trace/events/sched.h>

int core_uses_pid;
char core_pattern[CORENAME_MAX_SIZE] = "core";
unsigned int core_pipe_limit;

struct core_name {
	char *corename;
	int used, size;
};
static atomic_t call_count = ATOMIC_INIT(1);

/* The maximal length of core_pattern is also specified in sysctl.c */

static int expand_corename(struct core_name *cn)
{
	char *old_corename = cn->corename;

	cn->size = CORENAME_MAX_SIZE * atomic_inc_return(&call_count);
	cn->corename = krealloc(old_corename, cn->size, GFP_KERNEL);

	if (!cn->corename) {
		kfree(old_corename);
		return -ENOMEM;
	}

	return 0;
}

static int cn_printf(struct core_name *cn, const char *fmt, ...)
{
	char *cur;
	int need;
	int ret;
	va_list arg;

	va_start(arg, fmt);
	need = vsnprintf(NULL, 0, fmt, arg);
	va_end(arg);

	if (likely(need < cn->size - cn->used - 1))
		goto out_printf;

	ret = expand_corename(cn);
	if (ret)
		goto expand_fail;

out_printf:
	cur = cn->corename + cn->used;
	va_start(arg, fmt);
	vsnprintf(cur, need + 1, fmt, arg);
	va_end(arg);
	cn->used += need;
	return 0;

expand_fail:
	return ret;
}

static void cn_escape(char *str)
{
	for (; *str; str++)
		if (*str == '/')
			*str = '!';
}

static int cn_print_exe_file(struct core_name *cn)
{
	struct file *exe_file;
	char *pathbuf, *path;
	int ret;

	exe_file = get_mm_exe_file(current->mm);
	if (!exe_file) {
		char *commstart = cn->corename + cn->used;
		ret = cn_printf(cn, "%s (path unknown)", current->comm);
		cn_escape(commstart);
		return ret;
	}

	pathbuf = kmalloc(PATH_MAX, GFP_TEMPORARY);
	if (!pathbuf) {
		ret = -ENOMEM;
		goto put_exe_file;
	}

	path = d_path(&exe_file->f_path, pathbuf, PATH_MAX);
	if (IS_ERR(path)) {
		ret = PTR_ERR(path);
		goto free_buf;
	}

	cn_escape(path);

	ret = cn_printf(cn, "%s", path);

free_buf:
	kfree(pathbuf);
put_exe_file:
	fput(exe_file);
	return ret;
}

/* format_corename will inspect the pattern parameter, and output a
 * name into corename, which must have space for at least
 * CORENAME_MAX_SIZE bytes plus one byte for the zero terminator.
 */
static int format_corename(struct core_name *cn, struct coredump_params *cprm)
{
	const struct cred *cred = current_cred();
	const char *pat_ptr = core_pattern;
	int ispipe = (*pat_ptr == '|');
	int pid_in_pattern = 0;
	int err = 0;

	cn->size = CORENAME_MAX_SIZE * atomic_read(&call_count);
	cn->corename = kmalloc(cn->size, GFP_KERNEL);
	cn->used = 0;

	if (!cn->corename)
		return -ENOMEM;

	/* Repeat as long as we have more pattern to process and more output
	   space */
	while (*pat_ptr) {
		if (*pat_ptr != '%') {
			if (*pat_ptr == 0)
				goto out;
			err = cn_printf(cn, "%c", *pat_ptr++);
		} else {
			switch (*++pat_ptr) {
			/* single % at the end, drop that */
			case 0:
				goto out;
			/* Double percent, output one percent */
			case '%':
				err = cn_printf(cn, "%c", '%');
				break;
			/* pid */
			case 'p':
				pid_in_pattern = 1;
				err = cn_printf(cn, "%d",
					      task_tgid_vnr(current));
				break;
			/* uid */
			case 'u':
				err = cn_printf(cn, "%d", cred->uid);
				break;
			/* gid */
			case 'g':
				err = cn_printf(cn, "%d", cred->gid);
				break;
			case 'd':
				err = cn_printf(cn, "%d",
					__get_dumpable(cprm->mm_flags));
				break;
			/* signal that caused the coredump */
			case 's':
				err = cn_printf(cn, "%ld", cprm->siginfo->si_signo);
				break;
			/* UNIX time of coredump */
			case 't': {
				struct timeval tv;
				do_gettimeofday(&tv);
				err = cn_printf(cn, "%lu", tv.tv_sec);
				break;
			}
			/* hostname */
			case 'h': {
				char *namestart = cn->corename + cn->used;
				down_read(&uts_sem);
				err = cn_printf(cn, "%s",
					      utsname()->nodename);
				up_read(&uts_sem);
				cn_escape(namestart);
				break;
			}
			/* executable */
			case 'e': {
				char *commstart = cn->corename + cn->used;
				err = cn_printf(cn, "%s", current->comm);
				cn_escape(commstart);
				break;
			}
			case 'E':
				err = cn_print_exe_file(cn);
				break;
			/* core limit size */
			case 'c':
				err = cn_printf(cn, "%lu",
					      rlimit(RLIMIT_CORE));
				break;
			default:
				break;
			}
			++pat_ptr;
		}

		if (err)
			return err;
	}

	/* Backward compatibility with core_uses_pid:
	 *
	 * If core_pattern does not include a %p (as is the default)
	 * and core_uses_pid is set, then .%pid will be appended to
	 * the filename. Do not do this for piped commands. */
	if (!ispipe && !pid_in_pattern && core_uses_pid) {
		err = cn_printf(cn, ".%d", task_tgid_vnr(current));
		if (err)
			return err;
	}
out:
	return ispipe;
}

static int zap_process(struct task_struct *start, int exit_code)
{
	struct task_struct *t;
	int nr = 0;

	start->signal->group_exit_code = exit_code;
	start->signal->group_stop_count = 0;

	t = start;
	do {
		task_clear_jobctl_pending(t, JOBCTL_PENDING_MASK);
		if (t != current && t->mm) {
			sigaddset(&t->pending.signal, SIGKILL);
			signal_wake_up(t, 1);
			nr++;
		}
	} while_each_thread(start, t);

	return nr;
}

static int zap_threads(struct task_struct *tsk, struct mm_struct *mm,
			struct core_state *core_state, int exit_code)
{
	struct task_struct *g, *p;
	unsigned long flags;
	int nr = -EAGAIN;

	spin_lock_irq(&tsk->sighand->siglock);
	if (!signal_group_exit(tsk->signal)) {
		mm->core_state = core_state;
		nr = zap_process(tsk, exit_code);
		tsk->signal->group_exit_task = tsk;
		/* ignore all signals except SIGKILL, see prepare_signal() */
		tsk->signal->flags = SIGNAL_GROUP_COREDUMP;
		clear_tsk_thread_flag(tsk, TIF_SIGPENDING);
	}
	spin_unlock_irq(&tsk->sighand->siglock);
	if (unlikely(nr < 0))
		return nr;

	tsk->flags = PF_DUMPCORE;
	if (atomic_read(&mm->mm_users) == nr + 1)
		goto done;
	/*
	 * We should find and kill all tasks which use this mm, and we should
	 * count them correctly into ->nr_threads. We don't take tasklist
	 * lock, but this is safe wrt:
	 *
	 * fork:
	 *	None of sub-threads can fork after zap_process(leader). All
	 *	processes which were created before this point should be
	 *	visible to zap_threads() because copy_process() adds the new
	 *	process to the tail of init_task.tasks list, and lock/unlock
	 *	of ->siglock provides a memory barrier.
	 *
	 * do_exit:
	 *	The caller holds mm->mmap_sem. This means that the task which
	 *	uses this mm can't pass exit_mm(), so it can't exit or clear
	 *	its ->mm.
	 *
	 * de_thread:
	 *	It does list_replace_rcu(&leader->tasks, &current->tasks),
	 *	we must see either old or new leader, this does not matter.
	 *	However, it can change p->sighand, so lock_task_sighand(p)
	 *	must be used. Since p->mm != NULL and we hold ->mmap_sem
	 *	it can't fail.
	 *
	 *	Note also that "g" can be the old leader with ->mm == NULL
	 *	and already unhashed and thus removed from ->thread_group.
	 *	This is OK, __unhash_process()->list_del_rcu() does not
	 *	clear the ->next pointer, we will find the new leader via
	 *	next_thread().
	 */
	rcu_read_lock();
	for_each_process(g) {
		if (g == tsk->group_leader)
			continue;
		if (g->flags & PF_KTHREAD)
			continue;
		p = g;
		do {
			if (p->mm) {
				if (unlikely(p->mm == mm)) {
					lock_task_sighand(p, &flags);
					nr += zap_process(p, exit_code);
					p->signal->flags = SIGNAL_GROUP_EXIT;
					unlock_task_sighand(p, &flags);
				}
				break;
			}
		} while_each_thread(g, p);
	}
	rcu_read_unlock();
done:
	atomic_set(&core_state->nr_threads, nr);
	return nr;
}

static int coredump_wait(int exit_code, struct core_state *core_state)
{
	struct task_struct *tsk = current;
	struct mm_struct *mm = tsk->mm;
	int core_waiters = -EBUSY;

	init_completion(&core_state->startup);
	core_state->dumper.task = tsk;
	core_state->dumper.next = NULL;

	down_write(&mm->mmap_sem);
	if (!mm->core_state)
		core_waiters = zap_threads(tsk, mm, core_state, exit_code);
	up_write(&mm->mmap_sem);

	if (core_waiters > 0) {
		struct core_thread *ptr;

		wait_for_completion(&core_state->startup);
		/*
		 * Wait for all the threads to become inactive, so that
		 * all the thread context (extended register state, like
		 * fpu etc) gets copied to the memory.
		 */
		ptr = core_state->dumper.next;
		while (ptr != NULL) {
			wait_task_inactive(ptr->task, 0);
			ptr = ptr->next;
		}
	}

	return core_waiters;
}

static void coredump_finish(struct mm_struct *mm, bool core_dumped)
{
	struct core_thread *curr, *next;
	struct task_struct *task;

	spin_lock_irq(&current->sighand->siglock);
	if (core_dumped && !__fatal_signal_pending(current))
		current->signal->group_exit_code |= 0x80;
	current->signal->group_exit_task = NULL;
	current->signal->flags = SIGNAL_GROUP_EXIT;
	spin_unlock_irq(&current->sighand->siglock);

	next = mm->core_state->dumper.next;
	while ((curr = next) != NULL) {
		next = curr->next;
		task = curr->task;
		/*
		 * see exit_mm(), curr->task must not see
		 * ->task == NULL before we read ->next.
		 */
		smp_mb();
		curr->task = NULL;
		wake_up_process(task);
	}

	mm->core_state = NULL;
}

static bool dump_interrupted(void)
{
	/*
	 * SIGKILL or freezing() interrupt the coredumping. Perhaps we
	 * can do try_to_freeze() and check __fatal_signal_pending(),
	 * but then we need to teach dump_write() to restart and clear
	 * TIF_SIGPENDING.
	 */
	return signal_pending(current);
}

static void wait_for_dump_helpers(struct file *file)
{
	struct pipe_inode_info *pipe = file->private_data;

	pipe_lock(pipe);
	pipe->readers++;
	pipe->writers--;
	wake_up_interruptible_sync(&pipe->wait);
	kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
	pipe_unlock(pipe);

	/*
	 * We actually want wait_event_freezable() but then we need
	 * to clear TIF_SIGPENDING and improve dump_interrupted().
	 */
	wait_event_interruptible(pipe->wait, pipe->readers == 1);

	pipe_lock(pipe);
	pipe->readers--;
	pipe->writers++;
	pipe_unlock(pipe);
}

/*
 * umh_pipe_setup
 * helper function to customize the process used
 * to collect the core in userspace.  Specifically
 * it sets up a pipe and installs it as fd 0 (stdin)
 * for the process.  Returns 0 on success, or
 * PTR_ERR on failure.
 * Note that it also sets the core limit to 1.  This
 * is a special value that we use to trap recursive
 * core dumps
 */
static int umh_pipe_setup(struct subprocess_info *info, struct cred *new)
{
	struct file *files[2];
	struct coredump_params *cp = (struct coredump_params *)info->data;
	int err = create_pipe_files(files, 0);
	if (err)
		return err;

	cp->file = files[1];

	err = replace_fd(0, files[0], 0);
	fput(files[0]);
	/* and disallow core files too */
	current->signal->rlim[RLIMIT_CORE] = (struct rlimit){1, 1};

	return err;
}
#if (MP_DEBUG_TOOL_COREDUMP == 1)
	#if (MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY == 1 || MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP == 1)
		extern char * get_coredump_path(void);
	#endif /*MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY && MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP*/
#endif/*MP_DEBUG_TOOL_COREDUMP*/

#if (MP_DEBUG_TOOL_COREDUMP == 1)
#if (MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT == 1)
bool query_mount_state(char *con_file)
{
    char *buf;
    struct file *fp;
    int ret=0,i=0;
	bool mount_result=0;
     char* const delim = "\n";
     char *token = NULL;
    //When accessing user memory, we need to make sure the entire area really is in user-level space.
    //KERNEL_DS addr user-level space need less than TASK_SIZE
    mm_segment_t old_fs=get_fs();
    set_fs(KERNEL_DS);
    //open /proc/mounts
    fp = filp_open(con_file, O_RDONLY , 0x400);

    if (!fp)
    {
        printk(KERN_EMERG "Can not open /proc/mounts,query fail");
    }

    buf = kzalloc(QUERY_MOUNT_SIZE+1, GFP_KERNEL);
    if(!buf)
	{
		printk(KERN_EMERG "Can not read /proc/mounts data,query fail");
    }
    if (fp->f_op && fp->f_op->read)
    {
        ret = fp->f_op->read(fp, buf, QUERY_MOUNT_SIZE, &fp->f_pos);
    }

    if (ret < 0)
    {
		set_fs(old_fs);
        filp_close(fp, NULL);
    }

    mount_result=0;

     //seperate all the string contents to row by \n
     while((token = strsep(&buf, delim))){
     	for (i=0;i<=strlen(token);i++){
		if(token[i]=='/' && token[i+1]=='u' && token[i+2]=='s' && token[i+3]=='b' && token[i+4]=='/'&& token[i+5]=='s'&& token[i+6]=='d'&& token[i+7]=='a'){
			mount_result=1;
			break;
		}
	}
   }
    set_fs(old_fs);
    filp_close(fp, NULL);
    kfree(buf);
	return mount_result;
}

bool query_partitions_state(char *con_file)
{
    char *buf;
    struct file *fp;
    int ret=0;
	bool partitions_result=0;
     char* const delim = "\n";
     char *token = NULL;
    //When accessing user memory, we need to make sure the entire area really is in user-level space.
    //KERNEL_DS addr user-level space need less than TASK_SIZE
    mm_segment_t old_fs=get_fs();
    set_fs(KERNEL_DS);

    fp = filp_open(con_file, O_RDONLY , 0x400);

    if (!fp)
    {
        printk(KERN_EMERG "Can not open /proc/partitions,query fail");
    }

    buf = kzalloc(QUERY_PARTITIONS_SIZE+1, GFP_KERNEL);
    if(!buf)
	{
		printk(KERN_EMERG "Can not read /proc/partitions data,query fail");
    }
    if (fp->f_op && fp->f_op->read)
    {
        ret = fp->f_op->read(fp, buf, QUERY_PARTITIONS_SIZE, &fp->f_pos);
    }

    if (ret < 0)
    {
		set_fs(old_fs);
        filp_close(fp, NULL);
    }

    partitions_result=0;
     while((token = strsep(&buf, delim))){
	    int j = 0;
	    for(j = 0; j < strlen(token) ; j++){
		if(token[j]==32 && token[j+1]=='s' && token[j+2]=='d' && ((token[j+3]=='a') || (token[j+3]=='b')))
			partitions_result=1;
		if(token[j]==32 && token[j+1]=='s' && token[j+2]=='d' && ((token[j+3]=='a') || (token[j+3]=='b')) && token[j+4]=='1')
			partitions_result=1;

	     }
     }
    set_fs(old_fs);
    filp_close(fp, NULL);
    kfree(buf);
	return partitions_result;
}
#endif /* MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT */
#endif /* MP_DEBUG_TOOL_COREDUMP */


void do_coredump(siginfo_t *siginfo)
{
	struct core_state core_state;
	struct core_name cn;
	struct mm_struct *mm = current->mm;
	struct linux_binfmt * binfmt;
	const struct cred *old_cred;
	struct cred *cred;
	int retval = 0;
	int flag = 0;
	int ispipe;
#if (MP_DEBUG_TOOL_COREDUMP == 1)
#if (MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT == 1)
	bool mount_result=0;
	bool partitions_result=0;
	int mount_path_num = 0xFF; //initial value
#elif (MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY == 1)
#else/*users didn't chose any way to save core dump file*/
#error "Not define MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT or MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY"
#endif /*MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT */
#endif /*MP_DEBUG_TOOL_COREDUMP*/
	struct files_struct *displaced;
	bool need_nonrelative = false;
	bool core_dumped = false;
#if (MP_DEBUG_TOOL_COREDUMP == 1)
#if  (MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY == 1 || MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP == 1)
    char corename[CORENAME_MAX_SIZE] = {0};
#endif/*MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY && MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP*/
#endif/*MP_DEBUG_TOOL_COREDUMP*/
	static atomic_t core_dump_count = ATOMIC_INIT(0);
	struct coredump_params cprm = {
		.siginfo = siginfo,
		.regs = signal_pt_regs(),
		.limit = rlimit(RLIMIT_CORE),
		/*
		 * We must use the same mm->flags while dumping core to avoid
		 * inconsistency of bit flags, since this flag is not protected
		 * by any locks.
		 */
		.mm_flags = mm->flags,
	};

#if (MP_DEBUG_TOOL_COREDUMP == 1)
#ifdef CONFIG_BINFMT_ELF_COMP
#if (MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY == 1)
#else
#define COMP_CORENAME_PATH  7
	extern struct module *ultimate_module_check(const char * name);
	struct module *mod_common=NULL,  *mod_usbcore=NULL, *mod_ehci=NULL, *mod_storage=NULL;
	const char *usb_module_list[4] = {"usb_common","usbcore", "ehci_hcd", "usb_storage"};
	unsigned char is_usbmodule_loaded = 0;
    char comp_corename[COMP_CORENAME_PATH][CORENAME_MAX_SIZE + 1];
    const char *usb_mount_list[6] = {"sda1", "sda", "sdb1", "sdb", "sdc1", "sdc"};
	int cnt = 0;
#endif /*CONFIG_MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY*/
#endif/*CONFIG_BINFMT_ELF_COMP*/
#endif /*MP_DEBUG_TOOL_COREDUMP*/

	audit_core_dumps(siginfo->si_signo);

	binfmt = mm->binfmt;
	if (!binfmt || !binfmt->core_dump)
		goto fail;
	if (!__get_dumpable(cprm.mm_flags))
		goto fail;

	cred = prepare_creds();
	if (!cred)
		goto fail;
	/*
	 * We cannot trust fsuid as being the "true" uid of the process
	 * nor do we know its entire history. We only know it was tainted
	 * so we dump it as root in mode 2, and only into a controlled
	 * environment (pipe handler or fully qualified path).
	 */
	if (__get_dumpable(cprm.mm_flags) == SUID_DUMP_ROOT) {
		/* Setuid core dump mode */
		flag = O_EXCL;		/* Stop rewrite attacks */
		cred->fsuid = GLOBAL_ROOT_UID;	/* Dump root private */
		need_nonrelative = true;
	}

	retval = coredump_wait(siginfo->si_signo, &core_state);
	if (retval < 0)
		goto fail_creds;

	old_cred = override_creds(cred);

	/*
	 * Clear any false indication of pending signals that might
	 * be seen by the filesystem code called to write the core file.
	 */
	clear_thread_flag(TIF_SIGPENDING);
#if (MP_DEBUG_TOOL_COREDUMP == 1)
#if (MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY == 1 || MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP == 1)
	/*
   	 * depend on boot args to change core pattern
	 */
	strcpy(corename, get_coredump_path());
	if(*corename) /* bootargs */
	{
		snprintf(core_pattern, sizeof(core_pattern), corename);
	}
   	else
	{
		if(strcmp(core_pattern, "core")==0)
		                snprintf(core_pattern, sizeof(core_pattern), "/var/coredump.%%p.gz");
	}
#endif /*MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY && MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP*/
#endif/*MP_DEBUG_TOOL_COREDUMP*/

	ispipe = format_corename(&cn, &cprm);

	if (ispipe) {
		int dump_count;
		char **helper_argv;
		struct subprocess_info *sub_info;

		if (ispipe < 0) {
			printk(KERN_WARNING "format_corename failed\n");
			printk(KERN_WARNING "Aborting core\n");
			goto fail_corename;
		}

		if (cprm.limit == 1) {
			/* See umh_pipe_setup() which sets RLIMIT_CORE = 1.
			 *
			 * Normally core limits are irrelevant to pipes, since
			 * we're not writing to the file system, but we use
			 * cprm.limit of 1 here as a speacial value, this is a
			 * consistent way to catch recursive crashes.
			 * We can still crash if the core_pattern binary sets
			 * RLIM_CORE = !1, but it runs as root, and can do
			 * lots of stupid things.
			 *
			 * Note that we use task_tgid_vnr here to grab the pid
			 * of the process group leader.  That way we get the
			 * right pid if a thread in a multi-threaded
			 * core_pattern process dies.
			 */
			printk(KERN_WARNING
				"Process %d(%s) has RLIMIT_CORE set to 1\n",
				task_tgid_vnr(current), current->comm);
			printk(KERN_WARNING "Aborting core\n");
			goto fail_unlock;
		}
		cprm.limit = RLIM_INFINITY;

		dump_count = atomic_inc_return(&core_dump_count);
		if (core_pipe_limit && (core_pipe_limit < dump_count)) {
			printk(KERN_WARNING "Pid %d(%s) over core_pipe_limit\n",
			       task_tgid_vnr(current), current->comm);
			printk(KERN_WARNING "Skipping core dump\n");
			goto fail_dropcount;
		}

		helper_argv = argv_split(GFP_KERNEL, cn.corename+1, NULL);
		if (!helper_argv) {
			printk(KERN_WARNING "%s failed to allocate memory\n",
			       __func__);
			goto fail_dropcount;
		}

		retval = -ENOMEM;
		sub_info = call_usermodehelper_setup(helper_argv[0],
						helper_argv, NULL, GFP_KERNEL,
						umh_pipe_setup, NULL, &cprm);
		if (sub_info)
			retval = call_usermodehelper_exec(sub_info,
							  UMH_WAIT_EXEC);

		argv_free(helper_argv);
		if (retval) {
			printk(KERN_INFO "Core dump to %s pipe failed\n",
			       cn.corename);
			goto close_fail;
		}
	} else {
		struct inode *inode;

		if (cprm.limit < binfmt->min_coredump)
			goto fail_unlock;

#if (MP_DEBUG_TOOL_COREDUMP == 1) && defined(CONFIG_BINFMT_ELF_COMP)
#if (MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY == 1)
        cprm.file = filp_open(cn.corename, O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
        if (!IS_ERR(cprm.file))
        {
            printk(KERN_ALERT "***** Create coredump file to %s ******\n", cn.corename);
        }
        else
        {
            printk(KERN_ALERT "***** Coredump Fail... can't create corefile to %s \n", cn.corename);
        }
#elif (MP_DEBUG_TOOL_COREDUMP_USB_DEFAULT == 1)
		/* Change code for saving CoreDump file */
		mod_common = (struct module *)ultimate_module_check(usb_module_list[0]);
		mod_usbcore = (struct module *)ultimate_module_check(usb_module_list[1]);
		mod_ehci = (struct module *)ultimate_module_check(usb_module_list[2]);
		mod_storage = (struct module *)ultimate_module_check(usb_module_list[3]);
#ifdef CONFIG_MP_DEBUG_TOOL_COREDUMP_WITHOUT_COMPRESS
		for (cnt = 0; cnt < (COMP_CORENAME_PATH - 1); cnt++)
		{
			snprintf(comp_corename[cnt], sizeof(comp_corename[cnt]), "/usb/%s/Coredump.%d", usb_mount_list[cnt], current->pid);
        }
        snprintf(comp_corename[cnt], sizeof(comp_corename[cnt]), "/applications/Coredump.%d", current->pid);
#else
		for (cnt = 0; cnt < (COMP_CORENAME_PATH - 1); cnt++)
		{
			snprintf(comp_corename[cnt], sizeof(comp_corename[cnt]), "/usb/%s/Coredump.%d.gz", usb_mount_list[cnt], current->pid);
		}
		snprintf(comp_corename[cnt], sizeof(comp_corename[cnt]), "/applications/Coredump.%d.gz", current->pid);
#endif
    	/*check the usb devices whether is mounted or not(it shoeld be mounted after usb module inserted)*/
		mount_result=query_mount_state(QUERY_MOUNT_PATH);
		/*check the usb partition is created or not(it is created after users insert the usb modules)*/
		partitions_result=query_partitions_state(QUERY_PARTITIONS_PATH);

#ifdef CONFIG_MP_DEBUG_TOOL_COREDUMP_BUILD_IN_USB
    	if (partitions_result==1 && mount_result==1)
#else
    	if (mod_common && mod_usbcore && mod_ehci && mod_storage && (partitions_result  == 1) && (mount_result == 1))
#endif
		{
    		is_usbmodule_loaded = 1;        /* all usb modules loaded */
			printk(KERN_ALERT "***** Coredump : Insert USB memory stick, mount check per 10sec... *****\n");
detect:
			cprm.file = filp_open(comp_corename[0], O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);

       		if(IS_ERR(cprm.file))
       		{
				cprm.file = filp_open(comp_corename[1], O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
       		}
       		else
       		{
				if (mount_path_num == 0xFF)
	       			mount_path_num = 0;
       		}

       		if(IS_ERR(cprm.file))
       		{
               	cprm.file = filp_open(comp_corename[2], O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
       		}
       		else
       		{
	       		if (mount_path_num == 0xFF)
					mount_path_num = 1;
       		}

       		if(IS_ERR(cprm.file))
       		{
               	cprm.file = filp_open(comp_corename[3], O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
       		}
       		else
       		{
        		if (mount_path_num == 0xFF)
	       			mount_path_num = 2;
       		}

       		if(IS_ERR(cprm.file))
       		{
            	cprm.file = filp_open(comp_corename[4], O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
       		}
       		else
      	 	{
        		if (mount_path_num == 0xFF)
	       			mount_path_num = 3;
       		}

       		if(IS_ERR(cprm.file))
       		{
               	cprm.file = filp_open(comp_corename[5], O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
       		}
       		else
       		{
        		if (mount_path_num == 0xFF)
	       			mount_path_num = 4;
       		}

			if (!IS_ERR(cprm.file))
			{
				printk(KERN_ALERT "***** USB detected *****\n");
				printk(KERN_ALERT "***** Create pid : %d coredump file to USB mount dir %s ******\n", current->pid, comp_corename[mount_path_num]);
			}
			else
			{
				mdelay(10 * 1000);
				goto detect;
			}

		}
		else 
		{
			#if (MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP == 1)
		    //if usb fail, then write coredump to bootargs
            cprm.file = filp_open(cn.corename, O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
            if (!IS_ERR(cprm.file))
			{
				printk(KERN_ALERT "***** Create coredump file to %s ******\n", cn.corename);
			}
		  	else
			{
				printk(KERN_ALERT "***** Coredump Fail... can't create corefile to %s \n", cn.corename);
		   	}
			#else
			is_usbmodule_loaded = 0;        /* return NULL, usb modules not loaded */
		    printk(KERN_ALERT "***** USB modules not loaded ******\n");
            printk(KERN_ALERT "***** Create coredump file to tmpfs /core/Coredump.%d.gz ******\n", current->pid);

		    cprm.file = filp_open(comp_corename[6], O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag, 0600);
            if (IS_ERR(cprm.file))
		    	printk(KERN_ALERT "***** Coredump Fail... can't create corefile to /core dir *****\n");
            #endif /*MP_DEBUG_TOOL_COREDUMP_PATH_BACKUP*/

		}
#endif /*MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY*/
#else /*original coredump*/
		if (need_nonrelative && cn.corename[0] != '/') {
			printk(KERN_WARNING "Pid %d(%s) can only dump core "\
				"to fully qualified path!\n",
				task_tgid_vnr(current), current->comm);
			printk(KERN_WARNING "Skipping core dump\n");
			goto fail_unlock;
		}

		cprm.file = filp_open(cn.corename,
				 O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE | flag,
				 0600);
#endif /*MP_DEBUG_TOOL_COREDUMP && CONFIG_BINFMT_ELF_COMP*/
		if (IS_ERR(cprm.file))
			goto fail_unlock;

		inode = file_inode(cprm.file);
		if (inode->i_nlink > 1)
			goto close_fail;
		if (d_unhashed(cprm.file->f_path.dentry))
			goto close_fail;
		/*
		 * AK: actually i see no reason to not allow this for named
		 * pipes etc, but keep the previous behaviour for now.
		 */
		if (!S_ISREG(inode->i_mode))
			goto close_fail;
		/*
		 * Dont allow local users get cute and trick others to coredump
		 * into their pre-created files.
		 */
		if (!uid_eq(inode->i_uid, current_fsuid()))
			goto close_fail;
		if (!cprm.file->f_op || !cprm.file->f_op->write)
			goto close_fail;
		if (do_truncate(cprm.file->f_path.dentry, 0, 0, cprm.file))
			goto close_fail;
	}

	/* get us an unshared descriptor table; almost always a no-op */
	retval = unshare_files(&displaced);
	if (retval)
		goto close_fail;
	if (displaced)
		put_files_struct(displaced);

#if (MP_DEBUG_TOOL_COREDUMP == 1) && defined(CONFIG_BINFMT_ELF_COMP)
	printk(KERN_ALERT "* Ultimate CoreDump v1.0 : started dumping core into 'Coredump.%d.gz' file *\n", current->pid);
#else
	printk(KERN_ALERT "* Original coredump : started dumping core into Coredump file *\n");
#endif /*MP_DEBUG_TOOL_COREDUMP && CONFIG_BINFMT_ELF_COMP*/
	if (!dump_interrupted()) {
		file_start_write(cprm.file);
		core_dumped = binfmt->core_dump(&cprm);
		file_end_write(cprm.file);
	}
#if (MP_DEBUG_TOOL_COREDUMP == 1)
#ifdef  CONFIG_BINFMT_ELF_COMP
#if (MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY ==1)
#else
	if (is_usbmodule_loaded)
		printk(KERN_ALERT "***** Create coredump file to USB mount dir ******\n");
	else
		printk(KERN_ALERT "***** usb module is not loaded, so the core is saved to '%s ******\n", cn.corename);
#endif /*MP_DEBUG_TOOL_COREDUMP_PATH_BOOTARGS_ONLY */
#endif /*CONFIG_BINFMT_ELF_COMP*/
#endif /*MP_DEBUG_TOOL_COREDUMP*/
	printk(KERN_ALERT "CoreDump: finished dumping core\n");

	if (core_dumped)
		current->signal->group_exit_code |= 0x80;

	if (ispipe && core_pipe_limit)
		wait_for_dump_helpers(cprm.file);
close_fail:
	if (cprm.file)
		filp_close(cprm.file, NULL);
fail_dropcount:
	if (ispipe)
		atomic_dec(&core_dump_count);
fail_unlock:
	kfree(cn.corename);
fail_corename:
	coredump_finish(mm, core_dumped);
	revert_creds(old_cred);
fail_creds:
	put_cred(cred);
fail:
	return;
}

/*
 * Core dumping helper functions.  These are the only things you should
 * do on a core-file: use only these functions to write out all the
 * necessary info.
 */
int dump_write(struct file *file, const void *addr, int nr)
{
#if (MP_DEBUG_TOOL_COREDUMP == 1) && defined(CONFIG_BINFMT_ELF_COMP)
	int r0;
	int r1;

	r0 = access_ok(VERIFY_READ, addr, nr);
	r1 = file->f_op->write(file, addr, nr, &file->f_pos);

	if (r1 < nr) {
		printk(KERN_ALERT "##### No space left on device(disk full), check your device space \n");
		printk(KERN_ALERT "##### rc : %d, nr : %d \n", r1, nr);
	}

	return r0 && r1 == nr;
#else
	return !dump_interrupted() &&
		access_ok(VERIFY_READ, addr, nr) &&
		file->f_op->write(file, addr, nr, &file->f_pos) == nr;
#endif /*MP_DEBUG_TOOL_COREDUMP && CONFIG_BINFMT_ELF_COMP*/
}
EXPORT_SYMBOL(dump_write);

int dump_seek(struct file *file, loff_t off)
{
	int ret = 1;

	if (file->f_op->llseek && file->f_op->llseek != no_llseek) {
		if (dump_interrupted() ||
		    file->f_op->llseek(file, off, SEEK_CUR) < 0)
			return 0;
	} else {
		char *buf = (char *)get_zeroed_page(GFP_KERNEL);

		if (!buf)
			return 0;
		while (off > 0) {
			unsigned long n = off;

			if (n > PAGE_SIZE)
				n = PAGE_SIZE;
			if (!dump_write(file, buf, n)) {
				ret = 0;
				break;
			}
			off -= n;
		}
		free_page((unsigned long)buf);
	}
	return ret;
}
EXPORT_SYMBOL(dump_seek);
