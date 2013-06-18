namespace glext
{
  /// Constructors
  template <typename T1, typename T2>        
  renderer_data_2d<T>::renderer_data_2d()
  {}

  template <typename T1, typename T2>        
  renderer_data_2d<T>::renderer_data_2d(const std::vector<T1> &data_1,
    const std::vector<T2> &data_2) :
    _data_1(data_1),
    _data_2(data_2)
  {}

  /// Copy constructor
  template <typename T1, typename T2>        
  renderer_data_2d<T>::renderer_data_2d(const renderer_data_2d &rhs) :
    _data_1(rhs._data_1),
    _data_2(rhs._data_2)
  {}

  /// Destructor
  template <typename T1, typename T2>        
  ~renderer_data_2d()
  {
    _data_1.clear();
    _data_2.clear();
  }

  /// Assignment operator
  template <typename T1, typename T2>        
  renderer_data_2d &renderer_data_2d<T>::operator=(renderer_data_2d &rhs)
  {
    swap((*this), rhs);

    return (*this); 
  }

  /// Copy and swap idiom
  template <typename T1, typename T2>
  void swap(renderer_data_2d<T1> &lhs, renderer_data_2d<T1> &rhs)
  {
    lhs._data_1.swap(rhs.data_1);
    lhs._data_2.swap(rhs.data_2);
  }

  template <typename T1, typename T2>        
  bool operator==(const renderer_data_2d<T1> &lhs, 
    const renderer_data_2d<T1> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2); 
  }
  
  template <typename T1, typename T2>        
  bool operator!=(const renderer_data_2d<T1> &lhs, 
    const renderer_data_2d<T1> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2); 
  }
}
