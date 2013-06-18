namespace glext
{
  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_datum_4d<T1, T2, T3, T4>::interleaved_datum_4d() :
    _datum1(T1(0)),
    _datum2(T2(0)),   
    _datum3(T3(0)),
    _datum4(T4(0))    
  {}

  template <typename T1, typename T2, typename T3, typename T4>        
  interleaved_datum_4d<T1, T2, T3, T4>::interleaved_datum_4d(const T1 &datum_1, 
    const T2 &datum_2, const T3 &datum_3, const T4 &datum_4)
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
  interleaved_datum_4d &interleaved_datum_4d<T1, T2, T3, T4>::operator=(
    interleaved_datum_4d<T1, T2, T3, T4> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  } 

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3, typename T4>
  void swap(renderer_datum_1d<T1, T2, T3, T4> &lhs, 
    renderer_data_1d<T1, T2, T3, T4> &rhs)
  {
    std::swap(lhs._datum1, rhs._datum1);
    std::swap(lhs._datum2, rhs._datum2);
    std::swap(lhs._datum3, rhs._datum3);
    std::swap(lhs._datum4, rhs._datum4);
  }

  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator==(const interleaved_datum_4d<T1> &lhs, 
    const interleaved_datum_4d<T1> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2 &&
      lhs._data_3 == rhs._data_3 && lhs._data_4 == rhs._data_4); 
  }
  
  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator!=(const interleaved_datum_4d<T1> &lhs, 
    const interleaved_datum_4d<T1> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2 ||
      lhs._data_3 != rhs._data_3 || lhs._data_4 != rhs._data_4); 
  }
}

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
  interleaved_data_4d &interleaved_data_4d<T1, T2, T3, T4>::operator=(
    interleaved_data_4d<T1, T2, T3, T4> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3, typename T4>
  void swap(interleaved_data_1d<T1, T2, T3, T4> &lhs, 
    interleaved_data_1d<T1, T2, T3, T4> &rhs)
  {
    lhs._data.swap(rhs.data);
  }

  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator==(const interleaved_data_4d<T1> &lhs, 
    const interleaved_data_4d<T1> &rhs)
  {   
    return (lhs._data == rhs._data); 
  }
  
  template <typename T1, typename T2, typename T3, typename T4>        
  bool operator!=(const interleaved_data_4d<T1> &lhs, 
    const interleaved_data_4d<T1> &rhs)
  {
    return (lhs._data != rhs._data); 
  }
}
