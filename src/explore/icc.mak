# -*- Makefile -*- Time-stamp: <03/10/12 20:35:49 ptr>
# $Id$

SRCROOT := .
COMPILER_NAME := icc

STLPORT_INCLUDE_DIR = ../../stlport
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak


INCLUDES += -I$(STLPORT_INCLUDE_DIR)

ifeq ($(OSNAME),linux)
DEFS += -D_STLP_REAL_LOCALE_IMPLEMENTED -D_GNU_SOURCE
endif
