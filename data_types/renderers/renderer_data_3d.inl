namespace glext
{
  /// Constructors
  template <typename T1, typename T2, typename T3>        
  renderer_data_3d<T>::renderer_data_3d()
  {}

  template <typename T1, typename T2, typename T3>        
  renderer_data_3d<T>::renderer_data_3d(const std::vector<T1> &data_1,
    const std::vector<T2> &data_2, const std::vector<T3> &data_3) :
    _data_1(data_1),
    _data_2(data_2),
    _data_3(data_3)
  {}

  /// Copy constructor
  template <typename T1, typename T2, typename T3>        
  renderer_data_3d<T>::renderer_data_3d(const renderer_data_3d &rhs) :
    _data_1(rhs._data_1),
    _data_2(rhs._data_2),
    _data_3(rhs._data_3)
  {}

  /// Destructor
  template <typename T1, typename T2, typename T3>        
  renderer_data_3d<T>::~renderer_data_3d()
  {
    _data_1.clear();
    _data_2.clear();
    _data_3.clear();
  }

  /// Assignment operator
  template <typename T1, typename T2, typename T3>        
  renderer_data_3d &renderer_data_3d<T>::operator=(renderer_data_3d &rhs)
  {
    swap((*this), rhs);

    return (*this); 
  }
 
  /// VBO parameters
  template <typename T1, typename T2, typename T3>
  size_t renderer_data_3d<T>::t1_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2, typename T3>
  size_t renderer_data_3d<T>::t2_offset() const
  {
    return t1_offset() + _data_1.size() * sizeof(internal_type1);
  }

  template <typename T1, typename T2, typename T3>
  size_t renderer_data_3d<T>::t3_offset() const
  {
    return t2_offset() + _data_2.size() * sizeof(internal_type2);
  }

  template <typename T1, typename T2, typename T3>
  size_t renderer_data_3d<T>::size_of() const
  {
    return data1_size_of() + data2_size_of() + data3_size_of();
  }

  template <typename T1, typename T2, typename T3>
  size_t renderer_data_3d<T>::data1_size_of() const
  {
    return _data_1.size() * sizeof(internal_type1);
  }

  template <typename T1, typename T2, typename T3>
  size_t renderer_data_3d<T>::data2_size_of() const
  {
    return _data_2.size() * sizeof(internal_type2);
  }

  template <typename T1, typename T2, typename T3>
  size_t renderer_data_3d<T>::data3_size_of() const
  {
    return _data_3.size() * sizeof(internal_type3);
  }

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3>
  void swap(renderer_data_3d<T1> &lhs, renderer_data_3d<T1> &rhs)
  {
    lhs._data_1.swap(rhs.data_1);
    lhs._data_2.swap(rhs.data_2);
    lhs._data_3.swap(rhs.data_3);
  }

  /// Comparison Operators
  template <typename T1, typename T2, typename T3>        
  bool operator==(const renderer_data_3d<T1> &lhs, 
    const renderer_data_3d<T1> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2 &&
      lhs._data_3 == rhs._data_3); 
  }
  
  template <typename T1, typename T2, typename T3>        
  bool operator!=(const renderer_data_3d<T1> &lhs, 
    const renderer_data_3d<T1> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2 ||
      lhs._data_3 != lhs._data_3); 
  }
}
