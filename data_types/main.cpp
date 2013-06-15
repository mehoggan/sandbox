#include <types/vectors/type_vector_2d.h>
#include <types/vectors/type_vector_3d.h>
#include <types/vectors/type_vector_4d.h>
#include <types/points/type_point_2d.h>
#include <types/points/type_point_3d.h>
#include <math/trig.h>
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

  float cos_0 = glext::cos<float, glext::degrees>(0.0f);
  std::cout << "cos(0) = " << cos_0 << std::endl;
}
