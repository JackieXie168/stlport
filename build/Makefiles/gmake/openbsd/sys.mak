# Time-stamp: <05/09/09 21:10:45 ptr>
# $Id: sys.mak 1715 2005-09-11 06:27:35Z complement $

INSTALL := /usr/bin/install

INSTALL_SO := ${INSTALL} -c -m 0755
INSTALL_A := ${INSTALL} -c -m 0644
INSTALL_EXE := ${INSTALL} -c -m 0755

EXT_TEST := /usr/bin/test
