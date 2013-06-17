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
  vector_4d<T>::vector_4d() :
    _x(T(0)),
    _y(T(0)),
    _z(T(0)),
    _w(T(0))
  {}

  template <typename T>
  vector_4d<T>::vector_4d(const T &x, const T &y, const T &z, const T &w) :
    _x(x),
    _y(y),
    _z(z),
    _w(w)
  {}

  /// Copy constructor
  template <typename T>
  vector_4d<T>::vector_4d(const vector_4d<T> &rhs) :
    _x(rhs._x),
    _y(rhs._y),
    _z(rhs._z),
    _w(rhs._w)
  {}

  /// Destructor
  template <typename T>
  vector_4d<T>::~vector_4d()
  {}

  /// Assignment operator
  template <typename T>
  vector_4d<T> &vector_4d<T>::operator=(vector_4d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Sub-index operator
  template <typename T>
  T &vector_4d<T>::operator[](unsigned short index) 
  {
    assert(index < 4);

    switch(index) 
    {
      case(0): return _x;
      case(1): return _y;
      case(2): return _z;
      case(3): return _w;
      default: return _x;
    }
  }

  template <typename T>
  const T &vector_4d<T>::operator[](unsigned short index) const 
  {
    assert(index < 4);

    switch(index) 
    {
      case(0): return _x;
      case(1): return _y;
      case(2): return _z;
      case(3): return _w;
      default: return _x;
    }
  }

  /// Setters
  template <typename T>
  void vector_4d<T>::x(const T &x)
  {
    _x = x;
  }

  template <typename T>
  void vector_4d<T>::y(const T &y)
  {
    _y = y;
  }

  template <typename T>
  void vector_4d<T>::z(const T &z)
  {
    _z = z;
  }

  template <typename T>
  void vector_4d<T>::w(const T &w)
  {
    _w = w;
  }

  template <typename T>
  void vector_4d<T>::x_and_y_and_z_and_w(const T &x, const T &y, const T &z,
    const T &w)
  {
    _x = x;
    _y = y;
    _z = z;
    _w = w;
  }

  /// Getters
  template <typename T>
  T& vector_4d<T>::xref()
  {
    return _x;
  }

  template <typename T>
  T& vector_4d<T>::yref()
  {
    return _y;
  }

  template <typename T>
  T& vector_4d<T>::zref()
  {
    return _z;
  }

  template <typename T>
  T& vector_4d<T>::wref()
  {
    return _w;
  }

  /// Internal math algorithms 
  template <typename T> 
  T vector_4d<T>::magnitude() const
  {
    return sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
  }
  
  template <typename T> 
  void vector_4d<T>::normalize() 
  {
    if (magnitude()) {
      (*this) *= (T(1) / magnitude());
    }
  }

  template <typename T>
  T vector_4d<T>::dot(const vector_4d<T> &rhs) const
  {
    return (_x * rhs._x + _y * rhs._y + _z * rhs._z + _w * rhs._w);
  }

  template <typename T> 
  void vector_4d<T>::operator+=(const vector_4d<T> &rhs)
  {
    _x += rhs._x;
    _y += rhs._y;
    _z += rhs._z;
    _w += rhs._w;
  }

  template <typename T> 
  void vector_4d<T>::operator-=(const vector_4d<T> &rhs)
  {
    _x -= rhs._x;
    _y -= rhs._y;
    _z -= rhs._z;
    _w += rhs._w;
  }

  template <typename T> 
  void vector_4d<T>::operator*=(const T &rhs)
  {
    _x *= rhs;
    _y *= rhs;
    _z *= rhs;
    _w *= rhs;
  }

  /// Getters
  template <typename T>
  T vector_4d<T>::x() const
  {
    return _x;
  }

  template <typename T>
  T vector_4d<T>::y() const
  {
    return _y;
  }

  template <typename T>
  T vector_4d<T>::z() const
  {
    return _z;
  }
 
  template <typename T>
  T vector_4d<T>::w() const
  {
    return _w;
  }

  /// Copy and swap idiom
  template <typename T>
  void swap(vector_4d<T> &lhs, vector_4d<T> &rhs)
  {
    std::swap(lhs.xref(), rhs.xref());
    std::swap(lhs.yref(), rhs.yref());
    std::swap(lhs.zref(), rhs.zref());
    std::swap(lhs.wref(), rhs.wref());
  }

  /// Comparison operators
  template <typename T>
  bool operator<(const vector_4d<T> &lhs, const vector_4d<T> &rhs)
  {
    return (lhs.x() < rhs.x() && lhs.y() < rhs.y() && lhs.z() < rhs.z() &&
      lhs.w() < rhs.w());
  }

  template <typename T>
  bool operator>(const vector_4d<T> &lhs, const vector_4d<T> &rhs)
  {
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y() && lhs.z() > rhs.z() &&
      lhs.w() > rhs.w());
  }
  
  template <typename T>
  bool operator<=(const vector_4d<T> &lhs, const vector_4d<T> &rhs)
  {
    return (lhs.x() <= rhs.x() && lhs.y() <= rhs.y() && lhs.z() <= rhs.z() &&
      lhs.w() <= rhs.w());
  }

  template <typename T>
  bool operator>=(const vector_4d<T> &lhs, const vector_4d<T> &rhs)
  {
    return (lhs.x() >= rhs.x() && lhs.y() >= rhs.y() && lhs.z() >= rhs.z() &&
      lhs.w() >= rhs.w());
  }

  template <typename T>
  bool operator==(const vector_4d<T> &lhs, const vector_4d<T> &rhs)
  {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() &&
      lhs.w() == rhs.w());
  }

  template <typename T>
  bool operator!=(const vector_4d<T> &lhs, const vector_4d<T> &rhs)
  {
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.z() != rhs.z() ||
      lhs.w() != rhs.w());
  }

  /// Arithmetic operators
  template <typename T>
  vector_4d<T> operator+(const vector_4d<T> &v1, const vector_4d<T> &v2)
  {
    return vector_4d<T>(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z(),
      v1.w() + v2.w());
  }

  template <typename T>
  vector_4d<T> operator-(const vector_4d<T> &v1, const vector_4d<T> &v2)
  {
    return vector_4d<T>(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z(),
      v1.w() - v2.w());
  }

  template <typename T>
  vector_4d<T> operator-(const vector_4d<T> &v1)
  {
    return vector_4d<T>(T(-1) * v1.x(), T(-1) * v1.y(), T(-1) * v1.z(),
      T(-1) * v1.w());
  }

  template <typename T>
  vector_4d<T> operator*(const T &s, const vector_4d<T> &v1)
  {
    return vector_4d<T>(s * v1.x(), s * v1.y(), s * v1.z(), s * v1.w());
  }

  /// Output operators
  template <typename T>
  std::ostream &operator<<(std::ostream &out, const vector_4d<T> &rhs)
  {
    return out << "(" << rhs.x() << ", " << rhs.y() << ", " << rhs.z() << 
      ", " << rhs.w() << ")";
  }
}
