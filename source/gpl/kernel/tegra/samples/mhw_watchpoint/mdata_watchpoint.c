////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-2018 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    mdata_watchpoint.c
/// @brief  Mstar kernel module that places a breakpoint over specific address
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * mdata_watchpoint.c - HW Breakpoint file to watch specific address
 *
 * usage:
 *     insmod mdata_watchpoint.ko
 *        echo enable $slot $addr $mask_len > /proc/mstar_watchpoint
 *        echo filter $PID $process_name > /proc/msatr_watchpoint
 *        echo disable $slot > /proc/mstar_watchpoint
 *        echo info > /proc/mstar_watchpoint
 *     rmmod mdata_watchpoint
 *
 * This file is a kernel module that places a breakpoint over specific Address
 * variable using Hardware Breakpoint register. The corresponding handler which
 * prints a backtrace is invoked every time a write operation is performed on
 * that variable.
 *
 * Copyright (C) MStar Corporation, 2016
 *
 */
#include <linux/module.h>    /* Needed by all modules */
#include <linux/kernel.h>    /* Needed for KERN_INFO */
#include <linux/init.h>      /* Needed for the macros */
#include <linux/kallsyms.h>

#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <linux/proc_fs.h>   /* Needed for proc_fs */
#include <linux/uaccess.h>   /* Needed for copy_from_user */
#include <linux/string.h>    /* Needed for strsep */
#include <linux/slab.h>      /* Needed for kfree */
#include <asm/cputype.h>     /* Needed for read_cpuid */

#define MSTAR_DEFAULT_MASK_LEN 4
#define MSTAR_WATCHPOINT_BUFFER_LEN 64
#define MONITOR_MAX_PID 65536

static struct perf_event * __percpu **mstar_hbp;
static struct perf_event * __percpu **mstar_hbp2;
static bool *register_handler = NULL;
static bool *register_breakpoint_handler = NULL;

static char mstar_watcpoint_node[] = "mstar_watchpoint";
static bool default_dump_enable = true;
static bool is_watchpoint = false;
static bool is_breakpoint = false;
static bool is_disable_all = false;
static bool is_first_register = true;
static int monitor_pid = 0;
static char monitor_thread_name[MSTAR_WATCHPOINT_BUFFER_LEN] = {0};
static int register_slot_num = 0;

extern void show_usr_info(struct task_struct *task, struct pt_regs *regs, unsigned long addr);

static void mstar_hbp_handler(struct perf_event *bp,
                   struct perf_sample_data *data,
                   struct pt_regs *regs)
{
    printk(KERN_INFO "pid:%d, monitor_pid:%d\n", current->pid, monitor_pid);
    printk(KERN_INFO "process name:%s, monitor_thread_name:%s\n", current->comm, monitor_thread_name);

    if(default_dump_enable || ((current->pid == monitor_pid) || !strncmp(current->comm, monitor_thread_name,strlen(current->comm))) )
    {
        dump_stack();
        printk(KERN_INFO "Dump stack from mstar_hbp_handler\n");
#if defined (CONFIG_ARM64)
        show_usr_info(current, regs, regs->pc);
#else
        show_usr_info(current, regs, regs->ARM_pc);
#endif
        printk(KERN_INFO "Dump user info from mstar_hbp_handler\n");
    }
#if defined (CONFIG_ARM64)
    /*****************************************************************************
     * ARM64 watchpoint will hit infinite loop while watchpoint handler triggered
     * shift pc to solve this problem
     *****************************************************************************/
    regs->pc += 4;
#endif
}

#if defined (CONFIG_ARM64)
/* Determine number of BRP registers available. */
static int get_total_num_brps(void)
{
    return ((read_cpuid(ID_AA64DFR0_EL1) >> 12) & 0xf) + 1;
}

/* Determine number of WRP registers available. */
static int get_total_num_wrps(void)
{
    return ((read_cpuid(ID_AA64DFR0_EL1) >> 20) & 0xf) + 1;
}
#else
#include <asm/hw_breakpoint.h>

/* Determine number of BRP registers available. */
static int get_total_num_brps(void)
{
    u32 didr;
    ARM_DBG_READ(c0, c0, 0, didr);
    return ((didr >> 24) & 0xf) + 1;
}
/* Determine number of WRP registers available. */
static int get_total_num_wrps(void)
{
    u32 didr;
    ARM_DBG_READ(c0, c0, 0, didr);
    return ((didr >> 28) & 0xf) + 1;
}
#endif

static void unregister_all_slot(void)
{
    int cnt = 0;
    int watchpoint_slot_num = 0, breakpoint_slot_num = 0;

    watchpoint_slot_num = get_total_num_wrps();
    breakpoint_slot_num = get_total_num_brps();

    if (register_slot_num > 0)
    {
        printk(KERN_INFO "HW Watchpoint slot list:\n");
        for (cnt=0; cnt<watchpoint_slot_num; cnt++)
        {
            if(register_handler[cnt])
            {
                unregister_wide_hw_breakpoint(mstar_hbp[cnt]);
                register_slot_num--;
                printk(KERN_INFO "HW Watchpoint slot mstar_hbp[%d] uninstalled, register_slot_num: (%d)\n", cnt, register_slot_num);

                register_handler[cnt] = false;
            }
            else
                printk(KERN_INFO "HW Watchpoint slot mstar_hbp[%d] not register yet, skip unregister requirement!\n", cnt);
        }

        printk(KERN_INFO "\nHW Breakpoint slot list:\n");
        for (cnt=0; cnt<breakpoint_slot_num; cnt++)
        {
            if(register_breakpoint_handler[cnt])
            {
                unregister_wide_hw_breakpoint(mstar_hbp2[cnt]);
                register_slot_num--;
                printk(KERN_INFO "HW Breakpoint slot mstar_hbp2[%d] uninstalled, register_slot_num: (%d)\n", cnt, register_slot_num);

                register_breakpoint_handler[cnt] = false;
            }
            else
                printk(KERN_INFO "HW Breakpoint slot mstar_hbp2[%d] not register yet, skip unregister requirement!\n", cnt);
        }
    }
    else
        printk(KERN_INFO "There is no any installed slot, register_slot_num: (%d)\n", register_slot_num);
}

static void unregister_one_slot(int monitor_slot)
{
    if(is_watchpoint)
    {
        if (register_handler[monitor_slot])
        {
            unregister_wide_hw_breakpoint(mstar_hbp[monitor_slot]);
            register_slot_num--;
            printk(KERN_INFO "HW Watchpoint slot mstar_hbp[%d] uninstalled, register_slot_num: (%d)\n", monitor_slot, register_slot_num);

            register_handler[monitor_slot] = false;
        }
        else
            printk(KERN_INFO "HW Watchpoint slot mstar_hbp[%d] not register yet, skip unregister requirement!\n", monitor_slot);
    }

    if(is_breakpoint)
    {
        if (register_breakpoint_handler[monitor_slot])
        {
            unregister_wide_hw_breakpoint(mstar_hbp2[monitor_slot]);
            register_slot_num--;
            printk(KERN_INFO "HW Breakpoint slot mstar_hbp2[%d] uninstalled, register_slot_num: (%d)\n", monitor_slot, register_slot_num);

            register_breakpoint_handler[monitor_slot] = false;
        }
        else
            printk(KERN_INFO "HW Breakpoint slot mstar_hbp2[%d] not register yet, skip unregister requirement!\n", monitor_slot);
    }
}

