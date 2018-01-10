#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = csoap library
NAME     = libcsoap
VERSION  = 1.1.0
TYPE     = none

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-libs
PUBINCFOLDERS = nanohttp libcsoap
DEFINCDIRS += include/nanohttp-1.1 include/libcsoap-1.1
PUBLIBS  = $(LIBFOLDER)/libcsoap*
PUBLIBS += $(LIBFOLDER)/libnanohttp*

# include project targets 
include $(COMPENV)/mk/targets.mk
