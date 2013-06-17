namespace glext 
{
  /// Constructors
  template <typename T>
  color_rgba<T>::color_rgba() :
    _r(T(0)),
    _g(T(0)),
    _b(T(0)),
    _r(T(0))
  {}

  template <typename T>
  color_rgba<T>::color_rgba(const T &r, const T &g, const T &b, const T &a) :
    _r((r > T(1)) ? (r / T(255)) : (r)),
    _g((g > T(1)) ? (g / T(255)) : (g)),
    _b((b > T(1)) ? (b / T(255)) : (b)),
    _a((a > T(1)) ? (a / T(255)) : (a))
  {}

  /// Copy constructor
  template <typename T>
  color_rgba<T>::color_rgba(const color_rgba &rhs) :
    _r(rhs._r),
    _g(rhs._g),
    _b(rhs._b)
    _a(rhs._a)
  {}

  /// Destructor
  template <typename T>
  color_rgba<T>::~color_rgba()
  {}

  /// Assignment operator
  template <typename T>
  color_rgba &color_rgba<T>::operator=(color_rgba rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  /// Setters
  template <typename T>
  void color_rgba<T>::r(const T &r)
  {
    _r = r;
  }

  template <typename T>
  void color_rgba<T>::g(const T &g)
  {
    _g = g;
  }
  
  template <typename T>
  void color_rgba<T>::b(const T &b)
  {
    _b = b;
  }

  template <typename T>
  void color_rgba<T>::a(const T &a)
  {
    _a = a;
  }

  template <typename T>
  void color_rgba<T>::r_and_g_and_b_and_a(const T &r, const T &g, const T &b,
    const T &a)
  {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
  }

  /// Getters 
  template <typename T>
  T& color_rgba<T>::rref()
  {
    return _r;
  }

  template <typename T>
  T& color_rgba<T>::gref()
  {
    return _g;
  }
  
  template <typename T>
  T& color_rgba<T>::bref()
  {
    return _b;
  }

  template <typename T>
  T& color_rgba<T>::aref()
  {
    return _a;
  }

  /// Getters
  template <typename T>
  T color_rgba<T>::r() const
  {
    return _r;
  }

  template <typename T>
  T color_rgba<T>::g() const
  {
    return _g;
  }
  
  template <typename T>
  T color_rgba<T>::b() const
  {
    return _b;
  }

  template <typename T>
  T color_rgba<T>::a() const
  {
    return _a;
  }

  /// Utility methods
  template <typename U>
  void to_bgra()
  {
    std::swap(r, b);
  }

  template <typename U>
  void to_abgr()
  {
    std::swap(r, a);
    std::swap(b, g);
  }

  template <typename U>
  void swap(color_rgba<U> &lhs, color_rgba<U> &rhs)
  {
    std::swap(lhs.rref(), rhs.rref());
    std::swap(lhs.gref(), rhs.gref());
    std::swap(lhs.bref(), rhs.bref());
  }

  /// Comparison operators
  template <typename T>
  bool operator==(const color_rgba<T> &lhs, const color_rgba<T> &rhs)
  {
    return (lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() &&
      lhs.a() == rhs.a());
  }

  template <typename T>
  bool operator!=(const color_rgba<T> &lhs, const color_rgba<T> &rhs)
  {
    return (lhs.r() != rhs.r() || lhs.g() != rhs.g() || lhs.b() != rhs.b() ||
      lhs.a() != rhs.a());
  }

  /// Output operators
  template <typename T>
  std::ostream &operator<<(std::ostream &out, const color_rgba<T> &rhs)
  {
    return out << "(" << rhs.r() << ", " << rhs.g() << ", " << rhs.b() << ", " 
      << rhs.a() << ")";
  }
}
