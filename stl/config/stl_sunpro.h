// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#  define __STL_USE_EXCEPTIONS     1
#  define __STL_LONG_LONG  1
#  define __STL_WCHAR_T  1
#  define __STL_RAND48 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#  define __STL_STATIC_ARRAY_BUG 1
#  define __STL_NONTEMPL_BASE_MATCH_BUG 1

#  if ( __SUNPRO_CC >= 0x500 )
#  define __STL_DEFAULT_TEMPLATE_PARAM 1
#  define __STL_USE_NEW_IOSTREAMS 1
// <limits> bug in CC
// #  define __STL_USE_NEW_STYLE_HEADERS 1
#  define __STL_BOOL_KEYWORD 1
#  define __STL_HAS_NAMESPACES 1
#  define __STL_TYPENAME 1
#  define __STL_EXPLICIT 1
#  define __STL_MUTABLE  1
#  define __STL_FULL_SPEC_SYNTAX 1
#  define __STL_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS
#  else /* not 5.0 */
// common SunPro features
#  define __STL_NO_EXCEPTION_HEADER 1
#  define __STL_NO_BAD_ALLOC 1
#  define __STL_UNINITIALIZABLE_PRIVATE 1
#  define __STL_NO_BAD_ALLOC 1
#  define __SGI_STL_NO_ARROW_OPERATOR 1
#  define __STL_DEFAULT_CONSTRUCTOR_BUG 1

#  if ( __SUNPRO_CC > 0x401 )
#   if (__SUNPRO_CC==0x410)
#    define __STL_BASE_TYPEDEF_OUTSIDE_BUG  1
#   endif
#  else
   // SUNPro C++ 4.0.1
#   define __STL_BASE_MATCH_BUG          1
#   define __STL_BASE_TYPEDEF_BUG        1
#     if ( __SUNPRO_CC < 0x401 )
        __GIVE_UP_WITH_STL(SUNPRO_401)
#     endif
#  endif /* 4.0.1 */
#  endif /* not 5.0 */

#   if ( __SUNPRO_CC >= 0x420 )
#    define __STL_FULL_SPEC_SYNTAX 1
#    define __STL_NEW_STYLE_CASTS 1
#    define __STL_METHOD_SPECIALIZATION 1
#   endif
