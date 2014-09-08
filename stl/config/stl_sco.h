// SCO UDK 7 compiler (UnixWare 7x, OSR 5, UnixWare 2x)
// # if defined(__USLC__)
#     define __STL_BOOL_KEYWORD 1
#     define __STL_HAS_WCHAR_T 
#     define __STL_CLASS_PARTIAL_SPECIALIZATION
#     define __STL_PARTIAL_SPECIALIZATION_SYNTAX
#     define __STL_FUNCTION_TMPL_PARTIAL_ORDER
#     define __STL_MEMBER_TEMPLATES
// #     define __STL_MEMBER_TEMPLATE_CLASSES
#     define __STL_USE_EXCEPTIONS
#     define __STL_HAS_NAMESPACES
#     define __STL_USE_NAMESPACES
#     define __STL_LONG_LONG

#     if defined(_REENTRANT)
#           define _UITHREADS     /* if      UnixWare < 7.0.1 */
#           define __STL_UITHREADS

//   use the following defines instead of the UI threads defines when
//   you want to use POSIX threads
//#         define _PTHREADS      /* only if UnixWare >=7.0.1 */
//#         define __STL_PTHREADS

#     endif /* _REENTRANT */

//   use the following define when your UDK 7 compiler has some poblems
//   with the generalized _Alloc_traits::allocator_type declaration
//   (due to rebind weirdness) in stl_alloc.h 
//#     define __UDK7_REBIND_WORKAROUND

// # endif
