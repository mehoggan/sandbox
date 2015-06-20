#include <utility/interval.h>

#include <cfloat>
#include <cmath>
#include <limits>

namespace utility
{
  template<typename T>
  interval<T>::interval()
  {
    (*this) = infinite();
  }

  template<typename T>
  interval<T>::interval(const T &min, const T &max) :
    m_min(min),
    m_max(max)
  {
    if (m_min > m_max) {
      throw interval_exception("min must be less than or equal to max");
    }
  }

  template<typename T>
  bool interval<T>::intersects(const interval &other) const
  {
    return (intersection_of((*this), other) != empty());
  }

  template<typename T>
  interval<T> interval<T>::empty()
  {
    return interval<T>(static_cast<T>(0), static_cast<T>(0));
  }

  template<typename T>
  interval<T> interval<T>::infinite()
  {
    if (std::numeric_limits<T>::has_infinity) {
      return interval<T>(-std::numeric_limits<T>::infinity(),
        std::numeric_limits<T>::infinity());
    } else {
      return interval<T>(std::numeric_limits<T>::min(),
        std::numeric_limits<T>::max());
    }
  }

  template<typename T>
  interval<T> interval<T>::hull(const T& min, const T& max)
  {
    if (std::isnan(min) && std::isnan(max)) {
      return interval<T>();
    } else if (std::isnan(min)) {
      return interval<T>(max, max);
    } else if (std::isnan(max)) {
      return interval<T>(min, min);
    } else {
      return interval<T>(min, max);
    }
  }

  template<typename T>
  interval<T> interval<T>::intersection_of(const interval &a, const interval &b)
  {
    if (a.m_min >= b.m_min && a.m_min <= b.m_max) {
      if (a.m_max <= b.m_max) {
        return hull(a.m_min, a.m_max);
      } else {
        return hull(a.m_min, b.m_max);
      }
    } else if (a.m_max >= b.m_min && a.m_max <= b.m_max) {
      if (a.m_min <= b.m_min) {
        return hull(b.m_min, a.m_max);
      } else {
        return hull(a.m_min, a.m_max);
      }
    } else if (b.m_min >= a.m_min && b.m_min <= a.m_max) {
      if (b.m_max <= a.m_max) {
        return hull(b.m_min, b.m_max);
      } else {
        return hull(b.m_min, a.m_max);
      }
    } else if (b.m_max >= a.m_min && b.m_max <= a.m_max) {
      if (b.m_min <= a.m_min) {
        return hull(a.m_min, b.m_max);
      } else {
        return hull(b.m_min, b.m_max);
      }
    } else {
      return empty();
    }
  }

  /// Explicit template instantiations for supported types.
  template class interval<signed char>;
  template class interval<unsigned char>;
  template class interval<wchar_t>;
  template class interval<char16_t>;
  template class interval<char32_t>;
  template class interval<short int>;
  template class interval<unsigned short int>;
  template class interval<int>;
  template class interval<unsigned int>;
  template class interval<long int>;
  template class interval<unsigned long int>;
  template class interval<long long int>;
  template class interval<unsigned long long int>;
  template class interval<float>;
  template class interval<double>;
  template class interval<long double>;
}
