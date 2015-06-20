#ifndef INTERVAL_H_INCLUDED
#define INTERVAL_H_INCLUDED

#include <utility/declspec.h>

#include <tuple>
#include <iostream>
#include <stdexcept>

namespace utility
{
  class UTILITY_API interval_exception : public std::exception
  {
  public:
    explicit interval_exception(const char *what) :
      m_what(what)
    {}

    const char *what() const throw()
    {
      return m_what;
    }

  private:
    const char *m_what;
  };

  template<typename T>
  class UTILITY_API interval
  {
  public:
    interval();
    interval(const T &min, const T &max);

    bool intersects(const interval &other) const;

    static interval empty();
    static interval infinite();
    static interval hull(const T& min, const T& max);
    static interval intersection_of(const interval &a, const interval &b);

    const T &min() const { return m_min; }
    const T &max() const { return m_max; }

  private:
    T m_min;
    T m_max;

  public:
    friend std::ostream &operator<<(std::ostream &out, const interval i)
    {
      return out << "[" << i.m_min << "," << i.m_max << "]";
    }

    friend std::wostream &operator<<(std::wostream &wout, const interval i)
    {
      return wout << (L"[") << i.m_min << (L",") << i.m_max << (L"]");
    }

    friend bool operator==(const interval &lhs, const interval &rhs)
    {
      return (lhs.m_min == rhs.m_min && lhs.m_max == rhs.m_max);
    }

    friend bool operator!=(const interval &lhs, const interval &rhs)
    {
      return !(lhs == rhs);
    }

    friend bool operator<(const interval &lhs, const interval &rhs)
    {
      return ((lhs.m_max < rhs.m_min) ||
        (lhs.m_min < rhs.m_min && lhs.m_max <= rhs.m_max));
    }

    friend bool operator>(const interval &lhs, const interval &rhs)
    {
      return (lhs.m_min > rhs.m_max) ||
        (lhs.m_min > rhs.m_min && lhs.m_max > rhs.m_max);
    }
  };
}

#endif
