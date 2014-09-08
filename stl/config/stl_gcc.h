// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// g++ 2.7.x and above 

#   define __STL_BOOL_KEYWORD 1
#   define __STL_EXPLICIT 1
#   define __STL_LONG_LONG  1
#   define __STL_WCHAR_T  1
#   define __STL_MUTABLE  1
#   define __STL_NEW_STYLE_CASTS 1
#   define __STL_NO_EXCEPTION_HEADER 1
// gcc fails to initialize builtin types in expr. like this : new(p) char(); 
# define __STL_DEFAULT_CONSTRUCTOR_BUG 1
// this should always work
# define __STL_USE_SGI_STRING 1
// gcc 2.7.2 settings
#  if __GNUC__ <= 2 && __GNUC_MINOR__ <= 7 && ! defined (__CYGWIN32__)
// Will it work with 2.6 ? I doubt it.
#   if ( __GNUC_MINOR__ < 6 )
    __GIVE_UP_WITH_STL(GCC_272);
#   endif
#   define __STL_DEFAULT_TYPE_PARAM 1

# define  __STL_NO_BAD_ALLOC
# define  __SGI_STL_NO_ARROW_OPERATOR 1
# define  __STL_NO_STATIC_TEMPLATE_DATA

#  if !defined (__CYGWIN32__) 
#   define __STL_NESTED_TYPE_PARAM_BUG   1
#   define __STL_BASE_MATCH_BUG       1
//  unused operators are required (forward)
#   define  __STL_CONST_CONSTRUCTOR_BUG 
#   define __STL_NO_DEFAULT_NON_TYPE_PARAM
#   undef __STL_METHOD_SPECIALIZATION
#  endif
// static template data members workaround strategy for gcc tries
// to use weak symbols.
// if you don't want to use that, #define __STL_WEAK_ATTRIBUTE=0 ( you'll
// have to put "#define __PUT_STATIC_DATA_MEMBERS_HERE" line in one of your
// compilation unit ( or CFLAGS for it ) _before_ including any STL header ).
#   if !(defined (__STL_STATIC_TEMPLATE_DATA) || defined (__STL_WEAK_ATTRIBUTE ))
// systems using GNU ld or format that supports weak symbols
// may use "weak" attribute
// Linux & Solaris ( x86 & SPARC ) are being auto-recognized here
#    if defined(__STL_GNU_LD) || defined(__ELF__) || \
     (( defined (__SVR4) || defined ( __svr4__ )) && \
      ( defined (sun) || defined ( __sun__ )))
#     define __STL_WEAK_ATTRIBUTE 1
#    endif
#   endif /* __STL_WEAK_ATTRIBUTE */
#  else /* ! <= 2.7.* */

#   define __STL_MEMBER_TEMPLATES 1
#   define __STL_DEFAULT_TEMPLATE_PARAM 1
#   define __STL_CLASS_PARTIAL_SPECIALIZATION 1
#   define __STL_FUNC_PARTIAL_ORDERING 1
#   define __STL_FULL_SPEC_SYNTAX 1
#   define __STL_EXPLICIT_FUNCTION_TMPL_ARGS 1
#   define __STL_TYPENAME 1
#   define  __STL_METHOD_SPECIALIZATION 1
// #   define  __STL_USE_NEW_STYLE_HEADERS 1
#   if (__GNUC_MINOR__>= 90) /* egcs 1.1 */
#     define __STL_HAS_NAMESPACES 1
#     define __STL_MEMBER_TEMPLATE_CLASSES 1
#     define __STL_FRIEND_TEMPLATES 1
#   endif
#  endif /* ! <= 2.7.* */
