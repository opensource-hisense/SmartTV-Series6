SUBDIRS=nanohttp libcsoap

bin_SCRIPTS=csoap-config

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA=libcsoap.pc

m4datadir=$(datadir)/aclocal
m4data_DATA=libcsoap.m4

documentation=doc/Doxyfile.api \
              doc/compile.xml  \
              doc/doxygen.css  \
              doc/footer.html  \
              doc/header.html  \
              doc/tutorial.xml \
              doc/images/logo02.gif

broken_examples=examples/nanohttp/client_get.c   \
                examples/nanohttp/client_mime.c  \
                examples/nanohttp/httpcpost.c    \
                examples/nanohttp/httpget.c      \
                examples/nanohttp/httppost.c     \
                examples/nanohttp/postserver.c   \
                examples/nanohttp/client_post_chunked.c

win32_env=win32/MinGW/Makefile    \
          win32/MinGW/compile.bat \
          win32/MinGW/config.h    \
          win32/MinGW/readme.txt  \
          win32/include/wsockcompat.h

EXTRA_DIST=$(documentation) $(win32_env) libcsoap.pc.in libcsoap.m4 \
           $(broken_examples)

