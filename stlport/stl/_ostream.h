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


#ifndef __SGI_STL_OSTREAM_H
#define __SGI_STL_OSTREAM_H

#include <ios>                  // For basic_ios<>.  Includes <iosfwd>.
#include <limits>               // Needed for class numeric_limits<>.
#include <streambuf>            // For basic_streambuf.

__STL_BEGIN_NAMESPACE

template <class _CharT, class _Traits, class _Number> 
basic_ostream<_CharT, _Traits>& __STL_CALL
_M_put_num(basic_ostream<_CharT, _Traits>& __os, _Number __x);

# if defined (__STL_USE_TEMPLATE_EXPORT)
template <class _CharT, class _Traits>
class _Osentry;
# endif

//----------------------------------------------------------------------
// class basic_ostream<>

template <class _CharT, class _Traits>
class basic_ostream : virtual public basic_ios<_CharT, _Traits>
{
  typedef basic_ostream<_CharT, _Traits> _Self;
  
public:                         // Types
  typedef _CharT                     char_type;
  typedef typename _Traits::int_type int_type;
  typedef typename _Traits::pos_type pos_type;
  typedef typename _Traits::off_type off_type;
  typedef _Traits                    traits_type;
  typedef basic_ios<_CharT, _Traits> _Basic_ios;

public:                         // Constructor and destructor.
  explicit basic_ostream(basic_streambuf<_CharT, _Traits>* __buf);
  ~basic_ostream();

public:                         // Hooks for manipulators.
  typedef basic_ios<_CharT, _Traits>& (__STL_CALL *__ios_fn)(basic_ios<_CharT, _Traits>&);
  typedef ios_base& (__STL_CALL *__ios_base_fn)(ios_base&);
  typedef _Self& (__STL_CALL *__ostream_fn)(_Self&);
  _Self& operator<< (__ostream_fn __f) { return __f(*this); }
  _Self & operator<< (__ios_base_fn __f) { __f(*this); return *this; }
  _Self& operator<< (__ios_fn __ff) { __ff(*this); return *this; }

private:
  bool _M_copy_buffered(basic_streambuf<_CharT, _Traits>* __from,
                        basic_streambuf<_CharT, _Traits>* __to);
  bool _M_copy_unbuffered(basic_streambuf<_CharT, _Traits>* __from,
                          basic_streambuf<_CharT, _Traits>* __to);

public:
  void _M_put_char(_CharT __c);

  void _M_put_nowiden(const _CharT* __s);
  void _M_put_widen(const char* __s);
  bool _M_put_widen_aux(const char* __s, streamsize __n);

public:                         // Unformatted output.
  _Self& put(char_type __c);
  _Self& write(const char_type* __s, streamsize __n);

public:                         // Formatted output.
  // Formatted output from a streambuf.
  _Self& operator<<(basic_streambuf<_CharT, _Traits>* __buf);

  _Self& operator<<(short __x) { return _M_put_num(*this,  __STATIC_CAST(long,__x)); }
  _Self& operator<<(unsigned short __x) { return _M_put_num(*this,  __STATIC_CAST(unsigned long,__x)); }
  _Self& operator<<(int __x) { return _M_put_num(*this,  __STATIC_CAST(long,__x)); }
  _Self& operator<<(unsigned int __x) { return _M_put_num(*this,  __STATIC_CAST(unsigned long,__x)); }
  _Self& operator<<(long __x) { return _M_put_num(*this,  __x); }
  _Self& operator<<(unsigned long __x) { return _M_put_num(*this,  __x); }
#ifdef __STL_LONG_LONG
  _Self& operator<< (long long __x)     { return _M_put_num(*this,  __x); }
  _Self& operator<< (unsigned long long __x) { return _M_put_num(*this,  __x); }
#endif 
  _Self& operator<<(float __x)
    { return _M_put_num(*this,  __STATIC_CAST(double,__x)); }
  _Self& operator<<(double __x) { return _M_put_num(*this,  __x); }
  _Self& operator<<(long double __x) { return _M_put_num(*this,  __x); }
  _Self& operator<<(const void* __x) { return _M_put_num(*this,  __x); }
# ifndef __STL_NO_BOOL
  _Self& operator<<(bool __x) { return _M_put_num(*this,  __x); }
# endif

#if  (defined(__MRC__)||defined(__SC__))		//*TY 03/05/2000 - added workaround for mpw compilers;they have difficulty finding appropriate operator if defined as member and non-member functions
basic_ostream<_CharT, _Traits>& 
operator<<( const _CharT* __s) {
  _M_put_nowiden(__s);
  return *this;
}
basic_ostream<_CharT, _Traits>& 
operator<<(_CharT __c) {
  _M_put_char(__c);
  return *this;
}
#endif		//*TY 03/05/2000 - 

public:                         // Buffer positioning and manipulation.
  _Self& flush() {
    if (this->rdbuf())
      if (this->rdbuf()->pubsync() == -1)
        this->setstate(ios_base::badbit);
    return *this;
  }

  pos_type tellp() {
    return this->rdbuf() && !this->fail()
      ? this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::out)
      : pos_type(-1);
  }

  _Self& seekp(pos_type __pos) {
    if (this->rdbuf() && !this->fail())
      this->rdbuf()->pubseekpos(__pos, ios_base::out);
    return *this;
  }

  _Self& seekp(off_type __off, ios_base::seekdir __dir) {
    if (this->rdbuf() && !this->fail())
      this->rdbuf()->pubseekoff(__off, __dir, ios_base::out);
    return *this;
  }

#if defined (__STL_USE_TEMPLATE_EXPORT)
  // If we are using DLL specs, we have not to use inner classes
  // end class declaration here
  typedef _Osentry<_CharT, _Traits>  sentry;
};
#  define sentry _Osentry
  template <class _CharT, class _Traits>
  class _Osentry {
    typedef _Osentry<_CharT, _Traits> _Self;
# else
    class sentry {
      typedef sentry _Self;
# endif
    private:
      basic_ostream<_CharT, _Traits>& _M_str;
      basic_streambuf<_CharT, _Traits>* _M_buf;
      bool _M_ok;
    public:
      explicit sentry(basic_ostream<_CharT, _Traits>& __str)
        : _M_str(__str), _M_buf(__str.rdbuf()), _M_ok(false)
      {
        if (_M_str.good()) {
          if (!_M_buf)
            _M_str.setstate(ios_base::badbit);
          if (_M_str.tie())
            _M_str.tie()->flush();
          _M_ok = _M_str.good();      
        }
      }
      
      ~sentry() {
        if (_M_str.flags() & ios_base::unitbuf)
# ifndef __STL_INCOMPLETE_EXCEPTION_HEADER 
          if (!__STL_VENDOR_EXCEPT_STD::uncaught_exception())
# endif
            _M_str.flush();
      }

      operator bool() const { return _M_ok; }
    private:                        // Disable assignment and copy constructor.
      sentry(const _Self& __s) : _M_str (__s._M_str) {};
      void operator=(const _Self&) {};
    };
# if defined (__STL_USE_TEMPLATE_EXPORT)
#  undef sentry
# else
  // close basic_istream class definition here    
};
# endif
  
# if defined (__STL_USE_TEMPLATE_EXPORT)
__STL_EXPORT_TEMPLATE_CLASS basic_ostream<char, char_traits<char> >;
__STL_EXPORT_TEMPLATE_CLASS _Osentry<char, char_traits<char> >;
#  if !defined (__STL_NO_WCHAR_T)
__STL_EXPORT_TEMPLATE_CLASS basic_ostream<wchar_t, char_traits<wchar_t> >;
__STL_EXPORT_TEMPLATE_CLASS _Osentry<wchar_t, char_traits<wchar_t> >;
#  endif
# endif /* __STL_USE_TEMPLATE_EXPORT */

// Non-member functions.
# if !(defined(__MRC__)||defined(__SC__))		//*TY 03/05/2000 - added workaround for mpw compilers;they have dif
template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& __STL_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os, _CharT __c) {
  __os._M_put_char(__c);
  return __os;
}
# endif
# ifndef __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER

// also for compilers who might use that
template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& __STL_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os, char __c) {
  __os._M_put_char(__os.widen(__c));
  return __os;
}

template <class _Traits>
inline basic_ostream<char, _Traits>& __STL_CALL
operator<<(basic_ostream<char, _Traits>& __os, char __c) {
  __os._M_put_char(__c);
  return __os;
}

template <class _Traits>
inline basic_ostream<char, _Traits>& __STL_CALL
operator<<(basic_ostream<char, _Traits>& __os, signed char __c) {
  __os._M_put_char(__c);
  return __os;
}

template <class _Traits>
inline basic_ostream<char, _Traits>& __STL_CALL
operator<<(basic_ostream<char, _Traits>& __os, unsigned char __c) {
  __os._M_put_char(__c);
  return __os;
}

# endif /* __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER */

#if !(defined(__MRC__)||defined(__SC__))
template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& __STL_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os, const _CharT* __s) {
  __os._M_put_nowiden(__s);
  return __os;
}
#endif

# ifndef __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER

template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& __STL_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os, const char* __s) {
  __os._M_put_widen(__s);
  return __os;
}

template <class _Traits>
inline basic_ostream<char, _Traits>& __STL_CALL
operator<<(basic_ostream<char, _Traits>& __os, const char* __s) {
  __os._M_put_nowiden(__s);
  return __os;
}

template <class _Traits>
inline basic_ostream<char, _Traits>& __STL_CALL
operator<<(basic_ostream<char, _Traits>& __os, const signed char* __s) {
  __os._M_put_nowiden(__REINTERPRET_CAST(const char*,__s));
  return __os;
}

template <class _Traits>
inline basic_ostream<char, _Traits>&
operator<<(basic_ostream<char, _Traits>& __os, const unsigned char* __s) {
  __os._M_put_nowiden(__REINTERPRET_CAST(const char*,__s));
  return __os;
}
# endif /* __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER */

//----------------------------------------------------------------------
// basic_ostream manipulators.

template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& __STL_CALL
endl(basic_ostream<_CharT, _Traits>& __os) {
  __os.put(__os.widen('\n'));
  __os.flush();
  return __os;
}

template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& __STL_CALL
ends(basic_ostream<_CharT, _Traits>& __os) {
  __os.put(__STL_DEFAULT_CONSTRUCTED(_CharT));
  return __os;
}

template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& __STL_CALL
flush(basic_ostream<_CharT, _Traits>& __os) {
  __os.flush();
  return __os;
}

__STL_END_NAMESPACE

#  undef __STL_MANIP_INLINE

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_ostream.c>
# endif

#endif /* __SGI_STL_OSTREAM_H */

// Local Variables:
// mode:C++
// End:
