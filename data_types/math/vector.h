#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <types/vectors/type_vector_4d.h>
#include <types/vectors/type_vector_3d.h>
#include <types/vectors/type_vector_2d.h>
#include <types/points/type_point_2d.h>
#include <types/points/type_point_3d.h>
#include <types/points/type_point_4d.h>

#include <cmath>

namespace glext
{
  /* \brief method that returns a normalized 2d vector
   */
  template <typename T>
  vector_2d<T> norm(const vector_2d<T> &v) 
  {
    vector_2d<T> u = v;
    u.normalize();
    return u;
  }

  /* \brief method that returns a normalized 3d vector
   */
  template <typename T>
  vector_3d<T> norm(const vector_3d<T> &v) 
  {
    vector_3d<T> u = v;
    u.normalize();
    return u;
  }

  /* \brief method that returns the angle between two 2d vectors
   */
  template <typename T>
  T angle_between(const vector_2d<T> &v1, const vector_2d<T> &v2)
  {
    vector_2d<T> n1 = norm(v1);
    vector_2d<T> n2 = norm(v2);
    return std::acos(n1.dot(n2)); 
  }
  
  /* \brief method that returns the angle between two 3d vectors
   */
  template <typename T>
  T angle_between(const vector_3d<T> &v1, const vector_3d<T> &v2)
  {
    vector_3d<T> n1 = norm(v1);
    vector_3d<T> n2 = norm(v2);
    return std::acos(n1.dot(n2)); 
  }

  /* \brief given two points it returns a vector_2d
   */
  template <typename T>
  vector_2d<T> operator-(const point_2d<T> &p1, const point_2d<T> &p2)
  {
    return vector_2d<T>(p1.x() - p2.x(), p1.y() - p2.y());
  }

  /* \brief given two points it returns a vector_3d
   */
  template <typename T>
  vector_3d<T> operator-(const point_3d<T> &p1, const point_3d<T> &p2)
  {
    return vector_2d<T>(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
  }

  /* \brief given two points it returns a vector_3d
   */
  template <typename T>
  vector_4d<T> operator-(const point_4d<T> &p1, const point_4d<T> &p2)
  {
    return vector_2d<T>(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z(), 
      p1.w() - p2.w());
  }
}
#endif
