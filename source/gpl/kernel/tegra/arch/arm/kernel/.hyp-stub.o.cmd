cmd_arch/arm/kernel/hyp-stub.o := arm-none-linux-gnueabi-gcc -Wp,-MD,arch/arm/kernel/.hyp-stub.o.d  -nostdinc -isystem /data/yuchunyu/DBMaster/device/mstar/ToolChain/arm-2014.05/bin/../lib/gcc/arm-none-linux-gnueabi/4.8.3/include -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi -Iinclude/generated/uapi -include /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/include -Idrivers/mstar2 -Iarch/arm/arm-boards/generic/include/ -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu//include -Iarch/arm/arm-boards/plat-mstar//include -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu/ -Iarch/arm/arm-boards/plat-mstar/ -I drivers/mstar  -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float -gdwarf-2         -c -o arch/arm/kernel/hyp-stub.o arch/arm/kernel/hyp-stub.S

source_arch/arm/kernel/hyp-stub.o := arch/arm/kernel/hyp-stub.S

deps_arch/arm/kernel/hyp-stub.o := \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/arm/arch/timer.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/modules.h) \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
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
  include/linux/linkage.h \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/linkage.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/hwcap.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi/asm/hwcap.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/opcodes-virt.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be32.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/virt.h \
    $(wildcard include/config/arm/virt/ext.h) \

arch/arm/kernel/hyp-stub.o: $(deps_arch/arm/kernel/hyp-stub.o)

$(deps_arch/arm/kernel/hyp-stub.o):
