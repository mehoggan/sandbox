#ifndef INTERLEAVED_DATUM_4D_H_INCLUDED
#define INTERLEAVED_DATUM_4D_H_INCLUDED

#include <glext.h>

namespace glext
{
  template <typename T1, typename T2, typename T3, typename T4>
  struct interleaved_datum_4d
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

    /*! \brief determine type of the third interleaved type
     */
    typedef T4 internal_type4;

    /*! \brief first component in interleaved data 
     */
    T1 _datum1;
    
    /*! \brief second component in interleaved data
     */
    T2 _datum2;

    /*! \brief third component in interleaved data
     */
    T3 _datum3;
    
    /*! \brief fourth component in interleaved data
     */
    T4 _datum4;

    /*! \brief default constructor
     */
    interleaved_datum_4d();

    /*! \brief constructor
     */
    interleaved_datum_4d(const T1 &datum_1, const T2 &datum_2,
      const T3 &datum_3, const T4 &datum_4);

    /*! \brief copy constructor
     */
    interleaved_datum_4d(const interleaved_datum_4d &rhs);

    /*! \brief destructor
     */
    ~interleaved_datum_4d();

    /*! \brief assignment uses copy-swap idiom
     */
    interleaved_datum_4d &operator=(interleaved_datum_4d &rhs);
  };
}

#include "interleaved_datum_4d.inl"
#endif
