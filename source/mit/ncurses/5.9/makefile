#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = ncurses System V R4 curses emulation library
NAME     = ncurses
VERSION  = 5.9
TYPE     = none

PUBINCFOLDERS = .

ifeq "$(SETVARIANT)" "debug"
    LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib
    PUBLIBS  = $(wildcard $(LIBFOLDER)/*)
endif

# include project targets 
include $(COMPENV)/mk/targets.mk
