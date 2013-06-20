#ifndef INTERLEAVED_DATA_3D_H_INCLUDED
#define INTERLEAVED_DATA_3D_H_INCLUDED

#include <glext.h>
#include <types/interleaved/interleaved_datum_3d.h>

namespace glext
{
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

    /*! \brief data size
     */
    size_t size_of() const;

    /*! \brief offset to type one
     */
    size_t t1_offset() const;

    /*! \brief offset to type two
     */
    size_t t2_offset() const;

    /*! \brief offset to type three
     */
    size_t t3_offset() const;

    /*! \brief stride to get to next type within _data
     */
    size_t stride() const;
  };
}

#include "interleaved_data_3d.inl"
#endif
