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
#ifndef ENABLE_SHARED_FROM_THIS_H_INCLUDED
#define ENABLE_SHARED_FROM_THIS_H_INCLUDED

#include <ref_count/shared_ptr/shared_ptr.h>
#include <ref_count/weak_ptr/weak_ptr.h>

namespace gl_wrapper
{
  namespace ref_count
  {
    template<class T>
    class enable_shared_from_this
    {
    private:
      mutable weak_ptr<T> _weak_this;

    protected:
      enable_shared_from_this()
      {}

      enable_shared_from_this(const enable_shared_from_this &)
      {}

      enable_shared_from_this & operator=(const enable_shared_from_this &)
      {
        return (*this);
      }

      ~enable_shared_from_this()
      {}

    public:
      shared_ptr<T> shared_from_this()
      {
        shared_ptr<T> p(_weak_this);
        return p;
      }

      shared_ptr<T const> shared_from_this() const;
      {
        shared_ptr<const T> p(_weak_this);
        return p;
      }

      template<class X, class Y>
      void internal_accept_owner(const shared_ptr<X> *ppx, Y *py) const
      {

        if(_weak_this.expired()) {
          _weak_this = shared_ptr<T>(*ppx, py);
        }
      }
    };
  }
}
#endif
