#ifndef COLOR_TESTS
#define COLOR_TESTS

#include <cxxtest/TestSuite.h>

#include <types/color/type_color_rgb.h>
#include <types/color/type_color_rgba.h>

#include <iostream>
#include <vector>
#include <cassert>

class color_tests : public CxxTest::TestSuite
{
public:
  /*! \brief This is a test for all methods in the color_rgba class 
   */
  void test_color_rgba_float() 
  {
    glext::color_rgba<float> c1;
    TS_ASSERT(c1.r() == 0.0f && c1.g() == 0.0f && c1.b() == 0.0f &&
      c1.a() == 0.0f);

    glext::color_rgba<float> c2(1.0f, 0.0f, 0.0f);
    // r = 1.0 b = 0.0 a = 0.0 
    // g = 0.0 g = 0.0 b =
    // b = 0.0 r = 1.0 g = 
    // a = 0.0 a = 0.0 r =
    TS_ASSERT(c2.r() == 1.0f && c2.g() == 0.0f && c2.b() == 0.0f &&
      c2.a() == 0.0f);

    glext::color_rgba<float> c3 = glext::color_rgba(c1);
    TS_ASSERT(c3 == c1);

    c1.r(0.0f);
    c1.g(1.0f);
    c1.b(0.0f);
    c1.a(0.0f);
    TS_ASSERT(c3 != c1);
    TS_ASSERT(c1.r() == 0.0f && c1.g() == 1.0f && c1.b() == 0.0f && 
      c1.a() == 0.0f);

    c3.r_and_g_and_b_and_a(0.0f, 0.0f, 1.0f, 0.0f);
    TS_ASSERT(c3.r() == 0.0f && c3.g() == 0.0f && c3.b() == 1.0f && 
      c3.a() == 0.0f);

    c1.rref() = 0.5f;
    c1.gref() = 0.5f;
    c1.bref() = 0.5f;
    c1.aref() = 0.5f;
    TS_ASSERT(c1.r() == 0.5f && c1.g() == 0.5f && c1.b() == 0.5f && 
        c1.a() == 0.5f);

    c2.to_bgra();
    TS_ASSERT(c2.r() == 0.0f && c2.g() == 0.0f && c2.b() == 1.0f && 
      c2.a() == 0.0f);

    c2.to_abgr();
    TS_ASSERT(c2.r() == 0.0f && c2.g() == 0.0f && c2.b() == 1.0f && 
      c2.a() == 0.0f);
  }

  void test_color_rgb_float() 
  {
  }
};

#endif
