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
 * Unless required by applicable law or agreed to in writting, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef SP_COUNTED_BASE_UTILS_H_INCLUDED
#define SP_COUNTED_BASE_UTILS_H_INCLUDED

#include <system/atomics/atomics.h>
#include <core/ref_count/utils/non_copyable.h>

namespace gl_wrapper
{
  namespace ref_count
  {
    template<class T>
    struct sp_element
    {
      typedef T type;
    };

    class sp_counted_base : public non_copyable
    {
    private:
      long _use_count;

      long _weak_count;

    public:
      sp_counted_base() :
        _use_count(1),
        _weak_count(1)
      {}

      virtual ~sp_counted_base()
      {}

      virtual void dispose() = 0;

      virtual void destroy()
      {
        delete this;
      }

      void release()
      {
        if(system::atomics::fetch_and_sub<long>(&_use_count, 1) == 1) {
          dispose();
          weak_release();
        }
      }

      void weak_release()
      {
        if(system::atomics::fetch_and_sub<long>(&_weak_count, 1) == 1) {
          destroy();
        }
      }

      void weak_add_ref()
      {
        system::atomics::fetch_and_add<long>(&_weak_count, 1);
      }

      void add_ref_copy()
      {
        system::atomics::fetch_and_add<long>(&_use_count, 1);
      }

      bool add_ref_lock()
      {
        for (;;) {
          long tmp = static_cast<long const volatile &>(_use_count);
          if(tmp == 0) {
            return false;
          }

          long cmp = system::atomics::compare_and_swap<long>(
            reinterpret_cast<volatile long *>(&_use_count), tmp, tmp + 1);
          if(cmp == tmp) {
            return true;
          }
        }
      }

      void weak_add_ref_copy() // nothrow
      {
        system::atomics::fetch_and_add<long>(&_weak_count, 1);
      }

      long use_count() const
      {
        return *reinterpret_cast<long const volatile *>(&_use_count);
      }

      long weak_use_count() const
      {
        return *reinterpret_cast<long const volatile *>(&_weak_count);
      }
    };

    template<class X>
    class sp_counted_impl_p : public sp_counted_base
    {
    private:
      X *_px;

      typedef sp_counted_impl_p<X> this_type;

    public:
      explicit sp_counted_impl_p(X *px) :
        _px(px)
      {}

      virtual void dispose()
      {
        delete _px;
        _px = 0;
      }
    };

    template<class X, class D>
    class sp_counted_impl_pd : public sp_counted_base
    {
    private:
      X *_px;
      D _deleter;

      typedef sp_counted_impl_pd<X, D> this_type;

    public:
      explicit sp_counted_impl_pd(X *px) :
        _px(px),
        _deleter()
      {}

      sp_counted_impl_pd(X *px, const D &d) :
        _px(px),
        _deleter(d)
      {}

      virtual void dispose()
      {
        _deleter(_px);
      }
    };

    template<class T>
    struct sp_dereference
    {
      typedef T & type;
    };

    template<>
    struct sp_dereference<void>
    {
      typedef void type;
    };

    template<>
    struct sp_dereference<void const>
    {
      typedef void type;
    };

    template<>
    struct sp_dereference<void volatile>
    {
      typedef void type;
    };

    template<>
    struct sp_dereference<void const volatile>
    {
      typedef void type;
    };

    template<class T>
    struct sp_member_access
    {
      typedef T * type;
    };
  }
}

#endif
