# Time-stamp: <05/09/09 21:12:38 ptr>
# $Id: sys.mak 1737 2005-09-19 19:57:19Z dums $

RC := windres
INSTALL := install

INSTALL_SO := ${INSTALL} -m 0755
INSTALL_A := ${INSTALL} -m 0644
INSTALL_EXE := ${INSTALL} -m 0755

EXT_TEST := test
