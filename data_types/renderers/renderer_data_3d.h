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
    renderer_data_3d(const std::vector<T1> &data_1, const std::vector<T2> &data_2,
      const std::vector<T3> &data_3);

    /*! \brief copy constructor
     */
    renderer_data_3d(const renderer_data_3d &rhs);

    /*! \brief destructor
     */
    ~renderer_data_3d();

    /*! \brief assignment uses copy-swap idiom
     */
    renderer_data_3d &operator=(renderer_data_3d &rhs);
  };
}

#include "renderer_data_3d.h"
#endif
