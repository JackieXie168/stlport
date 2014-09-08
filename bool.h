/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * Copyright (c) 1997
 * Silicon Graphics
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef __STL_BOOL_H
# define __STL_BOOL_H

// What this file does.
//  (1) Defines bool, true, and false if the compiler doesn't do so already.
//  (2) Defines __STL_NO_DRAND48 if the compiler's standard library does
//      not support the drand48() function.
//  (3) Defines __STL_STATIC_TEMPLATE_MEMBER_BUG if the compiler can't 
//      handle static members of template classes.
//  (4) Defines 'typename' as a null macro if the compiler does not support
//      the typename keyword.
//  (5) Defines __STL_CLASS_PARTIAL_SPECIALIZATION if the compiler 
//      supports partial specialization of template classes.
//  (6) Defines __STL_MEMBER_TEMPLATES if the compiler supports
//      template members of classes.
//  (7) Defines __STL_USE_EXCEPTIONS if the compiler (in the current
//      compilation mode) supports exceptions.
//  (8) Defines __STL_SGI_THREADS if this is being compiled on an SGI
//      compiler, and if the user hasn't selected pthreads or no threads
//      instead.
//  (9) Defines __STL_WIN32THREADS if this is being compiled on a 
//      WIN32 compiler in multithreaded mode.


# if defined(__sgi) && !defined(__GNUC__)
#   if !defined(_BOOL)
#     define __STL_NEED_BOOL
#   endif
#   if !defined(_TYPENAME)
#     define __STL_NEED_TYPENAME
#   endif
#   ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#     define __STL_CLASS_PARTIAL_SPECIALIZATION
#   endif
#   ifdef _MEMBER_TEMPLATES
#     define __STL_MEMBER_TEMPLATES
#   endif
#   ifdef __EXCEPTIONS
#     define __STL_USE_EXCEPTIONS
#   endif
#   if !defined(_NOTHREADS) && !defined(_PTHREADS)
#     define __STL_SGI_THREADS
#   endif
# endif
# ifdef __GNUC__
#   if __GNUC__ == 2 && __GNUC_MINOR__ <= 7
#     define __STL_STATIC_TEMPLATE_MEMBER_BUG
#   endif
#   if __GNUC__ < 2 
#     define __STL_NEED_TYPENAME
#   endif
#   if __GNUC == 2 && __GNUC_MINOR >= 8
#     define __STL_CLASS_PARTIAL_SPECIALIZATION
#   endif
# endif
# if defined(__SUNPRO_CC) 
#   define __STL_NEED_BOOL
#   define __STL_NEED_TYPENAME
#   define __STL_USE_EXCEPTIONS
# endif
# if defined(_MSC_VER)
#   if _MSC_VER > 1000
#     include <yvals.h>
#   else
#     define __STL_NEED_BOOL
#   endif
#   define __STL_NO_DRAND48
#   define __STL_NEED_TYPENAME
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
#   ifdef _MT
#     define __STL_WIN32THREADS
#   endif
# endif
# if defined(__BORLANDC__)
#   define __STL_NO_DRAND48
#   define __STL_NEED_TYPENAME
#   ifdef _CPPUNWIND
#     define __STL_USE_EXCEPTIONS
#   endif
#   ifdef __MT__
#     define __STL_WIN32THREADS
#   endif
# endif


# if defined(__STL_NEED_BOOL)
    typedef int bool;
#   define true 1
#   define false 0
#   undef __STL_NEED_BOOL
# endif

# ifdef __STL_NEED_TYPENAME
#   define typename
#   undef __STL_NEED_TYPENAME
# endif

#endif /* __STL_BOOL_H */
