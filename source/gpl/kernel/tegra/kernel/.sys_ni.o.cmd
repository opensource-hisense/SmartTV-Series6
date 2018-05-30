cmd_kernel/sys_ni.o := arm-none-linux-gnueabi-gcc -Wp,-MD,kernel/.sys_ni.o.d  -nostdinc -isystem /data/yuchunyu/DBMaster/device/mstar/ToolChain/arm-2014.05/bin/../lib/gcc/arm-none-linux-gnueabi/4.8.3/include -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi -Iinclude/generated/uapi -include /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/include -Idrivers/mstar2 -Iarch/arm/arm-boards/generic/include/ -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu//include -Iarch/arm/arm-boards/plat-mstar//include -Iarch/arm/arm-boards/../../../../mstar2/hal/macan/cpu/ -Iarch/arm/arm-boards/plat-mstar/ -I drivers/mstar -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -fno-peephole2 -O2 -fconserve-stack -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fstack-protector -fno-conserve-stack -mabi=aapcs-linux -mno-thumb-interwork -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1080 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -Idrivers/mstar/mbx/drv -Idrivers/mstar/include -Idrivers/mstar2/drv/mbx -Idrivers/mstar2/include    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(sys_ni)"  -D"KBUILD_MODNAME=KBUILD_STR(sys_ni)" -c -o kernel/sys_ni.o kernel/sys_ni.c

source_kernel/sys_ni.o := kernel/sys_ni.c

deps_kernel/sys_ni.o := \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/kasan/switch/on.h) \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/linkage.h \
  include/linux/errno.h \
  include/uapi/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi/asm-generic/errno.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/include/uapi/asm-generic/errno-base.h \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/aeabi.h) \
    $(wildcard include/config/oabi/compat.h) \
  /data/yuchunyu/DBMaster/device/mstar/tegra/kernel/tegra/arch/arm/include/uapi/asm/unistd.h \

kernel/sys_ni.o: $(deps_kernel/sys_ni.o)

$(deps_kernel/sys_ni.o):
