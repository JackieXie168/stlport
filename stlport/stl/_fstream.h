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
// This header defines classes basic_filebuf, basic_ifstream,
// basic_ofstream, and basic_fstream.  These classes represent
// streambufs and streams whose sources or destinations are files.

#ifndef __SGI_STL_FSTREAM_H
#define __SGI_STL_FSTREAM_H

#if defined(__sgi) && !defined(__GNUC__) && !defined(_STANDARD_C_PLUS_PLUS)
#error This header file requires the -LANG:std option
#endif

#include <istream>              // Includes <ostream>, <ios>, <iosfwd>
#include <stl/_codecvt.h>
#include <cstdio>
#include <stl/_stdio_file.h>


#if !defined (__STL_USE_UNIX_IO) && !defined(__STL_USE_WIN32_IO) \
    && ! defined (__STL_USE_UNIX_EMULATION_IO) && !defined (__STL_USE_STDIO_IO)

# if defined (__STL_UNIX)  || defined (__CYGWIN__) 
// open/close/read/write
#  define __STL_USE_UNIX_IO
# elif defined (__STL_WIN32)  && ! defined (__CYGWIN__)
// CreateFile/ReadFile/WriteFile
#  define __STL_USE_WIN32_IO
# elif defined (__STL_WIN16) || defined (__STL_WIN32) || defined (__STL_MAC)
// _open/_read/_write
#  define __STL_USE_UNIX_EMULATION_IO
# else
// fopen/fread/fwrite
#  define __STL_USE_STDIO_IO
# endif /* __STL_UNIX */

#endif /* mode selection */


#if defined (__STL_USE_WIN32_IO)
typedef void* _STL_fd;
#elif defined (__STL_USE_UNIX_EMULATION_IO) || defined (__STL_USE_STDIO_IO) || defined (__STL_USE_UNIX_IO)
typedef int _STL_fd;
#else
#error "Configure i/o !"
#endif


__STL_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Class _Filebuf_base, a private base class to factor out the system-
// dependent code from basic_filebuf<>.

class __STL_CLASS_DECLSPEC _Filebuf_base {
public:                      // Opening and closing files.
  _Filebuf_base();

  bool _M_open(const char*, ios_base::openmode, long __protection);
  bool _M_open(const char*, ios_base::openmode);
  bool _M_open(int __id, ios_base::openmode = ios_base::__default_mode);
  bool _M_close();

public:                      // Low-level I/O, like Unix read/write
  ptrdiff_t _M_read(char* __buf,  ptrdiff_t __n);
  streamoff _M_seek(streamoff __offset, ios_base::seekdir __dir);
  streamoff _M_file_size();
  bool _M_write(char* __buf,  ptrdiff_t __n);

public:                      // Memory-mapped I/O.
  void* _M_mmap(streamoff __offset, streamoff __len);
  void _M_unmap(void* __mmap_base, streamoff __len);

public:
  // Returns a value n such that, if pos is the file pointer at the
  // beginning of the range [first, last), pos + n is the file pointer at
  // the end.  On many operating systems n == __last - __first.
  // In Unix, writing n characters always bumps the file position by n.
  // In Windows text mode, however, it bumps the file position by n + m,
  // where m is the number of newlines in the range.  That's because an
  // internal \n corresponds to an external two-character sequence.
  streamoff _M_get_offset(char* __first, char* __last) {
#if defined (__STL_UNIX) || defined (__STL_MAC)
    return __last - __first;
#else // defined (__STL_WIN32) || defined (__STL_WIN16) || defined (__STL_DOS)
    return ( (_M_openmode & ios_base::binary) != 0 )
      ? (__last - __first)
      : count(__first, __last, '\n') + (__last - __first);
#endif
  }

  // Returns true if we're in binary mode or if we're using an OS or file 
  // system where there is no distinction between text and binary mode.
  bool _M_in_binary_mode() const {
# if defined (__STL_UNIX) || defined (__STL_MAC)
    return true;
# elif defined (__STL_WIN32) || defined (__STL_WIN16) || defined (__STL_DOS)
    return (_M_openmode & ios_base::binary) != 0;
# else 
#   error "Port!"
# endif
  }

protected:                      // Static data members.
  static size_t _M_page_size;

protected:                      // Data members.
  _STL_fd _M_file_id;
# ifdef __STL_USE_STDIO_IO
  // for stdio, the whole FILE* is being kept here
  FILE* _M_file;
# endif
# ifdef __STL_USE_WIN32_IO
  void* _M_view_id; 
# endif

  ios_base::openmode _M_openmode     ;
  unsigned char      _M_is_open      ;
  unsigned char      _M_should_close ;
  unsigned char      _M_regular_file ;

public :
  static size_t  __STL_CALL __page_size() { return _M_page_size; } 
  int  __o_mode() const { return (int)_M_openmode; } 
  bool __is_open()      const { return (_M_is_open !=0 ); } 
  bool __should_close() const { return (_M_should_close != 0); } 
  bool __regular_file() const { return (_M_regular_file != 0); }
};




//----------------------------------------------------------------------
// Class basic_filebuf<>.

// Forward declaration of two helper classes.
template <class _Traits> class _Noconv_input;
__STL_TEMPLATE_NULL
class _Noconv_input<char_traits<char> >;

template <class _Traits> class _Noconv_output;
__STL_TEMPLATE_NULL
class _Noconv_output< char_traits<char> >;

// There is a specialized version of underflow, for basic_filebuf<char>,
// in fstream.cxx.

template <class _CharT, class _Traits>
class _Underflow;

 __STL_TEMPLATE_NULL class _Underflow< char, char_traits<char> >;

template <class _CharT, class _Traits>
class basic_filebuf : public basic_streambuf<_CharT, _Traits>
{
public:                         // Types.
  typedef _CharT                     char_type;
  typedef typename _Traits::int_type int_type;
  typedef typename _Traits::pos_type pos_type;
  typedef typename _Traits::off_type off_type;
  typedef _Traits                    traits_type;

  typedef typename _Traits::state_type _State_type;
  typedef basic_streambuf<_CharT, _Traits> _Base;
  typedef basic_filebuf<_CharT, _Traits> _Self;

public:                         // Constructors, destructor.
  basic_filebuf();  
  ~basic_filebuf();
  
public:                         // Opening and closing files.
  bool is_open() const { return _M_base.__is_open(); }

  _Self* open(const char* __s, ios_base::openmode __m) {
    return _M_base._M_open(__s, __m) ? this : 0;
  }

  // These two version of open() are extensions.
  _Self* open(const char* __s, ios_base::openmode __m,
		      long __protection) {
    return _M_base._M_open(__s, __m, __protection) ? this : 0;
  }
  
  _Self* open(int __id, ios_base::openmode __init_mode = ios_base::__default_mode) {
    return _M_base._M_open(__id, __init_mode) ? this : 0;
  }

  _Self* close();

protected:                      // Virtual functions from basic_streambuf.
  virtual streamsize showmanyc();
  virtual int_type underflow();

  virtual int_type pbackfail(int_type = traits_type::eof());
  virtual int_type overflow(int_type = traits_type::eof());

  virtual basic_streambuf<_CharT, _Traits>* setbuf(char_type*, streamsize);
  virtual pos_type seekoff(off_type, ios_base::seekdir,
                           ios_base::openmode = ios_base::in | ios_base::out);
  virtual pos_type seekpos(pos_type,
                           ios_base::openmode = ios_base::in | ios_base::out);

  virtual int sync();
  virtual void imbue(const locale&);

private:                        // Helper functions.

  // Precondition: we are currently in putback input mode.  Effect:
  // switches back to ordinary input mode.
  void _M_exit_putback_mode() {
    this->setg(_M_saved_eback, _M_saved_gptr, _M_saved_egptr);
    _M_in_putback_mode = false;
  }
  bool _M_switch_to_input_mode();
  void _M_exit_input_mode();
  bool _M_switch_to_output_mode();

  int_type _M_input_error();
  int_type _M_underflow_aux();
  //  friend class _Noconv_input<_Traits>;
  //  friend class _Noconv_output<_Traits>;
  friend class _Underflow<_CharT, _Traits>;

  int_type _M_output_error();
  bool _M_unshift();

  bool _M_allocate_buffers(_CharT* __buf, int __n);
  bool _M_allocate_buffers();
  void _M_deallocate_buffers();

  pos_type _M_seek_return(off_type __off, _State_type __state) {
    if (__off != -1) {
      if (_M_in_input_mode)
        _M_exit_input_mode();
      _M_in_input_mode = false;
      _M_in_output_mode = false;
      _M_in_putback_mode = false;
      _M_in_error_mode = false;
      this->setg(0, 0, 0);
      this->setp(0, 0);
    }
    
    pos_type __result(__off);
    __result.state(__state);
    return __result;
  }
  
  bool _M_seek_init(bool __do_unshift);

  void _M_setup_codecvt(const locale&);

private:                        // Data members used in all modes.

  _Filebuf_base _M_base;

private:                        // Locale-related information.

  unsigned char _M_constant_width;
  unsigned char _M_always_noconv;
  
  // private:                        // Mode flags.
  unsigned char _M_int_buf_dynamic;  // True if internal buffer is heap allocated,
  // false if it was supplied by the user.
  unsigned char _M_in_input_mode;
  unsigned char _M_in_output_mode;
  unsigned char _M_in_error_mode;
  unsigned char _M_in_putback_mode;
  
  // Internal buffer: characters seen by the filebuf's clients.
  _CharT* _M_int_buf;
  _CharT* _M_int_buf_EOS;
  
  // External buffer: characters corresponding to the external file.
  char* _M_ext_buf;
  char* _M_ext_buf_EOS;

  // The range [_M_ext_buf, _M_ext_buf_converted) contains the external
  // characters corresponding to the sequence in the internal buffer.  The
  // range [_M_ext_buf_converted, _M_ext_buf_end) contains characters that
  // have been read into the external buffer but have not been converted
  // to an internal sequence.
  char* _M_ext_buf_converted;
  char* _M_ext_buf_end;

  // State corresponding to beginning of internal buffer.
  _State_type _M_state;

private:                        // Data members used only in input mode.

  // Similar to _M_state except that it corresponds to
  // the end of the internal buffer instead of the beginning.
  _State_type _M_end_state;

  // This is a null pointer unless we are in mmap input mode.
  void*     _M_mmap_base;
  streamoff _M_mmap_len;

private:                        // Data members used only in putback mode.
  _CharT* _M_saved_eback;
  _CharT* _M_saved_gptr;
  _CharT* _M_saved_egptr;

  typedef codecvt<_CharT, char, _State_type> _Codecvt;
  const _Codecvt* _M_codecvt;

  int _M_width;                 // Width of the encoding (if constant), else 1
  int _M_max_width;             // Largest possible width of single character.


  enum { _S_pback_buf_size = 8 };
  _CharT _M_pback_buf[_S_pback_buf_size];

  // for _Noconv_output
public:
  bool _M_write(char* __buf,  ptrdiff_t __n) {return _M_base._M_write(__buf, __n); }

public:
  int_type
  _M_do_noconv_input() {
    _M_ext_buf_converted = _M_ext_buf_end;
    this->setg((char_type*)_M_ext_buf, (char_type*)_M_ext_buf, (char_type*)_M_ext_buf_end);
    return traits_type::to_int_type(*_M_ext_buf);
  }
};

# if defined (__STL_USE_TEMPLATE_EXPORT)
__STL_EXPORT_TEMPLATE_CLASS basic_filebuf<char, char_traits<char> >;
#  if ! defined (__STL_NO_WCHAR_T)
__STL_EXPORT_TEMPLATE_CLASS basic_filebuf<wchar_t, char_traits<wchar_t> >;
#  endif
# endif /* __STL_USE_TEMPLATE_EXPORT */

// public:
// helper class.
template <class _CharT>
struct _Filebuf_Tmp_Buf
{
  _CharT* _M_ptr;
  _Filebuf_Tmp_Buf(ptrdiff_t __n) : _M_ptr(0) { _M_ptr = new _CharT[__n]; }
  ~_Filebuf_Tmp_Buf() { delete[] _M_ptr; }
};


//
// This class had to be designed very carefully to work
// with Visual C++.
//
template <class _Traits>
class _Noconv_output {
public:
  typedef typename _Traits::char_type char_type;
  static bool  __STL_CALL _M_doit(basic_filebuf<char_type, _Traits >*, 
                                  char_type*, char_type*)
  {
      return false; 
  }
};

__STL_TEMPLATE_NULL
class __STL_CLASS_DECLSPEC _Noconv_output< char_traits<char> > {
public:
  static bool  __STL_CALL
  _M_doit(basic_filebuf<char, char_traits<char> >* __buf, 
          char* __first, char* __last)
  {
    ptrdiff_t __n = __last - __first;
    if (__buf->_M_write(__first, __n)) {
      return true;
    }
    else
      return false; 
  }
};

//----------------------------------------------------------------------
// basic_filebuf<> helper functions.


//----------------------------------------
// Helper functions for switching between modes.

//
// This class had to be designed very carefully to work
// with Visual C++.
//
template <class _Traits>
class _Noconv_input {
public:
  typedef typename _Traits::int_type int_type;
  typedef typename _Traits::char_type char_type;

  static inline int_type __STL_CALL
  _M_doit(basic_filebuf<char_type, _Traits>*) 
  {
    return 0;
  }
};

__STL_TEMPLATE_NULL
class _Noconv_input<char_traits<char> > {
public:
  static inline int __STL_CALL
  _M_doit(basic_filebuf<char, char_traits<char> >* __buf)  {
    return __buf->_M_do_noconv_input();
  }
};

// underflow() may be called for one of two reasons.  (1) We've
// been going through the special putback buffer, and we need to move back
// to the regular internal buffer.  (2) We've exhausted the internal buffer,
// and we need to replentish it.  
template <class _CharT, class _Traits>
class  __STL_CLASS_DECLSPEC _Underflow {
public:
  typedef typename _Traits::int_type int_type;
  typedef _Traits                    traits_type;
  
  static int_type __STL_CALL _M_doit(basic_filebuf<_CharT, _Traits>* __this);
};


// Specialization of underflow: if the character type is char, maybe
// we can use mmap instead of read.
__STL_TEMPLATE_NULL
class __STL_CLASS_DECLSPEC _Underflow< char, char_traits<char> > {
public:
  typedef char_traits<char>::int_type int_type;
  typedef char_traits<char> traits_type;
  static  int __STL_CALL _M_doit(basic_filebuf<char, traits_type >* __this);
};

// There is a specialized version of underflow, for basic_filebuf<char>,
// in fstream.cxx.

template <class _CharT, class _Traits>
__STL_TYPENAME_ON_RETURN_TYPE _Underflow<_CharT, _Traits>::int_type __STL_CALL
 _Underflow<_CharT, _Traits>::_M_doit(basic_filebuf<_CharT, _Traits>* __this)
{
  if (!__this->_M_in_input_mode) {
    if (!__this->_M_switch_to_input_mode())
      return traits_type::eof();
  }
  
  else if (__this->_M_in_putback_mode) {
    __this->_M_exit_putback_mode();
    if (__this->gptr() != __this->egptr()) {
      int_type __c = traits_type::to_int_type(*__this->gptr());
      return __c;
    }
  }
  
  return __this->_M_underflow_aux();
}

#if defined( __STL_USE_TEMPLATE_EXPORT ) && ! defined (__STL_NO_WCHAR_T)
__STL_EXPORT_TEMPLATE_CLASS _Underflow<wchar_t, char_traits<wchar_t> >;
#endif


//----------------------------------------------------------------------
// Class basic_ifstream<>

template <class _CharT, class _Traits>
class basic_ifstream : public basic_istream<_CharT, _Traits>
{
public:                         // Types
  typedef _CharT                     char_type;
  typedef typename _Traits::int_type int_type;
  typedef typename _Traits::pos_type pos_type;
  typedef typename _Traits::off_type off_type;
  typedef _Traits                    traits_type;

  typedef basic_ios<_CharT, _Traits>                _Basic_ios;
  typedef basic_istream<_CharT, _Traits>            _Base;
  typedef basic_filebuf<_CharT, _Traits>            _Buf;

public:                         // Constructors, destructor.

  basic_ifstream() : 
    basic_ios<_CharT, _Traits>(),  basic_istream<_CharT, _Traits>(0), _M_buf() {
      this->init(&_M_buf);
  }

  explicit basic_ifstream(const char* __s, ios_base::openmode __mod = ios_base::in) : 
    basic_ios<_CharT, _Traits>(),  basic_istream<_CharT, _Traits>(0),
    _M_buf() {
      this->init(&_M_buf);
      if (!_M_buf.open(__s, __mod | ios_base::in))
	this->setstate(ios_base::failbit);
  }

  ~basic_ifstream() {}

public:                         // File and buffer operations.
  basic_filebuf<_CharT, _Traits>* rdbuf() const
    { return __CONST_CAST(_Buf*,&_M_buf); }

  bool is_open() {
    return this->rdbuf()->is_open();
  }

  void open(const char* __s, ios_base::openmode __mod = ios_base::in) {
    if (!this->rdbuf()->open(__s, __mod | ios_base::in))
      this->setstate(ios_base::failbit);
  }

  void close() {
    if (!this->rdbuf()->close())
      this->setstate(ios_base::failbit);
  }


private:
  basic_filebuf<_CharT, _Traits> _M_buf;
};


//----------------------------------------------------------------------
// Class basic_ofstream<>

template <class _CharT, class _Traits>
class basic_ofstream : public basic_ostream<_CharT, _Traits>
{
public:                         // Types
  typedef _CharT                     char_type;
  typedef typename _Traits::int_type int_type;
  typedef typename _Traits::pos_type pos_type;
  typedef typename _Traits::off_type off_type;
  typedef _Traits                    traits_type;

  typedef basic_ios<_CharT, _Traits>                _Basic_ios;
  typedef basic_ostream<_CharT, _Traits>            _Base;
  typedef basic_filebuf<_CharT, _Traits>            _Buf;

public:                         // Constructors, destructor.
  basic_ofstream() : 
    basic_ios<_CharT, _Traits>(), 
    basic_ostream<_CharT, _Traits>(0), _M_buf() {
      this->init(&_M_buf);
  }
  explicit basic_ofstream(const char* __s, ios_base::openmode __mod = ios_base::out) 
    : basic_ios<_CharT, _Traits>(), basic_ostream<_CharT, _Traits>(0),
      _M_buf() {
	this->init(&_M_buf);
	if (!_M_buf.open(__s, __mod | ios_base::out))
	  this->setstate(ios_base::failbit);
  }
  ~basic_ofstream() {}

public:                         // File and buffer operations.
  basic_filebuf<_CharT, _Traits>* rdbuf() const
    { return __CONST_CAST(_Buf*,&_M_buf); } 

  bool is_open() {
    return this->rdbuf()->is_open();
  }

  void open(const char* __s, ios_base::openmode __mod= ios_base::out) {
    if (!this->rdbuf()->open(__s, __mod | ios_base::out))
      this->setstate(ios_base::failbit);
  }

  void close() {
    if (!this->rdbuf()->close())
      this->setstate(ios_base::failbit);
  }

private:
  basic_filebuf<_CharT, _Traits> _M_buf;
};


//----------------------------------------------------------------------
// Class basic_fstream<>

template <class _CharT, class _Traits>
class __STL_DECLSPEC basic_fstream : public basic_iostream<_CharT, _Traits>
{
public:                         // Types
  typedef _CharT                     char_type;
  typedef typename _Traits::int_type int_type;
  typedef typename _Traits::pos_type pos_type;
  typedef typename _Traits::off_type off_type;
  typedef _Traits                    traits_type;

  typedef basic_ios<_CharT, _Traits>                _Basic_ios;
  typedef basic_iostream<_CharT, _Traits>           _Base;
  typedef basic_filebuf<_CharT, _Traits>            _Buf;

public:                         // Constructors, destructor.
  
  basic_fstream()   
    : basic_ios<_CharT, _Traits>(), basic_iostream<_CharT, _Traits>(0), _M_buf() {
      this->init(&_M_buf);
  }

  explicit basic_fstream(const char* __s,
                         ios_base::openmode __mod = ios_base::in | ios_base::out) :
    basic_ios<_CharT, _Traits>(), basic_iostream<_CharT, _Traits>(0), _M_buf() {
      this->init(&_M_buf);
      if (!_M_buf.open(__s, __mod))
	this->setstate(ios_base::failbit);
  }
  ~basic_fstream() {}

public:                         // File and buffer operations.

  basic_filebuf<_CharT, _Traits>* rdbuf() const
    { return __CONST_CAST(_Buf*,&_M_buf); } 

  bool is_open() {
    return this->rdbuf()->is_open();
  }

  void open(const char* __s, 
	    ios_base::openmode __mod = 
	    ios_base::in | ios_base::out) {
    if (!this->rdbuf()->open(__s, __mod))
      this->setstate(ios_base::failbit);
  }

  void close() {
    if (!this->rdbuf()->close())
      this->setstate(ios_base::failbit);
  }

private:
  basic_filebuf<_CharT, _Traits> _M_buf;
};

__STL_END_NAMESPACE

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_fstream.c>
# endif

__STL_BEGIN_NAMESPACE

# if defined (__STL_USE_TEMPLATE_EXPORT)
__STL_EXPORT_TEMPLATE_CLASS basic_ifstream<char, char_traits<char> >;
__STL_EXPORT_TEMPLATE_CLASS basic_ofstream<char, char_traits<char> >;
__STL_EXPORT_TEMPLATE_CLASS basic_fstream<char, char_traits<char> >;
#  if ! defined (__STL_NO_WCHAR_T)
__STL_EXPORT_TEMPLATE_CLASS basic_ifstream<wchar_t, char_traits<wchar_t> >;
__STL_EXPORT_TEMPLATE_CLASS basic_ofstream<wchar_t, char_traits<wchar_t> >;
__STL_EXPORT_TEMPLATE_CLASS basic_fstream<wchar_t, char_traits<wchar_t> >;
#  endif
# endif /* __STL_USE_TEMPLATE_EXPORT */

__STL_END_NAMESPACE

#endif /* __SGI_STL_FSTREAM */


// Local Variables:
// mode:C++
// End:
