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

#include <iterator>
#include <cstring>
#include <cstdlib>

#include <locale>
#include <algorithm> // for copy

__STL_BEGIN_NAMESPACE

void __init_monetary_formats(money_base::pattern& pos_format,
                             money_base::pattern& neg_format);

# ifndef __STL_NO_WCHAR_T

moneypunct<wchar_t, true>::moneypunct(size_t refs)
#if !(defined(__MRC__) || defined(__SC__) )		//*TY 04/29/2000 - added workaround for mpw
  : locale::facet(refs)
#else					//*TY 04/29/2000 - 
  : _facet(refs)		//*TY 04/29/2000 - they forget to look into the nested class for the ctor
#endif					//*TY 04/29/2000 - 
{
  __init_monetary_formats(_M_pos_format, _M_neg_format);
}

moneypunct<wchar_t, true>::~moneypunct()  {}

wchar_t moneypunct<wchar_t, true>::do_decimal_point() const {return L' ';}
wchar_t moneypunct<wchar_t, true>::do_thousands_sep() const {return L' ';}
string moneypunct<wchar_t, true>::do_grouping() const {return "";}

wstring moneypunct<wchar_t, true>::do_curr_symbol() const
  {return L"";}
wstring moneypunct<wchar_t, true>::do_positive_sign() const
  {return L"";}
wstring moneypunct<wchar_t, true>::do_negative_sign() const
  {return L"";}
int moneypunct<wchar_t, true>::do_frac_digits() const {return 0;}
money_base::pattern moneypunct<wchar_t, true>::do_pos_format() const
  {return _M_pos_format;}
money_base::pattern moneypunct<wchar_t, true>::do_neg_format() const
  {return _M_neg_format;}

moneypunct<wchar_t, false>::moneypunct(size_t refs)
#if !(defined(__MRC__) || defined(__SC__) )		//*TY 04/29/2000 - added workaround for mpw
  : locale::facet(refs)
#else					//*TY 04/29/2000 - 
  : _facet(refs)		//*TY 04/29/2000 - they forget to look into the nested class for the ctor
#endif					//*TY 04/29/2000 - 
{
  __init_monetary_formats(_M_pos_format, _M_neg_format);
}

moneypunct<wchar_t, false>::~moneypunct() {}

wchar_t moneypunct<wchar_t, false>::do_decimal_point() const {return L' ';}
wchar_t moneypunct<wchar_t, false>::do_thousands_sep() const {return L' ';}
string moneypunct<wchar_t, false>::do_grouping() const {return "";}
wstring moneypunct<wchar_t, false>::do_curr_symbol() const
  {return L"";}
wstring moneypunct<wchar_t, false>::do_positive_sign() const
  {return L"";}
wstring moneypunct<wchar_t, false>::do_negative_sign() const
  {return L"";}
int moneypunct<wchar_t, false>::do_frac_digits() const {return 0;}

money_base::pattern moneypunct<wchar_t, false>::do_pos_format() const
  {return _M_pos_format;}
money_base::pattern moneypunct<wchar_t, false>::do_neg_format() const
  {return _M_neg_format;}

# endif /* WCHAR_T */

__STL_END_NAMESPACE  

// Local Variables:
// mode:C++
// End:
