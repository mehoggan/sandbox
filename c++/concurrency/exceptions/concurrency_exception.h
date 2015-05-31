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
#ifndef CONCURRENCY_EXCEPTION_H_INCLUDED
#define CONCURRENCY_EXCEPTION_H_INCLUDED

#include <system/declspec.h>

namespace gl_wrapper
{
  namespace system
  {
    class SYSTEM_API concurrency_exception
    {
    private:
      /// holds onto the message pased to the constructor
      const char *_msg;

    public:
      /**
       * @brief default constructor
       */
      explicit concurrency_exception(const char *msg);

      /**
       * @brief when exception is thrown returns message passed to the ctor
       */
      const char* what() const throw();
    };
  }
}
#endif
