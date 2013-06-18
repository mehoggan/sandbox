#ifndef RENDERER_1D_H_INCLUDED
#define RENDERER_1D_H_INCLUDED

#include <glext.h>

namespace glext
{
  template <typename T1>
  struct renderer_data_1d
  {
  public:
    /*! \brief determine type of the first renderer type
     */
    typedef T1 internal_type1;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<T1> _data_1;

    /*! \brief default constructor
     */
    renderer_data_1d();

    /*! \brief constructor
     */
    renderer_data_1d(const std::vector<T1> &data_1);

    /*! \brief copy constructor
     */
    renderer_data_1d(const renderer_data_1d &rhs);

    /*! \brief destructor
     */
    ~renderer_data_1d();

    /*! \brief assignment uses copy-swap idiom
     */
    renderer_data_1d &operator=(renderer_data_1d &rhs);
  };
}

#include "renderer_data_1d.h"
#endif
