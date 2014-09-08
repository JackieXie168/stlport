# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.04.04
# ---------------------------------------------------------------------------
PROJECT = eh_test.exe
OBJFILES = TestClass.obj \
  nc_alloc.obj \
  random_number.obj \
  test_algo.obj \
  test_algobase.obj \
  test_bit_vector.obj \
  test_bitset.obj \
  test_deque.obj \
  test_hash_map.obj \
  test_hash_set.obj \
  test_list.obj \
  test_map.obj \
  test_rope.obj \
  test_set.obj \
  test_slist.obj \
  test_string.obj \
  test_valarray.obj \
  test_vector.obj main.obj
RESFILES =
RESDEPEN = $(RESFILES)
LIBFILES =
IDLGENFILES =
IDLFILES =
LIBRARIES =
SPARELIBS = Vcl40.lib
PACKAGES = Vcl40.bpi Vclx40.bpi vcljpg40.bpi Vclmid40.bpi Vcldb40.bpi bcbsmp40.bpi \
  ibsmp40.bpi vcldbx40.bpi Qrpt40.bpi TeeUI40.bpi teedb40.bpi tee40.bpi Dss40.bpi
DEFFILE =
# ---------------------------------------------------------------------------
PATHCPP = .;
PATHPAS = .;
PATHASM = .;
PATHRC = .;
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = __STL_USE_NEWALLOC;_NOTHREADS
SYSDEFINES = _RTLDLL;NO_STRICT;USEPACKAGES
 # ---------------------------------------------------------------------------
CFLAG1 = -I.;..\..\stlport;$(BCB)\include;$(BCB)\include\vcl \
  -Od -w -Ve -r- -a8 -k -y -v -vi- -c -b- -w-par \
  -w-inl -Vx -tW -tWM -D$(SYSDEFINES);$(USERDEFINES)
# CFLAG1 = -I.;$(BCB)\include;$(BCB)\include\vcl \
  -Od -Hc -H=$(BCB)\lib\vcl40.csm -w -Ve -r- -a8 -k -y -v -vi- -c -b- -w-par \
  -w-inl -Vx -tW -tWM -D$(SYSDEFINES);$(USERDEFINES)
IDLCFLAGS = -I"." \
  -I"..\..\stl" -I$(BCB)\include -I$(BCB)\include\vcl \
  -src_suffixcpp -D__STL_USE_NEWALLOC
PFLAGS = -U.;$(BCB)\lib\obj;$(BCB)\lib;$(RELEASELIBPATH) \
  -I.;.\;..\..\stl;$(BCB)\include;$(BCB)\include\vcl \
  -D__STL_USE_NEWALLOC -$YD -$W -$O- -v -JPHNE -M
RFLAGS = -i.;.\;..\..\stl;$(BCB)\include;$(BCB)\include\vcl \
  -D__STL_USE_NEWALLOC
AFLAGS = /i. /iD:\home\fbp\stl\dev\stl /i$(BCB)\include \
  /i$(BCB)\include\vcl /d__STL_USE_NEWALLOC /mx /w2 /zd
LFLAGS = -L.;$(BCB)\lib\obj;$(BCB)\lib;$(RELEASELIBPATH) -aa \
  -Tpe -x -Gn -v
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj Memmgr.Lib $(PACKAGES) sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mti.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0
Locale=1033
CodePage=1252

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[HistoryLists\hlIncludePath]
Count=1
Item0=.;D:\home\fbp\stl\dev\stl;$(BCB)\include;$(BCB)\include\vcl

[HistoryLists\hlLibraryPath]
Count=1
Item0=$(BCB)\lib\obj;$(BCB)\lib

[HistoryLists\hlDebugSourcePath]
Count=1
Item0=$(BCB)\source\vcl

[HistoryLists\hlConditionals]
Count=1
Item0=__STL_USE_NEWALLOC

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

[Parameters]
RunParams=
HostApplication=
RemoteHost=
RemotePath=
RemoteDebug=0

[Compiler]
InMemoryExe=0
ShowInfoMsgs=0

[CORBA]
AddServerUnit=1
AddClientUnit=1
PrecompiledHeaders=1

!endif

# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif

!if !$d(IDL2CPP)
IDL2CPP = idl2cpp
!endif

# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) -n. -Sr -Ss -Sd {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -fo$@ $<
# ---------------------------------------------------------------------------
