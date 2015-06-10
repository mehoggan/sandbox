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

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include <system/concurrency/mutex/mutex.h>

namespace gl_wrapper
{
  namespace system
  {
    mutex::mutex() :
      _m(NULL),
      _active_count(0)
    {
      void *&tmp = const_cast<void *&>(_m);
      tmp = malloc(sizeof(pthread_mutex_t));
      pthread_mutex_t *m = static_cast<pthread_mutex_t *>(tmp);
      const int res = pthread_mutex_init(m, NULL);
      if (res) {
        throw concurrency_exception("ERROR: mutex() -- Could not obtain "
          "resources.");
      }
    }

    mutex::~mutex()
    {
      void *&tmp = const_cast<void *&>(_m);
      pthread_mutex_t *m = static_cast<pthread_mutex_t *>(tmp);
      const int dres = pthread_mutex_destroy(m);
      // Calls to unlock without a lock will leave the mutex busy
      if (dres) {

        if (dres == EBUSY) { // TODO: Code clean up remove
          printf("__lock %d, __count %d, __owner %d, __nusers %d, __kind %d\n",
            m->__data.__lock,
            m->__data.__count,
            m->__data.__owner,
            m->__data.__nusers,
            m->__data.__kind,
            m->__data.__spins);
        } else {
          free(tmp);
          throw concurrency_exception("ERROR: ~mutex() -- Could not destroy "
            "resources");
        }
      }
      free(tmp);
    }

    void mutex::lock()
    {
      void *&tmp = const_cast<void *&>(_m);
      pthread_mutex_t *m = static_cast<pthread_mutex_t *>(tmp);
      const int res = pthread_mutex_lock(m);
      if (res) {
        throw concurrency_exception("ERROR: pthread_mutex_lock() -- Could not "
          "lock mutex");
      }
    }

    void mutex::unlock()
    {
      void *&tmp = const_cast<void *&>(_m);
      pthread_mutex_t *m = static_cast<pthread_mutex_t *>(tmp);
      const int res = pthread_mutex_unlock(m);
      if (res) {
        throw concurrency_exception("ERROR: pthread_mutex_unlock() -- "
          "Could not unlock_mutex.");
      }
    }

    bool mutex::try_lock()
    {
      void *&tmp = const_cast<void *&>(_m);
      pthread_mutex_t *m = static_cast<pthread_mutex_t *>(tmp);
      int res = -1;
      do {
        res = pthread_mutex_trylock(m);
      } while (res == EINTR);

      if (res == EBUSY) {
        return false;
      }

      return !res;
    }
  }
}
