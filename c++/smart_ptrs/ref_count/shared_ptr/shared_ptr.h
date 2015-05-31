/* Copyright (C)
 *
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef SHARED_PTR_H_INCLUDED
#define SHARED_PTR_H_INCLUDED

#include <core/ref_count/shared_ptr/shared_count.h>
#include <core/ref_count/utils/sp_counted_base.h>
#include <core/type_traits/convertible.h>

namespace gl_wrapper
{
  namespace ref_count
  {
    template<class T> class weak_ptr;
    template<class T> class shared_ptr;

    namespace internal
    {
      template<class Y>
      void shared_pointer_construct(Y *p, shared_count &pn)
      {
        shared_count(p).swap(pn);
      }

      struct nullptr_t
      {
      };
    }

    template<class T>
    class shared_ptr
    {
    public:
      typedef typename sp_element<T>::type element_type;

    private:
      typedef shared_ptr<T> this_type;

      /// This is the pointer that this smart pointer is ref counting
      element_type *_px;

      /// This is the object that keeps track of the reference to _px.
      shared_count _pn;

      /// A weak_ptr and shared_ptr of type Y need to access memebers of type T
      template<class Y> friend class shared_ptr;
      template<class Y> friend class weak_ptr;

    public:
      /*! \brief default constructor which initializes _px to 0 and constructs
       * a shared_count with a reference count set to 0
       */
      shared_ptr() :
        _px(0),
        _pn()
      {}

      /*! \brief constructor which takes in a pointer and keeps hold of it in
       * _px. Then passes in p to shared count to intialize the count to 1
       */
      template<class Y>
      explicit shared_ptr(Y *p) :
        _px(p),
        _pn()
      {
        internal::shared_pointer_construct(p, _pn);
      }

      /*! \brief copy a weak_ptr into a shared ptr implemented in weak_ptr.h
       */
      template<class Y>
      shared_ptr(const weak_ptr<Y> &r);

      /*! \brief copy constructor for shared_ptr of same type
       */
      shared_ptr(const shared_ptr &r) :
        _px(r._px),
        _pn(r._pn)
      {}

      /*! \brief copy constructor for shared_ptr of different type
       */
      template<class Y>
      shared_ptr(const shared_ptr<Y> &r) :
        _px(r._px),
        _pn(r._pn)
      {
        type_traits::convertible::is_not_convertible_assert<Y, T>();
      }

      /*! \brief aliasing (needed for casting operations below)
       */
      template<class Y>
      shared_ptr(const shared_ptr<Y> &r, element_type *p) :
        _px(p),
        _pn(r._pn)
      {}

      /*! \brief assignment operator for shared_ptr of same type
       */
      shared_ptr &operator=(const shared_ptr &r)
      {
        this_type(r).swap(*this);
        return *this;
      }

      /*! \brief assignment operator for shared_ptr of different type
       */
      template<class Y>
      shared_ptr &operator=(const shared_ptr<Y> &r)
      {
        this_type(r).swap(*this);
        return *this;
      }

      /*! \brief create a null ptr if count goes to 0 then underlying pointer
       * is deleted.
       */
      void reset()
      {
        this_type().swap(*this);
      }

      /*! \brief reset the internal pointer of shared_ptr to a new pointer
       * freeing the memory of the previous pointer. It is not set back
       * to zero because we do not have a reference to the pointer
       */
      template<class Y>
      void reset(Y *p)
      {
        type_traits::convertible::is_not_convertible_assert<Y, T>();

        assert(p == 0 || p != _px);
        this_type(p).swap(*this);
      }

      /*! \brief indirection operator
       */
      typename sp_dereference<T>::type operator*() const
      {
        return *_px;
      }

      /*! \brief structure dereference_operator
       */
      typename sp_member_access<T>::type operator->() const
      {
        return _px;
      }

      /*! \brief get access to the underlying pointer
       */
      typename sp_element<T>::type *get() const
      {
        return _px;
      }

      /*! \brief cast to bool operator. Used to check if the internal pointer
       * is 0 or not
       */
      operator bool () const
      {
        return (_px != 0);
      }

      /*! \brief return the number of shared references
       */
      long use_count() const
      {
        return _pn.use_count();
      }

      /*! \brief return the number of weak_ptrs that are currently
       * pointing at the same internal pointer. Note weak count is 1
       * if initialized with non 0 pointer.
       */
      long weak_use_count() const
      {
        return _pn.weak_use_count();
      }

      /*! \brief test to see if the () count are equal to 1 or not. If equal to
       * one then return is true.
       */
      bool unique() const
      {
        return _pn.unique();
      }

      /*! \brief swap the internal pointers inside another shared pointer
       * with the one contained within.
       */
      void swap(shared_ptr &other)
      {
        std::swap(_px, other._px);
        _pn.swap(other._pn);
      }

      /*! \brief
       */
      template<class Y>
      bool owner_before(const shared_ptr<Y> &r) const
      {
        return _pn < r._pn;
      }

      /// Defined in weak_ptr
      template<class Y>
      bool owner_before(const weak_ptr<Y> &rhs) const;

      bool internally_equiv(const shared_ptr &r) const
      {
        return _px == r._px && _pn == r._pn;
      }
    };
  }

  /*! \brief
   */
  template<class T>
  inline bool operator==(const ref_count::shared_ptr<T> &a,
    const ref_count::shared_ptr<T> &b)
  {
    return a.get() == b.get();
  }

  /*! \brief
   */
  template<class T, class U>
  inline bool operator==(const ref_count::shared_ptr<T> &a,
    const ref_count::shared_ptr<U> &b)
  {
    return a.get() == b.get();
  }

  /*! \brief
   */
  template<class T>
  inline bool operator!=(const ref_count::shared_ptr<T> &a,
    const ref_count::shared_ptr<T> &b)
  {
    return a.get() != b.get();
  }

  /*! \brief
   */
  template<class T, class U>
  inline bool operator!=(const ref_count::shared_ptr<T> &a,
    const ref_count::shared_ptr<U> &b)
  {
    return a.get() != b.get();
  }

  /*! \brief
   */
  template<class T>
  inline bool operator==(const ref_count::shared_ptr<T> &p,
    const ref_count::internal::nullptr_t &)
  {
    return p.get() == 0;
  }

  /*! \brief
   */
  template<class T>
  inline bool operator==(const ref_count::internal::nullptr_t &,
    const ref_count::shared_ptr<T> &p)
  {
    return p.get() == 0;
  }

  /*! \brief
   */
  template<class T>
  inline bool operator!=(const ref_count::shared_ptr<T> &p,
    const ref_count::internal::nullptr_t &)
  {
    return p.get() != 0;
  }

  /*! \brief
   */
  template<class T>
  inline bool operator!=(const ref_count::internal::nullptr_t &,
    const ref_count::shared_ptr<T> &p)
  {
    return p.get() != 0;
  }

  /*! \brief
   */
  template<class T, class U>
  inline bool operator<(const ref_count::shared_ptr<T> &a,
    const ref_count::shared_ptr<U> &b)
  {
    return a.owner_before(b);
  }

  /*! \brief
   */
  template<class T>
  inline void swap(ref_count::shared_ptr<T> &a, ref_count::shared_ptr<T> &b)
  {
    a.swap(b);
  }

  /*! \brief given a shared_ptr returns r which now points to a type
   * U instead of T. The reference count is increased before.
   */
  template<class T, class U>
  ref_count::shared_ptr<T> static_pointer_cast(
    const ref_count::shared_ptr<U> &r)
  {
    (void)static_cast<T*>(static_cast<U*>(0));

    typedef typename ref_count::shared_ptr<T>::element_type E;

    E *p = static_cast<E*>(r.get());
    return ref_count::shared_ptr<T>(r, p);
  }

  /*! \brief given a shared_ptr returns r which now points to a type
   * U instead of T. The reference count is increased before. Removes or adds
   * const as a qualifier.
   */
  template<class T, class U>
  ref_count::shared_ptr<T> const_pointer_cast(const ref_count::shared_ptr<U> &r)
  {
    (void)const_cast<T*>(static_cast<U*>(0));

    typedef typename ref_count::shared_ptr<T>::element_type E;

    E * p = const_cast< E* >( r.get() );
    return ref_count::shared_ptr<T>(r, p);
  }

  /*! \brief given a shared_ptr returns r which now points to a type
   * U instead of T. The reference count is increased before.
   */
  template<class T, class U>
  ref_count::shared_ptr<T> dynamic_pointer_cast(
    const ref_count::shared_ptr<U> &r)
  {
    (void)dynamic_cast<T*>(static_cast<U*>(0));

    typedef typename ref_count::shared_ptr<T>::element_type E;

    E *p = dynamic_cast<E*>(r.get());
    return p ? ref_count::shared_ptr<T>(r, p) : ref_count::shared_ptr<T>();
  }

  /*! \brief given a shared_ptr returns r which now points to a type
   * U instead of T. The reference count is increased before.
   */
  template<class T, class U>
  ref_count::shared_ptr<T> reinterpret_pointer_cast(
    const ref_count::shared_ptr<U> &r)
  {
    (void)reinterpret_cast<T*>(static_cast<U*>(0));

    typedef typename ref_count::shared_ptr<T>::element_type E;

    E *p = reinterpret_cast<E*>(r.get());
    return ref_count::shared_ptr<T>(r, p);
  }

  /*! \brief
   */
  template<class T>
  typename ref_count::shared_ptr<T>::element_type *get_pointer(
    const ref_count::shared_ptr<T> &p)
  {
    return p.get();
  }

  template<class Y>
  std::ostream &operator<<(std::ostream & os, const ref_count::shared_ptr<Y> &p)
  {
    return (os << p.get());
  }
}
#endif
