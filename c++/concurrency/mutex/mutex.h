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
#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED

#include <system/declspec.h>

#include <system/atomics/atomics.h>
#include <system/concurrency/exceptions/concurrency_exception.h>
#include <system/utils/non_copyable.h>

namespace gl_wrapper
{
  namespace system
  {
    class SYSTEM_API mutex : public non_copyable
    {
    public:
      /// abstraction to hide the type of actual object used to implement a
      /// mutex for a given operationg system
      typedef void* native_mutex_ptr_t;

    private:
      /// points to the object created by the operating system to create a
      /// mutex
      native_mutex_ptr_t _m;

      /// used only in windows to keep track of how many threads are currently
      /// locking the mutex
      long _active_count;

    public:
      /**
       * @brief default constructor
       */
      mutex();

      /**
       * @brief default destructor
       */
      ~mutex();

      /**
       * @brief call when you want to acquire a mutex
       *
       * \pre User has not called lock() before. If lock() was called, unlock()
       * must be called before unlock is called.
       */
      void lock();

      /**
       * @brief call when you want to release a mutex
       *
       * \pre Lock is called before unlock. Behavior is undefined otherwise.
       */
      void unlock();

      /**
       * @brief call if you want to check to see if the mutex is locked, if it
       * is not then the lock will be acquired
       *
       * \post The mutex will be acquired if lock was not already acquired,
       * otherwise false will be returned and the lock will be untoched.
       */
      bool try_lock();
    };
  }
}
#endif
