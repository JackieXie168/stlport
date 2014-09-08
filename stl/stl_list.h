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

#ifndef __SGI_STL_INTERNAL_LIST_H
#define __SGI_STL_INTERNAL_LIST_H

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#pragma set woff 1375
#endif


#  define  list  __WORKAROUND_RENAME(list)

# if defined ( __STL_USE_ABBREVS )
#  define __list_iterator         _L__It
# endif

template <class _Tp, __STL_DEFAULT_ALLOCATOR_SELECT(_Tp) >
class list;

template <class _Tp>
struct _List_node {
  typedef void* _Void_pointer;
  _Void_pointer _M_next;
  _Void_pointer _M_prev;
  _Tp _M_data;
};

template<class _Tp, class _Ref, class _Ptr>
# if defined ( __STL_DEBUG )
struct _List_iterator : public __owned_link {
# else
struct _List_iterator {
# endif
  typedef _List_iterator<_Tp,_Tp&,_Tp*>             iterator;
  typedef _List_iterator<_Tp,const _Tp&,const _Tp*> const_iterator;
  typedef _List_iterator<_Tp,_Ref,_Ptr>             _Self;

  typedef bidirectional_iterator_tag iterator_category;
  typedef _Tp value_type;
  typedef _Ptr pointer;
  typedef _Ref reference;
  typedef _List_node<_Tp> _Node;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  _Node* _M_node;

# if defined ( __STL_DEBUG )
  _Node* _Get_iterator() const { return _M_node; }  
  _Node* _Owner_node() const {
      const __owned_list* __ptr = _Owner();
      return __ptr ? (_Node*)__ptr->_Owner() : (_Node*)0; 
  }
  _List_iterator(const __owned_list* __root, _Node* __x) : 
    __owned_link(__root), _M_node(__x) {}
  _List_iterator() : __owned_link(0) {}
  _List_iterator(const iterator& __x) : __owned_link(__x), _M_node(__x._M_node) {}
# else
  _List_iterator(_Node* __x) : _M_node(__x) {}
  _List_iterator() {}
  _List_iterator(const iterator& __x) : _M_node(__x._M_node) {}
# endif

  bool operator==(const _Self& __x) const { 
    __stl_debug_check(__check_same_owner_or_null(*this,__x));                         
    return _M_node == __x._M_node; 
  }
  bool operator!=(const _Self& __x) const { 
    __stl_debug_check(__check_same_owner_or_null(*this,__x));                         
    return _M_node != __x._M_node; 
  }
  reference operator*() const { 
            __stl_verbose_assert(_Valid() && _M_node!=_Owner_node(), 
				 __STL_MSG_NOT_DEREFERENCEABLE); 
            return (*_M_node)._M_data; 
  }

#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  _Self& operator++() { 
    __stl_verbose_assert(_M_node!=_Owner_node(), __STL_MSG_INVALID_ADVANCE); 
    _M_node = (_Node*)(_M_node->_M_next);
    return *this;
  }
  _Self operator++(int) { 
    _Self __tmp = *this;
    ++*this;
    return __tmp;
  }
  _Self& operator--() { 
    _M_node = (_Node*)(_M_node->_M_prev);
    __stl_verbose_assert(_M_node!=_Owner_node(), __STL_MSG_INVALID_ADVANCE); 
    return *this;
  }
  _Self operator--(int) { 
    _Self __tmp = *this;
    --*this;
    return __tmp;
  }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _Tp, class _Ref, class _Ptr>
inline bidirectional_iterator_tag
iterator_category(const _List_iterator<_Tp, _Ref, _Ptr>&)
{
  return bidirectional_iterator_tag();
}

template <class _Tp, class _Ref, class _Ptr>
inline _Tp*
value_type(const _List_iterator<_Tp, _Ref, _Ptr>&)
{
  return 0;
}

template <class _Tp, class _Ref, class _Ptr>
inline ptrdiff_t*
distance_type(const _List_iterator<_Tp, _Ref, _Ptr>&)
{
  return 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */


// Base class that encapsulates details of allocators.  Three cases:
// an ordinary standard-conforming allocator, a standard-conforming
// allocator with no non-static data, and an SGI-style allocator.
// This complexity is necessary only because we're worrying about backward
// compatibility and because we want to avoid wasting storage on an 
// allocator instance if it isn't necessary.

#ifdef __STL_USE_STD_ALLOCATORS

// Base for general standard-conforming allocators.
template <class _Tp, class _Allocator, bool _IsStatic>
class _List_alloc_base {
public:
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
          allocator_type;
  allocator_type get_allocator() const { return _Node_allocator; }

  _List_alloc_base(const allocator_type& __a) : _Node_allocator(__a) {}

protected:
  _List_node<_Tp>* _M_get_node()
   { return _Node_allocator.allocate(1); }
  void _M_put_node(_List_node<_Tp>* __p)
    { _Node_allocator.deallocate(__p, 1); }

protected:
  typename _Alloc_traits<_List_node<_Tp>, _Allocator>::allocator_type
           _Node_allocator;
  _List_node<_Tp>* _M_node;
};

// Specialization for instanceless allocators.

template <class _Tp, class _Allocator>
class _List_alloc_base<_Tp, _Allocator, true> {
public:
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
          allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _List_alloc_base(const allocator_type&) {}

protected:
  typedef typename _Alloc_traits<_List_node<_Tp>, _Allocator>::_Alloc_type
          _Alloc_type;
  _List_node<_Tp>* _M_get_node() { return _Alloc_type::allocate(1); }
  void _M_put_node(_List_node<_Tp>* __p) { _Alloc_type::deallocate(__p, 1); }

public:
  _List_node<_Tp>* _M_node;
};

template <class _Tp, class _Alloc>
class _List_base 
  : public _List_alloc_base<_Tp, _Alloc,
                            _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
{
public:
  typedef _List_alloc_base<_Tp, _Alloc,
                           _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
          _Base; 
  typedef typename _Base::allocator_type allocator_type;

  _List_base(const allocator_type& __a) : _Base(__a) {
    _M_node = _M_get_node();
    _M_node->_M_next = _M_node;
    _M_node->_M_prev = _M_node;
    __stl_debug_do(_M_iter_list._Safe_init(_M_node));
  }
  ~_List_base() {
    clear();
    _M_put_node(_M_node);
  }

  void clear();
#if defined( __STL_HAS_NAMESPACES )
  __STL_USING_BASE_MEMBER _List_alloc_base<_Tp, _Alloc,
                            _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_node;
  __STL_USING_BASE_MEMBER _List_alloc_base<_Tp, _Alloc,
                            _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_put_node;
  __STL_USING_BASE_MEMBER _List_alloc_base<_Tp, _Alloc,
                            _Alloc_traits<_Tp, _Alloc>::_S_instanceless>::_M_get_node;
#endif /* __STL_HAS_NAMESPACES */
protected:
# if defined (__STL_DEBUG)
protected:
    mutable __owned_list _M_iter_list;
    void _Invalidate_all() { _M_iter_list._Invalidate_all();}
# endif

};

#else /* __STL_USE_STD_ALLOCATORS */

template <class _Tp, class _Alloc>
class _List_base 
{
public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _List_base(const allocator_type&) {
    _M_node = _M_get_node();
    _M_node->_M_next = _M_node;
    _M_node->_M_prev = _M_node;
    __stl_debug_do(_M_iter_list._Safe_init(_M_node));
  }
  ~_List_base() {
    clear();
    _M_put_node(_M_node);
  }

  void clear();

protected:
  typedef simple_alloc<_List_node<_Tp>, _Alloc> _Alloc_type;
  _List_node<_Tp>* _M_get_node() { return _Alloc_type::allocate(1); }
  void _M_put_node(_List_node<_Tp>* __p) { _Alloc_type::deallocate(__p, 1); } 

public:
  _List_node<_Tp>* _M_node;
# if defined (__STL_DEBUG)
protected:
    mutable __owned_list _M_iter_list;
    void _Invalidate_all() { _M_iter_list._Invalidate_all();}
# endif
};

#endif /* __STL_USE_STD_ALLOCATORS */

template <class _Tp, class _Alloc>
void 
_List_base<_Tp,_Alloc>::clear() 
{
  __stl_debug_do(_Invalidate_all());
  _List_node<_Tp>* __cur = (_List_node<_Tp>*) _M_node->_M_next;
  while (__cur != _M_node) {
    _List_node<_Tp>* __tmp = __cur;
    __cur = (_List_node<_Tp>*) __cur->_M_next;
    destroy(&__tmp->_M_data);
    _M_put_node(__tmp);
  }
  _M_node->_M_next = _M_node;
  _M_node->_M_prev = _M_node;
}

template <class _Tp, class _Alloc>
class list : protected _List_base<_Tp, _Alloc> {
  typedef _List_base<_Tp, _Alloc> _Base;
  typedef list<_Tp, _Alloc> _Self;
protected:
  typedef void* _Void_pointer;
public:      
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef _List_node<_Tp> _Node;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

public:
  typedef _List_iterator<_Tp,_Tp&,_Tp*>             iterator;
  typedef _List_iterator<_Tp,const _Tp&,const _Tp*> const_iterator;

#if defined ( __STL_CLASS_PARTIAL_SPECIALIZATION ) && \
! defined (__STL_PARTIAL_SPECIALIZATION_BUG)
    typedef __STD::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef __STD::reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
# if defined (__STL_MSVC50_COMPATIBILITY)
    typedef reverse_bidirectional_iterator<const_iterator, value_type,
                                           const_reference, const value_type*, difference_type>
            const_reverse_iterator;
    typedef reverse_bidirectional_iterator<iterator, value_type, reference,
                                           pointer, difference_type>
            reverse_iterator; 
# else
  typedef reverse_bidirectional_iterator<const_iterator,value_type,
                                         const_reference,difference_type>
          const_reverse_iterator;
  typedef reverse_bidirectional_iterator<iterator,value_type,reference,
                                         difference_type>
          reverse_iterator; 
# endif /* __STL_MSVC50_COMPATIBILITY */
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

protected:
#if defined( __STL_HAS_NAMESPACES )
  __STL_USING_BASE_MEMBER _List_base<_Tp, _Alloc>::_M_node;
  __STL_USING_BASE_MEMBER _List_base<_Tp, _Alloc>::_M_put_node;
  __STL_USING_BASE_MEMBER _List_base<_Tp, _Alloc>::_M_get_node;
#endif /* __STL_HAS_NAMESPACES */

protected:
  _Node* _M_create_node(const _Tp& __x)
  {
    _Node* __p = _M_get_node();
    __STL_TRY {
      construct(&__p->_M_data, __x);
    }
    __STL_UNWIND(_M_put_node(__p));
    return __p;
  }

  _Node* _M_create_node()
  {
    _Node* __p = _M_get_node();
    __STL_TRY {
      construct(&__p->_M_data);
    }
    __STL_UNWIND(_M_put_node(__p));
    return __p;
  }

public:
  explicit list(const __STL_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__STL_ALLOC_PARAM)) :
    _List_base<_Tp, _Alloc>(__a) {}

# if defined (__STL_DEBUG)
  iterator begin()             { return iterator(&_M_iter_list, (_Node*)(_M_node->_M_next)); }
  const_iterator begin() const { return const_iterator(&_M_iter_list, (_Node*)(_M_node->_M_next)); }

  iterator end()             { return iterator(&_M_iter_list, _M_node); }
  const_iterator end() const { return const_iterator(&_M_iter_list, _M_node); }

  void _Invalidate_iterator(const iterator& __it) { 
    __invalidate_iterator(&_M_iter_list, __it._M_node, __it); 
  }
  void _Invalidate_range(const iterator& __it1, const iterator& __it2) { 
    __invalidate_range(&_M_iter_list, __it1, __it2); 
  }
# else
  iterator begin()             { return iterator((_Node*)(_M_node->_M_next)); }
  const_iterator begin() const { return const_iterator((_Node*)(_M_node->_M_next)); }

  iterator end()             { return _M_node; }
  const_iterator end() const { return _M_node; }
# endif

  reverse_iterator rbegin() 
    { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const 
    { return const_reverse_iterator(end()); }

  reverse_iterator rend()
    { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

  bool empty() const { return _M_node->_M_next == _M_node; }
  size_type size() const {
    size_type __result = 0;
    distance(begin(), end(), __result);
    return __result;
  }
  size_type max_size() const { return size_type(-1); }

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }

  void swap(list<_Tp, _Alloc>& __x) {
    __stl_debug_do(_M_iter_list._Swap_owners(__x._M_iter_list, true));
    __STD::swap(_M_node, __x._M_node); 
  }

  iterator insert(iterator __position, const _Tp& __x) {
    __stl_debug_check(__check_if_owner(&_M_iter_list,__position));
    _Node* __tmp = _M_create_node(__x);
    __tmp->_M_next = __position._M_node;
    __tmp->_M_prev = __position._M_node->_M_prev;
    ((_Node*) (__position._M_node->_M_prev))->_M_next = __tmp;
    __position._M_node->_M_prev = __tmp;
#  if defined ( __STL_DEBUG )
      return iterator(&_M_iter_list,__tmp);
#  else
    return __tmp;
#  endif
  }

  iterator insert(iterator __position) { return insert(__position, _Tp()); }
#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.

  template<class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
                          __true_type) {
    _M_fill_insert(__pos, (size_type) __n, (_Tp) __x);
  }

  template <class _InputIter>
  void 
  _M_insert_dispatch(iterator __position,
		     _InputIter __first, _InputIter __last,
		     __false_type) {
    for ( ; __first != __last; ++__first)
      insert(__position, *__first);
  }

  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

#else /* __STL_MEMBER_TEMPLATES */
  void insert(iterator __position, const _Tp* __first, const _Tp* __last);
  void insert(iterator __position,
              const_iterator __first, const_iterator __last);
#endif /* __STL_MEMBER_TEMPLATES */
  void insert(iterator __pos, size_type __n, const _Tp& __x)
  { _M_fill_insert(__pos, __n, __x); }
  void _M_fill_insert(iterator __pos, size_type __n, const _Tp& __x);
 
  void push_front(const _Tp& __x) { insert(begin(), __x); }
  void push_front() {insert(begin());}
  void push_back(const _Tp& __x) { insert(end(), __x); }
  void push_back() {insert(end());}

  iterator erase(iterator __position) {
    __stl_debug_check(__check_if_owner(&_M_iter_list,__position));
    __stl_verbose_assert(__position._M_node!=_M_node, __STL_MSG_ERASE_PAST_THE_END);
    _Node* __next_node = (_Node*) (__position._M_node->_M_next);
    _Node* __prev_node = (_Node*) (__position._M_node->_M_prev);
    __prev_node->_M_next = __next_node;
    __next_node->_M_prev = __prev_node;
    __stl_debug_do(_Invalidate_iterator(__position));
    destroy(&__position._M_node->_M_data);
    _M_put_node(__position._M_node);
#  if defined ( __STL_DEBUG )
      return iterator(&_M_iter_list,__next_node);
#  else
      return iterator(__next_node);
#  endif
    }
  iterator erase(iterator __first, iterator __last);
  void clear() { _Base::clear(); }

  void resize(size_type __new_size, const _Tp& __x);
  void resize(size_type __new_size) { resize(__new_size, _Tp()); }

  void pop_front() { erase(begin()); }
  void pop_back() { 
    iterator __tmp = end();
    erase(--__tmp);
  }
  list(size_type __n, const _Tp& __value,
       const __STL_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__STL_ALLOC_PARAM))
    : _List_base<_Tp, _Alloc>(__a)
    { insert(begin(), __n, __value); }
  explicit list(size_type __n)
    : _List_base<_Tp, _Alloc>(allocator_type())
    { insert(begin(), __n, _Tp()); }

#ifdef __STL_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because insert does all of
  // that anyway.  
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last,
       const __STL_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__STL_ALLOC_PARAM))
    : _List_base<_Tp, _Alloc>(__a)
    { insert(begin(), __first, __last); }

#else /* __STL_MEMBER_TEMPLATES */

  list(const _Tp* __first, const _Tp* __last,
       const __STL_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__STL_ALLOC_PARAM))
    : _List_base<_Tp, _Alloc>(__a)
    { insert(begin(), __first, __last); }
  list(const_iterator __first, const_iterator __last,
       const __STL_ALLOC_PARAM& __a)
    : _List_base<_Tp, _Alloc>(__a)
    { insert(begin(), __first, __last); }
  list(const_iterator __first, const_iterator __last)
    : _List_base<_Tp, _Alloc>(allocator_type())
    { insert(begin(), __first, __last); }

#endif /* __STL_MEMBER_TEMPLATES */
  list(const list<_Tp, _Alloc>& __x) : _List_base<_Tp, _Alloc>(__x.get_allocator())
    { insert(begin(), __x.begin(), __x.end()); }

  ~list() { }

  list<_Tp, _Alloc>& operator=(const list<_Tp, _Alloc>& __x);

public:
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

  template <class _InputIterator>
  void _M_assign_dispatch(_InputIterator __first2, _InputIterator __last2,
                          __false_type) {
    iterator __first1 = begin();
    iterator __last1 = end();
    for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
      *__first1 = *__first2;
    if (__first2 == __last2)
      erase(__first1, __last1);
    else
      insert(__last1, __first2, __last2);
  }

#endif /* __STL_MEMBER_TEMPLATES */

protected:
  void transfer(iterator __position, iterator __first, iterator __last) {
    if (__position._M_node != __last._M_node) {
      // Remove [first, last) from its old position.
      ((_Node*) (__last._M_node->_M_prev))->_M_next     = __position._M_node;
      ((_Node*) (__first._M_node->_M_prev))->_M_next    = __last._M_node;
      ((_Node*) (__position._M_node->_M_prev))->_M_next = __first._M_node; 

      // Splice [first, last) into its new position.
      _Node* __tmp = (_Node*) (__position._M_node->_M_prev);
      __position._M_node->_M_prev = __last._M_node->_M_prev;
      __last._M_node->_M_prev      = __first._M_node->_M_prev; 
      __first._M_node->_M_prev    = __tmp;
    }
  }

public:
  void splice(iterator __position, _Self& __x) {
    __stl_verbose_assert(&__x!=this, __STL_MSG_INVALID_ARGUMENT);
    __stl_debug_check(__check_if_owner(&_M_iter_list,__position));
    if (!__x.empty()) 
      transfer(__position, __x.begin(), __x.end());
    __stl_debug_do(__x._Invalidate_all());
  }
# if defined ( __STL_DEBUG )
  void splice(iterator __position, _Self& __x, iterator __i) {
# else
  void splice(iterator __position, _Self&, iterator __i) {
# endif
    __stl_debug_check(__check_if_owner(&_M_iter_list,__position) &&
		      __check_if_owner(&__x._M_iter_list ,__i));
    __stl_verbose_assert(__i._M_node!=__i._Owner_node(), __STL_MSG_NOT_DEREFERENCEABLE); 
    iterator __j = __i;
    ++__j;
#  if defined ( __STL_DEBUG )
    if (( &__x == this ) && (__position == __i || __position == __j)) return;
#  else
    if (__position == __i || __position == __j) return;
#  endif
    transfer(__position, __i, __j);
    __stl_debug_do(__x._Invalidate_iterator(__i));
  }
#  if defined ( __STL_DEBUG )
  void splice(iterator __position, _Self& __x, iterator __first, iterator __last) {
    __stl_debug_check(__check_if_owner(&_M_iter_list, __position));
    __stl_verbose_assert(__first._Owner()==&__x._M_iter_list && __last._Owner()==&__x._M_iter_list, 
			 __STL_MSG_NOT_OWNER);
#  else
  void splice(iterator __position, _Self&, iterator __first, iterator __last) {
#  endif
    if (__first != __last) 
      transfer(__position, __first, __last);
  }
  void remove(const _Tp& __value);
  void unique();
  void merge(_Self& __x);
  void reverse();
  void sort();

#ifdef __STL_MEMBER_TEMPLATES
  template <class _Predicate>
    void remove_if(_Predicate __pred) {
    iterator __first = begin();
    iterator __last = end();
    while (__first != __last) {
      iterator __next = __first;
      ++__next;
      if (__pred(*__first)) erase(__first);
      __first = __next;
    }
  }

  template <class _BinaryPredicate>
    void unique(_BinaryPredicate __binary_pred) {
    iterator __first = begin();
    iterator __last = end();
    if (__first == __last) return;
    iterator __next = __first;
    while (++__next != __last) {
      if (__binary_pred(*__first, *__next))
	erase(__next);
      else
	__first = __next;
      __next = __first;
    }
  }

  template <class _StrictWeakOrdering>
    void merge(list<_Tp, _Alloc>& __x,
	  _StrictWeakOrdering __comp) {
    iterator __first1 = begin();
    iterator __last1 = end();
    iterator __first2 = __x.begin();
    iterator __last2 = __x.end();
    while (__first1 != __last1 && __first2 != __last2)
      if (__comp(*__first2, *__first1)) {
	iterator __next = __first2;
	transfer(__first1, __first2, ++__next);
	__first2 = __next;
      }
      else
	++__first1;
    if (__first2 != __last2) transfer(__last1, __first2, __last2);
  }

  template <class _StrictWeakOrdering>
    void sort(_StrictWeakOrdering __comp) {
    // Do nothing if the list has length 0 or 1.
    if (_M_node->_M_next != _M_node &&
	((_Node*) (_M_node->_M_next))->_M_next != _M_node) {
      list<_Tp, _Alloc> __carry;
      list<_Tp, _Alloc> __counter[64];
      int __fill = 0;
      while (!empty()) {
	__carry.splice(__carry.begin(), *this, begin());
	int __i = 0;
	while(__i < __fill && !__counter[__i].empty()) {
	  __counter[__i].merge(__carry, __comp);
	  __carry.swap(__counter[__i++]);
	}
	__carry.swap(__counter[__i]);         
	if (__i == __fill) ++__fill;
      } 

      for (int __i = 1; __i < __fill; ++__i) 
	__counter[__i].merge(__counter[__i-1], __comp);
      swap(__counter[__fill-1]);
    }
    __stl_debug_do(_Invalidate_all());
  }
#endif /* __STL_MEMBER_TEMPLATES */

};

template <class _Tp, class _Alloc>
INLINE_LOOP bool operator==(const list<_Tp,_Alloc>& __x,
                       const list<_Tp,_Alloc>& __y)
{
  typedef typename list<_Tp,_Alloc>::const_iterator const_iterator;
  const_iterator __end1 = __x.end();
  const_iterator __end2 = __y.end();

  const_iterator __i1 = __x.begin();
  const_iterator __i2 = __y.begin();
  while (__i1 != __end1 && __i2 != __end2 && *__i1 == *__i2) {
    ++__i1;
    ++__i2;
  }
  return __i1 == __end1 && __i2 == __end2;
}

template <class _Tp, class _Alloc>
inline bool operator<(const list<_Tp,_Alloc>& __x,
                      const list<_Tp,_Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(),
                                 __y.begin(), __y.end());
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Tp, class _Alloc>
inline void 
swap(list<_Tp, _Alloc>& __x, list<_Tp, _Alloc>& __y)
{
  __x.swap(__y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

# if defined (__STL_NESTED_TYPE_PARAM_BUG) 
#  define __iterator__   _List_iterator<_Tp, _Tp&, _Tp*>
#  define iterator       _List_iterator<_Tp, _Tp&, _Tp*>
#  define const_iterator _List_iterator<_Tp, const _Tp&, const _Tp*>
#  define size_type      size_t
# else
#  define __iterator__ __STL_TYPENAME_ON_RETURN_TYPE list<_Tp,_Alloc>::iterator
# endif


#ifdef __STL_MEMBER_TEMPLATES
#else /* __STL_MEMBER_TEMPLATES */

template <class _Tp, class _Alloc>
void 
list<_Tp, _Alloc>::insert(iterator __position, 
                          const _Tp* __first, const _Tp* __last)
{
  for ( ; __first != __last; ++__first)
    insert(__position, *__first);
}

template <class _Tp, class _Alloc>
void 
list<_Tp, _Alloc>::insert(iterator __position,
                         const_iterator __first, const_iterator __last)
{
  for ( ; __first != __last; ++__first)
    insert(__position, *__first);
}

#endif /* __STL_MEMBER_TEMPLATES */

template <class _Tp, class _Alloc>
void 
list<_Tp, _Alloc>::_M_fill_insert(iterator __position, size_type __n, const _Tp& __x)
{
  for ( ; __n > 0; --__n)
    insert(__position, __x);
}

template <class _Tp, class _Alloc>
__iterator__ list<_Tp, _Alloc>::erase(iterator __first, 
				      iterator __last)
{
  while (__first != __last)
    erase(__first++);
  return __last;
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::resize(size_type __new_size, const _Tp& __x)
{
  iterator __i = begin();
  size_type __len = 0;
  for ( ; __i != end() && __len < __new_size; ++__i, ++__len)
    ;
  if (__len == __new_size)
    erase(__i, end());
  else                          // __i == end()
    insert(end(), __new_size - __len, __x);
}

template <class _Tp, class _Alloc>
list<_Tp, _Alloc>& list<_Tp, _Alloc>::operator=(const list<_Tp, _Alloc>& __x)
{
  if (this != &__x) {
    iterator __first1 = begin();
    iterator __last1 = end();
    const_iterator __first2 = __x.begin();
    const_iterator __last2 = __x.end();
    while (__first1 != __last1 && __first2 != __last2) 
      *__first1++ = *__first2++;
    if (__first2 == __last2)
      erase(__first1, __last1);
    else
      insert(__last1, __first2, __last2);
  }
  __stl_debug_do(_Invalidate_all());
  return *this;
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::_M_fill_assign(size_type __n, const _Tp& __val) {
  iterator __i = begin();
  for ( ; __i != end() && __n > 0; ++__i, --__n)
    *__i = __val;
  if (__n > 0)
    insert(end(), __n, __val);
  else
    erase(__i, end());
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::remove(const _Tp& __value)
{
  iterator __first = begin();
  iterator __last = end();
  while (__first != __last) {
    iterator __next = __first;
    ++__next;
    if (*__first == __value) erase(__first);
    __first = __next;
  }
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::unique()
{
  iterator __first = begin();
  iterator __last = end();
  if (__first == __last) return;
  iterator __next = __first;
  while (++__next != __last) {
    if (*__first == *__next)
      erase(__next);
    else
      __first = __next;
    __next = __first;
  }
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::merge(list<_Tp, _Alloc>& __x)
{
  iterator __first1 = begin();
  iterator __last1 = end();
  iterator __first2 = __x.begin();
  iterator __last2 = __x.end();
  while (__first1 != __last1 && __first2 != __last2)
    if (*__first2 < *__first1) {
      iterator __next = __first2;
      transfer(__first1, __first2, ++__next);
      __first2 = __next;
    }
    else
      ++__first1;
  if (__first2 != __last2) transfer(__last1, __first2, __last2);
  __stl_debug_do(__x._Invalidate_all());
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::reverse() 
{
  // Do nothing if the list has length 0 or 1.
  if (_M_node->_M_next != _M_node &&
      ((_Node*) (_M_node->_M_next))->_M_next != _M_node) {
    iterator __first = begin();
    ++__first;
    while (__first != end()) {
      iterator __old = __first;
      ++__first;
      transfer(begin(), __old, __first);
    }
  }
  __stl_debug_do(_Invalidate_all());
}    

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::sort()
{
  // Do nothing if the list has length 0 or 1.
  if (_M_node->_M_next != _M_node &&
      ((_Node*) (_M_node->_M_next))->_M_next != _M_node) {
    list<_Tp, _Alloc> __carry;
    list<_Tp, _Alloc> __counter[64];
    int __fill = 0;
    while (!empty()) {
      __carry.splice(__carry.begin(), *this, begin());
      int __i = 0;
      while(__i < __fill && !__counter[__i].empty()) {
        __counter[__i].merge(__carry);
        __carry.swap(__counter[__i++]);
      }
      __carry.swap(__counter[__i]);         
      if (__i == __fill) ++__fill;
    } 

    for (int __i = 1; __i < __fill; ++__i)
      __counter[__i].merge(__counter[__i-1]);
    swap(__counter[__fill-1]);
  }
  __stl_debug_do(_Invalidate_all());
}

// do a cleanup
# undef list
# define __list__ __FULL_NAME(list)
# if defined ( __STL_NESTED_TYPE_PARAM_BUG )
#  undef  iterator
#  undef  const_iterator
#  undef  size_type
# endif
# undef __iterator__

# if defined (__STL_USE_WRAPPER_FOR_ALLOC_PARAM)
// provide a "default" list adaptor
template <class _Tp>
class list : public __list__<_Tp, __STL_DEFAULT_ALLOCATOR(_Tp) >
{
#   define __LIST_SUPER __list__<_Tp, __STL_DEFAULT_ALLOCATOR(_Tp) >
  typedef __LIST_SUPER _Super;
  typedef list<_Tp> _Self;
public:
    __IMPORT_WITH_REVERSE_ITERATORS(_Super)
    __IMPORT_SUPER_COPY_ASSIGNMENT(list, _Self, __LIST_SUPER)
    list() { }
    explicit list(size_type __n, const _Tp& __value) : __LIST_SUPER(__n, __value) { }
    explicit list(size_type __n) :  __LIST_SUPER(__n) { } 
    list(const _Tp* __first, const _Tp* __last) : __LIST_SUPER(__first, __last) { } 
    list(const_iterator __first, const_iterator __last) : __LIST_SUPER(__first, __last) { }
# undef __LIST_SUPER
};

#  if defined (__STL_BASE_MATCH_BUG)
template <class _Tp>
inline bool operator==(const list<_Tp>& __x, const list<_Tp>& __y) {
    typedef typename list<_Tp>::_Super _Super;
    return operator == ((const _Super&)__x,(const _Super&)__y);
}

template <class _Tp>
inline bool operator<(const list<_Tp>& __x, const list<_Tp>& __y) {
    typedef typename list<_Tp>::_Super _Super;
    return operator < ((const _Super&)__x,(const _Super&)__y);
}
#  endif
# endif /*  __STL_DEFAULT_TEMPLATE_PARAM */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#pragma reset woff 1375
#endif

__STL_END_NAMESPACE 

#endif /* __SGI_STL_INTERNAL_LIST_H */

// Local Variables:
// mode:C++
// End:
