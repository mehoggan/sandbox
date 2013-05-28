#ifndef POINT_TESTS
#define POINT_TESTS

#include <cxxtest/TestSuite.h>

#include <types/points/type_point_2d.h>

#include <iostream>
#include <vector>
#include <cassert>

class vector_tests : public CxxTest::TestSuite
{
public:
  void test_point_2d_float() {
    /// Test base constructor
    glext::point_2d<float> p1;
    TS_ASSERT(p1.x() == 0 && p1.y() == 0);
    
    /// Test standard constructor and equivalence operator
    glext::point_2d<float> p2(10.0f, 10.1f);
    TS_ASSERT(p2 == glext::point_2d<float>(10.0f, 10.1f));

    /// Test copy constructor and equivalence operator along with less than or
    /// equal and greater than or equal
    glext::point_2d<float> p3(p2);
    TS_ASSERT(p2 == p3); 
    TS_ASSERT(p2 <= p3); 
    TS_ASSERT(p2 >= p3);

    /// Test assingment operator and not equal operator
    glext::point_2d<float> p4 = p1;
    TS_ASSERT(p4 != p2); 
    TS_ASSERT(p4 == p1); 

    /// Test getters by reference
    glext::point_2d<float> p5;
    float p5x = p5.xref();
    p5x = 4; 
    float p5y = p5.yref();
    p5y = 10;
    TS_ASSERT(p5 == glext::point_2d<float>(0.0f, 0.0f)); 

    /// Test getters by value
  }
};

#endif//
