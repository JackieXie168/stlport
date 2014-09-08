// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// AIX xlC 3.1 , 3.0.1 ==0x301
// Visual Age C++ 3.x
// OS-390 C++

#  define __STL_RESERVED_BOOL_KEYWORD 1
#  define __STL_UNINITIALIZABLE_PRIVATE 1
#  define __STL_BASE_TYPEDEF_OUTSIDE_BUG 1
#  define __STL_STATIC_ARRAY_BUG 1
#  define __STL_TRIVIAL_DESTRUCTOR_BUG  1  // AIX xlC, Visual Age 3.0 for OS/2 and MS 
#  if ( defined (__MULTI__) && defined (__WINDOWS__))
#   define  __STL_WIN32THREADS 1          // Only Visual Age 3.5 for Windows
#  endif
#  define __SGI_STL_NO_ARROW_OPERATOR 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#  define __STL_NO_EXCEPTION_HEADER 1
#  define __STL_NONTEMPL_BASE_MATCH_BUG 1
#  define __STL_NO_BAD_ALLOC
