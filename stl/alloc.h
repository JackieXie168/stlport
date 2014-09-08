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

#ifndef __SGI_STL_ALLOC_H
#define __SGI_STL_ALLOC_H

#ifndef __STL_CONFIG_H
#include <stl_config.h>
#endif
#ifndef __SGI_STL_INTERNAL_ALLOC_H
#include <stl_alloc.h>
#endif

#ifdef __STL_USE_NAMESPACES
# ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STD;
# else
using __STD::__malloc_alloc; 
using __STD::malloc_alloc; 
using __STD::simple_alloc; 
using __STD::debug_alloc; 
# if !(defined (__STL_USE_MALLOC) || defined (__STL_USE_NEWALLOC))
using __STD::__default_alloc_template; 
# endif
using __STD::alloc; 
using __STD::single_client_alloc; 
using __STD::__new_alloc;
#ifdef __STL_USE_STD_ALLOCATORS 
 using __STD::allocator;
#endif /* __STL_USE_STD_ALLOCATORS */

# endif /* __STL_BROKEN_USING_DIRECTIVE */
#endif /* __STL_USE_NAMESPACES */

#endif /* __SGI_STL_ALLOC_H */

// Local Variables:
// mode:C++
// End:
