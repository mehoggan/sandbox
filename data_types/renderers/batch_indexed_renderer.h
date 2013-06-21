#ifndef BATCH_INDEXED_RENDERER_H_INCLUDED
#define BATCH_INDEXED_RENDERER_H_INCLUDED

#include <glext.h>

namespace glext
{
  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode = triangles,
    index_type_enum index_type = unsigned_short,
    render_usage_enum render_usage = dynmaic_draw,
    render_target_enum render_target = array_buffer,
    render_target_enum index_target = element_array_buffer
  >
  class batch_indexed_renderer
  {
  private:
    GLsizeiptr vertex_count_;
    GLsizeiptr byte_count_;
    GLuint vbo_id_;

  public:
    /*! \brief Basic Constructor
     */
    batch_indexed_renderer();

    /*! \brief Basic Destructor
     */
    ~batch_indexed_renderer();

    /*! \brief Before this object goes out of scope call this method to release
     * the data in the VBO
     */
    void destroy_resources();

    /*! \brief Make sure the ID associated with the VBO is bound before use
     */
    bool bind();

    /*! \brief Set the current ID to 0 to keep unbind all buffers
     */
    void unbind();

    /*! \brief Based on the templated type this method loads interleaved
     * types into
     */
    bool load_data(render_data_type &data,
      std::vector<index_primitive_type> &indices, GLsizei buffer_count = 1);

    /*! \brief Make sure the ID is bound by calling bind, then this method
     * will request that OpenGL draw the data in your array
     */
    bool draw_data(GLint start = 0, GLsizei count = 0);

    /*! \brief This allows the user to modify a subset of the data based on the
     * data passed in
     */
    bool modify_data(render_data_type &data, GLsizeiptr start_index);

    /*! \brief This allows the user to modify a subset of the indices based on
     * the data passed in
     */
    bool modify_indices(std::vector<index_primitive_type> &indices,
      GLsizeiptr start_index = 0);
  };
}

#include "batch_indexed_renderer.inl"
#endif
