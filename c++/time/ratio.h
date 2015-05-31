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
#ifndef RATIO_H_INCLUDED
#define RATIO_H_INCLUDED

#include <system/time/utils.h>

namespace gl_wrapper
{
  namespace system
  {
    namespace time
    {
      template<long long int Num, long long int Den = 1ll>
      class ratio
      {
      private:
        compile_time_assert(Den != 0, "ratio division by 0");
        static const long long int abs_num = mpl::abs<N>::value;
        compile_time_assert(abs_num > 0, "ratio numerator out of range");
        static const long long int abs_den = mpl::abs<D>::value;
        compile_time_assert(abs_den > 0, "ratio denominator out of range");
        static const long long int sign_n = mpl::sign<N>::value *
          mpl::sign<D>::value;
        static const long long int gcd = mpl::gcd<abs_num, abs_den>::value;

      public:
        static const long long int num = sign_n * abs_n / gcd;
        static const long long int den = abs_d / gcd;

        typedef ratio<num, den> type;
        typedef rational<long long int> value_type;

        ratio();

        template<long long int Num2, long long int Den2>
        ratio(const ratio<Num2, Den2> &, traits::enable_if_compatible
          <
            (ratio<Num2, Den2>::num == num && ratio<Num2, Den2>::den == den)
          >::type* = 0);

        template<long long int Num2, long long int Den2>
        typename enable_if_compatible
        <
          (ratio<Num2, Den2>::num == num && ratio<Num2, _Den2>::den == den),
          ratio&
        >::type operator=(const ratio<_N2, _D2>&);

        static value_type value();
        value_type operator()() const;
      };
    }
  }
}
#endif

