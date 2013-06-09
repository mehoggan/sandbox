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
  typedef glext::point_2d<float> point2;
  typedef glext::point_3d<float> point3;
  typedef glext::matrix_4X4<float> mat4;

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
  
  mat4 A(glext::identity);
  mat4 B(glext::identity);
  mat4 C = A + B;
  std::cout << C << std::endl;
}
