namespace glext
{
  template <typename T1, typename T2, typename T3>        
  interleaved_data_3d<T1, T2, T3>::interleaved_data_3d()
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_data_3d<T1, T2, T3>::interleaved_data_3d(
    const std::vector<interleaved_datum_3d<T1, T2, T3> > &data) :
    _data(data)
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_data_3d<T1, T2, T3>::interleaved_data_3d(
    const interleaved_data_3d<T1, T2, T3> &rhs) :
    _data(rhs._data)
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_data_3d<T1, T2, T3>::~interleaved_data_3d()
  {
    _data.clear();
  }

  template <typename T1, typename T2, typename T3>
  interleaved_data_3d<T1, T2, T3> &interleaved_data_3d<T1, T2, T3>::operator=(
    interleaved_data_3d<T1, T2, T3> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  /// VBO paramaters
  template <typename T1, typename T2, typename T3>
  size_t interleaved_data_3d<T1, T2, T3>::size_of() const
  {
    return _data.size() * (sizeof(internal_type1) + sizeof(internal_type2)
       + sizeof(internal_type3));
  }

  template <typename T1, typename T2, typename T3>
  size_t interleaved_data_3d<T1, T2, T3>::t1_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2, typename T3>
  size_t interleaved_data_3d<T1, T2, T3>::t2_offset() const
  {
    return sizeof(internal_type1);
  }

  template <typename T1, typename T2, typename T3>
  size_t interleaved_data_3d<T1, T2, T3>::t3_offset() const
  {
    return sizeof(internal_type1) + sizeof(internal_type2);
  }

  template <typename T1, typename T2, typename T3>
  size_t interleaved_data_3d<T1, T2, T3>::stride() const
  {
    return sizeof(internal_type1) + sizeof(internal_type2) +
      sizeof(internal_type3);
  }

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3>
  void swap(interleaved_data_3d<T1, T2, T3> &lhs,
    interleaved_data_3d<T1, T2, T3> &rhs)
  {
    lhs._data.swap(rhs.data);
  }

  template <typename T1, typename T2, typename T3>        
  bool operator==(const interleaved_data_3d<T1, T2, T3> &lhs,
    const interleaved_data_3d<T1, T2, T3> &rhs)
  {   
    return (lhs._data == rhs._data); 
  }
  
  template <typename T1, typename T2, typename T3>        
  bool operator!=(const interleaved_data_3d<T1, T2, T3> &lhs,
    const interleaved_data_3d<T1, T2, T3> &rhs)
  {
    return (lhs._data != rhs._data); 
  }
}
