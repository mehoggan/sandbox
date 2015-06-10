#ifndef SYSTEM_MUTEX_TESTS
#define SYSTEM_MUTEX_TESTS

#include <cxxtest/TestSuite.h>

#include <gl_wrapper.h>
#include <system/concurrency/exceptions/concurrency_exception.h>
#include <system/concurrency/mutex/mutex.h>

class mutex_tests : public CxxTest::TestSuite
{
public:
  void test_mutex_ctor()
  {
    try {
      gl_wrapper::system::mutex m;
      TS_ASSERT(true);
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(false);
    }
  }

  void test_lock()
  {
    try {
      gl_wrapper::system::mutex m;
      m.lock();
      TS_ASSERT(true);
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(true); // Can't destroy a mutex that is locked EBUSY
    }

    try {
      gl_wrapper::system::mutex m;
      m.lock();
      m.unlock(); // This time unlock
      TS_ASSERT(true);
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(false);
    }
  }

  void test_unlock()
  {
    try {
      gl_wrapper::system::mutex m;
      m.unlock();
      TS_ASSERT(true); // Windows
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(true); // Posix
    }

    try {
      gl_wrapper::system::mutex m;
      m.lock(); // This time lock first
      m.unlock();
      TS_ASSERT(true);
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(false);
    }
  }

  void test_try_lock()
  {
    try {
      gl_wrapper::system::mutex m;
      m.lock();
      TS_ASSERT(!m.try_lock());
      m.unlock();
      TS_ASSERT(m.try_lock());
      TS_ASSERT(true);
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(false);
    }

    try {
      gl_wrapper::system::mutex m;
      m.lock();
      TS_ASSERT(!m.try_lock());
      m.unlock();
      TS_ASSERT(m.try_lock());
      m.unlock(); // This time unlock
      TS_ASSERT(true);
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(false);
    }
  }

  void test_unlock_lock_unlock()
  {
    try {
      gl_wrapper::system::mutex m;
      //m.unlock(); // On windows this fails by causing a dead lock
      m.lock();
      m.unlock();
      TS_ASSERT(true);
    } catch (gl_wrapper::system::concurrency_exception e) {
      GL_WRAPPER_UNUSED_VAR(e);
      TS_ASSERT(false);
    }
  }
};

#endif
