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
#ifndef WIN32_ATOMICS_H_INCLUDED
#define WIN32_ATOMICS_H_INCLUDED

#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>

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
        compile_time_assert(sizeof(long) == sizeof(int));
        return InterlockedExchangeAdd(reinterpret_cast<volatile long *&>(ptr),
          static_cast<long>(value));
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_sub<int>(volatile int *ptr, int value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return InterlockedExchangeAdd(reinterpret_cast<volatile long *&>(ptr),
          static_cast<long>(-value));
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_or<int>(volatile int *ptr, int value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return _InterlockedOr(reinterpret_cast<volatile long *&>(ptr),
          static_cast<long>(value));
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_and<int>(volatile int *ptr, int value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return _InterlockedAnd(reinterpret_cast<volatile long *&>(ptr),
          static_cast<long>(value));
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline int fetch_and_xor<int>(volatile int *ptr, int value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return _InterlockedXor(reinterpret_cast<volatile long *&>(ptr),
          static_cast<long>(value));
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_add<long>(volatile long *ptr, long value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return InterlockedExchangeAdd(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_sub<long>(volatile long *ptr, long value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return InterlockedExchangeAdd(ptr, -value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_or<long>(volatile long *ptr, long value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return _InterlockedOr(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_and<long>(volatile long *ptr, long value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return _InterlockedAnd(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long fetch_and_xor<long>(volatile long *ptr, long value)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return _InterlockedXor(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_add<long long>(volatile long long *ptr,
        long long value)
      {
        return InterlockedExchangeAdd64(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_sub<long long>(volatile long long *ptr,
        long long value)
      {
        return InterlockedExchangeAdd64(ptr, -value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_or<long long>(volatile long long *ptr,
        long long value)
      {
        return InterlockedOr64(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_and<long long>(volatile long long *ptr,
        long long value)
      {
        return InterlockedAnd64(ptr, value);
      }

      /**
       * Returns the previous value that had been in memory
       */
      template<>
      __inline long long fetch_and_xor<long long>(volatile long long *ptr,
        long long value)
      {
        return InterlockedXor64(ptr, value);
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<>
      __inline int compare_and_swap<int>(volatile int *ptr, int oldval, int newval)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return InterlockedCompareExchange(reinterpret_cast<volatile long *>(ptr),
          static_cast<int>(newval), static_cast<int>(oldval));
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<>
      __inline long compare_and_swap<long>(volatile long *ptr, long oldval,
        long newval)
      {
        compile_time_assert(sizeof(long) == sizeof(int));
        return InterlockedCompareExchange(ptr, newval, oldval);
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<>
      __inline long long compare_and_swap<long long>(volatile long long *ptr,
        long long oldval, long long newval)
      {
        return InterlockedCompareExchange64(ptr, newval, oldval);
      }

      /**
       * If the current value of *ptr is oldval, then write newval into *ptr
       */
      template<typename T>
      __inline void *compare_and_swap_pointers(T *volatile *ptr, T *oldval,
        T *newval)
      {
        return InterlockedCompareExchangePointer((void *volatile *)ptr,
          (void *)newval, (void *)oldval);
      }

      /**
       * Swap the pointers
       */
      template<typename T>
      __inline void* swap_pointers(T *volatile *ptr, T *swap)
      {
        return InterlockedExchangePointer((void *volatile *)ptr, (void *)swap);
      }

      /**
       * Full memory barrier
       */
      __inline void memory_barrier()
      {
        MemoryBarrier();
      }
    }
  }
}

#endif
