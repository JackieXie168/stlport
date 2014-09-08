// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// AS/400 C++ config

// #  define __STL_RESERVED_BOOL_KEYWORD 1 taken out in 3.12
#  define __STL_UNINITIALIZABLE_PRIVATE 1
#  define __STL_BASE_TYPEDEF_OUTSIDE_BUG 1
#  define __STL_STATIC_ARRAY_BUG 1
#  define __SGI_STL_NO_ARROW_OPERATOR 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#  define __STL_TRIVIAL_DESTRUCTOR_BUG  1
#  define __STL_USE_EXCEPTIONS 1
#  define __STL_NO_EXCEPTION_HEADER 1  // new for 3.12
#  define __STL_WCHAR_T 1
#  define __STL_NO_BAD_ALLOC 1         // new for 3.12
#  define __STL_NO_NEW_STYLE_HEADERS 1 // new for 3.12
#  define    __STL_NO_NEW_IOSTREAMS	1  // new for 3.12
#  if defined(_LONG_LONG)
#    define __STL_LONG_LONG 1
#  endif
#  define __STL_LONG_DOUBLE 1
#  if defined(_PTHREADS)
#    define _MULTI_THREADED
#  endif
// fbp : to fix __partition() problem
# define __STL_NONTEMPL_BASE_MATCH_BUG 1
