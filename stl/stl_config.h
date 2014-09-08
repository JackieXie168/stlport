/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
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

#ifndef __STL_CONFIG_H
# define __STL_CONFIG_H

/*
 * Purpose of this file :
 *
 * Defines all STLport settings.
 * This file is actually a wrapper : it includes compiler-specific
 * settings from <config/stlcomp.h> (<config/stlconf.h>, if you ran "configure),
 * and user-defined settings from <stl_user_config.h>.
 * See <config/stl_mycomp.h> and <stl_user_config.h> for the description
 * of those macros
 * 
 */
// Other macros defined by this file:

// * bool, true, and false, if __STL_NO_BOOL is defined.
// * typename, as a null macro if it's not already a keyword.
// * explicit, as a null macro if it's not already a keyword.
// * namespace-related macros (__STD, __STL_BEGIN_NAMESPACE, etc.)
// * exception-related macros (__STL_TRY, __STL_UNWIND, etc.)
// * __stl_assert, either as a test or as a null macro, depending on
//   whether or not __STL_ASSERTIONS is defined.

// SGI basic release
#   define __SGI_STL                                      0x312
// Adaptation version
#   define __SGI_STL_PORT                                 0x312

// First, attempt to include config file produced by "configure"
# include <config/stlconf.h>

# if defined (__AUTO_CONFIGURED)
// auto-configured, some adjustments to be sure

// Microsoft Visual C++ 4.0, 4.1, 4.2, 5.0
// distinguish real MSC
#  if defined(_MSC_VER) && !defined(__MWERKS__)
#   define __STL_MSVC _MSC_VER
#  endif

# else

// Not configured, use per-version compiler recognition
#  include <config/stlcomp.h>

# endif


//=========================================================

// some fixes to configuration, either "configure"d or
// hardcoded. This also includes modifications
// of STLport switches depending on compiler flags 

# include <config/stl_confix.h>

//=========================================================


// Placeholder for user to override settings.
// It could be also used to mask settings from 
// different directories

# include <stl_user_config.h>

//=========================================================


//==========================================================
// final workaround tuning based on given flags
//==========================================================

#ifndef __STL_UINT32_T
# define __STL_UINT32_T unsigned long
#endif

# if defined (__STL_HAS_NAMESPACES)
// undef only "USE"
# if defined __STL_NO_NAMESPACES
#  undef __STL_USE_NAMESPACES
# else
// assume it as the default, turn it off later if NO_NAMESPACES selected
#  undef __STL_USE_NAMESPACES
#  define __STL_USE_NAMESPACES 1
# endif
# endif

# ifndef __STLPORT_NAMESPACE
#  define __STLPORT_NAMESPACE stlport
# endif

# if defined (__STL_NO_NEW_IOSTREAMS)
#  undef __STL_USE_NEW_IOSTREAMS
# endif

# if defined (__STL_USE_NEW_IOSTREAMS) &&  \
    defined (__STL_USE_NAMESPACES) && !defined (__STL_BROKEN_USING_DIRECTIVE) && \
    !defined(__STL_STD_REBUILD) && !defined(__STL_NO_OWN_NAMESPACE)
#  undef  __STL_USE_OWN_NAMESPACE
#  define __STL_USE_OWN_NAMESPACE  1
# endif

# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __STL_PTHREADS
# endif

# if defined(_UITHREADS) && !defined(_NOTHREADS)
#     define __STL_UITHREADS
# endif

# ifdef _REENTRANT
# if !defined(_NOTHREADS) && !defined(_PTHREADS)
# if defined (__sgi)
#  define __STL_SGI_THREADS
# elif defined (__sun) && defined (__SVR4)
#  define __STL_SOLARIS_THREADS
# elif defined(_UITHREADS) && !defined(_NOTHREADS)
#     define __STL_UITHREADS
# elif defined (_WIN32) || defined (WIN32)
#  define __STL_WIN32THREADS
# else
#   define __STL_PTHREADS
# endif /* __sgi */
# endif /* _NOTHREADS */
# endif /* _REENTRANT */


#if defined(__STL_WIN32THREADS) || defined(STL_SGI_THREADS) \
    || defined(__STL_PTHREADS) || defined(__STL_SOLARIS_THREADS) || defined(__STL_UITHREADS)
#   define __STL_THREADS
#   define __STL_VOLATILE volatile
// windows.h _MUST be included before bool definition ;(
# if defined  (__STL_WIN32THREADS)
#   define NOMINMAX
#   include <windows.h>
#   undef min
#   undef max
# endif
#else
#   define __STL_VOLATILE
#endif

// disable new-style headers if requested
# if defined ( __STL_NO_NEW_STYLE_HEADERS )
#  undef __STL_USE_NEW_STYLE_HEADERS
# endif

# if defined ( __STL_NO_STATIC_TEMPLATE_DATA )
#   define __STL_STATIC_TEMPLATE_DATA 0
#   if !defined ( __STL_WEAK_ATTRIBUTE )
#    define __STL_WEAK_ATTRIBUTE 0
#   endif
# else
#   define __STL_STATIC_TEMPLATE_DATA 1
# endif

# if defined (__STL_BASE_TYPEDEF_BUG)
#  undef  __STL_BASE_TYPEDEF_OUTSIDE_BUG
#  define __STL_BASE_TYPEDEF_OUTSIDE_BUG 1
# endif

// comment this section if you want to use BufSize parameter
// of deque (note that no template function taking deque<T,Alloc,BufSize>
// as parameter will compile then)
# if defined (__STL_NON_TYPE_TMPL_PARAM_BUG)
#  undef  __STL_NO_DEFAULT_NON_TYPE_PARAM
#  define __STL_NO_DEFAULT_NON_TYPE_PARAM 1
# endif

# define __STL_NEW new
# define __STL_PLACEMENT_NEW new

// features tuning 
# ifdef __STL_DEBUG
#  define __STL_ASSERTIONS 1
# endif

# if !defined( __STL_DEBUG_MESSAGE )
#   define __stl_debug_message __STD::__stl_debug_engine<bool>::_Message
# else
    extern  void __stl_debug_message(const char * format_str, ...);
# endif

# ifndef __STL_DEBUG_MESSAGE_POST
#  define __STL_DEBUG_MESSAGE_POST
# endif

# ifndef __STL_ASSERT_MSG_TRAILER
#  define __STL_ASSERT_MSG_TRAILER
# endif

# if !defined(__STL_FILE__)
#   define __STL_FILE__ __FILE__
# endif
 
# ifdef __STL_ASSERTIONS 
#  if defined(_MFC_VER)
#    define __stl_assert(expr) \
      do { \
      if (!(expr)) \
      { \
      TRACE(_T("%s:%d STL assertion failure : %s\n"), __FILE__, __LINE__, # expr ); \
      ASSERT(0); \
      } \
      } while (0)
#  else	/* !_MFC_VER */
#   define __stl_assert(expr) \
     do { if (!(expr)) { __stl_debug_message("\n%s:%d STL assertion failure: %s\n" \
     __STL_ASSERT_MSG_TRAILER, \
      __STL_FILE__, __LINE__, # expr); } } while (0)
#  endif	/* !_MFC_VER */
# else
#  define __stl_assert(expr) do {} while(0)	// dwa 3/19/99 - prevents 'unwanted ;' warning
# endif

# ifdef __STL_DEBUG
    #if defined(_MFC_VER)
    #define __stl_verbose_assert(expr,diagnostic) \
    do { \
    if (!(expr)) \
    { \
    TRACE(_T("%s:%d STL error : %s\n%s:%d STL assertion failure : %s\n"), __FILE__, __LINE__, diagnostic, __FILE__, __LINE__, # expr ); \
    ASSERT(0); \
    } \
    } while (0)
    #else	// !_MFC_VER
    #  define __stl_verbose_assert(expr,diagnostic) \
    do { if (!(expr)) { __stl_debug_message("\n%s:%d STL error : %s\n"\
         "%s:%d STL assertion failure:     %s \n" __STL_ASSERT_MSG_TRAILER,\
     __STL_FILE__, __LINE__ , diagnostic, __STL_FILE__, __LINE__ , # expr ); } } while(0)
    #endif	// !_MFC_VER
#  define __stl_debug_check(expr) __stl_assert(expr)
#  define __stl_debug_do(expr) expr
# else
#  define __stl_verbose_assert(expr,diagnostic)
#  define __stl_debug_check(expr)
#  define __stl_debug_do(expr)
# endif

// tuning of static template data members workaround
# if ( __STL_STATIC_TEMPLATE_DATA < 1 )
// ignore __PUT directive in this case
#  if ( __STL_WEAK_ATTRIBUTE > 0 )
#   define __STL_WEAK __attribute__ (( weak ))
#   define __DECLARE_INSTANCE(type,item,init) type item __attribute__ (( weak )) init
#  else
#   define __STL_WEAK 
#   ifdef __PUT_STATIC_DATA_MEMBERS_HERE
#    define __DECLARE_INSTANCE(type,item,init) type item init
#   else
#    define __DECLARE_INSTANCE(type,item,init)
#   endif /* __PUT_STATIC_DATA_MEMBERS_HERE */
#  endif /* __STL_WEAK_ATTRIBUTE */
# endif /* __STL_STATIC_TEMPLATE_DATA */


// default parameters as template types derived from arguments ( not always supported )
#  if ! defined (__STL_DEFAULT_TEMPLATE_PARAM)
#   define __DFL_TMPL_PARAM( classname, defval ) class classname
#   define __DFL_TMPL_ARG(classname) , classname
#  else
#   define __STL_DEFAULT_TYPE_PARAM 1
#   define __DFL_TMPL_PARAM( classname, defval ) class classname = defval
#   define __DFL_TMPL_ARG(classname)  
#  endif

// default parameters as complete types
# if defined ( __STL_DEFAULT_TYPE_PARAM )
#   define __DFL_TYPE_PARAM( classname, defval ) class classname = defval
#   define __DFL_NON_TYPE_PARAM(type,name,val) type name = val
#   define __DFL_TYPE_ARG(classname)
# else
#   define __DFL_TYPE_PARAM( classname, defval ) class classname
#   define __DFL_NON_TYPE_PARAM(type,name,val) type name
#   define __DFL_TYPE_ARG(classname) , classname
# endif

// SGI compatibility
#  if ! defined (__STL_DEFAULT_TEMPLATE_PARAM)
#   define __STL_LIMITED_DEFAULT_TEMPLATES
#  endif

#if !defined (__STL_NO_AT_MEMBER_FUNCTION)
# define __STL_CAN_THROW_RANGE_ERRORS 1
#endif

// __STL_USE_SGI_ALLOCATORS is a hook so that users can 
// disable new-style allocators, and continue to use the same kind of
// allocators as before, without having to edit library headers.

# ifdef __STL_USE_SGI_ALLOCATORS
#   define __STL_DEFAULT_ALLOCATOR(T) alloc
#   define __STL_DEFAULT_ALLOCATOR_SELECT(T) __DFL_TYPE_PARAM(_Alloc,alloc)
#   if !(defined (__STL_DEFAULT_TYPE_PARAM) || defined (__STL_DEFAULT_TEMPLATE_PARAM))
#    define __STL_USE_WRAPPER_FOR_ALLOC_PARAM 1
#   endif
# else
#   define __STL_DEFAULT_ALLOCATOR(T) allocator<T>
#   define __STL_DEFAULT_ALLOCATOR_SELECT(T) __DFL_TMPL_PARAM(_Alloc,allocator<T>)
#   if !defined (__STL_DEFAULT_TEMPLATE_PARAM)
#     define __STL_USE_WRAPPER_FOR_ALLOC_PARAM 1
#   endif
# endif

// default parameters workaround tuning
#  if defined  ( __STL_USE_WRAPPER_FOR_ALLOC_PARAM ) 
#    define __WORKAROUND_RENAME(X) __##X
#  else
#    define __WORKAROUND_RENAME(X) X
#  endif

#  define __FULL_NAME(X) __WORKAROUND_RENAME(X)

// Use truly standard-conforming allocators if we have the necessary language
// features.
// __STL_INSTANCELESS_ALLOCATORS - ensure all allocators used are instanceless,
// thus we could avoid using complex constructs in base classes
  
# if defined(__STL_CLASS_PARTIAL_SPECIALIZATION) && \
     defined(__STL_MEMBER_TEMPLATES) && \
     defined(__STL_MEMBER_TEMPLATE_CLASSES) && \
     defined(__STL_BOOL_KEYWORD) && \
    !defined(__STL_NON_TYPE_TMPL_PARAM_BUG) && \
    !defined(__STL_LIMITED_DEFAULT_TEMPLATES) && \
    !defined(__STL_USE_SGI_ALLOCATORS) && \
    !defined(__STL_INSTANCELESS_ALLOCATORS) 
#   define __STL_USE_STD_ALLOCATORS
# endif

# if defined(__STL_USE_STD_ALLOCATORS) && defined(__STL_NO_TEMPLATE_CONVERSIONS)
#  define __STL_CONVERT_ALLOCATOR(a, T) __STL_DEFAULT_ALLOCATOR(T)()
# else
#  define __STL_CONVERT_ALLOCATOR(a, T) a
# endif

//# ifndef __STL_NESTED_TYPE_PARAM_BUG
# if defined (__STL_USE_STD_ALLOCATORS)
#  define __STL_ALLOC_PARAM allocator_type
# else
#  define __STL_ALLOC_PARAM _Alloc
# endif

// parameters passed to container's constructors.
// some compilers choke on default parameters 
// given as a constructor name
# if defined (__STL_DEFAULT_PARAM_CONSTRUCTOR_BUG)
#  define __STL_ALLOC_INSTANCE(_X) _STL_factory<_X>::_Instance()
# else
#  define __STL_ALLOC_INSTANCE(_X) _X()
# endif

#  define __STL_DEFAULT_ALLOC_PARAM , const __STL_ALLOC_PARAM& __a = __STL_ALLOC_PARAM


// namespace stuff adjustment

// Depending of whether compiler supports namespaces,
// tune the parameters for vendor-supplied libraries
# if defined (__STL_HAS_NAMESPACES)

// assume std:: namespace for C++ std library if not being told otherwise
#  ifndef __STL_VENDOR_STD
#   define __STL_VENDOR_STD std
#  endif

// tune things that come from C library
#  ifndef __STL_VENDOR_CSTD
#   ifdef __STL_USE_NEW_STYLE_HEADERS
#    define __STL_VENDOR_CSTD  __STL_VENDOR_STD
#   else
//  in old-style headers, C functions go to global scope.
#    define __STL_VENDOR_CSTD
#   endif
#  endif /* __STL_VENDOR_CSTD */

// if using stlport:: namespace or if C library stuff is not in vendor's std::,
// import 'em.
#  if (defined(__STL_USE_OWN_NAMESPACE) || defined (__STL_VENDOR_CSTD))
#    define  __STL_IMPORT_VENDOR_CSTD 1
#  endif

# ifndef __STL_USING_BASE_MEMBER
#  define __STL_USING_BASE_MEMBER using
# endif

# else 
// compiler has no namespace support
#  define __STL_VENDOR_STD 
#  define __STL_VENDOR_CSTD
#  define __STL_USING_BASE_MEMBER
# endif


# if defined (__STL_USE_NAMESPACES)
#  if defined (__STL_USE_OWN_NAMESPACE)
#   define __STD __STLPORT_NAMESPACE
#  else
#   define  __STD std
// provide stlport:: as equivalent namespace for portability anyways
namespace std { }
namespace __STLPORT_NAMESPACE = __STD;
#  endif /* __STL_USE_OWN_NAMESPACE */

# ifdef __STL_NO_QUALIFIED_FRIENDS
#   define __STD_QUAL
# else
#   define __STD_QUAL __STD::
# endif

// SGI term
#  define __STD_QUALIFIER __STD_QUAL

#  define __STL_BEGIN_NAMESPACE namespace __STD {
#  define __STL_END_NAMESPACE }

#   define  __STL_USE_NAMESPACE_FOR_RELOPS

// decide whether or not we use separate namespace for rel ops
#   if defined(__STL_FUNCTION_TMPL_PARTIAL_ORDER) && \
       !defined(__STL_NO_RELOPS_NAMESPACE)
#     define __STD_RELOPS __STD::rel_ops
#     define __STL_BEGIN_RELOPS_NAMESPACE namespace __STD { namespace rel_ops {
#     define __STL_END_RELOPS_NAMESPACE } }
#   else /* Use std::rel_ops namespace */
#     define __STL_BEGIN_RELOPS_NAMESPACE namespace __STD { namespace rel_ops {}
#     define __STL_END_RELOPS_NAMESPACE }
#     define __STD_RELOPS __STD
#   endif /* Use std::rel_ops namespace */

# else /* __STL_USE_NAMESPACES */

// STLport is being put into global namespace
#  define __STD
#  define __STD_QUAL

#  define __STL_BEGIN_NAMESPACE
#  define __STL_END_NAMESPACE

#  undef  __STL_USE_NAMESPACE_FOR_RELOPS
#  define __STL_BEGIN_RELOPS_NAMESPACE 
#  define __STL_END_RELOPS_NAMESPACE 
#  define __STD_RELOPS 
// this one is contradiction, so turn it off
#  undef  __STL_USE_OWN_NAMESPACE

# endif  /* __STL_USE_NAMESPACES */

// user level defines for STLport stuff and C-related stuff.
# define STLPORT __STD
# define STLPORT_CSTD __STL_VENDOR_CSTD

#if defined(__STL_BOGUS_TEMPLATE_TYPE_MATCHING_BUG)
// MrCpp erratically matches rope<...> to _CharT if the parameter type of __right is _CharT in operator xx (rope<_CharT,_Alloc>& __left, _CharT __right)
template<class T>
class _stl_trivial_proxy
{
public:
       _stl_trivial_proxy(T _rhs):_M_data(_rhs) {}
       operator T() const { return _M_data; }
       _stl_trivial_proxy& operator= (T _rhs) { _M_data = _rhs; return this*;}
       T* operator&() { return &_M_data; }
       const T* operator& () const { return &_M_data; }
private:
       T       _M_data;
};

#  define __STL_SIMPLE_TYPE(T) _stl_trivial_proxy<T>
#else
#  define __STL_SIMPLE_TYPE(T) T
#endif


// if we are going to use new iostreams, <string> and <stdexcept> should be defined
# if defined (__STL_USE_NEW_IOSTREAMS)
#  if !defined (__STL_HAS_STRING_HEADER)
#    define __STL_HAS_STRING_HEADER    1
#  endif
#  if !defined (__STL_HAS_STDEXCEPT_HEADER)
#   define __STL_HAS_STDEXCEPT_HEADER 1
#  endif
#  if !defined(__STL_STD_REBUILD) \
      && !defined(__STL_CHAR_TRAITS_DEFINED)
#   define __STL_CHAR_TRAITS_DEFINED    1
#  endif
#  define  __STL_IOSTREAM_STD __STL_VENDOR_STD
#  define  __STL_IOS_STD __STL_VENDOR_STD
# else /* __STL_USE_NEW_IOSTREAMS */
#  define  __STL_IOSTREAM_STD
#  define  __STL_IOS_STD
# endif /* __STL_USE_NEW_IOSTREAMS */

#  if defined (__STL_HAS_STRING_HEADER) && \
     !defined (__STL_USE_SGI_STRING)
#  define __STL_USE_NATIVE_STRING      1
# endif

#  if defined (__STL_HAS_STDEXCEPT_HEADER) && \
     !defined (__STL_USE_SGI_STRING)
#   define __STL_USE_NATIVE_STDEXCEPT
#  endif

# if defined(__STL_MSVC) && defined (__STL_USE_NEW_IOSTREAMS) && \
     !defined (__STL_USE_OWN_NAMESPACE) && defined (__STL_USE_SGI_STRING)
#   if !defined (CRTDLL2)
#    error "You have to #define CRTDLL2, and to link dynamically to work with <iostream> and SGI <string>, or to #define __STL_OWN_NAMESPACE. Read README.VC++"
#   endif /* CRTDLL2 */
# endif /* __STL_MSVC */

# ifndef __STL_RAND48
# define __STL_NO_DRAND48
# endif

// some backwards compatibility

#define __BEGIN_STL_NAMESPACE __STL_BEGIN_NAMESPACE 
#define __END_STL_NAMESPACE __STL_END_NAMESPACE 
#define __STL_NAMESPACE __STD 

#  define __STL_NAME(name) __STD::name  // Lo Russo Graziano <Graziano.LoRusso@CSELT.IT>


// advanced keywords usage
#  ifdef  __STL_NEW_STYLE_CASTS
#   define __CONST_CAST(__x,__y) const_cast<__x>(__y)
#   define __STATIC_CAST(__x,__y) static_cast<__x>(__y)
#  else
#   define __STATIC_CAST(__x,__y) ((__x)__y)
#   define __CONST_CAST(__x,__y) ((__x)__y)
#  endif

#  ifndef __STL_TYPENAME
#   define typename
#  endif

#ifndef __STL_TYPENAME_ON_RETURN_TYPE
#  define __STL_TYPENAME_ON_RETURN_TYPE
#endif

# ifdef __STL_MEMBER_TEMPLATE_KEYWORD
#   define __STL_TEMPLATE template
# else
#   define __STL_TEMPLATE
# endif

#  ifndef __STL_EXPLICIT
#   define explicit
#  endif

#  ifdef __STL_MUTABLE
#   define __ASSIGN_MUTABLE(type,x,y) x=y
#  else
#   define __ASSIGN_MUTABLE(type,x,y) __CONST_CAST(type,x)=y
#   define mutable
#  endif

# if defined (__STL_NO_SIGNED_BUILTINS)
// old HP-UX don't understand "signed" keyword
#  define signed
# endif

#  if defined (__STL_LOOP_INLINE_PROBLEMS)
#   define INLINE_LOOP
#  else
#   define INLINE_LOOP inline 
#  endif

//#if defined ( __STL_UNINITIALIZABLE_PRIVATE )
#if 1
#  define __PRIVATE public
#  define __PROTECTED public
#else
#  define __PRIVATE private
#  define __PROTECTED protected
#endif

#  ifdef __STL_FULL_SPEC_SYNTAX
#   define __STL_FULL_SPECIALIZATION template<>
#  else
#   define __STL_FULL_SPECIALIZATION
#  endif

// SGI terms

# if ! defined (__STL_BOOL_KEYWORD)
#  define __STL_NO_BOOL 1
# else
#  undef __STL_NO_BOOL
# endif

# if defined (__STL_RESERVED_BOOL_KEYWORD)
#  define __STL_DONT_USE_BOOL_TYPEDEF 1
# endif

# if defined(__STL_WCHAR_T)
#  define __STL_HAS_WCHAR_T 1
# endif

# ifdef __STL_FULL_SPEC_SYNTAX
#  define __STL_PARTIAL_SPECIALIZATION_SYNTAX 1
# endif
# define __STL_TEMPLATE_NULL __STL_FULL_SPECIALIZATION

# ifdef __STL_FUNC_PARTIAL_ORDERING
#  define __STL_FUNCTION_TMPL_PARTIAL_ORDER
# endif

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#   define __STL_NULL_TMPL_ARGS <>
# else
#   define __STL_NULL_TMPL_ARGS
# endif

#  define __IMPORT_CONTAINER_TYPEDEFS(_Super)                            \
    typedef typename _Super::value_type value_type;                      \
    typedef typename _Super::size_type size_type;                        \
    typedef typename _Super::difference_type difference_type;            \
    typedef typename _Super::reference reference;                        \
    typedef typename _Super::const_reference const_reference;            \
    typedef typename _Super::pointer pointer;                            \
    typedef typename _Super::const_pointer const_pointer;


#  define __IMPORT_ITERATORS(_Super)                                     \
    typedef typename _Super::iterator iterator;                                   \
    typedef typename _Super::const_iterator const_iterator; 

#  define __IMPORT_REVERSE_ITERATORS(_Super)                             \
    typedef typename _Super::const_reverse_iterator  const_reverse_iterator;      \
    typedef typename _Super::reverse_iterator reverse_iterator;

#define  __IMPORT_SUPER_COPY_ASSIGNMENT(__derived_name, _Self, _Super)         \
    __derived_name(const _Super& __x) : _Super(__x) {}          \
    _Self& operator=(const _Super& __x) {                       \
        *(_Super*)this = __x;                                   \
        return *this;                                           \
    }

# define __IMPORT_WITH_ITERATORS(_Super) \
__IMPORT_CONTAINER_TYPEDEFS(_Super) __IMPORT_ITERATORS(_Super)

# define __IMPORT_WITH_REVERSE_ITERATORS(_Super) \
__IMPORT_WITH_ITERATORS(_Super) __IMPORT_REVERSE_ITERATORS(_Super)


# if defined (__STL_TRIVIAL_CONSTRUCTOR_BUG) 
#  define __TRIVIAL_CONSTRUCTOR(__type) __type() {}  
# else
#  define __TRIVIAL_CONSTRUCTOR(__type)
# endif
# if defined (__STL_TRIVIAL_DESTRUCTOR_BUG)
#  define __TRIVIAL_DESTRUCTOR(__type) ~__type() {}  
# else
#  define __TRIVIAL_DESTRUCTOR(__type) 
# endif

#  define __TRIVIAL_STUFF(__type)  \
  __TRIVIAL_CONSTRUCTOR(__type) __TRIVIAL_DESTRUCTOR(__type)

# if defined ( __STL_NO_EXCEPTIONS )
#  undef __STL_USE_EXCEPTIONS
# endif 

# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_THROW(x) throw x
#   define __STL_RETHROW throw
#   define __STL_UNWIND(action) catch(...) { action; throw; }
#   if !defined ( __STL_NO_EXCEPTION_SPEC )
#    define __STL_THROWS(x) throw x
#    define __STL_NOTHROW throw()
#   else
#    define __STL_THROWS(x)
#    define __STL_NOTHROW 
#   endif
# else
#   define __STL_TRY 
#   define __STL_CATCH_ALL if (false)
#   define __STL_THROW(x) 
#   define __STL_RETHROW 
#   define __STL_UNWIND(action) 
#   define __STL_THROWS(x)
#   define __STL_NOTHROW 
# endif

# if defined (__IBMCPP__) && (__IBMCPP__ < 400)
#  include <isynonym.hpp>
# if defined (__OS400__) // rolandh
   typedef int bool;
# else
// if this fails, just remove the typedef
   typedef Boolean bool;
# endif
# else
#  if defined(__STL_YVALS_H)
#   include <yvals.h>
#  else
#   if ! defined(__STL_BOOL_KEYWORD)
#    if defined (__STL_RESERVED_BOOL_KEYWORD)
#     define bool int
#    else
      typedef int bool;
#    endif
#    define true 1
#    define false 0
#   endif /* __STL_BOOL_KEYWORD */
#  endif
# endif /* __IBMCPP__ */

#  ifdef __STL_MSVC
#   ifndef _CRTIMP
#    ifdef  _DLL
#     define _CRTIMP __declspec(dllimport)
#    else 
#     define _CRTIMP
#    endif 
#   endif
#  endif

# ifdef _CRTIMP
#  define __STLIMP _CRTIMP
# else
#  define __STLIMP
# endif 

// inclusion of vendor's library headers tuning,

# if !defined (__STL_NATIVE_INCLUDE_PATH)
#  define __STL_NATIVE_INCLUDE_PATH ../include
# endif

# if !defined (__STL_NATIVE_C_INCLUDE_PATH)
#  define __STL_NATIVE_C_INCLUDE_PATH __STL_NATIVE_INCLUDE_PATH
# endif

# if !defined(__STL_MAKE_HEADER)
#  define __STL_MAKE_HEADER(path, header) <path/header>
# endif

#ifndef __STL_C_HEADER
# define __STL_C_HEADER(header) __STL_C_HEADER_AUX(header)
#endif

#ifndef __STL_NATIVE_HEADER
# define __STL_NATIVE_HEADER(header) __STL_MAKE_HEADER(__STL_NATIVE_INCLUDE_PATH,header)
#endif

#ifndef __STL_NATIVE_C_HEADER
# define __STL_NATIVE_C_HEADER(header)  __STL_MAKE_HEADER(__STL_NATIVE_C_INCLUDE_PATH,header)
#endif

# ifndef __STL_DEBUG_MESSAGE
// dwa 12/30/98 - if __STL_DEBUG_MESSAGE is defined, the user can supply her own definition.
__STL_BEGIN_NAMESPACE
template <class _Dummy>
struct __stl_debug_engine {
  static void _Message(const char * format_str, ...);
};
__STL_END_NAMESPACE
# endif

# ifndef __STL_MPW_EXTRA_CONST
#  define __STL_MPW_EXTRA_CONST
# endif

# ifndef __STL_DEFAULTCHAR
#  define __STL_DEFAULTCHAR char
# endif

// some cleanup
# undef __STL_RESERVED_BOOL_KEYWORD
# undef __STL_YVALS_H
# undef __STL_LOOP_INLINE_PROBLEMS
# undef __STL_TYPENAME
# undef __STL_EXPLICIT
# undef __AUTO_CONFIGURED
# undef __STL_FULL_SPEC_SYNTAX

#endif /* __STL_CONFIG_H */
