namespace glext
{
  /// Constructors
  template <typename T1, typename T2, typename T3, typename T4>        
  renderer_data_4d<T1, T2, T3, T4>::renderer_data_4d() :
    _type_count(4)
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  renderer_data_4d<T1, T2, T3, T4>::renderer_data_4d(
    const std::vector<T1> &data_1, const std::vector<T2> &data_2, 
    const std::vector<T3> &data_3, const std::vector<T4> &data_4) :
    _type_count(4),
    _data_1(data_1),
    _data_2(data_2),
    _data_3(data_3),
    _data_4(data_4)
  {}

  /// Copy constructor
  template <typename T1, typename T2, typename T3, typename T4>        
  renderer_data_4d<T1, T2, T3, T4>::renderer_data_4d(
    const renderer_data_4d &rhs) :
    _type_count(4),
    _data_1(rhs._data_1),
    _data_2(rhs._data_2),
    _data_3(rhs._data_3),
    _data_4(rhs._data_4)
  {}

  /// Destructor
  template <typename T1, typename T2, typename T3, typename T4>        
  renderer_data_4d<T1, T2, T3, T4>::~renderer_data_4d()
  {
    _data_1.clear();
    _data_2.clear();
    _data_3.clear();
    _data_4.clear();
  }

  /// Assignment operator
  template <typename T1, typename T2, typename T3, typename T4>        
  renderer_data_4d<T1, T2, T3, T4> &renderer_data_4d<T1, T2, T3, T4>::operator=(
    renderer_data_4d<T1, T2, T3, T4> &rhs)
  {
    swap((*this), rhs);

    return (*this); 
  }

  /// VBO parameters
  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::t1_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::t2_offset() const
  {
    return t1_offset() + _data_1.size() * sizeof(internal_type1);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::t3_offset() const
  {
    return t2_offset() + _data_2.size() * sizeof(internal_type2);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::t4_offset() const
  {
    return t3_offset() + _data_3.size() * sizeof(internal_type3);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::size_of() const
  {
    return data1_size_of() + data2_size_of() + data3_size_of() + 
      data4_size_of(); 
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::data1_size_of() const
  {
    return _data_1.size() * sizeof(internal_type1);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::data2_size_of() const
  {
    return _data_2.size() * sizeof(internal_type2);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::data3_size_of() const
  {
    return _data_3.size() * sizeof(internal_type3);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t renderer_data_4d<T1, T2, T3, T4>::data4_size_of() const
  {
    return _data_4.size() * sizeof(internal_type4);
  }

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3, typename T4>
  void swap(renderer_data_4d<T1, T2, T3, T4> &lhs, 
    renderer_data_4d<T1, T2, T3, T4> &rhs)
  {
    lhs._data_1.swap(rhs.data_1);
    lhs._data_2.swap(rhs.data_2);
    lhs._data_3.swap(rhs.data_3);
    lhs._data_4.swap(rhs.data_4);
    std::swap(lhs._type_count, rhs._type_count);
  }

  /// Comparison Operators
  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator==(const renderer_data_4d<T1, T2, T3, T4> &lhs, 
    const renderer_data_4d<T1, T2, T3, T4> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2 &&
      lhs._data_3 == rhs._data_3 && lhs._data_4 == rhs._data_4); 
  }
  
  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator!=(const renderer_data_4d<T1, T2, T3, T4> &lhs, 
    const renderer_data_4d<T1, T2, T3, T4> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2 ||
      lhs._data_3 != lhs._data_3 || rhs._data_4 != rhs._data_4); 
  }
}