static void register_slot(int slot, unsigned long Addr, int mask_len)
{
    struct perf_event_attr attr;
    int ret, i = 0;
    int watchpoint_slot_num = 0, breakpoint_slot_num = 0;

    watchpoint_slot_num = get_total_num_wrps();
    breakpoint_slot_num = get_total_num_brps();

    hw_breakpoint_init(&attr);

    attr.bp_addr = Addr;

    /* Alloc necessary memory while the first time register slot */
    if (is_first_register)
    {
        register_handler = (bool *)kmalloc(sizeof(bool) * watchpoint_slot_num, GFP_ATOMIC);
        register_breakpoint_handler = (bool *)kmalloc(sizeof(bool) * breakpoint_slot_num, GFP_ATOMIC);

        mstar_hbp = (struct perf_event * __percpu**)kmalloc(sizeof(struct perf_event * __percpu *) * watchpoint_slot_num, GFP_ATOMIC);
        mstar_hbp2 = (struct perf_event * __percpu**)kmalloc(sizeof(struct perf_event * __percpu *) * breakpoint_slot_num, GFP_ATOMIC);

        /* Assign default flag while the first time register slot */
        for (i = 0; i < watchpoint_slot_num; i++)
            register_handler[i] = false;

        for (i = 0; i < breakpoint_slot_num; i++)
            register_breakpoint_handler[i] = false;

        is_first_register = false;
    }

    /* error handling for double register */
    if(is_watchpoint)
    {
        attr.bp_len = mask_len;
        attr.bp_type = HW_BREAKPOINT_W | HW_BREAKPOINT_R;

        if(register_handler[slot])
            printk(KERN_INFO "HW Watchpoint mstar_hbp[%d] alreay register, please unregister it first!\n", slot);
        else
        {
            mstar_hbp[slot] = register_wide_hw_breakpoint(&attr, mstar_hbp_handler, NULL);
            if (IS_ERR((void __force *)mstar_hbp[slot]))
            {
                ret = PTR_ERR((void __force *)mstar_hbp[slot]);
                printk(KERN_INFO "Watchpoint mstar_hbp[%d] registration failed, ret: (%d)\n", slot, ret);
            }
            else
            {
                register_handler[slot] = true;
                register_slot_num++;
                printk(KERN_INFO "HW Watchpoint slot [%d] installed, register_slot_num: (%d)\n", slot, register_slot_num);
            }
        }
    }

    if(is_breakpoint)
    {
        attr.bp_len = MSTAR_DEFAULT_MASK_LEN;
        attr.bp_type = HW_BREAKPOINT_X;

        if(register_breakpoint_handler[slot])
            printk(KERN_INFO "HW Breakpoint mstar_hbp2[%d] alreay register, please unregister it first!\n", slot);
        else
        {
            mstar_hbp2[slot] = register_wide_hw_breakpoint(&attr, mstar_hbp_handler, NULL);
            if (IS_ERR((void __force *)mstar_hbp2[slot])) {
                ret = PTR_ERR((void __force *)mstar_hbp2[slot]);
                printk(KERN_INFO "Breakpoint mstar_hbp2[%d] registration failed\n", slot);
            }
            else {
                register_breakpoint_handler[slot] = true;
                register_slot_num++;
                printk(KERN_INFO "HW Breakpoint slot [%d] installed, register_slot_num: (%d)\n", slot, register_slot_num);
            }
        }
    }
}

static void show_usage(void)
{
    printk(KERN_INFO "Usage:\n");
    printk(KERN_INFO "   echo enable watchpoint/breakpoint $slot_num $addr $mask_len > /proc/mstar_watchpoint\n");
    printk(KERN_INFO "   echo filter pid=$PID pname=$PROCESS_NAME > /proc/mstar_watchpoint\n");
    printk(KERN_INFO "   echo disable watchpoint/breakpoint/all $slot_num > /proc/mstar_watchpoint\n");
    printk(KERN_INFO "   echo info > /proc/mstar_watchpoint\n");
}

static void parse_pid_pname(char *parse_str)
{
    int name_len = 0;
    char *parse_pch = NULL;

    if (!strncmp(parse_str, "pid=", 4))
    {
        /* get "pid" string, so do nothing */
        parse_pch = strsep(&parse_str, "=");
        /* get $PID */
        parse_pch = strsep(&parse_str, "=");

        monitor_pid = simple_strtol(parse_pch, NULL, 0);

        if(monitor_pid < 0 || monitor_pid > MONITOR_MAX_PID)
        {
            printk(KERN_INFO "The input pid is invalid , only allow pid 0~99999, use the default pid value (0)\n");
            monitor_pid = 0; // use default process pid
            default_dump_enable = true;
        }
        else
            default_dump_enable = false;
    }
    else if (!strncmp(parse_str, "pname=", 6))
    {
        /* get "pname" string, so do nothing */
        parse_pch = strsep(&parse_str, "=");
        /* get $PROCESS_NAME */
        parse_pch = strsep(&parse_str, "=");

        //error handling to prevent filter_pch provide invalid string
        if (sizeof(parse_pch) >= (MSTAR_WATCHPOINT_BUFFER_LEN-1) )
        {
            name_len = MSTAR_WATCHPOINT_BUFFER_LEN - 1;
            parse_pch[name_len]='\0';
        }
        else
            name_len = sizeof(parse_pch);

        strncpy(monitor_thread_name, parse_pch, name_len);
        default_dump_enable = false;
    }
    else
    {
        printk(KERN_INFO "invalid command!\n");
        show_usage();
    }
}

static int mhw_watch_open(struct inode *inode, struct file *file)
{
    return 0;
}
static ssize_t mhw_watch_read(struct file *fp, char *bufp, size_t len, loff_t *where)
{
    return 0;
}

static int mhw_watch_release(struct inode *inode, struct file * file)
{
    return 0;
}

static ssize_t mhw_watch_write(struct file *file, const char __user *buf,
                size_t count, loff_t *ppos)
{
    char buffer[MSTAR_WATCHPOINT_BUFFER_LEN];
    int slot = 0;
    int command_cnt = 0;
    char *str = NULL;

    if (!count)
        return count;

    if (copy_from_user(buffer, buf, count))
        return -EFAULT;

    str = kstrdup(buffer, GFP_KERNEL);

    if(!str)
    {
        printk(KERN_INFO "kstrdup failed\n");
        return -ENOMEM;
    }

    buffer[count] = '\0';
    printk(KERN_ERR "incoming command line: %s\n", buffer);

    if(!strncmp(buffer, "enable", 6)) //enable watchpoint/breakpoint $slot $addr $mask_len > /proc/mstar_watchpoint
    {
        char *pch = NULL;
        unsigned long Addr = 0;
        int mask_len = MSTAR_DEFAULT_MASK_LEN;

        command_cnt = 0;
        pch = strsep(&str, " ");
        while(pch != NULL)
        {
            switch (command_cnt)
            {
                case 0:
                    //do nothing, since command_cnt=0 is mappint to command "enable"
                    break;
                case 1:
                    if(!strncmp(pch, "watchpoint", 10))
                        is_watchpoint = true;
                    else if(!strncmp(pch, "breakpoint", 10))
                        is_breakpoint = true;
                    else
                    {
                        printk(KERN_INFO "invalid command!\n");
                        show_usage();
                        goto error_exit;
                    }
                    break;
                case 2:
                    slot = simple_strtol(pch, NULL, 0);

                    if(is_watchpoint && (slot < 0 || slot > (get_total_num_wrps() - 1)))
                    {
                        printk(KERN_INFO "Invalid slot number, only support watchpoint slot 0 ~ %d\n", (get_total_num_wrps() - 1));
                        printk(KERN_INFO "Use default slot number [0]\n");
                        slot=0;
                    }
                    if(is_breakpoint && (slot < 0 || slot > (get_total_num_brps() - 1)))
                    {
                        printk(KERN_INFO "Invalid slot number, only support breakpoint slot 0 ~ %d\n", (get_total_num_brps() - 1));
                        printk(KERN_INFO "Use default slot number [0]\n");
                        slot=0;
                    }
                    break;
                case 3:
                    Addr=simple_strtol(pch, NULL, 0);
                    break;
                case 4:
                    mask_len = simple_strtol(pch, NULL, 0);

                    if((mask_len < 0) || (mask_len > HW_BREAKPOINT_LEN_8) || ((mask_len != HW_BREAKPOINT_LEN_1) && (mask_len != HW_BREAKPOINT_LEN_2)
                                                                           && (mask_len != HW_BREAKPOINT_LEN_4) && (mask_len != HW_BREAKPOINT_LEN_8)))
                    {
                        mask_len = MSTAR_DEFAULT_MASK_LEN; // use default value
                    }
                    break;
                default:
                    printk(KERN_INFO "unknown command_cnt!!! [%d]\n", command_cnt);
            }
            pch = strsep(&str, " ");
            command_cnt++;
        }

        /* error handle while command count is invalid */
        if(command_cnt <= 2)
        {
            printk(KERN_INFO "invalid command!\n");
            show_usage();
            goto error_exit;
        }

        /* start to register slot */
        register_slot(slot, Addr, mask_len);
    }
    else if(!strncmp(buffer, "filter", 6)) // echo filter pid=$PID pname=$PNAME
    {
        char *filter_pch = NULL;

        command_cnt = 0;
        filter_pch = strsep(&str, " ");
        while(filter_pch != NULL)
        {
            switch (command_cnt)
            {
                case 0:
                    /* do nothing, since cnt=0 is mapping to command "filter" */
                    break;
                case 1:
                    parse_pid_pname(filter_pch);
                    break;
                case 2:
                    parse_pid_pname(filter_pch);
                    break;
                default:
                    printk(KERN_INFO "unknown command_cnt!!! [%d]\n", command_cnt);
            }
            filter_pch = strsep(&str, " ");
            command_cnt++;
        }

        /* error handle while command count is invalid */
        if(command_cnt <= 1)
        {
            printk(KERN_INFO "invalid command!\n");
            show_usage();
            goto error_exit;
        }
    }
    else if(!strncmp(buffer, "disable", 7)) // disable watchpoint/breakpoint/all 0,1,2,3
    {
        char *unregister_pch = NULL;

        command_cnt = 0;
        unregister_pch = strsep(&str, " ");
        while(unregister_pch != NULL)
        {
            switch (command_cnt)
            {
                case 0:
                    //do nothing, since cmd_cnt=0 is mappint to command "disable"
                    break;
                case 1:
                    if(!strncmp(unregister_pch, "watchpoint", 10))
                        is_watchpoint = true;
                    else if(!strncmp(unregister_pch, "breakpoint", 10))
                        is_breakpoint = true;
                    else if(!strncmp(unregister_pch, "all", 3))
                    {
                        is_watchpoint = true;
                        is_breakpoint = true;
                        is_disable_all = true;
                    }
                    else
                    {
                        printk(KERN_INFO "invalid command!\n");
                        show_usage();
                        goto error_exit;
                    }
                    break;
                case 2:
                    slot = simple_strtol(unregister_pch, NULL, 0);

                    if(is_watchpoint && (slot < 0 || slot > (get_total_num_wrps() - 1)))
                    {
                        printk(KERN_INFO "Invalid slot number, only support watchpoint slot 0 ~ %d\n", (get_total_num_wrps() - 1));
                        printk(KERN_INFO "Use default slot number [0]\n");
                        slot=0;
                    }
                    if(is_breakpoint && (slot < 0 || slot > (get_total_num_brps()	 - 1)))
                    {
                        printk(KERN_INFO "Invalid slot number, only support breakpoint slot 0 ~ %d\n", (get_total_num_brps() - 1));
                        printk(KERN_INFO "Use default slot number [0]\n");
                        slot=0;
                    }
                    break;
                default:
                    printk(KERN_INFO "unknown command_cnt!!! [%d]\n", command_cnt);
            }
            unregister_pch = strsep(&str, " ");
            command_cnt++;
        }

        /* error handle while command count is invalid */
        if(command_cnt <= 2 && !is_disable_all)
        {
            printk(KERN_INFO "invalid command!\n");
            show_usage();
            goto error_exit;
        }

        /* handle disable command */
        if(is_disable_all)
        {
            unregister_all_slot();
        }
        else
        {
            unregister_one_slot(slot);
        }
    }
    else if(!strncmp(buffer, "info", 4))
    {
        int watchpoint_slot_num = 0, breakpoint_slot_num = 0;

        watchpoint_slot_num = get_total_num_wrps();
        breakpoint_slot_num = get_total_num_brps();

        /* only allow to show slot status after running "enable" command */
        if (!is_first_register)
        {
            printk(KERN_INFO "HW Watchpoint slot list:\n");
            for(slot=0; slot<watchpoint_slot_num; slot++)
            {
                if(register_handler[slot])
                    printk(KERN_INFO "Watchpoint mstar_hbp[%d] alreay register\n", slot);
                else
                    printk(KERN_INFO "Watchpoint mstar_hbp[%d] not register yet\n", slot);
            }

            printk(KERN_INFO "\nHW Breakpoint slot list:\n");
            for(slot=0; slot<breakpoint_slot_num; slot++)
            {
                if(register_breakpoint_handler[slot])
                    printk(KERN_INFO "Breakpoint mstar_hbp2[%d] alreay register\n", slot);
                else
                    printk(KERN_INFO "Breakpoint mstar_hbp2[%d] not register yet\n", slot);
            }
        }
        else
        {
            printk(KERN_INFO "There is no any installed slot, register_slot_num: (%d)\n", register_slot_num);
            printk(KERN_INFO "Please use [enable] command to install slot\n");
            show_usage();
        }
    }
    else
        printk(KERN_INFO "unknown cmd!!! [%s]\n", buffer);

error_exit:
    kfree(str);

    is_watchpoint = false;
    is_breakpoint = false;
    is_disable_all = false;

    return count;
}

