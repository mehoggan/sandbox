#ifndef VERTEX_BUFFER_TESTS
#define VERTEX_BUFFER_TESTS

#include <cxxtest/TestSuite.h>

#include <system/concurrency/exceptions/concurrency_exception.h>
#include <string.h>

namespace internal
{
  void throws_concurrency_exception()
  {
    throw gl_wrapper::system::concurrency_exception("thrown");
  }
}

class device_context_tests : public CxxTest::TestSuite
{
public:
  void test_concurrency_exception()
  {
    try {
      internal::throws_concurrency_exception();
      TS_ASSERT(false);
    } catch (gl_wrapper::system::concurrency_exception& e) {
      TS_ASSERT(strcmp("thrown", e.what()) == 0);
    }
  }
};

#endif
