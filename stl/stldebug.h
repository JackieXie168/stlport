/*
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

#ifndef __SGI_STL_STLDEBUG_H
# define __SGI_STL_STLDEBUG_H

# include <stl_config.h>

# if defined (__STL_ASSERTIONS)
#  if !defined( __STL_DEBUG_MESSAGE )
#   ifdef __STL_USE_NEW_STYLE_HEADERS
#    include <cstdarg>
#    include <cstdio>
#   else
#    include <stdarg.h>
#    include <stdio.h>
#   endif

__STL_BEGIN_NAMESPACE
template <class _Dummy>
void __stl_debug_engine<_Dummy>::_Message(const char * format_str, ...)
{
#if defined(__MSL__) && __MSL__ <= 0x4011
	using std::__files;
#endif
	va_list args;
	va_start( args, format_str );
	__STL_VENDOR_CSTD::vfprintf(stderr, format_str, args);
	__STL_DEBUG_MESSAGE_POST
	va_end(args);
}
__STL_END_NAMESPACE
#  endif /* __STL_DEBUG_MESSAGE */
# endif /* __STL_ASSERTIONS */

#if defined ( __STL_DEBUG )
#if defined(__MRC__)		//*TY 01/15/1999 - MrCpp optimizer confuses on this debugging code
#pragma options opt none
#endif

# ifdef __STL_USE_NEW_STYLE_HEADERS
// stderr
#  include <cstdio>
#  include <cstdlib>
# else
#  include <stdio.h>
#  include <stdlib.h>
# endif

# ifdef __STL_THREADS
#  include <stl_threads.h>
#  ifdef __STL_MUTABLE 
#   define __STL_ACQUIRE_LOCK(_Lock) _Lock._M_acquire_lock();
#   define __STL_RELEASE_LOCK(_Lock) _Lock._M_release_lock();
#  else
#   define __STL_ACQUIRE_LOCK(_Lock) ((_STL_mutex_lock&)_Lock)._M_acquire_lock();
#   define __STL_RELEASE_LOCK(_Lock) ((_STL_mutex_lock&)_Lock)._M_release_lock();
#  endif /* __STL_MUTABLE */
# else
#  define __STL_ACQUIRE_LOCK(_Lock)
#  define __STL_RELEASE_LOCK(_Lock)
# endif /* __STL_THREADS */

# include <stl_iterator_base.h>

// uninitialized value filler
# ifndef __STL_SHRED_BYTE
#  ifdef macintosh
 // This value is designed to cause problems on the Mac if an error occurs
#   define __STL_SHRED_BYTE 0xA3
#  else
#   define __STL_SHRED_BYTE 0xFF
#  endif
# endif

# define __STL_MSG_INVALID_ARGUMENT     "Invalid argument to operation (see operation documentation)"

# define __STL_MSG_INVALID_CONTAINER    "Taking an iterator out of destroyed (or otherwise corrupted) container"
# define __STL_MSG_EMPTY_CONTAINER      "Trying to extract an object out from empty container"
# define __STL_MSG_ERASE_PAST_THE_END   "Past-the-end iterator could not be erased"
# define __STL_MSG_OUT_OF_BOUNDS        "Index out of bounds"
# define __STL_MSG_NOT_OWNER            "Container doesn't own the iterator"
# define __STL_MSG_INVALID_ITERATOR     "Uninitialized or invalidated (by mutating operation)"\
       " iterator used"
# define __STL_MSG_INVALID_LEFTHAND_ITERATOR     "Uninitialized or invalidated (by mutating operation)"\
       " lefthand iterator in expression"
# define __STL_MSG_INVALID_RIGHTHAND_ITERATOR     "Uninitialized or invalidated (by mutating operation)"\
       " righthand iterator in expression"
# define __STL_MSG_DIFFERENT_OWNERS     "Iterators used in expression are from different owners"
# define __STL_MSG_NOT_DEREFERENCEABLE  "Iterator could not be dereferenced (past-the-end ?)"
# define __STL_MSG_INVALID_RANGE        "Range [first,last) is invalid"
# define __STL_MSG_NOT_IN_RANGE_1       "Iterator is not in range [first,last)"
# define __STL_MSG_NOT_IN_RANGE_2       "Range [first,last) is not in range [start,finish)"
# define __STL_MSG_INVALID_ADVANCE      "The advance would produce invalid iterator"
# define __STL_MSG_SINGULAR_ITERATOR    "Iterator is singular (advanced beyond the bounds ?)"

// debug alloc messages
# define __STL_MSG_DBA_DELETED_TWICE    "Memory block deallocated twice"
# define __STL_MSG_DBA_NEVER_ALLOCATED  "Deallocating a block that was never allocated"
# define __STL_MSG_DBA_TYPE_MISMATCH    "Deallocating a memory block allocated for another type"
# define __STL_MSG_DBA_SIZE_MISMATCH    "Size of block passed to deallocate() doesn't match block size"
# define __STL_MSG_DBA_UNDERRUN         "Pointer underrun - safety margin at front of memory block overwritten"
# define __STL_MSG_DBA_OVERRUN          "Pointer overrrun - safety margin at back of memory block overwritten"

#  define __stl_verbose_check(__expr,__diagnostic) ((__expr) ? true : \
(__stl_debug_message( __FILE__, __LINE__, __diagnostic ),false))

#  define __stl_verbose_return(__expr,__diagnostic) if (!(__expr)) { \
    __stl_debug_message( "\n%s:%d STL error: %s\n", __FILE__, __LINE__, __diagnostic ); return false; }

__STL_BEGIN_NAMESPACE

//============================================================================

inline bool __check_bounds(int __index, int __size) 
{
    __stl_verbose_return(__index<__size, __STL_MSG_OUT_OF_BOUNDS);
    return true;
}

//=============================================================
template <class __Iterator>
inline bool __valid_range(const __Iterator& __i1 ,const __Iterator& __i2, 
                          random_access_iterator_tag)
{ 
    return __i1<=__i2;
}

template <class __Iterator>
inline bool __valid_range(const __Iterator& __i1 ,const __Iterator& __i2, 
                          bidirectional_iterator_tag)
{ 
    // check if comparable
    bool __dummy(__i1==__i2);
    return (__dummy==__dummy); 
}

template <class __Iterator>
inline bool __valid_range(const __Iterator& __i1 ,const __Iterator& __i2, 
                          forward_iterator_tag)
{ 
    // check if comparable
    bool __dummy(__i1==__i2);
    return (__dummy==__dummy); 
}

template <class __Iterator>
inline bool __valid_range(const __Iterator&,const __Iterator&, 
                          input_iterator_tag)
{ 
    return false; 
}

template <class __Iterator>
inline bool __valid_range(const __Iterator&,const __Iterator&, 
                          output_iterator_tag)
{ 
    return false; 
}

template <class __Iterator>
inline bool __valid_range(const __Iterator& __i1, const __Iterator& __i2)
{ 
    return __valid_range(__i1,__i2,__ITERATOR_CATEGORY(__i1));
}

// Note : that means in range [i1, i2].
template <class __Iterator>
inline bool __in_range(const __Iterator& __it, const __Iterator& __i1,
		       const __Iterator& __i2)
{ 
    return __valid_range(__i1,__it,__ITERATOR_CATEGORY(__i1)) && 
        __valid_range(__it,__i2,__ITERATOR_CATEGORY(__it));
}

template <class __Iterator>
inline bool __in_range(const __Iterator& __first, const __Iterator& __last, 
                       const __Iterator& __start, const __Iterator& __finish)
{ 
    return __valid_range(__first,__last,__ITERATOR_CATEGORY(__first)) &&
        __valid_range(__start,__first,__ITERATOR_CATEGORY(__first)) && 
        __valid_range(__last,__finish,__ITERATOR_CATEGORY(__last));
}

//==========================================================

class __owned_link;
template <class _Dummy> class __owned_list_tmpl;

// this evil is because of some compilers
// are unable to recognize base class which is typedef
# define __owned_list __owned_list_tmpl<bool>


class __owned_link {
private:
    typedef __owned_link  _Self;
    typedef _Self* _Self_ptr;
    typedef __owned_list  _Owner_type;
    typedef __owned_list* _Owner_ptr;
public:
    inline __owned_link(const _Owner_type* __c);
    __owned_link() : _M_owner(0) {}

    const _Owner_type* _Owner() const { 
      return _M_owner; 
    }
    void _Set_owner(const _Owner_type* __o)  { 
      _M_owner= __o; 
    }
    bool  _Valid() const { 
      return _M_owner !=0; 
    }
    inline __owned_link(const _Self& __rhs);
    inline _Self& operator=(const _Self& __rhs);
    inline ~__owned_link();
    void _Invalidate() { _M_owner=0; }
    void _Link_to_self() { _M_next=_M_prev=this; }
    _Self* _Prev() { return _M_prev; }
    _Self* _Next() { return _M_next; }
    const _Self* _Prev() const { return _M_prev; }
    const _Self* _Next() const { return _M_next; }

 public:
    const _Owner_type* _M_owner;
    _Self_ptr          _M_next;
    _Self_ptr          _M_prev; 
    //    friend class       __owned_list_tmpl<bool>;
};

template <class _Dummy>
class __owned_list_tmpl {
private:
    typedef __owned_list_tmpl<_Dummy> _Self;
    typedef _Self* _Self_ptr;
    typedef __owned_link  _Node;
    typedef _Node* _Node_ptr;
    typedef void* _Owner_ptr;
    typedef const void* _Owner_const_ptr;
    // should never be called
    __owned_list_tmpl(const _Self&);
    _Self& operator=(const _Self&);
public:
    __owned_list_tmpl() {
    }
    ~__owned_list_tmpl() {
      _Invalidate_all();
      // that prevents detach
      _M_node._Invalidate();
    }
    _Owner_const_ptr _Owner() const { 
      return (_Owner_const_ptr)_M_node._M_owner; 
    }
    _Owner_ptr _Owner() { 
      return (_Owner_ptr)_M_node._M_owner; 
    }
    bool  _Valid() const { 
      return _M_node._M_owner!=0; 
    }
    void _Invalidate() { _M_node._M_owner=0; }
    void _Safe_init(const void* __c) { 
        _M_node._M_owner = (_Self_ptr)__c; 
        _M_node._Link_to_self();
    }
    void _Orphan(_Node& __it) {
      //      __stl_assert(&__it != &_M_node);
      if (__it._Owner()) {
	_M_detach(&__it);
      }
      __it._Link_to_self();
      __it._Set_owner(this);
    }

    _Node* _First() { return _M_node._Next(); }
    _Node* _Last() { return &_M_node; }
    const _Node* _First() const { return _M_node._Next(); }
    const _Node* _Last() const { return &_M_node; }

    void _Verify();
    void _Swap_owners(_Self&, bool =false);
    void _Invalidate_all();
    inline void _M_detach_nosync(const _Node*) const;
    void _M_detach(const _Node*) const;
    // code bloat reduction
    static bool _Check_same_owner( const __owned_link& __i1, 
				   const __owned_link& __i2);
    static bool _Check_same_owner_or_null( const __owned_link& __i1, 
					   const __owned_link& __i2);
    bool _Check_if_owner( const __owned_link& __it) const;

# ifdef __STL_THREADS
    mutable _STL_mutex_lock           _M_lock;
# endif
private:
    void _M_attach(const _Node*) const;
    //    _Owner_ptr                        _M_owner;
    mutable _Node                     _M_node; 
    friend class __owned_link;
};

//==========================================================

inline __owned_link::__owned_link(const __owned_list* __c): _M_owner(0) {
  if (__c) 
    __c->_M_attach(this);
}

inline __owned_link::__owned_link(const __owned_link& __rhs) {
  _M_owner = 0;
  if (__rhs._M_owner) 
    __rhs._M_owner->_M_attach(this);
}

inline __owned_link& __owned_link::operator=(const __owned_link& __rhs) {
  const _Owner_type* __new_owner = __rhs._Owner();
  const _Owner_type* __old_owner = _Owner();
  if ( __old_owner != __new_owner ) {
    if (__old_owner) __old_owner->_M_detach(this);
    if (__new_owner) 
      __new_owner->_M_attach(this);
    else
      _M_owner = 0;
  }
  return *this;
}

inline __owned_link::~__owned_link() {
  if (_Owner()) 
    _M_owner->_M_detach(this);
}

//==========================================================

template <class _Dummy>
void __owned_list_tmpl<_Dummy>::_Invalidate_all() {
  // crucial
  if (_Valid()) {
    for (_Node_ptr __position = _First(); 
	 __position!=_Last(); __position=__position->_Next()) {
      __position->_Invalidate();
    }
    _M_node._Link_to_self();
  }
}

template <class _Dummy>
void __owned_list_tmpl<_Dummy>::_Verify() {
  _Node* __position;
  for (__position = _First(); 
       __position!=_Last(); __position=__position->_Next()) {
    __stl_assert(__position->_Owner()== this);
  }
}

template <class _Dummy>
void 
__owned_list_tmpl<_Dummy>::_Swap_owners(__owned_list_tmpl<_Dummy>& __x, bool __swap_roots) {
  _Invalidate_all();
  __x._Invalidate_all();
  if (__swap_roots) {
    const _Self* __tmp = _M_node._M_owner;
    _M_node._M_owner=__x._M_node._M_owner;
    __x._M_node._M_owner=__tmp;
  }
}


//============================================================

template <class _Dummy>
void 
__owned_list_tmpl<_Dummy>::_M_attach(const __owned_link* __c_node) const {
  __stl_verbose_assert(_Owner()!=0, __STL_MSG_INVALID_CONTAINER);
  // lots of evil casts down there
  _Self* __that = (_Self*)this;
  __STL_ACQUIRE_LOCK(__that->_M_lock)
  _Node* __node =  ( _Node*)__c_node;
  //    __stl_verbose_assert(&_M_node!=__node, "Attempt to attach root node");
  __node->_M_next = &__that->_M_node;
  __node->_M_prev = __that->_M_node._M_prev;
  ((__that->_M_node)._M_prev)->_M_next=__node;
  (__that->_M_node)._M_prev=__node;
  __node->_Set_owner(this);
  __STL_RELEASE_LOCK(__that->_M_lock)
}

template <class _Dummy>
inline void 
__owned_list_tmpl<_Dummy>::_M_detach_nosync(const __owned_link* __c_node) const {
  // lots of evil casts down there
    _Node* __node =  ( _Node*)__c_node;
    _Node* __next_node = __node->_M_next;
    _Node* __prev_node = __node->_M_prev;
    __prev_node->_M_next = __next_node;
    __next_node->_M_prev = __prev_node;
    __node->_M_owner=0;
}

template <class _Dummy>
void 
__owned_list_tmpl<_Dummy>::_M_detach(const __owned_link* __c_node) const {
  __stl_verbose_assert(_Owner()!=0, __STL_MSG_INVALID_CONTAINER);
  __STL_ACQUIRE_LOCK(_M_lock)
  _M_detach_nosync(__c_node);
  __STL_RELEASE_LOCK(_M_lock)
}

//==========================================================

// forward declaratioins
template <class _Iterator>
bool __check_range(const _Iterator&, const _Iterator&);
template <class _Iterator>
bool __check_range(const _Iterator&, 
                   const _Iterator&, const _Iterator&);
template <class _Iterator>
bool __check_range(const _Iterator&, const _Iterator& , 
                   const _Iterator&, const _Iterator& );
// [ i1, i2)
template <class _Iterator>
inline bool __in_range_aux(const _Iterator& __it, const _Iterator& __first,
                           const _Iterator& __last, random_access_iterator_tag) {
    return ( __it >= __first && 
             __it < __last);
}

template <class _Iterator1, class _Iterator>
# if defined (__STL_MSVC) && (__STL_MSVC >= 1100)
inline bool __in_range_aux(_Iterator1 __it, const _Iterator& __first,
# else
inline bool __in_range_aux(const _Iterator1& __it, const _Iterator& __first,
# endif
                           const _Iterator& __last, forward_iterator_tag) {
    _Iterator1 __i(__first);
    for (;  __i != __last && __i != __it; ++__i);
    return (__i!=__last);
}

# if defined (__STL_NONTEMPL_BASE_MATCH_BUG) /* OBSOLETE by inheritance */
template <class _Iterator1, class _Iterator>
inline bool __in_range_aux(const _Iterator1& __it, const _Iterator& __first,
                           const _Iterator& __last, bidirectional_iterator_tag) {
    _Iterator1 __i(__first);
    for (;  __i != __last && __i != __it; ++__i);
    return (__i !=__last);
}
# endif

//============================================================

//=============================================================

template <class _Iterator>
bool __check_range(const _Iterator& __first, const _Iterator& __last) {
    __stl_verbose_return(__valid_range(__first,__last), __STL_MSG_INVALID_RANGE );
    return true;
}

template <class _Iterator>
bool __check_range(const _Iterator& __it, 
                   const _Iterator& __start, const _Iterator& __finish) {
    __stl_verbose_return(__in_range(__it,__start, __finish), 
                         __STL_MSG_NOT_IN_RANGE_1);
    return true;
}

template <class _Iterator>
bool __check_range(const _Iterator& __first, const _Iterator& __last, 
                   const _Iterator& __start, const _Iterator& __finish) {
    __stl_verbose_return(__in_range(__first, __last, __start, __finish), 
                         __STL_MSG_NOT_IN_RANGE_2);
    return true;
}
//===============================================================

template <class _Dummy, class _Iterator>
void __invalidate_range(const __owned_list_tmpl<_Dummy>* __base, 
                        const _Iterator& __first,
                        const _Iterator& __last)
{
    typedef _Iterator* _Safe_iterator_ptr;
    typedef __owned_link _L_type;
    __STL_ACQUIRE_LOCK(__base->_M_lock)
    _L_type* __pos;
    _Safe_iterator_ptr __position;
    for (__pos= (_L_type*)__base->_First(); 
         __pos!=__base->_Last();) {	    
        __position=(_Safe_iterator_ptr)__pos;
        if ((!(&__first == __position || &__last == __position))
            &&  __in_range_aux(__position->_Get_iterator(),
			       __first._Get_iterator(),
			       __last._Get_iterator(), __ITERATOR_CATEGORY(__first))) {
	  _L_type* __remove_position= __pos;
	  __pos=__pos->_Next();
	  __base->_M_detach_nosync(__remove_position);
	}
	else
	  __pos=__pos->_Next();
    }
    __STL_RELEASE_LOCK(__base->_M_lock)    
}

template <class _Dummy, class _Iterator, class _SafeIterator>
void __invalidate_iterator(const __owned_list_tmpl<_Dummy>* __base, 
                           const _Iterator& __it, const _SafeIterator& )
{
    typedef _SafeIterator* _Safe_iterator_ptr;
    typedef __owned_link   _L_type;
    _L_type*  __position;
    __STL_ACQUIRE_LOCK(__base->_M_lock)
    for (__position = (_L_type*)(__base->_First()); 
         __position!=(_L_type*)__base->_Last();) {
      // this requires safe iterators to be derived from __owned_link
       if (((_Safe_iterator_ptr)__position)->_Get_iterator()==__it) {
            _L_type* __remove_position= __position;
            __position=__position->_Next();
            __base->_M_detach_nosync(__remove_position);
        }
        else
            __position=__position->_Next();
    }
    __STL_RELEASE_LOCK(__base->_M_lock)
}


template <class _Dummy>
bool __owned_list_tmpl<_Dummy>::_Check_same_owner( const __owned_link& __i1, 
							 const __owned_link& __i2)
{
    __stl_verbose_return(__i1._Valid(), __STL_MSG_INVALID_LEFTHAND_ITERATOR);
    __stl_verbose_return(__i2._Valid(), __STL_MSG_INVALID_RIGHTHAND_ITERATOR);
    __stl_verbose_return(__i1._Owner()==__i2._Owner(), __STL_MSG_DIFFERENT_OWNERS);
    return true;
}

template <class _Dummy>
bool __owned_list_tmpl<_Dummy>::_Check_same_owner_or_null( const __owned_link& __i1, 
							   const __owned_link& __i2)
{
    __stl_verbose_return(__i1._Owner()==__i2._Owner(), __STL_MSG_DIFFERENT_OWNERS);
    return true;
}

inline bool 
__check_same_owner( const __owned_link& __i1, const __owned_link& __i2) {
  return __owned_list::_Check_same_owner(__i1,__i2);
}
inline bool 
__check_same_owner_or_null( const __owned_link& __i1, const __owned_link& __i2) {
  return __owned_list::_Check_same_owner_or_null(__i1,__i2);
}

template <class _Dummy>
bool __owned_list_tmpl<_Dummy>::_Check_if_owner( const __owned_link& __it) const 
{
    const __owned_list_tmpl<_Dummy>* __owner_ptr = __it._Owner();
    __stl_verbose_return(__owner_ptr!=0, __STL_MSG_INVALID_ITERATOR);
    __stl_verbose_return(this==__owner_ptr, __STL_MSG_NOT_OWNER);
    return true;
}

template <class _Dummy, class Iterator>
inline bool __check_if_owner( const __owned_list_tmpl<_Dummy>* __owner, 
		       const Iterator& __it) {
  return __owner->_Check_if_owner((const __owned_link&)__it);
}

//============================================================

__STL_END_NAMESPACE

# endif /* __STL_DEBUG */

#endif /* DEBUG_H */

