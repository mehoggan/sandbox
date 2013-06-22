namespace glext
{
  /// Constructor
  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::batch_indexed_renderer() :
    _vertex_count(0),
    _byte_count(0),
    _byte_count1(0),
    _byte_count2(0),
    _byte_count3(0),
    _byte_count4(0),
    _index_count(0),
    _index_byte_count(0),
    _vbo_id(0),
    _index_id(0)
  {}

  /// Destructor
  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::~batch_indexed_renderer()
  {}

  /// Methods that act on the VBO
  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  void batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::destroy_resources()
  {
    if (_vbo_id) {
      glBindBuffer(render_target, _vbo_id);
      glDeleteBuffers(_byte_count, &_vbo_id);
      _vbo_id = 0;
    }
    if (_index_id) {
      glBindBuffer(render_target, _index_id);
      glDeleteBuffers(_index_byte_count, &_index_id);
      _index_id = 0;
    }
  }

  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  bool batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::bind()
  {
    glBindBuffer(render_target, _vbo_id);
    return true;
  }

  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  bool batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::index_bind()
  {
    if (!_index_id) {
      return false;
    }

    glBindBuffer(index_target, _index_id);
    return true;
  }

  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  void batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::unbind()
  {
    glBindBuffer(render_target, 0);
  }

  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  bool batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::load_data(render_data_type &data,
      std::vector<index_primitive_type> &indices, GLsizei buffer_count)
  {
    if (_vbo_id) {
      destroy_resources();
    }

    _vertex_count = data._data_1.size();
    _byte_count = data.size_of();

    glGenBuffers(buffer_count, &_vbo_id);
    if (bind()) {
      glBufferData(render_target, _byte_count, NULL, render_usage);
      switch (data._type_count) {
      case (4): {
        _byte_count4 = data.data4_size_of();
        glBufferSubData(render_target, data.t4_offset(), data.data4_size_of(),
          data._data_4.data());
      }
      case (3): {
        _byte_count3 = data.data3_size_of();
        glBufferSubData(render_target, data.t3_offset(), data.data3_size_of(),
          data._data_3.data());
      }
      case (2): {
        _byte_count2 = data.data2_size_of();
        glBufferSubData(render_target, data.t2_offset(), data.data2_size_of(),
          data._data_2.data());
      }
      case (1): {
        _byte_count1 = data.data1_size_of();
        glBufferSubData(render_target, data.t1_offset(), data.data1_size_of(),
          data._data_1.data());
      }
        break;
      default: {
        return false;
      }
      }
    } else {
      return false;
    }

    _index_count = indices.size();
    _index_byte_count = _index_count * sizeof(index_primitive_type);
    glGenBuffers(buffer_count, &_index_id);
    if (index_bind()) {
      glBufferData(index_target, _index_byte_count, indices.data(),
        render_usage);
    } else {
      return false;
    }

    return true;
  }

  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  bool batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::draw_data(GLint start, GLsizei count)
  {
    if (!_vbo_id || !_index_id || start + count > _index_count) {
      return false;
    }

    if (count == 0) {
      count = _index_count;
    }

    glDrawElements(render_primitive_mode, count, index_type, (GLvoid *)start);

    return true;
  }

  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  bool batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::modify_data(render_data_type &data, data_set set, GLsizeiptr start)
  {
    if (!_vbo_id) {
        return false;
      }

      if (!bind()) {
        return false;
      }
      switch(set)
      {
      case(set4): {
        GLsizeiptr byte_count = data.data4_size_of();
        start += (_byte_count1 + _byte_count2 + _byte_count3);
        if ((start + byte_count) > _byte_count) {
          return false;
        }
        glBufferSubData(render_target, start, byte_count, data._data_4.data());
      }
        break;
      case(set3): {
        GLsizeiptr byte_count = data.data3_size_of();
        start += (_byte_count1 + _byte_count2);
        if ((start + byte_count) > _byte_count1 + _byte_count2 + _byte_count3) {
          return false;
        }
        glBufferSubData(render_target, start, byte_count, data._data_3.data());
      }
        break;
      case(set2): {
        GLsizeiptr byte_count = data.data2_size_of();
        start += (_byte_count1);
        if ((start + byte_count) > _byte_count1 + _byte_count2) {
          return false;
        }
        glBufferSubData(render_target, start, byte_count, data._data_2.data());
      }
        break;
      case(set1): {
        GLsizeiptr byte_count = data.data1_size_of();
        start += 0;
        if ((start + byte_count) > _byte_count1) {
          return false;
        }
        glBufferSubData(render_target, start, byte_count, data._data_1.data());
      }
        break;
      }
      unbind();

      return true;
  }

  template
  <
    typename render_data_type,
    typename index_primitive_type,
    render_primitive_mode_enum render_primitive_mode,
    index_type_enum index_type,
    render_usage_enum render_usage,
    render_target_enum render_target,
    render_target_enum index_target
  >
  bool batch_indexed_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::modify_indices(std::vector<index_primitive_type> &indices,
    GLsizeiptr start)
  {
    GLsizeiptr index_count = indices.size();
    GLsizeiptr index_byte_count = index_count * sizeof(index_primitive_type);
    if (index_bind() && start + index_byte_count < _index_byte_count) {
      glBufferData(index_target, start, index_byte_count, indices.data());
    } else {
      return false;
    }

    return true;
  }
}
