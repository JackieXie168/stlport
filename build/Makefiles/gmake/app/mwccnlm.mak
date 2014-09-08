# -*- makefile -*- Time-stamp: <05/06/03 21:29:43 ptr>
# $Id: mwccnlm.mak 1562 2005-06-06 17:16:05Z ptr $

LDFLAGS += -type generic -w off -nostdlib -msgstyle gcc

STDLIBS = -L"$(NWSDK_DIR)/imports" \
          -L"$(MWCW_NOVELL)/Libraries/Runtime/Output/CLib" \
          -L"$(NWSDK_DIR)/../libc/imports" \
          -lclib.imp -lthreads.imp -lmwcrtl.lib -lnlmlib.imp -llibc.imp
