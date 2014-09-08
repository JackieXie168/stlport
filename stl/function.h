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

#ifndef __SGI_STL_FUNCTION_H
#define __SGI_STL_FUNCTION_H

#ifndef __STL_CONFIG_H
#include <stl_config.h>
#endif
#ifdef __STL_USE_NEW_STYLE_HEADERS
# include <cstddef>
#else
# include <stddef.h>
#endif

#include <stl_relops.h>

#ifndef __SGI_STL_INTERNAL_FUNCTION_H
#include <stl_function.h>
#endif

#ifdef __STL_USE_NAMESPACES

# ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STD;

# else /* __STL_BROKEN_USING_DIRECTIVE */

#  if 0 // def __STL_USE_NAMESPACE_FOR_RELOPS
// Names from stl_relops.h
using __STD_RELOPS::operator!=;
using __STD_RELOPS::operator>;
using __STD_RELOPS::operator<=;
using __STD_RELOPS::operator>=;
#  endif /* __STL_USE_NAMESPACE_FOR_RELOPS */

// Names from stl_function.h
using __STD::unary_function; 
using __STD::binary_function; 
using __STD::plus; 
using __STD::minus; 
using __STD::multiplies; 
using __STD::divides; 
using __STD::identity_element; 
using __STD::modulus; 
using __STD::negate; 
using __STD::equal_to; 
using __STD::not_equal_to; 
using __STD::greater; 
using __STD::less; 
using __STD::greater_equal; 
using __STD::less_equal; 
using __STD::logical_and; 
using __STD::logical_or; 
using __STD::logical_not; 
using __STD::unary_negate; 
using __STD::binary_negate; 
using __STD::not1; 
using __STD::not2; 
using __STD::binder1st; 
using __STD::binder2nd; 
using __STD::bind1st; 
using __STD::bind2nd; 
using __STD::unary_compose; 
using __STD::binary_compose; 
using __STD::compose1; 
using __STD::compose2; 
using __STD::pointer_to_unary_function; 
using __STD::pointer_to_binary_function; 
using __STD::ptr_fun; 
using __STD::identity; 
using __STD::select1st; 
using __STD::select2nd; 
using __STD::project1st; 
using __STD::project2nd; 
using __STD::constant_void_fun; 
using __STD::constant_unary_fun; 
using __STD::constant_binary_fun; 
using __STD::constant0; 
using __STD::constant1; 
using __STD::constant2; 
using __STD::subtractive_rng; 
using __STD::mem_fun_t; 
using __STD::const_mem_fun_t; 
using __STD::mem_fun_ref_t; 
using __STD::const_mem_fun_ref_t; 
using __STD::mem_fun1_t; 
using __STD::const_mem_fun1_t; 
using __STD::mem_fun1_ref_t; 
using __STD::const_mem_fun1_ref_t; 
using __STD::mem_fun; 
using __STD::mem_fun_ref; 
using __STD::mem_fun1; 
using __STD::mem_fun1_ref; 
# endif
#endif /* __STL_USE_NAMESPACES */

#endif /* __SGI_STL_FUNCTION_H */

// Local Variables:
// mode:C++
// End:
