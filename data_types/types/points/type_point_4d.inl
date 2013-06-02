namespace glext 
{
  /// Constructors
  template <typename T>
  point_4d<T>::point_4d()
    _x(0),
    _y(0),
    _z(0),
    _w(0)
  {}

  template <typename T>
  point_4d<T>::point_4d(const T &x, const T &y, const T &z, const T &w) :
    _x(x),
    _y(y),
    _z(z),
    _w(w)
  {}

  /// Copy constructor
  template <typename T>
  point_4d<T>::point_4d(const point_4d<T> &rhs) :
    _x(rhs._x),
    _y(rhs._y),
    _z(rhs._z),
    _w(rhs._w)
  {}

  /// Destructor
  template <typename T>
  point_4d<T>::~point_4d()
  {}

  /// Assignment operator
  template <typename T>
  point_4d<T> &point_4d<T>::operator=(point_4d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Setters
  template <typename T>
  void point_4d<T>::x(const T &x)
  {
    _x = x;
  }

  template <typename T>
  void point_4d<T>::y(const T &y)
  {
    _y = y;
  }

  template <typename T>
  void point_4d<T>::z(const T &z)
  {
    _z = z;
  }

  template <typename T>
  void point_4d<T>::w(const T &w)
  {
    _w = w;
  }

  template <typename T>
  void point_4d<T>::x_and_y_and_z_and_w(const T &x, const T &y, const T &z,
    const T &w)
  {
    _x = x;
    _y = y;
    _z = z;
  }

  /// Getters
  template <typename T>
  T& point_4d<T>::xref()
  {
    return _x;
  }

  template <typename T>
  T& point_4d<T>::yref()
  {
    return _y;
  }

  template <typename T>
  T& point_4d<T>::zref()
  {
    return _z;
  }

  template <typename T>
  T& point_4d<T>::wref()
  {
    return _w;
  }

  /// Getters
  template <typename T>
  T point_4d<T>::x() const
  {
    return _x;
  }

  template <typename T>
  T point_4d<T>::y() const
  {
    return _y;
  }

  template <typename T>
  T point_4d<T>::z() const
  {
    return _z;
  }
 
  template <typename T>
  T point_4d<T>::w() const
  {
    return _w;
  }

  /// Copy and swap idiom
  template <typename T>
  void swap(point_4d<T> &lhs, point_4d<T> &rhs)
  {
    std::swap(lhs.x(), rhs.x());
    std::swap(lhs.y(), rhs.y());
    std::swap(lhs.z(), rhs.z());
    std::swap(lhs.w(), rhs.w());
  }

  /// Comparison operators
  template <typename T>
  bool operator<(const point_4d<T> &lhs, const point_4d<T> &rhs)
  {
    return (lhs.x() < rhs.x() && lhs.y() < rhs.y() && lhs.z() < rhs.z() &&
      lhs.w() < rhs.w());
  }

  template <typename T>
  bool operator>(const point_4d<T> &lhs, const point_4d<T> &rhs)
  {
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y() && lhs.z() > rhs.z() &&
      lhs.w() > rhs.w());
  }
  
  template <typename T>
  bool operator<=(const point_4d<T> &lhs, const point_4d<T> &rhs)
  {
    return (lhs.x() <= rhs.x() && lhs.y() <= rhs.y() && lhs.z() <= rhs.z() &&
      lhs.w() <= rhs.w());
  }

  template <typename T>
  bool operator>=(const point_4d<T> &lhs, const point_4d<T> &rhs)
  {
    return (lhs.x() >= rhs.x() && lhs.y() >= rhs.y() && lhs.z() >= rhs.z() &&
      lhs.w() >= rhs.w());
  }

  template <typename T>
  bool operator==(const point_4d<T> &lhs, const point_4d<T> &rhs)
  {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() &&
      lhs.w() == rhs.w());
  }

  template <typename T>
  bool operator!=(const point_4d<T> &lhs, const point_4d<T> &rhs)
  {
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.z() != rhs.z() ||
      lhs.w() == rhs.w());
  }
}
