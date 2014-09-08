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

__STL_BEGIN_NAMESPACE 

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#pragma set woff 1375
#endif

#  define vector __WORKAROUND_RENAME(vector)

# if defined ( __STL_NESTED_TYPE_PARAM_BUG )
#  define __pointer__             _Tp*
#  define __const_pointer__       const _Tp*
#  define __size_type__           size_t
#  define __difference_type__     ptrdiff_t
# else
#  define __pointer__         pointer
#  define __const_pointer__   const_pointer
#  define __size_type__       size_type
#  define __difference_type__ difference_type
# endif

# if defined (__STL_DEBUG)
#  define _Make_iterator(__i) iterator(&_M_iter_list, __i)
#  define _Make_const_iterator(__i) const_iterator(&_M_iter_list, __i)
#  define _Make_ptr(__i)   __i._Get_iterator()
#  define __iterator__       _Vector_iterator<_Tp,_Tp&, _Tp*>
#  define __const_iterator__ _Vector_iterator<_Tp,const _Tp&, const _Tp*>
# else
#  define __iterator__       __pointer__
#  define __const_iterator__ __const_pointer__  
#  define _Make_iterator(__i) __i
#  define _Make_const_iterator(__i) __i
#  define _Make_ptr(__i)   __i
# endif

# if defined ( __STL_USE_ABBREVS )
#  define  _Vector_iterator       _V__It
# endif

# if defined (__STL_DEBUG)

template <class _Tp, class _Ref, class _Ptr>
struct _Vector_iterator;

template <class _Tp,  class _Ref, class _Ptr>
bool __Dereferenceable(const  _Vector_iterator<_Tp, _Ref, _Ptr>& __that);
template <class _Tp,  class _Ref, class _Ptr>
bool __Nonsingular(const  _Vector_iterator<_Tp, _Ref, _Ptr>& __that);

template <class _Tp, class _Ref, class _Ptr>
struct _Vector_iterator : public __owned_link {
private:
    typedef _Vector_iterator<_Tp,_Ref, _Ptr> _Self;
    typedef _Vector_iterator<_Tp,_Tp&, _Tp*> iterator;
    typedef _Vector_iterator<_Tp,const _Tp&, const _Tp*> const_iterator;
public:
    typedef _Tp value_type;
    typedef _Ptr pointer;
    typedef _Ref reference;
    typedef ptrdiff_t difference_type;
    typedef random_access_iterator_tag iterator_category;
    pointer _M_iterator;
public:
    _Vector_iterator() : __owned_link(0)  {}
    _Vector_iterator(const __owned_list* __c, pointer __it) :
        __owned_link(__c), _M_iterator(__it) {}
    _Vector_iterator(const iterator& __it) :
        __owned_link(__it), _M_iterator(__it._Get_iterator()) {}
    ~_Vector_iterator() {}
    pointer  _Get_iterator() const { return _M_iterator; }
    bool _Dereferenceable() const {
      return __Dereferenceable(*this);
    }
    bool _Nonsingular() const {
      return __Nonsingular(*this);
    }
    reference operator*() const {
        __stl_debug_check(_Dereferenceable());
        return *_M_iterator;
    }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
    pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */
    _Self& operator++() {
        ++_M_iterator;
        __stl_debug_check(_Nonsingular());
        return *this;
    }
    _Self operator++(int) {
        _Self __tmp = *this;
        ++_M_iterator;
        return __tmp;
    }
    _Self& operator--() {
        --_M_iterator;
        __stl_debug_check(_Nonsingular());
        return *this;
    }
    _Self operator--(int) {
        _Self __tmp = *this;
        --_M_iterator;
        return __tmp;
    }
    difference_type operator-(const _Self& __y ) const {
      __stl_debug_check(__check_same_owner(*this, __y));
      return _Get_iterator()-__y._Get_iterator();
    }
    _Self& operator+=(difference_type __n) {
        _M_iterator+=__n;
        __stl_debug_check(_Nonsingular());
        return *this;
    }
    _Self& operator-=(difference_type __n) {
    return *this+=-__n;
    }
    _Self operator+(difference_type __n) const {
        _Self __tmp(*this);
        return __tmp += __n;
    }
    _Self operator-(difference_type __n) const {
        _Self __tmp(*this);
        return __tmp -= __n;
    }
    bool operator==(const _Self& __y) const {
      __stl_debug_check(__check_same_owner_or_null(*this, __y));
      return _Get_iterator()==__y._Get_iterator();
    }
    bool operator!=(const _Self& __y ) const {
      __stl_debug_check(__check_same_owner_or_null(*this, __y));
      return _Get_iterator()!=__y._Get_iterator();
    }
    bool operator<(const _Self& __y ) const {
      __stl_debug_check(__check_same_owner(*this, __y));
      return _Get_iterator()<__y._Get_iterator();
    }
    reference operator[](difference_type __n) const { return *(*this + __n); }
};

template <class _Tp, class _Ref, class _Ptr>
inline _Vector_iterator<_Tp, _Ref, _Ptr> 
operator+(ptrdiff_t __n, const _Vector_iterator<_Tp, _Ref, _Ptr>& __it) {
    _Vector_iterator<_Tp, _Ref, _Ptr> __tmp(__it);
    return __tmp += __n;
}

#  if !defined (__STL_CLASS_PARTIAL_SPECIALIZATION)
template <class _Tp, class _Ref, class _Ptr>
inline _Tp* 
value_type(const  _Vector_iterator<_Tp, _Ref, _Ptr>&) { return (_Tp*) 0; }
template <class _Tp, class _Ref, class _Ptr>
inline ptrdiff_t* 
distance_type(const  _Vector_iterator<_Tp, _Ref, _Ptr>&) { return (ptrdiff_t*) 0; }
template <class _Tp, class _Ref, class _Ptr>
inline random_access_iterator_tag
iterator_category(const _Vector_iterator<_Tp, _Ref, _Ptr>&) { 
    return random_access_iterator_tag();
}
#  endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _Tp,  class _Ref, class _Ptr>
bool __Dereferenceable(const  _Vector_iterator<_Tp, _Ref, _Ptr>& __that) {
    __stl_verbose_return(__that._Valid(), __STL_MSG_INVALID_ITERATOR);
    _Tp* const * __start = (_Tp* const *)(__that._Owner()->_Owner());
    __stl_verbose_return((__that._Get_iterator() < *(__start+1)) && 
                         (__that._Get_iterator() >= *__start),
                          __STL_MSG_NOT_DEREFERENCEABLE);    
    return true;
}

template <class _Tp,  class _Ref, class _Ptr>
bool __Nonsingular(const  _Vector_iterator<_Tp, _Ref, _Ptr>& __that) {
  __stl_verbose_return(__that._Valid(), __STL_MSG_INVALID_ITERATOR);
  _Tp* const * __start = (_Tp* const *)(__that._Owner()->_Owner());
  __stl_verbose_return((__that._Get_iterator() <= *(__start+1)) && 
		       (__that._Get_iterator() >= *__start),
		       __STL_MSG_SINGULAR_ITERATOR);    
    return true;
}

# endif /* __STL_DEBUG */



// The vector base class serves two purposes.  First, its constructor
// and destructor allocate (but don't initialize) storage.  This makes
// exception safety easier.  Second, the base class encapsulates all of
// the differences between SGI-style allocators and standard-conforming
// allocators.

#ifdef __STL_USE_STD_ALLOCATORS

// Base class for ordinary allocators.
template <class _Tp, class _Allocator, bool _IsStatic>
class _Vector_alloc_base {
public:
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
          allocator_type;
  allocator_type get_allocator() const { return _M_data_allocator; }

  _Vector_alloc_base(const allocator_type& __a)
    : _M_data_allocator(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0) 
  {}
  
protected:
  allocator_type _M_data_allocator;
  _Tp* _M_start;
  _Tp* _M_finish;
  _Tp* _M_end_of_storage;

  _Tp* _M_allocate(size_t __n)
    { return _M_data_allocator.allocate(__n); }
  void _M_deallocate(_Tp* __p, size_t __n)
    { if (__p) _M_data_allocator.deallocate(__p, __n); }
};

// Specialization for allocators that have the property that we don't
// actually have to store an allocator object.  
template <class _Tp, class _Allocator>
class _Vector_alloc_base<_Tp, _Allocator, true> {
public:
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
          allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Vector_alloc_base(const allocator_type&)
    : _M_start(0), _M_finish(0), _M_end_of_storage(0) 
  {}
  
protected:
  _Tp* _M_start;
  _Tp* _M_finish;
  _Tp* _M_end_of_storage;

  typedef typename _Alloc_traits<_Tp, _Allocator>::_Alloc_type _Alloc_type;
  _Tp* _M_allocate(size_t __n)
    { return _Alloc_type::allocate(__n); }
  void _M_deallocate(_Tp* __p, size_t __n)
    { _Alloc_type::deallocate(__p, __n);}
};

template <class _Tp, class _Alloc>
struct _Vector_base
  : public _Vector_alloc_base<_Tp, _Alloc,
                              _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
{
protected:
#if defined( __STL_HAS_NAMESPACES )
  __STL_USING_BASE_MEMBER _Vector_alloc_base<_Tp, _Alloc, 
                             _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_allocate;
  __STL_USING_BASE_MEMBER _Vector_alloc_base<_Tp, _Alloc, 
                             _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_deallocate;
  __STL_USING_BASE_MEMBER _Vector_alloc_base<_Tp, _Alloc, 
                             _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_start;
  __STL_USING_BASE_MEMBER _Vector_alloc_base<_Tp, _Alloc, 
                             _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_finish;
  __STL_USING_BASE_MEMBER _Vector_alloc_base<_Tp, _Alloc, 
                             _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_end_of_storage;
#endif /* __STL_HAS_NAMESPACES */
public:
  typedef _Vector_alloc_base<_Tp, _Alloc, 
                             _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
          _Base;
  typedef typename _Base::allocator_type allocator_type;

  _Vector_base(const allocator_type& __a) : _Base(__a) {}
  _Vector_base(size_t __n, const allocator_type& __a) : _Base(__a) {
    _M_start = _M_allocate(__n);
    _M_finish = _M_start;
    _M_end_of_storage = _M_start + __n;
  }

  ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }
};    

#else /* __STL_USE_STD_ALLOCATORS */

template <class _Tp, class _Alloc> 
class _Vector_base {
public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Vector_base(const _Alloc&)
    : _M_start(0), _M_finish(0), _M_end_of_storage(0) {
  }
  _Vector_base(size_t __n, const _Alloc&)
    : _M_start(0), _M_finish(0), _M_end_of_storage(0) 
  {
    _M_start = _M_allocate(__n);
    _M_finish = _M_start;
    _M_end_of_storage = _M_start + __n;
  }

  ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }

protected:
  _Tp* _M_start;
  _Tp* _M_finish;
  _Tp* _M_end_of_storage;

  typedef simple_alloc<_Tp, _Alloc> _M_data_allocator;
  _Tp* _M_allocate(size_t __n)
    { return _M_data_allocator::allocate(__n); }
  void _M_deallocate(_Tp* __p, size_t __n) 
    { _M_data_allocator::deallocate(__p, __n); }
};

#endif /* __STL_USE_STD_ALLOCATORS */

template <class _Tp, __STL_DEFAULT_ALLOCATOR_SELECT(_Tp)>
class vector : protected _Vector_base<_Tp, _Alloc> 
{
private:
  typedef _Vector_base<_Tp, _Alloc> _Base;
public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
# if defined (__STL_DEBUG)
  typedef _Vector_iterator<_Tp,_Tp&, pointer> iterator;
  typedef _Vector_iterator<_Tp,const _Tp&, const_pointer> const_iterator;
private:
  mutable __owned_list _M_iter_list;
# else
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
# endif
public:
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }
#if defined ( __STL_CLASS_PARTIAL_SPECIALIZATION ) && \
! defined (__STL_PARTIAL_SPECIALIZATION_BUG)
  typedef __STD::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef __STD::reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
# if defined (__STL_MSVC50_COMPATIBILITY)
  typedef __STD::reverse_iterator<const_iterator, value_type, const_reference, 
    const_pointer, difference_type>  const_reverse_iterator;
  typedef __STD::reverse_iterator<iterator, value_type, reference, pointer, difference_type>
    reverse_iterator;
# else
  typedef __STD::reverse_iterator<const_iterator, value_type, const_reference, 
    difference_type>  const_reverse_iterator;
  typedef __STD::reverse_iterator<iterator, value_type, reference, difference_type>
    reverse_iterator;
# endif
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

protected:
#if defined( __STL_HAS_NAMESPACES )
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_allocate;
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_deallocate;
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_start;
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_finish;
  __STL_USING_BASE_MEMBER _Vector_base<_Tp, _Alloc>::_M_end_of_storage;
#endif /* __STL_HAS_NAMESPACES */


protected:
  void _M_insert_aux(pointer __position, const _Tp& __x);
  void _M_insert_aux(pointer __position);

public:
  pointer _Begin_ptr() { return _M_start; }
  const_pointer _Begin_ptr() const { return _M_start; }
  pointer _End_ptr() { return _M_finish; }
  const_pointer _End_ptr() const { return _M_finish; }
# if defined (__STL_DEBUG)
  iterator begin() { return _Make_iterator(_M_start); }
  const_iterator begin() const { return _Make_const_iterator(_M_start); }
  iterator end() { return _Make_iterator(_M_finish); }
  const_iterator end() const { return _Make_const_iterator(_M_finish); }
  void _Invalidate_range(const iterator& __first, const iterator& __last) {
    __invalidate_range(&_M_iter_list, __first, __last);
  }
# else
  iterator begin() { return _M_start; }
  const_iterator begin() const { return _M_start; }
  iterator end() { return _M_finish; }
  const_iterator end() const { return _M_finish; }
# endif

  reverse_iterator rbegin()
    { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const
    { return const_reverse_iterator(end()); }
  reverse_iterator rend()
    { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

  size_type size() const
    { return size_type(_End_ptr() - _Begin_ptr()); }
  size_type max_size() const
    { return size_type(-1) / sizeof(_Tp); }
  size_type capacity() const
    { return size_type(_M_end_of_storage - _Begin_ptr()); }
  bool empty() const
    { return _Begin_ptr() == _End_ptr(); }

  reference operator[](size_type __n) { return *(begin() + __n); }
  const_reference operator[](size_type __n) const { return *(begin() + __n); }

#ifdef __STL_THROW_RANGE_ERRORS
  void _M_range_check(size_type __n) const {
    if (__n >= this->size())
      __stl_throw_range_error("vector");
  }

  reference at(size_type __n)
    { _M_range_check(__n); return (*this)[__n]; }
  const_reference at(size_type __n) const
    { _M_range_check(__n); return (*this)[__n]; }
#endif /* __STL_THROW_RANGE_ERRORS */

  explicit vector(const __STL_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__STL_ALLOC_PARAM))
    : _Vector_base<_Tp, _Alloc>(__a) {
        __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
  }

  vector(size_type __n, const _Tp& __value) 
    : _Vector_base<_Tp, _Alloc>(__n, allocator_type()) { 
      _M_finish = uninitialized_fill_n(_M_start, __n, __value); 
      __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
    }

  vector(size_type __n, const _Tp& __value,
         const allocator_type& __a) 
    : _Vector_base<_Tp, _Alloc>(__n, __a) { 
      _M_finish = uninitialized_fill_n(_M_start, __n, __value); 
      __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
  }

  explicit vector(size_type __n)
    : _Vector_base<_Tp, _Alloc>(__n, allocator_type()) { 
      _M_finish = uninitialized_fill_n(_M_start, __n, _Tp()); 
      __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
    }

  vector(const vector<_Tp, _Alloc>& __x) 
    : _Vector_base<_Tp, _Alloc>(__x.size(), __x.get_allocator()) { 
      _M_finish = uninitialized_copy(__x._Begin_ptr(), __x._End_ptr(), _M_start);
      __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
    }

#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
         const __STL_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__STL_ALLOC_PARAM)) : _Vector_base<_Tp, _Alloc>(__a) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_initialize_aux(__first, __last, _Integral());
    __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
  }

  template <class _Integer>
  void _M_initialize_aux(_Integer __n, _Integer __value, __true_type) {
    _M_start = _M_allocate(__n);
    _M_end_of_storage = _M_start + __n; 
    _M_finish = uninitialized_fill_n(_M_start, __n, __value);
  }

  template <class _InputIterator>
  void _M_initialize_aux(_InputIterator __first, _InputIterator __last,
                         __false_type) {
    _M_range_initialize(__first, __last, __ITERATOR_CATEGORY(__first));
  }

#else
  vector(const _Tp* __first, const _Tp* __last,
         const __STL_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__STL_ALLOC_PARAM))
    : _Vector_base<_Tp, _Alloc>(__last - __first, __a) { 
      _M_finish = uninitialized_copy(__first, __last, _M_start); 
      __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
  }
# ifdef __STL_DEBUG
  // mysterious VC++ bug
  vector(const_iterator __first, const_iterator __last)
    : _Vector_base<_Tp, _Alloc>(__last - __first, 
				__STL_ALLOC_INSTANCE(allocator_type)) { 
    _M_finish = uninitialized_copy(_Make_ptr(__first), _Make_ptr(__last), _M_start); 
    __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
  }
  vector(const_iterator __first, const_iterator __last , const __STL_ALLOC_PARAM& __a)
    : _Vector_base<_Tp, _Alloc>(__last - __first, __a) { 
    _M_finish = uninitialized_copy(_Make_ptr(__first), _Make_ptr(__last), _M_start); 
    __stl_debug_do(_M_iter_list._Safe_init(&_M_start));
  }
# endif
#endif /* __STL_MEMBER_TEMPLATES */

  ~vector() { destroy(_M_start, _M_finish); }

  vector<_Tp, _Alloc>& operator=(const vector<_Tp, _Alloc>& __x);

  void reserve(size_type __n) {
    if (capacity() < __n) {
      const size_type __old_size = size();
      pointer __tmp = _M_allocate_and_copy(__n, _M_start, _M_finish);
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __tmp;
      _M_finish = __tmp + __old_size;
      _M_end_of_storage = _M_start + __n;
    }
  }

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
		     forward_iterator_tag) {
    size_type __len = 0;
    distance(__first, __last, __len);
    
    if (__len > capacity()) {
      iterator __tmp = _M_allocate_and_copy(__len, __first, __last);
    destroy(_M_start, _M_finish);
    _M_deallocate(_M_start, _M_end_of_storage - _M_start);
    _M_start = __tmp;
    _M_end_of_storage = _M_finish = _M_start + __len;
    }
    else if (size() >= __len) {
      iterator __new_finish = copy(__first, __last, _M_start);
      destroy(__new_finish, _M_finish);
      _M_finish = __new_finish;
    }
    else {
    _ForwardIter __mid = __first;
    advance(__mid, size());
    copy(__first, __mid, _M_start);
    _M_finish = uninitialized_copy(__mid, __last, _M_finish);
    }
  }
#endif /* __STL_MEMBER_TEMPLATES */

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  void push_back(const _Tp& __x) {
    if (_M_finish != _M_end_of_storage) {
      construct(_M_finish, __x);
      ++_M_finish;
    }
    else
      _M_insert_aux(_End_ptr(), __x);
  }

  void push_back() {
    if (_M_finish != _M_end_of_storage) {
      construct(_M_finish);
      ++_M_finish;
    }
    else
      _M_insert_aux(_End_ptr());
  }

  void swap(vector<_Tp, _Alloc>& __x) {
    __stl_debug_do(_M_iter_list._Swap_owners(__x._M_iter_list));
    __STD::swap(_M_start, __x._M_start);
    __STD::swap(_M_finish, __x._M_finish);
    __STD::swap(_M_end_of_storage, __x._M_end_of_storage);
  }

  iterator insert(iterator __position, const _Tp& __x) {
    __stl_debug_check(__check_if_owner(&_M_iter_list, __position));
    size_type __n = __position - begin();
    if (_M_finish != _M_end_of_storage && __position == end()) {
      construct(_M_finish, __x);
      ++_M_finish;
    }
    else
      _M_insert_aux(_Make_ptr(__position), __x);
    return begin() + __n;
  }

  iterator insert(iterator __position) {
    __stl_debug_check(__check_if_owner(&_M_iter_list, __position));
    size_type __n = __position - begin();
    if (_M_finish != _M_end_of_storage && __position == end()) {
      construct(_M_finish);
      ++_M_finish;
    }
    else
      _M_insert_aux(_Make_ptr(__position));
    return begin() + __n;
  }

#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

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

#else /* __STL_MEMBER_TEMPLATES */
  void insert(iterator __position,
              const_iterator __first, const_iterator __last)
# if defined ( __STL_DEBUG )
    {    
        __stl_debug_check(__check_range(__first,__last));
        insert(__position, _Make_ptr(__first), _Make_ptr(__last));
    }
    void insert (iterator __position, const_pointer __first, 
                 const_pointer __last);
# else
    ;
# endif /* __STL_DEBUG */
#endif /* __STL_MEMBER_TEMPLATES */

  void insert (iterator __pos, size_type __n, const _Tp& __x)
    { _M_fill_insert(__pos, __n, __x); }

  void _M_fill_insert (iterator __pos, size_type __n, const _Tp& __x);

  void pop_back() {
    __stl_verbose_assert(!empty(), __STL_MSG_EMPTY_CONTAINER);
    --_M_finish;
    __stl_debug_do(__invalidate_iterator(&_M_iter_list,_M_finish,iterator()));
    destroy(_M_finish);
  }
  iterator erase(iterator __position) {
    __stl_debug_check(__check_if_owner(&_M_iter_list, __position));
    __stl_verbose_assert(_Make_ptr(__position)!=_M_finish,__STL_MSG_ERASE_PAST_THE_END);
    if (__position + 1 != end())
      copy(_Make_ptr(__position) + 1, _M_finish, _Make_ptr(__position));
    __stl_debug_do(_Invalidate_range(__position,end()));
    --_M_finish;
    destroy(_M_finish);
    return __position;
  }
  iterator erase(iterator __first, iterator __last) {
    __stl_debug_check(__check_range(__first,__last,begin(), end()));
    pointer __i = copy(_Make_ptr(__last), _M_finish, _Make_ptr(__first));
    destroy(__i, _M_finish);
    __stl_debug_do(_Invalidate_range(__first,end()));
    _M_finish = __i;
    return _Make_iterator(_Make_ptr(__first));
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
    pointer __result = _M_allocate(__n);
    __STL_TRY {
      uninitialized_copy(__first, __last, __result);
      return __result;
    } 
    __STL_UNWIND(_M_deallocate(__result, __n));
# if __STL_THROW_RETURN_BUG
	return __result;
# endif
  } 
