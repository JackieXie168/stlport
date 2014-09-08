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

#ifndef __SGI_STL_INTERNAL_VECTOR_H
#define __SGI_STL_INTERNAL_VECTOR_H

# ifndef __SGI_STL_INTERNAL_ALGOBASE_H
#  include <stl/_algobase.h>
# endif

# ifndef __SGI_STL_INTERNAL_ALLOC_H
#  include <stl/_alloc.h>
# endif

# ifndef __SGI_STL_INTERNAL_ITERATOR_H
#  include <stl/_iterator.h>
# endif

# ifndef __SGI_STL_INTERNAL_UNINITIALIZED_H
#  include <stl/_uninitialized.h>
# endif

# ifndef __STL_RANGE_ERRORS_H
#  include <stl/_range_errors.h>
# endif

#  undef  vector
#  define vector __WORKAROUND_DBG_RENAME(vector)

__STL_BEGIN_NAMESPACE 

// The vector base class serves two purposes.  First, its constructor
// and destructor allocate (but don't initialize) storage.  This makes
// exception safety easier.  Second, the base class encapsulates all of
// the differences between SGI-style allocators and standard-conforming
// allocators.

template <class _Tp, class _Alloc> 
class _Vector_base {
public:

  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;

  _Vector_base(const _Alloc& __a)
    : _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0) {
  }
  _Vector_base(size_t __n, const _Alloc& __a)
    : _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0)
  {
    _M_start = _M_end_of_storage.allocate(__n);
    _M_finish = _M_start;
    _M_end_of_storage._M_data = _M_start + __n;
	__STL_MPWFIX_TRY __STL_MPWFIX_CATCH		//*TY 06/01/2000 - to keep the exception handling support facility in sane condition.
  }

  ~_Vector_base() { _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }

protected:
  _Tp* _M_start;
  _Tp* _M_finish;
  _STL_alloc_proxy<_Tp*, _Tp, allocator_type> _M_end_of_storage;
};

template <class _Tp, __STL_DEFAULT_ALLOCATOR_SELECT(_Tp) >
class vector : public _Vector_base<_Tp, _Alloc> 
{
private:
  typedef _Vector_base<_Tp, _Alloc> _Base;
public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;

public:
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;

  __STL_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;

  typedef typename _Vector_base<_Tp, _Alloc>::allocator_type allocator_type;

  allocator_type get_allocator() const {
    return __STL_CONVERT_ALLOCATOR((const allocator_type&)_M_end_of_storage, _Tp);
  }

protected:
#if defined( __STL_HAS_NAMESPACES )
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_start;
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_finish;
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_end_of_storage;
#endif /* __STL_HAS_NAMESPACES */


protected:
  // handles both single and fill insertion on overflow
  void _M_insert_overflow(pointer __position, const _Tp& __x, size_type __n = 1);

public:
  iterator begin() { return _M_start; }
  const_iterator begin() const { return _M_start; }
  iterator end() { return _M_finish; }
  const_iterator end() const { return _M_finish; }

  reverse_iterator rbegin()
    { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const
    { return const_reverse_iterator(end()); }
  reverse_iterator rend()
    { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

  size_type size() const
    { return size_type(_M_finish - _M_start); }
  size_type max_size() const
    { return size_type(-1) / sizeof(_Tp); }
  size_type capacity() const
    { return size_type(_M_end_of_storage._M_data - _M_start); }
  bool empty() const
    { return _M_start == _M_finish; }

  reference operator[](size_type __n) { return *(begin() + __n); }
  const_reference operator[](size_type __n) const { return *(begin() + __n); }

  void _M_range_check(size_type __n) const {
    if (__n >= size_type(_M_finish-_M_start))
      __stl_throw_out_of_range("vector");
  }

  reference at(size_type __n)
    { _M_range_check(__n); return (*this)[__n]; }
  const_reference at(size_type __n) const
    { _M_range_check(__n); return (*this)[__n]; }

  explicit vector(const allocator_type& __a = allocator_type())
    : _Vector_base<_Tp, _Alloc>(__a) {}

  vector(size_type __n, const _Tp& __value,
         const allocator_type& __a = allocator_type()) 
    : _Vector_base<_Tp, _Alloc>(__n, __a) { 
    _M_finish = uninitialized_fill_n(_M_start, __n, __value); 
  }

  explicit vector(size_type __n)
    : _Vector_base<_Tp, _Alloc>(__n, allocator_type() ) {
    _M_finish = uninitialized_fill_n(_M_start, __n, _Tp()); 
  }

  vector(const vector<_Tp, _Alloc>& __x) 
    : _Vector_base<_Tp, _Alloc>(__x.size(), __x.get_allocator()) { 
    _M_finish = uninitialized_copy((const_pointer)__x._M_start, (const_pointer)__x._M_finish, _M_start);
  }
  
#ifdef __STL_MEMBER_TEMPLATES

  template <class _Integer>
  void _M_initialize_aux(_Integer __n, _Integer __value, __true_type) {
    _M_start = _M_end_of_storage.allocate(__n);
    _M_end_of_storage._M_data = _M_start + __n; 
    _M_finish = uninitialized_fill_n(_M_start, __n, __value);
  }

  template <class _InputIterator>
  void _M_initialize_aux(_InputIterator __first, _InputIterator __last,
                         __false_type) {
    _M_range_initialize(__first, __last, __ITERATOR_CATEGORY(__first));
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last) :
    _Vector_base<_Tp, _Alloc>(allocator_type()) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_aux(__first, __last, _Integral());
  }

  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
         const allocator_type& __a) :
    _Vector_base<_Tp, _Alloc>(__a) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_aux(__first, __last, _Integral());
  }

