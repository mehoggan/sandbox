#include <types/vectors/type_vector_2d.h>
#include <types/vectors/type_vector_3d.h>
#include <types/vectors/type_vector_4d.h>
#include <types/points/type_point_2d.h>
#include <types/points/type_point_3d.h>
#include <math/vector.h>

#include <types/matrices/type_matrix_4X4.h>

#include <iostream>
#include <cassert>

int main() {
  typedef glext::vector_2d<float> vec2;
  typedef glext::vector_3d<float> vec3;
  typedef glext::vector_4d<float> vec4;
  typedef glext::point_2d<float> point2;
  typedef glext::point_3d<float> point3;
  typedef glext::matrix_4X4<float, glext::column> cmat4;
  typedef glext::matrix_4X4<float, glext::row> rmat4;

  // Constructor Tests
  vec2 v1;
  vec2 v2(1.0f, 2.0f);

  assert(v1 != v2);
  assert(v1 < v2);
  assert(v1 <= v2);

  vec2 v3(v2);
  assert(v3 == v2);
  assert(v3 <= v2);
  assert(v3 >= v1);
  assert(v3 > v1);

  v2 = v1;
  assert(v2 != v3);
  assert(v2 == v1);

  vec2 v4(1.0f, 0.0f);
  vec2 v5(0.0f, 1.0f);

  float theta = glext::angle_between(v4, v5);
  GLEXT_UNUSED_VAR(theta);

  vec3 v6(1.0f, 0.0f, 0.0f);
  vec3 v7(0.0f, 1.0f, 0.0f);
  vec3 v8 = v6.cross(v7);
  GLEXT_UNUSED_VAR(v8);

  v6 = -v6;
  assert(v6.x() == -1.0 && v6.y() == -0.0 && v6.z() == -0.0);

  point2 p1(1.0, 1.0); 
  point2 p2(2.0, 2.0); 
  vec2 v9(p2 - p1);
  GLEXT_UNUSED_VAR(v9);
  
  vec4 vc1(1, 5, 9, 13);
  vec4 vc2(2, 6, 10, 14);
  vec4 vc3(3, 7, 11, 15);
  vec4 vc4(4, 8, 12, 16);
  cmat4 cm(vc1, vc2, vc3, vc4);
  cm *= cm;
  std::cout << cm << std::endl;
  cm = -cm; 
  std::cout << cm << std::endl;
  cm *= 10.0f;
  std::cout << cm << std::endl;
  cm = 10.0f * cm;
  std::cout << cm << std::endl;

  vec4 vr1(1, 2, 3, 4);
  vec4 vr2(5, 6, 7, 8);
  vec4 vr3(9, 10, 11, 12);
  vec4 vr4(13, 14, 15, 16);
  rmat4 rm(vr1, vr2, vr3, vr4);
  rm *= rm;
  std::cout << rm << std::endl;
  rm = -rm;
  std::cout << rm << std::endl;
  rm *= 10.0f;
  std::cout << rm << std::endl;
  rm = 10.0f * rm;
  std::cout << rm << std::endl;
}
