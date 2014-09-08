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

#ifndef __SGI_STL_INTERNAL_HASHTABLE_H
#define __SGI_STL_INTERNAL_HASHTABLE_H

// Hashtable class, used to implement the hashed associative containers
// hash_set, hash_map, hash_multiset, and hash_multimap.

#include <stl_algobase.h>
#include <stl_alloc.h>
#include <stl_construct.h>
#include <stl_tempbuf.h>
#include <stl_algo.h>
#include <stl_uninitialized.h>
#include <stl_function.h>

#include <stl_vector.h>
#include <stl_hash_fun.h>

__STL_BEGIN_NAMESPACE

# if defined ( __STL_USE_ABBREVS )
#  define _Hashtable_iterator         _hT__It
#  define _Hashtable_const_iterator   _hT__cIt
#  define _Hashtable_node             _hT__N
#  define _Hashtable_base             _hT__B
#  define hashtable                   _h__T
# endif


template <class _Val>
struct _Hashtable_node
{
  typedef _Hashtable_node<_Val> _Self;
  _Self* _M_next;
  _Val _M_val;
};  

// some compilers require the names of template parameters to be the same
template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
class hashtable;

template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
struct _Hashtable_iterator;

template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
struct _Hashtable_const_iterator;

template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
struct _Hashtable_iterator
# if defined ( __STL_DEBUG )
    : public __owned_link 
# endif
{
  typedef hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
          _Hashtable;
  typedef _Hashtable_iterator<_Val, _Key, _HF, 
                              _ExK, _EqK, _All>
          iterator;
  typedef _Hashtable_const_iterator<_Val, _Key, _HF, 
                                    _ExK, _EqK, _All>
          const_iterator;
  typedef _Hashtable_node<_Val> _Node;

  typedef forward_iterator_tag iterator_category;
  typedef _Val value_type;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef _Val& reference;
  typedef _Val* pointer;

  _Node* _M_cur;
  _Hashtable* _M_ht;

# if defined ( __STL_DEBUG )
  const _Node* _Get_iterator() const { return _M_cur; }
  //  const _Hashtable* _Owner() const { return (const _Hashtable*)__owned_link::_Owner(); }
  _Hashtable_iterator(_Node* __n, _Hashtable* __tab) : 
      __owned_link(__tab), _M_cur(__n), _M_ht(__tab) {}
  _Hashtable_iterator() : __owned_link(0) {}
# else
  _Hashtable_iterator(_Node* __n, _Hashtable* __tab) 
    : _M_cur(__n), _M_ht(__tab) {}
  _Hashtable_iterator() {}
# endif
  reference operator*() const { 
    __stl_verbose_assert(_Valid() && _M_cur!=0,__STL_MSG_NOT_DEREFERENCEABLE);
    return _M_cur->_M_val; 
  }

#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */
  iterator& operator++();
  iterator operator++(int);
  bool operator==(const iterator& __it) const { 
      __stl_debug_check(__check_same_owner_or_null(*this,__it));
      return _M_cur == __it._M_cur; 
  }
  bool operator!=(const iterator& __it) const { 
      __stl_debug_check(__check_same_owner_or_null(*this,__it));
    return _M_cur != __it._M_cur; 
  }

};


template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
struct _Hashtable_const_iterator 
# if defined ( __STL_DEBUG )
    : public __owned_link 
# endif
{
  typedef hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
          _Hashtable;
  typedef _Hashtable_iterator<_Val,_Key,_HF, 
                              _ExK,_EqK,_All>
          iterator;
  typedef _Hashtable_const_iterator<_Val, _Key, _HF, 
                                    _ExK, _EqK, _All>
          const_iterator;
  typedef _Hashtable_node<_Val> _Node;

  typedef forward_iterator_tag iterator_category;
  typedef _Val value_type;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef const _Val& reference;
  typedef const _Val* pointer;

  const _Node* _M_cur;
  const _Hashtable* _M_ht;

# if defined ( __STL_DEBUG )
  //  const _Hashtable* _Owner() const { return (const _Hashtable*)__owned_link::_Owner(); }
  const _Node* get_iterator() const { return _M_cur; }
  _Hashtable_const_iterator(const _Node* __n, const _Hashtable* __tab)
    : __owned_link(__tab), _M_cur(__n), _M_ht(__tab) {}
  _Hashtable_const_iterator() : __owned_link(0) {}
  _Hashtable_const_iterator(const iterator& __it) : 
    __owned_link(__it), _M_cur(__it._M_cur), _M_ht(__it._M_ht) {}
# else
  _Hashtable_const_iterator(const _Node* __n, const _Hashtable* __tab)
    : _M_cur(__n), _M_ht(__tab) {}
  _Hashtable_const_iterator() {}
  _Hashtable_const_iterator(const iterator& __it) : _M_cur(__it._M_cur), _M_ht(__it._M_ht) {}
# endif

  reference operator*() const { 
      __stl_verbose_assert(_Valid() && _M_cur!=0,__STL_MSG_NOT_DEREFERENCEABLE);
      return _M_cur->_M_val; 
  }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */
  const_iterator& operator++();
  inline const_iterator operator++(int);
  bool operator==(const const_iterator& __it) const { 
    __stl_debug_check(__check_same_owner(*this,__it));
    return _M_cur == __it._M_cur; 
  }
  bool operator!=(const const_iterator& __it) const { 
    __stl_debug_check(__check_same_owner(*this,__it));
    return _M_cur != __it._M_cur; 
  }
};

// Note: assumes long is at least 32 bits.
# define __stl_num_primes  28

#if ( __STL_STATIC_TEMPLATE_DATA > 0 ) && ! defined (__GNUC__)
#  define __stl_prime_list _Stl_prime<size_type>::_M_list
   template <class _Tp>
   struct _Stl_prime {
   public:
       static const _Tp _M_list[__stl_num_primes];
   };
   template <class _Tp>
   const _Tp _Stl_prime<_Tp>::_M_list[__stl_num_primes] =
#  else
#  if ( __STL_WEAK_ATTRIBUTE > 0 )
      extern const unsigned long __stl_prime_list[__stl_num_primes] __attribute__((weak)) =
#  else
      // give up
      static const unsigned long __stl_prime_list[__stl_num_primes] =
#  endif /* __STL_WEAK_ATTRIBUTE */
#endif /* __STL_STATIC_TEMPLATE_DATA */
{
  53ul,         97ul,         193ul,       389ul,       769ul,
  1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
  49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
  1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
  50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
  1610612741ul, 3221225473ul, 4294967291ul
};

// Forward declaration of operator==.

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
class hashtable;

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline bool operator==(const hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht1,
		       const hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht2);

// Hashtables handle allocators a bit differently than other containers
//  do.  If we're using standard-conforming allocators, then a hashtable
//  unconditionally has a member variable to hold its allocator, even if
//  it so happens that all instances of the allocator type are identical.
// This is because, for hashtables, this extra storage is negligible.  
//  Additionally, a base class wouldn't serve any other purposes; it 
//  wouldn't, for example, simplify the exception-handling code.
template <class _Val, class _Key, class _HF,
          class _ExK, class _EqK, class _All>
# if defined ( __STL_DEBUG )
class hashtable : public __owned_list {
# else
class hashtable {
# endif
  typedef hashtable<_Val, _Key, _HF, _ExK, _EqK, _All> _Self;
public:
  typedef _Key key_type;
  typedef _Val value_type;
  typedef _HF hasher;
  typedef _EqK key_equal;

  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;

  hasher hash_funct() const { return _M_hash; }
  key_equal key_eq() const { return _M_equals; }

private:
  typedef _Hashtable_node<_Val> _Node;

#ifdef __STL_USE_STD_ALLOCATORS
public:
  typedef typename _Alloc_traits<_Val,_All>::allocator_type allocator_type;
  allocator_type get_allocator() const { return _M_node_allocator; }
private:
  typename _Alloc_traits<_Node, _All>::allocator_type _M_node_allocator;
  _Node* _M_get_node() { return _M_node_allocator.allocate(1); }
  void _M_put_node(_Node* __p) { _M_node_allocator.deallocate(__p, 1); }
# define __HASH_ALLOC_INIT(__a) _M_node_allocator(__a), 
# define __HASH_ALLOC_PARAM   allocator_type
#else /* __STL_USE_STD_ALLOCATORS */
public:
  typedef _All allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }
private:
  typedef simple_alloc<_Node, _All> _M_node_allocator_type;
  _Node* _M_get_node() { return _M_node_allocator_type::allocate(1); }
  void _M_put_node(_Node* __p) { _M_node_allocator_type::deallocate(__p, 1); }
# define __HASH_ALLOC_INIT(__a)
# define __HASH_ALLOC_PARAM _All
#endif /* __STL_USE_STD_ALLOCATORS */
  typedef __vector__<_Hashtable_node<_Val>*,_All> _BucketVector;
private:
  hasher                _M_hash;
  key_equal             _M_equals;
  _ExK                  _M_get_key;
  _BucketVector         _M_buckets;
  size_type             _M_num_elements;
  const _Node* _M_get_bucket(size_t __n) const { return _M_buckets[__n]; }

public:
  typedef _Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>
          iterator;
  typedef _Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,
                                    _All>
          const_iterator;

  friend struct
  _Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>;
  friend struct
  _Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>;

public:
  hashtable(size_type __n,
            const _HF&  __hf,
            const _EqK& __eql,
            const _ExK& __ext,
            const __HASH_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__HASH_ALLOC_PARAM))
    : __HASH_ALLOC_INIT(__a)
      _M_hash(__hf),
      _M_equals(__eql),
      _M_get_key(__ext),
      _M_buckets(__STL_CONVERT_ALLOCATOR(__a,_Node*)),
      _M_num_elements(0)
  {
    _M_initialize_buckets(__n);
  }

  hashtable(size_type __n,
            const _HF&    __hf,
            const _EqK&   __eql,
            const __HASH_ALLOC_PARAM& __a = __STL_ALLOC_INSTANCE(__HASH_ALLOC_PARAM))
    : __HASH_ALLOC_INIT(__a)
      _M_hash(__hf),
      _M_equals(__eql),
      _M_get_key(_ExK()),
      _M_buckets(__STL_CONVERT_ALLOCATOR(__a,_Node*)),
      _M_num_elements(0)
  {
    _M_initialize_buckets(__n);
  }

  hashtable(const _Self& __ht)
    : __HASH_ALLOC_INIT(__ht.get_allocator())
      _M_hash(__ht._M_hash),
      _M_equals(__ht._M_equals),
      _M_get_key(__ht._M_get_key),
      _M_buckets(__STL_CONVERT_ALLOCATOR(__ht.get_allocator(),_Node*)),
      _M_num_elements(0)
  {
    __stl_debug_do(_Safe_init(0));
    _M_copy_from(__ht);
    __stl_debug_do(_Safe_init(this)); /* fbp : ??? */
  }

#undef __HASH_ALLOC_INIT
#undef __HASH_ALLOC_PARAM
  _Self& operator= (const _Self& __ht)
  {
    if (&__ht != this) {
      clear();
      _M_hash = __ht._M_hash;
      _M_equals = __ht._M_equals;
      _M_get_key = __ht._M_get_key;
      _M_copy_from(__ht);
    }
    return *this;
  }

  ~hashtable() { clear(); }

  size_type size() const { return _M_num_elements; }
  size_type max_size() const { return size_type(-1); }
  bool empty() const { return size() == 0; }

  void swap(_Self& __ht)
  {
    __STD::swap(_M_hash, __ht._M_hash);
    __STD::swap(_M_equals, __ht._M_equals);
    __STD::swap(_M_get_key, __ht._M_get_key);
    _M_buckets.swap(__ht._M_buckets);
    __STD::swap(_M_num_elements, __ht._M_num_elements);
    __stl_debug_do(_Swap_owners(__ht));
  }

  iterator begin()
  { 
    for (size_type __n = 0; __n < _M_buckets.size(); ++__n)
      if (_M_buckets[__n])
        return iterator(_M_buckets[__n], this);
    return end();
  }

  iterator end() { return iterator((_Node*)0, this); }

  const_iterator begin() const
  {
    for (size_type __n = 0; __n < _M_buckets.size(); ++__n)
      if (_M_buckets[__n])
        return const_iterator(_M_buckets[__n], this);
    return end();
  }

  const_iterator end() const { return const_iterator((_Node*)0, this); }
# if 0
  friend bool __STD_QUAL operator== __STL_NULL_TMPL_ARGS (const hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>&,
							  const hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>&);
# else
  static bool _M_equal (const hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>&,
			const hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>&);
# endif

