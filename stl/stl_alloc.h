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

#ifndef __SGI_STL_INTERNAL_ALLOC_H
#define __SGI_STL_INTERNAL_ALLOC_H


// This implements some standard node allocators.  These are
// NOT the same as the allocators in the C++ draft standard or in
// in the original STL.  They do not encapsulate different pointer
// types; indeed we assume that there is only one pointer type.
// The allocation primitives are intended to allocate individual objects,
// not larger arenas as with the original STL allocators.

#ifndef __ALLOC
#   define __ALLOC alloc
#endif

# ifndef __RESTRICT
#  define __RESTRICT
# endif

#if defined (__STL_USE_NEW_STYLE_HEADERS)
# include <cstddef>
# include <cstdlib>
# include <cstring>
# include <cassert>
# include <new>
#else
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <new.h>
#endif

# ifndef __SGI_STL_CONFIG_H
#  include <stl_config.h>
# endif

# if defined (__STL_DEBUG) && ! defined ( __SGI_STL_DEBUG_H )
#  include <stldebug.h>
# endif

# ifndef __THROW_BAD_ALLOC
#  if !defined(__STL_USE_NEW_STYLE_HEADERS) || !defined(__STL_USE_EXCEPTIONS)
#   if defined (__STL_USE_NEW_STYLE_HEADERS)
#    include <cstdio>
#   else
#    include <stdio.h>
#   endif
#   define __THROW_BAD_ALLOC fprintf(stderr, "out of memory\n"); exit(1)
#  else /* (__STL_USE_NEW_STYLE_HEADERS) || !defined(__STL_USE_EXCEPTIONS) */
#   define __THROW_BAD_ALLOC throw bad_alloc()
// this should go to <new>
#   ifndef __STL_NO_BAD_ALLOC
#    ifdef __STL_USE_OWN_NAMESPACE
      __STL_BEGIN_NAMESPACE
      using __STL_VENDOR_STD::bad_alloc;
      __STL_END_NAMESPACE
#    endif /* __STL_OWN_NAMESPACE */
#   else /* __STL_NO_BAD_ALLOC */
#    include <stl_exception.h>
     __STL_BEGIN_NAMESPACE
     class bad_alloc : public __STL_EXCEPTION_BASE { 
      public:
	bad_alloc () __STL_THROWS() { }
	bad_alloc(const bad_alloc&) __STL_THROWS() { }
	bad_alloc& operator=(const bad_alloc&) __STL_THROWS() {return *this;}
	~bad_alloc () __STL_THROWS() { }
	const char* what() const __STL_THROWS();
     };
     __STL_END_NAMESPACE
#   endif /* __STL_NO_BAD_ALLOC */
#  endif /* (__STL_USE_NEW_STYLE_HEADERS) || !defined(__STL_USE_EXCEPTIONS) */
# endif   /* __THROW_BAD_ALLOC */

# if defined ( __STL_USE_ABBREVS )
// ugliness is intentional - to reduce conflicts probability
#  define __malloc_alloc   M__A
#  define __default_alloc_template  D__A
#  define __new_alloc      N__A		//*TY 08/01/1998 - added to make the generated name short
#  define debug_alloc      G__A		//*TY 08/01/1998 - added to make the generated name short
# endif

#ifdef __STL_THREADS
# include <stl_threads.h>
# define __NODE_ALLOCATOR_THREADS true
# ifdef __STL_SGI_THREADS
  // We test whether threads are in use before locking.
  // Perhaps this should be moved into stl_threads.h, but that
  // probably makes it harder to avoid the procedure call when
  // it isn't needed.
    extern "C" {
      extern int __us_rsthread_malloc;
    }
	// The above is copied from malloc.h.  Including <malloc.h>
	// would be cleaner but fails with certain levels of standard
	// conformance.
#   define __NODE_ALLOCATOR_LOCK if (__threads && __us_rsthread_malloc) \
                { _S_node_allocator_lock._M_acquire_lock(); }
#   define __NODE_ALLOCATOR_UNLOCK if (__threads && __us_rsthread_malloc) \
                { _S_node_allocator_lock._M_release_lock(); }
# else /* !__STL_SGI_THREADS */
#   define __NODE_ALLOCATOR_LOCK \
        { if (__threads) _S_node_allocator_lock._M_acquire_lock(); }
#   define __NODE_ALLOCATOR_UNLOCK \
        { if (__threads) _S_node_allocator_lock._M_release_lock(); }
# endif
#else
//  Thread-unsafe
#   define __NODE_ALLOCATOR_LOCK
#   define __NODE_ALLOCATOR_UNLOCK
#   define __NODE_ALLOCATOR_THREADS false
#endif

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

// Specialised debug form of malloc which does not provide "false"
// memory leaks when run with debug CRT libraries.
#if defined(__STL_MSVC) && __STL_MSVC>=1020 && defined(_DEBUG)
#  include <crtdbg.h>
#  define   __STL_CHUNK_MALLOC(s)         _malloc_dbg(s, _CRT_BLOCK, __FILE__, __LINE__)
#else	// !_DEBUG
#  define   __STL_CHUNK_MALLOC(s)         malloc(s)
#endif	// !_DEBUG

__STL_BEGIN_NAMESPACE

// Malloc-based allocator.  Typically slower than default alloc below.
// Typically thread-safe and more storage efficient.

typedef void (* __oom_handler_type)();

template <int __inst>
class __malloc_alloc {
private:

  static void* _S_oom_malloc(size_t);
  static void* _S_oom_realloc(void*, size_t);

  static __oom_handler_type __oom_handler;

public:
  // this one is needed for proper simple_alloc wrapping
  typedef char value_type;

  static void* allocate(size_t __n)
    {
      void* __result = malloc(__n);
      if (0 == __result) __result = _S_oom_malloc(__n);
      return __result;
    }

  static void deallocate(void* __p, size_t /* __n */)
    {
      free((char*)__p);
    }

  static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz)
    {
      void* __result = realloc((char*)__p, __new_sz);
      if (0 == __result) __result = _S_oom_realloc(__p, __new_sz);
      return __result;
    }

  static __oom_handler_type set_malloc_handler(__oom_handler_type __f)
    {
      __oom_handler_type __old = __oom_handler;
      __oom_handler = __f;
      return(__old);
    }
    
};

typedef __malloc_alloc<0> malloc_alloc;

// malloc_alloc out-of-memory handling
# if ( __STL_STATIC_TEMPLATE_DATA > 0 )
template <int __inst>
__oom_handler_type __malloc_alloc<__inst>::__oom_handler=(__oom_handler_type)0 ;
#  else
__DECLARE_INSTANCE(__oom_handler_type, __malloc_alloc<0>::__oom_handler, =0);
# endif /* ( __STL_STATIC_TEMPLATE_DATA > 0 ) */

template <int __inst>
void * __malloc_alloc<__inst>::_S_oom_malloc(size_t __n)
{
  __oom_handler_type __my_malloc_handler;
  void * __result;

  for (;;) {
    __my_malloc_handler = __oom_handler;
    if (0 == __my_malloc_handler) { __THROW_BAD_ALLOC; }
    (*__my_malloc_handler)();
    __result = malloc(__n);
    if (__result) return(__result);
  }
}

template <int __inst>
void* __malloc_alloc<__inst>::_S_oom_realloc(void* __p, size_t __n)
{
  __oom_handler_type __my_malloc_handler;
  void* __result;

  for (;;) {
    __my_malloc_handler = __oom_handler;
    if (0 == __my_malloc_handler) { __THROW_BAD_ALLOC; }
    (*__my_malloc_handler)();
    __result = realloc(__p, __n);
    if (__result) return(__result);
  }
}



template<class _Tp, class _Alloc>
class simple_alloc {
  typedef _Alloc __alloc_type;
public:
  typedef typename _Alloc::value_type __alloc_value_type;
  typedef _Tp value_type;
  static size_t __chunk(size_t __n) { 
    return (__n+sizeof(__alloc_value_type)-1)/sizeof(__alloc_value_type);
  }
  static _Tp* allocate(size_t __n)
    { return 0 == __n ? (_Tp*)0 : (_Tp*) __alloc_type::allocate(__chunk(__n*sizeof(_Tp))); }
  static _Tp* allocate(void)
    { return (_Tp*) __alloc_type::allocate(__chunk(sizeof(_Tp))); }
  static void deallocate(_Tp * __p, size_t __n)
    { if (0 != __n) __alloc_type::deallocate((__alloc_value_type*)__p,
					     __chunk(__n* sizeof(_Tp))); }
  static void deallocate(_Tp * __p)
    { __alloc_value_type* __v = (__alloc_value_type*)__p;
      __alloc_type::deallocate(__v, __chunk(sizeof(_Tp)));
    }
};

// New-based allocator.  Typically slower than default alloc below.
// Typically thread-safe and more storage efficient.
template <int __inst>
class __new_alloc {
public:
  // this one is needed for proper simple_alloc wrapping
  typedef char value_type;
  static void*  allocate(size_t __n) { return 0 == __n ? 0 : ::operator __STL_NEW(__n
#if (( defined(__IBMCPP__)|| defined(__OS400__) || defined (qTidyHeap)) && \
                             defined(__DEBUG_ALLOC__) ) // Added
 , __FILE__, __LINE__                                   // Added
#endif                                                  // Added
									    );}
  static void*  reallocate(void *__p, size_t __old_sz, size_t __new_sz) {
    void* __result = allocate(__new_sz);
    size_t __copy_sz = __new_sz > __old_sz? __old_sz : __new_sz;
    memcpy(__result, __p, __copy_sz);
    deallocate(__p, __old_sz);
    return __result;
  }
  static void deallocate(void* __p) { ::operator delete(__p
#if (( defined(__IBMCPP__) || defined(__OS400__))  && defined(__DEBUG_ALLOC__) ) // Added
							, __FILE__, __LINE__
#endif                                                  // Added
							); }
  static void deallocate(void* __p, size_t) { ::operator delete(__p
#if (( defined(__IBMCPP__) || defined(__OS400__))&& defined(__DEBUG_ALLOC__) )
								, __FILE__, __LINE__
#endif                                                 
								); }
};

typedef __new_alloc<0> new_alloc;

// Allocator adaptor to check size arguments for debugging.
// Reports errors using assert.  Checking can be disabled with
// NDEBUG, but it's far better to just use the underlying allocator
// instead when no checking is desired.
// There is some evidence that this can confuse Purify.
template <class _Alloc>
class debug_alloc {
public:
  typedef _Alloc __allocator_type;
  typedef typename _Alloc::value_type value_type;
private:
  struct __alloc_header {
    size_t __magic: 16;
    size_t __type_size:16;
    __STL_UINT32_T __size;
  }; // that is 8 bytes for sure
  // Sunpro CC has bug on enums, so extra_before/after set explicitly
  enum { __pad=8, __magic=0xdeba, __deleted_magic = 0xdebd,
	 __shred_byte=
#  ifdef __STL_SHRED_BYTE
	 __STL_SHRED_BYTE   
# else
	 0xFF 
# endif  
  };
  static int __extra_before() { return 16; }
  static int __extra_after()  { return 8; }
  // Size of space used to store size.  Note
  // that this must be large enough to preserve
  // alignment.
  static size_t __extra_before_chunk() {
    return __extra_before()/sizeof(value_type)+
      (size_t)(__extra_before()%sizeof(value_type)>0);
  }
  static size_t __extra_after_chunk() {
    return __extra_before()/sizeof(value_type)+
      (size_t)(__extra_after()%sizeof(value_type)>0);
  }
public:
  static void * allocate(size_t);
  static void deallocate(void *, size_t);
  static void deallocate(void *__p) { deallocate(__p, sizeof(value_type)); }
  static void * allocate() { return allocate(sizeof(value_type));}

  static void * reallocate(void *, size_t, size_t); 
};

template <class _Alloc>
void * debug_alloc<_Alloc>::allocate(size_t __n) {
  size_t __real_n = __n + __extra_before_chunk() + __extra_after_chunk();
  __alloc_header *__result = (__alloc_header *)__allocator_type::allocate(__real_n);
  memset((char*)__result, __shred_byte, __real_n*sizeof(value_type));
  __result->__magic = __magic;
  __result->__type_size = sizeof(value_type);
  __result->__size = __n;
  return ((char*)__result) + __extra_before();
}

template <class _Alloc>
void debug_alloc<_Alloc>::deallocate(void *__p, size_t __n) {
  __alloc_header * __real_p = (__alloc_header*)((char *)__p -__extra_before());
  // check integrity
  __stl_verbose_assert(__real_p->__magic != __deleted_magic, __STL_MSG_DBA_DELETED_TWICE);
  __stl_verbose_assert(__real_p->__magic == __magic, __STL_MSG_DBA_NEVER_ALLOCATED);
  __stl_verbose_assert(__real_p->__type_size == sizeof(value_type), 
		       __STL_MSG_DBA_TYPE_MISMATCH);
  __stl_verbose_assert(__real_p->__size == __n, __STL_MSG_DBA_SIZE_MISMATCH);
  // check pads on both sides
  unsigned char* __tmp;
  for (__tmp= (unsigned char*)(__real_p+1); __tmp < (unsigned char*)__p; __tmp++)
    __stl_verbose_assert(*__tmp==__shred_byte, __STL_MSG_DBA_UNDERRUN);
  size_t __real_n= __n + __extra_before_chunk() + __extra_after_chunk();
  for (__tmp= ((unsigned char*)__p)+__n*sizeof(value_type); 
       __tmp < ((unsigned char*)__real_p)+__real_n ; __tmp++)
    __stl_verbose_assert(*__tmp==__shred_byte, __STL_MSG_DBA_OVERRUN);
  // that may be unfortunate, just in case
  __real_p->__magic=__deleted_magic;
  memset((char*)__p, __shred_byte, __n*sizeof(value_type));
  __allocator_type::deallocate(__real_p, __real_n);
}

template <class _Alloc>
void * 
debug_alloc<_Alloc>::reallocate(void *__p, size_t __old_sz, size_t __new_sz) {
  __alloc_header * __real_p = (__alloc_header*)((char *)__p - __extra_before());
  size_t __extra = __extra_before_chunk() + __extra_after_chunk();
  __stl_verbose_assert(__real_p->__magic != __deleted_magic, __STL_MSG_DBA_DELETED_TWICE);
  __stl_verbose_assert(__real_p->__magic == __magic, __STL_MSG_DBA_NEVER_ALLOCATED);
  __stl_verbose_assert(__real_p->__type_size == sizeof(value_type), 
		       __STL_MSG_DBA_TYPE_MISMATCH);
  __stl_verbose_assert(__real_p->__size == __old_sz, __STL_MSG_DBA_SIZE_MISMATCH);
  __real_p = (__alloc_header*)__allocator_type::reallocate(__real_p, __old_sz + __extra, 
							 __new_sz + __extra);
  __real_p->__size = __new_sz;
  return ((char*)__real_p) + __extra_before();
}


# if defined ( __STL_USE_NEWALLOC )
#  if defined ( __STL_DEBUG_ALLOC )
typedef debug_alloc<new_alloc> alloc;
#  else
typedef new_alloc alloc;
#  endif /* __STL_DEBUG_ALLOC */
typedef new_alloc single_client_alloc;
typedef new_alloc multithreaded_alloc;
#  else /* __STL_USE_NEWALLOC */
#  ifdef __STL_USE_MALLOC
#   if defined ( __STL_DEBUG_ALLOC )
typedef debug_alloc<malloc_alloc> alloc;
#   else
typedef malloc_alloc alloc;
#   endif /* __STL_DEBUG_ALLOC */
typedef malloc_alloc single_client_alloc;
typedef malloc_alloc multithreaded_alloc;
#  endif /* __STL_USE_MALLOC */
#  endif /* __STL_USE_NEWALLOC */

// __STL_END_NAMESPACE


# if ! defined (__STL_USE_MALLOC) && ! defined ( __STL_USE_NEWALLOC )

// __STL_BEGIN_NAMESPACE


// Default node allocator.
// With a reasonable compiler, this should be roughly as fast as the
// original STL class-specific allocators, but with less fragmentation.
// Default_alloc_template parameters are experimental and MAY
// DISAPPEAR in the future.  Clients should just use alloc for now.
//
// Important implementation properties:
// 1. If the client request an object of size > _MAX_BYTES, the resulting
//    object will be obtained directly from malloc.
// 2. In all other cases, we allocate an object of size exactly
//    _S_round_up(requested_size).  Thus the client has enough size
//    information that we can return the object to the proper free list
//    without permanently losing part of the object.
//

// The first template parameter specifies whether more than one thread
// may use this allocator.  It is safe to allocate an object from
// one instance of a default_alloc and deallocate it with another
// one.  This effectively transfers its ownership to the second one.
// This may have undesirable effects on reference locality.
// The second parameter is unreferenced and serves only to allow the
// creation of multiple default_alloc instances.
// Node that containers built on different allocator instances have
// different types, limiting the utility of this approach.

// #if defined ( __STL_STATIC_ARRAY_BUG )
// breaks if we make these template class members:
# if defined(__OS400__)
enum {_ALIGN = 16};
enum {_MAX_BYTES = 256};
#  define  _NFREELISTS 16
# else
enum {_ALIGN = 8};
enum {_MAX_BYTES = 128};
// SunPro CC 4.0.1 has bug on enums
//  enum {_NFREELISTS = _MAX_BYTES/_ALIGN};
#  define  _NFREELISTS 16
# endif /* __OS400__ */
//#endif 

union _Node_alloc_obj;

union _Node_alloc_obj {
  union _Node_alloc_obj * _M_free_list_link;
  char __M_client_data[1];    /* The client sees this.        */
};

template <bool __threads, int __inst>
class __default_alloc_template {
  //  __PRIVATE:
  // Really we should use static const int x = N
  // instead of enum { x = N }, but few compilers accept the former.
  //#if ! defined ( __STL_STATIC_ARRAY_BUG )
  //  enum {_ALIGN = 8};
  //  enum {_MAX_BYTES = 128};
  //  enum {_NFREELISTS = _MAX_BYTES/_ALIGN};
  //# endif
  __PRIVATE:
  static size_t
  _S_round_up(size_t __bytes) 
    { return (((__bytes) + _ALIGN-1) & ~(_ALIGN - 1)); }

  typedef _Node_alloc_obj _Obj;
private:
  static _Obj * __STL_VOLATILE _S_free_list[_NFREELISTS]; 
  static  size_t _S_freelist_index(size_t __bytes) {
    return ((__bytes + _ALIGN-1)/_ALIGN - 1);
  }

  // Returns an object of size __n, and optionally adds to size __n free list.
  static void* _S_refill(size_t __n);
  // Allocates a chunk for nobjs of size size.  nobjs may be reduced
  // if it is inconvenient to allocate the requested number.
  static char* _S_chunk_alloc(size_t __size, int& __nobjs);

  // Chunk allocation state.
  static char* _S_start_free;
  static char* _S_end_free;
  static size_t _S_heap_size;

# ifdef __STL_THREADS
    static _STL_mutex_base _S_node_allocator_lock;
# endif

  // It would be nice to use _STL_auto_lock here.  But we
  // don't need the NULL check.  And we do need a test whether
  // threads have actually been started.
  class _Lock;
  friend class _Lock;

  class _Lock {
  public:
    _Lock() { __NODE_ALLOCATOR_LOCK; }
    ~_Lock() { __NODE_ALLOCATOR_UNLOCK; }
  };

public:
  // this one is needed for proper simple_alloc wrapping
  typedef char value_type;

  /* __n must be > 0      */
  inline
  static void * allocate(size_t __n);
  /* __p may not be 0 */
  inline
  static void deallocate(void *__p, size_t __n);
  static void * reallocate(void *__p, size_t __old_sz, size_t __new_sz);

} ;

typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> _Node_alloc;
#   if defined ( __STL_DEBUG_ALLOC )
typedef debug_alloc<_Node_alloc> alloc;
#   else
typedef _Node_alloc alloc;
#   endif

typedef __default_alloc_template<false, 0> single_client_alloc;
typedef __default_alloc_template<true, 0>  multithreaded_alloc;

template <bool __threads, int __inst>
/* n must be > 0      */
inline 
void * 
__default_alloc_template<__threads,__inst>::allocate(size_t __n)
{
  _Obj * __STL_VOLATILE * __my_free_list;
  _Obj * __RESTRICT __result;

  if (__n > (size_t)_MAX_BYTES) {
    return(malloc_alloc::allocate(__n));
  }
  __my_free_list = _S_free_list + _S_freelist_index(__n);
  // Acquire the lock here with a constructor call.
  // This ensures that it is released in exit or during stack
  // unwinding.
#       ifndef _NOTHREADS
  /*REFERENCED*/
  _Lock __lock_instance;
#       endif
  __result = *__my_free_list;
  if (__result == 0) {
    void* __r = _S_refill(_S_round_up(__n));
    return __r;
  }
  *__my_free_list = __result -> _M_free_list_link;
  return (__result);
}

template <bool __threads, int __inst>
inline 
void 
__default_alloc_template<__threads, __inst>::deallocate(void *__p, size_t __n)
{
  _Obj *__q = (_Obj *)__p;
  _Obj * __STL_VOLATILE * __my_free_list;

  if (__n > (size_t) _MAX_BYTES) {
    malloc_alloc::deallocate(__p, __n);
    return;
  }
  __my_free_list = _S_free_list + _S_freelist_index(__n);
  // acquire lock
#       ifndef _NOTHREADS
  /*REFERENCED*/
  _Lock __lock_instance;
#       endif /* _NOTHREADS */
  __q -> _M_free_list_link = *__my_free_list;
  *__my_free_list = __q;
  // lock is released here
}

/* We allocate memory in large chunks in order to avoid fragmenting     */
/* the malloc heap too much.                                            */
/* We assume that size is properly aligned.                             */
/* We hold the allocation lock.                                         */
template <bool __threads, int __inst>
char*
__default_alloc_template<__threads, __inst>::_S_chunk_alloc(size_t __size, 
                                                            int& __nobjs)
{
  char* __result;
  size_t __total_bytes = __size * __nobjs;
  size_t __bytes_left = _S_end_free - _S_start_free;

  if (__bytes_left >= __total_bytes) {
    __result = _S_start_free;
    _S_start_free += __total_bytes;
    return(__result);
  } else if (__bytes_left >= __size) {
    __nobjs = (int)(__bytes_left/__size);
    __total_bytes = __size * __nobjs;
    __result = _S_start_free;
    _S_start_free += __total_bytes;
    return(__result);
  } else {
    size_t __bytes_to_get = 
      2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
    // Try to make use of the left-over piece.
    if (__bytes_left > 0) {
      _Obj* __STL_VOLATILE* __my_free_list =
	_S_free_list + _S_freelist_index(__bytes_left);

      ((_Obj*)_S_start_free) -> _M_free_list_link = *__my_free_list;
      *__my_free_list = (_Obj*)_S_start_free;
    }
    _S_start_free = (char*)__STL_CHUNK_MALLOC(__bytes_to_get);
    if (0 == _S_start_free) {
      size_t __i;
      _Obj* __STL_VOLATILE* __my_free_list;
      _Obj* __p;
      // Try to make do with what we have.  That can't
      // hurt.  We do not try smaller requests, since that tends
      // to result in disaster on multi-process machines.
      for (__i = __size; __i <= _MAX_BYTES; __i += _ALIGN) {
	__my_free_list = _S_free_list + _S_freelist_index(__i);
	__p = *__my_free_list;
	if (0 != __p) {
	  *__my_free_list = __p -> _M_free_list_link;
	  _S_start_free = (char*)__p;
	  _S_end_free = _S_start_free + __i;
	  return(_S_chunk_alloc(__size, __nobjs));
	  // Any leftover piece will eventually make it to the
	  // right free list.
	}
      }
      _S_end_free = 0;	// In case of exception.
      _S_start_free = (char*)malloc_alloc::allocate(__bytes_to_get);
      // This should either throw an
      // exception or remedy the situation.  Thus we assume it
      // succeeded.
    }
    _S_heap_size += __bytes_to_get;
    _S_end_free = _S_start_free + __bytes_to_get;
    return(_S_chunk_alloc(__size, __nobjs));
  }
}


