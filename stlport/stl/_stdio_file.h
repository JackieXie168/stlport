/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
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


// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.


#ifndef __SGI_STL_STDIO_FILE_H
#define __SGI_STL_STDIO_FILE_H

// This file provides a low-level interface between the internal 
// representation of struct FILE, from the C stdio library, and 
// the C++ I/O library.  The C++ I/O library views a FILE object as
// a collection of three pointers: the beginning of the buffer, the
// current read/write position, and the end of the buffer.

// The interface:
// - char* _FILE_[IO]_begin(const FILE& __f);
//       Returns a pointer to the beginning of the buffer.
// - char* _FILE_[IO]_next(const FILE& __f);
//       Returns the current read/write position within the buffer.
// - char* _FILE_[IO]_end(const FILE& __f);
//       Returns a pointer immediately past the end of the buffer.
// - char* _FILE_[IO]_avail(const FILE& __f);
//       Returns the number of characters remaining in the buffer, i.e.
//       _FILE_[IO]_end(__f) - _FILE_[IO]_next(__f).
// - char& _FILE_[IO]_preincr(FILE& __f)
//       Increments the current read/write position by 1, returning the 
//       character at the old position.
// - char& _FILE_[IO]_postincr(FILE& __f)
//       Increments the current read/write position by 1, returning the 
//       character at the old position.
// - char& _FILE_[IO]_predecr(FILE& __f)
//       Decrements the current read/write position by 1, returning the 
//       character at the old position.
// - char& _FILE_[IO]_postdecr(FILE& __f)
//       Decrements the current read/write position by 1, returning the 
//       character at the old position.
// - void _FILE_[IO]_bump(FILE& __f, int __n)
//       Increments the current read/write position by __n.
// - void _FILE_[IO]_set(FILE& __f, char* __begin, char* __next, char* __end);
//       Sets the beginning of the bufer to __begin, the current read/write
//       position to __next, and the buffer's past-the-end pointer to __end.
//       If any of those pointers is null, then all of them must be null.

// Each function comes in two versions, one for a FILE used as an input
// buffer and one for a FILE used as an output buffer.  In some stdio
// implementations the two functions are identical, but in others they are
// not.

#include <cstdio>

#if defined(__MSL__)
# include <unix.h>	// get the definition of fileno
#endif

__STL_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Implementation for the IRIX C library.
// Solaris interface looks to be identical.
#if !defined(__STL_USE_GLIBC) && \
    ( defined(__sgi) || \
      defined(__sun)  || \
      defined (__osf__) || defined(__DECCXX) || \
      defined (__STL_MSVC) || defined (__ICL) || defined (__MINGW32__) \
      || defined (__xlC__))

#if defined ( _MSC_VER ) || defined (__ICL) || defined (__MINGW32__)
typedef  char* _File_ptr_type;
#else
typedef  unsigned char* _File_ptr_type;
#endif

inline int   _FILE_fd(const FILE& __f) { return __f._file; }
inline char* _FILE_I_begin(const FILE& __f) { return (char*) __f._base; }
inline char* _FILE_I_next(const FILE& __f) { return (char*) __f._ptr; }  
inline char* _FILE_I_end(const FILE& __f)
  { return (char*) __f._ptr + __f._cnt; }

inline ptrdiff_t _FILE_I_avail(const FILE& __f) { return __f._cnt; }

inline char& _FILE_I_preincr(FILE& __f)
  { --__f._cnt; return *(char*) (++__f._ptr); }
inline char& _FILE_I_postincr(FILE& __f)
  { --__f._cnt; return *(char*) (__f._ptr++); }
inline char& _FILE_I_predecr(FILE& __f)
  { ++__f._cnt; return *(char*) (--__f._ptr); }
inline char& _FILE_I_postdecr(FILE& __f)
  { ++__f._cnt; return *(char*) (__f._ptr--); }
inline void  _FILE_I_bump(FILE& __f, int __n)
  { __f._ptr += __n; __f._cnt -= __n; }

inline void _FILE_I_set(FILE& __f, char* __begin, char* __next, char* __end) {
  __f._base = (_File_ptr_type) __begin;
  __f._ptr  = (_File_ptr_type) __next;
  __f._cnt  = __end - __next;
}

# define __STL_FILE_I_O_IDENTICAL 1

#elif defined (__CYGWIN__) || defined(__FreeBSD__)

inline int   _FILE_fd(const FILE& __f) { return __f._file; }
inline char* _FILE_I_begin(const FILE& __f) { return (char*) __f._bf._base; }
inline char* _FILE_I_next(const FILE& __f) { return (char*) __f._p; }  
inline char* _FILE_I_end(const FILE& __f)
  { return (char*) __f._p + __f._bf._size; }

inline ptrdiff_t _FILE_I_avail(const FILE& __f) { return __f._bf._size; }

inline char& _FILE_I_preincr(FILE& __f)
  { --__f._bf._size; return *(char*) (++__f._p); }
inline char& _FILE_I_postincr(FILE& __f)
  { --__f._bf._size; return *(char*) (__f._p++); }
inline char& _FILE_I_predecr(FILE& __f)
  { ++__f._bf._size; return *(char*) (--__f._p); }
inline char& _FILE_I_postdecr(FILE& __f)
  { ++__f._bf._size; return *(char*) (__f._p--); }
inline void  _FILE_I_bump(FILE& __f, int __n)
  { __f._p += __n; __f._bf._size -= __n; }

inline void _FILE_I_set(FILE& __f, char* __begin, char* __next, char* __end) {
  __f._bf._base = (unsigned char*) __begin;
  __f._p  = (unsigned char*) __next;
  __f._bf._size  = __end - __next;
}

# define __STL_FILE_I_O_IDENTICAL

#elif defined(__STL_USE_GLIBC)

inline int   _FILE_fd(const FILE& __f) { return fileno(__CONST_CAST(FILE*,&__f)); }
inline char* _FILE_I_begin(const FILE& __f) { return __f._IO_read_base; }
inline char* _FILE_I_next(const FILE& __f)  { return __f._IO_read_ptr; }
inline char* _FILE_I_end(const FILE& __f)   { return __f._IO_read_end; }

inline ptrdiff_t _FILE_I_avail(const FILE& __f) 
  { return __f._IO_read_end - __f._IO_read_ptr; }

inline char& _FILE_I_preincr(FILE& __f)  { return *++__f._IO_read_ptr; }
inline char& _FILE_I_postincr(FILE& __f) { return *__f._IO_read_ptr++; }
inline char& _FILE_I_predecr(FILE& __f)  { return *--__f._IO_read_ptr; }
inline char& _FILE_I_postdecr(FILE& __f) { return *__f._IO_read_ptr--; }
inline void  _FILE_I_bump(FILE& __f, int __n) { __f._IO_read_ptr += __n; }

inline void _FILE_I_set(FILE& __f, char* __begin, char* __next, char* __end) {
  __f._IO_read_base = __begin; 
  __f._IO_read_ptr  = __next; 
  __f._IO_read_end  = __end; 
}

inline char* _FILE_O_begin(const FILE& __f) { return __f._IO_write_base; }
inline char* _FILE_O_next(const FILE& __f)  { return __f._IO_write_ptr; }
inline char* _FILE_O_end(const FILE& __f)   { return __f._IO_write_end; }

inline ptrdiff_t _FILE_O_avail(const FILE& __f) 
  { return __f._IO_write_end - __f._IO_write_ptr; }

inline char& _FILE_O_preincr(FILE& __f)  { return *++__f._IO_write_ptr; }
inline char& _FILE_O_postincr(FILE& __f) { return *__f._IO_write_ptr++; }
inline char& _FILE_O_predecr(FILE& __f)  { return *--__f._IO_write_ptr; }
inline char& _FILE_O_postdecr(FILE& __f) { return *__f._IO_write_ptr--; }
inline void  _FILE_O_bump(FILE& __f, int __n) { __f._IO_write_ptr += __n; }

inline void _FILE_O_set(FILE& __f, char* __begin, char* __next, char* __end) {
  __f._IO_write_base = __begin; 
  __f._IO_write_ptr  = __next; 
  __f._IO_write_end  = __end; 

}

#elif defined(__hpux) /* && defined(__hppa) && defined(__HP_aCC)) */

#if defined(__STL_HPACC_BROKEN_BUFEND)
#  undef  _bufend
#  define _bufend(__p) \
     (*(((__p)->__flag & _IOEXT)  ? &((__REINTERPRET_CAST(_FILEX*,(__p)))->__bufendp)  \
                               : &(__bufendtab[__REINTERPRET_CAST(FILE*,(__p)) - __iob])))
#endif

inline int   _FILE_fd(const FILE& __f) { return fileno(__CONST_CAST(FILE *,&__f)); }
inline char* _FILE_I_begin(const FILE& __f) { return (__REINTERPRET_CAST(char*, __f.__base)); }
inline char* _FILE_I_next(const FILE& __f)  { return (__REINTERPRET_CAST(char*, __f.__ptr)); }
inline char* _FILE_I_end(const FILE& __f)   { return (__REINTERPRET_CAST(char*, __f.__ptr +__f._cnt)); }

inline ptrdiff_t _FILE_I_avail(const FILE& __f)  { return __f._cnt; }

inline char& _FILE_I_preincr(FILE& __f)  { --__f.__cnt; return *__REINTERPRET_CAST(char*, ++__f.__ptr); }
inline char& _FILE_I_postincr(FILE& __f) { --__f.__cnt; return *__REINTERPRET_CAST(char*, __f.__ptr++); }
inline char& _FILE_I_predecr(FILE& __f)  { ++__f.__cnt; return *__REINTERPRET_CAST(char*,--__f.__ptr); }
inline char& _FILE_I_postdecr(FILE& __f) { ++__f.__cnt; return *__REINTERPRET_CAST(char*,__f.__ptr--); }
inline void  _FILE_I_bump(FILE& __f, int __n) { __f.__cnt -= __n; __f.__ptr += __n; }
 
inline void _FILE_I_set(FILE& __f, char* __begin, char* __next, char* __end) {
# if defined(__hpux)
   if( (unsigned long) (&__f - &__iob[0]) > _NFILE)
        __f.__flag |= _IOEXT;  // used by stdio's _bufend macro and goodness knows what else...
# endif
  __f.__cnt  = __end - __next; 
  __f.__base = __REINTERPRET_CAST(unsigned char*, __begin); 
  __f.__ptr  = __REINTERPRET_CAST(unsigned char*, __next);
  _bufend(&__f) = __REINTERPRET_CAST(unsigned char*, __end); 
}

// For HPUX stdio, input and output FILE manipulation is identical.

# define __STL_FILE_I_O_IDENTICAL

#elif defined (__BORLANDC__)

typedef  unsigned char* _File_ptr_type;

inline int   _FILE_fd(const FILE& __f) { return __f.fd; }
inline char* _FILE_I_begin(const FILE& __f) { return (char*) __f.buffer; }
inline char* _FILE_I_next(const FILE& __f) { return (char*) __f.curp; }  
inline char* _FILE_I_end(const FILE& __f)
  { return (char*) __f.curp + __f.bsize; }

inline ptrdiff_t _FILE_I_avail(const FILE& __f) { return __f.bsize; }

inline char& _FILE_I_preincr(FILE& __f)
  { --__f.bsize; return *(char*) (++__f.curp); }
inline char& _FILE_I_postincr(FILE& __f)
  { --__f.bsize; return *(char*) (__f.curp++); }
inline char& _FILE_I_predecr(FILE& __f)
  { ++__f.bsize; return *(char*) (--__f.curp); }
inline char& _FILE_I_postdecr(FILE& __f)
  { ++__f.bsize; return *(char*) (__f.curp--); }
inline void  _FILE_I_bump(FILE& __f, int __n)
  { __f.curp += __n; __f.bsize -= __n; }

inline void _FILE_I_set(FILE& __f, char* __begin, char* __next, char* __end) {
  __f.buffer = (_File_ptr_type) __begin;
  __f.curp   = (_File_ptr_type) __next;
  __f.bsize  = __end - __next;
}

# define __STL_FILE_I_O_IDENTICAL

#elif defined( __MWERKS__ )

// using MWERKS-specific defines here to detect other OS targets
// dwa: I'm not sure they provide fileno for all OS's, but this should
// work for Win32 and WinCE
# if __dest_os == __mac_os
inline int   _FILE_fd(const FILE& __f) { return ::fileno(__CONST_CAST(FILE*, &__f)); }
# else
inline int   _FILE_fd(const FILE& __f) { return ::_fileno(__CONST_CAST(FILE*, &__f)); }
# endif

//       Returns a pointer to the beginning of the buffer.
inline char* _FILE_I_begin(const FILE& __f) { return __REINTERPRET_CAST(char*, __f.buffer); }
//       Returns the current read/write position within the buffer.
inline char* _FILE_I_next(const FILE& __f) { return __REINTERPRET_CAST(char*, __f.buffer_ptr); }

//       Returns a pointer immediately past the end of the buffer.
inline char* _FILE_I_end(const FILE& __f) { return __REINTERPRET_CAST(char*, __f.buffer_ptr + __f.buffer_len); }

//       Returns the number of characters remaining in the buffer, i.e.
//       _FILE_[IO]_end(__f) - _FILE_[IO]_next(__f).
inline ptrdiff_t _FILE_I_avail(const FILE& __f) { return __f.buffer_len; }

//       Increments the current read/write position by 1, returning the 
//       character at the old position.
inline char& _FILE_I_preincr(FILE& __f)
  { --__f.buffer_len; return *(char*) (++__f.buffer_ptr); }
inline char& _FILE_I_postincr(FILE& __f)
  { --__f.buffer_len; return *(char*) (__f.buffer_ptr++); }
inline char& _FILE_I_predecr(FILE& __f)
  { ++__f.buffer_len; return *(char*) (--__f.buffer_ptr); }
inline char& _FILE_I_postdecr(FILE& __f)
  { ++__f.buffer_len; return *(char*) (__f.buffer_ptr--); }
inline void  _FILE_I_bump(FILE& __f, int __n)
  { __f.buffer_ptr += __n; __f.buffer_len -= __n; }

inline void _FILE_I_set(FILE& __f, char* __begin, char* __next, char* __end) {
  __f.buffer = __REINTERPRET_CAST(unsigned char*, __begin);
  __f.buffer_ptr   = __REINTERPRET_CAST(unsigned char*, __next);
  __f.buffer_len  = __end - __next;
  __f.buffer_size = __end - __begin;
}

# define __STL_FILE_I_O_IDENTICAL

#elif defined(__MRC__) || defined(__SC__)		//*TY 02/24/2000 - added support for MPW

inline int   _FILE_fd(const FILE& __f) { return __f._file; }

//       Returns a pointer to the beginning of the buffer.
inline char* _FILE_I_begin(const FILE& __f) { return (char*) __f._base; }

//       Returns the current read/write position within the buffer.
inline char* _FILE_I_next(const FILE& __f) { return (char*) __f._ptr; }

//       Returns a pointer immediately past the end of the buffer.
inline char* _FILE_I_end(const FILE& __f) { return (char*)__f._end; }

//       Returns the number of characters remaining in the buffer, i.e.
//       _FILE_[IO]_end(__f) - _FILE_[IO]_next(__f).
inline ptrdiff_t _FILE_I_avail(const FILE& __f) { return __f._cnt; }

//       Increments the current read/write position by 1, returning the 
//       character at the NEW position.
inline char& _FILE_I_preincr(FILE& __f) { --__f._cnt; return*(char*) (++__f._ptr); }


//       Increments the current read/write position by 1, returning the 
//       character at the old position.
inline char& _FILE_I_postincr(FILE& __f) { --__f._cnt; return*(char*) (__f._ptr++); }

//       Decrements the current read/write position by 1, returning the 
//       character at the NEW position.
inline char& _FILE_I_predecr(FILE& __f) { ++__f._cnt; return*(char*) (--__f._ptr); }

//       Decrements the current read/write position by 1, returning the 
//       character at the old position.
inline char& _FILE_I_postdecr(FILE& __f) { ++__f._cnt; return*(char*) (__f._ptr--); }

//       Increments the current read/write position by __n.
inline void _FILE_I_bump(FILE& __f, int __n) { __f._cnt -= __n; __f._ptr += __n; }

//       Sets the beginning of the bufer to __begin, the current read/write
//       position to __next, and the buffer's past-the-end pointer to __end.
//       If any of those pointers is null, then all of them must be null.
inline void _FILE_I_set(FILE& __f, char* __begin, char* __next, char* __end)
{
	__f._base = (unsigned char*)__begin;
	__f._ptr  = (unsigned char*)__next;
	__f._end  = (unsigned char*)__end;
	__f._cnt  = __end - __next;
	__f._size = __end - __begin;
}

# define __STL_FILE_I_O_IDENTICAL

#else  /* A C library that we don't have an implementation for. */

# error The C++ I/O library is not configured for this compiler

#endif


// For most stdio's , input and output FILE manipulation is identical.
# ifdef __STL_FILE_I_O_IDENTICAL
inline char* _FILE_O_begin(const FILE& __f) { return _FILE_I_begin(__f); }
inline char* _FILE_O_next(const FILE& __f)  { return _FILE_I_next(__f); }
inline char* _FILE_O_end(const FILE& __f)   { return _FILE_I_end(__f); }

inline ptrdiff_t _FILE_O_avail(const FILE& __f) { return _FILE_I_avail(__f); }

inline char& _FILE_O_preincr(FILE& __f)  { return _FILE_I_preincr(__f); }
inline char& _FILE_O_postincr(FILE& __f) { return _FILE_I_postincr(__f); }
inline char& _FILE_O_predecr(FILE& __f)  { return _FILE_I_predecr(__f); }
inline char& _FILE_O_postdecr(FILE& __f) { return _FILE_I_postdecr(__f); }

inline void  _FILE_O_bump(FILE& __f, int __n) { _FILE_I_bump(__f, __n); }
inline void _FILE_O_set(FILE& __f, char* __begin, char* __next, char* __end)
  { _FILE_I_set(__f, __begin, __next, __end); }
# endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_STDIO_FILE_H */

// Local Variables:
// mode:C++
// End:
