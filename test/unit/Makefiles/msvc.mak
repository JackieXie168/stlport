!if EXIST(..\..\Makefiles\nmake\config.mak)
!include ..\..\Makefiles\nmake\config.mak
!endif


!ifndef COMPILER_NAME
!error No compiler set, please run 'configure --help' first and chose a compiler.
!endif

!if (("$(COMPILER_NAME)" != "vc6") && \
     ("$(COMPILER_NAME)" != "vc70") && \
     ("$(COMPILER_NAME)" != "vc71") && \
     ("$(COMPILER_NAME)" != "vc8") && \
     ("$(COMPILER_NAME)" != "vc9") && \
     ("$(COMPILER_NAME)" != "icl"))
!error '$(COMPILER_NAME)' not supported by this make file, please rerun 'configure' script and follow instructions.
!endif

SRCROOT=../..
STLPORT_DIR=../..
STLPORT_LIB_DIR= $(STLPORT_DIR)/../lib

!include Makefile.inc

!ifndef WITHOUT_STLPORT
INCLUDES=$(INCLUDES) /I$(STLPORT_INCLUDE_DIR) /I$(SRCROOT)/src /I../include /FI warning_disable.h
LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR) stlport.6.0.lib
!else
INCLUDES=$(INCLUDES) /I$(STLPORT_DIR)/src /I$(SRCROOT)/src /I../include  /FI warning_disable.h
DEFS=/DWITHOUT_STLPORT
!endif

DEFS_DBG=/D_STLP_DEBUG_UNINITIALIZED
DEFS_STLDBG=/D_STLP_DEBUG_UNINITIALIZED
DEFS_STATIC_DBG=/D_STLP_DEBUG_UNINITIALIZED
DEFS_STATIC_STLDBG=/D_STLP_DEBUG_UNINITIALIZED

!if ("$(COMPILER_NAME)" != "icl")
# Important in a number of builds.
OPT = /Zm800 /Od
!endif
!include $(SRCROOT)/Makefiles/nmake/top.mak

install:
  copy obj\vc9\shared\stl_unit_test.exe ..\..\..\bin
  copy obj\vc9\shared\stl_unit_test.pdb ..\..\..\bin
