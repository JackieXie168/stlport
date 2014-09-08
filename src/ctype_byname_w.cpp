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
# include "stlport_prefix.h"
#include <string>
#include <stl/_locale.h>
#include <stl/_ctype.h>
#include <stl/_threads.h>

__STL_BEGIN_NAMESPACE

_Locale_ctype* __acquire_ctype(const char* name); 
void __release_ctype(_Locale_ctype* cat);

// ctype_byname<wchar_t>

# ifndef __STL_NO_WCHAR_T

  struct _Ctype_byname_w_is_mask {
    typedef wchar_t argument_type;
    typedef bool    result_type;

    /* ctype_base::mask*/ int  M;
    _Locale_ctype* M_ctp;

    _Ctype_byname_w_is_mask(/* ctype_base::mask */ int m, _Locale_ctype* c) : M((int)m), M_ctp(c) {}
    bool operator()(wchar_t c) const
      { return (M & _Locale_wchar_ctype(M_ctp, c)) != 0; }
  };

ctype_byname<wchar_t>::ctype_byname(const char* name, size_t refs)
  : ctype<wchar_t>(refs),
    _M_ctype(__acquire_ctype(name))
{
  if (!_M_ctype)
    locale::_M_throw_runtime_error();    
}

ctype_byname<wchar_t>::~ctype_byname()
{
  __release_ctype(_M_ctype);
}

bool ctype_byname<wchar_t>::do_is(mask m, wchar_t c) const
{
  return (m & _Locale_wchar_ctype(_M_ctype, c)) != 0;
}

const wchar_t*
ctype_byname<wchar_t>::do_is(const wchar_t* low, const wchar_t* high,
                             mask* m) const
{
  for ( ; low < high; ++low, ++m)
    *m = mask(_Locale_wchar_ctype(_M_ctype, *low));
  return high;
}

    
const wchar_t*
ctype_byname<wchar_t>
  ::do_scan_is(mask m, const wchar_t* low, const wchar_t* high) const
{
  return find_if(low, high, _Ctype_byname_w_is_mask(m, _M_ctype));
}

const wchar_t*
ctype_byname<wchar_t>
  ::do_scan_not(mask m, const wchar_t* low, const wchar_t* high) const
{
  return find_if(low, high, not1(_Ctype_byname_w_is_mask(m, _M_ctype)));
}

wchar_t ctype_byname<wchar_t>::do_toupper(wchar_t c) const 
{
  return _Locale_wchar_toupper(_M_ctype, c);
}

const wchar_t* 
ctype_byname<wchar_t>::do_toupper(wchar_t* low, const wchar_t* high) const
{
  for ( ; low < high; ++low)
    *low = _Locale_wchar_toupper(_M_ctype, *low);
  return high;
}

wchar_t ctype_byname<wchar_t>::do_tolower(wchar_t c) const 
{
  return _Locale_wchar_tolower(_M_ctype, c);
}

const wchar_t* 
ctype_byname<wchar_t>::do_tolower(wchar_t* low, const wchar_t* high) const
{
  for ( ; low < high; ++low)
    *low = _Locale_wchar_tolower(_M_ctype, *low);
  return high;
}

# endif /* WCHAR_T */

__STL_END_NAMESPACE

// Local Variables:
// mode:C++
// End:

