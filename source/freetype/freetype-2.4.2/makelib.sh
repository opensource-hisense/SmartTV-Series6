#!/bin/bash

# add ST toolset to path
if [ $(uname -o) == Cygwin ]; then
_toolset=$(dirname $(dirname $(dirname $(pwd))))/loewe/buildtools/compenv/common/comp/i686-cygwin+st40-3.1.101/bin
export LIBS=-lgloss
else
_toolset=$(dirname $(dirname $(dirname $(pwd))))/loewe/buildtools/compenv/common/comp/i686-linux+stlinux-2.3/bin
fi

export PATH=$PATH:$_toolset

# required for ./configure when checking compiler output file
mv makefile makefile__
cp Makefile.mk makefile
# install to /tmp to avoid any corruption of the environment
if [ $(uname -o) == Cygwin ]; then
./configure -q --host=sh-superh-elf --prefix=/tmp
else
./configure -q --host=sh-linux --prefix=/tmp CC=sh4-linux-gcc
fi

make -f Makefile.mk
# create documentation in docs/reference, requires python to be installed
#make -f Makefile.mk refdoc


mkdir lib 2>/dev/null

if [ $(uname -o) == Cygwin ]; then
cp -f objs/.libs/libfreetype.a lib/
else
cp -f objs/.libs/libfreetype.a lib/libfreetype_stlinux.a
fi

rm makefile
mv makefile__ makefile
