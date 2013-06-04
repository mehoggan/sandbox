#ifndef POINT2D_H_INCLUDED
#define POINT2D_H_INCLUDED

#include <glext.h>
#include <math/sqrt.h>

namespace glext 
{
  /*! \class Point 3D class geometry based
   *  \brief This class defines a 3D vector
   */
  template <typename T>
  class vector_3d
  {
  private:
    /// The first element in the ordered pair
    T _x;
    
    /// The second element in the ordered pair
    T _y;
 
    /// The third element in the ordered pair
    T _z;

  public:
    /*! \brief default constructor sets three elements using default constructor
     */  
    vector_3d();

    /*! \brief constructor sets three elements to the paramaters provided
     */  
    vector_3d(const T &x, const T &y, const T &z);

    /*! \brief copy constructor
     */  
    vector_3d(const vector_3d &rhs);

    /*! \brief destructor 
     */
    ~vector_3d();

    /*! \brief assignment uses copy-swap idiom 
     */ 
    vector_3d &operator=(vector_3d rhs);

    /*! \brief setter for x element
     */ 
    void x(const T &x);

    /*! \brief setter for y element
     */
    void y(const T &y);

    /*! \brief setter for z element
     */
    void z(const T &z);

    /*! \brief setter for three elements x and y and z 
     */
    void x_and_y_and_z(const T &x, const T &y, const T &z);

    /*! \brief getter for x element returns a reference to x of type T
     */
    T& xref();

    /*! \brief getter for y element returns a reference to y of type T
     */
    T& yref();

    /*! \brief getter for z element returns a reference to z of type T
     */
    T& zref();

    /*! \brief getter for x element returns a copy of x of type T
     */
    T x() const;

    /*! \brief getter for y element returns a copy of y of type T
     */
    T y() const;

    /*! \brief getter for z element returns a copy of z of type T
     */
    T z() const;

    /*! \brief get the magnitude of a 3d vector
     */
    T magnitude() const;
    
    /*! \brief normalize the instace of this vector
     */
    void normalize();

    /*! \brief add a vector to this vector
     */
    void operator+=(const vector_2d<T> &rhs);

    /*! \brief subtract a vector from this vector
     */
    void operator-=(const vector_2d<T> &rhs);

    /*! \brief scale this vector by a constant T
     */
    void operator*=(const T &rhs);
  };

  template <typename U>
  void swap(vector_3d<U> &lhs, vector_3d<U> &rhs);
 
  /// Comparison/Relational operators
  template <typename T>
  bool operator<(const vector_3d<T> &lhs, const vector_3d<T> &rhs);

  template <typename T>
  bool operator>(const vector_3d<T> &lhs, const vector_3d<T> &rhs);

  template <typename T>
  bool operator<=(const vector_3d<T> &lhs, const vector_3d<T> &rhs);

  template <typename T>
  bool operator>=(const vector_3d<T> &lhs, const vector_3d<T> &rhs);

  template <typename T>
  bool operator==(const vector_3d<T> &lhs, const vector_3d<T> &rhs);

  template <typename T>
  bool operator!=(const vector_3d<T> &lhs, const vector_3d<T> &rhs);

  /// Arithmetic operators
  template <typename T>
  vector_3d<T> operator+(const vector_3d<T> &v1, const vector_3d<T> &v3);

  template <typename T>
  vector_3d<T> operator-(const vector_3d<T> &v1, const vector_3d<T> &v3);

  template <typename T>
  vector_3d<T> operator-(const vector_3d<T> &v1);

  template <typename T>
  vector_3d<T> operator*(const T &s, const vector_3d<T> &v1);
}
#include "type_vector_3d.inl"
#endif
