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
namespace gl_wrapper
{
  namespace system
  {
    namespace time
    {
      template<typename V, typename W>
      bool operator<=(const V &x, const W &y)
      {
        return !static_cast<bool>(x > y);
      }

      template<typename V, typename W>
      bool operator<=(const W &x, const V &y)
      {
        return !static_cast<bool>(y < x);
      }

      template<typename V, typename W>
      bool operator>=(const V &x, const W &y)
      {
        return !static_cast<bool>(x < y);
      }

      template<typename V, typename W>
      bool operator>=(const W &x, const V &y)
      {
        return !static_cast<bool>(y > x);
      }

      template<typename V, typename W>
      bool operator>(const W &x, const V &y)
      {
        return y < x;
      }

      template<typename V, typename W>
      bool operator<(const W &x, const V &y)
      {
        return y > x;
      }

      template<typename V, typename W>
      bool operator==(const W& y, const V& x)
      {
        return x == y;
      }

      template<typename V, typename W>
      bool operator!=(const W& y, const V& x)
      {
        return !static_cast<bool>(x == y);
      }

      template<typename V, typename W>
      bool operator!=(const V& y, const W& x)
      {
        return !static_cast<bool>(y == x);
      }

      template<typename V, typename W>
      V operator+(V lhs, const W& rhs)
      {
        return lhs += rhs;
      }

      template<typename V, typename W>
      V operator+(const W& lhs, V rhs)
      {
        return rhs += lhs;
      }

      template<typename V, typename W>
      V operator-(V lhs, const W& rhs)
      {
        return lhs -= rhs;
      }

      template<typename V, typename W>
      V operator*(V lhs, const W& rhs)
      {
        return lhs *= rhs;
      }

      template<typename V, typename W>
      V operator*(const W& lhs, V rhs)
      {
        return rhs *= lhs;
      }

      template<typename V, typename W>
      V operator/(V lhs, const W& rhs)
      {
        return lhs /= rhs;
      }

      template<typename V>
      V operator++(V& x, int)
      {
        return (++x);
      }

      template<typename V>
      V operator--(V& x, int)
      {
        return (--x);
      }

      template<typename IntType>
      rational<IntType>::rational() :
        _num(0),
        _den(0)
      {}

      template<typename IntType>
      rational<IntType>::rational(IntType num) :
        _num(num),
        _den(1)
      {}

      template<typename IntType>
      rational<IntType>::rational(IntType num, IntType den) :
        _num(num),
        _den(den)
      {
        normalize();
      }

      template<typename IntType>
      rational<IntType> &rational<IntType>::operator=(IntType num)
      {
        return assign(num, 1);
      }

      template<typename IntType>
      inline rational<IntType>& rational<IntType>::assign(IntType num,
        IntType den)
      {
        _num = num;
        _den = den;
        normalize();
        return *this;
      }

      template<typename IntType>
      IntType rational<IntType>::numerator() const
      {
        return _num;
      }

      template<typename IntType>
      IntType rational<IntType>::denominator() const
      {
        return _den;
      }

      template<typename IntType>
      inline rational<IntType> operator+(const rational<IntType>& r)
      {
        return r;
      }

      template<typename IntType>
      inline rational<IntType> operator-(const rational<IntType>& r)
      {
        return rational<IntType>(-r.numerator(), r.denominator());
      }

      template<typename IntType>
      rational<IntType>& rational<IntType>::operator+=(
        const rational<IntType>& r)
      {
        IntType r_num = r._num;
        IntType r_den = r._den;

        IntType gcd = core::math::gcd(_den, r_den);
        _den /= gcd;
        _num = _num * (r_den / gcd) + r_num * _den;

        gcd = core::math::gcd(_num, gcd);
        _num /= gcd;
        _den *= r_den / gcd;

        return *this;
      }

      template<typename IntType>
      inline rational<IntType>& rational<IntType>::operator+=(IntType i)
      {
        return operator+=(rational<IntType>(i));
      }

      template<typename IntType>
      rational<IntType>& rational<IntType>::operator-=(
        const rational<IntType>& r)
      {
        IntType r_num = r._num;
        IntType r_den = r._den;

        IntType gcd = core::math::gcd(_den, r_den);
        _den /= gcd;
        _num = _num * (r_den / gcd) - r_num * _den;
        gcd = core::math::gcd(_num, gcd);
        _num /= gcd;
        _den *= r_den / gcd;

        return *this;
      }

      template<typename IntType>
      inline rational<IntType>& rational<IntType>::operator-=(IntType i)
      {
        return operator-=(rational<IntType>(i));
      }

      template<typename IntType>
      rational<IntType>& rational<IntType>::operator*=(
        const rational<IntType>& r)
      {
        IntType r_num = r._num;
        IntType r_den = r._den;

        IntType gcd1 = core::math::gcd(_num, r_den);
        IntType gcd2 = core::math::gcd(r_num, _den);
        _num = (_num / gcd1) * (r_num / gcd2);
        _den = (_den / gcd2) * (r_den / gcd1);

        return *this;
      }

      template<typename IntType>
      inline rational<IntType>& rational<IntType>::operator*=(IntType i)
      {
        return operator*=(rational<IntType>(i));
      }

      template<typename IntType>
      rational<IntType>& rational<IntType>::operator/=(
        const rational<IntType>& r)
      {
        IntType r_num = r._num;
        IntType r_den = r._den;

        IntType zero(0);

        if (r_num == zero) {
          throw bad_rational();
        }
        if (_num == zero) {
          return *this;
        }

        IntType gcd1 = core::math::gcd(_num, r_num);
        IntType gcd2 = core::math::gcd(r_den, _den);
        _num = (_num / gcd1) * (r_den / gcd2);
        _den = (_den / gcd2) * (r_num / gcd1);

        if (_den < zero) {
            _num = -_num;
            _den = -_den;
        }

        return *this;
      }

      template<typename IntType>
      inline rational<IntType>& rational<IntType>::operator/=(IntType i)
      {
        return operator/=(rational<IntType>(i));
      }

      template<typename IntType>
      inline const rational<IntType>& rational<IntType>::operator++()
      {
        _num += _den;
        return *this;
      }

      template<typename IntType>
      inline const rational<IntType>& rational<IntType>::operator--()
      {
        _num -= _den;
        return *this;
      }

      template<typename IntType>
      bool rational<IntType>::operator<(const rational<IntType>& r) const
      {
        const IntType zero(0);

        IntType tn = _num;
        IntType td = _den;
        IntType tq = static_cast<IntType>(_num / _den);
        IntType tr = static_cast<IntType>(_num % _den);

        IntType rn = r._num;
        IntType rd = r._den;
        IntType rq = static_cast<IntType>(r._num / r._den);
        IntType rr = static_cast<IntType>(r._num % r._den);

        unsigned int reverse = 0u;

        while (tr < zero) {
          tr += td;
          --tq;
        }
        while (rr < zero) {
          rr += rd;
          --rq;
        }

        while (true) {
          if (tq != rq) {
              return reverse ? tq > rq : tq < rq;
          }

          reverse ^= 1u;
          if ((tr == zero) || (rr == zero)) {
              break;
          }

          tn = td;
          td = tr;
          tq = tn / td;
          tr = tn % td;

          rn = rd;
          rd = rr;
          rq = rn / rd;
          rr = rn % rd;
        }

        if (tr == rr) {
          return false;
        } else {
          return (tr != zero) != static_cast<bool>(reverse);
        }
      }

      template<typename IntType>
      bool rational<IntType>::operator<(IntType i) const
      {
        const IntType zero(0);

        IntType q = _num / _den;
        IntType r = _num % _den;
        while (r < zero) {
          r += _den;
          --q;
        }

        return q < i;
      }

      template<typename IntType>
      bool rational<IntType>::operator>(IntType i) const
      {
        if (_num == i && _den == IntType(1)) {
          return false;
        }

        return !operator<(i);
      }

      template<typename IntType>
      inline bool rational<IntType>::operator==(
        const rational<IntType>& r) const
      {
        return ((_num == r.num) && (_den == r.den));
      }

      template<typename IntType>
      inline bool rational<IntType>::operator==(IntType i) const
      {
        return ((_den == IntType(1)) && (_num == i));
      }

      template<typename IntType>
      void rational<IntType>::normalize()
      {
        IntType zero(0);

        if (_den == zero) {
          throw bad_rational(); // TODO Implement
        }

        if (_num == zero) {
          _den = IntType(1);
          return;
        }

        IntType gcd = core::math::gcd(_num, _den);

        _num /= gcd;
        _den /= gcd;

        _num = core::math::abs(_num);
        _den = core::math::abs(_den);

        // Ensure that the denominator is positive
        if (_den < zero) {
          _num = -_num;
          _den = -_den;
        }
      }
    }
  }
}
