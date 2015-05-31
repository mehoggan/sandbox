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
#include "stdafx.h"

#include <system/atomics/atomics.h>
#include <system/concurrency/mutex/mutex.h>

namespace gl_wrapper
{
  namespace system
  {
    namespace
    {
      const long lock_bit = 31;
      const long lock_flag = 1 << lock_bit;
      const long event_bit = 30;
      const long event_flag = 1 << event_bit;

      /* This function works on the _m variable of the mutex class.
       * It was not added to the class because pthread mutexs don't
       * need it.
       */
      mutex::native_mutex_ptr_t get_event(volatile void* event)
      {
        volatile void* current_event = event;

        if (current_event == 0) {
          const void* new_event = ::CreateEvent(0, false, false, 0);
          if (new_event == 0) {
            throw concurrency_exception("Unable to create event for mutex");
          }

          const void* old_event = atomics::compare_and_swap_pointers(
              (void *volatile *)&event, (void*)0,
              (void*)new_event);

          if (old_event != 0) {
            ::CloseHandle(const_cast<void *>(new_event));
            return const_cast<void *>(old_event);
          } else {
            return const_cast<void *>(new_event);
          }
        }

        return const_cast<void *>(current_event);
      }
    }

    mutex::mutex() :
      _m(0),
      _active_count(0)
    {}

    mutex::~mutex()
    {
      // Store the previous value in old_event, and NULL out _m
      void* const old_event = atomics::swap_pointers((void *volatile *)(&_m),
        (void *)0);

      // If ::SetEvent was called on _m then make sure to release the resources.
      if(old_event) {
          ::CloseHandle(old_event);
      }
    }

    void mutex::lock()
    {
      // If the lock bit was not set before then lock and return;
      if (try_lock()) {
        return;
      }

      long old_count = _active_count;

      /* (Assume we are looking at the active_count???)
       */
      {
        for(;;) {
          // A mutex is considered locked if its bit at the 31st index is set
          const bool was_locked = (old_count & lock_flag) ? true : false;

          // If the mutex was locked then (assume)increment the numeber of
          // active threads
          const long new_count = was_locked ? (old_count + 1) :
            (old_count | lock_flag);

          // If _active_count(old_count) (assume) has not been updated by
          // another thread, then write new_count into _active_count.
          const long current_count = atomics::compare_and_swap(&_active_count,
            old_count, new_count);

          // Current_count is the old value of _active_count.
          if (current_count == old_count) {
            if (was_locked) {
              old_count = new_count;
            }
            break;
          }
          old_count = current_count;
        }
      }

      // If the bit at the 31st index is set.
      if (old_count & lock_flag) {
        bool lock_acquired = false;

        void *sem = get_event(_m);

        do {
          const unsigned wait_abandoned = 0x00000080u;
          unsigned const ret_val(::WaitForSingleObjectEx(sem, INFINITE, 0));
          if (ret_val != 0 || ret_val == wait_abandoned) {
            throw concurrency_exception("Waiting for locked mutex failed.");
          }

          /* (Assume ...)?
           */
          {
            // Clear the bit at the 31st index
            old_count &= ~lock_flag;

            // Set the bit at the 30th index
            old_count |= event_flag;

            for (;;)
            {
              const long new_count = ((old_count & lock_flag) ? old_count :
                ((old_count - 1) | lock_flag)) & ~event_flag;
              const long current_count = atomics::compare_and_swap(
                &_active_count, old_count, new_count);
              if (current_count == old_count) {
                break;
              }
              old_count = current_count;
            }
          }

          lock_acquired = !(old_count & lock_flag);
        } while(!lock_acquired);
      }
    }

    void mutex::unlock()
    {
      // Add 1 << 31 to the current (assume) lock count and store off the
      // previous lock count.
      const long old_active_count = atomics::fetch_and_add(&_active_count,
        lock_flag);

      // If the event bit is not present && the previous lock count > (1 << 31)
      // (assume) that if active_count > 31 then it has been locked once
      if (!(old_active_count & event_flag) && (old_active_count > lock_flag)) {

        // If the event bit was not previously set
        if (!::_interlockedbittestandset(&_active_count, event_bit)) {
          // (assume) Signal to unblock waiting threads (WaitForSingleObject)
          ::SetEvent(get_event(_m));
        }
      }
    }

    bool mutex::try_lock()
    {
      // Return true if the bit at index 31 was not set before. Set
      // the bit at position 31 regardless.
      return !::_interlockedbittestandset(&_active_count, lock_bit);
    }
  }
}
