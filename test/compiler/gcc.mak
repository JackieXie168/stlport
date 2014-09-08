# -*- Makefile -*- Time-stamp: <04/03/14 23:50:57 ptr>
# $Id: gcc.mak 880 2004-08-09 11:24:12Z ptr $

SRCROOT := ../../src/explore
COMPILER_NAME := gcc

ALL_TAGS := compile-only
STLPORT_DIR := ../..
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak
compile-only:	$(OBJ)
