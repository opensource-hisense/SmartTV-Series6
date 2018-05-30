/*
 * Based on arch/arm/kernel/traps.c
 *
 * Copyright (C) 1995-2009 Russell King
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/signal.h>
#include <linux/personality.h>
#include <linux/kallsyms.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>
#include <linux/hardirq.h>
#include <linux/kdebug.h>
#include <linux/module.h>
#include <linux/kexec.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

#include <asm/atomic.h>
#include <asm/debug-monitors.h>
#include <asm/traps.h>
#include <asm/stacktrace.h>
#include <asm/exception.h>
#include <asm/system_misc.h>

static const char *handler[]= {
	"Synchronous Abort",
	"IRQ",
	"FIQ",
	"Error"
};

int show_unhandled_signals = 1;

#ifdef CONFIG_DEBUG_USER
#if (MP_DEBUG_TOOL_COREDUMP == 1) && defined(CONFIG_SHOW_FAULT_TRACE_INFO)
unsigned int user_debug = 0xff;
#else
unsigned int user_debug;
#endif

static int __init user_debug_setup(char *str)
{
	get_option(&str, &user_debug);
	return 1;
}
__setup("user_debug=", user_debug_setup);
#endif

#if (MP_DEBUG_TOOL_KDEBUG == 1 ) || (MP_DEBUG_TOOL_COREDUMP == 1)
#ifdef CONFIG_SHOW_FAULT_TRACE_INFO
void show_pid_maps(struct task_struct *task)
{
	struct task_struct *t;
	struct mm_struct *mm;
	struct vm_area_struct *vma, *gate_vma;
	struct file *file;
	unsigned long long pgoff = 0;
	unsigned long ino = 0;
	dev_t dev = 0;
	int tpid = 0;
	char path_buf[256];

	printk(KERN_ALERT "-----------------------------------------------------------\n");
	printk(KERN_ALERT "* dump maps on pid (%d)\n", task->pid);
	printk(KERN_ALERT "-----------------------------------------------------------\n");

	if (!down_read_trylock(&task->mm->mmap_sem)) {
		printk(KERN_ALERT "down_read_trylock() failed... do not dump pid maps info\n");
		return;
	}

	gate_vma = get_gate_vma(task->mm);

	vma = task->mm->mmap;
	if (!vma)
		vma = gate_vma;

	while (vma) {
		file = vma->vm_file;
		if (file) {
			struct inode *inode = file->f_dentry->d_inode;

			dev = inode->i_sb->s_dev;
			ino = inode->i_ino;
			pgoff = ((loff_t)vma->vm_pgoff) << PAGE_SHIFT;
		} else {
			dev = 0;
			ino = 0;
			pgoff = 0;
		}

		printk(KERN_ALERT "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %-10lu ",
				vma->vm_start,
				vma->vm_end,
				vma->vm_flags & VM_READ ? 'r' : '-',
				vma->vm_flags & VM_WRITE ? 'w' : '-',
				vma->vm_flags & VM_EXEC ? 'x' : '-',
				vma->vm_flags & VM_MAYSHARE ? 's' : 'p',
				pgoff,
				MAJOR(dev), MINOR(dev), ino);

		if (file) {
			char* p = d_path(&(file->f_path),path_buf, 256);

			if (!IS_ERR(p)) printk("%s", p);
		} else {
			const char *name = arch_vma_name(vma);

			mm = vma->vm_mm;
			tpid = 0;
			if (!name) {
				if (mm) {
					if (vma->vm_start <= mm->brk &&
					    vma->vm_end >= mm->start_brk) {
						name = "[heap]";
					} else if (vma->vm_start <= mm->start_stack &&
					           vma->vm_end >= mm->start_stack) {
						name = "[stack]";
					} else {
						t = task;
						do{
							if (vma->vm_start <= t->user_ssp &&
							    vma->vm_end >= t->user_ssp){
								tpid = t->pid;
								name = t->comm;
								break;
							}
						}while_each_thread(task, t);
					}
				} else {
					name = "[vdso]";
				}
			}
			if (name) {
				if (tpid)
					printk("[tstack: %s: %d]", name, tpid);
				else
					printk("%s", name);
			}
		}
		printk( "\n");

		if (vma->vm_next)
			vma = vma->vm_next;
		else if (vma == gate_vma)
			vma = NULL;
		else
			vma = gate_vma;
	}
	up_read(&task->mm->mmap_sem);

	printk(KERN_ALERT "-----------------------------------------------------------\n\n");
}

static void dump_mem(const char *lvl, const char *str, unsigned long bottom,
		     unsigned long top);

void __show_user_stack(struct task_struct *task, unsigned long sp)
{
	struct vm_area_struct *vma;

	vma = find_vma(task->mm, task->user_ssp);
	if (!vma) {
		printk(KERN_CONT "pid(%d) : printing user stack failed.\n", (int)task->pid);
		return;
	}

	if (sp < vma->vm_start) {
		printk(KERN_CONT "pid(%d) : seems stack overflow.\n"
				 "  sp(0x%08lx), stack vma (0x%08lx ~ 0x%08lx)\n",
				 (int)task->pid, sp, vma->vm_start, vma->vm_end);
		return;
	}

	printk(KERN_CONT "pid(%d) stack vma (0x%08lx ~ 0x%08lx)\n",
			 (int)task->pid, vma->vm_start, vma->vm_end);
	dump_mem(KERN_CONT, "User Stack: ", sp, task->user_ssp);
}

#ifdef CONFIG_SHOW_THREAD_GROUP_STACK
void __show_user_stack_tg(struct task_struct *task)
{
	struct task_struct *g, *p;
	struct pt_regs *regs;

	printk(KERN_CONT "--------------------------------------------------------\n");
	printk(KERN_CONT "* dump all user stack of pid(%d) thread group\n", (int)task->pid);
	printk(KERN_CONT "--------------------------------------------------------\n");

	read_lock(&tasklist_lock);
	do_each_thread(g, p) {
		if (task->mm != p->mm)
			continue;
		if (task->pid == p->pid)
			continue;
		regs = task_pt_regs(p);

        if (compat_user_mode(regs)) {
	     __show_user_stack(p, regs->compat_sp);
        } else {
	     __show_user_stack(p, regs->sp);
        }

		printk(KERN_CONT "\n");
	} while_each_thread(g, p);
	read_unlock(&tasklist_lock);
	printk(KERN_CONT "--------------------------------------------------------\n\n");
}
#else
#define __show_user_stack_tg(t)
#endif /* CONFIG_SHOW_THREAD_GROUP_STACK */

/*
 *  Assumes that user program uses frame pointer
 *  TODO : consider context safety
 */
void show_user_stack(struct task_struct *task, struct pt_regs *regs)
{
	struct vm_area_struct *vma;

	vma = find_vma(task->mm, task->user_ssp);
	if (vma) {
		printk(KERN_CONT "task stack info : pid(%d) stack area (0x%08lx ~ 0x%08lx)\n",
			         (int)task->pid, vma->vm_start, vma->vm_end);
	}

	printk(KERN_CONT "-----------------------------------------------------------\n");
	printk(KERN_CONT "* dump user stack\n");
	printk(KERN_CONT "-----------------------------------------------------------\n");

        if (compat_user_mode(regs)) {
	     __show_user_stack(task, regs->compat_sp);
        } else {
	     __show_user_stack(task, regs->sp);
        }


	printk(KERN_CONT "-----------------------------------------------------------\n\n");
	__show_user_stack_tg(task);
}

#ifdef CONFIG_SHOW_PC_LR_INFO
void dump_mem_kernel(const char *str, unsigned long bottom, unsigned long top)
{
        unsigned long p;
        int i;

        printk(KERN_CONT "%s(0x%08lx to 0x%08lx)\n", str, bottom, top);

        for (p = bottom & ~31; p <= top;) {
                printk(KERN_CONT "%04lx: ", p & 0xffff);
                for (i = 0; i < 8; i++, p += 4) {
                        if (p < bottom || p > top)
                                printk(KERN_CONT "         ");
                        else
                                printk(KERN_CONT "%08lx ", *(unsigned long*)p);
                }
                printk(KERN_CONT "\n");
        }
}


void show_pc_lr(struct task_struct *task, struct pt_regs *regs)
{
	unsigned long addr_pc_start, addr_lr_start;
	unsigned long addr_pc_end, addr_lr_end;
	struct vm_area_struct *vma;

	printk(KERN_CONT "\n");
	printk(KERN_CONT "--------------------------------------------------------------------------------------\n");
	printk(KERN_CONT "PC, LR MEMINFO\n");
	printk(KERN_CONT "--------------------------------------------------------------------------------------\n");
	printk(KERN_CONT "PC:%llx, LR:%llx\n", regs->ARM_pc, regs->ARM_lr);

	//Basic error handling
	if(regs->ARM_pc > 0x400)
		addr_pc_start = regs->ARM_pc - 0x400;   // pc - 1024 byte
	else
		addr_pc_start = 0;

	if(regs->ARM_pc < 0xfffffC00)
		addr_pc_end = regs->ARM_pc + 0x400;     // pc + 1024 byte
	else
		addr_pc_end = 0xffffffff;

	if(regs->ARM_lr > 0x800)
		addr_lr_start = regs->ARM_lr - 0x800;   // lr - 2048 byte
	else
		addr_lr_start = 0;

	if(regs->ARM_lr < 0xfffffC00)
		addr_lr_end = regs->ARM_lr + 0x400;     // lr + 1024 byte
	else
		addr_lr_end = 0xffffffff;

	//Calculate vma print range according which contain PC, LR
	if(((regs->ARM_pc & 0xfff) < 0x400) && !find_vma(task->mm, addr_pc_start))
		addr_pc_start = regs->ARM_pc & (~0xfff);
	if(((regs->ARM_pc & 0xfff) > 0xBFF) && !find_vma(task->mm, addr_pc_end))
		addr_pc_end = (regs->ARM_pc & (~0xfff)) + 0xfff;
	if(((regs->ARM_lr & 0xfff) < 0x800) && !find_vma(task->mm, addr_lr_start))
		addr_lr_start = regs->ARM_lr & (~0xfff);
	if(((regs->ARM_lr & 0xfff) > 0xBFF) && !find_vma(task->mm, addr_lr_end))
		addr_lr_end = (regs->ARM_lr & (~0xfff)) + 0xfff;

	//Find a duplicated address range
	if((addr_lr_start < addr_pc_start) && (addr_lr_end > addr_pc_end))
		addr_pc_start = addr_pc_end;
	else if((addr_pc_start <= addr_lr_start) && (addr_pc_end >= addr_lr_end))
		addr_lr_start = addr_lr_end;
	else if((addr_lr_start <= addr_pc_end) && (addr_lr_end > addr_pc_end))
		addr_lr_start = addr_pc_end + 0x4;
	else if((addr_pc_start <= addr_lr_end) && (addr_pc_end > addr_lr_end))
		addr_pc_start = addr_lr_end + 0x4;

	printk(KERN_CONT "--------------------------------------------------------------------------------------\n");
	if((vma=find_vma(task->mm, regs->ARM_pc)) && (regs->ARM_pc >= vma->vm_start))
		dump_mem(KERN_CONT, "PC meminfo ", addr_pc_start, addr_pc_end);
	else
		printk(KERN_CONT "No VMA for ADDR PC\n");

	printk(KERN_CONT "--------------------------------------------------------------------------------------\n");
	if((vma=find_vma(task->mm, regs->ARM_lr)) && (regs->ARM_lr >= vma->vm_start))
		dump_mem(KERN_CONT, "LR meminfo ", addr_lr_start, addr_lr_end);
	else
		printk(KERN_CONT "No VMA for ADDR LR\n");

	printk(KERN_CONT "--------------------------------------------------------------------------------------\n");
	printk(KERN_CONT "\n");
}

#if 0
static void show_pc_lr_kernel(const struct pt_regs *regs)
{
	unsigned long addr_pc, addr_lr;
	int valid_pc, valid_lr;
	int valid_pc_mod, valid_lr_mod;
	struct module *mod;

	addr_pc = regs->ARM_pc - 0x400;   // for 1024 byte
	addr_lr = regs->ARM_lr - 0x800;   // for 2048 byte

	valid_pc_mod = ((regs->ARM_pc >= VMALLOC_START && regs->ARM_pc < VMALLOC_END) ||
			(regs->ARM_pc >= MODULES_VADDR && regs->ARM_pc < MODULES_END));
	valid_lr_mod = ((regs->ARM_lr >= VMALLOC_START && regs->ARM_lr < VMALLOC_END) ||
			(regs->ARM_lr >= MODULES_VADDR && regs->ARM_lr < MODULES_END));

	valid_pc = (TASK_SIZE <= regs->ARM_pc && regs->ARM_pc < (unsigned long)high_memory)
			 || valid_pc_mod;
	valid_lr = (TASK_SIZE <= regs->ARM_lr && regs->ARM_lr < (unsigned long)high_memory)
			|| valid_lr_mod;

	/* Adjust the addr_pc according to the correct module virtual memory range. */
	if(valid_pc) {
		if (addr_pc < TASK_SIZE)
			addr_pc = TASK_SIZE;
		else if (valid_pc_mod) {
			mod = __module_address(regs->ARM_pc);

			if (!within_module_init(addr_pc, mod) &&
			    !within_module_core(addr_pc, mod))
				addr_pc = regs->ARM_pc & PAGE_MASK;
		}
	}

	/* Adjust the addr_lr according to the correct module virtual memory range. */
	if(valid_lr) {
		if (addr_lr < TASK_SIZE)
			addr_lr = TASK_SIZE;
		else if (valid_lr_mod) {
			mod = __module_address(regs->ARM_lr);
			if (!within_module_init(addr_lr, mod) &&
			    !within_module_core(addr_lr, mod))
				addr_lr = regs->ARM_lr & PAGE_MASK;
		}
	}

	if(valid_pc && valid_lr){
		// find a duplicated address range case1
		if((addr_lr<=regs->ARM_pc) && (regs->ARM_pc<regs->ARM_lr)){
			addr_lr = regs->ARM_pc + 0x4;
		}
		// find a duplicated address rage case2
		else if((addr_pc<=regs->ARM_lr) && (regs->ARM_lr<regs->ARM_pc)){
			addr_pc = regs->ARM_lr + 0x4;
		}
	}

	printk("--------------------------------------------------------------------------------------\n");
	printk("[VDLP] DISPLAY PC, LR in KERNEL Level\n");
	printk("pc:%llx, ra:%llx\n", regs->ARM_pc, regs->ARM_lr);
	printk("--------------------------------------------------------------------------------------\n");

	if(valid_pc){
		dump_mem_kernel("PC meminfo in kernel", addr_pc, regs->ARM_pc);
		printk("--------------------------------------------------------------------------------------\n");
		dump_mem_kernel("PC meminfo in kernel", regs->ARM_pc + 0x4, regs->ARM_pc + 0x20);
	} else {
		printk("[VDLP] Invalid pc addr\n");
	}
	printk("--------------------------------------------------------------------------------------\n");

	if(valid_lr)
		dump_mem_kernel("LR meminfo in kernel", addr_lr, regs->ARM_lr);
	else
		printk("[VDLP] Invalid lr addr\n");
	printk("--------------------------------------------------------------------------------------\n");
	printk("\n");
}
#endif//#if 0

#ifdef CONFIG_DUMP_RANGE_BASED_ON_REGISTER
int is_valid_kernel_addr(unsigned long register_value)
{
	if (register_value < PAGE_OFFSET ||
	    !virt_addr_valid((void*)register_value)){
		//includes checking NULL and user address
		return 0;
	} else {
		return 1;
	}
}

void show_register_memory_kernel(struct pt_regs * regs)
{
	unsigned long start_addr_for_printing = 0;
	unsigned long end_addr_for_printing = 0;
	int register_num;

	printk("--------------------------------------------------------------------------------------\n");
	printk("REGISTER MEMORY INFO\n");
	printk("--------------------------------------------------------------------------------------\n");

	for (register_num = 0; register_num < sizeof(regs->uregs)/sizeof(regs->uregs[0]); register_num++) {
		printk("\n\n* REGISTER : r%d\n",register_num);

		start_addr_for_printing = (regs->uregs[register_num] & PAGE_MASK) - 0x1000; //-4kbyte
		if (regs->uregs[register_num] >= 0xfffff000){
			// if virtual address is 0xffffffff, skip dump address to prevent overflow
			end_addr_for_printing = 0xffffffff;
		} else {
			end_addr_for_printing = (regs->uregs[register_num] & PAGE_MASK) + PAGE_SIZE + 0xfff;
		} //+about 8kbyte

		if (!is_valid_kernel_addr(regs->uregs[register_num])) {
			printk("# Register value 0x%lx is wrong address.\n", regs->uregs[register_num]);
			printk("# We can't do anything.\n");
			printk("# So, we search next register.\n");
			continue;
		}

		if (!is_valid_kernel_addr(start_addr_for_printing)) {
			printk("# 'start_addr_for_printing' is wrong address.\n");
			printk("# So, we use just 'regs->uregs[register_num] & PAGE_MASK)'\n");
			start_addr_for_printing = (regs->uregs[register_num] & PAGE_MASK);
		}

		if (!is_valid_kernel_addr(end_addr_for_printing)) {
			printk("# 'end_addr_for_printing' is wrong address.\n");
			printk("# So, we use 'PAGE_ALIGN(regs->uregs[register_num]) + PAGE_SIZE-1'\n");
			end_addr_for_printing = (regs->uregs[register_num] & PAGE_MASK) + PAGE_SIZE-1;
		}

		// dump
		printk("# r%d register :0x%lx, start_addr : 0x%lx, end_addr : 0x%lx\n",
			register_num, regs->uregs[register_num], start_addr_for_printing, end_addr_for_printing);
		printk("--------------------------------------------------------------------------------------\n");
		dump_mem_kernel("meminfo ", start_addr_for_printing, end_addr_for_printing);
		printk("--------------------------------------------------------------------------------------\n");
		printk("\n");
	}
}
#endif
#endif /* #ifdef CONFIG_SHOW_PC_LR_INFO */

#ifndef CONFIG_SEPARATE_PRINTK_FROM_USER
#define sep_printk_start
#define sep_printk_end
#else
extern void _sep_printk_start(void);
extern void _sep_printk_end(void);
#define sep_printk_start _sep_printk_start
#define sep_printk_end _sep_printk_end
#endif

#ifdef CONFIG_RUN_TIMER_DEBUG
extern void show_timer_list(void);
#endif

void show_usr_info(struct task_struct *task, struct pt_regs *regs, unsigned long addr)
{
	static atomic_t prn_once = ATOMIC_INIT(0);

	if(atomic_cmpxchg(&prn_once, 0, 1)) {
		return;
	}

#ifdef CONFIG_SEPARATE_PRINTK_FROM_USER
	sep_printk_start();
#endif

	console_verbose();      /* BSP patch : enable console while show_info */
	preempt_disable();

#ifdef CONFIG_VDLP_VERSION_INFO
	printk(KERN_ALERT"================================================================================\n");
	printk(KERN_ALERT" KERNEL Version : %s\n", DTV_KERNEL_VERSION);
	printk(KERN_ALERT"================================================================================\n");
#endif

#ifdef CONFIG_SUPPORT_REBOOT
	if( !print_permit() && reboot_permit() )
	{
		micom_reboot();
		while(1);
	}
#endif

#ifdef CONFIG_RUN_TIMER_DEBUG
	show_timer_list();
#endif

#ifdef CONFIG_SHOW_PC_LR_INFO
	show_pc_lr(task, regs);
#endif
	if(addr) {
		show_pte(task->mm, addr);
	}
	show_regs(regs);
	show_pid_maps(task);
	show_user_stack(task, regs);
	preempt_enable();

#ifdef CONFIG_SUPPORT_REBOOT
	if( reboot_permit() )
	{
		micom_reboot();
		while(1);
	}
#endif

#ifdef CONFIG_SEPARATE_PRINTK_FROM_USER
	sep_printk_end();
#endif
}
EXPORT_SYMBOL(show_usr_info);
#endif /*CONFIG_SHOW_FAULT_TRACE_INFO*/
#endif /*MP_DEBUG_TOOL_KDEBUG == 1 || MP_DEBUG_TOOL_COREDUMP == 1*/


/*
 * Dump out the contents of some memory nicely...
 */
static void dump_mem(const char *lvl, const char *str, unsigned long bottom,
		     unsigned long top)
{
	unsigned long first;
	mm_segment_t fs;
	int i;

	/*
	 * We need to switch to kernel mode so that we can use __get_user
	 * to safely read from kernel space.  Note that we now dump the
	 * code first, just in case the backtrace kills us.
	 */
	fs = get_fs();
	set_fs(KERNEL_DS);

	printk("%s%s(0x%016lx to 0x%016lx)\n", lvl, str, bottom, top);

	for (first = bottom & ~31; first < top; first += 32) {
		unsigned long p;
		char str[sizeof(" 12345678") * 8 + 1];

		memset(str, ' ', sizeof(str));
		str[sizeof(str) - 1] = '\0';

		for (p = first, i = 0; i < 8 && p < top; i++, p += 4) {
			if (p >= bottom && p < top) {
				unsigned int val;
				if (__get_user(val, (unsigned int *)p) == 0)
					sprintf(str + i * 9, " %08x", val);
				else
					sprintf(str + i * 9, " ????????");
			}
		}
		printk("%s%04lx:%s\n", lvl, first & 0xffff, str);
	}

	set_fs(fs);
}

static void dump_backtrace_entry(unsigned long where, unsigned long stack)
{
#ifdef CONFIG_KALLSYMS
	printk("[<%08lx>] (%pS) \n", where, (void *)where);
#else
	printk("Function entered at [<%08lx>] \n", where);
#endif

	print_ip_sym(where);
	if (in_exception_text(where))
		dump_mem("", "Exception stack", stack,
			 stack + sizeof(struct pt_regs));
}

#if 0
#ifndef CONFIG_ARM_UNWIND
/*
 * Stack pointers should always be within the kernels view of
 * physical memory.  If it is not there, then we can't dump
 * out any information relating to the stack.
 */
static int verify_stack(unsigned long sp)
{
	if (sp < PAGE_OFFSET ||
	    (sp > (unsigned long)high_memory && high_memory != NULL))
		return -EFAULT;

	return 0;
}
#endif
#endif //#if 0

static void dump_instr(const char *lvl, struct pt_regs *regs)
{
	unsigned long addr = instruction_pointer(regs);
	mm_segment_t fs;
	char str[sizeof("00000000 ") * 5 + 2 + 1], *p = str;
	int i;

	/*
	 * We need to switch to kernel mode so that we can use __get_user
	 * to safely read from kernel space.  Note that we now dump the
	 * code first, just in case the backtrace kills us.
	 */
	fs = get_fs();
	set_fs(KERNEL_DS);

	for (i = -4; i < 1; i++) {
		unsigned int val, bad;

		bad = __get_user(val, &((u32 *)addr)[i]);

		if (!bad)
			p += sprintf(p, i == 0 ? "(%08x) " : "%08x ", val);
		else {
			p += sprintf(p, "bad PC value");
			break;
		}
	}
	printk("%sCode: %s\n", lvl, str);

	set_fs(fs);
}

static void dump_backtrace(struct pt_regs *regs, struct task_struct *tsk)
{
	struct stackframe frame;
	const register unsigned long current_sp asm ("sp");

	pr_debug("%s(regs = %p tsk = %p)\n", __func__, regs, tsk);

	if (!tsk)
		tsk = current;

	if (regs) {
		frame.fp = regs->regs[29];
		frame.sp = regs->sp;
		frame.pc = regs->pc;
	} else if (tsk == current) {
		frame.fp = (unsigned long)__builtin_frame_address(0);
		frame.sp = current_sp;
		frame.pc = (unsigned long)dump_backtrace;
	} else {
		/*
		 * task blocked in __switch_to
		 */
		frame.fp = thread_saved_fp(tsk);
		frame.sp = thread_saved_sp(tsk);
		frame.pc = thread_saved_pc(tsk);
	}

	printk("Call trace:\n");
	while (1) {
		unsigned long where = frame.pc;
		int ret;

		ret = unwind_frame(&frame);
		if (ret < 0)
			break;
		dump_backtrace_entry(where, frame.sp);
	}
}

void show_stack(struct task_struct *tsk, unsigned long *sp)
{
	dump_backtrace(NULL, tsk);
	barrier();
}

#ifdef CONFIG_PREEMPT
#define S_PREEMPT " PREEMPT"
#else
#define S_PREEMPT ""
#endif
#ifdef CONFIG_SMP
#define S_SMP " SMP"
#else
#define S_SMP ""
#endif

static int __die(const char *str, int err, struct thread_info *thread,
		 struct pt_regs *regs)
{
	struct task_struct *tsk = thread->task;
	static int die_counter;
	int ret;

	pr_emerg("Internal error: %s: %x [#%d]" S_PREEMPT S_SMP "\n",
		 str, err, ++die_counter);

	/* trap and error numbers are mostly meaningless on ARM */
	ret = notify_die(DIE_OOPS, str, regs, err, 0, SIGSEGV);
	if (ret == NOTIFY_STOP)
		return ret;

	print_modules();
	__show_regs(regs);
	pr_emerg("Process %.*s (pid: %d, stack limit = 0x%p)\n",
		 TASK_COMM_LEN, tsk->comm, task_pid_nr(tsk), thread + 1);

	if (!user_mode(regs) || in_interrupt()) {
		dump_mem(KERN_EMERG, "Stack: ", regs->sp,
			 THREAD_SIZE + (unsigned long)task_stack_page(tsk));
		dump_backtrace(regs, tsk);
		dump_instr(KERN_EMERG, regs);
	}

	return ret;
}

static DEFINE_RAW_SPINLOCK(die_lock);

/*
 * This function is protected against re-entrancy.
 */
void die(const char *str, struct pt_regs *regs, int err)
{
	struct thread_info *thread = current_thread_info();
	int ret;

	oops_enter();

	raw_spin_lock_irq(&die_lock);
	console_verbose();
	bust_spinlocks(1);
	ret = __die(str, err, thread, regs);

	if (regs && kexec_should_crash(thread->task))
		crash_kexec(regs);

	bust_spinlocks(0);
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	raw_spin_unlock_irq(&die_lock);
	oops_exit();

	if (in_interrupt())
		panic("Fatal exception in interrupt");
	if (panic_on_oops)
		panic("Fatal exception");
	if (ret != NOTIFY_STOP)
		do_exit(SIGSEGV);
}

void arm64_notify_die(const char *str, struct pt_regs *regs,
		      struct siginfo *info, int err)
{

	printk("----------------------------------------------------------------------\n");
	if (user_mode(regs)){
#if (MP_DEBUG_TOOL_COREDUMP == 1)
#ifdef CONFIG_SHOW_FAULT_TRACE_INFO
#ifdef CONFIG_ANDROID
       /*prevent kernel coredump message mess up with Android coredump message*/
#else
	show_usr_info(current, regs, regs->pc);
#endif /*CONFIG_ANDROID*/
#endif /*CONFIG_SHOW_FAULT_TRACE_INFO */
#endif /*MP_DEBUG_TOOL_COREDUMP*/
		force_sig_info(info->si_signo, info, current);
	}
	else
		die(str, regs, err);
}

#ifdef CONFIG_GENERIC_BUG
int is_valid_bugaddr(unsigned long pc)
{
#ifdef CONFIG_THUMB2_KERNEL
	unsigned short bkpt;
#else
	unsigned long bkpt;
#endif

	if (probe_kernel_address((unsigned *)pc, bkpt))
		return 0;

	return bkpt == BUG_INSTR_VALUE;
}
#endif //CONFIG_GENERIC_BUG

static LIST_HEAD(undef_hook);
static DEFINE_RAW_SPINLOCK(undef_lock);

void register_undef_hook(struct undef_hook *hook)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_add(&hook->node, &undef_hook);
	raw_spin_unlock_irqrestore(&undef_lock, flags);
}

void unregister_undef_hook(struct undef_hook *hook)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_del(&hook->node);
	raw_spin_unlock_irqrestore(&undef_lock, flags);
}

static int call_undef_hook(struct pt_regs *regs)
{
	struct undef_hook *hook;
	unsigned long flags;
	u32 instr;
	int (*fn)(struct pt_regs *regs, u32 instr) = NULL;
	void __user *pc = (void __user *)instruction_pointer(regs);

	if (!user_mode(regs))
		return 1;

	if (compat_thumb_mode(regs)) {
		/* 16-bit Thumb instruction */
		if (get_user(instr, (u16 __user *)pc))
			goto exit;
		instr = le16_to_cpu(instr);
		if (aarch32_insn_is_wide(instr)) {
			u32 instr2;

			if (get_user(instr2, (u16 __user *)(pc + 2)))
				goto exit;
			instr2 = le16_to_cpu(instr2);
			instr = (instr << 16) | instr2;
		}
	} else {
		/* 32-bit ARM instruction */
		if (get_user(instr, (u32 __user *)pc))
			goto exit;
		instr = le32_to_cpu(instr);
	}

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_for_each_entry(hook, &undef_hook, node)
		if ((instr & hook->instr_mask) == hook->instr_val &&
			(regs->pstate & hook->pstate_mask) == hook->pstate_val)
			fn = hook->fn;

	raw_spin_unlock_irqrestore(&undef_lock, flags);
exit:
	return fn ? fn(regs, instr) : 1;
}

asmlinkage void __exception do_undefinstr(struct pt_regs *regs)
{
	u32 instr;
	siginfo_t info;
	void __user *pc = (void __user *)instruction_pointer(regs);

	/* check for AArch32 breakpoint instructions */
	if (!aarch32_break_handler(regs))
		return;

	if (call_undef_hook(regs) == 0)
		return;

	if (user_mode(regs)) {
		if (compat_thumb_mode(regs)) {
			if (get_user(instr, (u16 __user *)pc))
				goto die_sig;
			if (is_wide_instruction(instr)) {
				u32 instr2;
				if (get_user(instr2, (u16 __user *)pc+1))
					goto die_sig;
				instr <<= 16;
				instr |= instr2;
			}
		} else if (get_user(instr, (u32 __user *)pc)) {
			goto die_sig;
		}
	} else {
		/* kernel mode */
		instr = *((u32 *)pc);
	}

die_sig:
	if (show_unhandled_signals && unhandled_signal(current, SIGILL) &&
	    printk_ratelimit()) {
		pr_info("%s[%d]: undefined instruction: pc=%p\n",
			current->comm, task_pid_nr(current), pc);
		dump_instr(KERN_INFO, regs);
	}

#ifdef CONFIG_DEBUG_USER
	if (user_debug & UDBG_UNDEFINED) {
		printk(KERN_INFO "%s (%d): undefined instruction: pc=%p\n",
			current->comm, task_pid_nr(current), pc);
		dump_instr(KERN_INFO, regs);
	}
#endif

	info.si_signo = SIGILL;
	info.si_errno = 0;
	info.si_code  = ILL_ILLOPC;
	info.si_addr  = pc;

	arm64_notify_die("Oops - undefined instruction", regs, &info, 0);
}

long compat_arm_syscall(struct pt_regs *regs);

asmlinkage long do_ni_syscall(struct pt_regs *regs)
{
#ifdef CONFIG_COMPAT
	long ret;
	if (is_compat_task()) {
		ret = compat_arm_syscall(regs);
		if (ret != -ENOSYS)
			return ret;
	}
#endif

	if (show_unhandled_signals && printk_ratelimit()) {
		pr_info("%s[%d]: syscall %d\n", current->comm,
			task_pid_nr(current), (int)regs->syscallno);
		dump_instr("", regs);
		if (user_mode(regs))
			__show_regs(regs);
	}

#ifdef CONFIG_DEBUG_USER
	/*
	 * experience shows that these seem to indicate that
	 * something catastrophic has happened
	 */
	if (user_debug & UDBG_SYSCALL) {
		printk("[%d] %s: arm syscall %d\n",
		       task_pid_nr(current), current->comm, no);
		dump_instr("", regs);
		if (user_mode(regs)) {
			__show_regs(regs);
			c_backtrace(regs->ARM_fp, processor_mode(regs));
		}
	}
#endif
	return sys_ni_syscall();
}

#ifdef CONFIG_DENVER_CPU
/*
 * MCA assert register dump
*/
void dump_mca_debug(void)
{
	unsigned long cap;

	unsigned long serri_ctrl, serri_status, serri_addr,
		serri_misc1, serri_misc2;

	pr_crit("Machine Check Architecture assert failed:\n");

	asm volatile("mrs %0, s3_0_c15_c3_0" : "=r" (cap) : );
	cap = cap & 0xff;

	switch(cap)
	{
	case 11:
		asm volatile("mrs %0, s3_0_c15_c11_4" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c11_5" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c11_6" : "=r" (serri_addr) : );
		pr_crit("[Bank 10] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 10:
		asm volatile("mrs %0, s3_0_c15_c10_6" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c10_7" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c11_0" : "=r" (serri_addr) : );
		pr_crit("[Bank 9] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 9:
		asm volatile("mrs %0, s3_0_c15_c10_0" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c10_1" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c10_2" : "=r" (serri_addr) : );
		pr_crit("[Bank 8] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 8:
		asm volatile("mrs %0, s3_0_c15_c9_2" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c9_3" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c9_4" : "=r" (serri_addr) : );
		pr_crit("[Bank 7] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 7:
		asm volatile("mrs %0, s3_0_c15_c8_4" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c8_5" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c8_6" : "=r" (serri_addr) : );
		asm volatile("mrs %0, s3_0_c15_c8_7" : "=r" (serri_misc1) : );
		asm volatile("mrs %0, s3_0_c15_c9_0" : "=r" (serri_misc2) : );
		pr_crit("[Bank 6] ctrl:0x%016lx status:0x%016lx addr:0x%016lx \
misc1:0x%016lx, misc2:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr, serri_misc1, serri_misc2);
	case 6:
		asm volatile("mrs %0, s3_0_c15_c7_6" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c7_7" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c8_0" : "=r" (serri_addr) : );
		pr_crit("[Bank 5] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 5:
		asm volatile("mrs %0, s3_0_c15_c7_0" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c7_1" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c7_2" : "=r" (serri_addr) : );
		pr_crit("[Bank 4] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 4:
		asm volatile("mrs %0, s3_0_c15_c6_2" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c6_3" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c6_4" : "=r" (serri_addr) : );
		pr_crit("[Bank 3] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 3:
		asm volatile("mrs %0, s3_0_c15_c5_4" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c5_5" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c5_6" : "=r" (serri_addr) : );
		pr_crit("[Bank 2] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 2:
		asm volatile("mrs %0, s3_0_c15_c4_6" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c4_7" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c5_0" : "=r" (serri_addr) : );
		pr_crit("[Bank 1] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
	case 1:
		asm volatile("mrs %0, s3_0_c15_c4_0" : "=r" (serri_ctrl) : );
		asm volatile("mrs %0, s3_0_c15_c4_1" : "=r" (serri_status) : );
		asm volatile("mrs %0, s3_0_c15_c4_2" : "=r" (serri_addr) : );
		pr_crit("[Bank 0] ctrl:0x%016lx status:0x%016lx addr:0x%016lx\n",
			serri_ctrl, serri_status, serri_addr);
		break;
	default:
		if(!cap)
			pr_crit("no MCA banks implemented\n");
		else
			pr_crit("unknown MCA bank configuration\n");
		break;
	}

	return;
}
#endif /* CONFIG_DENVER_CPU */

/*
 * bad_mode handles the impossible case in the exception vector.
 */
asmlinkage void bad_mode(struct pt_regs *regs, int reason, unsigned int esr)
{
	siginfo_t info;
	void __user *pc = (void __user *)instruction_pointer(regs);
	console_verbose();

#ifdef CONFIG_DENVER_CPU
	unsigned long serr_status;
	/* check for MCA assert */
	asm volatile("mrs %0, s3_0_c15_c3_1" : "=r" (serr_status));
	if(serr_status & 4)
	{
		serr_status = 0;
		asm volatile("msr s3_0_c15_c3_1, %0" : : "r" (serr_status));
		dump_mca_debug();
	}
#endif

	pr_crit("Bad mode in %s handler detected, code 0x%08x\n",
		handler[reason], esr);
	__show_regs(regs);

#ifdef CONFIG_DEBUG_USER
	if (user_debug & UDBG_UDBG_BADABORT) {
		printk(KERN_INFO "%s (%d): bad mode: pc=%p\n",
			current->comm, task_pid_nr(current), pc);
		dump_instr(KERN_INFO, regs);
	}
#endif

	info.si_signo = SIGILL;
	info.si_errno = 0;
	info.si_code  = ILL_ILLOPC;
	info.si_addr  = pc;

	arm64_notify_die("Oops - bad mode", regs, &info, 0);
}

void __pte_error(const char *file, int line, unsigned long val)
{
	printk("%s:%d: bad pte %016lx.\n", file, line, val);
}

void __pmd_error(const char *file, int line, unsigned long val)
{
	printk("%s:%d: bad pmd %016lx.\n", file, line, val);
}

void __pgd_error(const char *file, int line, unsigned long val)
{
	printk("%s:%d: bad pgd %016lx.\n", file, line, val);
}

void __init trap_init(void)
{
	return;
}
