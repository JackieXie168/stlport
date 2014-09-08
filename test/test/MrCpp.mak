#   File:       MrCpp.make
#   Target:     stl_test.PPC
#   Created:    Wednesday, August 12, 1998 12:37:01 AM


MAKEFILE     = MrCpp.make
_MondoBuild_ = # {MAKEFILE}  # Make the definition blank to avoid rebuilding when makefile is modified
Includes     = -i : -i "{CIncludes}" -i "{STL}" -i "{STL}old_hp:"		#*TY 05/24/1999 - added old_hp directory
Sym_PPC      = # -sym big # turning on sym makes link time extremely long.
ObjDir_PPC   = :	# objects under current directory. if separate directory is desired, create it before running make
MrCpp_Options = -align power -exceptions on -rtti on -bool on -ansi on -ansifor -j0

STL_Options  = 	#-d __STL_USE_NEWALLOC=1 �
				-d __STL_DEBUG=1 -d __STL_DEBUG_ALLOC=1 �
				-d __STL_NO_EXCEPTION_HEADER=1		#*TY 01/19/1999 - added __STL_NO_EXCEPTION_HEADER (stdexcept.h in {CIncludes} can not be used)

PPCCPlusOptions = {Includes} {Sym_PPC} {STL_Options} {MrCpp_Options} -opt size

Objects_PPC  = �
	"{ObjDir_PPC}accum1.cpp.x" �
	"{ObjDir_PPC}accum2.cpp.x" �
	"{ObjDir_PPC}adjdiff0.cpp.x" �
	"{ObjDir_PPC}adjdiff1.cpp.x" �
	"{ObjDir_PPC}adjdiff2.cpp.x" �
	"{ObjDir_PPC}adjfind0.cpp.x" �
	"{ObjDir_PPC}adjfind1.cpp.x" �
	"{ObjDir_PPC}adjfind2.cpp.x" �
	"{ObjDir_PPC}advance.cpp.x" �
	"{ObjDir_PPC}alg1.cpp.x" �
	"{ObjDir_PPC}alg2.cpp.x" �
	"{ObjDir_PPC}alg3.cpp.x" �
	"{ObjDir_PPC}alg4.cpp.x" �
	"{ObjDir_PPC}alg5.cpp.x" �
	"{ObjDir_PPC}bcompos1.cpp.x" �
	"{ObjDir_PPC}bcompos2.cpp.x" �
	"{ObjDir_PPC}bind1st1.cpp.x" �
	"{ObjDir_PPC}bind1st2.cpp.x" �
	"{ObjDir_PPC}bind2nd1.cpp.x" �
	"{ObjDir_PPC}bind2nd2.cpp.x" �
	"{ObjDir_PPC}binsert1.cpp.x" �
	"{ObjDir_PPC}binsert2.cpp.x" �
	"{ObjDir_PPC}binsrch1.cpp.x" �
	"{ObjDir_PPC}binsrch2.cpp.x" �
	"{ObjDir_PPC}bitset1.cpp.x" �
	"{ObjDir_PPC}bnegate1.cpp.x" �
	"{ObjDir_PPC}bnegate2.cpp.x" �
	"{ObjDir_PPC}bvec1.cpp.x" �
	"{ObjDir_PPC}copy1.cpp.x" �
	"{ObjDir_PPC}copy2.cpp.x" �
	"{ObjDir_PPC}copy3.cpp.x" �
	"{ObjDir_PPC}copy4.cpp.x" �
	"{ObjDir_PPC}copyb.cpp.x" �
	"{ObjDir_PPC}copyb0.cpp.x" �
	"{ObjDir_PPC}count0.cpp.x" �
	"{ObjDir_PPC}count1.cpp.x" �
	"{ObjDir_PPC}countif1.cpp.x" �
	"{ObjDir_PPC}deque1.cpp.x" �
	"{ObjDir_PPC}divides.cpp.x" �
	"{ObjDir_PPC}eqlrnge0.cpp.x" �
	"{ObjDir_PPC}eqlrnge1.cpp.x" �
	"{ObjDir_PPC}eqlrnge2.cpp.x" �
	"{ObjDir_PPC}equal0.cpp.x" �
	"{ObjDir_PPC}equal1.cpp.x" �
	"{ObjDir_PPC}equal2.cpp.x" �
	"{ObjDir_PPC}equalto.cpp.x" �
	"{ObjDir_PPC}fill1.cpp.x" �
	"{ObjDir_PPC}filln1.cpp.x" �
	"{ObjDir_PPC}find0.cpp.x" �
	"{ObjDir_PPC}find1.cpp.x" �
	"{ObjDir_PPC}findif0.cpp.x" �
	"{ObjDir_PPC}findif1.cpp.x" �
	"{ObjDir_PPC}finsert1.cpp.x" �
	"{ObjDir_PPC}finsert2.cpp.x" �
	"{ObjDir_PPC}foreach0.cpp.x" �
	"{ObjDir_PPC}foreach1.cpp.x" �
	"{ObjDir_PPC}func1.cpp.x" �
	"{ObjDir_PPC}func2.cpp.x" �
	"{ObjDir_PPC}func3.cpp.x" �
	"{ObjDir_PPC}gener1.cpp.x" �
	"{ObjDir_PPC}gener2.cpp.x" �
	"{ObjDir_PPC}genern1.cpp.x" �
	"{ObjDir_PPC}genern2.cpp.x" �
	"{ObjDir_PPC}greateq.cpp.x" �
	"{ObjDir_PPC}greater.cpp.x" �
	"{ObjDir_PPC}hmap1.cpp.x" �
	"{ObjDir_PPC}hmmap1.cpp.x" �
	"{ObjDir_PPC}hmset1.cpp.x" �
	"{ObjDir_PPC}hset2.cpp.x" �
	"{ObjDir_PPC}incl0.cpp.x" �
	"{ObjDir_PPC}incl1.cpp.x" �
	"{ObjDir_PPC}incl2.cpp.x" �
	"{ObjDir_PPC}inplmrg1.cpp.x" �
	"{ObjDir_PPC}inplmrg2.cpp.x" �
	"{ObjDir_PPC}inrprod0.cpp.x" �
	"{ObjDir_PPC}inrprod1.cpp.x" �
	"{ObjDir_PPC}inrprod2.cpp.x" �
	"{ObjDir_PPC}insert1.cpp.x" �
	"{ObjDir_PPC}insert2.cpp.x" �
	"{ObjDir_PPC}iota1.cpp.x" �
	"{ObjDir_PPC}istmit1.cpp.x" �
	"{ObjDir_PPC}iter1.cpp.x" �
	"{ObjDir_PPC}iter2.cpp.x" �
	"{ObjDir_PPC}iter3.cpp.x" �
	"{ObjDir_PPC}iter4.cpp.x" �
	"{ObjDir_PPC}iterswp0.cpp.x" �
	"{ObjDir_PPC}iterswp1.cpp.x" �
	"{ObjDir_PPC}less.cpp.x" �
	"{ObjDir_PPC}lesseq.cpp.x" �
	"{ObjDir_PPC}lexcmp1.cpp.x" �
	"{ObjDir_PPC}lexcmp2.cpp.x" �
	"{ObjDir_PPC}list1.cpp.x" �
	"{ObjDir_PPC}list2.cpp.x" �
	"{ObjDir_PPC}list3.cpp.x" �
	"{ObjDir_PPC}list4.cpp.x" �
	"{ObjDir_PPC}logicand.cpp.x" �
	"{ObjDir_PPC}logicnot.cpp.x" �
	"{ObjDir_PPC}logicor.cpp.x" �
	"{ObjDir_PPC}lwrbnd1.cpp.x" �
	"{ObjDir_PPC}lwrbnd2.cpp.x" �
	"{ObjDir_PPC}map1.cpp.x" �
	"{ObjDir_PPC}max1.cpp.x" �
	"{ObjDir_PPC}max2.cpp.x" �
	"{ObjDir_PPC}maxelem1.cpp.x" �
	"{ObjDir_PPC}maxelem2.cpp.x" �
	"{ObjDir_PPC}merge0.cpp.x" �
	"{ObjDir_PPC}merge1.cpp.x" �
	"{ObjDir_PPC}merge2.cpp.x" �
	"{ObjDir_PPC}min1.cpp.x" �
	"{ObjDir_PPC}min2.cpp.x" �
	"{ObjDir_PPC}minelem1.cpp.x" �
	"{ObjDir_PPC}minelem2.cpp.x" �
	"{ObjDir_PPC}minus.cpp.x" �
	"{ObjDir_PPC}mismtch0.cpp.x" �
	"{ObjDir_PPC}mismtch1.cpp.x" �
	"{ObjDir_PPC}mismtch2.cpp.x" �
	"{ObjDir_PPC}mkheap0.cpp.x" �
	"{ObjDir_PPC}mkheap1.cpp.x" �
	"{ObjDir_PPC}mmap1.cpp.x" �
	"{ObjDir_PPC}mmap2.cpp.x" �
	"{ObjDir_PPC}modulus.cpp.x" �
	"{ObjDir_PPC}mset1.cpp.x" �
	"{ObjDir_PPC}mset3.cpp.x" �
	"{ObjDir_PPC}mset4.cpp.x" �
	"{ObjDir_PPC}mset5.cpp.x" �
	"{ObjDir_PPC}negate.cpp.x" �
	"{ObjDir_PPC}nequal.cpp.x" �
	"{ObjDir_PPC}nextprm0.cpp.x" �
	"{ObjDir_PPC}nextprm1.cpp.x" �
	"{ObjDir_PPC}nextprm2.cpp.x" �
	"{ObjDir_PPC}nthelem0.cpp.x" �
	"{ObjDir_PPC}nthelem1.cpp.x" �
	"{ObjDir_PPC}nthelem2.cpp.x" �
	"{ObjDir_PPC}ostmit.cpp.x" �
	"{ObjDir_PPC}pair0.cpp.x" �
	"{ObjDir_PPC}pair1.cpp.x" �
	"{ObjDir_PPC}pair2.cpp.x" �
	"{ObjDir_PPC}parsrt0.cpp.x" �
	"{ObjDir_PPC}parsrt1.cpp.x" �
	"{ObjDir_PPC}parsrt2.cpp.x" �
	"{ObjDir_PPC}parsrtc0.cpp.x" �
	"{ObjDir_PPC}parsrtc1.cpp.x" �
	"{ObjDir_PPC}parsrtc2.cpp.x" �
	"{ObjDir_PPC}partsrt0.cpp.x" �
	"{ObjDir_PPC}partsum0.cpp.x" �
	"{ObjDir_PPC}partsum1.cpp.x" �
	"{ObjDir_PPC}partsum2.cpp.x" �
	"{ObjDir_PPC}pheap1.cpp.x" �
	"{ObjDir_PPC}pheap2.cpp.x" �
	"{ObjDir_PPC}plus.cpp.x" �
	"{ObjDir_PPC}pqueue1.cpp.x" �
	"{ObjDir_PPC}prevprm0.cpp.x" �
	"{ObjDir_PPC}prevprm1.cpp.x" �
	"{ObjDir_PPC}prevprm2.cpp.x" �
	"{ObjDir_PPC}ptition0.cpp.x" �
	"{ObjDir_PPC}ptition1.cpp.x" �
	"{ObjDir_PPC}ptrbinf1.cpp.x" �
	"{ObjDir_PPC}ptrbinf2.cpp.x" �
	"{ObjDir_PPC}ptrunf1.cpp.x" �
	"{ObjDir_PPC}ptrunf2.cpp.x" �
	"{ObjDir_PPC}queue1.cpp.x" �
	"{ObjDir_PPC}rawiter.cpp.x" �
	"{ObjDir_PPC}remcopy1.cpp.x" �
	"{ObjDir_PPC}remcpif1.cpp.x" �
	"{ObjDir_PPC}remif1.cpp.x" �
	"{ObjDir_PPC}remove1.cpp.x" �
	"{ObjDir_PPC}repcpif1.cpp.x" �
	"{ObjDir_PPC}replace0.cpp.x" �
	"{ObjDir_PPC}replace1.cpp.x" �
	"{ObjDir_PPC}replcpy1.cpp.x" �
	"{ObjDir_PPC}replif1.cpp.x" �
	"{ObjDir_PPC}revbit1.cpp.x" �
	"{ObjDir_PPC}revbit2.cpp.x" �
	"{ObjDir_PPC}revcopy1.cpp.x" �
	"{ObjDir_PPC}reverse1.cpp.x" �
	"{ObjDir_PPC}reviter1.cpp.x" �
	"{ObjDir_PPC}reviter2.cpp.x" �
	"{ObjDir_PPC}rndshuf0.cpp.x" �
	"{ObjDir_PPC}rndshuf1.cpp.x" �
	"{ObjDir_PPC}rndshuf2.cpp.x" �
	"{ObjDir_PPC}rotate0.cpp.x" �
	"{ObjDir_PPC}rotate1.cpp.x" �
	"{ObjDir_PPC}rotcopy0.cpp.x" �
	"{ObjDir_PPC}rotcopy1.cpp.x" �
	"{ObjDir_PPC}search0.cpp.x" �
	"{ObjDir_PPC}search1.cpp.x" �
	"{ObjDir_PPC}search2.cpp.x" �
	"{ObjDir_PPC}set1.cpp.x" �
	"{ObjDir_PPC}set2.cpp.x" �
	"{ObjDir_PPC}setdiff0.cpp.x" �
	"{ObjDir_PPC}setdiff1.cpp.x" �
	"{ObjDir_PPC}setdiff2.cpp.x" �
	"{ObjDir_PPC}setintr0.cpp.x" �
	"{ObjDir_PPC}setintr1.cpp.x" �
	"{ObjDir_PPC}setintr2.cpp.x" �
	"{ObjDir_PPC}setsymd0.cpp.x" �
	"{ObjDir_PPC}setsymd1.cpp.x" �
	"{ObjDir_PPC}setsymd2.cpp.x" �
	"{ObjDir_PPC}setunon0.cpp.x" �
	"{ObjDir_PPC}setunon1.cpp.x" �
	"{ObjDir_PPC}setunon2.cpp.x" �
#	"{ObjDir_PPC}single.cpp.x" �
	"{ObjDir_PPC}slist1.cpp.x" �
	"{ObjDir_PPC}sort1.cpp.x" �
	"{ObjDir_PPC}sort2.cpp.x" �
	"{ObjDir_PPC}stack1.cpp.x" �
	"{ObjDir_PPC}stack2.cpp.x" �
#	"{ObjDir_PPC}stat.cpp.x" �
	"{ObjDir_PPC}stblptn0.cpp.x" �
	"{ObjDir_PPC}stblptn1.cpp.x" �
	"{ObjDir_PPC}stblsrt1.cpp.x" �
	"{ObjDir_PPC}stblsrt2.cpp.x" �
#	"{ObjDir_PPC}stl_single.cpp.x" �
	"{ObjDir_PPC}stl_test.cpp.x" �
	"{ObjDir_PPC}string1.cpp.x" �
	"{ObjDir_PPC}swap1.cpp.x" �
	"{ObjDir_PPC}swprnge1.cpp.x" �
	"{ObjDir_PPC}times.cpp.x" �
	"{ObjDir_PPC}trnsfrm1.cpp.x" �
	"{ObjDir_PPC}trnsfrm2.cpp.x" �
	"{ObjDir_PPC}ucompos1.cpp.x" �
	"{ObjDir_PPC}ucompos2.cpp.x" �
	"{ObjDir_PPC}unegate1.cpp.x" �
	"{ObjDir_PPC}unegate2.cpp.x" �
	"{ObjDir_PPC}uniqcpy1.cpp.x" �
	"{ObjDir_PPC}uniqcpy2.cpp.x" �
	"{ObjDir_PPC}unique1.cpp.x" �
	"{ObjDir_PPC}unique2.cpp.x" �
	"{ObjDir_PPC}uprbnd1.cpp.x" �
	"{ObjDir_PPC}uprbnd2.cpp.x" �
	"{ObjDir_PPC}vec1.cpp.x" �
	"{ObjDir_PPC}vec2.cpp.x" �
	"{ObjDir_PPC}vec3.cpp.x" �
	"{ObjDir_PPC}vec4.cpp.x" �
	"{ObjDir_PPC}vec5.cpp.x" �
	"{ObjDir_PPC}vec6.cpp.x" �
	"{ObjDir_PPC}vec7.cpp.x" �
	"{ObjDir_PPC}vec8.cpp.x" �
	# end


