// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// two levels of macros do not work good with icl.
#   define __STL_NATIVE_HEADER(header)    <../include/##header> 
#   define __STL_NATIVE_C_HEADER(header)    <../include/##header> 

// Intel compiler 4.0
#if (__ICL >= 400)

#   define __STL_HAS_NAMESPACES         1
#   define __STL_NEW_STYLE_CASTS        1
#   define __STL_LONG_LONG 1
#   define __STL_LONG_DOUBLE            1
#   define __STL_WCHAR_T                1
#   define __STL_WCHAR_T_IS_USHORT      1
#   define __STL_METHOD_SPECIALIZATION  1
#   define __STL_DEFAULT_CONSTRUCTOR_BUG 1

// #   define __STL_NO_QUALIFIED_FRIENDS    1


#   pragma warning(disable:4786)

// <stdio> and the like still put stuff in ::namespace
// up to version 6 
#    define __STL_VENDOR_CSTD
#    define __STL_USE_NEW_IOSTREAMS 1

#    define __STL_DEFAULT_TEMPLATE_PARAM 1
#    define __STL_MEMBER_TEMPLATES 1
#    define __STL_MEMBER_TEMPLATE_CLASSES 1
#    define __STL_FRIEND_TEMPLATES 1
#    define __STL_CLASS_PARTIAL_SPECIALIZATION 1
#    define __STL_FUNC_PARTIAL_ORDERING 1

#    define __STL_USE_NEW_STYLE_HEADERS 1
#    define __STL_TYPENAME      1
#    define __STL_EXPLICIT      1
#    define __STL_MUTABLE       1
#    define __STL_FULL_SPEC_SYNTAX 1

#   if ( _MSC_VER<=1020 )
#    define __STL_RESERVED_BOOL_KEYWORD 1
#    define __STL_NO_BAD_ALLOC
#    define __STL_YVALS_H 1
#   endif /* 1010 */

#   if (_MSC_VER >= 1100)  // MSVC 5.0
#    define __STL_BOOL_KEYWORD 1
#   else
#    define __STL_NO_BOOL
// up to 4.2, library is in global namespace
#    define __STL_VENDOR_STD
#   endif /* 1100 */

#   if _MSC_VER >= 1200 /* VC++ 6.0 */
#   else
#     define __STL_NON_TYPE_TMPL_PARAM_BUG 1 
#   endif

// these switches depend on compiler flags
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif

#   if defined ( _MT ) && !defined (_NOTHREADS) && !defined (_REENTRANT)
#     define _REENTRANT 1
#   endif

#else /* __ICL >=400 */
// this should work for older versions
# include <config/stl_msvc.h>
#endif /* __ICL >=400 */

