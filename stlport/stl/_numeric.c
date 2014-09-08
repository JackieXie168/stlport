/*
 *
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
#ifndef __STL_NUMERIC_C
#define __STL_NUMERIC_C

# ifndef __STL_INTERNAL_FUNCTION_H
#  include <stl/_function.h>
# endif

#ifndef __SGI_STL_INTERNAL_ITERATOR_BASE_H
# include <stl/_iterator_base.h>
#endif

__STL_BEGIN_NAMESPACE

template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator 
__partial_sum(_InputIterator __first, _InputIterator __last,
              _OutputIterator __result, _Tp*)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    __value = __value + *__first;
    *++__result = __value;
  }
  return ++__result;
}

template <class _InputIterator, class _OutputIterator>
_OutputIterator 
partial_sum(_InputIterator __first, _InputIterator __last,
            _OutputIterator __result)
{
  __STL_DEBUG_CHECK(__check_range(__first, __last))
  if (__first == __last) return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first));
}

template <class _InputIterator, class _OutputIterator, class _Tp,
          class _BinaryOperation>
_OutputIterator 
__partial_sum(_InputIterator __first, _InputIterator __last, 
              _OutputIterator __result, _Tp*, _BinaryOperation __binary_op)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    __value = __binary_op(__value, *__first);
    *++__result = __value;
  }
  return ++__result;
}

template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator 
partial_sum(_InputIterator __first, _InputIterator __last,
            _OutputIterator __result, _BinaryOperation __binary_op)
{
  __STL_DEBUG_CHECK(__check_range(__first, __last))
  if (__first == __last) return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first), 
                       __binary_op);
}

template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator 
__adjacent_difference(_InputIterator __first, _InputIterator __last,
                      _OutputIterator __result, _Tp*)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    _Tp __tmp = *__first;
    *++__result = __tmp - __value;
    __value = __tmp;
  }
  return ++__result;
}

template <class _InputIterator, class _OutputIterator>
_OutputIterator
adjacent_difference(_InputIterator __first,
                    _InputIterator __last, _OutputIterator __result)
{
  __STL_DEBUG_CHECK(__check_range(__first, __last))
  if (__first == __last) return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result,
                               __VALUE_TYPE(__first));
}

template <class _InputIterator, class _OutputIterator, class _Tp, 
          class _BinaryOperation>
_OutputIterator
__adjacent_difference(_InputIterator __first, _InputIterator __last, 
                      _OutputIterator __result, _Tp*,
                      _BinaryOperation __binary_op) {
  _Tp __value = *__first;
  while (++__first != __last) {
    _Tp __tmp = *__first;
    *++__result = __binary_op(__tmp, __value);
    __value = __tmp;
  }
  return ++__result;
}

template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator 
adjacent_difference(_InputIterator __first, _InputIterator __last,
                    _OutputIterator __result, _BinaryOperation __binary_op)
{
  __STL_DEBUG_CHECK(__check_range(__first, __last))
  if (__first == __last) return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result,
                               __VALUE_TYPE(__first),
                               __binary_op);
}

template <class _Tp, class _Integer, class _MonoidOperation>
_Tp __power(_Tp __x, _Integer __n, _MonoidOperation __opr) 
{
  __STL_MPWFIX_TRY		//*TY 06/01/2000 - mpw forgets to call dtor on __x when exception is thrown inside this func
  if (__n == 0)
    return identity_element(__opr);
  else {
    //    _Tp __x = __mx;    
    while ((__n & 1) == 0) {
      __n >>= 1;
      __x = __opr(__x, __x);
    }

    _Tp __result = __x;
	__STL_MPWFIX_TRY		//*TY 06/01/2000 - 
    __n >>= 1;
    while (__n != 0) {
      __x = __opr(__x, __x);
      if ((__n & 1) != 0)
        __result = __opr(__result, __x);
      __n >>= 1;
    }
    return __result;
	__STL_MPWFIX_CATCH		//*TY 06/01/2000 - 
  }
	__STL_MPWFIX_CATCH_ACTION(__x = _Tp())		//*TY 06/01/2000 - explicitly reset __x; power() called from rope(size_t , _CharT , const allocator_type& ):
}

template <class _Tp, class _Integer, class _MonoidOperation>
_Tp power(_Tp __x, _Integer __n, _MonoidOperation __opr)
{
  return __power(__x, __n, __opr);
}

template <class _Tp, class _Integer>
_Tp power(_Tp __x, _Integer __n)
{
  return __power(__x, __n);
}

__STL_END_NAMESPACE

#endif /*  __STL_NUMERIC_C */

// Local Variables:
// mode:C++
// End:
