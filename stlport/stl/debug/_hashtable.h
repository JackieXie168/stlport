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

#ifndef __SGI_STL_INTERNAL_DBG_HASHTABLE_H
#define __SGI_STL_INTERNAL_DBG_HASHTABLE_H

// Hashtable class, used to implement the hashed associative containers
// hash_set, hash_map, hash_multiset, and hash_multimap.

# include <stl/debug/_iterator.h>

#  undef  hashtable
#  undef  _DBG_hashtable
#  define _DBG_hashtable  hashtable

#  define __STL_DBG_HT_SUPER \
__WORKAROUND_DBG_RENAME(hashtable) <_Val, _Key, _HF, _ExK, _EqK, _All>

__STL_BEGIN_NAMESPACE

# ifdef __STL_DEBUG_USE_DISTINCT_VALUE_TYPE_HELPERS
template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
inline _Val*
__VALUE_TYPE(const  _DBG_iter_base< __STL_DBG_HT_SUPER >&) {
  return (_Val*)0;
}

template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
inline forward_iterator_tag
__ITERATOR_CATEGORY(const  _DBG_iter_base< __STL_DBG_HT_SUPER >&) {
  return forward_iterator_tag();
}
# endif

template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
class _DBG_hashtable : public __STL_DBG_HT_SUPER {
  typedef _DBG_hashtable<_Val, _Key, _HF, _ExK, _EqK, _All> _Self;
  typedef __STL_DBG_HT_SUPER _Base;
public:
  typedef _Key key_type;
  typedef _HF hasher;
  typedef _EqK key_equal;

  __IMPORT_CONTAINER_TYPEDEFS(_Base)

public:
  typedef _DBG_iter<_Base, _Nonconst_traits<value_type> >  iterator;
  typedef _DBG_iter<_Base, _Const_traits<value_type> > const_iterator;
  typedef typename _Base::iterator _Base_iterator;
  typedef typename _Base::const_iterator _Base_const_iterator;

public:
  _DBG_hashtable(size_type __n,
		 const _HF&  __hf,
		 const _EqK& __eql,
		 const _ExK& __ext,
		 const allocator_type& __a = allocator_type()):
    __STL_DBG_HT_SUPER(__n, __hf, __eql, __ext, __a),
    _M_iter_list((_Base*)this) {}
  
  _DBG_hashtable(size_type __n,
		 const _HF&    __hf,
		 const _EqK&   __eql,
		 const allocator_type& __a = allocator_type()):
    
    __STL_DBG_HT_SUPER(__n, __hf, __eql, __a),
    _M_iter_list((_Base*)this) {}
  
  _DBG_hashtable(const _Self& __ht):
    __STL_DBG_HT_SUPER(__ht),
    _M_iter_list((_Base*)this) {}
  
  _Self& operator= (const _Self& __ht) {
    _M_iter_list._Invalidate_all();
    _Base::operator=(__ht);
    return *this;
  }
  
  void swap(_Self& __ht)
  {
   _Swap_owners(__ht);
   _Base::swap(__ht);
  }

  iterator begin() { return iterator(&_M_iter_list, _Base::begin()); }
  iterator end()   { return iterator(&_M_iter_list, _Base::end()); }

  const_iterator begin() const { return const_iterator(&_M_iter_list, _Base::begin()); }
  const_iterator end() const { return const_iterator(&_M_iter_list, _Base::end()); }

  pair<iterator, bool> insert_unique(const value_type& __obj)
  {
    pair < _Base_iterator, bool> __res =
      _Base::insert_unique(__obj);
    return pair<iterator, bool> ( iterator(&_M_iter_list, __res.first), __res.second);
  }

  iterator insert_equal(const value_type& __obj) {
    return iterator(&_M_iter_list, _Base::insert_equal(__obj));
  }
  
  pair<iterator, bool> insert_unique_noresize(const value_type& __obj) {
    pair < _Base_iterator, bool> __res =
      _Base::insert_unique_noresize(__obj);
    return pair<iterator, bool> ( iterator(&_M_iter_list, __res.first), __res.second);
  }
  
  iterator insert_equal_noresize(const value_type& __obj) {
    return iterator(&_M_iter_list, _Base::insert_equal_noresize(__obj));
  }
  
#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  void insert_unique(_InputIterator __f, _InputIterator __l) {
    _Base::insert_unique(__f, __l);
  }

  template <class _InputIterator>
  void insert_equal(_InputIterator __f, _InputIterator __l){
    _Base::insert_equal(__f, __l);
  }

#else /* __STL_MEMBER_TEMPLATES */

  void insert_unique(const value_type* __f, const value_type* __l) {
    _Base::insert_unique(__f, __l);
  }
  
  void insert_equal(const value_type* __f, const value_type* __l) {
    _Base::insert_equal(__f, __l);
  }
  
  void insert_unique(const_iterator __f, const_iterator __l) {
    _Base::insert_unique(__f._M_iterator, __l._M_iterator);
  }
  
  void insert_equal(const_iterator __f, const_iterator __l) {
    _Base::insert_equal(__f._M_iterator, __l._M_iterator);
  }
#endif /*__STL_MEMBER_TEMPLATES */
  
  iterator find(const key_type& __key) {
    return iterator(&_M_iter_list, _Base::find(__key));
  } 

  const_iterator find(const key_type& __key) const {
    return const_iterator(&_M_iter_list, _Base::find(__key));
  } 

  pair<iterator, iterator> 
  equal_range(const key_type& __key) {
    pair < _Base_iterator, _Base_iterator > __res =
      _Base::equal_range(__key);
    return pair<iterator,iterator> (iterator(&_M_iter_list,__res.first),
				    iterator(&_M_iter_list,__res.second));
  }

  pair<const_iterator, const_iterator> 
  equal_range(const key_type& __key) const {
    pair <  _Base_iterator, _Base_iterator > __res =
      _Base::equal_range(__key);
    return pair<const_iterator,const_iterator> (const_iterator(&_M_iter_list,__res.first),
				    const_iterator(&_M_iter_list,__res.second));
  }

  size_type erase(const key_type& __key) {
    return _Base::erase(__key);
  }

  void erase(const const_iterator& __it) {
    __STL_VERBOSE_ASSERT(__it._Owner()==&_M_iter_list, _StlMsg_NOT_OWNER)
    _Base::erase(__it._M_iterator);
  }
  void erase(const_iterator __first, const_iterator __last) {
    __STL_DEBUG_CHECK(__check_if_owner(&_M_iter_list, __first)&&
                      __check_if_owner(&_M_iter_list, __last))
    _Base::erase(__first._M_iterator, __last._M_iterator);
  }
  void resize(size_type __num_elements_hint) {
    _Base::resize(__num_elements_hint);
  }
  
  void clear() {
    _M_iter_list._Invalidate_all();
    _Base::clear();
  }

private:
  __owned_list _M_iter_list;

};

#ifdef __STL_EXTRA_OPERATORS_FOR_DEBUG
template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline bool operator==(const  _DBG_hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht1,
                       const  _DBG_hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht2)
{
  return hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::_M_equal( __ht1, __ht2 );
}
#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE
template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
inline bool operator!=(const  _DBG_hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>& __ht1,
                       const  _DBG_hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>& __ht2) {
  return !(__ht1 == __ht2);
}
#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

#endif /* __STL_EXTRA_OPERATORS_FOR_DEBUG */

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline void swap( _DBG_hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>& __ht1,
                  _DBG_hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>& __ht2) {
  __ht1.swap(__ht2);
}
#endif
__STL_END_NAMESPACE
#  undef  hashtable

#endif /* __SGI_STL_INTERNAL_HASHTABLE_H */

// Local Variables:
// mode:C++
// End:


