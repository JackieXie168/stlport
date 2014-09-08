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

#ifndef __SGI_STL_INTERNAL_TREE_H
#define __SGI_STL_INTERNAL_TREE_H

/*

Red-black tree class, designed for use in implementing STL
associative containers (set, multiset, map, and multimap). The
insertion and deletion algorithms are based on those in Cormen,
Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990),
except that

(1) the header cell is maintained with links not only to the root
but also to the leftmost node of the tree, to enable constant time
begin(), and to the rightmost node of the tree, to enable linear time
performance when used with the generic set algorithms (set_union,
etc.);

(2) when a node being deleted has two children its successor node is
relinked into its place, rather than copied, so that the only
iterators invalidated are those referring to the deleted node.

*/

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

# ifndef __SGI_STL_INTERNAL_FUNCTION_H
#  include <stl/_function.h>
# endif

# if defined ( __STL_USE_ABBREVS )
// ugliness is intentional - to reduce conflicts possibility
#  define _Rb_tree_node_base       _rbT__NB
#  define _Rb_tree_node            _rbT__N
#  define _Rb_base_iterator        _rbTB__It
#  define _Rb_tree_base_iterator   _rbT__It
#  define _Rb_tree_base            _rbT__B
# endif

#if defined ( __STL_DEBUG)
#  define _Rb_tree __WORKAROUND_DBG_RENAME(Rb_tree)
#endif

__STL_BEGIN_NAMESPACE

typedef bool _Rb_tree_Color_type;
//const _Rb_tree_Color_type _S_rb_tree_red = false;
//const _Rb_tree_Color_type _S_rb_tree_black = true;

#define _S_rb_tree_red false
#define _S_rb_tree_black true

struct _Rb_tree_node_base
{
  typedef _Rb_tree_Color_type _Color_type;
  typedef _Rb_tree_node_base* _Base_ptr;

  _Color_type _M_color; 
  _Base_ptr _M_parent;
  _Base_ptr _M_left;
  _Base_ptr _M_right;

  static _Base_ptr __STL_CALL _S_minimum(_Base_ptr __x)
  {
    while (__x->_M_left != 0) __x = __x->_M_left;
    return __x;
  }

  static _Base_ptr __STL_CALL _S_maximum(_Base_ptr __x)
  {
    while (__x->_M_right != 0) __x = __x->_M_right;
    return __x;
  }
};

template <class _Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
  _Value _M_value_field;
  __TRIVIAL_STUFF(_Rb_tree_node)
};

struct _Rb_tree_base_iterator;

template <class _Dummy>
struct _Rb_global {
  typedef _Rb_tree_node_base* _Base_ptr;
  // those used to be global functions 
  static void __STL_CALL _Rebalance(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root);
  static _Rb_tree_node_base* __STL_CALL _Rebalance_for_erase(_Rb_tree_node_base* __z,
                                                             _Rb_tree_node_base*& __root,
                                                             _Rb_tree_node_base*& __leftmost,
                                                             _Rb_tree_node_base*& __rightmost);
  // those are from _Rb_tree_base_iterator - moved here to reduce code bloat
  // moved here to reduce code bloat without templatizing _Rb_tree_base_iterator
  static void  __STL_CALL _M_increment(_Rb_tree_base_iterator*);
  static void  __STL_CALL _M_decrement(_Rb_tree_base_iterator*);
};

typedef _Rb_global<bool> _Rb_global_inst;

struct _Rb_tree_base_iterator
{
  typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  _Base_ptr _M_node;
  bool operator==(const _Rb_tree_base_iterator& __y) const {
    return _M_node == __y._M_node;
  }
  bool operator!=(const _Rb_tree_base_iterator& __y) const {
    return _M_node != __y._M_node;
  }
};


template <class _Value, class _Traits>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator
{
  typedef _Value value_type;
  typedef typename _Traits::reference  reference;
  typedef typename _Traits::pointer    pointer;
  
  //  typedef _Rb_tree_iterator<_Value, _Nonconst_traits<_Value> >  iterator;
  //  typedef _Rb_tree_iterator<_Value, _Const_traits<_Value> > const_iterator;
  typedef _Rb_tree_iterator<_Value, _Traits> _Self;
  typedef _Rb_tree_node<_Value>* _Link_type;

  _Rb_tree_iterator() { _M_node = 0; }
  _Rb_tree_iterator(_Link_type __x) { _M_node = __x; }
  _Rb_tree_iterator(const _Rb_tree_iterator<_Value, 
                    _Nonconst_traits<_Value> >& __it) { _M_node = __it._M_node; }

  reference operator*() const { 
    return _Link_type(_M_node)->_M_value_field; 
  }
  
  __STL_DEFINE_ARROW_OPERATOR

  _Self& operator++() { _Rb_global_inst::_M_increment(this); return *this; }
  _Self operator++(int) {
    _Self __tmp = *this;
    _Rb_global_inst::_M_increment(this);
    return __tmp;
  }
    
  _Self& operator--() { _Rb_global_inst::_M_decrement(this); return *this; }
  _Self operator--(int) {
    _Self __tmp = *this;
    _Rb_global_inst::_M_decrement(this);
    return __tmp;
  }
};

# ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES
template <class _Value, class _Traits>
inline _Value*
__VALUE_TYPE(const _Rb_tree_iterator<_Value, _Traits>&) { return (_Value*)0; }
inline bidirectional_iterator_tag
__ITERATOR_CATEGORY(const _Rb_tree_base_iterator&) { return bidirectional_iterator_tag(); }
inline ptrdiff_t*
__DISTANCE_TYPE(const _Rb_tree_base_iterator&) { return (ptrdiff_t*) 0; }
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// Base class to help EH

template <class _Tp, class _Alloc>
struct _Rb_tree_base
{
  typedef _Rb_tree_node<_Tp> _Node;
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;

  _Rb_tree_base(const allocator_type& __a) : 
    _M_header(__STL_CONVERT_ALLOCATOR(__a, _Node), (_Node*)0) { 
      _M_header._M_data = _M_header.allocate(1); 
  }
  ~_Rb_tree_base() { 
    _M_header.deallocate(_M_header._M_data,1); 
  }
  allocator_type get_allocator() const { 
    return __STL_CONVERT_ALLOCATOR(_M_header, _Tp); 
  }
protected:
  typedef typename _Alloc_traits<_Node, _Alloc>::allocator_type _M_node_allocator_type;
  _STL_alloc_proxy<_Node*, _Node, _M_node_allocator_type> _M_header;
};


template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          __STL_DEFAULT_ALLOCATOR_SELECT(_Value) >
class _Rb_tree : public _Rb_tree_base<_Value, _Alloc> {
  typedef _Rb_tree_base<_Value, _Alloc> _Base;
protected:
  typedef _Rb_tree_node_base* _Base_ptr;
  typedef _Rb_tree_node<_Value> _Node;
  typedef _Rb_tree_Color_type _Color_type;
public:
  typedef _Key key_type;
  typedef _Value value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef _Rb_tree_node<_Value>* _Link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef bidirectional_iterator_tag _Iterator_category;

  typedef typename _Base::allocator_type allocator_type;
  
protected:
#if defined( __STL_HAS_NAMESPACES )
  __STL_USING_BASE_MEMBER _Rb_tree_base<_Value, _Alloc>::_M_header;
#endif /* __STL_USE_NAMESPACES */

protected:

  _Link_type _M_create_node(const value_type& __x)
  {
    _Link_type __tmp = _M_header.allocate(1);
    __STL_TRY {
      _Construct(&__tmp->_M_value_field, __x);
    }
    __STL_UNWIND(_M_header.deallocate(__tmp,1));
    return __tmp;
  }

  _Link_type _M_clone_node(_Link_type __x)
  {
    _Link_type __tmp = _M_create_node(__x->_M_value_field);
    __tmp->_M_color = __x->_M_color;
    __tmp->_M_left = 0;
    __tmp->_M_right = 0;
    return __tmp;
  }

  void destroy_node(_Link_type __p)
  {
    _Destroy(&__p->_M_value_field);
    _M_header.deallocate(__p,1);
  }

protected:
  size_type _M_node_count; // keeps track of size of tree
  _Compare _M_key_compare;

  _Link_type& _M_root() const 
    { return (_Link_type&) _M_header._M_data->_M_parent; }
  _Link_type& _M_leftmost() const 
    { return (_Link_type&) _M_header._M_data->_M_left; }
  _Link_type& _M_rightmost() const 
    { return (_Link_type&) _M_header._M_data->_M_right; }

  static _Link_type&  __STL_CALL _S_left(_Link_type __x)
    { return (_Link_type&)(__x->_M_left); }
  static _Link_type&  __STL_CALL _S_right(_Link_type __x)
    { return (_Link_type&)(__x->_M_right); }
  static _Link_type&  __STL_CALL _S_parent(_Link_type __x)
    { return (_Link_type&)(__x->_M_parent); }
  static reference  __STL_CALL _S_value(_Link_type __x)
    { return __x->_M_value_field; }
  static const _Key&  __STL_CALL _S_key(_Link_type __x)
    { return _KeyOfValue()(_S_value(__x)); }
  static _Color_type&  __STL_CALL _S_color(_Link_type __x)
    { return (_Color_type&)(__x->_M_color); }

  static _Link_type&  __STL_CALL _S_left(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_left); }
  static _Link_type&  __STL_CALL _S_right(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_right); }
  static _Link_type&  __STL_CALL _S_parent(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_parent); }
  static reference  __STL_CALL _S_value(_Base_ptr __x)
    { return ((_Link_type)__x)->_M_value_field; }
  static const _Key&  __STL_CALL _S_key(_Base_ptr __x)
    { return _KeyOfValue()(_S_value(_Link_type(__x)));} 
  static _Color_type&  __STL_CALL _S_color(_Base_ptr __x)
    { return (_Color_type&)(_Link_type(__x)->_M_color); }

  static _Link_type  __STL_CALL _S_minimum(_Link_type __x) 
    { return (_Link_type)  _Rb_tree_node_base::_S_minimum(__x); }

  static _Link_type  __STL_CALL _S_maximum(_Link_type __x)
    { return (_Link_type) _Rb_tree_node_base::_S_maximum(__x); }

public:
  typedef _Rb_tree_iterator<value_type, _Nonconst_traits<value_type> > iterator;
  typedef _Rb_tree_iterator<value_type, _Const_traits<value_type> > const_iterator;

  __STL_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS;

private:
  iterator _M_insert(_Base_ptr __x, _Base_ptr __y, const value_type& __v);
  _Link_type _M_copy(_Link_type __x, _Link_type __p);
  void _M_erase(_Link_type __x);

public:
                                // allocation/deallocation
  _Rb_tree()
    : _Rb_tree_base<_Value, _Alloc>(allocator_type()), _M_node_count(0), _M_key_compare(_Compare())
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp)
    : _Rb_tree_base<_Value, _Alloc>(allocator_type()), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp, const allocator_type& __a)
    : _Rb_tree_base<_Value, _Alloc>(__a), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x) 
    : _Rb_tree_base<_Value, _Alloc>(__x.get_allocator()),
      _M_node_count(0), _M_key_compare(__x._M_key_compare)
  { 
    if (__x._M_root() == 0)
      _M_empty_initialize();
    else {
      _S_color(_M_header._M_data) = _S_rb_tree_red;
      _M_root() = _M_copy(__x._M_root(), _M_header._M_data);
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
    }
    _M_node_count = __x._M_node_count;
  }
  ~_Rb_tree() { clear(); }
  _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& 
  operator=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x);

private:
  void _M_empty_initialize() {
    _S_color(_M_header._M_data) = _S_rb_tree_red; // used to distinguish header from 
                                          // __root, in iterator.operator++
    _M_root() = 0;
    _M_leftmost() = _M_header._M_data;
    _M_rightmost() = _M_header._M_data;
  }

public:    
                                // accessors:
  _Compare key_comp() const { return _M_key_compare; }

  iterator begin() { return iterator(_M_leftmost()); }
  const_iterator begin() const { return const_iterator(_M_leftmost()); }
  iterator end() { return iterator(_M_header._M_data); }
  const_iterator end() const { return const_iterator(_M_header._M_data); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { 
    return const_reverse_iterator(end()); 
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { 
    return const_reverse_iterator(begin());
  } 
  bool empty() const { return _M_node_count == 0; }
  size_type size() const { return _M_node_count; }
  size_type max_size() const { return size_type(-1); }

  void swap(_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __t) {
    __STLPORT_STD::swap(_M_header._M_data, __t._M_header._M_data);
    __STLPORT_STD::swap(_M_node_count, __t._M_node_count);
    __STLPORT_STD::swap(_M_key_compare, __t._M_key_compare);
  }
    
public:
                                // insert/erase
  pair<iterator,bool> insert_unique(const value_type& __x);
  iterator insert_equal(const value_type& __x);

  iterator insert_unique(iterator __position, const value_type& __x);
  iterator insert_equal(iterator __position, const value_type& __x);

#ifdef __STL_MEMBER_TEMPLATES  
  template<class _II>
  void insert_equal(_II __first, _II __last) {
    for ( ; __first != __last; ++__first)
      insert_equal(*__first);
  }
  template<class _II>
  void insert_unique(_II __first, _II __last) {
    for ( ; __first != __last; ++__first)
      insert_unique(*__first);
  }
#else /* __STL_MEMBER_TEMPLATES */
  void insert_unique(const_iterator __first, const_iterator __last) {
    for ( ; __first != __last; ++__first)
      insert_unique(*__first);
  }
  void insert_unique(const value_type* __first, const value_type* __last) {
    for ( ; __first != __last; ++__first)
      insert_unique(*__first);
  }
  void insert_equal(const_iterator __first, const_iterator __last) {
    for ( ; __first != __last; ++__first)
      insert_equal(*__first);
  }
  void insert_equal(const value_type* __first, const value_type* __last) {
    for ( ; __first != __last; ++__first)
      insert_equal(*__first);
  }
#endif /* __STL_MEMBER_TEMPLATES */

  void erase(iterator __position) {
    _Link_type __y = 
      (_Link_type) _Rb_global_inst::_Rebalance_for_erase(__position._M_node,
							 _M_header._M_data->_M_parent,
							 _M_header._M_data->_M_left,
							 _M_header._M_data->_M_right);
    destroy_node(__y);
    --_M_node_count;
  }
  size_type erase(const key_type& __x);
  void erase(iterator __first, iterator __last);
  void erase(const key_type* __first, const key_type* __last);

  void clear() {
    if (_M_node_count != 0) {
      _M_erase(_M_root());
      _M_leftmost() = _M_header._M_data;
      _M_root() = 0;
      _M_rightmost() = _M_header._M_data;
      _M_node_count = 0;
    }
  }      

public:
                                // set operations:
  iterator find(const key_type& __x);
  const_iterator find(const key_type& __x) const;
  size_type count(const key_type& __x) const;
  iterator lower_bound(const key_type& __x);
  const_iterator lower_bound(const key_type& __x) const;
  iterator upper_bound(const key_type& __x);
  const_iterator upper_bound(const key_type& __x) const;
  pair<iterator,iterator> equal_range(const key_type& __x) {
    return pair<iterator, iterator>(lower_bound(__x), upper_bound(__x));
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& __x) const {
    return pair<const_iterator,const_iterator>(lower_bound(__x),
					       upper_bound(__x));
  }

public:
                                // Debugging.
  bool __rb_verify() const;
};

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool __STL_CALL 
operator==(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool __STL_CALL 
operator<(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
          const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(), 
                                 __y.begin(), __y.end());
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool __STL_CALL 
operator!=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__x == __y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool __STL_CALL 
operator>(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
          const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return __y < __x;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool __STL_CALL 
operator<=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__y < __x);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool __STL_CALL 
operator>=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__x < __y);
}

#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline void __STL_CALL 
swap(_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
     _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  __x.swap(__y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */
         
__STL_END_NAMESPACE

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_tree.c>
# endif

# undef _Rb_tree

#if defined (__STL_DEBUG)
# include <stl/debug/_tree.h>
#endif

__STL_BEGIN_NAMESPACE
// Class rb_tree is not part of the C++ standard.  It is provided for
// compatibility with the HP STL.

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          __STL_DEFAULT_ALLOCATOR_SELECT(_Value) >
struct rb_tree : public _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>
{
  typedef _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> _Base;
  typedef typename _Base::allocator_type allocator_type;

  rb_tree()
     : _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>(_Compare(), allocator_type()) {}
  rb_tree(const _Compare& __comp,
          const allocator_type& __a = allocator_type())
    : _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>(__comp, __a) {} 
  ~rb_tree() {}
};
__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_TREE_H */

// Local Variables:
// mode:C++
// End:

