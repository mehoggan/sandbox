namespace glext
{
  /// Constructor
  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::batch_renderer() :
    _vertex_count(0),
    _byte_count(0),
    _vbo_id(0)
  {

  }

  /// Destructor
  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::~batch_renderer()
  {

  }

  /// Methods that act on the VBO
  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  void batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::destroy_resources()
  {
    if (_vbo_id) {
      glBindBuffer(render_target, _vbo_id);
      glDeleteBuffers(_byte_count, &_vbo_id);
      _vbo_id = 0;
    }
  }

  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  bool batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::bind()
  {
    if (!_vbo_id) {
      return false;
    }

    glBindBuffer(render_target, _vbo_id);
    return true;
  }

  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  void batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::unbind()
  {
    glBindBuffer(render_target, 0);
  }

  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  bool batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::load_data(render_data_type &data, GLsizei buffer_count)
  {
    if (_vbo_id) {
      destroy_resources();
    }

    _vertex_count = data._data_1.size();
    _byte_count = data.size_of();

    glGenBuffers(buffer_count, &_vbo_id);
    if (bind()) {
      glBufferData(render_target, _byte_count, NULL, render_usage);
      switch (_data.type_count) {
      case (4): {
        glBufferSubData(render_target,);
      }
      case (3): {
      
      }
      case (2): {
      
      }
      case (1): {
      
      }
        break;
      default: {
        return;
      }
      }
    } else {
      return false;
    }

    return true;
  }

  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  bool batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::draw_data(GLint start, GLsizei count)
  {
    if (!_vbo_id || start + count > _vertex_count) {
        return false;
      }

      if (count == 0) {
        count = _vertex_count;
      }

      glDrawArrays(render_primitive_mode, start, count);

      return true;
  }

  template
  <
    typename render_data_type,
    render_primitive_mode_enum render_primitive_mode,
    render_usage_enum render_usage,
    render_target_enum render_target
  >
  bool batch_renderer
  <
    render_data_type,
    render_primitive_mode,
    render_usage,
    render_target
  >::modify_data(render_data_type &data, GLsizeiptr start_index)
  {
    if (!_vbo_id) {
      return false;
    }

    //GLsizeiptr byte_count = data.size_of();
    /*
     * TODO -- Check if this is correct
     */
//    if ((start_index * sizeof(render_type) + byte_count) > _byte_count) {
//      return false;
//    }

    glBindBuffer(render_target, _vbo_id);
    //glBufferSubData(render_target, start_index, byte_count, data._data.data());
    glBindBuffer(render_target, 0);

    return true;
  }
}
