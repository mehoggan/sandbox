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
#ifndef CONVERTIBLE_TYPE_TRAITS_H_INCLUDED
#define CONVERTIBLE_TYPE_TRAITS_H_INCLUDED

namespace gl_wrapper
{
  namespace type_traits
  {
    namespace convertible
    {
      template <class Y, class T>
      struct is_convertible
      {
        typedef char (&yes)[1];
        typedef char (&no)[2];

        static yes f(T*);
        static no f(...);

        enum _vt
        {
          value = sizeof((f)(static_cast<Y*>(0))) == sizeof(yes)
        };
      };

      template <class Y, class T>
      struct is_convertible<Y, T[]>
      {
        enum _vt
        {
          value = false
        };
      };

      template <class Y, class T>
      struct is_convertible<Y[], T[]>
      {
        typedef char (&yes)[1];
        typedef char (&no)[2];

        static yes f(T*);
        static no f(...);

        enum _vt
        {
          value = sizeof((f)(static_cast<Y*>(0))) == sizeof(yes)
        };
      };

      template <class Y, std::size_t N, class T>
      struct is_convertible<Y[N], T[]>
      {
        enum _vt
        {
          value = is_convertible<Y[1], T[1]>::value
        };
      };

      template <class Y, class T> 
      inline void is_not_convertible_assert()
      {
        typedef char tmp[is_convertible<Y, T>::value ? 1 : -1];
        (void)sizeof(tmp); // Unused Variable
      }
    }
  }
}
#endif
