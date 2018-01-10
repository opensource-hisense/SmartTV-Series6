#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = Tuxera NTFS-3G
NAME     = ntfs-3g
VERSION  = 2012.1.15
TYPE     = none

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib
BINFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-bin

# copy library & headers - only needed for non-static-builds. 
# PUBLIBS  = $(LIBFOLDER)/libntfs-3g.so
# PUBLIBS += $(LIBFOLDER)/libntfs-3g.so.83
# PUBLIBS += $(LIBFOLDER)/libntfs-3g.so.83.0.0
# PUBINCFOLDERS = ntfs-3g

# copy binaries
CPFILES  = $(BINFOLDER)/mkntfs 
CPFILES += $(BINFOLDER)/ntfs-3g
CPFILES += $(BINFOLDER)/ntfsfix
CPFILES_DEST = $(notdir $(DEST))/bin

# include project targets 
include $(COMPENV)/mk/targets.mk
