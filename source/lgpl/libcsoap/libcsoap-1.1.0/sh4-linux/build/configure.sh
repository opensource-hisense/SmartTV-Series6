#!/bin/sh
TARGETOS=`basename "$COMPENV"`
TARGET="$COMPENV/../common/comp/`uname -m`-linux+$TARGETOS/target"
CPPVERSION="4.2.4"

INSTALLDIR="$COMPENV_INSTALL_DIR/$COMPENV_PROJECT_VARIANT+$TARGETOS/target"
XML2_CONFIG="$INSTALLDIR/usr/bin/xml2-config"
CFLAGS="-I $TARGET/usr/include/c++/$CPPVERSION/sh4-linux/ -I $TARGET/usr/include/c++/$CPPVERSION/ -I $CODEBASE_DIR/oss/gpl/$TARGETOS/target/usr/include/libxml2"
CXXFLAGS=$CFLAGS
LDFLAGS="-Wl,-L$TARGET/lib -Wl,-L$TARGET/usr/lib -Wl,-L$CODEBASE_DIR/oss/gpl/$TARGETOS/target/lib -Wl,-L$CODEBASE_DIR/oss/gpl/$TARGETOS/target/usr/lib -Wl,-L$CODEBASE_DIR/oss/gpl/$TARGETOS/target/usr/lib"

export CFLAGS
export CXXFLAGS
export LDFLAGS
export XML2_CONFIG

# temporary workaround for GrandCentrix ipad connection loss problem:
export CFLAGS="-DENABLE_TEMPORARY_IPAD_WORKAROUND $CFLAGS"

../../libcsoap-1.1.0/configure --host=sh4-linux --enable-shared=NO --prefix="$PWD/../usr" \
			       --includedir=$PWD/../../include \
			       --libdir=$PWD/../../sh4-linux-libs \
			       --with-ssl

