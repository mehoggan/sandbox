/*
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
