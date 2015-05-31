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
#ifndef WEAK_PTR_H_INCLUDED
#define WEAK_PTR_H_INCLUDED

#include <core/ref_count/utils/sp_counted_base.h>
#include <core/ref_count/shared_ptr/shared_ptr.h>
#include <core/ref_count/weak_ptr/weak_count.h>

namespace gl_wrapper
{
  namespace ref_count
  {
    template<class T>
    class weak_ptr
    {
    public:
      typedef typename sp_element<T>::type element_type;

    private:
      typedef weak_ptr<T> this_type;
      element_type *_px;

      weak_count _pn;

      template<class Y> friend class weak_ptr;
      template<class Y> friend class shared_ptr;

    public:
      /*! \brief initialize the internal pointer to NULL and create
       * a weak count initialized to 0
       */
      weak_ptr() :
        _px(0),
        _pn()
      {}

      /*! \brief given a shared pointer create a weak_ptr that references
       * the shared_ptr.
       */
      template<class Y>
      weak_ptr(const shared_ptr<Y> &r) :
        _px(r._px),
        _pn(r._pn)
      {}

      /*! \brief given a weak_ptr of same type T construct another that
       * points to the same data
       */
      weak_ptr(const weak_ptr &r) :
        _px(r._px),
        _pn(r._pn)
      {}

      /*! \brief given a weak_ptr of same type T construct another of type Y
       * that points to the same data
       */
      template<class Y>
      weak_ptr(const weak_ptr<Y> &r) :
        _px(r.lock().get()),
        _pn(r._pn)
      {
        type_traits::convertible::is_not_convertible_assert<Y, T>();
      }

      weak_ptr &operator=(const weak_ptr &r)
      {
        _px = r._px;
        _pn = r._pn;
        return *this;
      }

      template<class Y>
      weak_ptr &operator=(const weak_ptr<Y> &r)
      {
        type_traits::convertible::is_not_convertible_assert<Y, T>();

        _px = r.lock().get();
        _pn = r._pn;
        return *this;
      }

      template<class Y>
      weak_ptr &operator=(const shared_ptr<Y> &r)
      {
        _px = r.px;
        _pn = r.pn;

        return *this;
      }

      shared_ptr<T> lock() const
      {
        return shared_ptr<T>(*this);
      }

      long use_count() const
      {
        return _pn.use_count();
      }

      bool expired() const
      {
        return _pn.use_count() == 0;
      }

      bool empty() const
      {
        return _pn.empty();
      }

      void reset()
      {
        this_type().swap(*this);
      }

      void swap(this_type &other)
      {
        std::swap(_px, other._px);
        _pn.swap(other._pn);
      }

      operator bool () const
      {
        return (_px != NULL);
      }

      template<typename Y>
      void internal_aliasing_assign(const weak_ptr<Y> &r, element_type *px2)
      {
        _px = px2;
        _pn = r._pn;
      }

      template<class Y>
      bool owner_before(const weak_ptr<Y> &rhs) const
      {
        return _pn < rhs._pn;
      }

      template<class Y>
      bool owner_before(const shared_ptr<Y>  & rhs) const
      {
        return _pn < rhs._pn;
      }
    };
  }

  /**
   * @brief declared here to prevent circular dependencies
   */
  template<class T>
  template<class Y>
  ref_count::shared_ptr<T>::shared_ptr(const ref_count::weak_ptr<Y> &r) :
    _px(0),
    _pn(r._pn)
  {
    if(!_pn.empty()) {
      _px = r._px;
    }
  }

  /**
   * @brief declared here to prevent circular dependencies
   */
  template<class T>
  template<class Y>
  bool ref_count::shared_ptr<T>::owner_before(
    const ref_count::weak_ptr<Y> &rhs) const
  {
    return _pn < rhs._pn;
  }
}
#endif