#else
  vector(const _Tp* __first, const _Tp* __last,
         const allocator_type& __a = allocator_type())
    : _Vector_base<_Tp, _Alloc>(__last - __first, __a) { 
      _M_finish = uninitialized_copy(__first, __last, _M_start); 
  }
#endif /* __STL_MEMBER_TEMPLATES */

  ~vector() { _Destroy(_M_start, _M_finish); }

  vector<_Tp, _Alloc>& operator=(const vector<_Tp, _Alloc>& __x);

  void reserve(size_type __n);

  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const _Tp& __val) { _M_fill_assign(__n, __val); }
  void _M_fill_assign(size_type __n, const _Tp& __val);

#ifdef __STL_MEMBER_TEMPLATES
  
  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
    { assign((size_type) __n, (_Tp) __val); }

  template <class _InputIter>
  void _M_assign_dispatch(_InputIter __first, _InputIter __last, __false_type)
    { _M_assign_aux(__first, __last, __ITERATOR_CATEGORY(__first)); }


  template <class _InputIter>
  void _M_assign_aux(_InputIter __first, _InputIter __last,
		     input_iterator_tag) {
    iterator __cur = begin();
    for ( ; __first != __last && __cur != end(); ++__cur, ++__first)
      *__cur = *__first;
    if (__first == __last)
      erase(__cur, end());
    else
      insert(end(), __first, __last);
  }
  
  template <class _ForwardIter>
  void _M_assign_aux(_ForwardIter __first, _ForwardIter __last,
		     forward_iterator_tag)
# if ! defined (__STL_INLINE_MEMBER_TEMPLATES)
;
# else
    {
    size_type __len = 0;
    distance(__first, __last, __len);
    
    if (__len > capacity()) {
      iterator __tmp = _M_allocate_and_copy(__len, __first, __last);
    _Destroy(_M_start, _M_finish);
    _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
    _M_start = __tmp;
    _M_end_of_storage._M_data = _M_finish = _M_start + __len;
    }
    else if (size() >= __len) {
      iterator __new_finish = copy(__first, __last, _M_start);
      _Destroy(__new_finish, _M_finish);
      _M_finish = __new_finish;
    }
    else {
    _ForwardIter __mid = __first;
    advance(__mid, size());
    copy(__first, __mid, _M_start);
    _M_finish = uninitialized_copy(__mid, __last, _M_finish);
    }
  }
# endif /* __STL_INLINE_MEMBER_TEMPLATES */
#endif /* __STL_MEMBER_TEMPLATES */

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  void push_back(const _Tp& __x) {
    if (_M_finish != _M_end_of_storage._M_data) {
      _Construct(_M_finish, __x);
      ++_M_finish;
    }
    else
      _M_insert_overflow(_M_finish, __x);
  }

  void push_back() {
    if (_M_finish != _M_end_of_storage._M_data) {
      _Construct(_M_finish);
      ++_M_finish;
    }
    else
      _M_insert_overflow(_M_finish, _Tp());
  }

  void swap(vector<_Tp, _Alloc>& __x) {
    __STLPORT_STD::swap(_M_start, __x._M_start);
    __STLPORT_STD::swap(_M_finish, __x._M_finish);
    __STLPORT_STD::swap(_M_end_of_storage._M_data, __x._M_end_of_storage._M_data);
  }

  iterator insert(iterator __position, const _Tp& __x) {
    size_type __n = __position - begin();
    if (_M_finish != _M_end_of_storage._M_data) {
      if (__position == end()) {
	_Construct(_M_finish, __x);
	++_M_finish;
      } else {
	_Construct(_M_finish, *(_M_finish - 1));
	++_M_finish;
	_Tp __x_copy = __x;
	copy_backward(__position, _M_finish - 2, _M_finish - 1);
	*__position = __x_copy;
      }
    }
    else
      _M_insert_overflow(__position, __x);
    return begin() + __n;
  }

  iterator insert(iterator __position) {
    size_type __n = __position - begin();
    if (_M_finish != _M_end_of_storage._M_data) {
      if (__position == end()) {
	_Construct(_M_finish);
	++_M_finish;
      } else {
	_Construct(_M_finish, *(_M_finish - 1));
	++_M_finish;
	copy_backward(__position, _M_finish - 2, _M_finish - 1);
	*__position = _Tp();	
      }
    }
    else
      _M_insert_overflow(__position, _Tp());
    return begin() + __n;
  }

  void _M_fill_insert (iterator __pos, size_type __n, const _Tp& __x);

#if defined ( __STL_MEMBER_TEMPLATES) // && ! defined (__STL_INLINE_MEMBER_TEMPLATES)

  template <class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                          __true_type) {
    _M_fill_insert(__pos, (size_type) __n, (_Tp) __val);
  }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
                          _InputIterator __first, _InputIterator __last,
                          __false_type) {
    _M_range_insert(__pos, __first, __last, __ITERATOR_CATEGORY(__first));
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

#else /* __STL_MEMBER_TEMPLATES */
  void insert(iterator __position,
              const_iterator __first, const_iterator __last);
#endif /* __STL_MEMBER_TEMPLATES */

  void insert (iterator __pos, size_type __n, const _Tp& __x)
    { _M_fill_insert(__pos, __n, __x); }

  void pop_back() {
    --_M_finish;
    _Destroy(_M_finish);
  }
  iterator erase(iterator __position) {
    if (__position + 1 != end())
      copy(__position + 1, _M_finish, __position);
    --_M_finish;
    _Destroy(_M_finish);
    return __position;
  }
  iterator erase(iterator __first, iterator __last) {
    pointer __i = copy(__last, _M_finish, __first);
    _Destroy(__i, _M_finish);
    _M_finish = __i;
    return __first;
  }

  void resize(size_type __new_size, const _Tp& __x) {
    if (__new_size < size()) 
      erase(begin() + __new_size, end());
    else
      insert(end(), __new_size - size(), __x);
  }
  void resize(size_type __new_size) { resize(__new_size, _Tp()); }
  void clear() { 
    erase(begin(), end());
  }

protected:

#ifdef __STL_MEMBER_TEMPLATES
  template <class _ForwardIterator>
  pointer _M_allocate_and_copy(size_type __n, _ForwardIterator __first, 
				_ForwardIterator __last) {
    pointer __result = _M_end_of_storage.allocate(__n);
    __STL_TRY {
      uninitialized_copy(__first, __last, __result);
      return __result;
    } 
    __STL_UNWIND(_M_end_of_storage.deallocate(__result, __n));
# ifdef __STL_THROW_RETURN_BUG
	return __result;
# endif
  } 
#else /* __STL_MEMBER_TEMPLATES */
  pointer _M_allocate_and_copy(size_type __n, const_pointer __first, 
			       const_pointer __last)
  {
    pointer __result = _M_end_of_storage.allocate(__n);
    __STL_TRY {
      uninitialized_copy(__first, __last, __result);
      return __result;
    }
    __STL_UNWIND(_M_end_of_storage.deallocate(__result, __n));
# ifdef __STL_THROW_RETURN_BUG
	return __result;
# endif
  }
#endif /* __STL_MEMBER_TEMPLATES */

#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  void _M_range_initialize(_InputIterator __first,  
                           _InputIterator __last, input_iterator_tag)
  {
    for ( ; __first != __last; ++__first)
      push_back(*__first);
  }

  // This function is only called by the constructor. 
  template <class _ForwardIterator>
  void _M_range_initialize(_ForwardIterator __first,
                           _ForwardIterator __last, forward_iterator_tag)
  {
    size_type __n = 0;
    distance(__first, __last, __n);
    _M_start = _M_end_of_storage.allocate(__n);
    _M_end_of_storage._M_data = _M_start + __n;
    _M_finish = uninitialized_copy(__first, __last, _M_start);
  }

  template <class _InputIterator>
  void _M_range_insert(iterator __pos, 
		       _InputIterator __first, 
		       _InputIterator __last,
		       input_iterator_tag)
	{
	  for ( ; __first != __last; ++__first) {
	    __pos = insert(__pos, *__first);
	    ++__pos;
	  }
	}

   template <class _ForwardIterator>
   void _M_range_insert(iterator __position,
			_ForwardIterator __first,
			_ForwardIterator __last,
			forward_iterator_tag)
# ifndef __STL_INLINE_MEMBER_TEMPLATES
     ;
# else
  {
    if (__first != __last) {
      size_type __n = 0;
      distance(__first, __last, __n);
      if (size_type(_M_end_of_storage._M_data - _M_finish) >= __n) {
	const size_type __elems_after = _M_finish - __position;
	pointer __old_finish = _M_finish;
	if (__elems_after > __n) {
	  uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
	  _M_finish += __n;
	  copy_backward(__position, __old_finish - __n, __old_finish);
	  copy(__first, __last, __position);
	}
	else {
	  _ForwardIterator __mid = __first;
	  advance(__mid, __elems_after);
	  uninitialized_copy(__mid, __last, _M_finish);
	  _M_finish += __n - __elems_after;
	  uninitialized_copy(__position, __old_finish, _M_finish);
	  _M_finish += __elems_after;
	  copy(__first, __mid, __position);
	}
      }
      else {
	const size_type __old_size = size();
	const size_type __len = __old_size + max(__old_size, __n);
	pointer __new_start = _M_end_of_storage.allocate(__len);
	pointer __new_finish = __new_start;
	__STL_TRY {
	  __new_finish = uninitialized_copy(_M_start, __position, __new_start);
	  __new_finish = uninitialized_copy(__first, __last, __new_finish);
	  __new_finish
	    = uninitialized_copy(__position, _M_finish, __new_finish);
	}
	__STL_UNWIND((_Destroy(__new_start,__new_finish), 
		      _M_end_of_storage.deallocate(__new_start,__len)));
	_Destroy(_M_start, _M_finish);
	_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
	_M_start = __new_start;
	_M_finish = __new_finish;
	_M_end_of_storage._M_data = __new_start + __len;
      }
    }
  }
# endif /* __STL_INLINE_MEMBER_TEMPLATES */
#endif /* __STL_MEMBER_TEMPLATES */
};

# define __STL_TEMPLATE_CONTAINER vector<_Tp, _Alloc>
# define __STL_TEMPLATE_HEADER    template <class _Tp, class _Alloc>
# include <stl/_relops_cont.h>
# undef __STL_TEMPLATE_CONTAINER
# undef __STL_TEMPLATE_HEADER

# if defined (__STL_USE_TEMPLATE_EXPORT) 
__STL_EXPORT_TEMPLATE_CLASS allocator<void*>;
__STL_EXPORT_TEMPLATE_CLASS _STL_alloc_proxy<void**, void*, allocator<void*> >;
__STL_EXPORT_TEMPLATE_CLASS _Vector_base<void*,allocator<void*> >;
__STL_EXPORT_TEMPLATE_CLASS vector<void*,allocator<void*> >;
# endif

#  undef  vector
#  undef  __vector__
#  define __vector__ __WORKAROUND_RENAME(vector)

__STL_END_NAMESPACE

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_vector.c>
# endif

#ifndef __SGI_STL_INTERNAL_BVECTOR_H
# include <stl/_bvector.h>
#endif

# if defined (__STL_DEBUG)
#  include <stl/debug/_vector.h>
# endif

# if defined (__STL_USE_WRAPPER_FOR_ALLOC_PARAM)
#  include <stl/wrappers/_vector.h>
# endif

#endif /* __SGI_STL_VECTOR_H */

// Local Variables:
// mode:C++
// End:

