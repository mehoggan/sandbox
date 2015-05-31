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
#ifndef WEAK_COUNT_H_INCLUDED
#define WEAK_COUNT_H_INCLUDED

#include <core/ref_count/utils/sp_counted_base.h>
#include <core/ref_count/shared_ptr/shared_count.h>

namespace gl_wrapper
{
  namespace ref_count
  {
    class weak_count
    {
    private:
      sp_counted_base *_pi;

      friend class shared_count;

    public:
      weak_count() :
        _pi(0)
      {}

      ~weak_count()
      {
        if (_pi != 0) {
          _pi->weak_release();
        }
      }

      weak_count(const shared_count &r) :
      _pi(r._pi)
      {
        if (_pi != 0) {
          _pi->weak_add_ref();
        }
      }

      weak_count(const weak_count &r) :
      _pi(r._pi)
      {
        if (_pi != 0) {
          _pi->weak_add_ref();
        }
      }

      weak_count &operator=(const shared_count &r)
      {
        sp_counted_base *tmp = r._pi;

        if(tmp != _pi) {
          if(tmp != 0) {
            tmp->weak_add_ref();
          }

          if(_pi != 0) {
            _pi->weak_release();
          }

          _pi = tmp;
        }

        return *this;
      }

      weak_count &operator=(const weak_count &r)
      {
        sp_counted_base *tmp = r._pi;

        if(tmp != _pi) {
          if(tmp != 0) {
            tmp->weak_add_ref();
          }
          if(_pi != 0) {
            _pi->weak_release();
          }
          _pi = tmp;
        }

        return *this;
      }

      void swap(weak_count &r)
      {
        sp_counted_base *tmp = r._pi;
        r._pi = _pi;
        _pi = tmp;
      }

      long use_count() const
      {
        return _pi != 0 ? _pi->use_count() : 0;
      }

      bool empty() const
      {
        return _pi == 0;
      }

      friend bool operator==(const weak_count &a, const weak_count &b)
      {
        return a._pi == b._pi;
      }

      friend bool operator<(const weak_count &a, const weak_count &b)
      {
        return std::less<ref_count::sp_counted_base *>()(a._pi, b._pi);
      }
    };
  }

  /**
   * @brief copy ctor defined here to prevent circular dependencies
   */
  ref_count::shared_count::shared_count(const ref_count::weak_count &r) :
    _pi(r._pi)
  {
    if(_pi != 0 && !_pi->add_ref_lock()) {
      _pi = 0;
    }
  }
}
#endif
