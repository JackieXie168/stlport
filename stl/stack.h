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

#ifndef __SGI_STL_STACK_H
#define __SGI_STL_STACK_H

#include <vector.h>
#include <deque.h>
#include <heap.h>
#include <stl_stack.h>
#include <stl_queue.h>

#ifdef __STL_USE_NAMESPACES
# ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STD;
# else
using __STD::stack;
using __STD::queue;
using __STD::priority_queue;
# endif
#endif /* __STL_USE_NAMESPACES */

#endif /* __SGI_STL_STACK_H */

// Local Variables:
// mode:C++
// End:
