namespace glext 
{
  /// Constructors
  template <typename T>
  vector_2d<T>::vector_2d() :
    _x(0),
    _y(0)
  {}

  template <typename T>
  vector_2d<T>::vector_2d(const T &x, const T &y) :
    _x(x),
    _y(y)
  {}

  /// Copy constructor
  template <typename T>
  vector_2d<T>::vector_2d(const vector_2d<T> &rhs) :
    _x(rhs._x),
    _y(rhs._y)
  {}

  /// Destructor
  template <typename T>
  vector_2d<T>::~vector_2d()
  {}

  /// Assignment operator
  template <typename T>
  vector_2d<T> &vector_2d<T>::operator=(vector_2d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Sub-index operator
  template <typename T>
  T &vector_2d<T>::operator[] (unsigned short index) {
    assert(index < 2);

    switch(index) 
    {
      case(0): return _x;
      case(1): return _y;
    }
  }

  /// Setters
  template <typename T>
  void vector_2d<T>::x(const T &x)
  {
    _x = x;
  }

  template <typename T>
  void vector_2d<T>::y(const T &y)
  {
    _y = y;
  }

  template <typename T>
  void vector_2d<T>::x_and_y(const T &x, const T &y)
  {
    _x = x;
    _y = y;
  }

  /// Getters
  template <typename T>
  T& vector_2d<T>::xref()
  {
    return _x;
  }

  template <typename T>
  T& vector_2d<T>::yref()
  {
    return _y;
  }

  /// Getters
  template <typename T>
  T vector_2d<T>::x() const
  {
    return _x;
  }

  template <typename T>
  T vector_2d<T>::y() const
  {
    return _y;
  }
 
  /// Internal math algorithms 
  template <typename T> 
  T vector_2d<T>::magnitude() const
  {
    return sqrt(_x * _x + _y * _y);
  }

  template <typename T> 
  void vector_2d<T>::normalize() 
  {
    if (magnitude()) {
      (*this) *= (T(1) / magnitude());
    }
  }

  template <typename T>
  T vector_2d<T>::dot(const vector_2d<T> &rhs) const
  {
    return (_x * rhs._x + _y * rhs._y);
  }

  template <typename T> 
  void vector_2d<T>::operator+=(const vector_2d<T> &rhs)
  {
    _x += rhs._x;
    _y += rhs._y;
  }

  template <typename T> 
  void vector_2d<T>::operator-=(const vector_2d<T> &rhs)
  {
    _x -= rhs._x;
    _y -= rhs._y;
  }

  template <typename T> 
  void vector_2d<T>::operator*=(const T &rhs)
  {
    _x *= rhs;
    _y *= rhs;
  }

  /// Copy and swap idiom
  template <typename T>
  void swap(vector_2d<T> &lhs, vector_2d<T> &rhs)
  {
    std::swap(lhs.xref(), rhs.xref());
    std::swap(lhs.yref(), rhs.yref());
  }

  /// Comparison operators
  template <typename T>
  bool operator<(const vector_2d<T> &lhs, const vector_2d<T> &rhs)
  {
    return (lhs.x() < rhs.x() && lhs.y() < rhs.y());
  }

  template <typename T>
  bool operator>(const vector_2d<T> &lhs, const vector_2d<T> &rhs)
  {
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y());
  }
  
  template <typename T>
  bool operator<=(const vector_2d<T> &lhs, const vector_2d<T> &rhs)
  {
    return (lhs.x() <= rhs.x() && lhs.y() <= rhs.y());
  }

  template <typename T>
  bool operator>=(const vector_2d<T> &lhs, const vector_2d<T> &rhs)
  {
    return (lhs.x() >= rhs.x() && lhs.y() >= rhs.y());
  }

  template <typename T>
  bool operator==(const vector_2d<T> &lhs, const vector_2d<T> &rhs)
  {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
  }

  template <typename T>
  bool operator!=(const vector_2d<T> &lhs, const vector_2d<T> &rhs)
  {
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y());
  }

  /// Arithmetic operators
  template <typename T>
  vector_2d<T> operator+(const vector_2d<T> &v1, const vector_2d<T> &v2)
  {
    return vector_2d<T>(v1.x() + v2.x(), v1.y() + v2.y());
  }

  template <typename T>
  vector_2d<T> operator-(const vector_2d<T> &v1, const vector_2d<T> &v2)
  {
    return vector_2d<T>(v1.x() - v2.x(), v1.y() - v2.y());
  }

  template <typename T>
  vector_2d<T> operator-(const vector_2d<T> &v1)
  {
    return vector_2d<T>(T(-1) * v1.x(), T(-1) * v1.y());
  }

  template <typename T>
  vector_2d<T> operator*(const T &s, const vector_2d<T> &v1)
  {
    return vector_2d<T>(s * v1.x(), s * v1.y());
  }
}
