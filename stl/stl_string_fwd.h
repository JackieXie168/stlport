/*
 * Copyright (c) 1997
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

#ifndef __SGI_STL_STRING_FWD_H
#define __SGI_STL_STRING_FWD_H

#if defined (__STL_USE_NEW_STYLE_HEADERS)
# include <cstddef>
#else
# include <stddef.h>
#endif

#include <stl_config.h>
// to esure definition of char_traits appears before
#include <char_traits.h>

__STL_BEGIN_NAMESPACE

// template <class _CharT> struct char_traits;
template <class _Tp> class allocator;

# if !defined (__STL_LIMITED_DEFAULT_TEMPLATES)
template <class _CharT, 
          class _Traits = char_traits<_CharT>, 
          class _Alloc = __STL_DEFAULT_ALLOCATOR(_CharT) >
class basic_string;
# else
template <class _CharT, 
          class _Traits, 
          class _Alloc>
class basic_string;
# endif /* __STL_LIMITED_DEFAULT_TEMPLATES */

// fbp : to avoid problems with other parts of std library,
// use allocator<T> always
typedef basic_string<char, char_traits<char>, allocator<char> > string;

#  ifdef __STL_WCHAR_T
typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;
#  endif

template <class _CharT, class _Traits, class _Alloc>
const char* __get_c_string(const basic_string<_CharT, _Traits, _Alloc>& __str);

__STL_END_NAMESPACE

#endif /* __SGI_STL_STRING_FWD_H */

// Local Variables:
// mode:C++
// End:
