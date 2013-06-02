#ifndef POINT2D_H_INCLUDED
#define POINT2D_H_INCLUDED

#include <glext.h>
#include <types/type_point_2d.h>

namespace glext 
{
  /*! \class Point 3D class geometry based
   *  \brief This class defines a 3D point
   */
  template <typename T>
  class point_4d
  {
  private:
    /// The first element in the ordered pair
    T _x;
    
    /// The second element in the ordered pair
    T _y;
 
    /// The third element in the ordered pair
    T _z;

    /// The fourth element in the ordered pair
    T _w;

  public:
    /*! \brief default constructor sets three elements using default constructor
     */  
    point_4d();

    /*! \brief constructor sets three elements to the paramaters provided
     */  
    point_4d(const T &x, const T &y, const T &z, const T &w);

    /*! \brief copy constructor
     */  
    point_4d(const point_4d &rhs);

    /*! \brief destructor 
     */
    ~point_4d();

    /*! \brief assignment uses copy-swap idiom 
     */ 
    point_4d &operator=(point_4d rhs);

    /*! \brief setter for x element
     */ 
    void x(const T &x);

    /*! \brief setter for y element
     */
    void y(const T &y);

    /*! \brief setter for z element
     */
    void z(const T &z);

    /*! \brief setter for z element
     */
    void w(const T &w);

    /*! \brief setter for three elements x and y and z 
     */
    void x_and_y_and_z_and_w(const T &x, const T &y, const T &z, const T &w);

    /*! \brief getter for x element returns a reference to x of type T
     */
    T& xref();

    /*! \brief getter for y element returns a reference to y of type T
     */
    T& yref();

    /*! \brief getter for z element returns a reference to z of type T
     */
    T& zref();

    /*! \brief getter for w element returns a reference to w of type T
     */
    T& wref();

    /*! \brief getter for x element returns a copy of x of type T
     */
    T x() const;

    /*! \brief getter for y element returns a copy of y of type T
     */
    T y() const;

    /*! \brief getter for z element returns a copy of z of type T
     */
    T z() const;
    
    /*! \brief getter for w element returns a copy of w of type T
     */
    T w() const;
  };

  template <typename U>
  void swap(point_4d<U> &lhs, point_4d<U> &rhs);

  template <typename T>
  bool operator<(const point_4d<T> &lhs, const point_4d<T> &rhs);

  template <typename T>
  bool operator>(const point_4d<T> &lhs, const point_4d<T> &rhs);

  template <typename T>
  bool operator<=(const point_4d<T> &lhs, const point_4d<T> &rhs);

  template <typename T>
  bool operator>=(const point_4d<T> &lhs, const point_4d<T> &rhs);

  template <typename T>
  bool operator==(const point_4d<T> &lhs, const point_4d<T> &rhs);

  template <typename T>
  bool operator!=(const point_4d<T> &lhs, const point_4d<T> &rhs);
}
#include "type_point_4d.inl"
#endif
