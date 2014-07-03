namespace glext 
{
  /// Constructors
  template <typename T>
  point_2d<T>::point_2d()
  {}

  template <typename T>
  point_2d<T>::point_2d(const T &x, const T &y) :
    _x(x),
    _y(y)
  {}

  /// Copy constructor
  template <typename T>
  point_2d<T>::point_2d(const point_2d<T> &rhs) :
    _x(rhs._x),
    _y(rhs._y)
  {}

  /// Destructor
  template <typename T>
  point_2d<T>::~point_2d()
  {}

  /// Assignment operator
  template <typename T>
  point_2d<T> &point_2d<T>::operator=(point_2d<T> rhs)
  {
    swap((*this), rhs);
    
    return (*this);
  }

  /// Setters
  template <typename T>
  void point_2d<T>::x(const T &x)
  {
    _x = x;
  }

  template <typename T>
  void point_2d<T>::y(const T &y)
  {
    _y = y;
  }

  template <typename T>
  void point_2d<T>::x_and_y(const T &x, const T &y)
  {
    _x = x;
    _y = y;
  }

  /// Swizzle Methods
  template <typename T>
  point_2d<T> point_2d<T>::xy() const
  {
    return point_2d<T>(_x, _y);
  }

  template <typename T>
  point_2d<T> point_2d<T>::xx() const
  {
    return point_2d<T>(_x, _x);
  }

  template <typename T>
  point_2d<T> point_2d<T>::yy() const
  {
    return point_2d<T>(_y, _y);
  }

  template <typename T>
  point_2d<T> point_2d<T>::yx() const
  {
    return point_2d<T>(_y, _x);
  }

  /// Getters
  template <typename T>
  T& point_2d<T>::xref()
  {
    return _x;
  }

  template <typename T>
  T& point_2d<T>::yref()
  {
    return _y;
  }

  /// Getters
  template <typename T>
  T point_2d<T>::x() const
  {
    return _x;
  }

  template <typename T>
  T point_2d<T>::y() const
  {
    return _y;
  }

  /// Copy and swap idiom
  template <typename T>
  void swap(point_2d<T> &lhs, point_2d<T> &rhs)
  {
    std::swap(lhs.xref(), rhs.xref());
    std::swap(lhs.yref(), rhs.yref());
  }

  /// Comparison operators
  template <typename T>
  bool operator<(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() < rhs.x() && lhs.y() < rhs.y());
  }

  template <typename T>
  bool operator>(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y());
  }
  
  template <typename T>
  bool operator<=(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() <= rhs.x() && lhs.y() <= rhs.y());
  }

  template <typename T>
  bool operator>=(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() >= rhs.x() && lhs.y() >= rhs.y());
  }

  template <typename T>
  bool operator==(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
  }

  template <typename T>
  bool operator!=(const point_2d<T> &lhs, const point_2d<T> &rhs)
  {
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y());
  }
}
