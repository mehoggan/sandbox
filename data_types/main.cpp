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
#include <renderers/types/renderer_data_1d.h>
#include <renderers/types/renderer_data_2d.h>
#include <renderers/types/renderer_data_3d.h>
#include <renderers/types/renderer_data_4d.h>
#include <renderers/types/interleaved_data_2d.h>
#include <renderers/types/interleaved_data_3d.h>
#include <renderers/types/interleaved_data_4d.h>

#include <renderers/batch_interleaved_renderer.h>

#include <math/trig.h>
#include <math/vector.h>

#include <iostream>
#include <cassert>

int main() {
  typedef glext::point_2d<float> point2;
  typedef glext::color_rgb<float> color3;

  std::vector<glext::interleaved_datum_2d<point2, color3> > data;
  glext::interleaved_datum_2d<point2, color3> vertex1(
    point2(0.0f, 0.0f),
    color3(1.0f, 0.0f, 0.0f));
  glext::interleaved_datum_2d<point2, color3> vertex2(
    point2(1.0f, 0.0f),
    color3(1.0f, 0.0f, 0.0f));
  glext::interleaved_datum_2d<point2, color3> vertex3(
    point2(1.0f, 1.0f),
    color3(1.0f, 0.0f, 0.0f));
  glext::interleaved_datum_2d<point2, color3> vertex4(
    point2(0.0f, 1.0f),
    color3(1.0f, 0.0f, 0.0f));
  data.push_back(vertex1);
  data.push_back(vertex2);
  data.push_back(vertex3);
  data.push_back(vertex4);
  glext::interleaved_data_2d<point2, color3> verticies(data);

  glext::batch_interleaved_renderer<
    glext::interleaved_data_2d<point2, color3> > renderer;
  renderer.load_data(verticies);
  renderer.draw_data();
  renderer.modify_data(verticies);
  renderer.destroy_resources();
}
