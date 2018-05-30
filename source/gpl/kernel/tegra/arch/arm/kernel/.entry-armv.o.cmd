cmd_arch/arm/kernel/entry-armv.o := arm-none-linux-gnueabi-gcc -Wp,-MD,arch/arm/kernel/.entry-armv.o.d  -nostdinc -isystem /data/yuchunyu/DBMaster/device/mstar/ToolChain/arm-2014.05/bin/../lib/gcc/arm-none-linux-gnueabi/4.8.3/include -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi -Iinclude/generated/uapi -include /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/include -Idrivers/mstar2 -Iarch/arm/arm-boards/generic/include/ -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu//include -Iarch/arm/arm-boards/plat-mstar//include -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu/ -Iarch/arm/arm-boards/plat-mstar/ -I drivers/mstar  -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float -gdwarf-2         -c -o arch/arm/kernel/entry-armv.o arch/arm/kernel/entry-armv.S

source_arch/arm/kernel/entry-armv.o := arch/arm/kernel/entry-armv.S

deps_arch/arm/kernel/entry-armv.o := \
    $(wildcard include/config/multi/irq/handler.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/aeabi.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/needs/syscall/for/cmpxchg.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
    $(wildcard include/config/cpu/v7.h) \
    $(wildcard include/config/neon.h) \
    $(wildcard include/config/iwmmxt.h) \
    $(wildcard include/config/crunch.h) \
    $(wildcard include/config/vfp.h) \
    $(wildcard include/config/cpu/use/domains.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/kuser/helpers.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/ptrace.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi/asm/ptrace.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/hwcap.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi/asm/hwcap.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/opcodes-virt.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be32.h) \
  include/linux/stringify.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/task/size.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
    $(wildcard include/config/virt/to/bus.h) \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi/linux/const.h \
  include/linux/types.h \
    $(wildcard include/config/mp/debug/tool/changelist.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  arch/arm/include/generated/asm/types.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  include/linux/sizes.h \
  arch/arm/arm-boards/../../../../mstar2/hal/macan/cpu//include/mach/memory.h \
    $(wildcard include/config/memory/start/address.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/cma.h) \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/glue-df.h \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/abrt/ev4.h) \
    $(wildcard include/config/cpu/abrt/lv4t.h) \
    $(wildcard include/config/cpu/abrt/ev4t.h) \
    $(wildcard include/config/cpu/abrt/ev5t.h) \
    $(wildcard include/config/cpu/abrt/ev5tj.h) \
    $(wildcard include/config/cpu/abrt/ev6.h) \
    $(wildcard include/config/cpu/abrt/ev7.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/glue.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/glue-pf.h \
    $(wildcard include/config/cpu/pabrt/legacy.h) \
    $(wildcard include/config/cpu/pabrt/v6.h) \
    $(wildcard include/config/cpu/pabrt/v7.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/vfpmacros.h \
    $(wildcard include/config/vfpv3.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/vfp.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/thread_notify.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/unwind.h \
    $(wildcard include/config/arm/unwind.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi/asm/unistd.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/tls.h \
    $(wildcard include/config/tls/reg/emul.h) \
    $(wildcard include/config/cpu/v6.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/system_info.h \
  arch/arm/kernel/entry-header.S \
    $(wildcard include/config/frame/pointer.h) \
    $(wildcard include/config/alignment/trap.h) \
    $(wildcard include/config/context/tracking.h) \
  include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/modules.h) \
  include/linux/linkage.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/linkage.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  arch/arm/include/generated/asm/errno.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi/asm-generic/errno.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi/asm-generic/errno-base.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/fpstate.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/entry-macro-multi.S \

arch/arm/kernel/entry-armv.o: $(deps_arch/arm/kernel/entry-armv.o)

$(deps_arch/arm/kernel/entry-armv.o):
