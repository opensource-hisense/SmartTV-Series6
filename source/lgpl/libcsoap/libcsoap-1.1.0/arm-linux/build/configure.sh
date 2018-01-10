#!/bin/sh
TARGET="$BUILDENV_PROJECT_DIR/../device/mstar/MI_project/project/develop/extra/target"

CFLAGS="-I $TARGET/include/xml2 -I $TARGET/include/openssl -I $TARGET/include"
CXXFLAGS=$CFLAGS
LDFLAGS="-Wl,-L$TARGET/lib"

export CFLAGS
export CXXFLAGS
export LDFLAGS
#export XML2_CONFIG

# temporary workaround for GrandCentrix ipad connection loss problem:
export CFLAGS="-DENABLE_TEMPORARY_IPAD_WORKAROUND $CFLAGS"

../../libcsoap-1.1.0/configure --host=arm-none-linux-gnueabi --prefix="$PWD/../usr" \
			       --includedir=$PWD/../../include \
			       --libdir=$PWD/../../arm-linux-libs \
			       --with-ssl \
                               --with-xml-prefix=$TARGET

#sed -i "s/\/usr\/lib\/i386-linux-gnu/\/home\/$USER\/projects\/codebase2011\/coop\/hilo\/hl1\/utils\/arm-linux-libs\//g" $(find . -type f)
