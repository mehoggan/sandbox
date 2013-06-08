#ifndef POINT3D_H_INCLUDED
#define POINT3D_H_INCLUDED

#include <glext.h>

namespace glext 
{
  /*! \class Point 3D class geometry based
   *  \brief This class defines a 3D point
   */
  template <typename T>
  class point_3d
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
    point_3d();

    /*! \brief constructor sets three elements to the paramaters provided
     */  
    point_3d(const T &x, const T &y, const T &z);

    /*! \brief copy constructor
     */  
    point_3d(const point_3d &rhs);

    /*! \brief destructor 
     */
    ~point_3d();

    /*! \brief assignment uses copy-swap idiom 
     */ 
    point_3d &operator=(point_3d rhs);

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
  };

  template <typename U>
  void swap(point_3d<U> &lhs, point_3d<U> &rhs);

  template <typename T>
  bool operator<(const point_3d<T> &lhs, const point_3d<T> &rhs);

  template <typename T>
  bool operator>(const point_3d<T> &lhs, const point_3d<T> &rhs);

  template <typename T>
  bool operator<=(const point_3d<T> &lhs, const point_3d<T> &rhs);

  template <typename T>
  bool operator>=(const point_3d<T> &lhs, const point_3d<T> &rhs);

  template <typename T>
  bool operator==(const point_3d<T> &lhs, const point_3d<T> &rhs);

  template <typename T>
  bool operator!=(const point_3d<T> &lhs, const point_3d<T> &rhs);
}
#include "type_point_3d.inl"
#endif
