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
  texcoord_2d<T>::texcoord_2d() :
    _s(T(0)),
    _t(T(0))
  {}

  template <typename T>
  texcoord_2d<T>::texcoord_2d(const T &s, const T &t) :
    _s(s),
    _t(t)
  {}

  /// Copy constructor
  template <typename T>
  texcoord_2d<T>::texcoord_2d(const texcoord_2d<T> &rhs) :
    _s(rhs._s),
    _t(rhs._t)
  {}

  /// Destructor
  template <typename T>
  texcoord_2d<T>::~texcoord_2d()
  {}

  /// Assignment operator
  template <typename T>
  texcoord_2d<T> &texcoord_2d<T>::operator=(texcoord_2d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Sub-index operator
  template <typename T>
  T &texcoord_2d<T>::operator[](unsigned short index)
  {
    assert(index < 2);

    switch(index) 
    {
      case(0): return _s;
      case(1): return _t;
      default: return _s;
    }
  }

  template <typename T>
  const T &texcoord_2d<T>::operator[](unsigned short index) const
  {
    assert(index < 2);

    switch(index) 
    {
      case(0): return _s;
      case(1): return _t;
      default: return _s;
    }
  }

  /// Setters
  template <typename T>
  void texcoord_2d<T>::s(const T &s)
  {
    _s = s;
  }

  template <typename T>
  void texcoord_2d<T>::t(const T &t)
  {
    _t = t;
  }

  template <typename T>
  void texcoord_2d<T>::s_and_t(const T &x, const T &y)
  {
    _s = s;
    _t = t;
  }

  /// Getters
  template <typename T>
  T& texcoord_2d<T>::sref()
  {
    return _s;
  }

  template <typename T>
  T& texcoord_2d<T>::tref()
  {
    return _t;
  }

  /// Getters
  template <typename T>
  T texcoord_2d<T>::s() const
  {
    return _s;
  }

  template <typename T>
  T texcoord_2d<T>::t() const
  {
    return _t;
  }
 
  /// Copy and swap idiom
  template <typename T>
  void swap(texcoord_2d<T> &lhs, texcoord_2d<T> &rhs)
  {
    std::swap(lhs.sref(), rhs.sref());
    std::swap(lhs.tref(), rhs.tref());
  }

  template <typename T>
  bool operator==(const texcoord_2d<T> &lhs, const texcoord_2d<T> &rhs)
  {
    return (lhs.s() == rhs.s() && lhs.t() == rhs.t());
  }

  template <typename T>
  bool operator!=(const texcoord_2d<T> &lhs, const texcoord_2d<T> &rhs)
  {
    return (lhs.s() != rhs.s() || lhs.t() != rhs.t());
  }

  /// Output operators
  template <typename T>
  std::ostream &operator<<(std::ostream &out, const texcoord_2d<T> &rhs)
  {
    return out << "(" << rhs.s() << ", " << rhs.t() << ")";
  }
}
