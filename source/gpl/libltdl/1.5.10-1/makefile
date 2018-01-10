#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = system independent dlopen wrapper for GNU libtool.
NAME     = libltdl
VERSION  = 1.5.10
TYPE     = none

PUBINCFOLDERS = .

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

PUBLIBS  = $(LIBFOLDER)/libltdl.a
PUBLIBS += $(LIBFOLDER)/libltdl.so
PUBLIBS += $(LIBFOLDER)/libltdl.so.3
PUBLIBS += $(LIBFOLDER)/libltdl.so.3.1.0

# include project targets 
include $(COMPENV)/mk/targets.mk
