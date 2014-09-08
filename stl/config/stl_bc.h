// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#  define __STL_NEW_STYLE_CASTS 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#  define __STL_DEFAULT_CONSTRUCTOR_BUG 1
#  if ( __BORLANDC__ < 0x501 )
#   define  __STL_NONTEMPL_BASE_MATCH_BUG 1
#  endif
#  if ( __BORLANDC__ < 0x500 )
#   define __STL_NESTED_TYPE_PARAM_BUG 1
#   define __STL_STATIC_ARRAY_BUG 1
#   define __STL_NO_BAD_ALLOC
#  else
#   define __STL_BOOL_KEYWORD 1
#   define __STL_DEFAULT_TYPE_PARAM 1
#   define __STL_HAS_NAMESPACES 1
#   define __STL_BROKEN_USING_DIRECTIVE 1
#   define __STL_EXPLICIT   1
#   define __STL_TYPENAME   1
#   define __STL_LONG_DOUBLE 1
#   define __STL_MUTABLE 1
#   define __STL_WCHAR_T 1
#  endif
#  define __STL_LOOP_INLINE_PROBLEMS 1

//auto enable thread safety and exceptions:
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif

#   if defined ( __MT__ ) && !defined (_NOTHREADS) && !defined (_REENTRANT)
#     define _REENTRANT 1
#   endif

#  if defined ( __DEBUG ) &&( __DEBUG > 0 )
#   define __STL_DEBUG
#  endif
// Stop complaints about functions not inlined
#  pragma option -w-inl
// Stop complaints about significant digits
#  pragma option -w-sig
// Stop complaint about constant being long
#  pragma option -w-cln
#  define __STL_METHOD_SPECIALIZATION
