#
# Makefile for MStar TUNER device drivers.
#

ifeq ($(MAKE_TYPE), MODULE_STANDALONE)
include $(TOP_DIR)/modules.mk
endif

CONFIG_MSTAR_CHIP_NAME := $(subst ",,$(CONFIG_MSTAR_CHIP_NAME))

# general options
EXTRA_CFLAGS      +=  -Idrivers/mstar2/include
EXTRA_CFLAGS      +=  -Idrivers/mstar2/tuner
EXTRA_CFLAGS      +=  -Idrivers/mstar3party/tuner

# specific options
EXTRA_CFLAGS      +=  -DTITANIA
EXTRA_CFLAGS      +=  -DMSOS_TYPE_LINUX

# files Tuner Types

ifeq ($(CONFIG_MSTAR_TUNER_00), y)
obj-$(CONFIG_MSTAR_TUNER)	+= tuner_00/mdrv-tuner-00.o
tuner_00/mdrv-tuner-00-objs				+= tuner_00/mdrv_tuner_00.o mdrv_tuner_io.o
endif

ifeq ($(CONFIG_MSTAR_TUNER_01), y)
obj-$(CONFIG_MSTAR_TUNER)	+= tuner_01/mdrv-tuner-01.o
tuner_01/mdrv-tuner-01-objs				+= tuner_01/mdrv_tuner_01.o mdrv_tuner_io.o
endif

ifeq ($(CONFIG_MSTAR_TUNER_Si2151), y)
obj-$(CONFIG_MSTAR_TUNER)	+= tuner_Si2151/mdrv-tuner-Si2151.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/mdrv_tuner_Si2151.o mdrv_tuner_io.o
# tuner code 
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/si2151_i2c_api.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Si2151_L1_API.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Si2151_L1_Commands.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Si2151_L1_Properties.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Si2151_L2_API.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Si2151_L3_Test.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Si2151_Properties_strings.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Si2151_User_Properties.o
tuner_Si2151/mdrv-tuner-Si2151-objs				+= tuner_Si2151/Si2151/Silabs_L0_Connection.o
endif

ifeq ($(CONFIG_MSTAR_TUNER_MXL661), y)
obj-$(CONFIG_MSTAR_TUNER)	+= tuner_MXL661/mdrv-tuner-MXL661.o
tuner_MXL661/mdrv-tuner-MXL661-objs				+= tuner_MXL661/mdrv_tuner_MXL661.o mdrv_tuner_io.o
# tuner code 
tuner_MXL661/mdrv-tuner-MXL661-objs				+= tuner_MXL661/MxL661/MxL661_Main.o
tuner_MXL661/mdrv-tuner-MXL661-objs				+= tuner_MXL661/MxL661/MxL661_OEM_Drv.o
tuner_MXL661/mdrv-tuner-MXL661-objs				+= tuner_MXL661/MxL661/MxL661_TunerApi.o
tuner_MXL661/mdrv-tuner-MXL661-objs				+= tuner_MXL661/MxL661/MxL661_TunerCfg.o
tuner_MXL661/mdrv-tuner-MXL661-objs				+= tuner_MXL661/MxL661/MxL661_TunerSpurTable.o
endif


ifeq ($(CONFIG_MSTAR_TUNER_AV2012), y)
obj-$(CONFIG_MSTAR_TUNER)	+= tuner_AV2012/mdrv-tuner-AV2012.o
tuner_AV2012/mdrv-tuner-AV2012-objs				+= tuner_AV2012/mdrv_tuner_AV2012.o mdrv_tuner_io.o
endif
#export header files
