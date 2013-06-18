#ifndef RENDERER_2D_H_INCLUDED
#define RENDERER_2D_H_INCLUDED

#include <glext.h>

namespace glext
{
  template <template T1, template T2>
  struct renderer_data_2d
  {
  public:
    /*! \brief determine type of the first renderer type
     */
    typedef T1 internal_type1;

    /*! \brief determine type of the second renderer type
     */
    typedef T2 internal_type2;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<T1> _data_1;
   
    /*! \brief Data to be loaded into a vbo
     */
    std::vector<T2> _data_2;

    /*! \brief default constructor
     */
    renderer_data_2d();

    /*! \brief constructor
     */
    renderer_data_2d(std::vector<T1> &data_1, std::vector<T2> &data_2);

    /*! \brief copy constructor
     */
    renderer_data_2d(const renderer_data_2d &rhs);

    /*! \brief destructor
     */
    ~renderer_data_2d();

    /*! \brief assignment uses copy-swap idiom
     */
    renderer_data_2d &operator=(renderer_data_2d &rhs);
  };
}

#include "renderer_data_2d.h"
#endif
