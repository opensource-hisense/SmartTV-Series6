lib_LTLIBRARIES=libnanohttp.la

libnanohttp_ladir=$(includedir)/nanohttp-@nanohttp_release@/nanohttp

libnanohttp_la_SOURCES=nanohttp-common.c nanohttp-socket.c nanohttp-client.c     \
                           nanohttp-server.c nanohttp-stream.c nanohttp-mime.c   \
                           nanohttp-request.c nanohttp-response.c                \
                           nanohttp-base64.c nanohttp-ssl.c nanohttp-logging.c

libnanohttp_la_HEADERS=nanohttp-common.h nanohttp-socket.h nanohttp-client.h     \
                           nanohttp-server.h nanohttp-stream.h nanohttp-mime.h   \
                           nanohttp-request.h nanohttp-response.h                \
                           nanohttp-base64.h nanohttp-ssl.h nanohttp-logging.h

libnanohttp_la_LDFLAGS= -version-info @nanohttp_version@ -release @nanohttp_release@
libnanohttp_la_CFLAGS=-I${top_srcdir}

