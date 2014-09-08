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

#ifndef __SGI_STL_INTERNAL_DBG_LIST_H
#define __SGI_STL_INTERNAL_DBG_LIST_H

#include <stl/debug/_iterator.h>

# ifndef __STL_USE_WRAPPER_FOR_ALLOC_PARAM
#  undef  _DBG_list
#  define _DBG_list list
# endif

#  define __STL_DBG_LIST_BASE \
__WORKAROUND_DBG_RENAME(list) <_Tp, _Alloc>

__STL_BEGIN_NAMESPACE

# ifdef __STL_DEBUG_USE_DISTINCT_VALUE_TYPE_HELPERS
template <class _Tp, class _Alloc>
inline _Tp*
__VALUE_TYPE(const  _DBG_iter_base< __STL_DBG_LIST_BASE >&) {
  return (_Tp*)0;
}
template <class _Tp, class _Alloc>
inline bidirectional_iterator_tag
__ITERATOR_CATEGORY(const _DBG_iter_base< __STL_DBG_LIST_BASE >&) {
  return bidirectional_iterator_tag();
}
# endif

template <class _Tp, __STL_DEFAULT_ALLOCATOR_SELECT(_Tp) >
class _DBG_list : public __STL_DBG_LIST_BASE {

  typedef __STL_DBG_LIST_BASE _Base;
  typedef _DBG_list<_Tp, _Alloc> _Self;

public:      
  __IMPORT_CONTAINER_TYPEDEFS(_Base)

public:
  typedef _DBG_iter<_Base, _Nonconst_traits<value_type> >     iterator;
  typedef _DBG_iter<_Base, _Const_traits<value_type> >    const_iterator;

  __STL_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS;

protected:
  mutable __owned_list _M_iter_list;
  void _Invalidate_all() { _M_iter_list._Invalidate_all();}

public:
  const _Base* _Get_base() const { return (const _Base*)this; }
  _Base* _Get_base() { return (_Base*)this; }
  explicit _DBG_list(const allocator_type& __a = allocator_type()) :
    __STL_DBG_LIST_BASE(__a), _M_iter_list(_Get_base()) {}
  _DBG_list(size_type __n, const _Tp& __value,
	    const allocator_type& __a = allocator_type())
    : __STL_DBG_LIST_BASE(__n, __value, __a), _M_iter_list(_Get_base()) {}
  explicit _DBG_list(size_type __n)
    : __STL_DBG_LIST_BASE(__n), _M_iter_list(_Get_base()) {}
  
#ifdef __STL_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because insert does all of
  // that anyway.  
  template <class _InputIterator>
  _DBG_list(_InputIterator __first, _InputIterator __last)
    : __STL_DBG_LIST_BASE(__first, __last, allocator_type()), _M_iter_list(_Get_base()) {}

  template <class _InputIterator>
  _DBG_list(_InputIterator __first, _InputIterator __last,
       const allocator_type& __a)
    : __STL_DBG_LIST_BASE(__first, __last, __a), _M_iter_list(_Get_base()) {}

#else /* __STL_MEMBER_TEMPLATES */

  _DBG_list(const _Tp* __first, const _Tp* __last,
       const allocator_type& __a = allocator_type())
    : __STL_DBG_LIST_BASE(__first, __last, __a), _M_iter_list(_Get_base()) {}
  _DBG_list(const_iterator __first, const_iterator __last,
       const allocator_type& __a = allocator_type()):
    __STL_DBG_LIST_BASE(__first._M_iterator, __last._M_iterator, __a),
    _M_iter_list(_Get_base()) {}

#endif /* __STL_MEMBER_TEMPLATES */

  _DBG_list(const _Self& __x) : 
    __STL_DBG_LIST_BASE(__x) , _M_iter_list(_Get_base()) {}

  _Self& operator=(const _Self& __x) {
    _Invalidate_all();
    _Base::operator=((const _Base&)__x);
    return *this;
  }

public:
  iterator begin()             { return iterator(&_M_iter_list, _Base::begin()); }
  const_iterator begin() const { return const_iterator(&_M_iter_list, _Base::begin()); }

  iterator end()               { return iterator(&_M_iter_list, _Base::end()); }
  const_iterator end() const   { return const_iterator(&_M_iter_list, _Base::end()); }

  reverse_iterator rbegin()    { return reverse_iterator(end()); }
  reverse_iterator rend()      { return reverse_iterator(begin()); }

  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  // those are here to enforce checking
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }

  void swap(_Self& __x) {
    _M_iter_list._Swap_owners(__x._M_iter_list, true);
    _Base::swap(__x); 
  }

  iterator insert(iterator __position, const _Tp& __x) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
      return iterator(&_M_iter_list,_Base::insert(__position._M_iterator, __x) );
  }

  iterator insert(iterator __position) { return insert(__position, _Tp()); }

#ifdef __STL_MEMBER_TEMPLATES

  template <class _InputIterator>
  void insert(iterator __position, _InputIterator __first, _InputIterator __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
    _Base::insert(__position._M_iterator, __first, __last);
  }

#else

  void insert(iterator __position, const _Tp* __first, const _Tp* __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
    _Base::insert(__position._M_iterator, __first, __last);
  }

  void insert(iterator __position,
	      const_iterator __first, const_iterator __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
    _Base::insert(__position._M_iterator, __first._M_iterator, __last._M_iterator);
  }
  
#endif /* __STL_MEMBER_TEMPLATES */

  void insert(iterator __position, size_type __n, const _Tp& __x) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
    _Base::insert(__position._M_iterator, __n, __x);    
  }

  iterator erase(iterator __position) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
    __STL_VERBOSE_ASSERT(__position._M_iterator._M_node!=this->_M_node._M_data, 
			 _StlMsg_ERASE_PAST_THE_END)
    // fbp : CHECK !!!
    //    __invalidate_iterator(&_M_iter_list, __position);
    return iterator(&_M_iter_list,_Base::erase(__position._M_iterator));
  }
  iterator erase(iterator __first, iterator __last) {
    // fbp : do range invalidation here !
    return iterator(&_M_iter_list,_Base::erase(__first._M_iterator, __last._M_iterator));
  }
  void clear() {   
    _Invalidate_all();
    _Base::clear(); 
  }

public:
  void splice(iterator __position, _Self& __x) {
    __STL_VERBOSE_ASSERT(&__x!=this, _StlMsg_INVALID_ARGUMENT)
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position))
    _Base::splice(__position._M_iterator, __x);
    __x._Invalidate_all();
  }

  void splice(iterator __position, _Self& __x, iterator __i) {
      __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__position) &&
                        __check_if_owner(&__x._M_iter_list ,__i))
    __STL_DEBUG_CHECK(_Dereferenceable(__i))
    // fbp : CHECK !!!
    //    __invalidate_iterator(&__x._M_iter_list, __i);
    _Base::splice(__position._M_iterator, __x, __i._M_iterator);
  }

  void splice(iterator __position, _Self& __x, iterator __first, iterator __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __position))
    __STL_VERBOSE_ASSERT(__first._Owner()==&__x._M_iter_list && __last._Owner()==&__x._M_iter_list, 
			 _StlMsg_NOT_OWNER)
    _Base::splice(__position._M_iterator, __x, __first._M_iterator, __last._M_iterator);
  }

  void merge(_Self& __x) {   
    __x._Invalidate_all();
    _Base::merge(__x); 
  }
  void reverse() {
    _Invalidate_all();
    _Base::reverse();
  }
  void sort() {
    _Invalidate_all();
    _Base::sort();
  }

#ifdef __STL_MEMBER_TEMPLATES
  template <class _StrictWeakOrdering>
  void sort(_StrictWeakOrdering __comp) {
      _Invalidate_all();
      _Base::sort(__comp);
  }
#endif /* __STL_MEMBER_TEMPLATES */

};

#ifdef __STL_EXTRA_OPERATORS_FOR_DEBUG
template <class _Tp, class _Alloc>
__STL_INLINE_LOOP bool operator==(const _DBG_list<_Tp,_Alloc>& __x,
				  const _DBG_list<_Tp,_Alloc>& __y)
{
  return (const __STL_DBG_LIST_BASE&)__x == (const __STL_DBG_LIST_BASE&)__y;
}
template <class _Tp, class _Alloc>
inline bool operator<(const _DBG_list<_Tp,_Alloc>& __x,
                      const _DBG_list<_Tp,_Alloc>& __y)
{
  return (const __STL_DBG_LIST_BASE&)__x < (const __STL_DBG_LIST_BASE&)__y;
}
#endif

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE
template <class _Tp, class _Alloc>
inline void 
swap(_DBG_list<_Tp, _Alloc>& __x, _DBG_list<_Tp, _Alloc>& __y)
{
  __x.swap(__y);
}
#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

__STL_END_NAMESPACE 

#endif /* __SGI_STL_INTERNAL_LIST_H */

// Local Variables:
// mode:C++
// End:
