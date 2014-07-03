#ifndef POINT2D_H_INCLUDED
#define POINT2D_H_INCLUDED

#include <glext.h>

namespace glext 
{
  /*! \class Point 2D class geometry based
   *  \brief This class defines a 2D point_2d
   */
  template <typename T>
  class point_2d
  {
  private:
    /// The first element in the ordered pair
    T _x;
    
    /// The second element in the ordered pair
    T _y;
  
  public:
    /*! \brief default constructor sets both elements using default constructor
     */  
    point_2d();

    /*! \brief constructor sets both elements to the paramaters provided
     */  
    point_2d(const T &x, const T &y);

    /*! \brief copy constructor
     */  
    point_2d(const point_2d &rhs);

    /*! \brief destructor 
     */
    ~point_2d();

    /*! \brief assignment uses copy-swap idiom 
     */ 
    point_2d &operator=(point_2d rhs);

    /*! \brief setter for x element
     */ 
    void x(const T &x);

    /*! \brief setter for y element
     */
    void y(const T &y);

    /*! \brief setter for both x and y element
     */
    void x_and_y(const T &x, const T &y);

    /*! \brief swizzle for both x and y returns a copy of a point_2d
     */
    point_2d xy() const;

    /*! \brief swizzle for x element returns a copy of a point_2d
     */
    point_2d xx() const;

    /*! \brief swizzle for y element returns a copy of a point_2d
     */
    point_2d yy() const;

    /*! \brief swizzle for reverse of y and x returns a copy of a point_2d
     */
    point_2d yx() const;

    /*! \brief getter for x element returns a reference to x of type T
     */
    T& xref();

    /*! \brief getter for y element returns a reference to y of type T
     */
    T& yref();
    
    /*! \brief getter for x element returns a copy of x of type T
     */
    T x() const;

    /*! \brief getter for y element returns a copy of y of type T
     */
    T y() const;
  };

  template <typename U>
  void swap(point_2d<U> &lhs, point_2d<U> &rhs);

  template <typename T>
  bool operator<(const point_2d<T> &lhs, const point_2d<T> &rhs);

  template <typename T>
  bool operator>(const point_2d<T> &lhs, const point_2d<T> &rhs);

  template <typename T>
  bool operator<=(const point_2d<T> &lhs, const point_2d<T> &rhs);

  template <typename T>
  bool operator>=(const point_2d<T> &lhs, const point_2d<T> &rhs);

  template <typename T>
  bool operator==(const point_2d<T> &lhs, const point_2d<T> &rhs);

  template <typename T>
  bool operator!=(const point_2d<T> &lhs, const point_2d<T> &rhs);
}
#include "type_point_2d.inl"
#endif
