#!/bin/sh
TARGETOS=`basename "$COMPENV"`
TARGET=""
CPPVERSION="`ls /usr/include/c++|tail -n1`"

INSTALLDIR="$COMPENV_INSTALL_DIR/$COMPENV_PROJECT_VARIANT+$TARGETOS/target"
CFLAGS="-I $TARGET/usr/include/c++/$CPPVERSION/sh4-linux/ -I $TARGET/usr/include/c++/$CPPVERSION/ -I $CODEBASE_DIR/oss/gpl/$TARGETOS/target/usr/include/libxml2"
CXXFLAGS=$CFLAGS
LDFLAGS="-Wl,-L$TARGET/lib -Wl,-L$TARGET/usr/lib -Wl,-L$CODEBASE_DIR/oss/gpl/$TARGETOS/target/lib -Wl,-L$CODEBASE_DIR/oss/gpl/$TARGETOS/target/usr/lib -Wl,-L$CODEBASE_DIR/oss/gpl/$TARGETOS/target/usr/lib"

export CFLAGS
export CXXFLAGS
export LDFLAGS

../../libcsoap-1.1.0/configure --enable-shared=NO --prefix="$PWD/../usr" \
			       --includedir=$PWD/../../include \
			       --libdir=$PWD/../../`uname -m`-linux-libs

