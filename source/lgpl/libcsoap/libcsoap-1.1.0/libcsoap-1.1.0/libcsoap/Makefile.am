
lib_LTLIBRARIES=libcsoap.la

libcsoap_ladir=$(includedir)/libcsoap-@csoap_release@/libcsoap

libcsoap_la_SOURCES=soap-xml.c soap-fault.c soap-env.c soap-service.c    \
                    soap-router.c soap-client.c soap-server.c soap-ctx.c \
                    soap-admin.c

libcsoap_la_HEADERS=soap-xml.h soap-fault.h soap-env.h soap-service.h    \
                    soap-router.h soap-client.h soap-server.h soap-ctx.h \
                    soap-admin.h

libcsoap_la_LDFLAGS= -version-info @csoap_version@ -release @csoap_release@
libcsoap_la_CFLAGS=-I${top_srcdir}

