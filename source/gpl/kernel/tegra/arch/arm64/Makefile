#
# arch/arm64/Makefile
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies.
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 1995-2001 by Russell King

LDFLAGS_vmlinux	:=-p --no-undefined -X
CPPFLAGS_vmlinux.lds = -DTEXT_OFFSET=$(TEXT_OFFSET)
OBJCOPYFLAGS	:=-O binary -R .note -R .note.gnu.build-id -R .comment -S
GZFLAGS		:=-9

LIBGCC 		:= $(shell $(CC) $(KBUILD_CFLAGS) -print-libgcc-file-name)

KBUILD_DEFCONFIG := defconfig

KBUILD_CFLAGS	+= -mgeneral-regs-only
ifeq ($(CONFIG_CPU_BIG_ENDIAN), y)
KBUILD_CPPFLAGS	+= -mbig-endian
AS		+= -EB
LD		+= -EB
else
machine-$(CONFIG_MSTAR_NAPOLI)      += ../../../../mstar2/hal/napoli/cpu
machine-$(CONFIG_MSTAR_MADISON)     += ../../../../mstar2/hal/madison/cpu
machine-$(CONFIG_MSTAR_CLIPPERS)    += ../../../../mstar2/hal/clippers/cpu
machine-$(CONFIG_MSTAR_MIAMI)       += ../../../../mstar2/hal/miami/cpu
machine-$(CONFIG_MSTAR_MONACO)      += ../../../../mstar2/hal/monaco/cpu
machine-$(CONFIG_MSTAR_KAISER)      += ../../../../mstar2/hal/kaiser/cpu
machine-$(CONFIG_MSTAR_MUJI)        += ../../../../mstar2/hal/muji/cpu/arm64
machine-$(CONFIG_MSTAR_KANO)        += ../../../../mstar2/hal/kano/cpu/arm64
machine-$(CONFIG_MSTAR_K6)        += ../../../../mstar2/hal/k6/cpu/arm64
machine-$(CONFIG_MSTAR_K7U_CA53)        += ../../../../mstar2/hal/k7u_ca53/cpu/arm64
machine-$(CONFIG_MSTAR_MONET)       += ../../../../mstar2/hal/monet/cpu/arm64
machine-$(CONFIG_MSTAR_MANHATTAN)   += ../../../../mstar2/hal/manhattan/cpu/arm64
machine-$(CONFIG_MSTAR_MASERATI)    += ../../../../mstar2/hal/maserati/cpu/arm64
machine-$(CONFIG_MSTAR_CURRY)    += ../../../../mstar2/hal/curry/cpu/arm64
machine-$(CONFIG_MSTAR_CAVALIER)    += ../../../../mstar2/hal/cavalier/cpu/arm64
machine-$(CONFIG_MSTAR_MOONEY)    += ../../../../mstar2/hal/mooney/cpu/arm64

ifeq ($(CONFIG_MP_MSTAR_STR_BASE),y)
mstar_chip = $(subst ",,$(CONFIG_MSTAR_CHIP_NAME))
ifneq ($(wildcard drivers/mstar2/hal/$(mstar_chip)/cpu/arm64/mstar_strmisc_chip.h),)
KBUILD_CPPFLAGS += -DMSTAR_STRMISC_CHIP
endif
endif

KBUILD_CPPFLAGS += -Iarch/arm64/include
KBUILD_CPPFLAGS += -Idrivers/mstar2

# Platform directory name.  This list is sorted alphanumerically
plat-$(CONFIG_PLAT_MSTAR)    += mstar


ifneq ($(CONFIG_MSTAR_CHIP),)
MACHINE  := arch/arm64/arm-boards/$(word 1,$(machine-y))/
machdirs := $(patsubst %,arch/arm64/arm-boards/%/,$(machine-y))
platdirs := $(patsubst %,arch/arm64/arm-boards/plat-%/,$(plat-y))
core-y += arch/arm64/arm-boards/generic/
core-y += $(machdirs)
#core-y += ../mstar2/hal/$(subst ",,$(CONFIG_MSTAR_CHIP_NAME))/cpu/arm64/

ifeq ($(KBUILD_SRC),)
KBUILD_CPPFLAGS += $(patsubst %,-I%/include,$(machdirs) $(platdirs))
KBUILD_CPPFLAGS += $(patsubst %,-I%,$(machdirs) $(platdirs))
else
KBUILD_CPPFLAGS += $(patsubst %,-I$(srctree)/%/include,$(machdirs) $(platdirs))
KBUILD_CPPFLAGS += $(patsubst %,-I$(srctree)/%,$(machdirs) $(platdirs))
endif
endif

ifeq ($(CONFIG_MSTAR_CHIP_NAME), $(filter $(CONFIG_MSTAR_CHIP_NAME), "curry" "kano" "k6"))
KBUILD_CPPFLAGS	+= -mlittle-endian
AS		+= -EL
LD		+= -EL
else
KBUILD_CPPFLAGS	+= -mlittle-endian -Wl,-fix-cortex-a53-843419
AS		+= -EL -fix-cortex-a53-843419
LD		+= -EL -fix-cortex-a53-843419
endif
endif

# For mach-xxx/mach/{io.h|irqs.h}
KBUILD_CPPFLAGS += -Iarch/arm/mach-tegra/include

comma = ,

CHECKFLAGS	+= -D__aarch64__

# Default value
head-y		:= arch/arm64/kernel/head.o

# The byte offset of the kernel image in RAM from the start of RAM.
TEXT_OFFSET := 0x00080000

export	TEXT_OFFSET GZFLAGS

core-y		+= arch/arm64/kernel/ arch/arm64/mm/
drivers-$(CONFIG_OPROFILE)      += arch/arm64/oprofile/

#core-y          += arch/arm64/mach-tegra/

core-$(CONFIG_CRYPTO) += arch/arm64/crypto/
libs-y		:= arch/arm64/lib/ $(libs-y)
libs-y		+= $(LIBGCC)

# Default target when executing plain make
ifeq ($(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE),y)
KBUILD_IMAGE	:= Image.gz-dtb
else
KBUILD_IMAGE	:= Image.gz
endif

KBUILD_DTBS	:= dtbs

all:	$(KBUILD_IMAGE) $(KBUILD_DTBS)

boot := arch/arm64/boot

# FIXME: copied from arch/arm/Makefile
archprepare:
	$(Q)$(MAKE) $(build)=arch/arm/tools include/generated/mach-types.h

Image Image.gz uImage zuImage: vmlinux
#	$(Q)$(MAKE) $(build)=$(boot) $(boot)/$@
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@

zinstall install uinstall: vmlinux
#	$(Q)$(MAKE) $(build)=$(boot) $@
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $@

%.dtb: scripts
	$(Q)$(MAKE) $(build)=$(boot)/dts $(boot)/dts/$@

dtbs: scripts
	$(Q)$(MAKE) $(build)=$(boot)/dts dtbs

Image.gz-dtb: vmlinux scripts dtbs
	$(Q)$(MAKE) $(build)=$(boot) $(boot)/$@

# We use MRPROPER_FILES and CLEAN_FILES now
archclean:
	$(Q)$(MAKE) $(clean)=$(boot)

define archhelp
  echo  '* Image.gz      - Compressed kernel image (arch/$(ARCH)/boot/Image.gz)'
  echo  '  Image         - Uncompressed kernel image (arch/$(ARCH)/boot/Image)'
  echo  '  uImage        - U-Boot wrapped Image'
  echo  '  zuImage       - U-Boot wrapped Image.gz'
  echo  '* dtbs          - Build device tree blobs for enabled boards'
  echo  '  install       - Install uncompressed kernel'
  echo  '  zinstall      - Install compressed kernel'
  echo  '  uinstall      - Install U-Boot wrapped uncompressed kernel'
  echo  '                  Install using (your) ~/bin/installkernel or'
  echo  '                  (distribution) /sbin/installkernel or'
  echo  '                  install to $$(INSTALL_PATH) and run lilo'
endef

