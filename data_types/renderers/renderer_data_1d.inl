namespace glext
{
  /// Constructors
  template <typename T1>        
  renderer_data_1d_<T>::renderer_data_1d()
  {
  }

  template <typename T1>        
  renderer_data_1d_<T>::renderer_data_1d(std::vector<T1> &data_1) :
    _data_1(data_1)
  {
  }

  /// Copy constructor
  template <typename T1>        
  renderer_data_1d_<T>::renderer_data_1d(const renderer_data_1d &rhs) :
    _data_1(rhs._data_1)
  {
  }

  /// Destructor
  template <typename T1>        
  ~renderer_data_1d()
  {
    _data_1.clear();
  }

  /// Assignment operator
  template <typename T1>        
  renderer_data_1d &renderer_data_1d_<T>::operator=(renderer_data_1d &rhs)
  {
    swap((*this), rhs);

    return (*this); 
  }

  /// Copy and swap idiom
  template <typename T1>
  void swap(renderer_data_1d<T1> &lhs, renderer_data_1d<T1> &rhs)
  {
    lhs._data_1.swap(rhs.data_1);
  }


  template <typename T1>        
  bool operator==(const renderer_data_1d<T1> &lhs, 
    const renderer_data_1d<T1> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1); 
  }
  
  template <typename T1>        
  bool operator!=(const renderer_data_1d<T1> &lhs, 
    const renderer_data_1d<T1> &rhs)
  {
    return (lhs._data_1 != rhs._data_1); 
  }
}
