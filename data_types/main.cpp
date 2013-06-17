#include <types/vectors/type_vector_2d.h>
#include <types/vectors/type_vector_3d.h>
#include <types/vectors/type_vector_4d.h>
#include <types/points/type_point_2d.h>
#include <types/points/type_point_3d.h>
#include <types/points/type_point_4d.h>
#include <types/colors/type_color_rgb.h>
#include <types/colors/type_color_rgba.h>
#include <types/texcoord/type_texcoord_2d.h>
#include <types/texcoord/type_texcoord_3d.h>
#include <types/texcoord/type_texcoord_4d.h>
#include <types/matrices/type_matrix_4X4.h>

#include <math/trig.h>
#include <math/vector.h>

#include <iostream>
#include <cassert>

int main() {
  typedef glext::vector_2d<float> vec2;
  typedef glext::vector_3d<float> vec3;
  typedef glext::vector_4d<float> vec4;
  typedef glext::point_2d<float> point2;
  typedef glext::point_3d<float> point3;
  typedef glext::point_4d<float> point4;
  typedef glext::texcoord_2d<float> tex2;
  typedef glext::texcoord_3d<float> tex3;
  typedef glext::texcoord_4d<float> tex4;
  typedef glext::matrix_4X4<float, glext::column> cmat4;
  typedef glext::matrix_4X4<float, glext::row> rmat4;

  tex2 t0;
  tex2 t1 = t0;
  std::cout << t1 << std::endl;
}
