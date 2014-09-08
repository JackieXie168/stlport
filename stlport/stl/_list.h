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

# ifndef __SGI_STL_INTERNAL_ALGOBASE_H
#  include <stl/_algobase.h>
# endif

# ifndef __SGI_STL_INTERNAL_ALLOC_H
#  include <stl/_alloc.h>
# endif

# ifndef __SGI_STL_INTERNAL_ITERATOR_H
#  include <stl/_iterator.h>
# endif

# ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#  include <stl/_construct.h>
# endif

__STL_BEGIN_NAMESPACE

# undef list
# define  list  __WORKAROUND_DBG_RENAME(list)

# if defined ( __STL_USE_ABBREVS )
#  define __list_iterator         _L__It
# endif

struct _List_node_base {
  _List_node_base* _M_next;
  _List_node_base* _M_prev;
};

template <class _Dummy>
struct _List_global {
  typedef _List_node_base _Node;
  static void  __STL_CALL _Transfer(_List_node_base* __position, 
                                    _List_node_base* __first, _List_node_base* __last);
};

typedef _List_global<bool> _List_global_inst;

template <class _Tp>
struct _List_node : public _List_node_base {
  _Tp _M_data;
  __TRIVIAL_STUFF(_List_node)
};

struct _List_iterator_base {
  typedef size_t                     size_type;
  typedef ptrdiff_t                  difference_type;
  typedef bidirectional_iterator_tag iterator_category;

  _List_node_base* _M_node;

  _List_iterator_base(_List_node_base* __x) : _M_node(__x) {}
  _List_iterator_base() {}

  void _M_incr() { _M_node = _M_node->_M_next; }
  void _M_decr() { _M_node = _M_node->_M_prev; }
  bool operator==(const _List_iterator_base& __y ) const { 
    return _M_node == __y._M_node; 
  }
  bool operator!=(const _List_iterator_base& __y ) const { 
    return _M_node != __y._M_node; 
  }
};  




template<class _Tp, class _Traits>
struct _List_iterator : public _List_iterator_base {
  typedef _Tp value_type;
  typedef typename _Traits::pointer    pointer;
  typedef typename _Traits::reference  reference;

  typedef _List_iterator<_Tp, _Nonconst_traits<_Tp> > iterator;
  typedef _List_iterator<_Tp, _Const_traits<_Tp> >    const_iterator;
  typedef _List_iterator<_Tp, _Traits>                       _Self;

  typedef bidirectional_iterator_tag iterator_category;
  typedef _List_node<_Tp> _Node;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  _List_iterator(_Node* __x) : _List_iterator_base(__x) {}
  _List_iterator() {}
  _List_iterator(const iterator& __x) :  _List_iterator_base(__x._M_node) {}

  reference operator*() const { return ((_Node*)_M_node)->_M_data; }

  __STL_DEFINE_ARROW_OPERATOR

  _Self& operator++() { 
    this->_M_incr();
    return *this;
  }
  _Self operator++(int) { 
    _Self __tmp = *this;
    this->_M_incr();
    return __tmp;
  }
  _Self& operator--() { 
    this->_M_decr();
    return *this;
  }
  _Self operator--(int) { 
    _Self __tmp = *this;
    this->_M_decr();
    return __tmp;
  }
};


#ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES
template <class _Tp, class _Traits>
inline _Tp* __VALUE_TYPE(const _List_iterator<_Tp, _Traits>&) { return 0; }
inline bidirectional_iterator_tag __ITERATOR_CATEGORY(const _List_iterator_base&) { return bidirectional_iterator_tag();}
inline ptrdiff_t* __DISTANCE_TYPE(const _List_iterator_base&) { return 0; }
#endif


// Base class that encapsulates details of allocators and helps 
// to simplify EH

template <class _Tp, class _Alloc>
class _List_base 
{
protected:
  typedef _List_node<_Tp> _Node;
  typedef typename _Alloc_traits<_Node, _Alloc>::allocator_type
           _Node_allocator_type;
public:
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type
          allocator_type;

  allocator_type get_allocator() const { 
    return __STL_CONVERT_ALLOCATOR((const _Node_allocator_type&)_M_node, _Tp);
  }

  _List_base(const allocator_type& __a) : _M_node(__STL_CONVERT_ALLOCATOR(__a, _Node), (_Node*)0) {
    _Node* __n = _M_node.allocate(1);
    __n->_M_next = __n;
    __n->_M_prev = __n;
    _M_node._M_data = __n;
  }
  ~_List_base() {
    clear();
    _M_node.deallocate(_M_node._M_data, 1);
  }

  void clear();

public:
  _STL_alloc_proxy<_Node*, _Node, _Node_allocator_type>  _M_node;
};

template <class _Tp, __STL_DEFAULT_ALLOCATOR_SELECT(_Tp) >
class list : protected _List_base<_Tp, _Alloc> {
  typedef _List_base<_Tp, _Alloc> _Base;
  typedef list<_Tp, _Alloc> _Self;
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
  typedef bidirectional_iterator_tag _Iterator_category;

public:
  typedef _List_iterator<_Tp, _Nonconst_traits<_Tp> > iterator;
  typedef _List_iterator<_Tp, _Const_traits<_Tp> >    const_iterator;

  __STL_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS;

#if defined( __STL_HAS_NAMESPACES )
  __STL_USING_BASE_MEMBER _List_base<_Tp, _Alloc>::_M_node;
#endif /* __STL_HAS_NAMESPACES */
public:
  __STL_USING_BASE_MEMBER _List_base<_Tp, _Alloc>::get_allocator;
  __STL_USING_BASE_MEMBER _List_base<_Tp, _Alloc>::clear;

protected:
  _Node* _M_create_node(const _Tp& __x)
  {
    _Node* __p = _M_node.allocate(1);
    __STL_TRY {
      _Construct(&__p->_M_data, __x);
    }
    __STL_UNWIND(_M_node.deallocate(__p, 1));
    return __p;
  }

  _Node* _M_create_node()
  {
    _Node* __p = _M_node.allocate(1);
    __STL_TRY {
      _Construct(&__p->_M_data);
    }
    __STL_UNWIND(_M_node.deallocate(__p, 1));
    return __p;
  }

public:
# if !(defined(__MRC__)||defined(__SC__))
  explicit
# endif
  list(const allocator_type& __a = allocator_type()) :
    _List_base<_Tp, _Alloc>(__a) {}

  iterator begin()             { return iterator((_Node*)(_M_node._M_data->_M_next)); }
  const_iterator begin() const { return const_iterator((_Node*)(_M_node._M_data->_M_next)); }

  iterator end()             { return _M_node._M_data; }
  const_iterator end() const { return _M_node._M_data; }

  reverse_iterator rbegin() 
    { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const 
    { return const_reverse_iterator(end()); }

  reverse_iterator rend()
    { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

  bool empty() const { return _M_node._M_data->_M_next == _M_node._M_data; }
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
    __STLPORT_STD::swap(_M_node, __x._M_node); 
  }

  iterator insert(iterator __position, const _Tp& __x) {

    _Node* __tmp = _M_create_node(__x);
# if 0
    cerr <<"before: ";
    for ( _Node* __tmp1 = (_Node*)(_M_node._M_data->_M_next);;) {
      cerr<< hex<<(long)(__tmp1->_M_prev)<<"<-"<<(long)__tmp1<<":"<<__tmp1->_M_data<<"->"<<(long)__tmp1->_M_next<<";";
      __tmp1 = (_Node*)__tmp1->_M_next;
      if (__tmp1 == (_Node*)_M_node._M_data) {
        cerr << endl;
        break;
      }
    }
# endif
    _List_node_base* __n = __position._M_node;
    _List_node_base* __p = __n->_M_prev;
    __tmp->_M_next = __n;
    __tmp->_M_prev = __p;
    __p->_M_next = __tmp;
    __n->_M_prev = __tmp;
# if 0
    cerr<<"after : ";
    for ( _Node* __tmp1 = (_Node*)(_M_node._M_data->_M_next);;) {
      cerr<<hex<<(long)(__tmp1->_M_prev)<<"<-"<<(long)__tmp1<<":"<<__tmp1->_M_data<<"->"<<(long)__tmp1->_M_next<<";";
      __tmp1 = (_Node*)__tmp1->_M_next;
      if (__tmp1 == (_Node*)_M_node._M_data) {
        cerr << endl;
        break;
      }
    }
# endif   
    return __tmp;
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
    _List_node_base* __next_node = __position._M_node->_M_next;
    _List_node_base* __prev_node = __position._M_node->_M_prev;
    _Node* __n = (_Node*) __position._M_node;
    __prev_node->_M_next = __next_node;
    __next_node->_M_prev = __prev_node;
    _Destroy(&__n->_M_data);
    _M_node.deallocate(__n, 1);
    return iterator((_Node*)__next_node);
    }
  iterator erase(iterator __first, iterator __last);

  void resize(size_type __new_size, const _Tp& __x);
  void resize(size_type __new_size) { this->resize(__new_size, _Tp()); }

  void pop_front() { erase(begin()); }
  void pop_back() { 
    iterator __tmp = end();
    erase(--__tmp);
  }
  list(size_type __n, const _Tp& __value,
       const allocator_type& __a = allocator_type())
    : _List_base<_Tp, _Alloc>(__a)
    { this->insert(begin(), __n, __value); }
  explicit list(size_type __n)
    : _List_base<_Tp, _Alloc>(allocator_type())
    { this->insert(begin(), __n, _Tp()); }

#ifdef __STL_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because insert does all of
  // that anyway.  
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last,
       const allocator_type& __a = allocator_type())
    : _List_base<_Tp, _Alloc>(__a)
  { insert(begin(), __first, __last); }
  
#else /* __STL_MEMBER_TEMPLATES */

  list(const _Tp* __first, const _Tp* __last,
       const allocator_type& __a = allocator_type())
    : _List_base<_Tp, _Alloc>(__a)
    { insert(begin(), __first, __last); }
  list(const_iterator __first, const_iterator __last,
       const allocator_type& __a = allocator_type())
    : _List_base<_Tp, _Alloc>(__a)
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
public:
  void splice(iterator __position, _Self& __x) {
    if (!__x.empty()) 
      _List_global_inst::_Transfer(__position._M_node, __x.begin()._M_node, __x.end()._M_node);
  }
  void splice(iterator __position, _Self&, iterator __i) {
    iterator __j = __i;
    ++__j;
    if (__position == __i || __position == __j) return;
    _List_global_inst::_Transfer(__position._M_node, __i._M_node, __j._M_node);
  }
  void splice(iterator __position, _Self&, iterator __first, iterator __last) {
    if (__first != __last) 
      _List_global_inst::_Transfer(__position._M_node, __first._M_node, __last._M_node);
  }
  void remove(const _Tp& __value);
  void unique();
  void merge(_Self& __x);
  void reverse();
  void sort();

#ifdef __STL_MEMBER_TEMPLATES
# ifndef __STL_INLINE_MEMBER_TEMPLATES
  template <class _Predicate> void remove_if(_Predicate);
  template <class _BinaryPredicate> void unique(_BinaryPredicate);
  template <class _StrictWeakOrdering> void merge(list<_Tp, _Alloc>&, _StrictWeakOrdering);
  template <class _StrictWeakOrdering> void sort(_StrictWeakOrdering);
# else
  template <class _Predicate>
    void remove_if(_Predicate __pred) 
{
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
	_List_global_inst::_Transfer(__first1._M_node, __first2._M_node, (++__next)._M_node);
	__first2 = __next;
      }
      else
	++__first1;
    if (__first2 != __last2) _List_global_inst::_Transfer(__last1._M_node, __first2._M_node, __last2._M_node);
  }

  template <class _StrictWeakOrdering>
    void sort(_StrictWeakOrdering __comp) {
    // Do nothing if the list has length 0 or 1.
    if (_M_node._M_data->_M_next != _M_node._M_data &&
	(_M_node._M_data->_M_next)->_M_next != _M_node._M_data) {
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
  }
# endif /* __STL_INLINE_MEMBER_TEMPLATES */
#endif /* __STL_MEMBER_TEMPLATES */

};

template <class _Tp, class _Alloc>
__STL_INLINE_LOOP bool  __STL_CALL
operator==(const list<_Tp,_Alloc>& __x, const list<_Tp,_Alloc>& __y)
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
inline bool  __STL_CALL operator<(const list<_Tp,_Alloc>& __x,
                                  const list<_Tp,_Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(),
                                 __y.begin(), __y.end());
}

# define __STL_TEMPLATE_CONTAINER list<_Tp, _Alloc>
# define __STL_TEMPLATE_HEADER    template <class _Tp, class _Alloc>
__STL_RELOPS_OPERATORS(__STL_TEMPLATE_HEADER, __STL_TEMPLATE_CONTAINER)
# undef __STL_TEMPLATE_CONTAINER
# undef __STL_TEMPLATE_HEADER

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _Tp, class _Alloc>
inline void __STL_CALL 
swap(list<_Tp, _Alloc>& __x, list<_Tp, _Alloc>& __y)
{
  __x.swap(__y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

__STL_END_NAMESPACE 

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_list.c>
# endif

// do a cleanup
# undef list
# define __list__ __FULL_NAME(list)

#if defined (__STL_DEBUG)
# include <stl/debug/_list.h>
#endif

#if defined (__STL_USE_WRAPPER_FOR_ALLOC_PARAM)
# include <stl/wrappers/_list.h>
#endif

#endif /* __SGI_STL_INTERNAL_LIST_H */

// Local Variables:
// mode:C++
// End:
