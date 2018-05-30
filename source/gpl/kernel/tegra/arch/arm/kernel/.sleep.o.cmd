cmd_arch/arm/kernel/sleep.o := arm-none-linux-gnueabi-gcc -Wp,-MD,arch/arm/kernel/.sleep.o.d  -nostdinc -isystem /data/yuchunyu/DBMaster/device/mstar/ToolChain/arm-2014.05/bin/../lib/gcc/arm-none-linux-gnueabi/4.8.3/include -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi -Iinclude/generated/uapi -include /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/include -Idrivers/mstar2 -Iarch/arm/arm-boards/generic/include/ -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu//include -Iarch/arm/arm-boards/plat-mstar//include -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu/ -Iarch/arm/arm-boards/plat-mstar/ -I drivers/mstar  -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float -gdwarf-2         -c -o arch/arm/kernel/sleep.o arch/arm/kernel/sleep.S

source_arch/arm/kernel/sleep.o := arch/arm/kernel/sleep.S

deps_arch/arm/kernel/sleep.o := \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/nr/cpus.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/linkage.h \
  include/linux/threads.h \
    $(wildcard include/config/base/small.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
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
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/glue-cache.h \
    $(wildcard include/config/cpu/cache/v4.h) \
    $(wildcard include/config/cpu/arm920t.h) \
    $(wildcard include/config/cpu/arm922t.h) \
    $(wildcard include/config/cpu/arm925t.h) \
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/cpu/arm926t.h) \
    $(wildcard include/config/cpu/arm940t.h) \
    $(wildcard include/config/cpu/arm946e.h) \
    $(wildcard include/config/cpu/cache/v4wb.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/glue.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/glue-proc.h \
    $(wildcard include/config/cpu/arm7tdmi.h) \
    $(wildcard include/config/cpu/arm720t.h) \
    $(wildcard include/config/cpu/arm740t.h) \
    $(wildcard include/config/cpu/arm9tdmi.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/pj4b.h) \

arch/arm/kernel/sleep.o: $(deps_arch/arm/kernel/sleep.o)

$(deps_arch/arm/kernel/sleep.o):
