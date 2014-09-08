// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#  define __STL_USE_NEW_IOSTREAMS	1
#  define __STL_USE_EXCEPTIONS	        1	// Enable exception handling
// fbp : added for those who does not recompile STD
#  define __STL_HAS_STRING_HEADER       1
#  define __STL_HAS_STDEXCEPT_HEADER    1

// typical MAC installation.
# if __MWERKS__ >= 0x2300	// CWPro5 changes paths - dwa 2/28/99
#  define __STL_NATIVE_INCLUDE_PATH  Macintosh HD:Codewarrior Pro 5:Metrowerks CodeWarrior:MSL:MSL_C++:MSL_Common:Include
#  define __STL_NATIVE_C_INCLUDE_PATH  Macintosh HD:Codewarrior Pro 5:Metrowerks CodeWarrior:MSL:MSL_C:MSL_Common:Include
#  define __STL_NATIVE_HEADER(header)     <Macintosh HD:Codewarrior Pro 5:Metrowerks CodeWarrior:MSL:MSL_C++:MSL_Common:Include:##header>
#  define __STL_NATIVE_C_HEADER(header)     <Macintosh HD:Codewarrior Pro 5:Metrowerks CodeWarrior:MSL:MSL_C:MSL_Common:Include:##header>
#  define __STL_TYPENAME_ON_RETURN_TYPE typename
# else
#  define __STL_NATIVE_INCLUDE_PATH  Macintosh HD:Codewarrior Pro 4:Metrowerks CodeWarrior:Metrowerks Standard Library:MSL C++:Include
#  define __STL_NATIVE_C_INCLUDE_PATH  Macintosh HD:Codewarrior Pro 4:Metrowerks CodeWarrior:Metrowerks Standard Library:MSL C:MSL Common:Public Includes
#  define __STL_NATIVE_HEADER(header)     <Macintosh HD:Codewarrior Pro 4:Metrowerks CodeWarrior:Metrowerks Standard Library:MSL C++:Include:##header>
#  define __STL_NATIVE_C_HEADER(header)     <Macintosh HD:Codewarrior Pro 4:Metrowerks CodeWarrior:Metrowerks Standard Library:MSL C:MSL Common:Public Includes:##header>
# endif
# define __STL_MAKE_HEADER(path, header) <path:header>

// *** CodeWarrior Compiler Features ***
#  if __option(longlong)
#   define __STL_LONG_LONG	1
#  endif
#  define __STL_BOOL_KEYWORD	1
#  define __STL_EXPLICIT 1
#  define __STL_EXCEPTIONS 1
#  define __STL_MUTABLE 1
#  define __STL_NEW_STYLE_CASTS 1
#  define __STL_FULL_SPEC_SYNTAX 1

// *** CodeWarrior Compiler Bugs ***
#  define __MSL_FIX_ITERATORS__(myType)		// Some MSL headers rely on this
#  define __STL_NO_TEMPLATE_CONVERSIONS	1
#  define __STL_THROW_RETURN_BUG	1
#  define __STL_MEMBER_SPECIALIZATION_BUG	1

// *** Metrowerks Standard Library Features ***

#  define __STL_USE_NEW_STYLE_HEADERS 1

// Version-specific settings
#  if __MWERKS__ >= 0x2300		// CW Pro5 features
	// Member functions can now be defined outside the class definition
#  else							// Pre-Pro5 bugs
#   define __STL_RELOPS_IN_STD_BUG	1
#   define __STL_DEFAULT_CONSTRUCTOR_BUG 1
#  endif

#  if __MWERKS__ >= 0x2200		// CW Pro4 features
#   define __STL_FUNC_PARTIAL_ORDERING 1
#	define __STL_MEMBER_TEMPLATES	1		// but no conversion operators
#   define __STL_MEMBER_TEMPLATE_CLASSES	1
#  else							// Pre-4.0 bugs
#   define __STL_BROKEN_USING_DIRECTIVE	1
#  endif

#  if __MWERKS__ >= 0x2110
#   define __STL_CLASS_PARTIAL_SPECIALIZATION 1
#  else
#  endif

#  if __MWERKS__ >= 0x2100			// CW Pro3 features
#   define __STL_HAS_NAMESPACES 1
#   define __STL_EXPLICIT_FUNCTION_TMPL_ARGS 1

// The state of the compiler's support for typename is somewhat ambiguous, but there appear
// to be at least some cases that absolutely require it.
#   define __STL_TYPENAME				1

#  else								// Pre-3.0 bugs
#   define __SGI_STL_NO_ARROW_OPERATOR 1
#   define __STL_TEMPLATE_PARAM_SUBTYPE_BUG	1
#   define __STL_FORCED_INLINE_INSTANTIATION_BUG	1
#   define __STL_NO_NAMESPACES 1	// Namespaces not implemented in MSL
#   define __STL_MULTI_CONST_TEMPLATE_ARG_BUG	1
#   define __STL_INLINE_NAME_RESOLUTION_BUG	1
// *** Metrowerks Standard Library Bug ***
#   define __STL_MSVC50_COMPATIBILITY 1
#  endif

#  if __MWERKS__ >= 0x2000			// v. 2.0 features

#   define __STL_WCHAR_T                1
#  else								// Pre-2.0 bugs
#   define  __STL_NON_TYPE_TMPL_PARAM_BUG	1	// dwa 8/21/97 - this bug fixed for CWPro2
#   define __STL_UNINITIALIZABLE_PRIVATE  1		// dwa 10/23/97 - this bug fixed for CWPro2
#  endif

#  if __MWERKS__ >= 0x1900         				// dwa 8/19/97 - 1.9 Compiler feature defines
#   define __STL_DEFAULT_TEMPLATE_PARAM 1
#  else								// Pre-1.9 bugs
#   if __MWERKS__ < 0x1800
    __GIVE_UP_WITH_STL(CW_18)
#   endif
#   define __STL_BASE_TYPEDEF_BUG        1
#   define __STL_BASE_MATCH_BUG   1
#   define __STL_NONTEMPL_BASE_MATCH_BUG 1
#   define __STL_DEFAULT_TYPE_PARAM  1			// More limited template parameters
#  endif
