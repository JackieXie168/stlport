/*
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
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

#ifndef __SGI_STL_CHAR_TRAITS_H
#define __SGI_STL_CHAR_TRAITS_H

#if defined (__STL_USE_NEW_STYLE_HEADERS)
# include <cstddef> /* wchar_t */
# ifdef __STL_MSVC
#  include <cstdio>
# endif
# include <cstring>
#else
# include <string.h>
# if ! defined (__MRC__) && !defined (__SC__)
#   include <wchar.h>
# endif			
# include <stddef.h>							
#endif

#include <stl_function.h>


// Define char_traits
// If we import new iostreams from vendor library, just do it
#if defined (__STL_CHAR_TRAITS_DEFINED)
# include __STL_NATIVE_HEADER(iosfwd)
#  ifndef __STL_BROKEN_USING_DIRECTIVE
   __STL_BEGIN_NAMESPACE
   using __STL_VENDOR_STD::char_traits;
   __STL_END_NAMESPACE
#  endif
# else
__STL_BEGIN_NAMESPACE

// Class __char_traits_base.

template <class _CharT, class _IntT> struct __char_traits_base {
  typedef _CharT char_type;
  typedef _IntT int_type;
#ifdef __STL_USE_NEW_IOSTREAMS
  typedef streamoff off_type;
  typedef streampos pos_type;
  typedef mbstate_t state_type;
#endif /* __STL_USE_NEW_IOSTREAMS */

  static void assign(char_type& __c1, const char_type& __c2) { __c1 = __c2; }
  static bool eq(const _CharT& __c1, const _CharT& __c2) 
    { return __c1 == __c2; }
  static bool lt(const _CharT& __c1, const _CharT& __c2) 
    { return __c1 < __c2; }

  static int compare(const _CharT* __s1, const _CharT* __s2, size_t __n) {
    for (size_t __i = 0; __i < __n; ++__i)
      if (!eq(__s1[__i], __s2[__i]))
        return __s1[__i] < __s2[__i] ? -1 : 1;
    return 0;
  }

  static size_t length(const _CharT* __s) {
# ifdef __STL_DEFAULT_CONSTRUCTOR_BUG
    const _CharT _NullChar = _CharT(0);
# else
    const _CharT _NullChar = _CharT();
# endif
    size_t __i;
    for (__i = 0; !eq(__s[__i], _NullChar); ++__i)
      {}
    return __i;
  }

  static const _CharT* find(const _CharT* __s, size_t __n, const _CharT& __c)
  {
    for ( ; __n > 0 ; ++__s, --__n)
      if (eq(*__s, __c))
        return __s;
    return 0;
  }

  static _CharT* move(_CharT* __s1, const _CharT* __s2, size_t __n) {
    memmove(__s1, __s2, __n * sizeof(_CharT));
    return __s1;
  }
    
  static _CharT* copy(_CharT* __s1, const _CharT* __s2, size_t __n) {
    memcpy(__s1, __s2, __n * sizeof(_CharT));
    return __s1;
  } 

  static _CharT* assign(_CharT* __s, size_t __n, _CharT __c) {
    for (size_t __i = 0; __i < __n; ++__i)
      __s[__i] = __c;
    return __s;
  }

  static int_type not_eof(const int_type& __c) {
    return !eq_int_type(__c, eof()) ? __c : 0;
  }

  static char_type to_char_type(const int_type& __c) {
    return __STATIC_CAST(char_type,__c);
  }

  static int_type to_int_type(const char_type& __c) {
    return __STATIC_CAST(int_type,__c);
  }

  static bool eq_int_type(const int_type& __c1, const int_type& __c2) {
    return __c1 == __c2;
  }

  static int_type eof() {
    return __STATIC_CAST(int_type,-1);
  }
};

// Generic char_traits class.  Note that this class is provided only
//  as a base for explicit specialization; it is unlikely to be useful
//  as is for any particular user-defined type.  In particular, it 
//  *will not work* for a non-POD type.

template <class _CharT> struct char_traits
  : public __char_traits_base<_CharT, _CharT>
{};

// Specialization for char.

__STL_TEMPLATE_NULL struct char_traits<char> 
  : public __char_traits_base<char, int>
{
  typedef char char_type;
  typedef int int_type;
#ifdef __STL_USE_NEW_IOSTREAMS
  typedef streamoff off_type;
  typedef streampos pos_type;
  typedef mbstate_t state_type;
#endif /* __STL_USE_NEW_IOSTREAMS */

  static int compare(const char* __s1, const char* __s2, size_t __n) 
    { return memcmp(__s1, __s2, __n); }
  
  static size_t length(const char* __s) { return strlen(__s); }

  static void assign(char& __c1, const char& __c2) { __c1 = __c2; }

  static char* assign(char* __s, size_t __n, char __c)
    { memset(__s, __c, __n); return __s; }
};

# if defined (__STL_WCHAR_T)
// Specialization for wchar_t.

__STL_TEMPLATE_NULL struct char_traits<wchar_t>
  : public __char_traits_base<wchar_t, wint_t>
{};
# endif

__STL_END_NAMESPACE
# endif /* __STL_CHAR_TRAITS_DEFINED */

__STL_BEGIN_NAMESPACE
// Helper classes that turn char_traits into function objects.

template <class _Traits>
struct _Eq_traits
  : public binary_function<typename _Traits::char_type,
                           typename _Traits::char_type,
                           bool>
{
  bool operator()(const typename _Traits::char_type& __x,
                  const typename _Traits::char_type& __y) const
    { return _Traits::eq(__x, __y); }
};

template <class _Traits>
struct _Eq_int_traits
  : public binary_function<typename _Traits::char_type,
                           typename _Traits::int_type,
                           bool>
{
  bool operator()(const typename _Traits::char_type& __x,
                  const typename _Traits::int_type& __y) const
    { return _Traits::eq_int_type(_Traits::to_int_type(__x), __y); }
};

template <class _Traits>
struct _Lt_traits
  : public binary_function<typename _Traits::char_type,
                           typename _Traits::char_type,
                           bool>
{
  bool operator()(const typename _Traits::char_type& __x,
                  const typename _Traits::char_type& __y) const
    { return _Traits::lt(__x, __y); }
};

__STL_END_NAMESPACE

#endif /* __SGI_STL_CHAR_TRAITS_H */

// Local Variables:
// mode:C++
// End:

