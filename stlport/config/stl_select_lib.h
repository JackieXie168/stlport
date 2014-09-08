# if !defined (__STL_NO_SGI_IOSTREAMS)

#  if ! defined (__STL_LIB_STATIC_SUFFIX)
#   define __STL_LIB_STATIC_SUFFIX ""
#  endif

// Note : the code below is intended to make use of compiled
// SGI iostreams easier. If you are with to change names used for
// STLport libraries , please also change RELEASE_NAME and DEBUG_NAME
// macros in makefile ../../src/vc6.mak (or whatever .mak you are using to build
// STLport). If you are using binaries, you may just rename the binaries.
#    if ! defined (__BUILDING_STLPORT) && ! defined (__STL_DONT_FORCE_MSVC_LIB_NAME)
#     if defined (__STL_USE_DECLSPEC)
#      ifdef __STL_DEBUG
#       pragma comment(lib, __STL_LIB_BASENAME"_stldebug.lib")
#      elif defined (_DEBUG) || defined (__DEBUG)
#       pragma comment(lib, __STL_LIB_BASENAME"_debug.lib")
#      else
#       pragma comment(lib, __STL_LIB_BASENAME".lib")
#      endif
#     else /* __STL_USE_DECLSPEC */
// fbp : for static linking, debug setting _MUST_ correspond to what
// has been compiled into binary lib
#      ifdef __STL_DEBUG
#       if (! defined (_DEBUG))
#        error "For static link with STLport library, _DEBUG setting MUST be on when __STL_DEBUG is on. (/MTd forces _DEBUG)"
#       endif
#       pragma comment(lib, __STL_LIB_BASENAME"_stldebug"__STL_LIB_STATIC_SUFFIX".lib")
#      elif defined (_DEBUG) || defined (__DEBUG)
#       pragma comment(lib, __STL_LIB_BASENAME"_debug"__STL_LIB_STATIC_SUFFIX".lib")
#      else
#       pragma comment(lib, __STL_LIB_BASENAME""__STL_LIB_STATIC_SUFFIX".lib")
#      endif
#     endif /* __STL_USE_DECLSPEC */
#    endif /* __BUILDING_STLPORT */
#   endif /* __SGI_STL_OWN_IOSTREAMS */
