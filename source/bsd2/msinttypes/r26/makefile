#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = inttype headers for MSVC (msinttypes)
NAME     = msinttypes
VERSION  = 0.26
TYPE     = none

LIBFOLDER=

ifeq ($(COMPENV_TARGET_OS),winnt-msvc)
PUBINCFOLDERS = .
else
endif

PUBLIBS  =

# include project targets 
include $(COMPENV)/mk/targets.mk

