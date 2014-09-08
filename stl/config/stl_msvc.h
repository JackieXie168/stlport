// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// Microsoft Visual C++ 4.0, 4.1, 4.2, 5.0

#  if ( _MSC_VER>=1000 )
// VC++ 4.0 and higher
#   define __STL_HAS_NAMESPACES         1
#   define __STL_NEW_STYLE_CASTS        1
#   define __STL_LONG_DOUBLE            1
#   define __STL_WCHAR_T                1
#   define __STL_WCHAR_T_IS_USHORT      1
#   define __STL_METHOD_SPECIALIZATION  1
#   define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#   define __STL_NO_QUALIFIED_FRIENDS    1

// <NBulteau@jouve.fr> : suppressed "truncated debug info" warning
#   pragma warning(disable:4786)

// <stdio> and the like still put stuff in ::namespace
// up to version 6 
#  define __STL_VENDOR_CSTD

#   if ( _MSC_VER<=1010 )
// "bool" is reserved in MSVC 4.1 while <yvals.h> absent, so :
#    define __STL_RESERVED_BOOL_KEYWORD 1
#    define __STL_USE_ABBREVS           1
#    define __STL_NO_BAD_ALLOC
#   else
// VC++ 4.2 and higher
#    define __STL_RESERVED_BOOL_KEYWORD 1
#    define __STL_YVALS_H 1
// by default, use new <iostream>
#    define __STL_USE_NEW_IOSTREAMS 1
#   endif /* 1010 */

#   if (_MSC_VER >= 1100)  // MSVC 5.0
#    define __STL_DEFAULT_TEMPLATE_PARAM 1
// these work, as long they are inline
#    define __STL_MEMBER_TEMPLATES 1
#    define __STL_MEMBER_TEMPLATE_CLASSES 1
#    define __STL_USE_NEW_STYLE_HEADERS 1
#    define __STL_TYPENAME      1
#    define __STL_EXPLICIT      1
#    define __STL_MUTABLE       1
#    define __STL_FULL_SPEC_SYNTAX 1
#   else
// up to 4.2, library is in global namespace
#    define __STL_VENDOR_STD
#    define __STL_NONTEMPL_BASE_MATCH_BUG 1
#    define __STL_BROKEN_USING_DIRECTIVE  1
#   endif /* 1100 */
#   if _MSC_VER >= 1200 /* VC++ 6.0 */
//  are there any differences ?
#   endif
#   define __SGI_STL_NO_ARROW_OPERATOR
#   define __STL_DEFAULT_CONSTRUCTOR_BUG 1
// these switches depend on compiler flags
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
// you should define _REENTRANT to turn these on
//#   if defined ( _MT ) && !defined (_NOTHREADS) && !defined (__STL_WIN32THREADS)
//#     define __STL_WIN32THREADS
//#   endif
#  endif /* 1000 */
