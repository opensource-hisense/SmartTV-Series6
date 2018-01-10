#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = Photo camera access library
NAME     = libgphoto2
VERSION  = 2.4.14
TYPE     = none

PUBINCFOLDERS = gphoto2

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

PUBLIBS  = $(LIBFOLDER)/libgphoto2.so
PUBLIBS += $(LIBFOLDER)/libgphoto2.so.2
PUBLIBS += $(LIBFOLDER)/libgphoto2.so.2.4.0
PUBLIBS += $(LIBFOLDER)/libgphoto2_port.so
PUBLIBS += $(LIBFOLDER)/libgphoto2_port.so.0
PUBLIBS += $(LIBFOLDER)/libgphoto2_port.so.0.8.0

# copy library sub-folders recursively
CPDIRS=$(LIBFOLDER)/libgphoto2 $(LIBFOLDER)/libgphoto2_port
CPDIRS_DEST=$(notdir $(DEST))/lib

# include project targets 
include $(COMPENV)/mk/targets.mk