/* Returns an object of size __n, and optionally adds to size __n free list.*/
/* We assume that __n is properly aligned.                                */
/* We hold the allocation lock.                                         */
template <bool __threads, int __inst>
void*
__default_alloc_template<__threads, __inst>::_S_refill(size_t __n)
{
  int __nobjs = 20;
  char* __chunk = _S_chunk_alloc(__n, __nobjs);
  _Obj* __STL_VOLATILE* __my_free_list;
  _Obj* __result;
  _Obj* __current_obj;
  _Obj* __next_obj;
  int __i;

  if (1 == __nobjs) return(__chunk);
  __my_free_list = _S_free_list + _S_freelist_index(__n);

  /* Build free list in chunk */
  __result = (_Obj*)__chunk;
  *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
  for (__i = 1; ; __i++) {
    __current_obj = __next_obj;
    __next_obj = (_Obj*)((char*)__next_obj + __n);
    if (__nobjs - 1 == __i) {
      __current_obj -> _M_free_list_link = 0;
      break;
    } else {
      __current_obj -> _M_free_list_link = __next_obj;
    }
  }
  return(__result);
}

template <bool threads, int inst>
void*
__default_alloc_template<threads, inst>::reallocate(void* __p,
                                                    size_t __old_sz,
                                                    size_t __new_sz)
{
  void* __result;
  size_t __copy_sz;

  if (__old_sz > (size_t) _MAX_BYTES && __new_sz > (size_t) _MAX_BYTES) {
    return(realloc(__p, __new_sz));
  }
  if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) return(__p);
  __result = allocate(__new_sz);
  __copy_sz = __new_sz > __old_sz? __old_sz : __new_sz;
  memcpy(__result, __p, __copy_sz);
  deallocate(__p, __old_sz);
  return(__result);
}

# if ( __STL_STATIC_TEMPLATE_DATA > 0 )

#ifdef __STL_THREADS
    template <bool __threads, int __inst>
    _STL_mutex_base
    __default_alloc_template<__threads, __inst>::_S_node_allocator_lock __STL_MUTEX_INITIALIZER;
#endif

template <bool __threads, int __inst>
char *__default_alloc_template<__threads, __inst>::_S_start_free = 0;

template <bool __threads, int __inst>
char *__default_alloc_template<__threads, __inst>::_S_end_free = 0;

template <bool __threads, int __inst>
size_t __default_alloc_template<__threads, __inst>::_S_heap_size = 0;

template <bool __threads, int __inst>
_Node_alloc_obj * __STL_VOLATILE
__default_alloc_template<__threads, __inst>::_S_free_list[_NFREELISTS]
 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// The 16 zeros are necessary to make version 4.1 of the SunPro
// compiler happy.  Otherwise it appears to allocate too little
// space for the array.

# else /* ( __STL_STATIC_TEMPLATE_DATA > 0 ) */
__DECLARE_INSTANCE(char *, single_client_alloc::_S_start_free,=0);
__DECLARE_INSTANCE(char *, single_client_alloc::_S_end_free,=0);
__DECLARE_INSTANCE(size_t, single_client_alloc::_S_heap_size,=0);
__DECLARE_INSTANCE(_Node_alloc_obj * __STL_VOLATILE,
                   single_client_alloc::_S_free_list[_NFREELISTS],
                   ={0});
__DECLARE_INSTANCE(char *, multithreaded_alloc::_S_start_free,=0);
__DECLARE_INSTANCE(char *, multithreaded_alloc::_S_end_free,=0);
__DECLARE_INSTANCE(size_t, multithreaded_alloc::_S_heap_size,=0);
__DECLARE_INSTANCE(_Node_alloc_obj * __STL_VOLATILE,
                   multithreaded_alloc::_S_free_list[_NFREELISTS],
                   ={0});
#   ifdef __STL_THREADS
__DECLARE_INSTANCE(_STL_mutex_base,
                   single_client_alloc::_S_node_allocator_lock,
                   __STL_MUTEX_INITIALIZER);
__DECLARE_INSTANCE(_STL_mutex_base,
                   multithreaded_alloc::_S_node_allocator_lock,
                   __STL_MUTEX_INITIALIZER);
#   endif
#  endif /* __STL_STATIC_TEMPLATE_DATA */

# endif /* ! __USE_MALLOC && ! __USE_NEWALLOC */

// This implements allocators as specified in the C++ standard.  
//
// Note that standard-conforming allocators use many language features
// that are not yet widely implemented.  In particular, they rely on
// member templates, partial specialization, partial ordering of function
// templates, the typename keyword, and the use of the template keyword
// to refer to a template member of a dependent type.

template <class _Tp>
class allocator {
  typedef alloc _Alloc;          // The underlying allocator.
  typedef allocator<_Tp> _Self;
public:
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

# if defined (__STL_MEMBER_TEMPLATE_CLASSES)
  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };
# endif

  allocator() __STL_NOTHROW {}
# if defined (__STL_MEMBER_TEMPLATES)
  template <class _Tp1> allocator(const allocator<_Tp1>&) __STL_NOTHROW {}
# else
  allocator(const _Self&) __STL_NOTHROW {}
