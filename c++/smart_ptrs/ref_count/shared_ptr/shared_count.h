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
#ifndef SHARED_COUNT_HPP_INCLUDED
#define SHARED_COUNT_HPP_INCLUDED

#include <core/ref_count/utils/sp_counted_base.h>

namespace gl_wrapper
{
  namespace ref_count
  {
    class weak_count;

    class shared_count
    {
    private:
      sp_counted_base *_pi;

      friend class weak_count;

    public:
      shared_count() :
        _pi(0)
      {}

      template<class Y>
      explicit shared_count(Y *p) :
        _pi(0)
      {
        try {
          _pi = new sp_counted_impl_p<Y>(p);
        } catch(...) {
          delete p;
          throw "sp bad_alloc()";
        }
      }

      template<class Y, class D>
      shared_count(Y *p, const D &d) :
        _pi(0)
      {
        try {
          _pi = new sp_counted_impl_pd<Y, D>(p);
        } catch (...) {
          d.operator()(p);
          throw "sp bad_alloc()";
        }
      }

      ~shared_count()
      {
        if(_pi != 0) {
          _pi->release();
        }
      }

      shared_count(const shared_count &r) :
        _pi(r._pi)
      {
        if(_pi != 0) {
          _pi->add_ref_copy();
        }
      }

      shared_count(const ref_count::weak_count &r);

      shared_count &operator=(const shared_count &r)
      {
        sp_counted_base *tmp = r._pi;

        if(tmp != _pi) {
          if(tmp != 0) {
            tmp->add_ref_copy();
          }
          if(_pi != 0) {
            _pi->release();
          }
          _pi = tmp;
        }
        return *this;
      }

      long use_count() const
      {
        return _pi != 0 ? _pi->use_count() : 0;
      }

      long weak_use_count() const
      {
        return _pi != 0 ? _pi->weak_use_count() : 0;
      }

      bool unique() const
      {
        return use_count() == 1;
      }

      bool empty() const
      {
        return _pi == 0;
      }

      void swap(shared_count &r)
      {
        sp_counted_base *tmp = r._pi;
        r._pi = _pi;
        _pi = tmp;
      }

      friend bool operator==(const shared_count &a, const shared_count &b)
      {
        return a._pi == b._pi;
      }

      friend bool operator<(const shared_count &a, const shared_count &b)
      {
        return std::less<ref_count::sp_counted_base *>()(a._pi, b._pi);
      }
    };
  }
}
#endif
