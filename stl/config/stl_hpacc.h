// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// HP compilers

#  if __cplusplus >= 199707L
// it is aCC
// use the most conservative configuration as the base
#  define __STL_BOOL_KEYWORD 1
#  define __STL_DEFAULT_TEMPLATE_PARAM 1
#  define __STL_RAND48 1


#define __STL_PARTIAL_SPECIALIZATION_BUG 1

// #define __STL_USE_SGI_ALLOCATORS         1

#define __STL_NO_QUALIFIED_FRIENDS       1

// there were reports on problems with namespaces 
// in complex cases for 1.06. If run into one of them,
/// you may want to disable the feature.
#  define __STL_HAS_NAMESPACES 1

#  define __STL_TYPENAME 1
#  define __STL_EXPLICIT 1
#  define __STL_USE_EXCEPTIONS 1
#  define __STL_NEW_STYLE_CASTS 1
#  define __STL_WCHAR_T 1
#  define __STL_LONG_LONG 1
#  define __STL_LONG_DOUBLE 1
#  define __STL_MUTABLE 1
#  define __STL_FULL_SPEC_SYNTAX 1

#  define __STL_CLASS_PARTIAL_SPECIALIZATION 1

// aCC bug ? need explicit args on constructors of partial specialized
// classes
#  define __STL_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS 1

//  1.06 claims to support this feature. You may try enabling them.
//  If running into aCC bugs, disable it back.
#  define __STL_MEMBER_TEMPLATES 1

#  define __STL_FUNC_PARTIAL_ORDERING 1
#  define __STL_METHOD_SPECIALIZATION 1
// ?? fbp: really needed ?
#  define __STL_STATIC_ARRAY_BUG 1

// <exception> and stuff is in global namespace
# define __STL_VENDOR_STD

# define __STL_TYPENAME_ON_RETURN_TYPE typename

#  else
// it is HP's old cfront-based compiler.
# define __STL_NO_SIGNED_BUILTINS
#  endif /* cfront */

