#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include <cmath>

namespace glext 
{
  template <typename T>
  bool isnan(const T &val)
  {
#if defined(__linux__)
    return std::isnan(val);
#elif defined(_WIN32)
    return _isnan(val);
#endif
  }
}

#endif
