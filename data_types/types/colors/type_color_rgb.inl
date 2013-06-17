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

namespace glext 
{
  /// Constructors
  template <typename T>
  color_rgb<T>::color_rgb() :
    _r(T(0)),
    _g(T(0)),
    _b(T(0))
  {}

  template <typename T>
  color_rgb<T>::color_rgb(const T &r, const T &g, const T &b) :
    _r((r > T(1)) ? (r / T(255)) : (r)),
    _g((g > T(1)) ? (g / T(255)) : (g)),
    _b((b > T(1)) ? (b / T(255)) : (b))
  {}

  /// Copy constructor
  template <typename T>
  color_rgb<T>::color_rgb(const color_rgb &rhs) :
    _r(rhs._r),
    _g(rhs._g),
    _b(rhs._b)
  {}

  /// Destructor
  template <typename T>
  color_rgb<T>::~color_rgb()
  {}

  /// Assignment operator
  template <typename T>
  color_rgb<T> &color_rgb<T>::operator=(color_rgb rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  /// Setters
  template <typename T>
  void color_rgb<T>::r(const T &r)
  {
    _r = r;
  }

  template <typename T>
  void color_rgb<T>::g(const T &g)
  {
    _g = g;
  }
  
  template <typename T>
  void color_rgb<T>::b(const T &b)
  {
    _b = b;
  }

  template <typename T>
  void color_rgb<T>::r_and_g_and_b(const T &r, const T &g, const T &b)
  {
    _r = r;
    _g = g;
    _b = b;
  }

  /// Getters 
  template <typename T>
  T& color_rgb<T>::rref()
  {
    return _r;
  }

  template <typename T>
  T& color_rgb<T>::gref()
  {
    return _g;
  }
  
  template <typename T>
  T& color_rgb<T>::bref()
  {
    return _b;
  }

  /// Getters
  template <typename T>
  T color_rgb<T>::r() const
  {
    return _r;
  }

  template <typename T>
  T color_rgb<T>::g() const
  {
    return _g;
  }
  
  template <typename T>
  T color_rgb<T>::b() const
  {
    return _b;
  }

  /// Utility methods
  template <typename T>
  void color_rgb<T>::to_bgr()
  {
    std::swap(_r, _b);
  }

  template <typename U>
  void swap(color_rgb<U> &lhs, color_rgb<U> &rhs)
  {
    std::swap(lhs.rref(), rhs.rref());
    std::swap(lhs.gref(), rhs.gref());
    std::swap(lhs.bref(), rhs.bref());
  }

  /// Comparison operators
  template <typename T>
  bool operator==(const color_rgb<T> &lhs, const color_rgb<T> &rhs)
  {
    return (lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b());
  }

  template <typename T>
  bool operator!=(const color_rgb<T> &lhs, const color_rgb<T> &rhs)
  {
    return (lhs.r() != rhs.r() || lhs.g() != rhs.g() || lhs.b() != rhs.b());
  }

  /// Output operators
  template <typename T>
  std::ostream &operator<<(std::ostream &out, const color_rgb<T> &rhs)
  {
    return out << "(" << rhs.r() << ", " << rhs.g() << ", " << rhs.b() << ")";
  }
}
