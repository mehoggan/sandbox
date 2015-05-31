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
#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <core/math/numbers.h>

namespace gl_wrapper
{
  namespace system
  {
    namespace time
    {
      template<typename T, class U = T>
      struct less_than_comparable
      {
        template<typename V, typename W>
        friend bool operator<=(const V &x, const W &y);
        template<typename V, typename W>
        friend bool operator<=(const W &x, const V &y);

        template<typename V, typename W>
        friend bool operator>=(const V &x, const W &y);
        template<typename V, typename W>
        friend bool operator>=(const W &x, const V &y);

        template<typename V, typename W>
        friend bool operator>(const V &x, const W &y);

        template<typename V, typename W>
        friend bool operator<(const V &x, const W &y);
      };

      template<class T, class U = T>
      struct equality_comparable
      {
        template<typename V, typename W>
        friend bool operator==(const V &y, const W &x);

        template<typename V, typename W>
        friend bool operator!=(const V &y, const W &x);

        template<typename V, typename W>
        friend bool operator!=(const V &y, const W &x);
      };

      template <class T, class U = T>
      struct addable
      {
        template<typename V, typename W>
        friend V operator+(V lhs, const W& rhs);

        template<typename V, typename W>
        friend V operator+(const V& lhs, W rhs);
      };

      template <class T, class U = T>
      struct subtractable
      {
        template<typename V, typename W>
        friend V operator-(V lhs, const W& rhs);
      };

      template <class T, class U = T>
      struct multipliable
      {
        template<typename V, typename W>
        friend V operator*(V lhs, const W& rhs);

        template<typename V, typename W>
        friend V operator*(const W& lhs, V rhs);
      };

      template <class T, class U = T>
      struct dividable
      {
        template<typename V, typename W>
        friend V operator/(V lhs, const W& rhs);
      };

      template <class T>
      struct incrementable
      {
        template<typename V>
        friend V operator++(V& x, int);
      };

      template <class T>
      struct decrementable
      {
        template<typename V>
        friend V operator--(V& x, int);
      };

      class bad_rational
      {
      private:
        const char* _exception;

      public:
        explicit bad_rational(const char* exception) :
          _exception(exception)
        {
        }

        const char* what() const
        {
          return _exception;
        }
      };

      template<typename IntType>
      class rational :
        less_than_comparable<rational<IntType> >,
        less_than_comparable<rational<IntType>, IntType>,
        equality_comparable<rational<IntType> >,
        equality_comparable<rational<IntType>, IntType>,
        addable<rational<IntType> >,
        addable<rational<IntType>, IntType>,
        subtractable<rational<IntType> >,
        subtractable<rational<IntType>, IntType>,
        multipliable<rational<IntType> >,
        multipliable<rational<IntType>, IntType>,
        dividable<rational<IntType> >,
        dividable<rational<IntType>, IntType>,
        incrementable<rational<IntType> >,
        decrementable<rational<IntType> >
      {
      private:
        IntType _num;
        IntType _den;

      public:
        typedef IntType type;

        rational();
        rational(IntType num);
        rational(IntType num, IntType den);

        rational &operator=(IntType num);
        rational &assign(IntType num, IntType den);

        IntType numerator() const;
        IntType denominator() const;

        rational& operator+= (const rational& r);
        rational& operator+= (IntType i);
        rational& operator-= (const rational& r);
        rational& operator-= (IntType i);
        rational& operator*= (const rational& r);
        rational& operator*= (IntType i);
        rational& operator/= (const rational& r);
        rational& operator/= (IntType i);

        const rational& operator++();
        const rational& operator--();

        bool operator!() const;

        bool operator< (const rational& r) const;
        bool operator== (const rational& r) const;

        bool operator< (IntType i) const;
        bool operator> (IntType i) const;
        bool operator== (IntType i) const;

      private:
        void normalize();
      };
    }
  }
}
#include "rational.inl"
#endif
