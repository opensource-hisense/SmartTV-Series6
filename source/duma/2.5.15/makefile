#
# Loewe Module Makefile
# 

# include projects defaults
include $(COMPENV)/mk/config.mk

# module configuration
LONGNAME = Detect Unintended Memory Access (DUMA)
NAME     = duma
VERSION  = 2.5.15
TYPE     = lib

DEFINCDIRS = ./duma_2_5_15
DEFSRCDIRS = ./duma_2_5_15
OBJROOT = obj

WARNFLAGS = -Wall -W

PUBINCFOLDERS = .

DUMADIR = duma_2_5_15

CFLAGS= -D_GNU_SOURCE -pthread -I $(COMPROOT)/target/usr/include
CPPVERSION= `$(CXX) --version|head -n 1 | cut -d ' ' -f 3`
CPPFLAGS= -pthread -I $(COMPROOT)/target/usr/include/c++/$(CPPVERSION) -I $(COMPROOT)/target/usr/include/c++/$(CPPVERSION)/sh4-linux/m4-nofpu
LDFLAGS=
MAKEFILE=GNUmakefile 

# own and overridden targets
build: $(DUMADIR)/libduma.a $(DUMADIR)/libduma.so.0.0.0

hinstall:
	mkdir -p $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/include/
	cp -u $(DUMADIR)/*.h $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/include/

install: $(DUMADIR)/libduma.a $(DUMADIR)/libduma.so.0.0.0
	mkdir -p $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/lib/
	cp -u $(DUMADIR)/libduma.a $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/lib/
	cp -u $(DUMADIR)/libduma.so.0.0.0 $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/lib/
	#ln -fs $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/lib/libduma.so.0.0.0 $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/lib/libduma.so.0
	#ln -fs $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/lib/libduma.so.0.0.0 $(COMPENV_INSTALL_DIR)/$(COMPENV_PROJECT_VARIANT)+`basename $(COMPENV)`/loewe/lib/libduma.so

$(DUMADIR)/libduma.a:
	CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" make -C "$(DUMADIR)" -f $(MAKEFILE) libduma.a

$(DUMADIR)/libduma.so.0.0.0:
	CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" make -C "$(DUMADIR)" -f $(MAKEFILE) libduma.so.0.0.0

distclean:
	CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" make -C "$(DUMADIR)" -f $(MAKEFILE) distclean

clean: distclean

debug:
final:

# include project targets
#include $(COMPENV)/mk/targets.mk

