#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = htop interactive process viewer
NAME     = htop
VERSION  = 1.0.1
TYPE     = none

ifeq "$(SETVARIANT)" "debug"
    BINFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-bin
    CPFILES = $(BINFOLDER)/htop
    CPFILES_DEST = $(notdir $(DEST))/bin
endif

# include project targets 
include $(COMPENV)/mk/targets.mk
