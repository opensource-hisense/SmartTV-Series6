dtb-$(CONFIG_ARCH_VEXPRESS) += $(subst ",,$(CONFIG_MSTAR_CHIP_NAME)_ramdisk).dtb
dtb-$(CONFIG_ARCH_VEXPRESS) += $(subst ",,$(CONFIG_MSTAR_CHIP_NAME)_an).dtb

targets += dtbs

DTB_NAMES := $(subst $\",,$(CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE_NAMES))
ifneq ($(DTB_NAMES),)
DTB_LIST := $(addsuffix .dtb,$(DTB_NAMES))
else
DTB_LIST := $(dtb-y)
endif
targets += $(DTB_LIST)

DTC_FLAGS := -i $(srctree)/arch/arm/boot/dts

DTCCPP_FLAGS := -I$(srctree)/arch/arm/boot/dts

dtbs: $(addprefix $(obj)/, $(DTB_LIST))

clean-files := dts/*.dtb *.dtb