#else /* __STL_MEMBER_TEMPLATES */
  pointer _M_allocate_and_copy(size_type __n, const_pointer __first, 
			       const_pointer __last)
  {
    pointer __result = _M_allocate(__n);
    __STL_TRY {
      uninitialized_copy(__first, __last, __result);
      return __result;
    }
    __STL_UNWIND(_M_deallocate(__result, __n));
# if __STL_THROW_RETURN_BUG
	return __result;
# endif
  }
#endif /* __STL_MEMBER_TEMPLATES */

#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  void _M_range_initialize(_InputIterator __first,  
                           _InputIterator __last, input_iterator_tag)
  {
    __stl_debug_check(__check_range(__first,__last));
    for ( ; __first != __last; ++__first)
      push_back(*__first);
  }

  // This function is only called by the constructor. 
  template <class _ForwardIterator>
  void _M_range_initialize(_ForwardIterator __first,
                           _ForwardIterator __last, forward_iterator_tag)
  {
    __stl_debug_check(__check_range(__first,__last));
    size_type __n = 0;
    distance(__first, __last, __n);
    _M_start = _M_allocate(__n);
    _M_end_of_storage = _M_start + __n;
    _M_finish = uninitialized_copy(__first, __last, _M_start);
  }

  template <class _InputIterator>
  void _M_range_insert(iterator __pos, 
		       _InputIterator __first, 
		       _InputIterator __last,
		       input_iterator_tag)
	{
	  __stl_debug_check(__check_range(__first,__last));
	  for ( ; __first != __last; ++__first) {
	    __pos = insert(__pos, *__first);
	    ++__pos;
	  }
	}

template <class _ForwardIterator>
# ifdef __STL_DEBUG
void _M_range_insert(__iterator__ __pos,
		     _ForwardIterator __first,
		     _ForwardIterator __last,
		     forward_iterator_tag) {
  __stl_debug_check(__check_if_owner(&_M_iter_list, __pos));
  pointer __position(_Make_ptr(__pos));
# else
  void _M_range_insert(__iterator__ __position,
					 _ForwardIterator __first,
					 _ForwardIterator __last,
					 forward_iterator_tag) {
# endif

    if (__first != __last) {
      __stl_debug_check(__check_range(__first,__last));
      size_type __n = 0;
      distance(__first, __last, __n);
      if (size_type(_M_end_of_storage - _M_finish) >= __n) {
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
	__stl_debug_do(_Invalidate_range(__pos,end()));
      }
      else {
	const size_type __old_size = size();
	const size_type __len = __old_size + max(__old_size, __n);
	pointer __new_start = _M_allocate(__len);
	pointer __new_finish = __new_start;
	__STL_TRY {
	  __new_finish = uninitialized_copy(_M_start, __position, __new_start);
	  __new_finish = uninitialized_copy(__first, __last, __new_finish);
	  __new_finish
	    = uninitialized_copy(__position, _M_finish, __new_finish);
	}
	__STL_UNWIND((destroy(__new_start,__new_finish), 
		      _M_deallocate(__new_start,__len)));
	destroy(_M_start, _M_finish);
	_M_deallocate(_M_start, _M_end_of_storage - _M_start);
	_M_start = __new_start;
	_M_finish = __new_finish;
	_M_end_of_storage = __new_start + __len;
      }
    }
  }
#endif /* __STL_MEMBER_TEMPLATES */
};

template <class _Tp, class _Alloc>
inline bool 
operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
{
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Tp, class _Alloc>
inline bool 
operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(), 
                                 __y.begin(), __y.end());
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Tp, class _Alloc>
inline void swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
{
  __x.swap(__y);
}

template <class _Tp, class _Alloc>
inline bool
operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__x == __y);
}

template <class _Tp, class _Alloc>
inline bool
operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return __y < __x;
}

template <class _Tp, class _Alloc>
inline bool
operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__y < __x);
}

template <class _Tp, class _Alloc>
inline bool
operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__x < __y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

template <class _Tp, class _Alloc>
vector<_Tp,_Alloc>& 
vector<_Tp,_Alloc>::operator=(const vector<_Tp, _Alloc>& __x)
{
  if (&__x != this) {
    const size_type __xlen = __x.size();
    __stl_debug_do(_M_iter_list._Invalidate_all());
    if (__xlen > capacity()) {
      pointer __tmp = _M_allocate_and_copy(__xlen, __x._Begin_ptr(), __x._End_ptr());
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __tmp;
      _M_end_of_storage = _M_start + __xlen;
    }
    else if (size() >= __xlen) {
      pointer __i = copy(__x._Begin_ptr(), __x._End_ptr(), _Begin_ptr());
      destroy(__i, _M_finish);
    }
    else {
      copy(__x._Begin_ptr(), __x._Begin_ptr() + size(), _M_start);
      uninitialized_copy(__x._Begin_ptr() + size(), __x._End_ptr(), _M_finish);
    }
    _M_finish = _M_start + __xlen;
  }
  return *this;
}

template <class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_assign(size_t __n, const _Tp& __val) {
  if (__n > capacity()) {
    vector<_Tp, _Alloc> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  }
  else if (__n > size()) {
    fill(begin(), end(), __val);
    _M_finish = uninitialized_fill_n(_M_finish, __n - size(), __val);
  }
  else
    erase(fill_n(begin(), __n, __val), end());
}

template <class _Tp, class _Alloc>
void 
vector<_Tp, _Alloc>::_M_insert_aux(_Tp* __position, const _Tp& __x)
{
  if (_M_finish != _M_end_of_storage) {
    construct(_M_finish, *(_M_finish - 1));
    ++_M_finish;
    _Tp __x_copy = __x;
    copy_backward(__position, _M_finish - 2, _M_finish - 1);
    *__position = __x_copy;
  }
  else {
    const size_type __old_size = size();
    const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
    pointer __new_start = _M_allocate(__len);
    pointer __new_finish = __new_start;
    __STL_TRY {
      __new_finish = uninitialized_copy(_M_start, __position, __new_start);
      construct(__new_finish, __x);
      ++__new_finish;
      __new_finish = uninitialized_copy(__position, _M_finish, __new_finish);
    }
    __STL_UNWIND((destroy(__new_start,__new_finish), 
                  _M_deallocate(__new_start,__len)));
    destroy(_Begin_ptr(), _End_ptr());
    _M_deallocate(_M_start, _M_end_of_storage - _M_start);
    _M_start = __new_start;
    _M_finish = __new_finish;
    _M_end_of_storage = __new_start + __len;
  }
}

template <class _Tp, class _Alloc>
void 
vector<_Tp, _Alloc>::_M_insert_aux(_Tp* __position)
{
  if (_M_finish != _M_end_of_storage) {
    construct(_M_finish, *(_M_finish - 1));
    ++_M_finish;
    copy_backward(__position, _M_finish - 2, _M_finish - 1);
    *__position = _Tp();
  }
  else {
    const size_type __old_size = size();
    const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
    pointer __new_start = _M_allocate(__len);
    pointer __new_finish = __new_start;
    __STL_TRY {
      __new_finish = uninitialized_copy(_M_start, __position, __new_start);
      construct(__new_finish);
      ++__new_finish;
      __new_finish = uninitialized_copy(__position, _M_finish, __new_finish);
    }
    __STL_UNWIND((destroy(__new_start,__new_finish), 
                  _M_deallocate(__new_start,__len)));
    destroy(begin(), end());
    _M_deallocate(_M_start, _M_end_of_storage - _M_start);
    _M_start = __new_start;
    _M_finish = __new_finish;
    _M_end_of_storage = __new_start + __len;
  }
}

