#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

# Module Configuration
LONGNAME = Avahi IPv4LL network address configuration daemon
NAME     = avahi-autoipd
VERSION  = 0.6.31
TYPE     = none

BINFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-bin

CPFILES = $(BINFOLDER)/avahi-autoipd
CPFILES_DEST = loewe/bin

# The helper scripts in /etc are more like examples. They should better 
# be maintained (and installed) by the linux distribution. 
# CPDIRS = etc/avahi
# CPDIRS_DEST = target/etc

# include project targets 
include $(COMPENV)/mk/targets.mk
