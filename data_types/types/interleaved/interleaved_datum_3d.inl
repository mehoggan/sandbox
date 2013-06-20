namespace glext
{
  template <typename T1, typename T2, typename T3>        
  interleaved_datum_3d<T1, T2, T3>::interleaved_datum_3d()
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_datum_3d<T1, T2, T3>::interleaved_datum_3d(const T1 &datum_1, 
    const T2 &datum_2, const T3 &datum_3) :
    _datum1(datum_1),
    _datum2(datum_2),    
    _datum3(datum_3)    
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_datum_3d<T1, T2, T3>::interleaved_datum_3d(
    const interleaved_datum_3d<T1, T2, T3> &rhs) :
    _datum1(rhs._datum1),
    _datum2(rhs._datum2),
    _datum3(rhs._datum3)
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_datum_3d<T1, T2, T3>::~interleaved_datum_3d()
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_datum_3d<T1, T2, T3> &interleaved_datum_3d<T1, T2, T3>::operator=(
    interleaved_datum_3d<T1, T2, T3> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  } 

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3>
  void swap(interleaved_datum_3d<T1, T2, T3> &lhs,
    interleaved_datum_3d<T1, T2, T3> &rhs)
  {
    std::swap(lhs._datum1, rhs._datum1);
    std::swap(lhs._datum2, rhs._datum2);
    std::swap(lhs._datum3, rhs._datum3);
  }

  template <typename T1, typename T2, typename T3>        
  bool operator==(const interleaved_datum_3d<T1, T2, T3> &lhs,
    const interleaved_datum_3d<T1, T2, T3> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2 &&
      lhs._data_3 == rhs._data_3); 
  }
  
  template <typename T1, typename T2, typename T3>        
  bool operator!=(const interleaved_datum_3d<T1, T2, T3> &lhs,
    const interleaved_datum_3d<T1, T2, T3> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2 ||
      lhs._data_3 != rhs._data_3); 
  }
}
