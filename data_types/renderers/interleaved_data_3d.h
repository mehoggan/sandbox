#ifndef INTERLEAVED_3D_H_INCLUDED
#define INTERLEAVED_3D_H_INCLUDED

#include <glext.h>

namespace glext
{
  template <typename T1, typename T2, typename T3>
  struct interleaved_datum_3d
  {
  public:
    /*! \brief determine type of the first interleaved type
     */
    typedef T1 internal_type1;

    /*! \brief determine type of the second interleaved type
     */
    typedef T2 internal_type2;

    /*! \brief determine type of the third interleaved type
     */
    typedef T3 internal_type3;

    /*! \brief first component in interleaved data 
     */
    T1 _datum1;
    
    /*! \brief second component in interleaved data
     */
    T2 _datum2;

    /*! \brief second component in interleaved data
     */
    T3 _datum3;

    /*! \brief default constructor
     */
    interleaved_datum_3d();

    /*! \brief constructor
     */
    interleaved_datum_3d(const T1 &datum_1, const T2 &datum_2, const T3 &datum_3);

    /*! \brief copy constructor
     */
    interleaved_datum_3d(const interleaved_datum_3d &rhs);

    /*! \brief destructor
     */
    ~interleaved_datum_3d();

    /*! \brief assignment uses copy-swap idiom
     */
    interleaved_datum_3d &operator=(interleaved_datum_3d &rhs);
  };

  template <typename T1, typename T2, typename T3>
  struct interleaved_data_3d
  {
  public:
    /*! \brief determine type of the first interleaved type
     */
    typedef T1 internal_type1;

    /*! \brief determine type of the second interleaved type
     */
    typedef T2 internal_type2;

    /*! \brief determine type of the second interleaved type
     */
    typedef T3 internal_type3;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<interleaved_datum_3d<T1, T2, T3> > _data;
   
    /*! \brief default constructor
     */
    interleaved_data_3d();

    /*! \brief constructor
     */
    interleaved_data_3d(
      const std::vector<interleaved_datum_3d<T1, T2, T3> > &data);

    /*! \brief copy constructor
     */
    interleaved_data_3d(const interleaved_data_3d &rhs);

    /*! \brief destructor
     */
    ~interleaved_data_3d();

    /*! \brief assignment uses copy-swap idiom
     */
    interleaved_data_3d &operator=(interleaved_data_3d &rhs);
  };
}

#include "interleaved_data_3d.h"
#endif
