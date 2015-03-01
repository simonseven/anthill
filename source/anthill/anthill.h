#pragma once

#include <memory>
#include <cstddef>

#include "config.h"

namespace anthill {

// Consistent naming scheme for bit-specific types.
typedef ::int8_t    ax_int8;
typedef ::int16_t   ax_int16;
typedef ::int32_t   ax_int32;
typedef ::int64_t   ax_int64;

typedef ::uint8_t   ax_uint8;
typedef ::uint16_t  ax_uint16;
typedef ::uint32_t  ax_uint32;
typedef ::uint64_t  ax_uint64;

typedef std::size_t ax_size;
typedef std::size_t ax_index;

} // anthill

// remove this once it's added to <memory>

// this version is Stephan T. Lavavej's version, which handles the array
// case correctly. See http://herbsutter.com/gotw/_102/

namespace std {

template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args) {
   static_assert(std::extent<T>::value == 0,
       "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

   typedef typename std::remove_extent<T>::type U;
   return std::unique_ptr<T>(new U[sizeof...(Args)]{std::forward<Args>(args)...});
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
   return make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);
}

} // std

