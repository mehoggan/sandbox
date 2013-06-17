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
  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML>::matrix_4X4(matrix_type type)
  {
    if (type == null) {
      _v0 = vector_4d<T>();
      _v1 = vector_4d<T>();
      _v2 = vector_4d<T>();
      _v3 = vector_4d<T>();
    } else if (type == identity) {
      _v0 = vector_4d<T>(T(1.0), T(0.0), T(0.0), T(0.0));
      _v1 = vector_4d<T>(T(0.0), T(1.0), T(0.0), T(0.0));
      _v2 = vector_4d<T>(T(0.0), T(0.0), T(1.0), T(0.0));
      _v3 = vector_4d<T>(T(0.0), T(0.0), T(0.0), T(1.0));
    } 
  }

  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML>::matrix_4X4(const vector_4d<T> &v0, const vector_4d<T> &v1, 
    const vector_4d<T> &v2, const vector_4d<T> &v3) :
    _v0(v0),
    _v1(v1),
    _v2(v2),
    _v3(v3) 
  {}
  
  /// Copy constructor
  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML>::matrix_4X4(const matrix_4X4<T, ML> &rhs) :
    _v0(rhs._v0),
    _v1(rhs._v1),
    _v2(rhs._v2),
    _v3(rhs._v3)
  {}

  /// Destructor
  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML>::~matrix_4X4()
  {}

  /// Assignment operator
  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML> &matrix_4X4<T, ML>::operator=(matrix_4X4<T, ML> rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  /// Sub-index operator
  template <typename T, matrix_layout ML>
  vector_4d<T> &matrix_4X4<T, ML>::operator[](unsigned short index)
  {
    assert(index < 4);

    switch(index)
    {
      case(0): return _v0;
      case(1): return _v1;
      case(2): return _v2;
      case(3): return _v3;
      default: return _v0;
    }
    return _v0;
  }

  template <typename T, matrix_layout ML>
  const vector_4d<T> &matrix_4X4<T, ML>::operator[](unsigned short index) const
  {
    assert(index < 4);

    switch(index)
    {
      case(0): return _v0;
      case(1): return _v1;
      case(2): return _v2;
      case(3): return _v3;
      default: return _v0;
    }
    return _v0;
  }

  /// Setters
  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::vec0(const vector_4d<T> &v0)
  {
    _v0 = v0;
  }

  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::vec1(const vector_4d<T> &v1)
  {
    _v1 = v1;
  }

  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::vec2(const vector_4d<T> &v2)
  {
    _v2 = v2;
  }

  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::vec3(const vector_4d<T> &v3)
  {
    _v3 = v3;
  }

  /// Getters
  template <typename T, matrix_layout ML>
  vector_4d<T> matrix_4X4<T, ML>::vec0() const
  {
    return _v0;
  }

  template <typename T, matrix_layout ML>
  vector_4d<T> matrix_4X4<T, ML>::vec1() const
  {
    return _v1;
  }
  
  template <typename T, matrix_layout ML>
  vector_4d<T> matrix_4X4<T, ML>::vec2() const
  {
    return _v2;
  }
  
  template <typename T, matrix_layout ML>
  vector_4d<T> matrix_4X4<T, ML>::vec3() const
  {
    return _v3;
  }
  
  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::operator+=(const matrix_4X4 &rhs)
  {
    _v0 += rhs._v0;
    _v1 += rhs._v1;
    _v2 += rhs._v2;
    _v3 += rhs._v3;
  }

  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::operator-=(const matrix_4X4 &rhs)
  {
    _v0 -= rhs._v0;
    _v1 -= rhs._v1;
    _v2 -= rhs._v2;
    _v3 -= rhs._v3;
  }

  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::operator*=(const matrix_4X4 &rhs)
  {
    if (ML == column) {
      /* [col][row] */
      vector_4d<T> v0(
        _v0[0]*rhs[0][0]+_v1[0]*rhs[0][1]+_v2[0]*rhs[0][2]+_v3[0]*rhs[0][3],
        _v0[1]*rhs[0][0]+_v1[1]*rhs[0][1]+_v2[1]*rhs[0][2]+_v3[1]*rhs[0][3],
        _v0[2]*rhs[0][0]+_v1[2]*rhs[0][1]+_v2[2]*rhs[0][2]+_v3[2]*rhs[0][3],
        _v0[3]*rhs[0][0]+_v1[3]*rhs[0][1]+_v2[3]*rhs[0][2]+_v3[3]*rhs[0][3]);
      vector_4d<T>v1(
        _v0[0]*rhs[1][0]+_v1[0]*rhs[1][1]+_v2[0]*rhs[1][2]+_v3[0]*rhs[1][3],
        _v0[1]*rhs[1][0]+_v1[1]*rhs[1][1]+_v2[1]*rhs[1][2]+_v3[1]*rhs[1][3],
        _v0[2]*rhs[1][0]+_v1[2]*rhs[1][1]+_v2[2]*rhs[1][2]+_v3[2]*rhs[1][3],
        _v0[3]*rhs[1][0]+_v1[3]*rhs[1][1]+_v2[3]*rhs[1][2]+_v3[3]*rhs[1][3]);
      vector_4d<T>v2(
        _v0[0]*rhs[2][0]+_v1[0]*rhs[2][1]+_v2[0]*rhs[2][2]+_v3[0]*rhs[2][3],
        _v0[1]*rhs[2][0]+_v1[1]*rhs[2][1]+_v2[1]*rhs[2][2]+_v3[1]*rhs[2][3],
        _v0[2]*rhs[2][0]+_v1[2]*rhs[2][1]+_v2[2]*rhs[2][2]+_v3[2]*rhs[2][3],
        _v0[3]*rhs[2][0]+_v1[3]*rhs[2][1]+_v2[3]*rhs[2][2]+_v3[3]*rhs[2][3]);
      vector_4d<T>v3(
        _v0[0]*rhs[3][0]+_v1[0]*rhs[3][1]+_v2[0]*rhs[3][2]+_v3[0]*rhs[3][3],
        _v0[1]*rhs[3][0]+_v1[1]*rhs[3][1]+_v2[1]*rhs[3][2]+_v3[1]*rhs[3][3],
        _v0[2]*rhs[3][0]+_v1[2]*rhs[3][1]+_v2[2]*rhs[3][2]+_v3[2]*rhs[3][3],
        _v0[3]*rhs[3][0]+_v1[3]*rhs[3][1]+_v2[3]*rhs[3][2]+_v3[3]*rhs[3][3]);
      /* construct matrix using column vectors */
      (*this) = matrix_4X4<T, ML>(v0, v1, v2, v3);
    } else if (ML == row) {
      /* [row][col] */
      vector_4d<T> v0(
        _v0[0]*rhs[0][0]+_v0[1]*rhs[1][0]+_v0[2]*rhs[2][0]+_v0[3]*rhs[3][0],
        _v0[0]*rhs[0][1]+_v0[1]*rhs[1][1]+_v0[2]*rhs[2][1]+_v0[3]*rhs[3][1],
        _v0[0]*rhs[0][2]+_v0[1]*rhs[1][2]+_v0[2]*rhs[2][2]+_v0[3]*rhs[3][2],
        _v0[0]*rhs[0][3]+_v0[1]*rhs[1][3]+_v0[2]*rhs[2][3]+_v0[3]*rhs[3][3]);
      vector_4d<T> v1(
        _v1[0]*rhs[0][0]+_v1[1]*rhs[1][0]+_v1[2]*rhs[2][0]+_v1[3]*rhs[3][0],
        _v1[0]*rhs[0][1]+_v1[1]*rhs[1][1]+_v1[2]*rhs[2][1]+_v1[3]*rhs[3][1],
        _v1[0]*rhs[0][2]+_v1[1]*rhs[1][2]+_v1[2]*rhs[2][2]+_v1[3]*rhs[3][2],
        _v1[0]*rhs[0][3]+_v1[1]*rhs[1][3]+_v1[2]*rhs[2][3]+_v1[3]*rhs[3][3]);
      vector_4d<T> v2(
        _v2[0]*rhs[0][0]+_v2[1]*rhs[1][0]+_v2[2]*rhs[2][0]+_v2[3]*rhs[3][0],
        _v2[0]*rhs[0][1]+_v2[1]*rhs[1][1]+_v2[2]*rhs[2][1]+_v2[3]*rhs[3][1],
        _v2[0]*rhs[0][2]+_v2[1]*rhs[1][2]+_v2[2]*rhs[2][2]+_v2[3]*rhs[3][2],
        _v2[0]*rhs[0][3]+_v2[1]*rhs[1][3]+_v2[2]*rhs[2][3]+_v2[3]*rhs[3][3]);
      vector_4d<T> v3(
        _v3[0]*rhs[0][0]+_v3[1]*rhs[1][0]+_v3[2]*rhs[2][0]+_v3[3]*rhs[3][0],
        _v3[0]*rhs[0][1]+_v3[1]*rhs[1][1]+_v3[2]*rhs[2][1]+_v3[3]*rhs[3][1],
        _v3[0]*rhs[0][2]+_v3[1]*rhs[1][2]+_v3[2]*rhs[2][2]+_v3[3]*rhs[3][2],
        _v3[0]*rhs[0][3]+_v3[1]*rhs[1][3]+_v3[2]*rhs[2][3]+_v3[3]*rhs[3][3]);
      /* construct matrix using row vectors */
      (*this) = matrix_4X4<T, ML>(v0, v1, v2, v3);
    }
  }

  template <typename T, matrix_layout ML>
  void matrix_4X4<T, ML>::operator*=(const T &rhs)
  {
      _v0 *= rhs;
      _v1 *= rhs; 
      _v2 *= rhs; 
      _v3 *= rhs;
  }

  template <typename U, matrix_layout ML>
  void swap(matrix_4X4<U, ML> &lhs, matrix_4X4<U, ML> &rhs)
  {
    std::swap(lhs[0], rhs[0]);
    std::swap(lhs[1], rhs[1]);
    std::swap(lhs[2], rhs[2]);
    std::swap(lhs[3], rhs[3]);
  }

  /// Arithmetic operators
  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML> operator+(const matrix_4X4<T, ML> &m1, 
    const matrix_4X4<T, ML> &m2)
  {     
    return matrix_4X4<T, ML>(
      m1.vec0() + m2.vec0(),
      m1.vec1() + m2.vec1(),
      m1.vec2() + m2.vec2(),
      m1.vec3() + m2.vec3());
  }

  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML> operator-(const matrix_4X4<T, ML> &m1, 
    const matrix_4X4<T, ML> &m2)
  {
    return matrix_4X4<T, ML>(
      m1.vec0() - m2.vec0(),
      m1.vec1() - m2.vec1(),
      m1.vec2() - m2.vec2(),
      m1.vec3() - m2.vec3());
  }

  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML> operator-(const matrix_4X4<T, ML> &m1)
  {
    return matrix_4X4<T, ML>(-m1.vec0(), -m1.vec1(), -m1.vec2(), -m1.vec3());
  }

  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML> operator*(const T &s, const matrix_4X4<T, ML> &m1)
  {
    return matrix_4X4<T, ML>(
      s * m1.vec0(), 
      s * m1.vec1(), 
      s * m1.vec2(), 
      s * m1.vec3());
  }

  template <typename T, matrix_layout ML>
  matrix_4X4<T, ML> operator*(const matrix_4X4<T, ML> &m1, 
    const matrix_4X4<T, ML> &m2)
  {
    // TODO Implement this by unrolling the loops
  }

  /// Output operators
  template <typename T, matrix_layout ML>
  std::ostream &operator<<(std::ostream &out, const matrix_4X4<T, ML> &rhs)
  {
    if (ML == row) {
      return out << "row matrix" << std::endl << rhs.vec0() << std::endl 
        << rhs.vec1() << std::endl << rhs.vec2() << std::endl << rhs.vec3();
    } else if (ML == column) {
      return out 
        << "colmn matrix" << std::endl
        << "(" 
        << rhs.vec0().x() << ", " << rhs.vec1().x() << ", " 
        << rhs.vec2().x() << ", " << rhs.vec3().x()
        << ")" << std::endl
        << "(" 
        << rhs.vec0().y() << ", " << rhs.vec1().y() << ", " 
        << rhs.vec2().y() << ", " << rhs.vec3().y()
        << ")" << std::endl
        << "(" 
        << rhs.vec0().z() << ", " << rhs.vec1().z() << ", " 
        << rhs.vec2().z() << ", " << rhs.vec3().z()
        << ")" << std::endl
        << "(" 
        << rhs.vec0().w() << ", " << rhs.vec1().w() << ", " 
        << rhs.vec2().w() << ", " << rhs.vec3().w()
        << ")";
    }
  }
}