static const struct file_operations mwatchpoint_operations = {
    .open = mhw_watch_open,
    .read = mhw_watch_read,
    .write = mhw_watch_write,
    .release = mhw_watch_release,
};

static int __init mhw_watch_module_init(void)
{
    struct proc_dir_entry *entry;
    int watchpoint_slot_num = 0, breakpoint_slot_num = 0;

    watchpoint_slot_num = get_total_num_wrps();
    breakpoint_slot_num = get_total_num_brps();

    /* create proc fs file node */
    entry = proc_create(mstar_watcpoint_node, S_IRUSR | S_IWUSR, NULL, &mwatchpoint_operations);
    if(!entry)
    {
        printk(KERN_INFO "Error creating proc entry: MStar mstar_watchpoint\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "Create file node: (%s)\n", mstar_watcpoint_node);
    printk(KERN_INFO "Available watchpoint slots: (%d)\n", watchpoint_slot_num);
    printk(KERN_INFO "Available breakpoint slots: (%d)\n", breakpoint_slot_num);

    return 0;
}

static void __exit mhw_watch_module_exit(void)
{
    int watchpoint_slot_num = 0, breakpoint_slot_num = 0;

    watchpoint_slot_num = get_total_num_wrps();
    breakpoint_slot_num = get_total_num_brps();

    if(register_slot_num > 0)
        unregister_all_slot();

    /* remove proc fs file node */
    printk(KERN_INFO "Remove file node: (%s)\n", mstar_watcpoint_node);
    remove_proc_entry(mstar_watcpoint_node, NULL);

    /* only allow to free memory after running "enable" command */
    if (!is_first_register)
    {
        /* free allocated memory before exit module */
        if (mstar_hbp)
            kfree(mstar_hbp);

        if (mstar_hbp2)
            kfree(mstar_hbp2);

        if (register_handler)
            kfree(register_handler);

        if (register_breakpoint_handler)
            kfree(register_breakpoint_handler);
    }
}

module_init(mhw_watch_module_init);
module_exit(mhw_watch_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MStar");
MODULE_DESCRIPTION("mstar hw watchpoint");
