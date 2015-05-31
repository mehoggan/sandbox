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
#ifndef REF_COUNTED_H_INCLUDED
#define REF_COUNTED_H_INCLUDED

#include <core/ref_count/intrusive_ptr/intrusive_ptr.h>
#include <core/ref_count/utils/non_copyable.h>
#include <core/type_traits/convertible.h>
#include <system/atomics/atomics.h>

namespace gl_wrapper
{
  namespace ref_count
  {
    class ref_counted_base : public non_copyable
    {
    private:
      long _use_count;

    public:
      ref_counted_base() :
        _use_count(0)
      {}

      virtual ~ref_counted_base()
      {}

      friend void intrusive_ptr_add_ref(ref_counted_base *obj)
      {
        if (obj) {
          system::atomics::fetch_and_add<long>(&obj->_use_count, 1);
        }
      }

      friend void intrusive_ptr_release(ref_counted_base *obj)
      {
        if (obj) {
          if(system::atomics::fetch_and_sub<long>(&obj->_use_count, 1) == 1) {
            delete obj;
          }
        }
      }
    };
  }
}
#endif