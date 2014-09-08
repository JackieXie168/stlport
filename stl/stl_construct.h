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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#if defined (__STL_USE_NEW_STYLE_HEADERS)
# include <new>
#else
# include <new.h>
#endif

__STL_BEGIN_NAMESPACE

template <class _Tp>
inline void destroy(_Tp* __pointer) {
# if _MSC_VER >= 1010
  __pointer;
# endif	// _MSC_VER >= 1000
# if ( defined (__BORLANDC__) && ( __BORLANDC__ < 0x500 ) )
    __pointer->_Tp::~_Tp();
# else
    __pointer->~_Tp();
# endif
# ifdef __STL_SHRED_BYTE
	fill_n((char*)__pointer, sizeof(_Tp), __STL_SHRED_BYTE);
# endif
}

# if defined (new)
#   define __STL_NEW_REDEFINE new
#   undef new
# endif 

template <class _T1, class _T2>
inline void construct(_T1* __p, const _T2& __value) {
# ifdef __STL_SHRED_BYTE
	fill_n((char*)__p, sizeof(_T1), __STL_SHRED_BYTE);
# endif
    __STL_PLACEMENT_NEW (__p) _T1(__value);
}

template <class _T1>
inline void construct(_T1* __p) {
# ifdef __STL_SHRED_BYTE
	fill_n((char*)__p, sizeof(_T1), __STL_SHRED_BYTE);
# endif
  __STL_PLACEMENT_NEW (__p) _T1();
}

# if defined(__STL_NEW_REDEFINE)
# ifdef DEBUG_NEW
#  define new DEBUG_NEW
# endif
#  undef __STL_NEW_REDEFINE
# endif 

#ifdef __STL_TRIVIAL_DESTRUCTOR_BUG       // JKR addition start
inline void destroy(char*) {}
inline void destroy(char**) {}
inline void destroy(unsigned char*) {}
inline void destroy(short*) {}
inline void destroy(unsigned short*) {}
inline void destroy(int*) {}
inline void destroy(unsigned int*) {}
inline void destroy(long*) {}
inline void destroy(unsigned long*) {}
inline void destroy(float*) {}
inline void destroy(double*) {}
inline void destroy(void**) {}
inline void destroy(const void**) {}

inline void destroy(const char*) {}
inline void destroy(const char**) {}
inline void destroy(const unsigned char*) {}
inline void destroy(const short*) {}
inline void destroy(const unsigned short*) {}
inline void destroy(const int*) {}
inline void destroy(const unsigned int*) {}
inline void destroy(const long*) {}
inline void destroy(const unsigned long*) {}
inline void destroy(const float*) {}
inline void destroy(const double*) {}
#endif // JKR addition end

template <class _ForwardIterator>
INLINE_LOOP void
__destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
{
  for ( ; __first < __last; ++__first)
    destroy(&*__first);
}

template <class _ForwardIterator> 
inline void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}

template <class _ForwardIterator, class _Tp>
inline void 
__destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*)
{
  typedef typename __type_traits<_Tp>::has_trivial_destructor
          _Trivial_destructor;
  __destroy_aux(__first, __last, _Trivial_destructor());
}

template <class _ForwardIterator>
inline void destroy(_ForwardIterator __first, _ForwardIterator __last) {
  __destroy(__first, __last, __VALUE_TYPE(__first));
}

inline void destroy(char*, char*) {}
# ifdef __STL_WCHAR_T // dwa 8/15/97
inline void destroy(wchar_t*, wchar_t*) {}
inline void destroy(const wchar_t*, const wchar_t*) {}
# endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
