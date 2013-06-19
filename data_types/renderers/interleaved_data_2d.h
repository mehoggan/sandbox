#ifndef INTERLEAVED_DATA_2D_H_INCLUDED
#define INTERLEAVED_DATA_2D_H_INCLUDED

#include <glext.h>
#include <types/interleaved/interleaved_datum_2d.h>

namespace glext
{
  template <typename T1, typename T2>
  struct interleaved_data_2d
  {
  public:
    /*! \brief determine type of the first interleaved type
     */
    typedef T1 internal_type1;

    /*! \brief determine type of the second interleaved type
     */
    typedef T2 internal_type2;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<interleaved_datum_2d<T1, T2> > _data;
   
    /*! \brief default constructor
     */
    interleaved_data_2d();

    /*! \brief constructor
     */
    interleaved_data_2d(
      const std::vector<interleaved_datum_2d<T1, T2> > &data);

    /*! \brief copy constructor
     */
    interleaved_data_2d(const interleaved_data_2d &rhs);

    /*! \brief destructor
     */
    ~interleaved_data_2d();

    /*! \brief assignment uses copy-swap idiom
     */
    interleaved_data_2d &operator=(interleaved_data_2d &rhs);

    /*! \brief data size
     */
    size_t size_of() const;

    /*! \brief offset to type one
     */
    size_t t1_offset() const;

    /*! \brief offset to type two
     */
    size_t t2_offset() const;

    /*! \brief stride to get to next type within _data
     */
    size_t stride() const;
  };
}

#include "interleaved_data_2d.inl"
#endif
