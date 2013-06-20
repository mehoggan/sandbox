namespace glext
{
  template <typename T1, typename T2>        
  interleaved_datum_2d<T1, T2>::interleaved_datum_2d()
  {}

  template <typename T1, typename T2>        
  interleaved_datum_2d<T1, T2>::interleaved_datum_2d(const T1 &datum_1, 
    const T2 &datum_2) :
    _datum1(datum_1),
    _datum2(datum_2)    
  {}

  template <typename T1, typename T2>        
  interleaved_datum_2d<T1, T2>::interleaved_datum_2d(
    const interleaved_datum_2d<T1, T2> &rhs) :
    _datum1(rhs._datum1),
    _datum2(rhs._datum2)
  {}

  template <typename T1, typename T2>        
  interleaved_datum_2d<T1, T2>::~interleaved_datum_2d()
  {}

  template <typename T1, typename T2>        
  interleaved_datum_2d<T1, T2> &interleaved_datum_2d<T1, T2>::operator=(
    interleaved_datum_2d<T1, T2> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  } 

  /// Copy and swap idiom
  template <typename T1, typename T2>
  void swap(interleaved_datum_2d<T1, T2> &lhs,
    interleaved_datum_2d<T1, T2> &rhs)
  {
    std::swap(lhs._datum1, rhs._datum1);
    std::swap(lhs._datum2, rhs._datum2);
  }

  template <typename T1, typename T2>        
  bool operator==(const interleaved_datum_2d<T1, T2> &lhs,
    const interleaved_datum_2d<T1, T2> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2); 
  }
  
  template <typename T1, typename T2>        
  bool operator!=(const interleaved_datum_2d<T1, T2> &lhs,
    const interleaved_datum_2d<T1, T2> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2); 
  }
}
