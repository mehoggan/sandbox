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
#ifndef SHARED_ARRAY_H_INCLUDED
#define SHARED_ARRAY_H_INCLUDED

#include <core/type_traits/convertible.h>
#include <core/ref_count/shared_ptr/shared_count.h>

#include <cassert>

namespace gl_wrapper
{
  namespace ref_count
  {
    /*! \brief class used to allow for shared instance of an array with
     * with ref counting
     */
    template<class T>
    class shared_array
    {
    private:
      /*! \brief class used by shared_array to delete the object pointed to
       */
      struct checked_array_deleter
      {
        void operator()(T *x) const
        {
          typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
          (void)sizeof(type_must_be_complete);
          delete [] x;
        }
      };

      /// typedef to help certain compilers (aka Borland)
      typedef shared_array<T> this_type;

      /// The array pointed to by this class
      T *_px;

      /// Ref. counted class.
      shared_count _pn;

      template<class Y>
      friend class shared_array;

    public:
      /*! \brief default ctor
       */
      shared_array() :
        _px(0),
        _pn()
      {}

      /*! \brief ctor
       */
      template<class Y>
      explicit shared_array(Y *p) :
        _px(p),
        _pn(p, checked_array_deleter())
      {
        type_traits::convertible::is_not_convertible_assert<Y[], T[]>();
      }

      /*! \brief copy ctor of same template type
       */
      shared_array(const shared_array &r) :
        _px(r._px),
        _pn(r._pn)
      {}

      /*! \brief copy ctor for derived/base types.
       */
      template<class Y>
      shared_array(const shared_array<Y> &r) :
        _px(r._px),
        _pn(r._pn)
      {
        type_traits::convertible::is_not_convertible_assert<Y[], T[]>();
      }

      /*! \brief aliasing copy ctor used by the casting functions below
       */
      template<class Y>
      shared_array(const shared_array<Y> &r, T *p) :
        _px(p),
        _pn(r._pn)
      {}

      /*! \brief assignment operator on same template type
       */
      shared_array &operator=(const shared_array &r)
      {
        this_type(r).swap(*this);
        return *this;
      }

      /*! \brief assignment operator on same template type
       */
      template<class Y>
      shared_array & operator=(const shared_array<Y> &r)
      {
        type_traits::convertible::is_not_convertible_assert<Y[], T[]>();

        this_type(r).swap(*this);
        return *this;
      }

      /*! \brief reset the array pointed to by "this" to a nullptr
       */
      void reset()
      {
        this_type().swap(*this);
      }

      /*! \brief reset to a new pointer deleting the memory pointed to by the
       * previous pointer
       */
      template<class Y>
      void reset(Y *p)
      {
        type_traits::convertible::is_not_convertible_assert<Y[], T[]>();

        assert(p == 0 || p != _px );
        this_type(p).swap(*this);
      }

      /*! \brief treat the array like any other array
       */
      T &operator[] (std::ptrdiff_t i) const
      {
        assert(_px != 0);
        assert(i >= 0);
        return _px[i];
      }

      T *get() const
      {
        return _px;
      }

      operator bool () const
      {
        return (_px != 0);
      }

      bool unique() const
      {
        return _pn.unique();
      }

      long use_count() const
      {
        return _pn.use_count();
      }

      void swap(shared_array<T> & other)
      {
        std::swap(_px, other._px);
        _pn.swap(other._pn);
      }
    };

    template<class T>
    inline bool operator==(const shared_array<T> &a, const shared_array<T> &b)
    {
      return a.get() == b.get();
    }

    template<class T>
    inline bool operator!=(const shared_array<T> &a, const shared_array<T> &b)
    {
      return a.get() != b.get();
    }

    template<class T>
    void swap(shared_array<T> &a, shared_array<T> &b)
    {
      a.swap(b);
    }
  }
}
#endif
