/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996-1998
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

#ifndef __SGI_STL_INTERNAL_ITERATOR_BASE_H
#define __SGI_STL_INTERNAL_ITERATOR_BASE_H

#ifndef __STLPORT_CSTDDEF
# include <cstddef>
#endif

#ifndef __TYPE_TRAITS_H
# include <type_traits.h>
#endif

# if defined ( __STL_USE_ABBREVS )
// ugliness is intentional - to reduce conflicts
#  define input_iterator_tag             _In__ItT
#  define output_iterator_tag            _Ou__ItT
#  define bidirectional_iterator_tag     _Bd__ItT
#  define random_access_iterator_tag     _Ra__ItT
#  define input_iterator                 _In__It
#  define output_iterator                _Ou__It
#  define bidirectional_iterator         _Bd__It
#  define random_access_iterator         _Ra__It
#  define reverse_bidirectional_iterator _rBd__It
#  define reverse_iterator               _r__It
#  define back_insert_iterator           _bI__It
#  define front_insert_iterator          _fI__It
#  define raw_storage_iterator           _rS__It
#  define _Const_traits _C_Tr
#  define _Nonconst_traits _N_Tr
# endif

__STL_BEGIN_NAMESPACE

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// The base classes input_iterator, output_iterator, forward_iterator,
// bidirectional_iterator, and random_access_iterator are not part of
// the C++ standard.  (They have been replaced by struct iterator.)
// They are included for backward compatibility with the HP STL.

template <class _Tp, class _Distance> struct input_iterator {
  typedef input_iterator_tag iterator_category;
  typedef _Tp                value_type;
  typedef _Distance          difference_type;
  typedef _Tp*               pointer;
  typedef _Tp&               reference;
};

struct output_iterator {
  typedef output_iterator_tag iterator_category;
# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;
# endif
};

template <class _Tp, class _Distance> struct forward_iterator {
  typedef forward_iterator_tag iterator_category;
  typedef _Tp                  value_type;
  typedef _Distance            difference_type;
  typedef _Tp*                 pointer;
  typedef _Tp&                 reference;
};


template <class _Tp, class _Distance> struct bidirectional_iterator {
  typedef bidirectional_iterator_tag iterator_category;
  typedef _Tp                        value_type;
  typedef _Distance                  difference_type;
  typedef _Tp*                       pointer;
  typedef _Tp&                       reference;
};

template <class _Tp, class _Distance> struct random_access_iterator {
  typedef random_access_iterator_tag iterator_category;
  typedef _Tp                        value_type;
  typedef _Distance                  difference_type;
  typedef _Tp*                       pointer;
  typedef _Tp&                       reference;
};

#  ifdef __STL_USE_NAMESPACES
template <class _Category, class _Tp, __DFL_TMPL_PARAM(_Distance,ptrdiff_t),
          __DFL_TMPL_PARAM(_Pointer,_Tp*), __DFL_TMPL_PARAM(_Reference,_Tp&) >
struct iterator {
  typedef _Category  iterator_category;
  typedef _Tp        value_type;
  typedef _Distance  difference_type;
  typedef _Pointer   pointer;
  typedef _Reference reference;
};
#  endif /* __STL_USE_NAMESPACES */

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _Iterator>
struct iterator_traits {
  typedef typename _Iterator::iterator_category iterator_category;
  typedef typename _Iterator::value_type        value_type;
  typedef typename _Iterator::difference_type   difference_type;
  typedef typename _Iterator::pointer           pointer;
  typedef typename _Iterator::reference         reference;
};

// fbp : this order keeps gcc happy
template <class _Tp>
struct iterator_traits<const _Tp*> {
  typedef random_access_iterator_tag iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef const _Tp*                  pointer;
  typedef const _Tp&                  reference;
};

template <class _Tp>
struct iterator_traits<_Tp*> {
  typedef random_access_iterator_tag iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};

# ifdef __BORLANDC__
template <class _Tp>
struct iterator_traits<_Tp* const> {
  typedef random_access_iterator_tag iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef const _Tp*                  pointer;
  typedef const _Tp&                  reference;
};
# endif
// The overloaded functions iterator_category, distance_type, and
// value_type are not part of the C++ standard.  (They have been
// replaced by struct iterator_traits.)  They are included for
// backward compatibility with the HP STL.

// We introduce internal names for these functions.

template <class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
__iterator_category(const _Iter&)
{
  typedef typename iterator_traits<_Iter>::iterator_category _Category;
  return _Category();
}

template <class _Iter>
inline typename iterator_traits<_Iter>::difference_type*
__distance_type(const _Iter&)
{
  typedef typename iterator_traits<_Iter>::difference_type _diff_type;
  return __STATIC_CAST(_diff_type*,0);
}

template <class _Iter>
inline typename iterator_traits<_Iter>::value_type*
__value_type(const _Iter&)
{
  typedef typename iterator_traits<_Iter>::value_type _value_type;
  return __STATIC_CAST(_value_type*,0);
}

template <class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
iterator_category(const _Iter& __i) { return __iterator_category(__i); }


template <class _Iter>
inline typename iterator_traits<_Iter>::difference_type*
distance_type(const _Iter& __i) { return __distance_type(__i); }

template <class _Iter>
inline typename iterator_traits<_Iter>::value_type*
value_type(const _Iter& __i) { return __value_type(__i); }

#define __ITERATOR_CATEGORY(__i) __iterator_category(__i)
#define __DISTANCE_TYPE(__i)     __distance_type(__i)
#define __VALUE_TYPE(__i)        __value_type(__i)

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _Tp, class _Distance> 
inline input_iterator_tag 
iterator_category(const input_iterator<_Tp, _Distance>&)
  { return input_iterator_tag(); }

inline output_iterator_tag iterator_category(const output_iterator&)
  { return output_iterator_tag(); }

template <class _Tp, class _Distance> 
inline forward_iterator_tag
iterator_category(const forward_iterator<_Tp, _Distance>&)
  { return forward_iterator_tag(); }

template <class _Tp, class _Distance> 
inline bidirectional_iterator_tag
iterator_category(const bidirectional_iterator<_Tp, _Distance>&)
  { return bidirectional_iterator_tag(); }

template <class _Tp, class _Distance> 
inline random_access_iterator_tag
iterator_category(const random_access_iterator<_Tp, _Distance>&)
  { return random_access_iterator_tag(); }

template <class _Tp>
inline random_access_iterator_tag iterator_category(const _Tp*)
  { return random_access_iterator_tag(); }

template <class _Tp, class _Distance> 
inline _Tp* value_type(const input_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <class _Tp, class _Distance> 
inline _Tp* value_type(const forward_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <class _Tp, class _Distance> 
inline _Tp* value_type(const bidirectional_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <class _Tp, class _Distance> 
inline _Tp* value_type(const random_access_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <class _Tp>
inline _Tp* value_type(const _Tp*) { return (_Tp*)(0); }

template <class _Tp, class _Distance> 
inline _Distance* distance_type(const input_iterator<_Tp, _Distance>&)
{
  return (_Distance*)(0);
}

template <class _Tp, class _Distance> 
inline _Distance* distance_type(const forward_iterator<_Tp, _Distance>&)
{
  return (_Distance*)(0);
}

template <class _Tp, class _Distance> 
inline _Distance* 
distance_type(const bidirectional_iterator<_Tp, _Distance>&)
{
  return (_Distance*)(0);
}

template <class _Tp, class _Distance> 
inline _Distance* 
distance_type(const random_access_iterator<_Tp, _Distance>&)
{
  return (_Distance*)(0);
}

template <class _Tp>
inline ptrdiff_t* distance_type(const _Tp*) { return (ptrdiff_t*)(0); }

// Without partial specialization we can't use iterator_traits, so
// we must keep the old iterator query functions around.  

#define __ITERATOR_CATEGORY(__i) iterator_category(__i)
#define __DISTANCE_TYPE(__i)     distance_type(__i)
#define __VALUE_TYPE(__i)        value_type(__i)

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _InputIterator, class _Distance>
inline void __distance(_InputIterator __first, _InputIterator __last,
                       _Distance& __n, input_iterator_tag)
{
  while (__first != __last) { ++__first; ++__n; }
}

# if defined (__STL_NONTEMPL_BASE_MATCH_BUG) 
template <class _ForwardIterator, class _Distance>
inline void __distance(_ForwardIterator __first, _ForwardIterator __last,
                       _Distance& __n, forward_iterator_tag)
{
  while (__first != __last) { ++__first; ++__n; }
}

template <class _BidirectionalIterator, class _Distance>
__STL_INLINE_LOOP void __distance(_BidirectionalIterator __first, 
                            _BidirectionalIterator __last,
                            _Distance& __n, bidirectional_iterator_tag) {
    while (__first != __last) { ++__first; ++__n; }
}
# endif

template <class _RandomAccessIterator, class _Distance>
inline void __distance(_RandomAccessIterator __first, 
                       _RandomAccessIterator __last, 
                       _Distance& __n, random_access_iterator_tag)
{
  __n += __last - __first;
}

template <class _InputIterator, class _Distance>
inline void distance(_InputIterator __first, 
                     _InputIterator __last, _Distance& __n)
{
  __distance(__first, __last, __n, iterator_category(__first));
}

template <class _InputIterator>
inline __STL_DIFFERENCE_TYPE(_InputIterator)
__distance(_InputIterator __first, _InputIterator __last, input_iterator_tag)
{
  __STL_DIFFERENCE_TYPE(_InputIterator) __n = 0;
  while (__first != __last) {
    ++__first; ++__n;
  }
  return __n;
}

template <class _RandomAccessIterator>
inline __STL_DIFFERENCE_TYPE(_RandomAccessIterator)
__distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
           random_access_iterator_tag) {
  return __last - __first;
}

template <class _InputIterator>
inline __STL_DIFFERENCE_TYPE(_InputIterator)
distance(_InputIterator __first, _InputIterator __last) {
# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef typename iterator_traits<_InputIterator>::iterator_category 
    _Category;
  return __distance(__first, __last, _Category());
# else
  return __distance(__first, __last, iterator_category(__first));  
# endif
}


# if defined (__STL_MSVC50_COMPATIBILITY)
# define __Reference _Reference, class _Pointer
# define Reference__ _Reference, _Pointer
template <class _BidirectionalIterator, class _Tp, 
    __DFL_TMPL_PARAM(_Reference, _Tp& ),
    __DFL_TMPL_PARAM(_Pointer, _Tp*),
    __DFL_TYPE_PARAM(_Distance, ptrdiff_t)> 
# else
# define __Reference _Reference
# define Reference__ _Reference
template <class _BidirectionalIterator, class _Tp, __DFL_TMPL_PARAM(_Reference, _Tp& ),
    __DFL_TYPE_PARAM(_Distance, ptrdiff_t)> 
# endif
class reverse_bidirectional_iterator {
  typedef reverse_bidirectional_iterator<_BidirectionalIterator, _Tp, 
                                         Reference__, _Distance> _Self;
  //  friend inline bool operator== __STL_NULL_TMPL_ARGS (const _Self& x, const _Self& y);
protected:
  _BidirectionalIterator current;
public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef _Tp                        value_type;
  typedef _Distance                  difference_type;
# if defined (__STL_MSVC50_COMPATIBILITY)
  typedef _Pointer                   pointer;
# else
  typedef _Tp*                       pointer;
# endif
  typedef _Reference                 reference;

  reverse_bidirectional_iterator() {}
  explicit reverse_bidirectional_iterator(_BidirectionalIterator __x)
    : current(__x) {}
  _BidirectionalIterator base() const { return current; }
  _Reference operator*() const {
    _BidirectionalIterator __tmp = current;
    return *--__tmp;
  }
# if !(defined __SGI_STL_NO_ARROW_OPERATOR && ! defined (__STL_MSVC50_COMPATIBILITY))
  __STL_DEFINE_ARROW_OPERATOR
# endif
  _Self& operator++() {
    --current;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    --current;
    return __tmp;
  }
  _Self& operator--() {
    ++current;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    ++current;
    return __tmp;
  }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _BidirectionalIterator, class _Tp, class __Reference, 
          class _Distance>
inline bidirectional_iterator_tag
iterator_category(const reverse_bidirectional_iterator<_BidirectionalIterator,
                                                       _Tp, Reference__, 
                                                       _Distance>&) 
{
  return bidirectional_iterator_tag();
}

template <class _BidirectionalIterator, class _Tp, class __Reference, 
          class _Distance>
inline _Tp*
value_type(const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
                                               Reference__, _Distance>&)
{
  return (_Tp*) 0;
}

template <class _BidirectionalIterator, class _Tp, class __Reference, 
          class _Distance>
inline _Distance*
distance_type(const reverse_bidirectional_iterator<_BidirectionalIterator, 
                                                   _Tp,
                                                   Reference__, _Distance>&)
{
  return (_Distance*) 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _BidirectionalIterator, class _Tp, class __Reference, 
          class _Distance>
inline bool operator==(
    const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
                                               Reference__, _Distance>& __x,
    const reverse_bidirectional_iterator<_BidirectionalIterator, _Tp,
                                               Reference__, _Distance>& __y)
{
  return __x.base() == __y.base();
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _BiIter, class _Tp, class __Reference, class _Distance>
inline bool operator!=(
    const reverse_bidirectional_iterator<_BiIter, _Tp, Reference__, _Distance>& __x, 
    const reverse_bidirectional_iterator<_BiIter, _Tp, Reference__, _Distance>& __y)
{
  return !(__x == __y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

#if defined ( __STL_CLASS_PARTIAL_SPECIALIZATION ) && \
! defined (__STL_PARTIAL_SPECIALIZATION_BUG)

// This is the new version of reverse_iterator, as defined in the
//  draft C++ standard.  It relies on the iterator_traits template,
//  which in turn relies on partial specialization.  The class
//  reverse_bidirectional_iterator is no longer part of the draft
//  standard, but it is retained for backward compatibility.

template <class _Iterator>
class reverse_iterator 
{
protected:
  _Iterator current;
public:
  typedef typename iterator_traits<_Iterator>::iterator_category
          iterator_category;
  typedef typename iterator_traits<_Iterator>::value_type
          value_type;
  typedef typename iterator_traits<_Iterator>::difference_type
          difference_type;
  typedef typename iterator_traits<_Iterator>::pointer
          pointer;
  typedef typename iterator_traits<_Iterator>::reference
          reference;

  typedef _Iterator iterator_type;
  typedef reverse_iterator<_Iterator> _Self;

public:
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type __x) : current(__x) {}

  reverse_iterator(const _Self& __x) : current(__x.current) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class _Iter>
  reverse_iterator(const reverse_iterator<_Iter>& __x)
    : current(__x.base()) {}
#endif /* __STL_MEMBER_TEMPLATES */
    
  iterator_type base() const { return current; }
  reference operator*() const {
    _Iterator __tmp = current;
    return *--__tmp;
  }
  __STL_DEFINE_ARROW_OPERATOR
  _Self& operator++() {
    --current;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    --current;
    return __tmp;
  }
  _Self& operator--() {
    ++current;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    ++current;
    return __tmp;
  }

  _Self operator+(difference_type __n) const {
    return _Self(current - __n);
  }
  _Self& operator+=(difference_type __n) {
    current -= __n;
    return *this;
  }
  _Self operator-(difference_type __n) const {
    return _Self(current + __n);
  }
  _Self& operator-=(difference_type __n) {
    current += __n;
    return *this;
  }
  reference operator[](difference_type __n) const { return *(*this + __n); }  
}; 
 
template <class _Iterator>
inline bool operator==(const reverse_iterator<_Iterator>& __x, 
                       const reverse_iterator<_Iterator>& __y) {
  return __x.base() == __y.base();
}

template <class _Iterator>
inline bool operator<(const reverse_iterator<_Iterator>& __x, 
                      const reverse_iterator<_Iterator>& __y) {
  return __y.base() < __x.base();
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _Iterator>
inline bool operator!=(const reverse_iterator<_Iterator>& __x, 
                       const reverse_iterator<_Iterator>& __y) {
  return !(__x == __y);
}

template <class _Iterator>
inline bool operator>(const reverse_iterator<_Iterator>& __x, 
                      const reverse_iterator<_Iterator>& __y) {
  return __y < __x;
}

template <class _Iterator>
inline bool operator<=(const reverse_iterator<_Iterator>& __x, 
                       const reverse_iterator<_Iterator>& __y) {
  return !(__y < __x);
}

template <class _Iterator>
inline bool operator>=(const reverse_iterator<_Iterator>& __x, 
                      const reverse_iterator<_Iterator>& __y) {
  return !(__x < __y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

template <class _Iterator>
inline typename reverse_iterator<_Iterator>::difference_type
operator-(const reverse_iterator<_Iterator>& __x, 
          const reverse_iterator<_Iterator>& __y) {
  return __y.base() - __x.base();
}

template <class _Iterator>
inline reverse_iterator<_Iterator> 
operator+(typename reverse_iterator<_Iterator>::difference_type __n,
          const reverse_iterator<_Iterator>& __x) {
  return reverse_iterator<_Iterator>(__x.base() - __n);
}

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// This is the old version of reverse_iterator, as found in the original
//  HP STL.  It does not use partial specialization.

template <class _RandomAccessIterator, 
# if defined (__MSL__) && (__MSL__ >= 0x2405)
	__DFL_TMPL_PARAM(_Tp,iterator_traits<_RandomAccessIterator>::value_type),
# else
	class _Tp,
#endif
 __DFL_TMPL_PARAM(_Reference,_Tp&),
# if defined (__STL_MSVC50_COMPATIBILITY)
        __DFL_TMPL_PARAM(_Pointer, _Tp*),
# endif
        __DFL_TYPE_PARAM(_Distance,ptrdiff_t)> 
class reverse_iterator {
  typedef reverse_iterator<_RandomAccessIterator, _Tp, Reference__, _Distance>
          _Self;
protected:
  _RandomAccessIterator __current;
public:
  typedef random_access_iterator_tag iterator_category;
  typedef _Tp                        value_type;
  typedef _Distance                  difference_type;
# if defined (__STL_MSVC50_COMPATIBILITY)
  typedef _Pointer                   pointer;
# else
  typedef _Tp*                       pointer;
# endif
  typedef _Reference                 reference;

  reverse_iterator() {}
  reverse_iterator(const _Self& __x) : __current(__x.base()) {}
  explicit reverse_iterator(_RandomAccessIterator __x) : __current(__x) {}
  _Self& operator=(const _Self& __x) {__current = __x.base(); return *this; }  
       
  _RandomAccessIterator base() const { return __current; }
  _Reference operator*() const { return *(__current - 1); }

# if !(defined __SGI_STL_NO_ARROW_OPERATOR && ! defined (__STL_MSVC50_COMPATIBILITY))
  __STL_DEFINE_ARROW_OPERATOR
# endif

  _Self& operator++() {
    --__current;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    --__current;
    return __tmp;
  }
  _Self& operator--() {
    ++__current;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    ++__current;
    return __tmp;
  }
  _Self operator+(_Distance __n) const {
    return _Self(__current - __n);
  }
  _Self& operator+=(_Distance __n) {
    __current -= __n;
    return *this;
  }
  _Self operator-(_Distance __n) const {
    return _Self(__current + __n);
  }
  _Self& operator-=(_Distance __n) {
    __current += __n;
    return *this;
  }
  _Reference operator[](_Distance __n) const { return *(*this + __n); }
};

template <class _RandomAccessIterator, class _Tp, 
          class __Reference, class _Distance>
inline random_access_iterator_tag
iterator_category(const reverse_iterator<_RandomAccessIterator, _Tp,
                                         Reference__, _Distance>&)
{
  return random_access_iterator_tag();
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline _Tp* value_type(const reverse_iterator<_RandomAccessIterator, _Tp,
                                              Reference__, _Distance>&)
{
  return (_Tp*) 0;
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline _Distance* 
distance_type(const reverse_iterator<_RandomAccessIterator, 
                                     _Tp, Reference__, _Distance>&)
{
  return (_Distance*) 0;
}


template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool 
operator==(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __y)
{
  return __x.base() == __y.base();
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool 
operator<(const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x, 
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __y)
{
  return __y.base() < __x.base();
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool 
operator!=(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  Reference__, _Distance>& __y) {
  return !(__x == __y);
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline bool 
operator>(const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x, 
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __y) {
  return __y < __x;
}

template <class _RandomAccessIterator, class _Tp,
          class _Reference, class _Distance>
inline bool 
operator<=(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  _Reference, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  _Reference, _Distance>& __y) {
  return !(__y < __x);
}

template <class _RandomAccessIterator, class _Tp,
          class _Reference, class _Distance>
inline bool 
operator>=(const reverse_iterator<_RandomAccessIterator, _Tp,
                                  _Reference, _Distance>& __x, 
           const reverse_iterator<_RandomAccessIterator, _Tp,
                                  _Reference, _Distance>& __y) {
  return !(__x < __y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline _Distance 
operator-(const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x, 
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __y)
{
  return __y.base() - __x.base();
}

template <class _RandomAccessIterator, class _Tp,
          class __Reference, class _Distance>
inline reverse_iterator<_RandomAccessIterator, _Tp,
                        Reference__, _Distance> 
operator+(_Distance __n,
          const reverse_iterator<_RandomAccessIterator, _Tp,
                                 Reference__, _Distance>& __x)
{
  return reverse_iterator<_RandomAccessIterator, _Tp,
                          Reference__, _Distance>(__x.base() - __n);
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */


// fbp: those are being used for iterator/const_iterator definitions everywhere
template <class _Tp>
struct _Const_traits {
  typedef _Tp value_type;
  typedef const _Tp&  reference;
  typedef const _Tp*  pointer;
  //  typedef __true_type _is_const;
};

template <class _Tp>
struct _Nonconst_traits {
  typedef _Tp value_type;
  typedef _Tp& reference;
  typedef _Tp* pointer;
  //  typedef __false_type _is_const;
};

#  if defined (__STL_BASE_TYPEDEF_BUG)
// this workaround is needed for SunPro 4.0.1
template <class _Traits>
struct __cnst_traits_aux : private _Traits
{
  typedef typename _Traits::value_type value_type;
};
#  define __TRAITS_VALUE_TYPE(_Traits) __cnst_traits_aux<_Traits>::value_type
#  else
#  define __TRAITS_VALUE_TYPE(_Traits) _Traits::value_type
#  endif

# if defined (__STL_MSVC)
// MSVC specific
template <class _InputIterator, class _Dist>
inline void _Distance(_InputIterator __first, 
		      _InputIterator __last, _Dist& __n)
{
  __distance(__first, __last, __n, iterator_category(__first));
}
# endif

template <class _InputIter, class _Distance>
__STL_INLINE_LOOP void __advance(_InputIter& __i, _Distance __n, input_iterator_tag) {
  while (__n--) ++__i;
}

# if defined (__STL_NONTEMPL_BASE_MATCH_BUG)
template <class _ForwardIterator, class _Distance>
__STL_INLINE_LOOP void __advance(_ForwardIterator& i, _Distance n, forward_iterator_tag) {
    while (n--) ++i;
}
# endif

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1183
#endif

template <class _BidirectionalIterator, class _Distance>
__STL_INLINE_LOOP void __advance(_BidirectionalIterator& __i, _Distance __n, 
                      bidirectional_iterator_tag) {
  if (__n > 0)
    while (__n--) ++__i;
  else
    while (__n++) --__i;
}

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1183
#endif

template <class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator& __i, _Distance __n, 
                      random_access_iterator_tag) {
  __i += __n;
}

template <class _InputIterator, class _Distance>
inline void advance(_InputIterator& __i, _Distance __n) {
  __advance(__i, __n, iterator_category(__i));
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_ITERATOR_BASE_H */



// Local Variables:
// mode:C++
// End:
