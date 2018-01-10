#
# Loewe Module Makefile
#

# include project defaults
include $(COMPENV)/mk/config.mk

LONGNAME = boost header 
NAME     = boost
VERSION  = 1.48
TYPE     = none
NODOC    = YES

PUBINCFOLDERS = boost 

LIBFOLDER= $(COMPENV_TARGET_MACHINE)-$(COMPENV_TARGET_OS)-lib

ifeq ($(COMPENV_TARGET_OS),winnt-msvc)
LIBFOLDER= $(COMPENV_TARGET_OS)-lib
PUBLIBS += $(wildcard $(LIBFOLDER)/boost_system.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/boost_date_time.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/boost_thread.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/boost_filesystem.*)
else
#PUBLIBS  = $(wildcard $(LIBFOLDER)/lib*)
PUBLIBS += $(LIBFOLDER)/libboost_test_exec_monitor.a
ifneq ($(COMPENV_TARGET_MACHINE),sh4) 
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_unit_test_framework.so*)
endif

PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_signals.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_system.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_atomic.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_date_time.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_thread.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_filesystem.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_program_options.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_serialization.*)
PUBLIBS += $(wildcard $(LIBFOLDER)/libboost_regex.*)
endif

ifeq ($(COMPENV_TARGET_MACHINE),sh4) 
LINSTALLDIR=$(PRJROOT)/target/usr/lib
endif

# include project targets 
include $(COMPENV)/mk/targets.mk
