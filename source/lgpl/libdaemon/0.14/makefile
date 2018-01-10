#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = unix deamon tools library
NAME     = libdaemon
VERSION  = 0.14
TYPE     = none

PUBINCFOLDERS = libdaemon

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

PUBLIBS  = $(LIBFOLDER)/libdaemon.a
PUBLIBS += $(LIBFOLDER)/libdaemon.so
PUBLIBS += $(LIBFOLDER)/libdaemon.so.0
PUBLIBS += $(LIBFOLDER)/libdaemon.so.0.5.0

# include project targets 
include $(COMPENV)/mk/targets.mk
