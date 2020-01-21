#ifndef _STLP_INTERNAL_MEMTOOLS_H
#define _STLP_INTERNAL_MEMTOOLS_H

#ifndef _STLP_CSTDINT
#  include <cstdint>
#endif

_STLP_BEGIN_NAMESPACE

/**
 * @ingroup StandardFeatures
 * @brief Returns the address of an object.
 */
template <typename T> inline
T* addressof (T& arg) {
    return reinterpret_cast<T*>(&reinterpret_cast<char&> (arg) );
}

//! @overloads addressof
template <typename T> inline
T const* addressof (T const& arg) {
    return reinterpret_cast<T const*>(&reinterpret_cast<char const&> (arg) );
}

_STLP_END_NAMESPACE

#endif