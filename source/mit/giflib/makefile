#
# Loewe Module Makefile
#

# type "make install" to install the precompiled libraries
# 
# to re-compile the original gif library (found in ./current),
# type
#        make build-sh4-libs
# or
#        make build-x86-libs
#
# and the "make install" to install

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = giflib image library
NAME     = libgif
VERSION  = 0.5
TYPE     = none

compile-sh4:
	cd current ; export CC=sh4-linux-gcc ; ./configure --host=sh4
	cd current ; make

compile-i686:
	cd current ; export CC=gcc ; ./configure
	cd current ; make

copy2so-i686:
	cp current/lib/.libs/libgif.so i686-linux-lib/libgif.so

libs2so-sh4:
	mkdir tmp
	cd tmp ; sh4-linux-ar x ../current/lib/.libs/libgif.a
	cd tmp ; sh4-linux-gcc --shared -fpic -o ../sh4-linux-lib/libgif.so *.o
	rm -rf tmp

copy-header:
	cp current/lib/gif_lib.h include

build-sh4-libs:	copy-header compile-sh4 libs2so-sh4

build-x86-libs: copy-header compile-i686 copy2so-i686

PUBINCFOLDERS = .

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

PUBLIBS  = $(LIBFOLDER)/libgif.so

# include project targets 
include $(COMPENV)/mk/targets.mk

