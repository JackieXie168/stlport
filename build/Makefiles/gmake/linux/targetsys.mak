# Time-stamp: <05/09/09 20:59:42 ptr>
# $Id: targetsys.mak 1715 2005-09-11 06:27:35Z complement $

SO := so

ARCH := a
ifdef TARGET_OS
AR := ${TARGET_OS}-ar
else
AR := ar
endif
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@
