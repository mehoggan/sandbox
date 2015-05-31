#ifndef REF_COUNT_SMART_PTR_TESTS
#define REF_COUNT_SMART_PTR_TESTS

#include <cxxtest/TestSuite.h>

#include <algorithm>
#include <cstring>

#include <gl_wrapper.h>

#include <core/ref_count/shared_ptr/shared_ptr.h>
#include <core/ref_count/weak_ptr/weak_ptr.h>

#include <core/ref_count/intrusive_ptr/intrusive_ptr.h>
#include <core/ref_count/intrusive_ptr/ref_counted_base.h>

#include <core/ref_count/shared_array/shared_array.h>

namespace test_detail
{
  class base
  {
  private:
    int m_val;
  public:
    base() :
      m_val(-1)
    {}

    base(int val) :
      m_val(val)
    {}

    int get_val() const
    {
      return m_val;
    }
  };

  class derived : public base
  {
  private:
    int m_dval;

  public:
    derived() :
      base()
    {}

    derived(int val) :
      base(val)
    {}

    void set_dval(int val)
    {
      m_dval = val;
    }

    int get_dval() const
    {
      return m_dval;
    }
  };

  class ref_counted : public gl_wrapper::ref_count::ref_counted_base
  {
  private:
    // Pointer used to test for memory leaks when deleting derived through
    // base pointer.
    int *_val;

  public:
    explicit ref_counted(int val = -1) :
      _val(new int(val))
    {}

    ~ref_counted()
    {
      delete _val;
    }

    int get_val() const
    {
      return *_val;
    }
  };

  class ref_counted_impl : public ref_counted
  {
  private:
    // Pointer used to test for memory leaks
    double *_dval;

  public:
    explicit ref_counted_impl(int val = -1) :
      ref_counted(val),
      _dval(new double(val + 0.1))
    {}

    ~ref_counted_impl()
    {
      delete _dval;
    }

    double get_dval() const
    {
      return *_dval;
    }
  };
}

class ref_count_smart_ptr_tests : public CxxTest::TestSuite
{
public:
  /// Tests for shared_ptr:

  /*! \brief default ctor
   */
  void test_shared_ptr_default_ctor()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr;
    TS_ASSERT(!sptr);
    TS_ASSERT(sptr == 0);
    TS_ASSERT(!sptr.unique());
    TS_ASSERT(sptr.use_count() == 0);
  }

  /*! \brief ctor shared ptr
   */
  void test_shared_ptr_ctor()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived);
    TS_ASSERT(sptr);
    TS_ASSERT(sptr != 0);
    TS_ASSERT(sptr.unique());
    TS_ASSERT(sptr.use_count() == 1);
  }

  /*! \brief copy ctor of same shared_ptr type
   */
  void test_shared_ptr_copy_ctor_same_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(
      new test_detail::base);
    TS_ASSERT(sptr.use_count() == 1);
    gl_wrapper::ref_count::shared_ptr<test_detail::base> csptr(sptr);
    TS_ASSERT(sptr->get_val() == csptr.get()->get_val());
    TS_ASSERT(!sptr.unique());
    TS_ASSERT(!csptr.unique());
    TS_ASSERT(csptr == sptr);
    TS_ASSERT(sptr.use_count() == 2);
    TS_ASSERT(csptr.use_count() == 2);
  }

  /*! \brief copy ctor of different shared_ptr type
   */
  void test_shared_ptr_copy_ctor_different_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived);
    TS_ASSERT(sptr.use_count() == 1);
    gl_wrapper::ref_count::shared_ptr<test_detail::base> csptr(sptr);
    TS_ASSERT(sptr->get_val() == csptr.get()->get_val());
    TS_ASSERT(!sptr.unique());
    TS_ASSERT(!csptr.unique());
    TS_ASSERT(csptr == sptr);
    TS_ASSERT(sptr.use_count() == 2);
    TS_ASSERT(csptr.use_count() == 2);
  }

  /*! \brief test assignment operator of same type
   */
  void test_shared_ptr_assignement_operator_same_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(
      new test_detail::base);
    TS_ASSERT(sptr.use_count() == 1);
    gl_wrapper::ref_count::shared_ptr<test_detail::base> csptr;
    csptr = sptr;
    TS_ASSERT(sptr->get_val() == csptr.get()->get_val());
    TS_ASSERT(!sptr.unique());
    TS_ASSERT(!csptr.unique());
    TS_ASSERT(csptr == sptr);
    TS_ASSERT(sptr.use_count() == 2);
    TS_ASSERT(csptr.use_count() == 2);
  }

  /*! \brief test assignment operator of different type
   */
  void test_shared_ptr_assignement_operator_different_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived);
    TS_ASSERT(sptr.use_count() == 1);
    gl_wrapper::ref_count::shared_ptr<test_detail::base> csptr;
    csptr = sptr;
    TS_ASSERT(sptr->get_val() == csptr.get()->get_val());
    TS_ASSERT(!sptr.unique());
    TS_ASSERT(!csptr.unique());
    TS_ASSERT(csptr == sptr);
    TS_ASSERT(sptr.use_count() == 2);
    TS_ASSERT(csptr.use_count() == 2);
  }

  /*! \brief test reset of a shared pointer
   */
  void test_reset_to_null()
  {
    { // Basic test
      gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
        new test_detail::derived);
      TS_ASSERT(sptr.unique());
      TS_ASSERT(sptr.use_count() == 1);

      // Call copy constructor
      gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr0 = sptr;
      TS_ASSERT(!sptr.unique());
      TS_ASSERT(!sptr0.unique());
      TS_ASSERT(sptr0 == sptr);
      TS_ASSERT(sptr.use_count() == 2);
      TS_ASSERT(sptr0.use_count() == 2);

      sptr.reset();
      TS_ASSERT(!sptr.unique());
      TS_ASSERT(sptr0.unique());
      TS_ASSERT(sptr0 != sptr);
      TS_ASSERT(sptr.use_count() == 0);
      TS_ASSERT(sptr0.use_count() == 1);

      sptr0.reset();
      TS_ASSERT(!sptr.unique());
      TS_ASSERT(!sptr0.unique());
      TS_ASSERT(sptr0 == sptr);
      TS_ASSERT(sptr.use_count() == 0);
      TS_ASSERT(sptr0.use_count() == 0);
    }
  }

  /*! \brief test reset of a shared pointer to a new value
   */
  void test_reset_to_new_pointer()
  {
    { // Same type
      test_detail::derived *original = new test_detail::derived(10);
      gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(original);
      TS_ASSERT(sptr.use_count() == 1);

      test_detail::derived *replace = new test_detail::derived(9);
      sptr.reset(replace);
      TS_ASSERT(sptr.use_count() == 1);

      // Because we shared_ptr does not hold a reference to a pointer
      // we are guaranteed that the memory is deleted but cannot be set
      // to 0
      TS_ASSERT(original != 0);
      TS_ASSERT(sptr->get_val() == 9);
    }

    { // Different type
      test_detail::base *original = new test_detail::base(10);
      gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(original);
      TS_ASSERT(sptr.use_count() == 1);

      test_detail::derived *replace = new test_detail::derived(9);
      sptr.reset(replace);
      TS_ASSERT(sptr.use_count() == 1);

      // Because we shared_ptr does not hold a reference to a pointer
      // we are guaranteed that the memory is deleted but cannot be set
      // to 0
      TS_ASSERT(original != 0);
      TS_ASSERT(sptr->get_val() == 9);
    }
  }

  /*! \brief test that indirection operator behaves as expected
   */
  void test_inderection_operator()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(
      new test_detail::derived(12));

    TS_ASSERT_EQUALS((*sptr).get_val(), 12);
  }

  /*! \brief test that structure dereference operator behaves as expected
   */
  void test_structure_dereference_operator()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(
      new test_detail::derived(12));

    TS_ASSERT_EQUALS(sptr->get_val(), 12);
  }

  /*! \brief test get function (gets value of internal pointer)
   */
  void test_get()
  {
    test_detail::base *ptr = new test_detail::base(20);
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(ptr);

    TS_ASSERT_EQUALS(sptr.get()->get_val(), 20);
    TS_ASSERT_EQUALS(ptr, sptr.get());
  }

  /*! \brief testing cast to boolean
   */
  void test_bool_cast()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr;
    TS_ASSERT(!sptr);

    sptr = gl_wrapper::ref_count::shared_ptr<test_detail::base>(
      new test_detail::base(12));
    TS_ASSERT(sptr);
  }

  /*! \brief test uniqueness of pointer (how many instances are shared)
   */
  void test_unique()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr;
    TS_ASSERT(!sptr.unique());

    sptr = gl_wrapper::ref_count::shared_ptr<test_detail::base>(
      new test_detail::base(12));
    TS_ASSERT(sptr.unique());

    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr0 = sptr;
    TS_ASSERT(!sptr.unique());

    sptr.reset();
    TS_ASSERT(!sptr.unique());
    TS_ASSERT(sptr0.unique());

    sptr0.reset();
    TS_ASSERT(!sptr.unique());
    TS_ASSERT(!sptr0.unique());
  }

  /*! \brief swap two shared pointers
   */
  void test_swap()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> ptr0(
      new test_detail::derived(12));

    gl_wrapper::ref_count::shared_ptr<test_detail::base> ptr1(
      new test_detail::derived(15));

    TS_ASSERT_EQUALS(12, ptr0->get_val());
    TS_ASSERT_EQUALS(15, ptr1->get_val());

    ptr0.swap(ptr1);

    TS_ASSERT_EQUALS(15, ptr0->get_val());
    TS_ASSERT_EQUALS(12, ptr1->get_val());
  }

  /*! \brief owner before
   */
  void test_owner_before()
  {
  }

  struct window
  {
    int handle;
    const char *name;
    union
    {
      int size;
      char data;
    } data;
  };

  /*! \brief test shared_ptr castings
   */
  void test_c_plus_plus_style_castings()
  {
    { // static_cast
      gl_wrapper::ref_count::shared_ptr<window> sptr(new window());
      sptr->handle = 0;
      sptr->data.data = 0;
      sptr->data.size = sizeof(window);
      sptr->name = "Rudolph";
      TS_ASSERT(sptr.use_count() == 1);

      gl_wrapper::ref_count::shared_ptr<void> void_ptr =
        gl_wrapper::static_pointer_cast<void>(sptr);
      TS_ASSERT(sptr.use_count() == 2);
      TS_ASSERT(void_ptr.use_count() == 2);

      TS_ASSERT(!sptr.unique());
      TS_ASSERT(!void_ptr.unique());

      window *win = static_cast<window *>(void_ptr.get());
      TS_ASSERT_EQUALS(win->name, "Rudolph");
    }

    { // const_pointer_cast
      gl_wrapper::ref_count::shared_ptr<const std::string> sptr(
        new std::string("TEST"));
      TS_ASSERT(sptr.use_count() == 1);

      // Will not compile with this
      //sptr->operator[](0) = 'C';

      gl_wrapper::ref_count::shared_ptr<std::string> ncsptr =
        gl_wrapper::const_pointer_cast<std::string>(sptr);
      TS_ASSERT(sptr.use_count() == 2);
      TS_ASSERT(ncsptr.use_count() == 2);

      ncsptr->operator[](0) = 'C';
      TS_ASSERT(strcmp("CEST", sptr->c_str()) == 0);
    }

    { // dynamic_cast and reinterpret cast
      gl_wrapper::ref_count::shared_ptr<test_detail::derived> dsptr(
        new test_detail::derived(30));
      dsptr->set_dval(20);
      TS_ASSERT(dsptr.use_count() == 1);

      gl_wrapper::ref_count::shared_ptr<test_detail::base> bsptr =
        gl_wrapper::dynamic_pointer_cast<test_detail::base>(dsptr);
      TS_ASSERT(dsptr.use_count() == 2);
      TS_ASSERT(bsptr.use_count() == 2);

      TS_ASSERT_EQUALS(dsptr->get_val(), bsptr->get_val());

      gl_wrapper::ref_count::shared_ptr<test_detail::derived> dcsptr =
        gl_wrapper::reinterpret_pointer_cast<test_detail::derived>(bsptr);
      TS_ASSERT(dsptr.use_count() == 3);
      TS_ASSERT(bsptr.use_count() == 3);
      TS_ASSERT(dcsptr.use_count() == 3);

      TS_ASSERT_EQUALS(dsptr->get_val(), dcsptr->get_val());
      TS_ASSERT_EQUALS(dsptr->get_dval(), dcsptr->get_dval());
    }
  }

  /// Tests for weak_ptr:

  /*! \brief default ctor
   */
  void test_weak_ptr_default_ctor()
  {
    gl_wrapper::ref_count::weak_ptr<test_detail::base> wptr;
    TS_ASSERT(wptr.expired());
    TS_ASSERT_EQUALS(0, wptr.use_count());
  }

  /*! \brief create a weak_ptr from a shared_ptr
   */
  void test_create_weak_ptr_from_shared_ptr()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(
      new test_detail::derived(1));

    {
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(1, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::base> wptr(sptr);
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(2, sptr.weak_use_count());
    }
    TS_ASSERT_EQUALS(1, sptr.use_count());
    TS_ASSERT_EQUALS(1, sptr.weak_use_count());

    // After weak pointer goes out of scope our object should still be alive
    TS_ASSERT(sptr);
  }

  /*! \brief create a weak_ptr from a weak_ptr same type
   */
  void test_create_weak_ptr_from_same_weak_ptr_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::base> sptr(
      new test_detail::derived(1));

    {
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(1, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::base> wptr(sptr);
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(2, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::base> cwptr(wptr);
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(3, sptr.weak_use_count());
    }

    TS_ASSERT_EQUALS(1, sptr.use_count());
    TS_ASSERT_EQUALS(1, sptr.weak_use_count());

    // After weak pointers goes out of scope our object should still be alive
    TS_ASSERT(sptr);
  }

  /*! \brief create a weak_ptr from a weak_ptr different type
   */
  void test_create_weak_ptr_from_different_weak_ptr_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived(1));

    {
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(1, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::derived> wptr(sptr);
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(2, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::base> cwptr(wptr);
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(3, sptr.weak_use_count());
    }

    TS_ASSERT_EQUALS(1, sptr.use_count());

    // After weak pointers goes out of scope our object should still be alive
    TS_ASSERT(sptr);
  }


  /*! \brief weak_ptr assignment of same type
   */
  void test_weak_ptr_assignment_of_same_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived(1));

    {
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(1, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::derived> wptr(sptr);
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(2, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::derived> cwptr;
      cwptr = wptr;
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(3, sptr.weak_use_count());
    }

    TS_ASSERT_EQUALS(1, sptr.use_count());

    // After weak pointers goes out of scope our object should still be alive
    TS_ASSERT(sptr);
  }

  /*! \brief weak_ptr assignment of different type
   */
  void test_weak_ptr_assignment_of_different_type()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived(1));

    {
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(1, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::derived> wptr(sptr);
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(2, sptr.weak_use_count());
      gl_wrapper::ref_count::weak_ptr<test_detail::base> cwptr;
      cwptr = wptr;
      TS_ASSERT_EQUALS(1, sptr.use_count());
      TS_ASSERT_EQUALS(3, sptr.weak_use_count());
    }

    TS_ASSERT_EQUALS(1, sptr.use_count());

    // After weak pointers goes out of scope our object should still be alive
    TS_ASSERT(sptr);
  }

  /*! \brief get a shared ptr back from weak_ptr
   */
  void test_lock()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> original_sptr(
      new test_detail::derived(1));
    TS_ASSERT_EQUALS(1, original_sptr.use_count());
    TS_ASSERT_EQUALS(1, original_sptr.weak_use_count());

    gl_wrapper::ref_count::weak_ptr<test_detail::derived> wptr = original_sptr;
    TS_ASSERT_EQUALS(1, original_sptr.use_count());
    TS_ASSERT_EQUALS(2, original_sptr.weak_use_count());
    TS_ASSERT_EQUALS(1, wptr.use_count());

    gl_wrapper::ref_count::shared_ptr<test_detail::derived> locked_sptr =
      wptr.lock();
    TS_ASSERT_EQUALS(2, original_sptr.use_count());
    TS_ASSERT_EQUALS(2, locked_sptr.use_count());
    TS_ASSERT_EQUALS(2, original_sptr.weak_use_count());
    TS_ASSERT_EQUALS(2, wptr.use_count());

    TS_ASSERT_EQUALS(locked_sptr, original_sptr);
  }

  /*! \brief test reset of weak_ptr
   */
  void test_reset_of_weak_ptr()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived(1));
    TS_ASSERT_EQUALS(1, sptr.use_count());
    TS_ASSERT_EQUALS(1, sptr.weak_use_count());

    gl_wrapper::ref_count::weak_ptr<test_detail::derived> wptr(sptr);
    TS_ASSERT_EQUALS(1, sptr.use_count());
    TS_ASSERT_EQUALS(2, sptr.weak_use_count());

    wptr.reset();
    TS_ASSERT_EQUALS(1, sptr.use_count());
    TS_ASSERT_EQUALS(1, sptr.weak_use_count());

    TS_ASSERT(!wptr);
  }

  /*! \brief test swap of weak_ptrs
   */
  void test_swap_weak_ptr()
  {
    gl_wrapper::ref_count::shared_ptr<test_detail::derived> sptr(
      new test_detail::derived(1));

    gl_wrapper::ref_count::weak_ptr<test_detail::derived> wptr(sptr);

    gl_wrapper::ref_count::weak_ptr<test_detail::derived> swap_wptr;

    wptr.swap(swap_wptr);

    TS_ASSERT_EQUALS(1, sptr.use_count());
    TS_ASSERT_EQUALS(2, sptr.weak_use_count());

    TS_ASSERT(!wptr);
    TS_ASSERT_EQUALS(swap_wptr.lock()->get_val(), sptr->get_val());
  }

  /// Tests for intrusive_ptr:

  /*! \brief default constructor for intrusive_ptr
   */
  void test_intrusive_ptr_default_ctor()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr;

    TS_ASSERT(!iptr);
  }

  /*! \brief ctor intrusive ptr
   */
  void test_intrusive_ptr_ctor()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted);

    TS_ASSERT(iptr);
    TS_ASSERT_EQUALS(-1, iptr->get_val());
  }

  /*! \brief test of intrusive_ptr copy constructor on same type
   */
  void test_intrusive_ptr_copy_ctor_of_same_type()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> ciptr(iptr);

    TS_ASSERT_EQUALS(iptr, ciptr);
    TS_ASSERT_EQUALS(10, ciptr->get_val());
    TS_ASSERT_EQUALS(10, iptr->get_val());
  }

  /*! \brief test of intrusive_ptr on copy constructor on different type
   */
  void test_intrusive_ptr_copy_ctor_of_different_type()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted_impl> iptr(
      new test_detail::ref_counted_impl(10));

    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> ciptr(iptr);

    TS_ASSERT_EQUALS(iptr, ciptr);
    TS_ASSERT_EQUALS(10, ciptr->get_val());
    TS_ASSERT_EQUALS(10, iptr->get_val());
    TS_ASSERT_EQUALS(10.1, iptr->get_dval());
  }

  /*! \brief test of intrusive_ptr assignment operator on same type
   */
  void test_intrusive_ptr_assignment_operator_of_same_type()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> ciptr;
    ciptr = iptr;

    TS_ASSERT_EQUALS(iptr, ciptr);
    TS_ASSERT_EQUALS(10, ciptr->get_val());
    TS_ASSERT_EQUALS(10, iptr->get_val());
  }

  /*! \brief test of intrusive_ptr assignment operator on different type
   */
  void test_intrusive_ptr_assignment_operator_of_different_type()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted_impl> iptr(
      new test_detail::ref_counted_impl(10));

    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> ciptr;
    ciptr = iptr;

    TS_ASSERT_EQUALS(iptr, ciptr);
    TS_ASSERT_EQUALS(10, ciptr->get_val());
    TS_ASSERT_EQUALS(10, iptr->get_val());
    TS_ASSERT_EQUALS(10.1, iptr->get_dval());
  }

  /*! \brief test intrusive_ptr assignment operator on same type of pointer
   */
  void test_intrusive_ptr_assignment_operator_of_same_type_pointer()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    TS_ASSERT_EQUALS(10, iptr->get_val());

    test_detail::ref_counted *ptr = new test_detail::ref_counted(11);
    iptr = ptr;

    TS_ASSERT_EQUALS(11, ptr->get_val());
    TS_ASSERT_EQUALS(11, iptr->get_val());

    TS_ASSERT_EQUALS(iptr, ptr);
  }

  /*! \brief test intrusive_ptr assignment operator on different type of pointer
   */
  void test_intrusive_ptr_assignment_operator_of_different_type_pointer()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    TS_ASSERT_EQUALS(10, iptr->get_val());

    test_detail::ref_counted_impl *ptr = new test_detail::ref_counted_impl(11);
    iptr = ptr;

    TS_ASSERT_EQUALS(11, ptr->get_val());
    TS_ASSERT_EQUALS(11, iptr->get_val());

    TS_ASSERT_EQUALS(iptr, ptr);
  }

  /*! \brief test reset or releasing of the pointer
   */
  void test_intrusive_ptr_reset()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    TS_ASSERT(iptr);

    iptr.reset();

    TS_ASSERT(!iptr);
  }

  /*! \brief test reset or releasing of the pointer to a new pointer
   */
  void test_intrusive_ptr_reset_to_new_ptr()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    TS_ASSERT(iptr);
    TS_ASSERT_EQUALS(10, iptr->get_val());

    iptr.reset(new test_detail::ref_counted(12));

    TS_ASSERT(iptr);
    TS_ASSERT_EQUALS(12, iptr->get_val());
  }

  /*! \brief test detachment of ref counted pointer
   */
  void test_intrusive_ptr_detach()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    TS_ASSERT(iptr);
    test_detail::ref_counted *dptr = iptr.detach();
    TS_ASSERT(!iptr);

    // mandatory delete because we own the pointer.
    delete dptr;
  }

  /*! \brief test indirection operator
   */
  void test_intrusive_ptr_indirection_operator()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    TS_ASSERT(iptr);
    TS_ASSERT((*iptr).get_val() == 10);
  }

  /*! \brief test structure dereference operator
   */
  void test_intrusive_ptr_structure_dereference_operator()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(
      new test_detail::ref_counted(10));

    TS_ASSERT(iptr);
    TS_ASSERT(iptr->get_val() == 10);
  }

  /*! \brief test intrusive pointer swap
   */
  void test_intrusive_pointer_swap()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr0(
      new test_detail::ref_counted(10));

    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr1(
      new test_detail::ref_counted(11));

    TS_ASSERT_EQUALS(10, iptr0->get_val());
    TS_ASSERT_EQUALS(11, iptr1->get_val());

    iptr0.swap(iptr1);

    TS_ASSERT_EQUALS(11, iptr0->get_val());
    TS_ASSERT_EQUALS(10, iptr1->get_val());
  }

  /*! \brief we should be able to upcast a derived type to a base class no problem
   */
  void test_intrusive_ptr_static_pointer_cast()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted_impl> diptr(
      new test_detail::ref_counted_impl(10));

    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr =
      gl_wrapper::ref_count::static_intrusive_ptr_cast<
        test_detail::ref_counted>(diptr);

    TS_ASSERT(diptr == iptr);
  }

  /*! \brief we should be able to cast away const on a pointer type
   */
  void test_intrusive_ptr_const_pointer_cast()
  {
    //gl_wrapper::ref_count::intrusive_ptr<const test_detail::ref_counted_impl>
    //  diptr(new test_detail::ref_counted_impl(10));

    //gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted_impl> nciptr =
    //  gl_wrapper::ref_count::const_intrusive_ptr_cast<
    //    test_detail::ref_counted_impl>(diptr);

    //TS_ASSERT(diptr == nciptr);
  }

  /*! \brief we should be able to downcast on pointer types
   */
  void test_intrusive_ptr_dynamic_pointer_cast()
  {
    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted> iptr(new
      test_detail::ref_counted_impl(10));

    gl_wrapper::ref_count::intrusive_ptr<test_detail::ref_counted_impl> idcptr;
    idcptr = gl_wrapper::ref_count::dynamic_intrusive_ptr_cast<
      test_detail::ref_counted_impl>(iptr);

    TS_ASSERT(iptr == idcptr);
    TS_ASSERT_EQUALS(10.1, idcptr->get_dval());
  }

  /// Tests for shared_array:

  /*! \brief test default constructor for shared_array
   */
  void test_shared_array_default_ctor()
  {
    gl_wrapper::ref_count::shared_array<int> sarray;

    TS_ASSERT(!sarray);
  }

  /*! \brief test constructor for shared_array
   */
  void test_shared_array_ctor()
  {
    gl_wrapper::ref_count::shared_array<int> sarray(new int[10]);
    TS_ASSERT(sarray);
    TS_ASSERT_EQUALS(1, sarray.use_count());
  }

  /*! \brief test copy ctor of same type for shared_array
   */
  void test_shared_array_copy_ctor_same_type()
  {
    gl_wrapper::ref_count::shared_array<int> sarray(new int[10]);
    TS_ASSERT_EQUALS(1, sarray.use_count());

    gl_wrapper::ref_count::shared_array<int> csarray(sarray);
    TS_ASSERT_EQUALS(2, sarray.use_count());
    TS_ASSERT_EQUALS(2, csarray.use_count());

    TS_ASSERT_EQUALS(sarray, csarray);
  }

  /*! \brief test copy ctor of different type for shared_array
   */
  void test_shared_array_copy_ctor_different_type()
  {
    gl_wrapper::ref_count::shared_array<test_detail::derived> sarray(
      new test_detail::derived[10]);
    TS_ASSERT_EQUALS(1, sarray.use_count());

    gl_wrapper::ref_count::shared_array<test_detail::base> csarray(sarray);
    TS_ASSERT_EQUALS(2, sarray.use_count());
    TS_ASSERT_EQUALS(2, csarray.use_count());

    TS_ASSERT_EQUALS(sarray, csarray);
  }

  /*! \brief test assignment operator same template type
   */
  void test_shared_array_assignment_operator_same_type()
  {
    gl_wrapper::ref_count::shared_array<int> sarray(new int[12]);

    gl_wrapper::ref_count::shared_array<int> asarray;
    asarray = sarray;

    TS_ASSERT_EQUALS(2, sarray.use_count());
    TS_ASSERT_EQUALS(2, asarray.use_count());
  }

  /*! \brief test copy ctor of different type for shared_array
   */
  void test_shared_array_assignment_operator_different_type()
  {
    gl_wrapper::ref_count::shared_array<test_detail::derived> sarray(
      new test_detail::derived[10]);
    TS_ASSERT_EQUALS(1, sarray.use_count());

    gl_wrapper::ref_count::shared_array<test_detail::base> csarray;
    csarray = sarray;
    TS_ASSERT_EQUALS(2, sarray.use_count());
    TS_ASSERT_EQUALS(2, csarray.use_count());

    TS_ASSERT_EQUALS(sarray, csarray);
  }

  /*! \brief test reset to nullptr
   */
  void test_shared_array_reset_to_null()
  {
    gl_wrapper::ref_count::shared_array<int> sarray(new int[200]);
    TS_ASSERT_EQUALS(1, sarray.use_count());
    TS_ASSERT(sarray.unique());

    sarray.reset();

    TS_ASSERT(!sarray);
    TS_ASSERT_EQUALS(0, sarray.use_count());
    TS_ASSERT(!sarray.unique());
  }

  /*! \brief test reset to another pointer
   */
  void test_shared_array_reset_to_same_and_differente_types()
  {
    { // different
      gl_wrapper::ref_count::shared_array<test_detail::base> csarray(
        new test_detail::base[12]);
      TS_ASSERT_EQUALS(1, csarray.use_count());
      TS_ASSERT(csarray.unique());

      csarray.reset(new test_detail::derived[30]);
      TS_ASSERT_EQUALS(1, csarray.use_count());
      TS_ASSERT(csarray.unique());
    }

    { // same
      gl_wrapper::ref_count::shared_array<int> sarray(new int[20]);
      TS_ASSERT_EQUALS(1, sarray.use_count());
      TS_ASSERT(sarray.unique());

      sarray.reset(new int[30]);
      TS_ASSERT_EQUALS(1, sarray.use_count());
      TS_ASSERT(sarray.unique());
    }

    { // complicated
      gl_wrapper::ref_count::shared_array<int> sarray(new int[20]);
      gl_wrapper::ref_count::shared_array<int> sarray0 = sarray;
      gl_wrapper::ref_count::shared_array<int> sarray1 = sarray;
      gl_wrapper::ref_count::shared_array<int> sarray2 = sarray0;
      TS_ASSERT_EQUALS(4, sarray.use_count());
      TS_ASSERT(!sarray.unique());

      sarray0.reset(new int[30]);

      TS_ASSERT_EQUALS(sarray, sarray1);
      TS_ASSERT_EQUALS(sarray, sarray2);

      TS_ASSERT_DIFFERS(sarray, sarray0);
      TS_ASSERT(sarray0.unique());
    }
  }

  /*! \brief test subscript operator
   */
  void test_shared_array_subscript_operator()
  {
    gl_wrapper::ref_count::shared_array<int> sarray(new int[10]);

    for (unsigned int i = 0; i < 10; ++i) {
      sarray[i] = static_cast<int>(i+ 1);
    }

    for (unsigned int i = 0; i < 10; ++i) {
      TS_ASSERT(sarray[i] == static_cast<int>(i + 1));
    }
  }
};

#endif