public:

  size_type bucket_count() const { return _M_buckets.size(); }

  size_type max_bucket_count() const
    { return __stl_prime_list[__stl_num_primes - 1]; } 

  size_type elems_in_bucket(size_type __bucket) const
  {
    size_type __result = 0;
    for (_Node* __cur = _M_buckets[__bucket]; __cur; __cur = __cur->_M_next)
      __result += 1;
    return __result;
  }

  pair<iterator, bool> insert_unique(const value_type& __obj)
  {
    resize(_M_num_elements + 1);
    return insert_unique_noresize(__obj);
  }

  iterator insert_equal(const value_type& __obj)
  {
    resize(_M_num_elements + 1);
    return insert_equal_noresize(__obj);
  }

  pair<iterator, bool> insert_unique_noresize(const value_type& __obj);
  iterator insert_equal_noresize(const value_type& __obj);
 
#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  void insert_unique(_InputIterator __f, _InputIterator __l)
  {
    insert_unique(__f, __l, __ITERATOR_CATEGORY(__f));
  }

  template <class _InputIterator>
  void insert_equal(_InputIterator __f, _InputIterator __l)
  {
    insert_equal(__f, __l, __ITERATOR_CATEGORY(__f));
  }

  template <class _InputIterator>
  void insert_unique(_InputIterator __f, _InputIterator __l,
                     input_iterator_tag)
  {
    for ( ; __f != __l; ++__f)
      insert_unique(*__f);
  }

  template <class _InputIterator>
  void insert_equal(_InputIterator __f, _InputIterator __l,
                    input_iterator_tag)
  {
    for ( ; __f != __l; ++__f)
      insert_equal(*__f);
  }

  template <class _ForwardIterator>
  void insert_unique(_ForwardIterator __f, _ForwardIterator __l,
                     forward_iterator_tag)
  {
    size_type __n = 0;
    distance(__f, __l, __n);
    resize(_M_num_elements + __n);
    for ( ; __n > 0; --__n, ++__f)
      insert_unique_noresize(*__f);
  }

  template <class _ForwardIterator>
  void insert_equal(_ForwardIterator __f, _ForwardIterator __l,
                    forward_iterator_tag)
  {
    size_type __n = 0;
    distance(__f, __l, __n);
    resize(_M_num_elements + __n);
    for ( ; __n > 0; --__n, ++__f)
      insert_equal_noresize(*__f);
  }

#else /* __STL_MEMBER_TEMPLATES */
  void insert_unique(const value_type* __f, const value_type* __l)
  {
    size_type __n = __l - __f;
    resize(_M_num_elements + __n);
    for ( ; __n > 0; --__n, ++__f)
      insert_unique_noresize(*__f);
  }

  void insert_equal(const value_type* __f, const value_type* __l)
  {
    size_type __n = __l - __f;
    resize(_M_num_elements + __n);
    for ( ; __n > 0; --__n, ++__f)
      insert_equal_noresize(*__f);
  }

  void insert_unique(const_iterator __f, const_iterator __l)
  {
    size_type __n = 0;
    distance(__f, __l, __n);
    resize(_M_num_elements + __n);
    for ( ; __n > 0; --__n, ++__f)
      insert_unique_noresize(*__f);
  }

  void insert_equal(const_iterator __f, const_iterator __l)
  {
    size_type __n = 0;
    distance(__f, __l, __n);
    resize(_M_num_elements + __n);
    for ( ; __n > 0; --__n, ++__f)
      insert_equal_noresize(*__f);
  }
#endif /*__STL_MEMBER_TEMPLATES */

  reference find_or_insert(const value_type& __obj);

  iterator find(const key_type& __key) 
  {
    size_type __n = _M_bkt_num_key(__key);
    _Node* __first;
    for ( __first = _M_buckets[__n];
          __first && !_M_equals(_M_get_key(__first->_M_val), __key);
          __first = __first->_M_next)
      {}
    return iterator(__first, this);
  } 

  const_iterator find(const key_type& __key) const
  {
    size_type __n = _M_bkt_num_key(__key);
    const _Node* __first;
    for ( __first = _M_buckets[__n];
          __first && !_M_equals(_M_get_key(__first->_M_val), __key);
          __first = __first->_M_next)
      {}
    return const_iterator(__first, this);
  } 

  size_type count(const key_type& __key) const
  {
    const size_type __n = _M_bkt_num_key(__key);
    size_type __result = 0;

    for (const _Node* __cur = _M_buckets[__n]; __cur; __cur = __cur->_M_next)
      if (_M_equals(_M_get_key(__cur->_M_val), __key))
        ++__result;
    return __result;
  }

  pair<iterator, iterator> 
  equal_range(const key_type& __key);

  pair<const_iterator, const_iterator> 
  equal_range(const key_type& __key) const;

  size_type erase(const key_type& __key);
  void erase(const iterator& __it);
  void erase(iterator __first, iterator __last);

  void erase(const const_iterator& __it);
  void erase(const_iterator __first, const_iterator __last);

  void resize(size_type __num_elements_hint);
  void clear();
