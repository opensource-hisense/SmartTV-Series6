#
# Loewe Module Makefile
#

# include projects defaults
include $(COMPENV)/mk/config.mk


# module configuration
LONGNAME = Simple IPv4 Link-Local addressing tool
NAME     = avh-ipv4ll
VERSION  = 0.0.1
TYPE     = exe
MAKEFILE = makefile

linux-libs = pthread rt

# LIBS       += csp-lemory csp-lore csp-debug csp-osal-common
LIBS       += $($(COMPENV_TARGET_OS)-libs)
ifeq "$(USE_MEM_DEBUGGING)" "1"
  LIBS += duma
endif


# include project targets
include $(COMPENV)/mk/targets.mk
