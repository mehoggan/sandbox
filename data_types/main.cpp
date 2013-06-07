#include <types/vectors/type_vector_2d.h>
#include <types/vectors/type_vector_3d.h>
#include <math/vector.h>

#include <iostream>
#include <cassert>

int main() {
  typedef glext::vector_2d<float> vec2;
  typedef glext::vector_3d<float> vec3;

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
  std::cout << "theta is " << theta << std::endl;

  vec3 v6(1.0f, 0.0f, 0.0f);
  vec3 v7(0.0f, 1.0f, 0.0f);
  vec3 v8 = v6.cross(v7);

  std::cout << "<" << v8.x() << ", " << v8.y() << ", " << v8.z() << ">" << 
    std::endl;
}
