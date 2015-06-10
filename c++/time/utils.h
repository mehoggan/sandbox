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
#ifndef SYSTEM_TIME_UTILS_H_INCLUDED
#define SYSTEM_TIME_UTILS_H_INCLUDED

namespace gl_wrapper
{
  namespace system
  {
    namespace time
    {
      #define compile_time_assert(expr, msg) \
        {char a[(expr && msg) ? 1 : 0]; (void)a;}

      namespace traits
      {
        template<bool B, class T = void>
        struct enable_if_compatible
        {
          typedef T type;
        };

        template<class T>
        struct enable_if_compatible<false, T>
        {
        };
      }

      namespace mpl
      {
        template<long long int N>
        struct abs
        {
          static const long long int value = (N < 0) ? -N : N;
        };

        template<long long int N>
        struct sign
        {
          static const long long int value = (N < 0) ? -1ll : 1ll;
        };

        template<long long int R, long long int S>
        struct min
        {
          static const long long int value = (R < S) ? R : S;
        };

        template<long long int R, long long int S>
        struct max
        {
          static const long long int value = (R > S) ? R : S;
        };

        template<long long int R, long long int S>
        struct gcd
        {
          static const long long int value =
            gcd<min<R, S>::value, max<R, S>::value % min<R, S>::value>::value;
        };

        template<long long int R>
        struct gcd<R, 0>
        {
          static const long long int value = abs<R>::value;
        };
      }
    }
  }
}


#endif
