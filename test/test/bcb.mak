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
PROJECT = stl_test.exe
OBJFILES = \
   vec2.obj\
   vec7.obj\
   vec6.obj\
   vec5.obj\
   vec4.obj\
   vec3.obj\
   vec8.obj\
   stat.obj\
   uprbnd2.obj\
   uprbnd1.obj\
   unique2.obj\
   unique1.obj\
   uniqcpy2.obj\
   uniqcpy1.obj\
   unegate2.obj\
   unegate1.obj\
   ucompos2.obj\
   ucompos1.obj\
   trnsfrm2.obj\
   trnsfrm1.obj\
   times.obj\
   swprnge1.obj\
   swap1.obj\
   stl_test.obj\
   stblsrt2.obj\
   stblsrt1.obj\
   stblptn1.obj\
   stblptn0.obj\
   vec1.obj\
   rotcopy0.obj\
   stack1.obj\
   sort2.obj\
   sort1.obj\
   setunon2.obj\
   setunon1.obj\
   setunon0.obj\
   setsymd2.obj\
   setsymd1.obj\
   setsymd0.obj\
   setintr2.obj\
   setintr1.obj\
   setintr0.obj\
   setdiff2.obj\
   setdiff1.obj\
   setdiff0.obj\
   set2.obj\
   set1.obj\
   search2.obj\
   search1.obj\
   search0.obj\
   rotcopy1.obj\
   stack2.obj\
   ptrunf1.obj\
   rotate0.obj\
   rndshuf2.obj\
   rndshuf1.obj\
   rndshuf0.obj\
   reviter2.obj\
   reviter1.obj\
   reverse1.obj\
   revcopy1.obj\
   revbit2.obj\
   revbit1.obj\
   replif1.obj\
   replcpy1.obj\
   replace1.obj\
   replace0.obj\
   repcpif1.obj\
   remove1.obj\
   remif1.obj\
   remcpif1.obj\
   remcopy1.obj\
   rawiter.obj\
   queue1.obj\
   ptrunf2.obj\
   rotate1.obj\
   pair0.obj\
   ptrbinf1.obj\
   ptition1.obj\
   ptition0.obj\
   prevprm2.obj\
   prevprm1.obj\
   prevprm0.obj\
   pqueue1.obj\
   plus.obj\
   pheap2.obj\
   pheap1.obj\
   partsum2.obj\
   partsum1.obj\
   partsum0.obj\
   partsrt0.obj\
   parsrtc2.obj\
   parsrtc1.obj\
   parsrtc0.obj\
   parsrt2.obj\
   parsrt1.obj\
   parsrt0.obj\
   pair2.obj\
   pair1.obj\
   ptrbinf2.obj\
   minelem1.obj\
   nthelem2.obj\
   nthelem1.obj\
   nthelem0.obj\
   nextprm2.obj\
   nextprm1.obj\
   nextprm0.obj\
   nequal.obj\
   negate.obj\
   mset5.obj\
   mset4.obj\
   mset3.obj\
   mset1.obj\
   modulus.obj\
   mmap2.obj\
   mmap1.obj\
   mkheap1.obj\
   mkheap0.obj\
   mismtch2.obj\
   mismtch1.obj\
   mismtch0.obj\
   minus.obj\
   minelem2.obj\
   ostmit.obj\
   iterswp1.obj\
   min1.obj\
   merge2.obj\
   merge1.obj\
   merge0.obj\
   maxelem2.obj\
   maxelem1.obj\
   max2.obj\
   max1.obj\
   map1.obj\
   lwrbnd2.obj\
   lwrbnd1.obj\
   logicor.obj\
   logicnot.obj\
   logicand.obj\
   list4.obj\
   list3.obj\
   list2.obj\
   list1.obj\
   lexcmp2.obj\
   lexcmp1.obj\
   lesseq.obj\
   less.obj\
   min2.obj\
   greater.obj\
   iter4.obj\
   iter3.obj\
   iter2.obj\
   iter1.obj\
   istmit1.obj\
   iota1.obj\
   insert2.obj\
   insert1.obj\
   inrprod2.obj\
   inrprod1.obj\
   inrprod0.obj\
   inplmrg2.obj\
   inplmrg1.obj\
   incl2.obj\
   incl1.obj\
   incl0.obj\
   iterswp0.obj\
   eqlrnge2.obj\
   genern2.obj\
   genern1.obj\
   gener2.obj\
   gener1.obj\
   func3.obj\
   func2.obj\
   func1.obj\
   foreach1.obj\
   foreach0.obj\
   finsert2.obj\
   finsert1.obj\
   findif1.obj\
   findif0.obj\
   find1.obj\
   find0.obj\
   filln1.obj\
   fill1.obj\
   equalto.obj\
   equal2.obj\
   equal1.obj\
   equal0.obj\
   greateq.obj\
   binsrch1.obj\
   eqlrnge0.obj\
   divides.obj\
   deque1.obj\
   countif1.obj\
   count1.obj\
   count0.obj\
   copyb0.obj\
   copyb.obj\
   copy4.obj\
   copy3.obj\
   copy2.obj\
   copy1.obj\
   bvec1.obj\
   bnegate2.obj\
   bnegate1.obj\
   binsrch2.obj\
   eqlrnge1.obj\
   accum1.obj\
   binsert1.obj\
   bind2nd2.obj\
   bind2nd1.obj\
   bind1st1.obj\
   bind1st2.obj\
   bcompos2.obj\
   bcompos1.obj\
   alg5.obj\
   alg4.obj\
   alg3.obj\
   alg2.obj\
   alg1.obj\
   advance.obj\
   adjfind2.obj\
   adjfind1.obj\
   adjfind0.obj\
   adjdiff2.obj\
   adjdiff1.obj\
   adjdiff0.obj\
   accum2.obj\
   binsert2.obj\
   hmap1.obj hmmap1.obj hset2.obj hmset1.obj

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
CFLAG1 = -I.;..\..\stlport\old_hp;..\..\stlport\BCB;..\..\stlport;$(BCB)\include;$(BCB)\include\vcl \
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
