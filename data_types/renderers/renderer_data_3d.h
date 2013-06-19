#ifndef RENDERER_3D_H_INCLUDED
#define RENDERER_3D_H_INCLUDED

#include <glext.h>

namespace glext
{
  template <typename T1, typename T2, typename T3>
  struct renderer_data_3d
  {
  public:
    /*! \brief determine type of the first renderer type
     */
    typedef T1 internal_type1;

    /*! \brief determine type of the second renderer type
     */
    typedef T2 internal_type2;

    /*! \brief determine type of the third renderer type
     */
    typedef T3 internal_type3;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<T1> _data_1;
   
    /*! \brief Data to be loaded into a vbo
     */
    std::vector<T2> _data_2;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<T3> _data_3;

    /*! \brief default constructor
     */
    renderer_data_3d();

    /*! \brief constructor
     */
    renderer_data_3d(const std::vector<T1> &data_1,
      const std::vector<T2> &data_2, const std::vector<T3> &data_3);

    /*! \brief copy constructor
     */
    renderer_data_3d(const renderer_data_3d &rhs);

    /*! \brief destructor
     */
    ~renderer_data_3d();

    /*! \brief assignment uses copy-swap idiom
     */
    renderer_data_3d &operator=(renderer_data_3d &rhs);

    /*! \brief if all data is in same vbo then this points to first element
     * in the vbo of type T1
     */
    size_t t1_offset() const;

    /*! \brief if all data is in same vbo then this points to first element
     * in the vbo of type T2
     */
    size_t t2_offset() const;

    /*! \brief if all data is in same vbo then this points to first element
     * in the vbo of type T3
     */
    size_t t3_offset() const;

    /*! \brief data size
     */
    size_t size_of() const;

    /*! \brief if all data is in same vbo then this points to last element
     * in the vbo of type T1 when added to t1_offset()
     */
    size_t data1_size_of() const;

    /*! \brief if all data is in same vbo then this points to last element
     * in the vbo of type T2 when added to t2_offset()
     */
    size_t data2_size_of() const;

    /*! \brief if all data is in same vbo then this points to last element
     * in the vbo of type T3 when added to t3_offset()
     */
    size_t data3_size_of() const;
  };
}

#include "renderer_data_3d.h"
#endif
