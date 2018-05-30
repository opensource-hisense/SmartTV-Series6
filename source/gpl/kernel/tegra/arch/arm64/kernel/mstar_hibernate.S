#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/memory.h>
#include <linux/init.h>
#include <asm/ptrace.h>
#include <asm/asm-offsets.h>
#include <asm/cputype.h>
#include <asm/thread_info.h>
#include <asm/pgtable-hwdef.h>
#include <asm/pgtable.h>
#include <asm/page.h>
#include <asm/virt.h>
#include <mach/pm.h>


SAVE_IMP_DEFINE0 = 0
SAVE_IMP_DEFINE1 = 0

.text
.align 4
bmstar_fast_boot: .quad 0
fastboot_savedlr: .quad 0
fastboot_savedlr_stk: .quad 0

fastboot_save_mmu_ctr:  .quad 0
fastboot_save_mmu_ttb:  .quad 0
fastboot_save_mmu_dmn:  .quad 0
//@ c1
fastboot_save_mmu_ACTLR: .quad 0
fastboot_save_mmu_CPACR: .quad 0
//@ c2
fastboot_save_mmu_TTBR1: .quad 0
fastboot_save_mmu_TTBCR: .quad 0
//@ c10
fastboot_save_mmu_PRRR:  .quad 0
fastboot_save_mmu_NMRR:  .quad 0
//@ c13
fastboot_save_mmu_FCSEIDR:  .quad 0
fastboot_save_mmu_CTXIDR:   .quad 0
fastboot_save_mmu_TPIDRURW: .quad 0
fastboot_save_mmu_TPIDRURO: .quad 0
fastboot_save_mmu_TPIDRPRW: .quad 0

fastboot_save_mmu_VBAR:     .quad 0

.if (SAVE_IMP_DEFINE0==1)
fastboot_save_imp_define0:   .quad 0
.endif

.if (SAVE_IMP_DEFINE1==1)
fastboot_save_imp_define1:   .quad 0
.endif

//@
fastboot_save_asimde_FPSCR:  .quad 0
fastboot_save_asimde_FPEXEC: .quad 0

.align 3
fastboot_saved_magic: .quad 0
fastboot_save: .fill 10, 8, 0
fastboot_save_spt: .quad 0
fastboot_save_ret_addr: .quad 0
fastboot_save_wakup_vir: .quad 0
fastboot_save_wakup_phy: .quad 0
fastboot_save_regs: .fill 14, 8, 0
fastboot_save2: .quad 0
fastboot_save_wakup_save: .quad 0
fastboot_save_L2CTLR_EL1: .quad 0
fastboot_save_L2ECTLR_EL1: .quad 0
fastboot_save_L2ACTLR_EL1: .quad 0
fastboot_save_PAR_EL1: .quad 0
fastboot_save_CPUACTLR_EL1: .quad 0
fastboot_save_CPUECTLR_EL1: .quad 0
fastboot_save_CPUMERRSR_EL1: .quad 0
fastboot_save_TPIDR_EL1: .quad 0
fastboot_save_CNTP_CVAL_EL0: .quad 0
fastboot_save_CNTP_TVAL_EL0: .quad 0
fastboot_save_CNTV_CVAL_EL0: .quad 0
fastboot_save_CNTV_TVAL_EL0: .quad 0
fastboot_save_CNTP_CTL_EL0: .quad 0
fastboot_save_CNTV_CTL_EL0: .quad 0
fastboot_save_CNTKCTL_EL1: .quad 0

.macro MVEX1,a1, a2, a3,tmp
    LDR \tmp,[\a2]
    STR \tmp,[\a1],#8
    LDR \tmp,[\a3],#8
    STR \tmp,[\a2],#8
.endm
.macro MVEX,a1, a2, tmp
    LDR \tmp,[\a2],#8
    STR \tmp,[\a1],#8
.endm




ENTRY(is_mstar_fastboot)
    adr x0, bmstar_fast_boot
    ldr x0, [x0]
	ret
#if 0
    adr r0, bmstar_fast_boot
    ldr r0, [r0]
    mov pc, lr
#endif

ENTRY(set_mstar_fastboot)
	adr x0, bmstar_fast_boot
	ldr x1, [x0]
	add x1, x1, #1
	str x1, [x0]
	ret
#if 0
    adr r0, bmstar_fast_boot
    ldr r1, [r0]
    add r1, r1, #1
    str r1, [r0]
    mov pc, lr
#endif


ENTRY(unset_mstar_fastboot)
	adr x0, bmstar_fast_boot
	ldr x1, [x0]
	sub x1, x1, #1
	str x1, [x0]
	ret
#if 0
    adr r0, bmstar_fast_boot
    ldr r1, [r0]
    sub r1, r1, #1
    str r1, [r0]
    mov pc, lr
#endif

ENTRY(fastboot_put_char)
#ifdef CONFIG_EARLY_PRINTK
    b   prom_putchar
#else
	ret
#endif
#if 0
#ifdef CONFIG_EARLY_PRINTK
    b   prom_putchar
#else
    mov pc, lr
#endif
#endif

ENTRY(mstar_fastboot_save_last)
    STP X29, X30, [SP,#-32]!
    MOV X29, SP
    STP X27, X28, [X29,#16]
    ADR X4, fastboot_save_L2CTLR_EL1
    MRS X5, S3_1_C11_C0_2
    STR X5, [X4],#8
    MRS X5, S3_1_C11_C0_3
    STR X5, [X4],#8
    MRS X5, S3_1_C15_C0_0
    STR X5, [X4],#8
    MRS X5, PAR_EL1
    STR X5, [X4],#8
    MRS X5, S3_1_C15_C2_0
    STR X5, [X4],#8
    MRS X5, S3_1_C15_C2_1
    STR X5, [X4],#8
    MRS X5, S3_1_c15_c2_2
    STR X5, [X4],#8
    MRS X5, TPIDR_EL1
    STR X5, [X4],#8
    MRS X5, CNTP_CVAL_EL0
    STR X5, [X4],#8
    MRS X5, CNTP_TVAL_EL0
    STR X5, [X4],#8
    MRS X5, CNTV_CVAL_EL0
    STR X5, [X4],#8
    MRS X5, CNTV_TVAL_EL0
    STR X5, [X4],#8
    MRS X5, CNTP_CTL_EL0
    STR X5, [X4],#8
    MRS X5, CNTV_CTL_EL0
    STR X5, [X4],#8
    MRS X5, CNTKCTL_EL1
    STR X5, [X4],#8
    ADR X4, wakup
    ADR X5, fastboot_saved_magic
    LDR X6, [X4],#8
    MOV X0, X6
    LDR X27, =MSTAR_SLEEP_MAGIC
    STR X27, [X5],#8
    MVEX1 X5, X6, X4, X7
    MVEX1 X5, X6, X4, X7
    MVEX1 X5, X6, X4, X7
    LDR X28, =WAKEUP_SAVE_ADDR
    MOV X1, X28
    ADR X2, fastboot_save2
    MVEX X2, X1, X7
    ADR X0, mstar_fastboot_restore_first
    BL  mstar_virt_to_phy
    STP W27, W0, [X28]
    MOV X0, X28
    BL  mstar_virt_to_phy
    ADR X1, fastboot_save_wakup_save
    STR X0, [X1]
    LSR X0, X0, #20
    LSL X0, X0, #4
    ORR X0, X0, #WAKEUP_FLAG_SLEPT
    BL  mstar_pm_regw
    LDP X27, X28, [X29, #16]
    LDP X29, X30, [SP],#32
    RET
.align 3
       .quad .
wakup: .quad _text
wakup_vect:
    ADR X5, wakup2
    LDR X4, [X5]
    BR   X4
    BL   mstar_fastboot_restore_first
wakup2: .quad ((PHYS_OFFSET-PAGE_OFFSET)-4+.)
ENTRY(fastboot_set_wakeup_addr_phy)
    ADR X5, fastboot_save_wakup_vir
    STP X1, X0, [X5]
    RET
ENTRY(fastboot_suspend_ret)
    ADR X5, fastboot_save_spt
    LDP X29, X30, [X5],#16
    ADR X5, fastboot_save_regs
    LDP X16,X17, [X5],#16
    LDP X18,X19, [X5],#16
    LDP X20,X21, [X5],#16
    LDP X22,X23, [X5],#16
    LDP X24,X25, [X5],#16
    LDP X26,X27, [X5],#16
    LDP X28,X8, [X5],#16
    RET
ENTRY(fastboot_save_cpu_registers)
    ADR X5, fastboot_save_spt
    STP X29, X30, [X5]
    ADR X5, fastboot_save_regs
    STP X16,X17, [X5],#16
    STP X18,X19, [X5],#16
    STP X20,X21, [X5],#16
    STP X22,X23, [X5],#16
    STP X24,X25, [X5],#16
    STP X26,X27, [X5],#16
    STP X28,X8, [X5],#16
    STP X29, X30, [SP,#-16]!
    MOV X29, SP
    MOV X0, XZR
    ADR X1, fastboot_suspend_ret
    BL  cpu_suspend
    LDP X29, X30, [SP],#16
    ADR X5, fastboot_save_ret_addr
    LDP X5, X30, [X5]
    RET
#if 0
    stmfd   sp!,{r0-r7,lr}
    adrl    r2, fastboot_save_mmu_ctr
    mrc     p15, 0, r3, c1, c0, 0   /* MMU Control */
    str     r3, [r2], #4
    mrc     p15, 0, r3, c2, c0, 0   /* TTB address. */
    str     r3, [r2], #4
    mrc     p15, 0, r3, c3, c0, 0   /* domain access control. */
    str     r3, [r2], #4
    mrc     p15,0,r3,c1,c0,1        /* ACTLR*/
    str     r3, [r2], #4
    mrc     p15,0,r3,c1,c0,2        /* CPACR*/
    str     r3, [r2], #4
    mrc     p15, 0, r3, c2, c0, 1   /* TTBR 1 */
    str     r3, [r2], #4
    mrc     p15, 0, r3, c2, c0, 2   /* TTBCR */
    str     r3, [r2], #4
    mrc     p15, 0, r3, c10, c2, 0   /* PRRR */
    str     r3, [r2], #4
    mrc     p15, 0, r3, c10, c2, 1   /* NMRR */
    str     r3, [r2], #4
    mrc     p15,0,r3,c13,c0,0        /* FCSEIDR */
    str     r3, [r2], #4
    mrc     p15,0,r3,c13,c0,1        /* CTXIDR */
    str     r3, [r2], #4
    mrc     p15,0,r3,c13,c0,2        /* TPIDRURW */
    str     r3, [r2], #4
    mrc     p15,0,r3,c13,c0,3        /* TPIDRURO */
    str     r3, [r2], #4
    mrc     p15,0,r3,c13,c0,4        /* TPIDRPRW */
    str     r3, [r2], #4
    mrc	    p15,0,r3,c12,c0,0	     /* VBAR */
    str     r3, [r2], #4
.if (SAVE_IMP_DEFINE0==1)
    mrc     p15, 1, r3, c9, c0, 2   /* imp defined */
    str     r3, [r2], #4
.endif
.if (SAVE_IMP_DEFINE1==1)
    mrc     p15, 0, r3, c15, c0, 1
    str     r3, [r2], #4
.endif

    /* neon */
    adrl    r2, fastboot_save_asimde_FPSCR
    mrc   p15,0,r7,c1,c0,2
    orr   r3, r7, #0x00F00000
    bic   r3, r3, #0xC0000000
    mcr   p15,0,r3,c1,c0,2
    VFPFMRX  r6, FPEXC
    orr   r3, r6, #0x40000000
    VFPFMXR  FPEXC, r3
    VFPFMRX  r3, FPSCR
    str   r3, [r2], #4
    str   r6, [r2], #4
    VFPFMXR  FPEXC, r6
    mcr   p15,0,r7,c1,c0,2
    /* end neon*/

    ldmfd   sp!,{r0-r7,pc}
#endif


ENTRY(mstar_fastboot_restore_first)
    MOV X19, X0
    MOV X20, X1
    MOV X21, X5
    BL  __flush_dcache_all
    IC IALLU
    TLBI VMALLE1IS
    DSB SY
    ISB
    SUB X5, X21, #16
    ADR X6, fastboot_saved_magic
    STR XZR, [X6],#8
    MVEX X5,X6,X7
    MVEX X5,X6,X7
    MVEX X5,X6,X7
    ADR X2, fastboot_save2
    LDP X0, X1, [X2]
    STR X0, [X1]
    ADR X4, fastboot_save_L2CTLR_EL1
    LDR X5, [X4],#8
    MSR S3_1_C11_C0_2, X5
    LDR X5, [X4],#8
    MSR S3_1_C11_C0_3, X5
    LDR X5, [X4],#8
    MSR S3_1_C15_C0_0, X5
    LDR X5, [X4],#8
    MSR PAR_EL1, X5
    LDR X5, [X4],#8
    MSR S3_1_C15_C2_0, X5
    LDR X5, [X4],#8
    MSR S3_1_C15_C2_1, X5
    LDR X5, [X4],#8
    MSR S3_1_c15_c2_2, X5
    LDR X5, [X4],#8
    MSR TPIDR_EL1, X5
    LDR X5, [X4],#8
    MSR CNTP_CVAL_EL0, X5
    LDR X5, [X4],#8
    MSR CNTP_TVAL_EL0, X5
    LDR X5, [X4],#8
    MSR CNTV_CVAL_EL0, X5
    LDR X5, [X4],#8
    MSR CNTV_TVAL_EL0, X5
    LDR X5, [X4],#8
    MSR CNTP_CTL_EL0, X5
    LDR X5, [X4],#8
    MSR CNTV_CTL_EL0, X5
    LDR X5, [X4],#8
    MSR CNTKCTL_EL1, X5
    B   cpu_resume
#if 0
    bl ensure_environment
    mov r0, #'K'
    bl PUTCHAR
    adrl    r2, fastboot_save_mmu_ctr
    ldmia   r2!, {r0,r3,r4}    /* r0: mmu ctrl */
    ldr     r1, =fastboot_restore1_ret
	mcr	    p15, 0, r4, c3, c0, 0		@ load domain access register
	mcr	    p15, 0, r3, c2, c0, 0		@ load page table pointer
    ldr     r3, [r2], #4
	mcr     p15,0,r3,c1,c0,1        /* ACTLR*/
    ldr     r3, [r2], #4
    mcr     p15,0,r3,c1,c0,2        /* CPACR*/
    ldr     r3, [r2], #4
    mcr     p15, 0, r3, c2, c0, 1   /* TTBR 1 */
    ldr     r3, [r2], #4
    mcr     p15, 0, r3, c2, c0, 2   /* TTBCR */
    ldr     r3, [r2], #4
    mcr     p15, 0, r3, c10, c2, 0   /* PRRR */
    ldr     r3, [r2], #4
    mcr     p15, 0, r3, c10, c2, 1   /* NMRR */
    ldr     r3, [r2], #4
    mcr     p15,0,r3,c13,c0,0        /* FCSEIDR */
    ldr     r3, [r2], #4
    mcr     p15,0,r3,c13,c0,1        /* CTXIDR */
    ldr     r3, [r2], #4
    mcr     p15,0,r3,c13,c0,2        /* TPIDRURW */
    ldr     r3, [r2], #4
    mcr     p15,0,r3,c13,c0,3        /* TPIDRURO */
    ldr     r3, [r2], #4
    mcr     p15,0,r3,c13,c0,4        /* TPIDRPRW */
    ldr     r3, [r2], #4
    mcr	    p15,0,r3,c12,c0,0	     /* VBAR */
.if (SAVE_IMP_DEFINE0)
    ldr     r3, [r2], #4
    mcr     p15, 1, r3, c9, c0, 2   /* imp defined */
.endif
.if (SAVE_IMP_DEFINE1)
    ldr     r3, [r2], #4
    mcr     p15, 0, r3, c15, c0, 1
.endif

    /* neon */
    adrl    r2, fastboot_save_asimde_FPSCR
    mrc   p15,0,r7,c1,c0,2
    orr   r3, r7, #0x00F00000
    bic   r3, r3, #0xC0000000
    mcr   p15,0,r3,c1,c0,2
    VFPFMRX  r6, FPEXC
    orr   r3, r6, #0x40000000
    VFPFMXR  FPEXC, r3
    ldr   r3, [r2], #4
    VFPFMXR  FPSCR, r3
    ldr   r6, [r2], #4
    VFPFMXR  FPEXC, r6
    mcr   p15,0,r7,c1,c0,2
    /* end neon*/

	b	MMU_ctrl
#endif

ENTRY(swsusp_arch_suspend)
	adr x0, fastboot_savedlr
	str x30, [x0]
	adr x0, fastboot_savedlr_stk
	str x29, [x0]
	bl  mstar_fastboot_save
	bl  mstar_fastboot_save_last
	bl   swsusp_save
	adr x1, fastboot_savedlr
	ldr x30, [x1]
	adr x1, fastboot_savedlr_stk
	ldr x29, [x1]
	mov sp, x29 
	ret

#if 0
    adr r0, fastboot_savedlr
    str lr, [r0]
    bl  mstar_fastboot_save
    bl  mstar_fastboot_save_last
    adr r0, fastboot_savedlr
    ldr lr, [r0]
    b   swsusp_save
#endif


ENTRY(swsusp_arch_resume)
	bl  mstar_fastboot_restore_first
//fastboot_restore1_ret:
ENTRY(fastboot_restore1_ret)
    bl  mstar_fastboot_restore
    bl  fastboot_reset_onresume
	adr x1, fastboot_savedlr
	ldr x30, [x1]
	adr x1, fastboot_savedlr_stk
	ldr x29, [x1]
	mov sp, x29 
    eor x0, x0, x0
	ret
#if 0
    bl  mstar_fastboot_restore_first
fastboot_restore1_ret:
    mov r0, #'L'
    bl  PUTCHAR_VIRT
    bl  mstar_fastboot_restore
    bl  fastboot_reset_onresume
    adr r0, fastboot_savedlr
    ldr lr, [r0]
    eor r0, r0, r0
    mov pc, lr
#endif

ENTRY(save_processor_state)
	eor x0, x0, x0
	ret
#if 0
    eor r0, r0, r0
    mov pc, lr
#endif

ENTRY(restore_processor_state)
	eor x0, x0, x0
	ret
#if 0
    eor r0, r0, r0
    mov pc, lr
#endif

ENTRY(pfn_is_nosave)
	eor x0, x0, x0
	ret
#if 0
    eor r0, r0, r0
    mov pc, lr
#endif
