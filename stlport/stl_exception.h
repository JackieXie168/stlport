/*
 * Copyright (c) 1996,1997
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

#ifndef __SGI_STL_EXCEPTION_H
#define __SGI_STL_EXCEPTION_H

// This header exists solely for portability.  Normally it just includes
// the header <exception>.

// The header <exception> contains low-level functions that interact
// with a compiler's exception-handling mechanism.  It is assumed to
// be supplied with the compiler, rather than with the library, because
// it is inherently tied very closely to the compiler itself.

// On platforms where <exception> does not exist, this header defines
// an exception base class.  This is *not* a substitute for everything
// in <exception>, but it suffices to support a bare minimum of STL
// functionality.


#ifndef __STL_NO_EXCEPTION_HEADER

#include <exception>
#define __STL_EXCEPTION_BASE __STL_VENDOR_STD::exception

#  ifdef __STL_USE_OWN_NAMESPACE
__STL_BEGIN_NAMESPACE
using __STL_VENDOR_STD::exception;
__STL_END_NAMESPACE
#  endif /* __STL_OWN_NAMESPACE */

#else /* __STL_NO_EXCEPTION_HEADER */

__STL_BEGIN_NAMESPACE

class _Exception {
public:
  virtual ~_Exception() __STL_NOTHROW {}
  virtual const char* what() const __STL_NOTHROW { return ""; }
};

#define __STL_EXCEPTION_BASE _Exception

__STL_END_NAMESPACE

#endif /* __STL_NO_EXCEPTION_HEADER */

#endif /* __SGI_STL_EXCEPTION_H */

// Local Variables:
// mode:C++
// End:
