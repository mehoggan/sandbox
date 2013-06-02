namespace glext 
{
  /// Constructors
  template <typename T>
  vector_3d<T>::vector_3d()
    _x(0),
    _y(0),
    _z(0)
  {}

  template <typename T>
  vector_3d<T>::vector_3d(const T &x, const T &y, const T &z) :
    _x(x),
    _y(y),
    _z(z)
  {}

  /// Copy constructor
  template <typename T>
  vector_3d<T>::vector_3d(const vector_3d<T> &rhs) :
    _x(rhs._x),
    _y(rhs._y),
    _z(rhs._z)
  {}

  /// Destructor
  template <typename T>
  vector_3d<T>::~vector_3d()
  {}

  /// Assignment operator
  template <typename T>
  vector_3d<T> &vector_3d<T>::operator=(vector_3d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Setters
  template <typename T>
  void vector_3d<T>::x(const T &x)
  {
    _x = x;
  }

  template <typename T>
  void vector_3d<T>::y(const T &y)
  {
    _y = y;
  }

  template <typename T>
  void vector_3d<T>::z(const T &z)
  {
    _z = z;
  }

  template <typename T>
  void vector_3d<T>::x_and_y_and_z(const T &x, const T &y, const T &z)
  {
    _x = x;
    _y = y;
    _z = z;
  }

  /// Getters
  template <typename T>
  T& vector_3d<T>::xref()
  {
    return _x;
  }

  template <typename T>
  T& vector_3d<T>::yref()
  {
    return _y;
  }

  template <typename T>
  T& vector_3d<T>::zref()
  {
    return _z;
  }

  /// Getters
  template <typename T>
  T vector_3d<T>::x() const
  {
    return _x;
  }

  template <typename T>
  T vector_3d<T>::y() const
  {
    return _y;
  }

  template <typename T>
  T vector_3d<T>::z() const
  {
    return _z;
  }
 
  /// Internal math algorithms 
  template <typename T> 
  T vector_3d<T>::magnitude() const
  {
    return sqrt(_x * _x + _y * _y + _z * _z);
  }

  /// Copy and swap idiom
  template <typename T>
  void swap(vector_3d<T> &lhs, vector_3d<T> &rhs)
  {
    std::swap(lhs.xref(), rhs.xref());
    std::swap(lhs.yref(), rhs.yref());
    std::swap(lhs.zref(), rhs.zref());
  }

  /// Comparison operators
  template <typename T>
  bool operator<(const vector_3d<T> &lhs, const vector_3d<T> &rhs)
  {
    return (lhs.x() < rhs.x() && lhs.y() < rhs.y() && lhs.z() < rhs.z());
  }

  template <typename T>
  bool operator>(const vector_3d<T> &lhs, const vector_3d<T> &rhs)
  {
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y() && lhs.z() > rhs.z());
  }
  
  template <typename T>
  bool operator<=(const vector_3d<T> &lhs, const vector_3d<T> &rhs)
  {
    return (lhs.x() <= rhs.x() && lhs.y() <= rhs.y() && lhs.z() <= rhs.z());
  }

  template <typename T>
  bool operator>=(const vector_3d<T> &lhs, const vector_3d<T> &rhs)
  {
    return (lhs.x() >= rhs.x() && lhs.y() >= rhs.y() && lhs.z() >= rhs.z());
  }

  template <typename T>
  bool operator==(const vector_3d<T> &lhs, const vector_3d<T> &rhs)
  {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
  }

  template <typename T>
  bool operator!=(const vector_3d<T> &lhs, const vector_3d<T> &rhs)
  {
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.z() != rhs.z());
  }
}
