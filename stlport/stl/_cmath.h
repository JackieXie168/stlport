/*
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

#ifndef _STLP_CMATH_H_HEADER
#define _STLP_CMATH_H_HEADER

#include <cmath>

_STLP_BEGIN_NAMESPACE

#ifdef _STLP_SAME_FUNCTION_NAME_RESOLUTION_BUG

// this proxy is needed for some compilers to resolve problems
// calling sqrt() from within sqrt(), etc.
template <class _Tp>
struct _STL_math_proxy {
  static inline _Tp _do_abs(const _Tp& __x)     { return _STLP_VENDOR_CSTD::fabs(__x); } 
  static inline _Tp _do_acos(const _Tp& __x)    { return _STLP_VENDOR_CSTD::acos(__x); } 
  static inline _Tp _do_asin(const _Tp& __x)    { return _STLP_VENDOR_CSTD::asin(__x); } 
  static inline _Tp _do_atan(const _Tp& __x)    { return _STLP_VENDOR_CSTD::atan(__x); } 
  static inline _Tp _do_atan2(const _Tp& __x, const _Tp& __y)  { return _STLP_VENDOR_CSTD::atan2(__x, __y); } 
  static inline _Tp _do_cos(const _Tp& __x)     { return _STLP_VENDOR_CSTD::cos(__x); } 
  static inline _Tp _do_cosh(const _Tp& __x)    { return _STLP_VENDOR_CSTD::cosh(__x); } 
  static inline _Tp _do_floor(const _Tp& __x)    { return _STLP_VENDOR_CSTD::floor(__x); } 
  static inline _Tp _do_ceil(const _Tp& __x)    { return _STLP_VENDOR_CSTD::ceil(__x); } 
  static inline _Tp _do_fmod(const _Tp& __x, const _Tp& __y)    { return _STLP_VENDOR_CSTD::fmod(__x, __y); } 
  static inline _Tp _do_frexp(const _Tp& __x, int* __y)    { return _STLP_VENDOR_CSTD::frexp(__x, __y); } 
  static inline _Tp _do_ldexp(const _Tp& __x, int __y)    { return _STLP_VENDOR_CSTD::ldexp(__x, __y); } 
  static inline _Tp _do_modf(const _Tp& __x, double* __y) { return _STLP_VENDOR_CSTD::modf(__x, __y); }
  static inline _Tp _do_log(const _Tp& __x)     { return _STLP_VENDOR_CSTD::log(__x); } 
  static inline _Tp _do_log10(const _Tp& __x)   { return _STLP_VENDOR_CSTD::log10(__x); } 
  static inline _Tp _do_pow(const _Tp& __x, const _Tp& __y)    { return _STLP_VENDOR_CSTD::pow(__x, __y); } 
  static inline _Tp _do_pow(const _Tp& __x, int __y)    { return _STLP_VENDOR_CSTD::pow(__x, __y); } 
  static inline _Tp _do_sin(const _Tp& __x)     { return _STLP_VENDOR_CSTD::sin(__x); } 
  static inline _Tp _do_sinh(const _Tp& __x)    { return _STLP_VENDOR_CSTD::sinh(__x); } 

  static inline _Tp _do_sqrt(const _Tp& __x)    { return _STLP_VENDOR_CSTD::sqrt(__x); } 
  static inline _Tp _do_tan(const _Tp& __x)     { return _STLP_VENDOR_CSTD::tan(__x); } 
  static inline _Tp _do_tanh(const _Tp& __x)    { return _STLP_VENDOR_CSTD::tanh(__x); } 
  static inline _Tp _do_exp(const _Tp& __x)     { return _STLP_VENDOR_CSTD::exp(__x); } 
#  ifdef _STLP_WCE
  static inline _Tp _do_hypot(const _Tp& __x, const _Tp& __y)   { return _STLP_VENDOR_CSTD::sqrt(__x * __x + __y * __y); } 
#  else  
  static inline _Tp _do_hypot(const _Tp& __x, const _Tp& __y)   { return _STLP_VENDOR_CSTD::hypot(__x, __y); } 
#  endif
};

#  define _STLP_DO_ABS(_Tp)   _STL_math_proxy<_Tp>::_do_abs
#  define _STLP_DO_ACOS(_Tp)  _STL_math_proxy<_Tp>::_do_acos
#  define _STLP_DO_ASIN(_Tp)  _STL_math_proxy<_Tp>::_do_asin
#  define _STLP_DO_ATAN(_Tp)  _STL_math_proxy<_Tp>::_do_atan
#  define _STLP_DO_ATAN2(_Tp) _STL_math_proxy<_Tp>::_do_atan2
#  define _STLP_DO_COS(_Tp)   _STL_math_proxy<_Tp>::_do_cos
#  define _STLP_DO_COSH(_Tp)  _STL_math_proxy<_Tp>::_do_cosh
#  define _STLP_DO_FLOOR(_Tp) _STL_math_proxy<_Tp>::_do_floor
#  define _STLP_DO_CEIL(_Tp) _STL_math_proxy<_Tp>::_do_ceil
#  define _STLP_DO_FMOD(_Tp) _STL_math_proxy<_Tp>::_do_fmod
#  define _STLP_DO_FREXP(_Tp) _STL_math_proxy<_Tp>::_do_frexp
#  define _STLP_DO_LDEXP(_Tp) _STL_math_proxy<_Tp>::_do_ldexp
#  define _STLP_DO_MODF(_Tp) _STL_math_proxy<_Tp>::_do_modf
#  define _STLP_DO_LOG(_Tp)   _STL_math_proxy<_Tp>::_do_log
#  define _STLP_DO_LOG10(_Tp) _STL_math_proxy<_Tp>::_do_log10
#  define _STLP_DO_POW(_Tp)   _STL_math_proxy<_Tp>::_do_pow
#  define _STLP_DO_SIN(_Tp)   _STL_math_proxy<_Tp>::_do_sin
#  define _STLP_DO_SINH(_Tp)  _STL_math_proxy<_Tp>::_do_sinh
#  define _STLP_DO_SQRT(_Tp)  _STL_math_proxy<_Tp>::_do_sqrt
#  define _STLP_DO_TAN(_Tp)   _STL_math_proxy<_Tp>::_do_tan
#  define _STLP_DO_TANH(_Tp)  _STL_math_proxy<_Tp>::_do_tanh
#  define _STLP_DO_EXP(_Tp)   _STL_math_proxy<_Tp>::_do_exp
#  define _STLP_DO_HYPOT(_Tp) _STL_math_proxy<_Tp>::_do_hypot

#else /* _STLP_SAME_FUNCTION_NAME_RESOLUTION_BUG */

#  define _STLP_DO_ABS(_Tp)   _STLP_VENDOR_CSTD::fabs
#  define _STLP_DO_ACOS(_Tp)  _STLP_VENDOR_CSTD::acos
#  define _STLP_DO_ASIN(_Tp)  _STLP_VENDOR_CSTD::asin
#  define _STLP_DO_ATAN(_Tp)  _STLP_VENDOR_CSTD::atan
#  define _STLP_DO_ATAN2(_Tp) _STLP_VENDOR_CSTD::atan2
#  define _STLP_DO_COS(_Tp)   _STLP_VENDOR_CSTD::cos
#  define _STLP_DO_COSH(_Tp)  _STLP_VENDOR_CSTD::cosh
#  define _STLP_DO_FLOOR(_Tp)  _STLP_VENDOR_CSTD::floor
#  define _STLP_DO_CEIL(_Tp)   _STLP_VENDOR_CSTD::ceil
#  define _STLP_DO_FMOD(_Tp)   _STLP_VENDOR_CSTD::fmod
#  define _STLP_DO_FREXP(_Tp) _STLP_VENDOR_CSTD::frexp
#  define _STLP_DO_LDEXP(_Tp) _STLP_VENDOR_CSTD::ldexp
#  define _STLP_DO_MODF(_Tp) _STLP_VENDOR_CSTD::modf
#  define _STLP_DO_LOG(_Tp)   _STLP_VENDOR_CSTD::log
#  define _STLP_DO_LOG10(_Tp) _STLP_VENDOR_CSTD::log10
#  define _STLP_DO_POW(_Tp)   _STLP_VENDOR_CSTD::pow
#  define _STLP_DO_SIN(_Tp)   _STLP_VENDOR_CSTD::sin
#  define _STLP_DO_SINH(_Tp)  _STLP_VENDOR_CSTD::sinh
#  define _STLP_DO_SQRT(_Tp)  _STLP_VENDOR_CSTD::sqrt
#  define _STLP_DO_TAN(_Tp)   _STLP_VENDOR_CSTD::tan
#  define _STLP_DO_TANH(_Tp)  _STLP_VENDOR_CSTD::tanh
#  define _STLP_DO_EXP(_Tp)   _STLP_VENDOR_CSTD::exp
//# if defined (__GNUC__) || defined ( __IBMCPP__ ) || defined (__SUNPRO_CC) || defined (__HP_aCC) || (_MSC_VER >= 1310)
#  define _STLP_DO_HYPOT(_Tp) ::hypot
// # else
// #  define _STLP_DO_HYPOT(_Tp) _STLP_VENDOR_CSTD::hypot
// # endif

#endif /* _STLP_SAME_FUNCTION_NAME_RESOLUTION_BUG */

_STLP_END_NAMESPACE

#if (defined (_STLP_HAS_NO_NEW_C_HEADERS) || defined(_STLP_MSVC) || defined (__ICL)) && !defined (_STLP_HAS_NO_NAMESPACES)

#  if !defined (_STLP_USE_NEW_C_HEADERS) 

_STLP_BEGIN_NAMESPACE
#    if defined (_STLP_WCE)
#      pragma warning(push)
#      pragma warning(disable: 4162 4163) // "no function with C linkage found", "not available as an intrinsic function"
#      pragma function (abs, acos, asin, atan, atan2, cos, cosh, exp, fabs, fmod, log, log10, sin, sinh, sqrt, tan, tanh, ceil, floor)
#    endif

#    if !defined (_STLP_HAS_NATIVE_FLOAT_ABS) || defined (_STLP_WCE)
inline double abs(double __x)                 { return _STLP_DO_ABS(double)(__x); }
inline float abs (float __x)                  { return _STLP_DO_ABS(float)(__x); }
#    endif

inline double pow(double __x, int __y)        { return _STLP_DO_POW(double)(__x, __y); }
inline float acos (float __x)                 { return _STLP_DO_ACOS(float)(__x); }
inline float asin (float __x)                 { return _STLP_DO_ASIN(float)(__x); }
inline float atan (float __x)                 { return _STLP_DO_ATAN(float)(__x); }
inline float atan2(float __x, float __y)      { return _STLP_DO_ATAN2(float)(__x, __y); }
inline float ceil (float __x)                 { return _STLP_DO_CEIL(float)(__x); }
inline float cos (float __x)                  { return _STLP_DO_COS(float)(__x); }
inline float cosh (float __x)                 { return _STLP_DO_COSH(float)(__x); }
inline float exp (float __x)                  { return _STLP_DO_EXP(float)(__x); }
#    ifdef _STLP_USE_NAMESPACES
inline float fabs (float __x)                 { return _STLP_DO_ABS(float)(__x); }
#    endif
inline float floor(float __x)                 { return _STLP_DO_FLOOR(float)(__x); }
inline float fmod (float __x, float __y)      { return _STLP_DO_FMOD(float)(__x, __y); }
inline float frexp(float __x, int* __y)       { return _STLP_DO_FREXP(float)(__x, __y); }
inline float ldexp(float __x, int __y)        { return _STLP_DO_LDEXP(float)(__x, __y); }
// fbp : float versions are not always available
#    if !defined(_STLP_VENDOR_LONG_DOUBLE_MATH)  //*ty 11/25/2001 - 
inline float modf (float __x, float* __y)     { 
  double __dd[2]; 
  double __res = _STLP_DO_MODF(double)((double)__x, __dd); 
  __y[0] = (float)__dd[0] ; __y[1] = (float)__dd[1]; 
  return (float)__res; 
}
#    else  //*ty 11/25/2001 - i.e. for apple SCpp
inline float modf (float __x, float* __y)     { 
  long double __dd[2]; 
  long double __res = _STLP_DO_MODF(long double)((long double)__x, __dd); 
  __y[0] = (float)__dd[0] ; __y[1] = (float)__dd[1]; 
  return (float)__res; 
}
#    endif  //*ty 11/25/2001 - 

inline float log (float __x)                  { return _STLP_DO_LOG(float)(__x); }
inline float log10(float __x)                 { return _STLP_DO_LOG10(float)(__x); }
inline float pow (float __x, float __y)       { return _STLP_DO_POW(float)(__x, __y); }
inline float pow (float __x, int __y)         { return _STLP_DO_POW(float)(__x, __y); }
inline float sin (float __x)                  { return _STLP_DO_SIN(float)(__x); }
inline float sinh (float __x)                 { return _STLP_DO_SINH(float)(__x); }
inline float sqrt (float __x)                 { return _STLP_DO_SQRT(float)(__x); }
inline float tan (float __x)                  { return _STLP_DO_TAN(float)(__x); }
inline float tanh (float __x)                 { return _STLP_DO_TANH(float)(__x); }

#    if !(defined  (_STLP_NO_LONG_DOUBLE) || defined (_STLP_VENDOR_LONG_DOUBLE_MATH))

#      if !defined (__MVS__)
inline long double abs (long double __x)                  { return _STLP_DO_ABS(long double)((double)__x); }
#      endif
inline long double acos (long double __x)                 { return _STLP_DO_ACOS(long double)(__x); }
inline long double asin (long double __x)                 { return _STLP_DO_ASIN(long double)(__x); }
inline long double atan (long double __x)                 { return _STLP_DO_ATAN(long double)(__x); }
inline long double atan2(long double __x, long double __y)      { return _STLP_DO_ATAN2(long double)(__x, __y); }
inline long double ceil (long double __x)                 { return _STLP_DO_CEIL(long double)(__x); }
inline long double cos (long double __x)                  { return _STLP_DO_COS(long double)(__x); }
inline long double cosh (long double __x)                 { return _STLP_DO_COSH(long double)(__x); }
inline long double exp (long double __x)                  { return _STLP_DO_EXP(long double)(__x); }
inline long double fabs (long double __x)                 { return _STLP_DO_ABS(long double)(__x); }
inline long double floor(long double __x)                 { return _STLP_DO_FLOOR(long double)(__x); }
inline long double fmod (long double __x, long double __y)      { return _STLP_DO_FMOD(long double)(__x, __y); }
inline long double frexp(long double __x, int* __y)       { return _STLP_DO_FREXP(long double)(__x, __y); }
inline long double ldexp(long double __x, int __y)        { return _STLP_DO_LDEXP(long double)(__x, __y); }
// fbp : long double versions are not available
inline long double modf (long double __x, long double* __y)     { 
  double __dd[2]; 
  double __res = _STLP_DO_MODF(double)((double)__x, __dd); 
  __y[0] = (long double)__dd[0] ; __y[1] = (long double)__dd[1]; 
  return (long double)__res; 
}
inline long double log (long double __x)                  { return _STLP_DO_LOG(long double)(__x); }
inline long double log10(long double __x)                 { return _STLP_DO_LOG10(long double)(__x); }
inline long double pow (long double __x, long double __y)       { return _STLP_DO_POW(long double)(__x, __y); }
inline long double pow (long double __x, int __y)         { return _STLP_DO_POW(long double)(__x, __y); }
inline long double sin (long double __x)                  { return _STLP_DO_SIN(long double)(__x); }
inline long double sinh (long double __x)                 { return _STLP_DO_SINH(long double)(__x); }
inline long double sqrt (long double __x)                 { return _STLP_DO_SQRT(long double)(__x); }
inline long double tan (long double __x)                  { return _STLP_DO_TAN(long double)(__x); }
inline long double tanh (long double __x)                 { return _STLP_DO_TANH(long double)(__x); }

#    endif /* ! _STLP_NO_LONG_DOUBLE || _STLP_VENDOR_LONG_DOUBLE_MATH */

#    ifdef _STLP_WCE
#      pragma intrinsic (abs, acos, asin, atan, atan2, cos, cosh, exp, fabs, fmod, log, log10, sin, sinh, sqrt, tan, tanh, ceil, floor)
#      pragma warning(default: 4162)
#      pragma warning(pop)
#    endif

_STLP_END_NAMESPACE

#  endif /* _STLP_USE_NEW_C_HEADERS */

#  if defined (_STLP_MSVC) && (_STLP_MSVC <= 1300) && !defined(_STLP_WCE)
_STLP_BEGIN_NAMESPACE

#    if defined (_MSC_EXTENSIONS) /* && !defined(_STLP_WCE_NET) */
/*
 * dums: VC6 has all the required C++ functions but only define them if
 * _MSC_EXTENSIONS is not defined (a bug?). STLport just do the same
 * thing also when _MSC_EXTENSIONS is defined.
 */
//We have to tell the compilers that abs, acos ... math functions are not intrinsic
//otherwise we have Internal Compiler Error in release mode...
#pragma warning(push)
#pragma warning(disable: 4162) // "no function with C linkage found"
#pragma function (abs, acos, asin, atan, atan2, cos, cosh, exp, fabs, fmod, log, log10, sin, sinh, sqrt, tan, tanh)
inline double abs(double __x) {return (fabs(__x)); }
inline float abs(float __x) {return (fabsf(__x)); }
inline float acos(float __x) {return (acosf(__x)); }
inline float asin(float __x) {return (asinf(__x)); }
inline float atan(float __x) {return (atanf(__x)); }
inline float atan2(float __y, float __x) {return (atan2f(__y, __x)); }
inline float ceil(float __x) {return (ceilf(__x)); }
inline float cos(float __x) {return (cosf(__x)); }
inline float cosh(float __x) {return (coshf(__x)); }
inline float exp(float __x) {return (expf(__x)); }
inline float fabs(float __x) {return (fabsf(__x)); }
inline float floor(float __x) {return (floorf(__x)); }
inline float fmod(float __x, float __y) {return (fmodf(__x, __y)); }
inline float frexp(float __x, int * __y) {return (frexpf(__x, __y)); }
inline float ldexp(float __x, int __y) {return (ldexpf(__x, __y)); }
inline float log(float __x) {return (logf(__x)); }
inline float log10(float __x) {return (log10f(__x)); }
inline float modf(float __x, float * __y) {return (modff(__x, __y)); }
inline float sin(float __x) {return (sinf(__x)); }
inline float sinh(float __x) {return (sinhf(__x)); }
inline float sqrt(float __x) {return (sqrtf(__x)); }
inline float tan(float __x) {return (tanf(__x)); }
inline float tanh(float __x) {return (tanhf(__x)); }
inline long double abs(long double __x) {return (fabsl(__x)); }
inline long double acos(long double __x) {return (acosl(__x)); }
inline long double asin(long double __x) {return (asinl(__x)); }
inline long double atan(long double __x) {return (atanl(__x)); }
inline long double atan2(long double __y, long double __x) {return (atan2l(__y, __x)); }
inline long double ceil(long double __x) {return (ceill(__x)); }
inline long double cos(long double __x) {return (cosl(__x)); }
inline long double cosh(long double __x) {return (coshl(__x)); }
inline long double exp(long double __x) {return (expl(__x)); }
inline long double fabs(long double __x) {return (fabsl(__x)); }
inline long double floor(long double __x) {return (floorl(__x)); }
inline long double fmod(long double __x, long double __y) {return (fmodl(__x, __y)); }
inline long double frexp(long double __x, int * __y) {return (frexpl(__x, __y)); }
inline long double ldexp(long double __x, int __y) {return (ldexpl(__x, __y)); }
inline long double log(long double __x) {return (logl(__x)); }
inline long double log10(long double __x) {return (log10l(__x)); }
inline long double modf(long double __x, long double * __y) {return (modfl(__x, __y)); }
inline long double sin(long double __x) {return (sinl(__x)); }
inline long double sinh(long double __x) {return (sinhl(__x)); }
inline long double sqrt(long double __x) {return (sqrtl(__x)); }
inline long double tan(long double __x) {return (tanl(__x)); }
inline long double tanh(long double __x) {return (tanhl(__x)); }
//restoration of the default intrinsic status of those functions:
#pragma intrinsic (abs, acos, asin, atan, atan2, cos, cosh, exp, fabs, fmod, log, log10, sin, sinh, sqrt, tan, tanh)
#pragma warning(pop)
#    endif

//The native pow version has a bugged overload so it is not imported
//in the STLport namespace.
inline double pow(double __x, double __y) { return _STLP_VENDOR_CSTD::pow(__x, __y); }
inline double pow(double __x, int __y) {return (_Pow_int(__x, __y)); }
//Here is the bugged version:
//inline double pow(int __x, int __y) {return (_Pow_int(__x, __y)); }
inline float pow(float __x, float __y) {return (powf(__x, __y)); }
inline float pow(float __x, int __y) {return (_Pow_int(__x, __y)); }
inline long double pow(long double __x, long double __y) {return (powl(__x, __y)); }
inline long double pow(long double __x, int __y) {return (_Pow_int(__x, __y)); }
_STLP_END_NAMESPACE
#  endif

#endif /* (_STLP_HAS_NO_NEW_C_HEADERS || _STLP_MSVC || __ICL) && ! _STLP_HAS_NO_NAMESPACES */

#endif /* CMATH_H */
