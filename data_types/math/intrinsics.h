#ifndef INTRINSICS_H_INCLUDED
#define INTRINSICS_H_INCLUDED

#if defined(_WIN32)
#elif defined(__gnu_linux__) || defined(__linux__)
#elif defined(__ANDROID__)
#elif defined(__CYGWIN__)
#elif defined(macintosh)
#else
#include <cmath>
#endif

#include <iostream>

namespace glext
{
#if defined(_WIN32)
#pragma function( sqrt )
#endif
  template<typename T>
  inline float sqrt(const T &val)
  {
#if defined(_WIN32)
    return sqrt(val);
#elif defined(__gnu_linux__) || defined(__linux__)
    return __builtin_sqrt(val);
#elif defined(__ANDROID__)
    return __builtin_sqrt(val);
#elif defined(__CYGWIN__)
    return __builtin_sqrt(val);
#elif defined(macintosh)
    // How do I do this
#else
    return std::sqrt(val);
#endif
  }
#if defined(_WIN32)
#pragma function( sqrt )
#endif
}
#endif