# if defined (__STL_DEBUG)
    void _Invalidate_node(_Node* __it) { 
      __invalidate_iterator((__owned_list*)this,__it,iterator());
    }
# endif

private:

  size_type _M_next_size(size_type __n) const
    { 
      const size_type* __first = (const size_type*)__stl_prime_list;
      const size_type* __last =  (const size_type*)__stl_prime_list + __stl_num_primes;
      const size_type* pos = lower_bound(__first, __last, __n);
      return (pos == __last ? *(__last - 1) : *pos);
    }

  void _M_initialize_buckets(size_type __n)
  {
    const size_type __n_buckets = _M_next_size(__n);
    _M_buckets.reserve(__n_buckets);
    _M_buckets.insert(_M_buckets.end(), __n_buckets, (_Node*) 0);
    _M_num_elements = 0;
    __stl_debug_do(_Safe_init(this));
  }

  size_type _M_bkt_num_key(const key_type& __key) const
  {
    return _M_bkt_num_key(__key, _M_buckets.size());
  }

  size_type _M_bkt_num(const value_type& __obj) const
  {
    return _M_bkt_num_key(_M_get_key(__obj));
  }

  size_type _M_bkt_num_key(const key_type& __key, size_t __n) const
  {
    return _M_hash(__key) % __n;
  }

  size_type _M_bkt_num(const value_type& __obj, size_t __n) const
  {
    return _M_bkt_num_key(_M_get_key(__obj), __n);
  }

  _Node* _M_new_node(const value_type& __obj)
  {
    _Node* __n = _M_get_node();
    __n->_M_next = 0;
    __STL_TRY {
      construct(&__n->_M_val, __obj);
      return __n;
    }
    __STL_UNWIND(_M_put_node(__n));
    return __n;
  }
  
  void _M_delete_node(_Node* __n)
  {
    __stl_debug_do(_Invalidate_node(__n));
    destroy(&__n->_M_val);
    _M_put_node(__n);
  }

  void _M_erase_bucket(const size_type __n, _Node* __first, _Node* __last);
  void _M_erase_bucket(const size_type __n, _Node* __last);

  void _M_copy_from(const _Self& __ht);
};


// fbp: these defines are for outline methods definitions.
// needed to definitions to be portable. Should not be used in method bodies.

# if defined ( __STL_NESTED_TYPE_PARAM_BUG )
#  define __difference_type__ ptrdiff_t
#  define __size_type__       size_t
#  define __value_type__      _Val
#  define __key_type__        _Key
#  define __node__            _Hashtable_node<_Val>
#  define __reference__       _Val&
#  define __iterator__        _Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>
#  define __const_iterator__  _Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>
# else
#  define __difference_type__  typename hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::difference_type
#  define __size_type__        __STL_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::size_type
#  define __value_type__       __STL_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::value_type
#  define __key_type__         __STL_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::key_type
#  define __node__             __STL_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::_Node
#  define __reference__        __STL_TYPENAME_ON_RETURN_TYPE  hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::reference
#  define __iterator__         __STL_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::iterator
#  define __const_iterator__   __STL_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::const_iterator
# endif


template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
_Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&
_Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>::operator++()
{
  const _Node* __old = _M_cur;
  _M_cur = _M_cur->_M_next;
  if (!_M_cur) {
    size_type __bucket = _M_ht->_M_bkt_num(__old->_M_val);
    while (!_M_cur && ++__bucket < _M_ht->_M_buckets.size())
      _M_cur = _M_ht->_M_buckets[__bucket];
  }
  return *this;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline _Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>
_Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>::operator++(int)
{
  iterator __tmp = *this;
  ++*this;
  return __tmp;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
_Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&
_Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>::operator++()
{
  const _Node* __old = _M_cur;
  __stl_verbose_assert(__old!=0,__STL_MSG_INVALID_ADVANCE);
  _M_cur = _M_cur->_M_next;
  if (!_M_cur) {
    size_type __bucket = _M_ht->_M_bkt_num(__old->_M_val);
    while (!_M_cur && ++__bucket < _M_ht->_M_buckets.size())
      _M_cur = _M_ht->_M_buckets[__bucket];
  }
  return *this;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline _Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>
_Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>::operator++(int)
{
  const_iterator __tmp = *this;
  ++*this;
  return __tmp;
}

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline forward_iterator_tag
iterator_category(const _Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&)
{
  return forward_iterator_tag();
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline _Val* 
value_type(const _Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&)
{
  return (_Val*) 0;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline ptrdiff_t*
distance_type(const _Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&)
{
  return (__difference_type__*) 0;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline forward_iterator_tag
iterator_category(const _Hashtable_const_iterator<_Val,_Key,_HF,
                                                  _ExK,_EqK,_All>&)
{
  return forward_iterator_tag();
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline _Val* 
value_type(const _Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&)
{
  return (_Val*) 0;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline ptrdiff_t*
distance_type(const _Hashtable_const_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&)
{
  return (__difference_type__*) 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline bool operator==(const hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht1,
                       const hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht2)
{
  return hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::_M_equal( __ht1, __ht2 );
}


template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
bool 
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::_M_equal(
						  const hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht1,
						  const hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht2)
{
  //  typedef _Hashtable_node<_Val> _Node;
  if (__ht1.bucket_count() != __ht2.bucket_count())
    return false;
  for (size_t __n = 0; __n < __ht1.bucket_count(); ++__n) {
    const _Node* __cur1 = __ht1._M_get_bucket(__n);
    const _Node* __cur2 = __ht2._M_get_bucket(__n);
    for ( ; __cur1 && __cur2 && __cur1->_M_val == __cur2->_M_val;
          __cur1 = __cur1->_M_next, __cur2 = __cur2->_M_next)
      {}
    if (__cur1 || __cur2)
      return false;
  }
  return true;
}  

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
inline bool operator!=(const hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>& __ht1,
                       const hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>& __ht2) {
  return !(__ht1 == __ht2);
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
inline void swap(hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>& __ht1,
                 hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>& __ht2) {
  __ht1.swap(__ht2);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */


template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
pair<__iterator__, bool> 
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::insert_unique_noresize(const __value_type__& __obj)
{
  const size_type __n = _M_bkt_num(__obj);
  _Node* __first = _M_buckets[__n];

  for (_Node* __cur = __first; __cur; __cur = __cur->_M_next) 
    if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj)))
      return pair<iterator, bool>(iterator(__cur, this), false);

  _Node* __tmp = _M_new_node(__obj);
  __tmp->_M_next = __first;
  _M_buckets[__n] = __tmp;
  ++_M_num_elements;
  return pair<iterator, bool>(iterator(__tmp, this), true);
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
__iterator__ 
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::insert_equal_noresize(const __value_type__& __obj)
{
  const size_type __n = _M_bkt_num(__obj);
  _Node* __first = _M_buckets[__n];

  for (_Node* __cur = __first; __cur; __cur = __cur->_M_next) 
    if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj))) {
      _Node* __tmp = _M_new_node(__obj);
      __tmp->_M_next = __cur->_M_next;
      __cur->_M_next = __tmp;
      ++_M_num_elements;
      return iterator(__tmp, this);
    }

  _Node* __tmp = _M_new_node(__obj);
  __tmp->_M_next = __first;
  _M_buckets[__n] = __tmp;
  ++_M_num_elements;
  return iterator(__tmp, this);
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
__reference__ 
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::find_or_insert(const __value_type__& __obj)
{
  resize(_M_num_elements + 1);

  size_type __n = _M_bkt_num(__obj);
  _Node* __first = _M_buckets[__n];

  for (_Node* __cur = __first; __cur; __cur = __cur->_M_next)
    if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj)))
      return __cur->_M_val;

  _Node* __tmp = _M_new_node(__obj);
  __tmp->_M_next = __first;
  _M_buckets[__n] = __tmp;
  ++_M_num_elements;
  return __tmp->_M_val;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
pair<__iterator__,
     __iterator__> 
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::equal_range(const __key_type__& __key)
{
  typedef pair<iterator, iterator> _Pii;
  const size_type __n = _M_bkt_num_key(__key);

  for (_Node* __first = _M_buckets[__n]; __first; __first = __first->_M_next)
    if (_M_equals(_M_get_key(__first->_M_val), __key)) {
      for (_Node* __cur = __first->_M_next; __cur; __cur = __cur->_M_next)
        if (!_M_equals(_M_get_key(__cur->_M_val), __key))
          return _Pii(iterator(__first, this), iterator(__cur, this));
      for (size_type __m = __n + 1; __m < _M_buckets.size(); ++__m)
        if (_M_buckets[__m])
          return _Pii(iterator(__first, this),
                     iterator(_M_buckets[__m], this));
      return _Pii(iterator(__first, this), end());
    }
  return _Pii(end(), end());
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
pair<__const_iterator__, 
     __const_iterator__> 
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::equal_range(const __key_type__& __key) const
{
  typedef pair<const_iterator, const_iterator> _Pii;
  const size_type __n = _M_bkt_num_key(__key);

  for (const _Node* __first = _M_buckets[__n] ;
       __first; 
       __first = __first->_M_next) {
    if (_M_equals(_M_get_key(__first->_M_val), __key)) {
      for (const _Node* __cur = __first->_M_next;
           __cur;
           __cur = __cur->_M_next)
        if (!_M_equals(_M_get_key(__cur->_M_val), __key))
          return _Pii(const_iterator(__first, this),
                      const_iterator(__cur, this));
      for (size_type __m = __n + 1; __m < _M_buckets.size(); ++__m)
        if (_M_buckets[__m])
          return _Pii(const_iterator(__first, this),
                      const_iterator(_M_buckets[__m], this));
      return _Pii(const_iterator(__first, this), end());
    }
  }
  return _Pii(end(), end());
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
__size_type__ 
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::erase(const __key_type__& __key)
{
  const size_type __n = _M_bkt_num_key(__key);
  _Node* __first = _M_buckets[__n];
  size_type __erased = 0;

  if (__first) {
    _Node* __cur = __first;
    _Node* __next = __cur->_M_next;
    while (__next) {
      if (_M_equals(_M_get_key(__next->_M_val), __key)) {
        __cur->_M_next = __next->_M_next;
        _M_delete_node(__next);
        __next = __cur->_M_next;
        ++__erased;
        --_M_num_elements;
      }
      else {
        __cur = __next;
        __next = __cur->_M_next;
      }
    }
    if (_M_equals(_M_get_key(__first->_M_val), __key)) {
      _M_buckets[__n] = __first->_M_next;
      _M_delete_node(__first);
      ++__erased;
      --_M_num_elements;
    }
  }
  return __erased;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
void hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::erase(const __iterator__& __it)
{
  _Node* const __p = __it._M_cur;
  __stl_verbose_assert(__it._Owner()==this, __STL_MSG_NOT_OWNER);
  if (__p) {
    const size_type __n = _M_bkt_num(__p->_M_val);
    _Node* __cur = _M_buckets[__n];

    if (__cur == __p) {
      _M_buckets[__n] = __cur->_M_next;
      _M_delete_node(__cur);
      --_M_num_elements;
    }
    else {
      _Node* __next = __cur->_M_next;
      while (__next) {
        if (__next == __p) {
          __cur->_M_next = __next->_M_next;
          _M_delete_node(__next);
          --_M_num_elements;
          break;
        }
        else {
          __cur = __next;
          __next = __cur->_M_next;
        }
      }
    }
  }
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
void hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::erase(__iterator__ __first, __iterator__ __last)
{
  size_type __f_bucket = __first._M_cur ? 
    _M_bkt_num(__first._M_cur->_M_val) : _M_buckets.size();
  size_type __l_bucket = __last._M_cur ? 
    _M_bkt_num(__last._M_cur->_M_val) : _M_buckets.size();
  __stl_debug_check(__check_if_owner((__owned_list*)this,
				     __first)&&__check_if_owner((__owned_list*)this,
								__last));
  __stl_verbose_assert(__f_bucket <= __l_bucket, __STL_MSG_INVALID_RANGE);

  if (__first._M_cur == __last._M_cur)
    return;
  else if (__f_bucket == __l_bucket)
    _M_erase_bucket(__f_bucket, __first._M_cur, __last._M_cur);
  else {
    _M_erase_bucket(__f_bucket, __first._M_cur, 0);
    for (size_type __n = __f_bucket + 1; __n < __l_bucket; ++__n)
      _M_erase_bucket(__n, 0);
    if (__l_bucket != _M_buckets.size())
      _M_erase_bucket(__l_bucket, __last._M_cur);
  }
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline void
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::erase(__const_iterator__ __first,
                                             __const_iterator__ __last)
{
  erase(iterator(__CONST_CAST(_Node*,__first._M_cur),
                 __CONST_CAST(_Self*,__first._M_ht)),
        iterator(__CONST_CAST(_Node*,__last._M_cur),
                 __CONST_CAST(_Self*,__last._M_ht)));
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline void
hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::erase(const __const_iterator__& __it)
{
  erase(iterator(__CONST_CAST(_Node*,__it._M_cur),
                 __CONST_CAST(_Self*,__it._M_ht)));
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
void hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::resize(__size_type__ __num_elements_hint)
{
  const size_type __old_n = _M_buckets.size();
  if (__num_elements_hint > __old_n) {
    const size_type __n = _M_next_size(__num_elements_hint);
    if (__n > __old_n) {
      _BucketVector __tmp(__n, (_Hashtable_node<_Val>*)(0),
			  _M_buckets.get_allocator());
      __STL_TRY {
        for (size_type __bucket = 0; __bucket < __old_n; ++__bucket) {
          _Node* __first = _M_buckets[__bucket];
          while (__first) {
            size_type __new_bucket = _M_bkt_num(__first->_M_val, __n);
            _M_buckets[__bucket] = __first->_M_next;
            __first->_M_next = __tmp[__new_bucket];
            __tmp[__new_bucket] = __first;
            __first = _M_buckets[__bucket];          
          }
        }
        _M_buckets.swap(__tmp);
      }
#         ifdef __STL_USE_EXCEPTIONS
      catch(...) {
        for (size_type __bucket = 0; __bucket < __tmp.size(); ++__bucket) {
          while (__tmp[__bucket]) {
            _Node* __next = __tmp[__bucket]->_M_next;
            _M_delete_node(__tmp[__bucket]);
            __tmp[__bucket] = __next;
          }
        }
        throw;
      }
#         endif /* __STL_USE_EXCEPTIONS */
    }
  }
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
void hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::_M_erase_bucket(const __size_type__ __n, __node__* __first, __node__* __last)
{
  _Node* __cur = _M_buckets[__n];
  if (__cur == __first)
    _M_erase_bucket(__n, __last);
  else {
    _Node* __next;
    for (__next = __cur->_M_next; 
         __next != __first; 
         __cur = __next, __next = __cur->_M_next)
      ;
    while (__next) {
      __cur->_M_next = __next->_M_next;
      _M_delete_node(__next);
      __next = __cur->_M_next;
      --_M_num_elements;
    }
  }
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
void hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::_M_erase_bucket(const __size_type__ __n, __node__* __last)
{
  _Node* __cur = _M_buckets[__n];
  while (__cur && __cur != __last) {
    _Node* __next = __cur->_M_next;
    _M_delete_node(__cur);
    __cur = __next;
    _M_buckets[__n] = __cur;
    --_M_num_elements;
  }
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
void hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>::clear()
{
  for (size_type __i = 0; __i < _M_buckets.size(); ++__i) {
    _Node* __cur = _M_buckets[__i];
    while (__cur != 0) {
      _Node* __next = __cur->_M_next;
      _M_delete_node(__cur);
      __cur = __next;
    }
    _M_buckets[__i] = 0;
  }
  _M_num_elements = 0;
  __stl_debug_do(_Invalidate_all());
}

    
template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
void hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>
  ::_M_copy_from(const hashtable<_Val,_Key,_HF,_ExK,_EqK,_All>& __ht)
{
  _M_buckets.clear();
  _M_buckets.reserve(__ht._M_buckets.size());
  _M_buckets.insert(_M_buckets.end(), __ht._M_buckets.size(), (_Node*) 0);
  __STL_TRY {
    for (size_type __i = 0; __i < __ht._M_buckets.size(); ++__i) {
      const _Node* __cur = __ht._M_buckets[__i];
      if (__cur) {
        _Node* __copy = _M_new_node(__cur->_M_val);
        _M_buckets[__i] = __copy;

        for (_Node* __next = __cur->_M_next; 
             __next; 
             __cur = __next, __next = __cur->_M_next) {
          __copy->_M_next = _M_new_node(__next->_M_val);
          __copy = __copy->_M_next;
        }
      }
    }
    _M_num_elements = __ht._M_num_elements;
  }
  __STL_UNWIND(clear());
}


# undef __iterator__ 
# undef __const_iterator__ 
# undef __difference_type__ 
# undef __size_type__       
# undef __value_type__      
# undef __key_type__        
# undef __node__            
# undef __stl_num_primes
# undef __stl_prime_list

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_HASHTABLE_H */

// Local Variables:
// mode:C++
// End:


