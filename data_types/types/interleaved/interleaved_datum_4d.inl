namespace glext
{
  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_datum_4d<T1, T2, T3, T4>::interleaved_datum_4d()
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_datum_4d<T1, T2, T3, T4>::interleaved_datum_4d(const T1 &datum_1, 
    const T2 &datum_2, const T3 &datum_3, const T4 &datum_4) :
    _datum1(datum_1),
    _datum2(datum_2),    
    _datum3(datum_3),
    _datum4(datum_4)
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_datum_4d<T1, T2, T3, T4>::interleaved_datum_4d(
    const interleaved_datum_4d<T1, T2, T3, T4> &rhs) :
    _datum1(rhs._datum1),
    _datum2(rhs._datum2),
    _datum3(rhs._datum3),
    _datum4(rhs._datum4)
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_datum_4d<T1, T2, T3, T4>::~interleaved_datum_4d()
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_datum_4d<T1, T2, T3, T4> &
    interleaved_datum_4d<T1, T2, T3, T4>::operator=(
    interleaved_datum_4d<T1, T2, T3, T4> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  } 

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3, typename T4>
  void swap(interleaved_datum_4d<T1, T2, T3, T4> &lhs,
    interleaved_datum_4d<T1, T2, T3, T4> &rhs)
  {
    std::swap(lhs._datum1, rhs._datum1);
    std::swap(lhs._datum2, rhs._datum2);
    std::swap(lhs._datum3, rhs._datum3);
    std::swap(lhs._datum4, rhs._datum4);
  }

  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator==(const interleaved_datum_4d<T1, T2, T3, T4> &lhs,
    const interleaved_datum_4d<T1, T2, T3, T4> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2 &&
      lhs._data_3 == rhs._data_3 && lhs._data_4 == rhs._data_4); 
  }
  
  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator!=(const interleaved_datum_4d<T1, T2, T3, T4> &lhs,
    const interleaved_datum_4d<T1, T2, T3, T4> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2 ||
      lhs._data_3 != rhs._data_3 || lhs._data_4 != rhs._data_4); 
  }
}
