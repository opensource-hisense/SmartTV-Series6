#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = taglib for audio and video
NAME     = taglib
VERSION  = 1.7.0
TYPE     = none

PUBINCFOLDERS = taglib

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

PUBLIBS  = $(wildcard $(LIBFOLDER)/libtag.so*)

# include project targets 
include $(COMPENV)/mk/targets.mk
