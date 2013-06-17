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
  point_2d<T>::point_2d() :
    _x(T(0)),
    _y(T(0))
  {}

  template <typename T>
  point_2d<T>::point_2d(const T &x, const T &y) :
    _x(x),
    _y(y)
  {}

  /// Copy constructor
  template <typename T>
  point_2d<T>::point_2d(const point_2d<T> &rhs) :
    _x(rhs._x),
    _y(rhs._y)
  {}

  /// Destructor
  template <typename T>
  point_2d<T>::~point_2d()
  {}

  /// Assignment operator
  template <typename T>
  point_2d<T> &point_2d<T>::operator=(point_2d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Setters
  template <typename T>
  void point_2d<T>::x(const T &x)
  {
    _x = x;
  }

  template <typename T>
  void point_2d<T>::y(const T &y)
  {
    _y = y;
  }

  template <typename T>
  void point_2d<T>::x_and_y(const T &x, const T &y)
  {
    _x = x;
    _y = y;
  }

  /// Getters
  template <typename T>
  T& point_2d<T>::xref()
  {
    return _x;
  }

  template <typename T>
  T& point_2d<T>::yref()
  {
    return _y;
  }

  /// Getters
  template <typename T>
  T point_2d<T>::x() const
  {
    return _x;
  }

  template <typename T>
  T point_2d<T>::y() const
  {
    return _y;
  }

  /// Copy and swap idiom
  template <typename T>
  void swap(point_2d<T> &lhs, point_2d<T> &rhs)
  {
    std::swap(lhs.xref(), rhs.xref());
    std::swap(lhs.yref(), rhs.yref());
  }

  /// Comparison operators
  template <typename T>
  bool operator<(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() < rhs.x() && lhs.y() < rhs.y());
  }

  template <typename T>
  bool operator>(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y());
  }
  
  template <typename T>
  bool operator<=(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() <= rhs.x() && lhs.y() <= rhs.y());
  }

  template <typename T>
  bool operator>=(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() >= rhs.x() && lhs.y() >= rhs.y());
  }

  template <typename T>
  bool operator==(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
  }

  template <typename T>
  bool operator!=(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y());
  }

  /// Output operators
  template <typename T>
  std::ostream &operator<<(std::ostream &out, const point_2d<T> &rhs)
  {
    return out << "(" << rhs.x() << ", " << rhs.y() << ")";
  }
}
