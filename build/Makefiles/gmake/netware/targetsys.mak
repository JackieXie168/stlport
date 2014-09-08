# Time-stamp: <05/09/09 21:07:10 ptr>
# $Id: targetsys.mak 1715 2005-09-11 06:27:35Z complement $

SO := nlm

ARCH := lib
AR := mwldnlm -type library -msgstyle gcc -w off
AR_INS_R := 
AR_EXTR :=
AR_OUT = -o $@

EXE := .nlm
