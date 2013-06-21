#ifndef RENDERER_1D_H_INCLUDED
#define RENDERER_1D_H_INCLUDED

#include <glext.h>

namespace glext
{
  template <typename T1>
  struct renderer_data_1d
  {
  public:
    /*! \brief tells the renderers how many types to load in batch mode
     */
    uint8_t _type_count;
  
    /*! \brief determine type of the first renderer type
     */
    typedef T1 internal_type1;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<T1> _data_1;
   
    /*! \brief Data to be loaded into a vbo
     */
    std::vector<null_type> _data_2;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<null_type> _data_3;

    /*! \brief Data to be loaded into a vbo
     */
    std::vector<null_type> _data_4;

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

    /*! \brief if all data is in same vbo then this points to first element
     * in the vbo of type T1
     */
    size_t t1_offset() const;

    /*! \brief data size
     */
    size_t size_of() const;

    /*! \brief if all data is in same vbo then this points to last element
     * in the vbo of type T1 when added to t1_offset()
     */
    size_t data1_size_of() const;
  };
}

#include "renderer_data_1d.inl"
#endif
