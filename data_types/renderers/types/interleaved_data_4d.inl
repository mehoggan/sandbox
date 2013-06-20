namespace glext
{
  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_data_4d<T1, T2, T3, T4>::interleaved_data_4d()
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_data_4d<T1, T2, T3, T4>::interleaved_data_4d(
    const std::vector<interleaved_datum_4d<T1, T2, T3, T4> > &data) :
    _data(data)
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_data_4d<T1, T2, T3, T4>::interleaved_data_4d(
    const interleaved_data_4d<T1, T2, T3, T4> &rhs) :
    _data(rhs._data)
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_data_4d<T1, T2, T3, T4>::~interleaved_data_4d()
  {
    _data.clear();
  }

  template <typename T1, typename T2, typename T3, typename T4>
  interleaved_data_4d<T1, T2, T3, T4> &interleaved_data_4d<T1, T2, T3, T4>::
    operator=(interleaved_data_4d<T1, T2, T3, T4> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t interleaved_data_4d<T1, T2, T3, T4>::size_of() const
  {
    return _data.size() * (sizeof(internal_type1) + sizeof(internal_type2) +
      sizeof(internal_type3) + sizeof(internal_type4));
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t interleaved_data_4d<T1, T2, T3, T4>::t1_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t interleaved_data_4d<T1, T2, T3, T4>::t2_offset() const
  {
    return sizeof(internal_type1);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t interleaved_data_4d<T1, T2, T3, T4>::t3_offset() const
  {
    return sizeof(internal_type1) + sizeof(internal_type2);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t interleaved_data_4d<T1, T2, T3, T4>::t4_offset() const
  {
    return sizeof(internal_type1) + sizeof(internal_type2) +
      sizeof(internal_type3);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  size_t interleaved_data_4d<T1, T2, T3, T4>::stride() const
  {
    return sizeof(internal_type1) + sizeof(internal_type2) +
      sizeof(internal_type3) + sizeof(internal_type4);
  }

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3, typename T4>
  void swap(interleaved_data_4d<T1, T2, T3, T4> &lhs,
    interleaved_data_4d<T1, T2, T3, T4> &rhs)
  {
    lhs._data.swap(rhs.data);
  }

  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator==(const interleaved_data_4d<T1, T2, T3, T4> &lhs,
    const interleaved_data_4d<T1, T2, T3, T4> &rhs)
  {   
    return (lhs._data == rhs._data); 
  }
  
  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator!=(const interleaved_data_4d<T1, T2, T3, T4> &lhs,
    const interleaved_data_4d<T1, T2, T3, T4> &rhs)
  {
    return (lhs._data != rhs._data); 
  }
}
