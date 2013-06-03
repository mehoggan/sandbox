#include <types/vectors/type_vector_2d.h>

#include <iostream>
#include <cassert>

int main(int argc, char * argv[]) {
  // Constructor Tests
  glext::vector_2d<float> v1;
  glext::vector_2d<float> v2(1.0f, 2.0f);

  assert(v1 != v2);
  assert(v1 < v2);
  assert(v1 <= v2);

  glext::vector_2d<float> v3(v2);
  assert(v3 == v2);
  assert(v3 <= v2);
  assert(v3 >= v1);
  assert(v3 > v1);

  v2 = v1;
  assert(v2 != v3);
  assert(v2 == v1);

  glext::vector_2d<float> v4(1.0f, 1.0f);
  v4.magnitude();
}
