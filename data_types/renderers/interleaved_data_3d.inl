namespace glext
{
  template <typename T1, typename T2, typename T3>        
  interleaved_datum_3d<T1, T2, T3>::interleaved_datum_3d() :
    _datum1(T1(0)),
    _datum2(T2(0)),   
    _datum3(T3(0))    
  {}

  template <typename T1, typename T2, typename T3>        
  interleaved_datum_3d<T1, T2, T3>::interleaved_datum_3d(const T1 &datum_1, 
    const T2 &datum_2, const T3 &datum_3)
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
  interleaved_datum_3d &interleaved_datum_3d<T1, T2, T3>::operator=(
    interleaved_datum_3d<T1, T2, T3> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  } 

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3>
  void swap(renderer_datum_1d<T1, T2, T3> &lhs, renderer_data_1d<T1, T2, T3> &rhs)
  {
    std::swap(lhs._datum1, rhs._datum1);
    std::swap(lhs._datum2, rhs._datum2);
    std::swap(lhs._datum3, rhs._datum3);
  }

  template <typename T1, typename T2, typename T3>        
  bool operator==(const interleaved_datum_3d<T1> &lhs, 
    const interleaved_datum_3d<T1> &rhs)
  {   
    return (lhs._data_1 == rhs._data_1 && lhs._data_2 == rhs._data_2 &&
      lhs._data_3 == rhs._data_3); 
  }
  
  template <typename T1, typename T2, typename T3>        
  bool operator!=(const interleaved_datum_3d<T1> &lhs, 
    const interleaved_datum_3d<T1> &rhs)
  {
    return (lhs._data_1 != rhs._data_1 || lhs._data_2 != rhs._data_2 ||
      lhs._data_3 != rhs._data_3); 
  }
}

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
  interleaved_data_3d &interleaved_data_3d<T1, T2, T3>::operator=(
    interleaved_data_3d<T1, T2, T3> &rhs)
  {
    swap((*this), rhs);

    return (*this);
  }

  /// Copy and swap idiom
  template <typename T1, typename T2, typename T3>
  void swap(interleaved_data_1d<T1, T2, T3> &lhs, 
    interleaved_data_1d<T1, T2, T3> &rhs)
  {
    lhs._data.swap(rhs.data);
  }

  template <typename T1, typename T2, typename T3>        
  bool operator==(const interleaved_data_3d<T1> &lhs, 
    const interleaved_data_3d<T1> &rhs)
  {   
    return (lhs._data == rhs._data); 
  }
  
  template <typename T1, typename T2, typename T3>        
  bool operator!=(const interleaved_data_3d<T1> &lhs, 
    const interleaved_data_3d<T1> &rhs)
  {
    return (lhs._data != rhs._data); 
  }
}
