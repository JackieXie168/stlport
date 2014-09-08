// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#   define __STL_BASE_TYPEDEF_OUTSIDE_BUG 1

// #   define __STL_USE_NEW_STYLE_HEADERS 1
#   define __STL_LONG_DOUBLE 1
#   define __STL_NO_DEFAULT_NON_TYPE_PARAM 1
#   define __STL_METHOD_SPECIALIZATION 1
#   define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#   define __STL_NONTEMPL_BASE_MATCH_BUG

#   define __STL_NO_BAD_ALLOC 1

// Get rid of Watcom's min and max macros 
#undef min 
#undef max

// for switches (-xs,  -xss,  -xst)
//
#if defined (__SW_XS) || defined (__SW_XSS) || defined(__SW_XST)
#    define __STL_USE_EXCEPTIONS 1
# endif

#  define __STL_NESTED_TYPE_PARAM_BUG 1

#  if (__WATCOM_CPLUSPLUS__ >= 1100 )
#   define __STL_BOOL_KEYWORD 1
#   define __STL_EXPLICIT 1
#   define __STL_MUTABLE 1
#   define __STL_NEW_STYLE_CASTS 1
#  endif
