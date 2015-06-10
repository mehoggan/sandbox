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
#ifndef ATOMICS_H_INCLUDED
#define ATOMICS_H_INCLUDED

#include <platform.h>
#include <core/type_traits/pointers.h>

namespace gl_wrapper
{
  namespace system
  {
    namespace atomics
    {

#if !defined(NDEBUG)
#define compile_time_assert(expr) { char a[(expr) ? 1 : 0]; (void)a; }
#else
#define compile_time_assert(expr) {}
#endif

      template<typename T>
      T fetch_and_add(volatile T *ptr, T val);
      template<typename T>
      T fetch_and_sub(volatile T *ptr, T val);
      template<typename T>
      T fetch_and_or(volatile T *ptr, T val);
      template<typename T>
      T fetch_and_and(volatile T *ptr, T val);
      template<typename T>
      T fetch_and_xor(volatile T *ptr, T val);
      template<typename T>
      T compare_and_swap(volatile T *ptr, T oldval, T newval);
      template<typename T>
      void* compare_and_swap_pointers(T *volatile *ptr, T *oldval, T *newval);
      template<typename T>
      void* swap_pointers(T *volatile *ptr, T *swap);
    }
  }
}

#if defined(__GL_WRAPPER_ANDROID__)
#include <system/atomics/android/atomics.h>
#elif defined(__GL_WRAPPER_CYGWIN__)
#include <system/atomics/cygwin/atomics.h>
#elif defined(__GL_WRAPPER_GNULINUX__)
#include <system/atomics/gnulinux/atomics.h>
#elif defined(__GL_WRAPPER_MACOSX__)
#include <system/atomics/macintosh/atomics.h>
#elif defined(__GL_WRAPPER_WINDOWS__)
#include <system/atomics/win32/atomics.h>
#endif

#endif
