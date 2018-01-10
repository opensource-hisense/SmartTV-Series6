#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = FreeType2
NAME     = freetype
VERSION  = 2.4.2
TYPE     = none

#INCDIRS += ../include/freetype
PUBINCS= include/ft2build.h
PUBINCFOLDERS = freetype freetype/config
ifeq "$(COMPENV_TARGET_OS)" "linux"
PUBLIBS += lib/libfreetype_stlinux.a
else
PUBLIBS += lib/libfreetype.a
endif

# include project targets 
include $(COMPENV)/mk/targets.mk

#OBJ_DIR=$(OBJDIR)
#include Makefile.mk
