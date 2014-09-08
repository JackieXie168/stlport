/*
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

#ifndef __SGI_STL_INTERNAL_DBG_SLIST_H
#define __SGI_STL_INTERNAL_DBG_SLIST_H

#include <stl/debug/_iterator.h>

# ifndef __STL_USE_WRAPPER_FOR_ALLOC_PARAM
#  undef  _DBG_slist
#  define _DBG_slist slist
# endif

#  define __STL_DBG_SLIST_BASE __WORKAROUND_DBG_RENAME(slist) <_Tp, _Alloc>

__STL_BEGIN_NAMESPACE

# ifdef __STL_DEBUG_USE_DISTINCT_VALUE_TYPE_HELPERS
template <class _Tp, class _Alloc>
inline _Tp*
__VALUE_TYPE(const _DBG_iter_base< __STL_DBG_SLIST_BASE >&) {
  return (_Tp*)0;
}

template <class _Tp, class _Alloc>
inline forward_iterator_tag
__ITERATOR_CATEGORY(const _DBG_iter_base< __STL_DBG_SLIST_BASE >&) {
  return forward_iterator_tag();
}
# endif

template <class _Tp, __STL_DEFAULT_ALLOCATOR_SELECT(_Tp) >
class _DBG_slist : public __STL_DBG_SLIST_BASE
{
private:
  typedef __STL_DBG_SLIST_BASE _Base;
  typedef _DBG_slist<_Tp,_Alloc> _Self;

public:

  __IMPORT_CONTAINER_TYPEDEFS(_Base)

  typedef _DBG_iter<_Base, _Nonconst_traits<value_type> >      iterator;
  typedef _DBG_iter<_Base, _Const_traits<value_type> >     const_iterator;

protected:
  friend class __owned_link;
  mutable __owned_list _M_iter_list;
  void _Invalidate_all() { _M_iter_list._Invalidate_all();}
  void _Invalidate_iterator(const iterator& __it) {__invalidate_iterator(&_M_iter_list, __it); }

public:
  const _Base* _Get_base() const { return (const _Base*)this; }
  _Base* _Get_base() { return (_Base*)this; }

public:

  explicit _DBG_slist(const allocator_type& __a = allocator_type()) :
    __STL_DBG_SLIST_BASE(__a) , _M_iter_list(_Get_base()) {}
  
  _DBG_slist(size_type __n, const value_type& __x,
	     const allocator_type& __a =  allocator_type()) :
    __STL_DBG_SLIST_BASE(__n, __x, __a), _M_iter_list(_Get_base()) {}
  
  explicit _DBG_slist(size_type __n) : __STL_DBG_SLIST_BASE(__n) , _M_iter_list(_Get_base()) {}
  
#ifdef __STL_MEMBER_TEMPLATES
  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InputIterator>
  _DBG_slist(_InputIterator __first, _InputIterator __last):
    __STL_DBG_SLIST_BASE(__first, __last, allocator_type()), _M_iter_list(_Get_base()) {} 

  template <class _InputIterator>
  _DBG_slist(_InputIterator __first, _InputIterator __last,
	     const allocator_type& __a) : 
    __STL_DBG_SLIST_BASE(__first, __last, __a), _M_iter_list(_Get_base()) {} 

#else /* __STL_MEMBER_TEMPLATES */

  _DBG_slist(const_iterator __first, const_iterator __last,
	     const allocator_type& __a = allocator_type() ) :
    __STL_DBG_SLIST_BASE(__first._M_iterator, __last._M_iterator, __a),
    _M_iter_list(_Get_base()) {}
  
  _DBG_slist(const value_type* __first, const value_type* __last,
        const allocator_type& __a =  allocator_type()) : 
    __STL_DBG_SLIST_BASE(__first, __last, __a), _M_iter_list(_Get_base())  {}

#endif /* __STL_MEMBER_TEMPLATES */

  _DBG_slist(const _Self& __x) : __STL_DBG_SLIST_BASE(__x), _M_iter_list(_Get_base()) {}
  
  _Self& operator= (const _Self& __x) {
    _Invalidate_all();
    (_Base&)*this = (const _Base&)__x;
    return *this;
  }
  
  ~_DBG_slist() {}

public:
  void assign(size_type __n, const _Tp& __val) {
    // fbp :check invalidation here !
    _Base::assign(__n, __val); 
  }

public:

  iterator before_begin() { return iterator(&_M_iter_list, _Base::before_begin()); }
  const_iterator before_begin() const
    { return const_iterator(&_M_iter_list, _Base::before_begin()); }

  iterator begin() { return iterator(&_M_iter_list, _Base::begin()); }
  const_iterator begin() const 
    { return const_iterator(&_M_iter_list,_Base::begin());}

  iterator end() { return iterator(&_M_iter_list, _Base::end()); }
  const_iterator end() const { return const_iterator(&_M_iter_list, _Base::end()); }

  void swap(_Self& __x) { 
    _M_iter_list._Swap_owners(__x._M_iter_list);
    _Base::swap(__x); 
  }

