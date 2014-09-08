// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// Apple MPW SCpp 8.8.2  

# if defined (__SC__) && (__SC__ >= 0x882)
# ifdef qMacApp
#  include "CoreSwitches_AC.h"
#  include "ConditionalMacros_AC.h"
#  include "Types_AC.h"
#               define __STL_FILE__ _FILE_AC
#               define __STL_DEBUG_MESSAGE      
#               define __stl_debug_message ProgramBreak_AC
#  include <ConditionalMacros.h>
#  include <Types.h>
# else
#  include <ConditionalMacros.h>
#  include <Types.h>
# endif
# define __STL_DEBUG_MESSAGE_POST DebugStr("\pSTL diagnosis issued. See 'stderr' for detail.");
# define __STL_ASSERT_MSG_TRAILER " "

#   undef __STL_UINT32_T
#   define __STL_UINT32_T UInt32
# if TYPE_BOOL
// #  define __STL_BOOL_KEYWORD 1
# else
#   define __STL_NO_BOOL
# endif
#   define __STL_DONT_USE_BOOL_TYPEDEF 1
# if TYPE_LONGLONG
#    define __STL_LONG_LONG 1
# else
#  undef __STL_LONG_LONG
# endif
// # define __STL_LONG_DOUBLE 1
// # define __STL_WCHAR_T 1
 typedef int wint_t;

# if __option(exceptions)
// #   define __STL_USE_EXCEPTIONS 1
# else
#   define __STL_HAS_NO_EXCEPTIONS
# endif
# define __STL_HAS_NO_NAMESPACES
# define __STL_LIMITED_DEFAULT_TEMPLATES
// # undef __STL_DEFAULT_TYPE_PARAM
// # undef __STL_RAND48
# define __STL_NEED_TYPENAME
# define __STL_NEED_EXPLICIT
# define __STL_NO_EXCEPTION_SPEC
# define __STL_NEED_MUTABLE
# define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX
# define __STL_NO_BAD_ALLOC
# define __STL_NO_MEMBER_TEMPLATES
# define __STL_NO_MEMBER_CLASS_TEMPLATES
# define __STL_NO_FRIEND_TEMPLATES
# define __STL_NO_CLASS_PARTIAL_SPECIALIZATION
# define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER
# define __STL_USE_ABBREVS 1 
//# undef __STL_NO_EXCEPTION_HEADER 

# define __STL_NON_TYPE_TMPL_PARAM_BUG 1
# define __STL_THROW_RETURN_BUG 1
# define __STL_DEFAULT_PARAM_CONSTRUCTOR_BUG 1
# define __STL_BOGUS_TEMPLATE_TYPE_MATCHING_BUG 1
# define __STL_MPW_EXTRA_CONST const  
# define __SGI_STL_NO_ARROW_OPERATOR 1
# define __STL_HAS_NO_NEW_C_HEADERS 1
# define __STL_NO_NEW_NEW_HEADER 1
# define __STL_NO_MEMBER_TEMPLATE_CLASSES
# define __STL_HAS_NO_NEW_IOSTREAMS
# define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS
# define __STL_GLOBAL_NESTED_RETURN_TYPE_PARAM_BUG
# define __STL_NO_PROXY_ARROW_OPERATOR
# endif // defined (__SC__) && (__SC__ >= 0x882)

// Apple MPW MrCpp 4.1.0
#if defined (__MRC__)
# ifdef qMacApp 
#  include "CoreSwitches_AC.h"
#  include "ConditionalMacros_AC.h"
#  include "Types_AC.h"
#   define __STL_FILE__ _FILE_AC
#   define __STL_DEBUG_MESSAGE
#   define __stl_debug_message ProgramBreak_AC
# else         // qMacApp
#  include <ConditionalMacros.h> 
#  include <Types.h>    
# endif         // qMacApp
# define __STL_DEBUG_MESSAGE_POST DebugStr("\pSTL diagnosis issued. See 'stderr' for detail.");
# define __STL_ASSERT_MSG_TRAILER " "

# ifndef TYPE_BOOL
#  error <ConditionalMacros.h> must be included. (TYPE_BOOL)
# endif
# if TYPE_BOOL
// #  define __STL_BOOL_KEYWORD
# else
# define __STL_NO_BOOL
# endif
#   define __STL_DONT_USE_BOOL_TYPEDEF
#   undef __STL_UINT32_T
#   define __STL_UINT32_T UInt32
# ifndef TYPE_LONGLONG
#  error <ConditionalMacros.h> must be included. (TYPE_LONGLONG)
# endif
# if TYPE_LONGLONG
#    define __STL_LONG_LONG 1
# else
#  undef __STL_LONG_LONG
# endif
// # define __STL_LONG_DOUBLE 1
// # define __STL_WCHAR_T 1
 typedef int wint_t;

# if __option(exceptions)
// #   define __STL_USE_EXCEPTIONS
# else
#   define __STL_HAS_NO_EXCEPTIONS
# endif
#  if __MRC__ > 0x400
# else
#  define __STL_NO_EXCEPTION_SPEC
# endif
# define __STL_HAS_NO_NAMESPACES // it looks like MrCpp does not support namespace in combination with templates
# define __STL_LIMITED_DEFAULT_TEMPLATES
// # undef __STL_DEFAULT_TYPE_PARAM

# undef __STL_RAND48
# define __STL_NEED_TYPENAME
# define __STL_NEED_EXPLICIT // it looks like MrCpp does not support explicit in templated classes
// # define __STL_NEW_STYLE_CASTS
#  if __MRC__ > 0x400
// #  define __STL_MUTABLE
# else
#  define __STL_NEED_MUTABLE
# endif
# define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX
# define __STL_NO_BAD_ALLOC
# define __STL_NO_MEMBER_TEMPLATES
# define __STL_NO_MEMBER_CLASS_TEMPLATES
# define __STL_NO_FRIEND_TEMPLATES 1
# define __STL_NO_CLASS_PARTIAL_SPECIALIZATION
# define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER
// # define __STL_AUTOMATIC_TYPE_TRAITS 1
// # define __STL_METHOD_SPECIALIZATION 1
# define __STL_USE_ABBREVS 1
// # define __STL_STATIC_TEMPLATE_DATA 1

# define __STL_NON_TYPE_TMPL_PARAM_BUG 1
# define __STL_THROW_RETURN_BUG 1
# define __STL_DEFAULT_PARAM_CONSTRUCTOR_BUG 1
# define __STL_BOGUS_TEMPLATE_TYPE_MATCHING_BUG 1
# define __STL_MPW_EXTRA_CONST const
# define __SGI_STL_NO_ARROW_OPERATOR 1
# define __STL_HAS_NO_NEW_C_HEADERS 1
# define __STL_NO_NEW_NEW_HEADER 1
# define __STL_NO_MEMBER_TEMPLATE_CLASSES
# define __STL_HAS_NO_NEW_IOSTREAMS
# define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS
# define __STL_GLOBAL_NESTED_RETURN_TYPE_PARAM_BUG
# define __STL_NO_PROXY_ARROW_OPERATOR
# endif // defined (__MRC__)

// Note : this line is dangerous, since it remanes the public class.
// Only use it if experience major difficulties with symbol length 
// during compilation.

// # define allocator _Al

