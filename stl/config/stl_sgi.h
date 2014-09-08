// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#   include <standards.h>
#   if defined(_BOOL)
#     define __STL_BOOL_KEYWORD
#   endif
#   define __EDG_SWITCHES
#   if defined(_MIPS_SIM) && _MIPS_SIM != _MIPS_SIM_ABI32
#     define __STL_DEFAULT_CONSTRUCTOR_BUG
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABI32
#     define __STL_MEMBER_TEMPLATE_KEYWORD
#   endif
#   if defined(_STANDARD_C_PLUS_PLUS)
#     define __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#   endif
#   if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
#     define __STL_HAS_NAMESPACES
#   endif 
#   if (_COMPILER_VERSION < 721)
#     define __STL_NO_EXCEPTION_HEADER
#   endif
#   if _COMPILER_VERSION < 730 || !defined(_STANDARD_C_PLUS_PLUS) || !defined(_NAMESPACES)
#     define __STL_NO_BAD_ALLOC
#   endif
#   if defined(_LONGLONG) && defined(_SGIAPI) && _SGIAPI
#     define __STL_LONG_LONG
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __STL_USE_NEW_IOSTREAMS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __STL_CAN_THROW_RANGE_ERRORS
#   endif
#   if _COMPILER_VERSION >= 730 && defined(_STANDARD_C_PLUS_PLUS)
#     define __SGI_STL_USE_AUTO_PTR_CONVERSIONS
#   endif
#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABI32
#     define __STL_FUNCTION_TMPL_PARTIAL_ORDER
#   endif

#  define __STL_ARROW_OPERATOR
#  define __STL_METHOD_SPECIALIZATION
#  define __STL_DEFAULT_TEMPLATE_PARAM 1
#  define __STL_USE_SGI_STRING         1
