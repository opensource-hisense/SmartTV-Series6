include $(SWCFGPATH_DAILEO)/config.mk
include $(SWCFGPATH_DAILEO)/default_config.mk
include $(SWCFGPATH_DAILEO)/tool_config.mk
# =====================================
# file name define
# =====================================
MODULE_NAME=mali

# temp dir to untar file

# **********************************************
# Release shared libs path
# **********************************************
DYNAMIC_LIBPATH = $(TARGET_DIRPATH)/$(PROJ_MODE).$(CHIP)/mslib


ifeq ($(PURESW), 1)
LIBDIR = sim
else
ifeq ($(TOOLCHAIN), )
	$(error ERROR USAGE - Please select the correct target cpu for TOOLCHAIN)
endif

ifeq ($(FPU_ENABLE), 1)
FLOATING_TYPE=hard_float
else
FLOATING_TYPE=soft_float
endif

ifeq ($(UMP_ENABLE),1)
LIBDIR = $(TOOLCHAIN)/$(get-gcc-version)/$(CHIP)/$(FLOATING_TYPE)/dynamic/mali_ump
else
LIBDIR = $(TOOLCHAIN)/$(get-gcc-version)/$(CHIP)/$(FLOATING_TYPE)/dynamic
endif
endif
# =====================================
# Rules
# =====================================
.PHONY: all release

all: release

release:
#copy libs
ifeq ($(MALI_ENABLE),1)
ifeq ($(UMP_ENABLE),1)
	@echo "Release $(MODULE_NAME) with UMP from $(LIBDIR) ....."
	@cp -f $(LIBDIR)/libUMP.so $(DYNAMIC_LIBPATH)
else
	@echo "Release $(MODULE_NAME) from $(LIBDIR) ....."
endif
ifeq ($(filter munich muji manhattan macan mustang, $(CHIP)),)
	@cp -f $(LIBDIR)/libEGL.so $(DYNAMIC_LIBPATH)
	@cp -f $(LIBDIR)/libGLESv1_CM.so $(DYNAMIC_LIBPATH)
	@cp -f $(LIBDIR)/libGLESv2.so $(DYNAMIC_LIBPATH)
endif
ifeq ($(CHIP),monaco)
	@cp -f $(LIBDIR)/libmali.so $(DYNAMIC_LIBPATH)
	@if [ -f $(DYNAMIC_LIBPATH)/libMali.so ]; then rm $(DYNAMIC_LIBPATH)/libMali.so ;fi
	@ln -s libmali.so $(DYNAMIC_LIBPATH)/libMali.so
else
	@cp -f $(LIBDIR)/libMali.so $(DYNAMIC_LIBPATH)
ifneq ($(filter munich muji manhattan macan mustang, $(CHIP)),)
	@ln -sf libMali.so $(DYNAMIC_LIBPATH)/libEGL.so
	@ln -sf libMali.so $(DYNAMIC_LIBPATH)/libGLESv1_CM.so
	@ln -sf libMali.so $(DYNAMIC_LIBPATH)/libGLESv2.so
endif
endif
	@if [ -f $(LIBDIR)/libOpenVG.so ]; then cp -f $(LIBDIR)/libOpenVG.so $(DYNAMIC_LIBPATH) ;fi
	@if [ -f $(LIBDIR)/libOpenVGU.so ]; then cp -f $(LIBDIR)/libOpenVGU.so $(DYNAMIC_LIBPATH) ;fi
#copy header file
	@[ -d $(INCLUDE_PATH)/$(MODULE_NAME) ] || mkdir -p $(INCLUDE_PATH)/$(MODULE_NAME)
	@cp -ruf include/* $(INCLUDE_PATH)/$(MODULE_NAME)
endif

clean:
	@echo "clean up $(MODULE_NAME) headers"
	@rm -rf $(INCLUDE_PATH)/$(MODULE_NAME)
	@echo "clean up $(MODULE_NAME) library"
	@if [ -f $(DYNAMIC_LIBPATH)/libUMP.so ]; then rm -f $(DYNAMIC_LIBPATH)/libUMP.so ;fi
	@if [ -f $(DYNAMIC_LIBPATH)/libEGL.so ]; then rm -f $(DYNAMIC_LIBPATH)/libEGL.so ;fi
	@if [ -f $(DYNAMIC_LIBPATH)/libGLESv1_CM.so ]; then rm -f $(DYNAMIC_LIBPATH)/libGLESv1_CM.so ;fi
	@if [ -f $(DYNAMIC_LIBPATH)/libGLESv2.so ]; then rm -f $(DYNAMIC_LIBPATH)/libGLESv2.so ;fi
ifeq ($(CHIP),monaco)
	@if [ -f $(DYNAMIC_LIBPATH)/libmali.so ]; then rm -f $(DYNAMIC_LIBPATH)/libMali.so ;fi
else
	@if [ -f $(DYNAMIC_LIBPATH)/libMali.so ]; then rm -f $(DYNAMIC_LIBPATH)/libMali.so ;fi
endif
	@if [ -f $(DYNAMIC_LIBPATH)/libOpenVG.so ]; then rm -f $(DYNAMIC_LIBPATH)/libOpenVG.so ;fi
	@if [ -f $(DYNAMIC_LIBPATH)/libOpenVGU.so ]; then rm -f $(DYNAMIC_LIBPATH)/libOpenVGU.so ;fi
