#include <types/points/type_point_2d.h>
#include <cassert>

int main(int argc, char * argv[]) {
  // Constructor Tests
  glext::point_2d<float> p1;
  glext::point_2d<float> p2(1.0f, 2.0f);

  assert(p1 != p2);
  assert(p1 < p2);
  assert(p1 <= p2);

  glext::point_2d<float> p3(p2);
  assert(p3 == p2);
  assert(p3 <= p2);
  assert(p3 >= p1);
  assert(p3 > p1);

  p2 = p1;
  assert(p2 != p3);
  assert(p2 == p1);
}
