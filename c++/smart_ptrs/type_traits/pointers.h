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
#ifndef POINTER_TYPE_TRAITS_H_INCLUDED
#define POINTER_TYPE_TRAITS_H_INCLUDED

namespace type_traits
{
  namespace pointers
  {
    enum enum_pointer_size
    {
      e0bit = 0,
      e8bit = 1,
      e16bit = 2,
      e32bit = 4,
      e64bit = 8
    };

    template <typename T>
    struct is_pointer
    {
      static const bool value = false;
    };

    template <typename T>
    struct is_pointer<T*>
    {
      static const bool value = false;
    };

    template <typename T>
    struct pointer_size
    {
      static const enum_pointer_size value =
        (sizeof(T*) == 1) ? e8bit :
        (sizeof(T*) == 2) ? e16bit :
        (sizeof(T*) == 4) ? e32bit :
        (sizeof(T*) == 8) ? e64bit : e0bit;
    };

  }
}
#endif
