namespace glext
{
  template <typename T1, typename T2>
  interleaved_data_2d<T1, T2>::interleaved_data_2d()
  {}

  template <typename T1, typename T2>
  interleaved_data_2d<T1, T2>::interleaved_data_2d(
      const std::vector<interleaved_datum_2d<T1, T2> > &data) :
    _data(data)
  {}

  template <typename T1, typename T2>
  interleaved_data_2d<T1, T2>::interleaved_data_2d(
    const interleaved_data_2d<T1, T2> &rhs) :
    _data(rhs._data)
  {}

  template <typename T1, typename T2>
  interleaved_data_2d<T1, T2>::~interleaved_data_2d()
  {
    _data.clear();
  }

  template <typename T1, typename T2>
  interleaved_data_2d<T1, T2> &interleaved_data_2d<T1, T2>::operator=(
    interleaved_data_2d<T1, T2> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  /// VBO paramaters
  template <typename T1, typename T2>
  size_t interleaved_data_2d<T1, T2>::size_of() const
  {
    return _data.size() * (sizeof(internal_type1) + sizeof(internal_type2));
  }

  template <typename T1, typename T2>
  size_t interleaved_data_2d<T1, T2>::t1_offset() const
  {
    return 0;
  }

  template <typename T1, typename T2>
  size_t interleaved_data_2d<T1, T2>::t2_offset() const
  {
    return sizeof(internal_type1);
  }

  template <typename T1, typename T2>
  size_t interleaved_data_2d<T1, T2>::stride() const
  {
    return sizeof(internal_type1) + sizeof(internal_type2);
  }

  /// Copy and swap idiom
  template <typename T1, typename T2>
  void swap(interleaved_data_2d<T1, T2> &lhs, interleaved_data_2d<T1, T2> &rhs)
  {
    lhs._data.swap(rhs.data);
  }

  template <typename T1, typename T2>
  bool operator==(const interleaved_data_2d<T1, T2> &lhs,
    const interleaved_data_2d<T1, T2> &rhs)
  {
    return (lhs._data == rhs._data);
  }
  
  template <typename T1, typename T2>
  bool operator!=(const interleaved_data_2d<T1, T2> &lhs,
    const interleaved_data_2d<T1, T2> &rhs)
  {
    return (lhs._data != rhs._data);
  }
}
