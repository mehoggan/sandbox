#ifndef interleaved_renderer_H_INCLUDED
#define interleaved_renderer_H_INCLUDED

#include <glext.h>

namespace glext
{
  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode = triangles,
    render_usage_enum render_usage = dynmaic_draw,
    render_target_enum render_target = array_buffer
  >
  class interleaved_renderer
  {
  private:
    GLsizeiptr _vertex_count;
    GLsizeiptr _byte_count;
    GLuint _vbo_id;

  public:
    /*! \brief Basic Constructor
     */
    interleaved_renderer();

    /*! \brief Basic Destructor
     */
    ~interleaved_renderer();

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
    bool load_data(render_data_type &data, GLsizei buffer_count = 1);

    /*! \brief Make sure the ID is bound by calling bind, then this method
     * will request that OpenGL draw the data in your array
     */
    bool draw_data(GLint start = 0, GLsizei count = 0);

    /*! \brief This allows the user to modify a subset of the data based on the
     * data passed in
     */
    bool modify_data(render_data_type &data, GLsizeiptr start_index = 0);
  };
}

#include "interleaved_renderer.inl"
#endif
