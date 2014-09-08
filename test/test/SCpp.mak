#   File:       SCpp.make
#   Target:     stl_test.68K
#   Created:    Wednesday, August 12, 1998 08:14:00 PM


MAKEFILE     = SCpp.make
_MondoBuild_ = # {MAKEFILE}  # Make blank to avoid rebuilds when makefile is modified
Includes     = -i : -i "{CIncludes}" -i "{STL}" # -i "{STL}supplement:"		#*TY 01/19/1999 - removed supplement:
Sym_68K      = # -sym on 
ObjDir_68K   = :	# objects under current directory. if separate directory is desired, create it before running make
SCpp_Options = -ansi on -bool on -exceptions on  -rtti on -b2 -frames -mbg full -opt all -w 12

STL_Options  = 	#-d __STL_USE_NEWALLOC=1 �
				-d __STL_DEBUG=1 -d __STL_DEBUG_ALLOC=1 �
				-d __STL_NO_EXCEPTION_HEADER=1		#*TY 01/19/1999 - added __STL_NO_EXCEPTION_HEADER (stdexcept.h in {CIncludes} can not be used)
				
CPlusOptions = {Includes} {Sym_68K} {STL_Options} {SCpp_Options} -model far -mc68020 


Objects_68K  = �
	"{ObjDir_68K}accum1.cpp.o" �
	"{ObjDir_68K}accum2.cpp.o" �
	"{ObjDir_68K}adjdiff0.cpp.o" �
	"{ObjDir_68K}adjdiff1.cpp.o" �
	"{ObjDir_68K}adjdiff2.cpp.o" �
	"{ObjDir_68K}adjfind0.cpp.o" �
	"{ObjDir_68K}adjfind1.cpp.o" �
	"{ObjDir_68K}adjfind2.cpp.o" �
	"{ObjDir_68K}advance.cpp.o" �
	"{ObjDir_68K}alg1.cpp.o" �
	"{ObjDir_68K}alg2.cpp.o" �
	"{ObjDir_68K}alg3.cpp.o" �
	"{ObjDir_68K}alg4.cpp.o" �
	"{ObjDir_68K}alg5.cpp.o" �
	"{ObjDir_68K}bcompos1.cpp.o" �
	"{ObjDir_68K}bcompos2.cpp.o" �
	"{ObjDir_68K}bind1st1.cpp.o" �
	"{ObjDir_68K}bind1st2.cpp.o" �
	"{ObjDir_68K}bind2nd1.cpp.o" �
	"{ObjDir_68K}bind2nd2.cpp.o" �
	"{ObjDir_68K}binsert1.cpp.o" �
	"{ObjDir_68K}binsert2.cpp.o" �
	"{ObjDir_68K}binsrch1.cpp.o" �
	"{ObjDir_68K}binsrch2.cpp.o" �
	"{ObjDir_68K}bitset1.cpp.o" �
	"{ObjDir_68K}bnegate1.cpp.o" �
	"{ObjDir_68K}bnegate2.cpp.o" �
	"{ObjDir_68K}bvec1.cpp.o" �
	"{ObjDir_68K}copy1.cpp.o" �
	"{ObjDir_68K}copy2.cpp.o" �
	"{ObjDir_68K}copy3.cpp.o" �
	"{ObjDir_68K}copy4.cpp.o" �
	"{ObjDir_68K}copyb.cpp.o" �
	"{ObjDir_68K}copyb0.cpp.o" �
	"{ObjDir_68K}count0.cpp.o" �
	"{ObjDir_68K}count1.cpp.o" �
	"{ObjDir_68K}countif1.cpp.o" �
	"{ObjDir_68K}deque1.cpp.o" �
	"{ObjDir_68K}divides.cpp.o" �
	"{ObjDir_68K}eqlrnge0.cpp.o" �
	"{ObjDir_68K}eqlrnge1.cpp.o" �
	"{ObjDir_68K}eqlrnge2.cpp.o" �
	"{ObjDir_68K}equal0.cpp.o" �
	"{ObjDir_68K}equal1.cpp.o" �
	"{ObjDir_68K}equal2.cpp.o" �
	"{ObjDir_68K}equalto.cpp.o" �
	"{ObjDir_68K}fill1.cpp.o" �
	"{ObjDir_68K}filln1.cpp.o" �
	"{ObjDir_68K}find0.cpp.o" �
	"{ObjDir_68K}find1.cpp.o" �
	"{ObjDir_68K}findif0.cpp.o" �
	"{ObjDir_68K}findif1.cpp.o" �
	"{ObjDir_68K}finsert1.cpp.o" �
	"{ObjDir_68K}finsert2.cpp.o" �
	"{ObjDir_68K}foreach0.cpp.o" �
	"{ObjDir_68K}foreach1.cpp.o" �
	"{ObjDir_68K}func1.cpp.o" �
	"{ObjDir_68K}func2.cpp.o" �
	"{ObjDir_68K}func3.cpp.o" �
	"{ObjDir_68K}gener1.cpp.o" �
	"{ObjDir_68K}gener2.cpp.o" �
	"{ObjDir_68K}genern1.cpp.o" �
	"{ObjDir_68K}genern2.cpp.o" �
	"{ObjDir_68K}greateq.cpp.o" �
	"{ObjDir_68K}greater.cpp.o" �
	"{ObjDir_68K}hmap1.cpp.o" �
	"{ObjDir_68K}hmmap1.cpp.o" �
	"{ObjDir_68K}hmset1.cpp.o" �
	"{ObjDir_68K}hset2.cpp.o" �
	"{ObjDir_68K}incl0.cpp.o" �
	"{ObjDir_68K}incl1.cpp.o" �
	"{ObjDir_68K}incl2.cpp.o" �
	"{ObjDir_68K}inplmrg1.cpp.o" �
	"{ObjDir_68K}inplmrg2.cpp.o" �
	"{ObjDir_68K}inrprod0.cpp.o" �
	"{ObjDir_68K}inrprod1.cpp.o" �
	"{ObjDir_68K}inrprod2.cpp.o" �
	"{ObjDir_68K}insert1.cpp.o" �
	"{ObjDir_68K}insert2.cpp.o" �
	"{ObjDir_68K}iota1.cpp.o" �
	"{ObjDir_68K}istmit1.cpp.o" �
	"{ObjDir_68K}iter1.cpp.o" �
	"{ObjDir_68K}iter2.cpp.o" �
	"{ObjDir_68K}iter3.cpp.o" �
	"{ObjDir_68K}iter4.cpp.o" �
	"{ObjDir_68K}iterswp0.cpp.o" �
	"{ObjDir_68K}iterswp1.cpp.o" �
	"{ObjDir_68K}less.cpp.o" �
	"{ObjDir_68K}lesseq.cpp.o" �
	"{ObjDir_68K}lexcmp1.cpp.o" �
	"{ObjDir_68K}lexcmp2.cpp.o" �
	"{ObjDir_68K}list1.cpp.o" �
	"{ObjDir_68K}list2.cpp.o" �
	"{ObjDir_68K}list3.cpp.o" �
	"{ObjDir_68K}list4.cpp.o" �
	"{ObjDir_68K}logicand.cpp.o" �
	"{ObjDir_68K}logicnot.cpp.o" �
	"{ObjDir_68K}logicor.cpp.o" �
	"{ObjDir_68K}lwrbnd1.cpp.o" �
	"{ObjDir_68K}lwrbnd2.cpp.o" �
	"{ObjDir_68K}map1.cpp.o" �
	"{ObjDir_68K}max1.cpp.o" �
	"{ObjDir_68K}max2.cpp.o" �
	"{ObjDir_68K}maxelem1.cpp.o" �
	"{ObjDir_68K}maxelem2.cpp.o" �
	"{ObjDir_68K}merge0.cpp.o" �
	"{ObjDir_68K}merge1.cpp.o" �
	"{ObjDir_68K}merge2.cpp.o" �
	"{ObjDir_68K}min1.cpp.o" �
	"{ObjDir_68K}min2.cpp.o" �
	"{ObjDir_68K}minelem1.cpp.o" �
	"{ObjDir_68K}minelem2.cpp.o" �
	"{ObjDir_68K}minus.cpp.o" �
	"{ObjDir_68K}mismtch0.cpp.o" �
	"{ObjDir_68K}mismtch1.cpp.o" �
	"{ObjDir_68K}mismtch2.cpp.o" �
	"{ObjDir_68K}mkheap0.cpp.o" �
	"{ObjDir_68K}mkheap1.cpp.o" �
	"{ObjDir_68K}mmap1.cpp.o" �
	"{ObjDir_68K}mmap2.cpp.o" �
	"{ObjDir_68K}modulus.cpp.o" �
	"{ObjDir_68K}mset1.cpp.o" �
	"{ObjDir_68K}mset3.cpp.o" �
	"{ObjDir_68K}mset4.cpp.o" �
	"{ObjDir_68K}mset5.cpp.o" �
	"{ObjDir_68K}negate.cpp.o" �
	"{ObjDir_68K}nequal.cpp.o" �
	"{ObjDir_68K}nextprm0.cpp.o" �
	"{ObjDir_68K}nextprm1.cpp.o" �
	"{ObjDir_68K}nextprm2.cpp.o" �
	"{ObjDir_68K}nthelem0.cpp.o" �
	"{ObjDir_68K}nthelem1.cpp.o" �
	"{ObjDir_68K}nthelem2.cpp.o" �
	"{ObjDir_68K}ostmit.cpp.o" �
	"{ObjDir_68K}pair0.cpp.o" �
	"{ObjDir_68K}pair1.cpp.o" �
	"{ObjDir_68K}pair2.cpp.o" �
	"{ObjDir_68K}parsrt0.cpp.o" �
	"{ObjDir_68K}parsrt1.cpp.o" �
	"{ObjDir_68K}parsrt2.cpp.o" �
	"{ObjDir_68K}parsrtc0.cpp.o" �
	"{ObjDir_68K}parsrtc1.cpp.o" �
	"{ObjDir_68K}parsrtc2.cpp.o" �
	"{ObjDir_68K}partsrt0.cpp.o" �
	"{ObjDir_68K}partsum0.cpp.o" �
	"{ObjDir_68K}partsum1.cpp.o" �
	"{ObjDir_68K}partsum2.cpp.o" �
	"{ObjDir_68K}pheap1.cpp.o" �
	"{ObjDir_68K}pheap2.cpp.o" �
	"{ObjDir_68K}plus.cpp.o" �
	"{ObjDir_68K}pqueue1.cpp.o" �
	"{ObjDir_68K}prevprm0.cpp.o" �
	"{ObjDir_68K}prevprm1.cpp.o" �
	"{ObjDir_68K}prevprm2.cpp.o" �
	"{ObjDir_68K}ptition0.cpp.o" �
	"{ObjDir_68K}ptition1.cpp.o" �
	"{ObjDir_68K}ptrbinf1.cpp.o" �
	"{ObjDir_68K}ptrbinf2.cpp.o" �
	"{ObjDir_68K}ptrunf1.cpp.o" �
	"{ObjDir_68K}ptrunf2.cpp.o" �
	"{ObjDir_68K}queue1.cpp.o" �
	"{ObjDir_68K}rawiter.cpp.o" �
	"{ObjDir_68K}remcopy1.cpp.o" �
	"{ObjDir_68K}remcpif1.cpp.o" �
	"{ObjDir_68K}remif1.cpp.o" �
	"{ObjDir_68K}remove1.cpp.o" �
	"{ObjDir_68K}repcpif1.cpp.o" �
	"{ObjDir_68K}replace0.cpp.o" �
	"{ObjDir_68K}replace1.cpp.o" �
	"{ObjDir_68K}replcpy1.cpp.o" �
	"{ObjDir_68K}replif1.cpp.o" �
	"{ObjDir_68K}revbit1.cpp.o" �
	"{ObjDir_68K}revbit2.cpp.o" �
	"{ObjDir_68K}revcopy1.cpp.o" �
	"{ObjDir_68K}reverse1.cpp.o" �
	"{ObjDir_68K}reviter1.cpp.o" �
	"{ObjDir_68K}reviter2.cpp.o" �
	"{ObjDir_68K}rndshuf0.cpp.o" �
	"{ObjDir_68K}rndshuf1.cpp.o" �
	"{ObjDir_68K}rndshuf2.cpp.o" �
	"{ObjDir_68K}rotate0.cpp.o" �
	"{ObjDir_68K}rotate1.cpp.o" �
	"{ObjDir_68K}rotcopy0.cpp.o" �
	"{ObjDir_68K}rotcopy1.cpp.o" �
	"{ObjDir_68K}search0.cpp.o" �
	"{ObjDir_68K}search1.cpp.o" �
	"{ObjDir_68K}search2.cpp.o" �
	"{ObjDir_68K}set1.cpp.o" �
	"{ObjDir_68K}set2.cpp.o" �
	"{ObjDir_68K}setdiff0.cpp.o" �
	"{ObjDir_68K}setdiff1.cpp.o" �
	"{ObjDir_68K}setdiff2.cpp.o" �
	"{ObjDir_68K}setintr0.cpp.o" �
	"{ObjDir_68K}setintr1.cpp.o" �
	"{ObjDir_68K}setintr2.cpp.o" �
	"{ObjDir_68K}setsymd0.cpp.o" �
	"{ObjDir_68K}setsymd1.cpp.o" �
	"{ObjDir_68K}setsymd2.cpp.o" �
	"{ObjDir_68K}setunon0.cpp.o" �
	"{ObjDir_68K}setunon1.cpp.o" �
	"{ObjDir_68K}setunon2.cpp.o" �
#	"{ObjDir_68K}single.cpp.o" �
	"{ObjDir_68K}slist1.cpp.o" �
	"{ObjDir_68K}sort1.cpp.o" �
	"{ObjDir_68K}sort2.cpp.o" �
	"{ObjDir_68K}stack1.cpp.o" �
	"{ObjDir_68K}stack2.cpp.o" �
#	"{ObjDir_68K}stat.cpp.o" �
	"{ObjDir_68K}stblptn0.cpp.o" �
	"{ObjDir_68K}stblptn1.cpp.o" �
	"{ObjDir_68K}stblsrt1.cpp.o" �
	"{ObjDir_68K}stblsrt2.cpp.o" �
#	"{ObjDir_68K}stl_single.cpp.o" �
	"{ObjDir_68K}stl_test.cpp.o" �
	"{ObjDir_68K}string1.cpp.o" �
	"{ObjDir_68K}swap1.cpp.o" �
	"{ObjDir_68K}swprnge1.cpp.o" �
	"{ObjDir_68K}times.cpp.o" �
	"{ObjDir_68K}trnsfrm1.cpp.o" �
	"{ObjDir_68K}trnsfrm2.cpp.o" �
	"{ObjDir_68K}ucompos1.cpp.o" �
	"{ObjDir_68K}ucompos2.cpp.o" �
	"{ObjDir_68K}unegate1.cpp.o" �
	"{ObjDir_68K}unegate2.cpp.o" �
	"{ObjDir_68K}uniqcpy1.cpp.o" �
	"{ObjDir_68K}uniqcpy2.cpp.o" �
	"{ObjDir_68K}unique1.cpp.o" �
	"{ObjDir_68K}unique2.cpp.o" �
	"{ObjDir_68K}uprbnd1.cpp.o" �
	"{ObjDir_68K}uprbnd2.cpp.o" �
	"{ObjDir_68K}vec1.cpp.o" �
	"{ObjDir_68K}vec2.cpp.o" �
	"{ObjDir_68K}vec3.cpp.o" �
	"{ObjDir_68K}vec4.cpp.o" �
	"{ObjDir_68K}vec5.cpp.o" �
	"{ObjDir_68K}vec6.cpp.o" �
	"{ObjDir_68K}vec7.cpp.o" �
	"{ObjDir_68K}vec8.cpp.o" �
#	end


"{ObjDir_68K}" � :		#*TY 08/12/1998 - directory dependency


.cpp.o � .cpp {_MondoBuild_}
	###########
	echo Compiling:  file "'{default}.cpp'"
	{CPlus} {depDir}{default}.cpp -o {targDir}{default}.cpp.o {CPlusOptions} -seg {default}
	echo 


stl_test.68K �� {_MondoBuild_} {Objects_68K}
	###########
	echo Linking:    "{Targ}"
	Link �
		-o {Targ} -d -sym 3.2 -cSym Alar �
		{Objects_68K} �
		-t 'MPST' �
		-c 'MPS ' �
		-mf �
		-model far �
		"{Libraries}Stubs.o" �
		"{Libraries}MathLib.o" �
		#"{CLibraries}Complex.o" �
		"{CLibraries}CPlusLib.o" �
		"{CLibraries}IOStreams.o" �
		"{CLibraries}StdCLib.o" �
		"{Libraries}MacRuntime.o" �
		"{Libraries}IntEnv.o" �
		#"{Libraries}ToolLibs.o" �
		"{Libraries}Interface.o" �
		# end
	echo �# Finished Building "'{Targ}'"


