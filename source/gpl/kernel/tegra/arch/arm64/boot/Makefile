#
# arch/arm64/boot/Makefile
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies.
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 2012, ARM Ltd.
# Author: Will Deacon <will.deacon@arm.com>
#
# Based on the ia64 boot/Makefile.
#

include $(srctree)/arch/arm64/boot/dts/Makefile
ifneq ($(MACHINE),)
include $(srctree)/$(MACHINE)/Makefile.boot
endif

ZRELADDR    := $(zreladdr-y)

export ZRELADDR

targets := Image Image.gz uImage

DTB_NAMES := $(subst $\",,$(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE_NAMES))
ifneq ($(DTB_NAMES),)
DTB_LIST := $(addsuffix .dtb,$(DTB_NAMES))
else
DTB_LIST := $(dtb-y)
endif
DTB_OBJS := $(addprefix $(obj)/dts/,$(DTB_LIST))

$(obj)/Image: vmlinux FORCE
	$(call if_changed,objcopy)
	@echo '  Image $@ is ready'

$(obj)/Image.gz: $(obj)/Image FORCE
	$(call if_changed,gzip)
	@echo '  Image $@ is ready'

$(obj)/Image.gz-dtb: $(obj)/Image.gz $(DTB_OBJS) FORCE
	$(call if_changed,cat)


ifneq ($(LOADADDR),)
  UIMAGE_LOADADDR=$(LOADADDR)
else
  ifeq ($(CONFIG_ZBOOT_ROM),y)
    UIMAGE_LOADADDR=$(CONFIG_ZBOOT_ROM_TEXT)
  else
    UIMAGE_LOADADDR=$(ZRELADDR)
  endif
endif

$(obj)/uImage: $(obj)/Image FORCE
	$(call if_changed,uimage)
	@echo '  Image $@ is ready'

quiet_cmd_zuimage = ZUIMAGE $@
      cmd_zuimage = $(CONFIG_SHELL) $(MKIMAGE) -A arm -O linux -T kernel \
	                -C gzip -a $(UIMAGE_LOADADDR) -e $(UIMAGE_LOADADDR) \
					-n 'Linux-$(KERNELRELEASE)' -d $< $@

$(obj)/zuImage: $(obj)/Image.gz FORCE
	$(call if_changed,zuimage)
	@echo '  zuImage $@ is ready'

install: $(obj)/Image
	$(CONFIG_SHELL) $(srctree)/$(src)/install.sh $(KERNELRELEASE) \
	$(obj)/Image System.map "$(INSTALL_PATH)"

zinstall: $(obj)/Image.gz
	$(CONFIG_SHELL) $(srctree)/$(src)/install.sh $(KERNELRELEASE) \
	$(obj)/Image.gz System.map "$(INSTALL_PATH)"

uinstall: $(obj)/uImage
	$(CONFIG_SHELL) $(srctree)/$(src)/install.sh $(KERNELRELEASE) \
	$(obj)/uImage System.map "$(INSTALL_PATH)"