template <class _Tp, class _Alloc>
# if defined ( __STL_DEBUG )
void vector<_Tp, _Alloc>::_M_fill_insert(__iterator__ __pos, __size_type__ __n, 
                                 const _Tp& __x) {
    __stl_debug_check(__check_if_owner(&_M_iter_list, __pos));
    pointer __position=_Make_ptr(__pos);
# else
void vector<_Tp, _Alloc>::_M_fill_insert(__iterator__ __position, __size_type__ __n, 
                                 const _Tp& __x) {
# endif
  if (__n != 0) {
    if (size_type(_M_end_of_storage - _M_finish) >= __n) {
      _Tp __x_copy = __x;
      const size_type __elems_after = _M_finish - __position;
      pointer __old_finish = _M_finish;
      if (__elems_after > __n) {
        uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
        _M_finish += __n;
        copy_backward(__position, __old_finish - __n, __old_finish);
        fill(__position, __position + __n, __x_copy);
      }
      else {
        uninitialized_fill_n(_M_finish, __n - __elems_after, __x_copy);
        _M_finish += __n - __elems_after;
        uninitialized_copy(__position, __old_finish, _M_finish);
        _M_finish += __elems_after;
        fill(__position, __old_finish, __x_copy);
      }
      __stl_debug_do(_Invalidate_range(__pos,end()));
    }
    else {
      const size_type __old_size = size();        
      const size_type __len = __old_size + max(__old_size, __n);
      pointer __new_start = _M_allocate(__len);
      pointer __new_finish = __new_start;
      __STL_TRY {
        __new_finish = uninitialized_copy(_M_start, __position, __new_start);
        __new_finish = uninitialized_fill_n(__new_finish, __n, __x);
        __new_finish
          = uninitialized_copy(__position, _M_finish, __new_finish);
      }
      __STL_UNWIND((destroy(__new_start,__new_finish), 
                    _M_deallocate(__new_start,__len)));
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __new_start;
      _M_finish = __new_finish;
      _M_end_of_storage = __new_start + __len;
    }
  }
}

#ifndef __STL_MEMBER_TEMPLATES
template <class _Tp, class _Alloc>
# if defined ( __STL_DEBUG )
void 
vector<_Tp, _Alloc>::insert(__iterator__ __pos, 
                            __const_pointer__ __first, 
                            __const_pointer__ __last) {
  __stl_debug_check(__check_if_owner(&_M_iter_list, __pos));
  pointer __position=_Make_ptr(__pos);
# else
void 
vector<_Tp, _Alloc>::insert(__iterator__ __position, 
                            __const_iterator__ __first, 
                            __const_iterator__ __last) {
# endif
  
  if (__first != __last) {
    size_type __n = 0;
    distance(__first, __last, __n);
    if (size_type(_M_end_of_storage - _M_finish) >= __n) {
      const size_type __elems_after = _M_finish - __position;
      pointer __old_finish = _M_finish;
      if (__elems_after > __n) {
        uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
        _M_finish += __n;
        copy_backward(__position, __old_finish - __n, __old_finish);
        copy(__first, __last, __position);
      }
      else {
        uninitialized_copy(__first + __elems_after, __last, _M_finish);
        _M_finish += __n - __elems_after;
        uninitialized_copy(__position, __old_finish, _M_finish);
        _M_finish += __elems_after;
        copy(__first, __first + __elems_after, __position);
      }
      __stl_debug_do(_Invalidate_range(__pos,end()));
    }
    else {
      const size_type __old_size = size();
      const size_type __len = __old_size + max(__old_size, __n);
      pointer __new_start = _M_allocate(__len);
      pointer __new_finish = __new_start;
      __STL_TRY {
        __new_finish = uninitialized_copy(_M_start, __position, __new_start);
        __new_finish = uninitialized_copy(__first, __last, __new_finish);
        __new_finish
          = uninitialized_copy(__position, _M_finish, __new_finish);
      }
      __STL_UNWIND((destroy(__new_start,__new_finish),
                    _M_deallocate(__new_start,__len)));
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __new_start;
      _M_finish = __new_finish;
      _M_end_of_storage = __new_start + __len;
    }
  }
}

#endif /* __STL_MEMBER_TEMPLATES */

// do a cleanup
# undef  vector
# undef  __iterator__
# undef  __const_iterator__
# undef _Make_iterator
# undef _Make_const_iterator
# undef _Make_ptr

#  undef __vector__
// provide a uniform way to access full funclionality
#  define __vector__ __FULL_NAME(vector)

# if defined (__STL_USE_WRAPPER_FOR_ALLOC_PARAM)
// provide a "default" vector adaptor
template <class _Tp>
class vector : public __vector__<_Tp, __STL_DEFAULT_ALLOCATOR(_Tp) >
{
public:
#   define _VEC_SUPER __vector__<_Tp, __STL_DEFAULT_ALLOCATOR(_Tp) >
    typedef _VEC_SUPER  _Super;
    __IMPORT_WITH_REVERSE_ITERATORS(_Super)
    __IMPORT_SUPER_COPY_ASSIGNMENT(vector, vector<_Tp>, _VEC_SUPER)
    vector() {}
    explicit vector(size_type __n, const _Tp& __value) : _VEC_SUPER(__n, __value) { }
    explicit vector(size_type __n) : _VEC_SUPER(__n) { }
# if defined ( __STL_DEBUG )
    vector(const value_type* __first, const value_type* __last) : _VEC_SUPER(__first,__last) { }
# endif
    vector(const_iterator __first, const_iterator __last) : _VEC_SUPER(__first,__last) { }
    ~vector() {}
};

#  if defined (__STL_BASE_MATCH_BUG)
template <class _Tp>
    inline bool operator==(const vector<_Tp>& __x, const vector<_Tp>& __y) {
    typedef  __vector__<_Tp,alloc> _Super;
    return operator == ((const _Super&)__x,(const _Super&)__y);
}

template <class _Tp>
    inline bool operator<(const vector<_Tp>& __x, const vector<_Tp>& __y) {
    typedef  __vector__<_Tp,alloc> _Super;
    return operator < ((const _Super&)__x,(const _Super&)__y);
}
#  endif /* __STL_BASE_MATCH_BUG */
#  undef _VEC_SUPER
# endif /* __STL_DEFAULT_TEMPLATE_PARAM */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#pragma reset woff 1375
#endif

// cleanup
# undef  __pointer__
# undef  __const_pointer__
# undef  __size_type__
# undef  __difference_type__

// close std namespace
__STL_END_NAMESPACE

#endif /* __SGI_STL_VECTOR_H */

// Local Variables:
// mode:C++
// End:
