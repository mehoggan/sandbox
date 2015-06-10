/* Copyright(C)
 *
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0(the "License")
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
#ifndef GNULINUX_ATOMICS_H_INCLUDED
#define GNULINUX_ATOMICS_H_INCLUDED

#include <system/atomics/atomics.h>

namespace gl_wrapper
{
  namespace system
  {
    namespace atomics
    {
      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_add<int>(volatile int *ptr, int value)
      {
        return __sync_fetch_and_add(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_sub<int>(volatile int *ptr, int value)
      {
        return __sync_fetch_and_sub(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_or<int>(volatile int *ptr, int value)
      {
        return __sync_fetch_and_or(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_and<int>(volatile int *ptr, int value)
      {
        return __sync_fetch_and_and(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_xor<int>(volatile int *ptr, int value)
      {
        return __sync_fetch_and_xor(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_add<long>(volatile long *ptr, long value)
      {
        return __sync_fetch_and_add(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_sub<long>(volatile long *ptr, long value)
      {
        return __sync_fetch_and_sub(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_or<long>(volatile long *ptr, long value)
      {
        return __sync_fetch_and_or(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_and<long>(volatile long *ptr, long value)
      {
        return __sync_fetch_and_and(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_xor<long>(volatile long *ptr, long value)
      {
        return __sync_fetch_and_xor(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_add<long long>(volatile long long *ptr,
        long long value)
      {
        return __sync_fetch_and_add(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_sub<long long>(volatile long long *ptr,
        long long value)
      {
        return __sync_fetch_and_sub(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_or<long long>(volatile long long *ptr,
        long long value)
      {
        return __sync_fetch_and_or(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_and<long long>(volatile long long *ptr,
        long long value)
      {
        return __sync_fetch_and_and(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_xor<long long>(volatile long long *ptr,
        long long value)
      {
        return __sync_fetch_and_xor(ptr, value);
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<>
      __inline int compare_and_swap<int>(volatile int *ptr, int oldval,
        int newval)
      {
        return __sync_val_compare_and_swap(ptr, oldval, newval);
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<>
      __inline long compare_and_swap<long>(volatile long *ptr, long oldval,
        long newval)
      {
        return __sync_val_compare_and_swap(ptr, oldval, newval);
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<>
      __inline long long compare_and_swap<long long>(volatile long long *ptr,
        long long oldval, long long newval)
      {
        return __sync_val_compare_and_swap(ptr, oldval, newval);
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<typename T>
      __inline void *compare_and_swap_pointers(T *volatile* ptr, T *oldval,
        T *newval)
      {
        return __sync_val_compare_and_swap((void *volatile *)ptr,
          (void *)oldval, (void *)newval);
      }

      /**
       * Swap the pointers
       */
      template<typename T>
      __inline void* swap_pointers(T *volatile* ptr, T *swap)
      {
        return __sync_val_compare_and_swap((void *volatile *)ptr,
          (void *)(*ptr), (void *)swap);
      }

      /**
       * Full memory barrier
       */
      __inline void memory_barrier()
      {
        __sync_synchronize();
      }
    }
  }
}

#endif
