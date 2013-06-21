namespace glext
{
  /// Constructors
  template <typename T1, typename T2>        
  renderer_data_2d<T1, T2>::renderer_data_2d() :
    _type_count(2)
  {}

  template <typename T1, typename T2>        
  renderer_data_2d<T1, T2>::renderer_data_2d(const std::vector<T1> &data_1,
    const std::vector<T2> &data_2) :
    _type_count(2),
    _data_1(data_1),
    _data_2(data_2)
  {}

  /// Copy constructor
  template <typename T1, typename T2>        
  renderer_data_2d<T1, T2>::renderer_data_2d(const renderer_data_2d &rhs) :
    _type_count(2),
    _data_1(rhs._data_1),
    _data_2(rhs._data_2)
  {}

  /// Destructor
  template <typename T1, typename T2>        
  renderer_data_2d<T1, T2>::~renderer_data_2d()
  {
    _data_1.clear();
    _data_2.clear();
  }

  /// Assignment operator
  template <typename T1, typename T2>        
  renderer_data_2d<T1, T2> &renderer_data_2d<T1, T2>::operator=(
    renderer_data_2d<T1, T2> &rhs)
  {
    swap((*this), rhs);

    return (*this); 
  }

  /// VBO parameters
  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::t1_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::t2_offset() const
  {
    return t1_offset() + _data_1.size() * sizeof(internal_type1);
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::t3_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::t4_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::size_of() const
  {
    return data1_size_of() + data2_size_of() + data3_size_of() +
      data4_size_of();
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::data1_size_of() const
  {
    return _data_1.size() * sizeof(internal_type1);
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::data2_size_of() const
  {
    return _data_2.size() * sizeof(internal_type2);
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::data3_size_of() const
  {
    return 0;
  }

  template <typename T1, typename T2>
  size_t renderer_data_2d<T1, T2>::data4_size_of() const
  {
    return 0;
  }

  /// Copy and swap idiom
  template <typename T1, typename T2>
  void swap(renderer_data_2d<T1, T2> &lhs, renderer_data_2d<T1, T2> &rhs)
  {
    lhs._data_1.swap(rhs.data_1);
    lhs._data_2.swap(rhs.data_2);
    std::swap(lhs._type_count, rhs._type_count);
  }

  template <typename T1, typename T2>        
  bool operator==(const renderer_data_2d<T1, T2> &lhs, 
    const renderer_data_2d<T1, T2> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2); 
  }
  
  template <typename T1, typename T2>        
  bool operator!=(const renderer_data_2d<T1, T2> &lhs, 
    const renderer_data_2d<T1, T2> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2); 
  }
}
