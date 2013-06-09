#ifndef SQRT_H_INCLUDED
#define SQRT_H_INCLUDED

#include <cmath>

namespace glext
{
  template<typename T>
  inline float sqrt(const T &val)
  {
    return std::sqrt(val);
  }
}
#endif
