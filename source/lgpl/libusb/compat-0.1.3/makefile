#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = legacy API compatibility layer for libusb >= 1.0
NAME     = libusb-compat
VERSION  = 0.1.3
TYPE     = none

PUBINCFOLDERS = .

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

PUBLIBS  = $(LIBFOLDER)/libusb.so
PUBLIBS += $(LIBFOLDER)/libusb-0.1.so.4
PUBLIBS += $(LIBFOLDER)/libusb-0.1.so.4.4.4

# include project targets 
include $(COMPENV)/mk/targets.mk
