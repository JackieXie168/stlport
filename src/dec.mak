#
# Basename for libraries
#
LIB_BASENAME = libstlport_dec

# point this to proper location
STL_INCL= -I. -I../stlport -I/usr/include

#
# guts for common stuff
#
#
CC = cxx
CXX = cxx

LINK=$(CXX)
DYN_LINK=$(CXX)

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=DEC

# LINK_OUT=-xar -o  
# DYNLINK_OUT=-o 

all: all_dynamic all_static

include common_macros.mak

# Rules

MTFLAGS = -pthread

CXXFLAGS_COMMON = -std strict_ansi -protect_headers none -tall_repository -rtti $(MTFLAGS) ${STL_INCL} -D_PTHREADS -D__STL_LONG_LONG -D__SGI_STL_OWN_IOSTREAMS

SHCXXFLAGS = -shared
# DEBUG_FLAGS = -g

LIBS = 

# RELEASE_static_rep = -ptr${RELEASE_OBJDIR_static}
# RELEASE_dynamic_rep = -ptr${RELEASE_OBJDIR_dynamic}
# DEBUG_static_rep = -ptr${DEBUG_OBJDIR_static}
# DEBUG_dynamic_rep = -ptr${DEBUG_OBJDIR_dynamic}
# STLDEBUG_static_rep = -ptr${STLDEBUG_OBJDIR_static}
# STLDEBUG_dynamic_rep = -ptr${STLDEBUG_OBJDIR_dynamic}

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) ${RELEASE_FLAGS} ${RELEASE_static_rep}
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) ${RELEASE_FLAGS} $(SHCXXFLAGS) ${RELEASE_dynamic_rep}

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -g ${DEBUG_static_rep}
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -g $(SHCXXFLAGS) ${DEBUG_dynamic_rep}

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_COMMON) -g ${STLDEBUG_static_rep} -D__STL_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_COMMON) -g $(SHCXXFLAGS) ${STLDEBUG_dynamic_rep} -D__STL_DEBUG

LDFLAGS_RELEASE_static = ${CXXFLAGS_RELEASE_static}
LDFLAGS_RELEASE_dynamic = ${CXXFLAGS_RELEASE_dynamic}

LDFLAGS_DEBUG_static = ${CXXFLAGS_DEBUG_static}
LDFLAGS_DEBUG_dynamic = ${CXXFLAGS_DEBUG_dynamic}

LDFLAGS_STLDEBUG_static = ${CXXFLAGS_STLDEBUG_static}
LDFLAGS_STLDEBUG_dynamic = ${CXXFLAGS_STLDEBUG_dynamic}

include common_percent_rules.mak
include common_rules.mak


%.i : %.cpp
	$(CXX) $(CXXFLAGS) $*.cpp -v -E > $@

%.s: %.cpp
	$(CXX) $(CXXFLAGS) -O4 -S -pto $<  -o $@