"{ObjDir_PPC}" � :		#*TY 08/12/1998 - directory dependency

.cpp.x � .cpp {_MondoBuild_}
	###########
	echo Compiling:  file "'{default}.cpp'"
	{MrCpp} {depDir}{default}.cpp -o {targDir}{default}.cpp.x {PPCCPlusOptions}
	if "{status}"
		set compile_status 1
	end
	echo 


stl_test.PPC �� {_MondoBuild_} {Objects_PPC}
	###########
	if "{compile_status}"
		echo "### Link not performed due to compile error"
		exit "{compile_status}"
	end
	echo Linking:    "{Targ}"
	if "`exists {Targ}`" 
		delete {Targ}		#*TY 01/14/1999 - it is faster to generate executable from the ground up than modifying the existing ones.
	end
	PPCLink �
		-o {Targ} -d {Sym_PPC} �
		{Objects_PPC} �
		-t 'MPST' �
		-c 'MPS ' �
		-mf �
		-Linkfaster off �
		"{SharedLibraries}InterfaceLib" �
#		"{SharedLibraries}StdCLib" �
		"{SharedLibraries}StdCLib_3.5d7" �
		"{SharedLibraries}MathLib" �
		"{PPCLibraries}StdCRuntime.o" �
		"{PPCLibraries}PPCCRuntime.o" �
		"{PPCLibraries}PPCToolLibs.o" �
		"{PPCLibraries}MrCPlusLib.o" �
		"{PPCLibraries}MrCIOStreams.o" �
#		"{SharedLibraries}MrCExceptionsLib" �
		"{SharedLibraries}MrCExceptionsLib_4.1d1" �
		# end
	echo �# Finished Building "'{Targ}'"