# endif
  ~allocator() __STL_NOTHROW {}

  static pointer address(reference __x) { return &__x; }
  static const_pointer address(const_reference __x) { return &__x; }

  // __n is permitted to be 0.  The C++ standard says nothing about what
  // the return value is when __n == 0.
  static _Tp* allocate(size_type __n, const void* = 0) {
    return __n != 0 ? __STATIC_CAST(_Tp*,_Alloc::allocate(__n * sizeof(_Tp))) 
                    : 0;
  }

  // __p is not permitted to be a null pointer.
  static void deallocate(pointer __p, size_type __n)
    { _Alloc::deallocate(__p, __n * sizeof(_Tp)); }
  // backwards compatibility
  static void deallocate(pointer __p)
    { _Alloc::deallocate(__p, sizeof(_Tp)); }

  static size_type max_size() __STL_NOTHROW 
    { return size_t(-1) / sizeof(_Tp); }

  static void construct(pointer __p, const _Tp& __val) { __STL_PLACEMENT_NEW(__p) _Tp(__val); }
  static void destroy(pointer __p) { __p->~_Tp(); }
};

__STL_FULL_SPECIALIZATION
class allocator<void> {
public:
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef void*       pointer;
  typedef const void* const_pointer;
# if defined (__STL_CLASS_PARTIAL_SPECIALIZATION)
  typedef void        value_type;
# endif
# if defined (__STL_MEMBER_TEMPLATE_CLASSES)
  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };
# endif
};


template <class _T1, class _T2>
inline bool operator==(const allocator<_T1>&, const allocator<_T2>&) 
{
  return true;
}

template <class _T1, class _T2>
inline bool operator!=(const allocator<_T1>&, const allocator<_T2>&)
{
  return false;
}

#ifdef __STL_USE_STD_ALLOCATORS

// Allocator adaptor to turn an SGI-style allocator (e.g. alloc, malloc_alloc)
// into a standard-conforming allocator.   Note that this adaptor does
// *not* assume that all objects of the underlying alloc class are
// identical, nor does it assume that all of the underlying alloc's
// member functions are static member functions.  Note, also, that 
// __allocator<_Tp, alloc> is essentially the same thing as allocator<_Tp>.

template <class _Tp, class _Alloc>
struct __allocator {
  _Alloc __underlying_alloc;

  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

# if defined (__STL_MEMBER_TEMPLATE_CLASSES)
  template <class _Tp1> struct rebind {
    typedef __allocator<_Tp1, _Alloc> other;
  };
# endif
  __allocator() __STL_NOTHROW {}
  __allocator(const __allocator& __a) __STL_NOTHROW
    : __underlying_alloc(__a.__underlying_alloc) {}
  template <class _Tp1> 
  __allocator(const __allocator<_Tp1, _Alloc>& __a) __STL_NOTHROW
    : __underlying_alloc(__a.__underlying_alloc) {}
  ~__allocator() __STL_NOTHROW {}

  pointer address(reference __x) const { return &__x; }
  const_pointer address(const_reference __x) const { return &__x; }

  // __n is permitted to be 0.
  _Tp* allocate(size_type __n, const void* = 0) {
    return __n != 0 
        ? __STATIC_CAST(_Tp*,__underlying_alloc.allocate(__n * sizeof(_Tp))) 
        : 0;
  }

  // __p is not permitted to be a null pointer.
  void deallocate(pointer __p, size_type __n)
    { __underlying_alloc.deallocate(__p, __n * sizeof(_Tp)); }

  size_type max_size() const __STL_NOTHROW 
    { return size_t(-1) / sizeof(_Tp); }

  void construct(pointer __p, const _Tp& __val) { __STL_NEW(__p) _Tp(__val); }
  void destroy(pointer __p) { __p->~_Tp(); }
};

template <class _Alloc>
class __allocator<void, _Alloc> {
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef void*       pointer;
  typedef const void* const_pointer;
  typedef void        value_type;

  template <class _Tp1> struct rebind {
    typedef __allocator<_Tp1, _Alloc> other;
  };
};

template <class _Tp, class _Alloc>
inline bool operator==(const __allocator<_Tp, _Alloc>& __a1,
                       const __allocator<_Tp, _Alloc>& __a2)
{
  return __a1.__underlying_alloc == __a2.__underlying_alloc;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class _Tp, class _Alloc>
inline bool operator!=(const __allocator<_Tp, _Alloc>& __a1,
                       const __allocator<_Tp, _Alloc>& __a2)
{
  return __a1.__underlying_alloc != __a2.__underlying_alloc;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

// Comparison operators for all of the predifined SGI-style allocators.
// This ensures that __allocator<malloc_alloc> (for example) will
// work correctly.

template <int inst>
inline bool operator==(const __malloc_alloc<inst>&,
                       const __malloc_alloc<inst>&)
{
  return true;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <int __inst>
inline bool operator!=(const __malloc_alloc<__inst>&,
                       const __malloc_alloc<__inst>&)
{
  return false;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#if ! defined (__STL_USE_MALLOC) && ! defined ( __STL_USE_NEWALLOC )

template <bool __threads, int __inst>
inline bool operator==(const __default_alloc_template<__threads, __inst>&,
                       const __default_alloc_template<__threads, __inst>&)
{
  return true;
}

#endif

#if defined( __STL_FUNCTION_TMPL_PARTIAL_ORDER ) && !defined (__STL_USE_MALLOC) && !defined ( __STL_USE_NEWALLOC )

template <bool __threads, int __inst>
inline bool operator!=(const __default_alloc_template<__threads, __inst>&,
                       const __default_alloc_template<__threads, __inst>&)
{
  return false;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

template <class _Alloc>
inline bool operator==(const debug_alloc<_Alloc>&,
                       const debug_alloc<_Alloc>&) {
  return true;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class _Alloc>
inline bool operator!=(const debug_alloc<_Alloc>&,
                       const debug_alloc<_Alloc>&) {
  return false;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

// Another allocator adaptor: _Alloc_traits.  This serves two
// purposes.  First, make it possible to write containers that can use
// either SGI-style allocators or standard-conforming allocator.
// Second, provide a mechanism so that containers can query whether or
// not the allocator has distinct instances.  If not, the container
// can avoid wasting a word of memory to store an empty object.

// This adaptor uses partial specialization.  The general case of
// _Alloc_traits<_Tp, _Alloc> assumes that _Alloc is a
// standard-conforming allocator, possibly with non-equal instances
// and non-static members.  (It still behaves correctly even if _Alloc
// has static member and if all instances are equal.  Refinements
// affect performance, not correctness.)

// There are always two members: allocator_type, which is a standard-
// conforming allocator type for allocating objects of type _Tp, and
// _S_instanceless, a static const member of type bool.  If
// _S_instanceless is true, this means that there is no difference
// between any two instances of type allocator_type.  Furthermore, if
// _S_instanceless is true, then _Alloc_traits has one additional
// member: _Alloc_type.  This type encapsulates allocation and
// deallocation of objects of type _Tp through a static interface; it
// has two member functions, whose signatures are
//    static _Tp* allocate(size_t)
//    static void deallocate(_Tp*, size_t)

// The fully general version.

template <class _Tp, class _Allocator>
struct _Alloc_traits
{
  static const bool _S_instanceless = false;
  typedef typename _Allocator::__STL_TEMPLATE rebind<_Tp>::other 
          allocator_type;
};

template <class _Tp, class _Allocator>
const bool _Alloc_traits<_Tp, _Allocator>::_S_instanceless;

// The version for the default allocator.

template <class _Tp, class _Tp1>
struct _Alloc_traits<_Tp, allocator<_Tp1> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, alloc> _Alloc_type;
  typedef allocator<_Tp> allocator_type;
};

// Versions for the predefined SGI-style allocators.

template <class _Tp, int __inst>
struct _Alloc_traits<_Tp, __malloc_alloc<__inst> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __malloc_alloc<__inst> > _Alloc_type;
  typedef __allocator<_Tp, __malloc_alloc<__inst> > allocator_type;
};

#if ! defined (__STL_USE_MALLOC) && ! defined ( __STL_USE_NEWALLOC )
template <class _Tp, bool __threads, int __inst>
struct _Alloc_traits<_Tp, __default_alloc_template<__threads, __inst> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __default_alloc_template<__threads, __inst> > 
          _Alloc_type;
  typedef __allocator<_Tp, __default_alloc_template<__threads, __inst> > 
          allocator_type;
};
#endif

template <class _Tp, class _Alloc>
struct _Alloc_traits<_Tp, debug_alloc<_Alloc> >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, debug_alloc<_Alloc> > _Alloc_type;
  typedef __allocator<_Tp, debug_alloc<_Alloc> > allocator_type;
};

// Versions for the __allocator adaptor used with the predefined
// SGI-style allocators.

template <class _Tp, class _Tp1, int __inst>
struct _Alloc_traits<_Tp, 
                     __allocator<_Tp1, __malloc_alloc<__inst> > >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __malloc_alloc<__inst> > _Alloc_type;
  typedef __allocator<_Tp, __malloc_alloc<__inst> > allocator_type;
};

#if ! defined (__STL_USE_MALLOC) && ! defined ( __STL_USE_NEWALLOC )
template <class _Tp, class _Tp1, bool __thr, int __inst>
struct _Alloc_traits<_Tp, 
                      __allocator<_Tp1, 
                                  __default_alloc_template<__thr, __inst> > >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, __default_alloc_template<__thr,__inst> > 
          _Alloc_type;
  typedef __allocator<_Tp, __default_alloc_template<__thr,__inst> > 
          allocator_type;
};
#endif

template <class _Tp, class _Tp1, class _Alloc>
struct _Alloc_traits<_Tp, __allocator<_Tp1, debug_alloc<_Alloc> > >
{
  static const bool _S_instanceless = true;
  typedef simple_alloc<_Tp, debug_alloc<_Alloc> > _Alloc_type;
  typedef __allocator<_Tp, debug_alloc<_Alloc> > allocator_type;
};

#endif /* __STL_USE_STD_ALLOCATORS */

// this extension is used only for Apple workaround now
template <class _All>
struct _STL_factory {
  static _All _Instance() { return _All(); }
};

__STL_END_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

#endif /* __SGI_STL_INTERNAL_ALLOC_H */

// Local Variables:
// mode:C++
// End:
