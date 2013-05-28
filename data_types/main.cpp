#include <types/type_point_2d.h>
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

  // Swizzle Tests
  glext::point_2d<float> p4(10.4, 10.3);
  glext::point_2d<float> p5(10.3, 10.4);
  glext::point_2d<float> p6(10.4, 10.4);
  glext::point_2d<float> p7(p6.xx());
  assert(p4 == p5.yx());
  assert(p4.xx() == p6);
  assert(p6.xy() == p6.yx());
}