public:
  // fbp : checks here !
  reference front() { return _Base::front(); }
  const_reference front() const { return _Base::front(); }
  void pop_front() {
    _Base::pop_front();
  }
  iterator previous(const_iterator __pos) {
    return iterator(&_M_iter_list,_Base::previous(__pos._M_iterator));
  }
  const_iterator previous(const_iterator __pos) const {
    return const_iterator(&_M_iter_list,_Base::previous(__pos._M_iterator));
  }

public:

  iterator insert_after(iterator __pos, const value_type& __x) {
    return iterator(&_M_iter_list,_Base::insert_after(__pos._M_iterator, __x));
  }

  iterator insert_after(iterator __pos) {
    return iterator(&_M_iter_list,_Base::insert_after(__pos._M_iterator));
  }

  void insert_after(iterator __pos, size_type __n, const value_type& __x) {
    _Base::insert_after(__pos._M_iterator, __n, __x);
  }

#ifdef __STL_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    // fbp :check invalidation here !
    _Base::assign(__first, __last);
  }

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert_after(iterator __pos, _InIter __first, _InIter __last) {
    _Base::insert_after(__pos._M_iterator, __first, __last);
  }

  // We don't need any dispatching tricks here, because _M_insert_after_range
  // already does them.
  template <class _InIter>
  void insert(iterator __pos, _InIter __first, _InIter __last) {
    _Base::insert(__pos._M_iterator, __first, __last);

  }

#else /* __STL_MEMBER_TEMPLATES */

  void insert_after(iterator __pos,
                    const_iterator __first, const_iterator __last) {
    _Base::insert_after(__pos._M_iterator, __first._M_iterator, __last._M_iterator);
  }
  void insert_after(iterator __pos,
                    const value_type* __first, const value_type* __last) {
    _Base::insert_after(__pos._M_iterator, __first, __last);
  }

  void insert(iterator __pos, const_iterator __first, const_iterator __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _Base::insert(__pos._M_iterator, __first._M_iterator, __last._M_iterator);
  }
  void insert(iterator __pos, const value_type* __first, 
                              const value_type* __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _Base::insert(__pos._M_iterator, __first, __last);
  }

#endif /* __STL_MEMBER_TEMPLATES */

  iterator insert(iterator __pos, const value_type& __x) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    return iterator(&_M_iter_list, _Base::insert(__pos._M_iterator, __x));
  }

  iterator insert(iterator __pos) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    return iterator(&_M_iter_list, _Base::insert(__pos._M_iterator));
  }

  void insert(iterator __pos, size_type __n, const value_type& __x) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _Base::insert(__pos._M_iterator, __n, __x);
  } 
    
public:
  iterator erase_after(iterator __pos) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    return iterator(&_M_iter_list, _Base::erase_after(__pos._M_iterator));
  }
  iterator erase_after(iterator __before_first, iterator __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__before_first))
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__last))
    return iterator(&_M_iter_list, 
		    _Base::erase_after(__before_first._M_iterator, __last._M_iterator));
  } 

  iterator erase(iterator __pos) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    return iterator(&_M_iter_list, _Base::erase(__pos._M_iterator));
  }
  iterator erase(iterator __first, iterator __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__first))
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__last))
    return iterator(&_M_iter_list, 
		    _Base::erase(__first._M_iterator, __last._M_iterator));
  }

  void resize(size_type __new_size, const _Tp& __x) {
    _Base::resize(__new_size, __x);
  }
  void resize(size_type new_size) { resize(new_size, _Tp()); }

  void clear() {
    _Invalidate_all();      
    _Base::clear();
  }

public:
  // Moves the range [__before_first + 1, __before_last + 1) to *this,
  //  inserting it immediately after __pos.  This is constant time.
  void splice_after(iterator __pos, 
                    iterator __before_first, iterator __before_last)
  {
    if (__before_first != __before_last) {
      _Base::splice_after(__pos._M_iterator, 
                          __before_first._M_iterator, __before_last._M_iterator);
      __before_first++;
      __before_last++;
      __invalidate_range(__before_first._Owner(), 
                         __before_first, __before_last);
    }
  }

  // Moves the element that follows __prev to *this, inserting it immediately
  //  after __pos.  This is constant time.
  void splice_after(iterator __pos, iterator __prev)
  {
    _Base::splice_after(__pos._M_iterator, __prev._M_iterator);
    __invalidate_iterator(__prev._Owner(), ++__prev);
  }

  // Removes all of the elements from the list __x to *this, inserting
  // them immediately after __pos.  __x must not be *this.  Complexity:
  // linear in __x.size().
  void splice_after(iterator __pos, _Self& __x)
  {
    _Base::splice_after(__pos._M_iterator, (_Base&)__x);
    __x._Invalidate_all();
  }

  // Linear in distance(begin(), __pos), and linear in __x.size().
  void splice(iterator __pos, _Self& __x) {
    __STL_VERBOSE_ASSERT(!(&__x==this), _StlMsg_INVALID_ARGUMENT)
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    _Base::splice(__pos._M_iterator, (_Base&)__x);
    __x._Invalidate_all();
  }

  // Linear in distance(begin(), __pos), and in distance(__x.begin(), __i).
  void splice(iterator __pos, _Self& __x, iterator __i) {
    __STL_VERBOSE_ASSERT(&__x!=this, _StlMsg_INVALID_ARGUMENT)
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos) && 
                      __check_if_owner(&__x._M_iter_list ,__i))
    _Base::splice(__pos._M_iterator, (_Base&)__x, __i._M_iterator);
    __x._Invalidate_iterator(__i);
  }

  // Linear in distance(begin(), __pos), in distance(__x.begin(), __first),
  // and in distance(__first, __last).
  void splice(iterator __pos, _Self& __x, iterator __first, iterator __last)
  {
    __STL_VERBOSE_ASSERT(&__x!=this, _StlMsg_INVALID_ARGUMENT)
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list,__pos))
    if (__first != __last)
      _Base::splice(__pos._M_iterator, (_Base&)__x, __first._M_iterator, __last._M_iterator);      
    __invalidate_range(&__x._M_iter_list, __first, __last);
  }

public:

  void remove(const _Tp& __val) {
    _Base::remove(__val);
    //    __x._Invalidate_all();    
  }
  void unique() {
    _Base::unique();
  }
  void merge(_Self& __x) {
    _Base::merge((_Base&)__x);
    __x._Invalidate_all();
  }

#ifdef __STL_MEMBER_TEMPLATES

  template <class _Predicate> 
  void remove_if(_Predicate __pred) {
    _Base::remove_if(__pred);
  }

  template <class _BinaryPredicate> 
  void unique(_BinaryPredicate __pred) {
    _Base::unique(__pred);
  }

  template <class _StrictWeakOrdering> 
  void merge(_Self& __x, _StrictWeakOrdering __ord) {
    _Base::merge((_Base&)__x, __ord);
    __x._Invalidate_all();    
  }

#endif /* __STL_MEMBER_TEMPLATES */

};

#ifdef __STL_EXTRA_OPERATORS_FOR_DEBUG

template <class _Tp, class _Alloc>
inline bool 
operator==(const  _DBG_slist<_Tp,_Alloc>& _SL1, 
	   const  _DBG_slist<_Tp,_Alloc>& _SL2)
{
  return (const __STL_DBG_SLIST_BASE&)_SL1 == (const __STL_DBG_SLIST_BASE&)_SL2;
}

template <class _Tp, class _Alloc>
inline bool operator<(const  _DBG_slist<_Tp,_Alloc>& _SL1,
                      const  _DBG_slist<_Tp,_Alloc>& _SL2)
{
  return (const __STL_DBG_SLIST_BASE&)_SL1 < (const __STL_DBG_SLIST_BASE&)_SL2;
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _Tp, class _Alloc>
inline bool 
operator!=(const  _DBG_slist<_Tp,_Alloc>& _SL1, 
	   const  _DBG_slist<_Tp,_Alloc>& _SL2) {
  return !(_SL1 == _SL2);
}

template <class _Tp, class _Alloc>
inline bool 
operator>(const  _DBG_slist<_Tp,_Alloc>& _SL1, 
	  const  _DBG_slist<_Tp,_Alloc>& _SL2) {
  return _SL2 < _SL1;
}

template <class _Tp, class _Alloc>
inline bool 
operator<=(const  _DBG_slist<_Tp,_Alloc>& _SL1, 
	   const  _DBG_slist<_Tp,_Alloc>& _SL2) {
  return !(_SL2 < _SL1);
}

template <class _Tp, class _Alloc>
inline bool 
operator>=(const  _DBG_slist<_Tp,_Alloc>& _SL1, 
	   const  _DBG_slist<_Tp,_Alloc>& _SL2) {
  return !(_SL1 < _SL2);
}
#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */
#endif /* __STL_EXTRA_OPERATORS_FOR_DEBUG */

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class _Tp, class _Alloc>
inline void swap( _DBG_slist<_Tp,_Alloc>& __x, 
		  _DBG_slist<_Tp,_Alloc>& __y) {
  __x.swap(__y);
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_DBG_SLIST_H */

// Local Variables:
// mode:C++
// End:
