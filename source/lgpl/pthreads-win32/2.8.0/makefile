#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = pthreads-win32 library
NAME     = pthreads-win32
VERSION  = 2.8.0
TYPE     = none

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

PUBINCFOLDERS = .

# Only copy the GCE2 libs for MinGW and the VSE2 for MSVC
PUBLIBS  = $(wildcard $(LIBFOLDER)/*.*)

# include project targets 
include $(COMPENV)/mk/targets.mk

