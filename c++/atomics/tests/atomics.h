#ifndef SYSTEM_ATOMICS_TESTS
#define SYSTEM_ATOMICS_TESTS

#include <cxxtest/TestSuite.h>

#include <system/atomics/atomics.h>

class system_atomics_tests : public CxxTest::TestSuite
{
public:
  void test_fetch_and_add()
  {
    {
      int count = 0;
      int ret = gl_wrapper::system::atomics::fetch_and_add(&count, 1);
      TS_ASSERT_EQUALS(1, count);
      TS_ASSERT_EQUALS(0, ret);
    }

    {
      long count = 0;
      long ret = gl_wrapper::system::atomics::fetch_and_add(&count, 1l);
      TS_ASSERT_EQUALS(1, count);
      TS_ASSERT_EQUALS(0, ret);
    }

    {
      long long count = 0;
      long long ret = gl_wrapper::system::atomics::fetch_and_add(&count, 1ll);
      TS_ASSERT_EQUALS(1, count);
      TS_ASSERT_EQUALS(0, ret);
    }
  }

  void test_fetch_and_sub()
  {
    {
      int count = 1;
      int ret = gl_wrapper::system::atomics::fetch_and_sub(&count, 1);
      TS_ASSERT_EQUALS(0, count);
      TS_ASSERT_EQUALS(1, ret);
    }

    {
      long count = 1;
      long ret = gl_wrapper::system::atomics::fetch_and_sub(&count, 1l);
      TS_ASSERT_EQUALS(0, count);
      TS_ASSERT_EQUALS(1, ret);
    }

    {
      long long count = 1;
      long long ret = gl_wrapper::system::atomics::fetch_and_sub(&count, 1ll);
      TS_ASSERT_EQUALS(0, count);
      TS_ASSERT_EQUALS(1, ret);
    }
  }

  void test_fetch_and_or()
  {
    {
      int count = 1;
      int ret = gl_wrapper::system::atomics::fetch_and_or(&count, 0x2);
      TS_ASSERT_EQUALS(3, count);
      TS_ASSERT_EQUALS(1, ret);
    }

    {
      long count = 1;
      long ret = gl_wrapper::system::atomics::fetch_and_or(&count, 0x2l);
      TS_ASSERT_EQUALS(3, count);
      TS_ASSERT_EQUALS(1, ret);
    }

    {
      long long count = 1;
      long long ret = gl_wrapper::system::atomics::fetch_and_or(&count, 0x2ll);
      TS_ASSERT_EQUALS(3, count);
      TS_ASSERT_EQUALS(1, ret);
    }
  }

  void test_fetch_and_and()
  {
    {
      int count = 1;
      int ret = gl_wrapper::system::atomics::fetch_and_and(&count, 0x2);
      TS_ASSERT_EQUALS(0, count);
      TS_ASSERT_EQUALS(1, ret);
    }

   {
      long count = 1;
      long ret = gl_wrapper::system::atomics::fetch_and_and(&count, 0x2l);
      TS_ASSERT_EQUALS(0, count);
      TS_ASSERT_EQUALS(1, ret);
    }

   {
      long long count = 1;
      long long ret = gl_wrapper::system::atomics::fetch_and_and(&count, 0x2ll);
      TS_ASSERT_EQUALS(0, count);
      TS_ASSERT_EQUALS(1, ret);
    }
  }

  void test_fetch_and_xor()
  {
    {
      int count = 5;
      int ret = gl_wrapper::system::atomics::fetch_and_xor(&count, 0x6);
      TS_ASSERT_EQUALS(3, count);
      TS_ASSERT_EQUALS(5, ret);
    }

    {
      long count = 5;
      long ret = gl_wrapper::system::atomics::fetch_and_xor(&count, 0x6l);
      TS_ASSERT_EQUALS(3, count);
      TS_ASSERT_EQUALS(5, ret);
    }

    {
      long long count = 5;
      long long ret = gl_wrapper::system::atomics::fetch_and_xor(&count, 0x6ll);
      TS_ASSERT_EQUALS(3, count);
      TS_ASSERT_EQUALS(5, ret);
    }
  }

  void test_compare_and_swap()
  {
    {
      int count = 7;
      int ret = gl_wrapper::system::atomics::compare_and_swap(&count, 7, 8);
      TS_ASSERT_EQUALS(8, count);
      TS_ASSERT_EQUALS(7, ret);
      ret = gl_wrapper::system::atomics::compare_and_swap(&count, 7, 9);
      TS_ASSERT_EQUALS(8, count);
      TS_ASSERT_EQUALS(8, ret);
    }

    {
      long count = 7;
      long ret = gl_wrapper::system::atomics::compare_and_swap(&count, 7l, 8l);
      TS_ASSERT_EQUALS(8, count);
      TS_ASSERT_EQUALS(7, ret);
      ret = gl_wrapper::system::atomics::compare_and_swap(&count, 7l, 9l);
      TS_ASSERT_EQUALS(8, count);
      TS_ASSERT_EQUALS(8, ret);
    }

    {
      long long count = 7;
      long long ret = gl_wrapper::system::atomics::compare_and_swap(&count,
        7ll, 8ll);
      TS_ASSERT_EQUALS(8, count);
      TS_ASSERT_EQUALS(7, ret);
      ret = gl_wrapper::system::atomics::compare_and_swap(&count, 7ll, 9ll);
      TS_ASSERT_EQUALS(8, count);
      TS_ASSERT_EQUALS(8, ret);
    }
  }

  void test_compare_and_swap_pointers()
  {
    int *val_a = new int(10);
    int *val_b = new int(12);
    void *ret = gl_wrapper::system::atomics::compare_and_swap_pointers(&val_a,
      val_a, val_b);
    TS_ASSERT_EQUALS(12, *val_a);
    TS_ASSERT_EQUALS(10, *((int*)ret));
    TS_ASSERT_EQUALS(12, *val_b);
    delete val_a;
    delete (int*)ret;
  }

  void test_swap_pointers()
  {
    int *val_a = new int(10);
    int *val_b = new int(12);
    void *ret = gl_wrapper::system::atomics::swap_pointers(&val_a, val_b);
    TS_ASSERT_EQUALS(12, *val_a);
    TS_ASSERT_EQUALS(10, *((int*)ret));
    TS_ASSERT_EQUALS(12, *val_b);
    delete val_a;
    delete (int*)ret;
  }
};

#endif
