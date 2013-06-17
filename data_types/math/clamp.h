#ifndef CLAMP_H_INCLUDED
#define CLAMP_H_INCLUDED

#include <glext.h>

namespace gl_extensions {
  template<typename T>
  void clamp(T &a, const T min, const T max) {
    (a < min) ? (a = min) : (a > max) ? (a = max) : (a = a);
  }

  template<typename T>
  void clamp_pair(T &a, T &b, const T min, const T max) {
    (a < min) ? (a = min) : (a > max) ? (a = max) : (a = a);
    (b < min) ? (b = min) : (b > max) ? (b = max) : (b = b);
  }

  template<typename T>
  void clamp_triplet(T &a, T &b, T &c, const T min, const T max) {
    (a < min) ? (a = min) : (a > max) ? (a = max) : (a = a);
    (b < min) ? (b = min) : (b > max) ? (b = max) : (b = b);
    (c < min) ? (c = min) : (c > max) ? (c = max) : (c = c);
  }

  template<typename T>
  void clamp_quad(T &a, T &b, T &c, T &d, const T min, const T max) {
    (a < min) ? (a = min) : (a > max) ? (a = max) : (a = a);
    (b < min) ? (b = min) : (b > max) ? (b = max) : (b = b);
    (c < min) ? (c = min) : (c > max) ? (c = max) : (c = c);
    (d < min) ? (d = min) : (d > max) ? (d = max) : (d = d);
  }
}
#endif//CLAMP_H
