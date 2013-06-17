namespace glext 
{
  /// Constructors
  template <typename T>
  point_3d<T>::point_3d() :
    _x(T(0)),
    _y(T(0)),
    _z(T(0))
  {}

  template <typename T>
  point_3d<T>::point_3d(const T &x, const T &y, const T &z) :
    _x(x),
    _y(y),
    _z(z)
  {}

  /// Copy constructor
  template <typename T>
  point_3d<T>::point_3d(const point_3d<T> &rhs) :
    _x(rhs._x),
    _y(rhs._y),
    _z(rhs._z)
  {}

  /// Destructor
  template <typename T>
  point_3d<T>::~point_3d()
  {}

  /// Assignment operator
  template <typename T>
  point_3d<T> &point_3d<T>::operator=(point_3d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Setters
  template <typename T>
  void point_3d<T>::x(const T &x)
  {
    _x = x;
  }

  template <typename T>
  void point_3d<T>::y(const T &y)
  {
    _y = y;
  }

  template <typename T>
  void point_3d<T>::z(const T &z)
  {
    _z = z;
  }

  template <typename T>
  void point_3d<T>::x_and_y_and_z(const T &x, const T &y, const T &z)
  {
    _x = x;
    _y = y;
    _z = z;
  }

  /// Getters
  template <typename T>
  T& point_3d<T>::xref()
  {
    return _x;
  }

  template <typename T>
  T& point_3d<T>::yref()
  {
    return _y;
  }

  template <typename T>
  T& point_3d<T>::zref()
  {
    return _z;
  }

  /// Getters
  template <typename T>
  T point_3d<T>::x() const
  {
    return _x;
  }

  template <typename T>
  T point_3d<T>::y() const
  {
    return _y;
  }

  template <typename T>
  T point_3d<T>::z() const
  {
    return _z;
  }

  /// Copy and swap idiom
  template <typename T>
  void swap(point_3d<T> &lhs, point_3d<T> &rhs)
  {
    std::swap(lhs.xref(), rhs.xref());
    std::swap(lhs.yref(), rhs.yref());
    std::swap(lhs.zref(), rhs.zref());
  }

  /// Comparison operators
  template <typename T>
  bool operator<(const point_3d<T> &lhs, const point_3d<T> &rhs)
  {
    return (lhs.x() < rhs.x() && lhs.y() < rhs.y() && lhs.z() < rhs.z());
  }

  template <typename T>
  bool operator>(const point_3d<T> &lhs, const point_3d<T> &rhs)
  {
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y() && lhs.z() > rhs.z());
  }
  
  template <typename T>
  bool operator<=(const point_3d<T> &lhs, const point_3d<T> &rhs)
  {
    return (lhs.x() <= rhs.x() && lhs.y() <= rhs.y() && lhs.z() <= rhs.z());
  }

  template <typename T>
  bool operator>=(const point_3d<T> &lhs, const point_3d<T> &rhs)
  {
    return (lhs.x() >= rhs.x() && lhs.y() >= rhs.y() && lhs.z() >= rhs.z());
  }

  template <typename T>
  bool operator==(const point_3d<T> &lhs, const point_3d<T> &rhs)
  {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
  }

  template <typename T>
  bool operator!=(const point_3d<T> &lhs, const point_3d<T> &rhs)
  {
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.z() != rhs.z());
  }

  /// Output operators
  template <typename T>
  std::ostream &operator<<(std::ostream &out, const point_3d<T> &rhs)
  {
    return out << "(" << rhs.x() << ", " << rhs.y() << ", " << rhs.z() << ")";
  }
}
