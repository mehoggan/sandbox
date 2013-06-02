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
}
