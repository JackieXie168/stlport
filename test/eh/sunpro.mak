# ;;; -*- Mode:makefile;-*- 
# Generated automatically from Makefile.in by configure.
# This requires GNU make.

# SHELL=/bin/sh
# srcdir = .
# VPATH = .


# point this to proper location
STL_INCL=-I../../stl/SC5 -I../../stl

AUX_LIST=TestClass.cpp main.cpp nc_alloc.cpp random_number.cpp

TEST_LIST=test_algo.cpp  \
test_algobase.cpp     test_list.cpp test_slist.cpp \
test_bit_vector.cpp   test_vector.cpp \
test_deque.cpp test_set.cpp test_map.cpp \
test_hash_map.cpp  test_hash_set.cpp test_rope.cpp \
test_string.cpp test_bitset.cpp test_valarray.cpp

# TEST_LIST=test_deque.cpp


LIST=${AUX_LIST} ${TEST_LIST}

OBJECTS = $(LIST:%.cpp=%.o) $(STAT_MODULE)
EXECS = $(LIST:%.cpp=%)
TESTS = $(LIST:%.cpp=%.out)
TEST_EXE  = eh_test
TEST  = eh_test.out

CC = CC
CXX = $(CC)

# CXXFLAGS = +w2 -O -xildoff ${STL_INCL} -D__STL_USE_NEWALLOC  -DNO_FAST_ALLOCATOR

# CXXFLAGS = +w2 -xildoff ${STL_INCL}  -I. -D__STL_USE_NEWALLOC
CXXFLAGS = +w2 -pta -xildoff ${STL_INCL} -D__STL_USE_NEWALLOC -DNO_FAST_ALLOCATOR
# CXXFLAGS = +w2 -xildoff -D__STL_USE_NEWALLOC -DNO_FAST_ALLOCATOR -DEH_NO_SGI_STL -DEH_NEW_HEADERS

LIBS = -lm 
LIBSTDCXX = 

all:

check: $(TEST)

$(TEST) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) -o $(TEST_EXE)
	$(TEST_EXE)

SUFFIXES: .cpp.o.out.res

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

%.i : %.cpp
	$(CXX) $(CXXFLAGS) $< -E -H > $@

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -USINGLE -DMAIN -g -o $*.o
	$(CXX) $(CXXFLAGS) $*.o $(LIBS) -o $*
	./$* -q
	-rm -f $*

%.s: %.cpp
	$(CXX) $(CXXFLAGS) -O4 -S -pto $<  -o $@

clean:
	-rm -fr ${TEST_EXE} *.o *.rpo *.obj *.out core *~ Templates.DB
