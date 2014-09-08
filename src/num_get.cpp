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
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cfloat>

#include <iterator>
#include <locale>
#include <limits>
#include <ostream>

__STL_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// num_get

// Helper functions for _M_do_get_integer.

void  __STL_CALL
__initialize_get_digit(wchar_t* digits, wchar_t* xdigits,
                       const ctype<wchar_t>& ct)
{
  char narrow_digits[11]  = "0123456789";
  char narrow_xdigits[13] = "aAbBcCdDeEfF";

  ct.widen(narrow_digits + 0,  narrow_digits + 10,  digits);
  ct.widen(narrow_xdigits + 0, narrow_xdigits + 10, xdigits);
}

// Return either the digit corresponding to c, or a negative number if
// if c isn't a digit.  We return -1 if c is the separator character, and
// -2 if it's some other non-digit.
int __get_digit(wchar_t c,
                const wchar_t* digits, const wchar_t* xdigits,
                wchar_t separator)
{
  // Test if it's the separator.
  if (c == separator)
    return -1;

  const wchar_t* p;

  // Test if it's a decimal digit.
  p = find(digits, digits + 10, c);
  if (p != digits + 10)
    return p - digits;

  // Test if it's a hex digit.
  p = find(xdigits, xdigits + 12, c);
  if (p != xdigits + 12)
    return 10 + (xdigits - p) / 2;
  else
    return -2;                  // It's not a digit and not the separator.
}

// __valid_grouping compares two strings, one representing the
// group sizes encountered when reading an integer, and the other
// representing the valid group sizes as returned by the numpunct
// grouping() member function.  Both are interpreted right-to-left.
// The grouping string is treated as if it were extended indefinitely
// with its last value.  For a grouping to be valid, each term in
// the first string must be equal to the corresponding term in the
// second, except for the last, which must be less than or equal.

bool  __STL_CALL
__valid_grouping(const string& group_sizes,
                 const string& prescribed_grouping)
{
  const char * first1 = group_sizes.data();
  const char * last1  = first1 + group_sizes.size();
  const char * first2 = prescribed_grouping.data();
  const char * last2  = first2 + prescribed_grouping.size();

  if (first1 == last1 || first2 == last2) return true;

  --last1; --last2;

  while (first1 != last1) {
    if (*first1 != *first2)
      return false;
    ++first1;
    if (first2 != last2) ++first2;
  }
  return *first1 <= *first2;
}


const unsigned char __digit_val_table[128] = 
{
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,10,11,12,13,14,15,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,10,11,12,13,14,15,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};     

const char __narrow_atoms[5] = {'+', '-', '0', 'x', 'X'};

// index is actually a char


__STL_END_NAMESPACE

// Local Variables:
// mode:C++
// End:


