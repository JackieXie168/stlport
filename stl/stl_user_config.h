/*
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/*
 * Purpose of this file :
 *
 * To hold user-definable portion of STLport settings.
 * If you use STLport in several projects, you may want
 * to place copy of this file modified for each project
 * in project include directory, so that you have different
 * settings for different projects.
 *
 */

// User-settable macros that control compilation:
// * __STL_USE_SGI_ALLOCATORS: if defined, then the STL will use older
//   SGI-style allocators, instead of standard-conforming allocators,
//   even if the compiler supports all of the language features needed
//   for standard-conforming allocators.
// * __STL_NO_NAMESPACES: if defined, don't put the library in namespace
//   std, even if the compiler supports namespaces.
// * __STL_NO_RELOPS_NAMESPACE: if defined, don't put the relational
//   operator templates (>, <=. >=, !=) in namespace std::rel_ops, even
//   if the compiler supports namespaces and partial ordering of
//   function templates.
// * __STL_ASSERTIONS: if defined, then enable runtime checking through the
//   __stl_assert macro.
// * _PTHREADS: if defined, use Posix threads for multithreading support.
// * _NOTHREADS: if defined, don't use any multithreading support.  
// * __STL_USE_NEW_IOSTREAMS: if defined, then the STL will use new,
//   standard-conforming iostreams (e.g. the <iosfwd> header).  If not
//   defined, the STL will use old cfront-style iostreams (e.g. the
//   <iostream.h> header).


//==========================================================
//              Features selection
//==========================================================

/* 
 * Uncomment to suppress using new-style streams even if they are
 * available.
 * Beware - __STL_USE_OWN_NAMESPACE depends on this macro, too.
 * Do that only if you are absolutely sure backwards-compatible 
 * <iostream.h> is not actually a wrapper with <iostream>
 * Hint : In VC++ 5.x, they are not.
 */

// #define   __STL_NO_NEW_IOSTREAMS	1

/*
 * __STL_STD_REBUILD - define this if you are actually rebuilding
 * vendor's C++ support library with STLport installed.
 */
// # define __STL_STD_REBUILD 1

/* 
 * __STL_USE_OWN_NAMESPACE/__STL_NO_OWN_NAMESPACE
 * If defined, STLport uses STLport:: namespace, else std::
 * Defining this helps A LOT in resolving problems with 
 * vendor C++ standard library interaction. 
 * The reason you have to use separate namespace is that new-style IO
 * compiled library may have its own idea about STL stuff (string, vector, etc.),
 * so redefining them in the same namespace would break ODR and may cause
 * undefined behaviour. Rule of thumb is - if new-style iostreams are
 * available, there could be a conflict. Otherwise you should be OK.
 * This flag is going to be defined in stl_config.h if __STL_USE_NEW_IOSTREAMS is on.
 * But you may wish to force it anyway.
 * Alternatively, you may want to disable it setting __STL_NO_OWN_NAMESPACE on.
 */
// #  define __STL_USE_OWN_NAMESPACE  1
// #  define __STL_NO_OWN_NAMESPACE  1


/* 
 * __STLPORT_NAMESPACE : This is the namespace STLport uses. 
 * Do NOT try to change it to "std".
 * In case you defined __STL_USE_OWN_NAMESPACE, STLport reside there.
 * If you put STLport in std:: (__STL_NO_OWN_NAMESPACE), stlport::
 * namespace is still available and is equivalent to std::
 * STLport also defines user-level macro STLPORT (=__STLPORT_NAMESPACE)
 * which is intended to be used in application's code for portability.
 */

#  define __STLPORT_NAMESPACE stlport

/* 
 * __STL_USE_SGI_STRING : Forces use of SGI string even if
 * native <string> is available. Unless you defined __STL_USE_OWN_NAMESPACE,
 * STLport uses native <string> if new iostreams are being used, 
 * as part of compiled runtime library depends on it.
 * You may force use of SGI string uncommenting this macro.
 * IMPORTANT:
 * DO NOT use SGI <string> with native <iostream> unless you recompile 
 * standard C++ runtime library with STLport installed, or
 * (better) defined __STL_USE_OWN_NAMESPACE
 */

// #define  __STL_USE_SGI_STRING  1


/* 
 * Edit relative path below (or put full path) to get native 
 * compiler vendor's headers included. Default is "../include"
 * Hint : never install STLport in the directory that ends with "include"
 */
// #  define __STL_NATIVE_INCLUDE_PATH ../include

/* 
 * Set __STL_DEBUG to turn the "Debug Mode" on.
 * That gets you checked iterators/ranges in the manner
 * of "Safe STL". Very useful for debugging. Thread-safe.
 */
// #define   __STL_DEBUG 1

/* Uncomment this to use the system-defined assert instead of fprintf to stderr */
// #define   __STL_USE_SYSTEM_ASSERT 1

/*
 * Uncomment this to force all failed assertions to be directed through a
 * user-defined global function:
 *	void __stl_debug_message(const char * format_str, ...). This allows
 * you to take control of assertions for debugging purposes.
 */
//#define __STL_DEBUG_MESSAGE 1

/* 
 * Uncomment that to disable exception handling code 
 */
// #define   __STL_NO_EXCEPTIONS 1

/*
 * __STL_NO_NAMESPACES: if defined, don't put the library in namespace
 * stlport:: or std::, even if the compiler supports namespaces
 */

// #define   __STL_NO_NAMESPACES 1

/* 
 * __STL_NO_RELOPS_NAMESPACE: if defined, don't put the relational
 * operator templates (>, <=. >=, !=) in namespace std::rel_ops, even
 * if the compiler supports namespaces and partial ordering of
 * function templates.
 */

// #define __STL_NO_RELOPS_NAMESPACE 1

/* _REENTRANT: define this if your project is multithreaded.
 * STLport uses MT-safe allocator support then. 
*/ 
// #define _REENTRANT

/* 
 * _NOTHREADS: if defined, STLport don't use any 
 * multithreading support.
 */
// #define _NOTHREADS

/*
 * __STL_NO_NEW_STYLE_HEADERS:  if defined, STLport does not 
 * use new-style headers : <cstdlib>, etc. 
 */
// #define   __STL_NO_NEW_STYLE_HEADERS 1

/*
 * __STL_USE_SGI_ALLOCATORS: if defined, then the STL will use older
 * SGI-style allocators, instead of standard-conforming allocator<T>.
 * Note : defining that would decrease portability of your code
 */
// #define   __STL_USE_SGI_ALLOCATORS 1

/* 
 * Uncomment __STL_USE_NEWALLOC to force allocator<T> to use plain "new"
 * instead of SGI optimized node allocator engine.
 */
// #define   __STL_USE_NEWALLOC   1

/* 
 * Uncomment __STL_USE_MALLOC to force allocator<T> to use plain "malloc" 
 * instead of SGI optimized node allocator engine.
 */
// #define   __STL_USE_MALLOC 1

/*
 * Set __STL_DEBUG_ALLOC to use allocators that perform memory debugging,
 * such as padding/checking for memory consistency 
 */
// #define   __STL_DEBUG_ALLOC 1

/*
 * Uncomment and provide a definition for the byte with which raw memory
 * will be filled if __STL_DEBUG_ALLOC is defined. Choose a value which
 * is likely to cause a noticeable problem if dereferenced or otherwise
 * abused. A good value may already be defined for your platform; see
 * stldebug.h
 */
// #define __STL_SHRED_BYTE 0xFF




//==========================================================
// Compatibility section
//==========================================================

/* 
 * This definition makes SGI reverse_iterator to be compatible with
 * other parts of MSVC library. (With partial specialization, it just
 * has no effect).
 * Its use is strongly discouraged - for MSVC5.0 configuration, it is being
 * set automatically. 
 */
// #    define __STL_MSVC50_COMPATIBILITY 1

/* 
 * Use abbreviated class names for linker benefit (don't affect interface).
 * This option is obsolete, but should work in this release.
 *
 */
// # define __STL_USE_ABBREVS

//==========================================================
