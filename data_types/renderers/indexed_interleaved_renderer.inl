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
  indexed_interleaved_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::indexed_interleaved_renderer()
  {

  }

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
  indexed_interleaved_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::~indexed_interleaved_renderer()
  {

  }

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
  void indexed_interleaved_renderer
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
  bool indexed_interleaved_renderer
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
  void indexed_interleaved_renderer
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
  bool indexed_interleaved_renderer
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
  bool indexed_interleaved_renderer
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
  bool indexed_interleaved_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::modify_data(render_data_type &data, GLsizeiptr start_index)
  {
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
  bool indexed_interleaved_renderer
  <
    render_data_type,
    index_primitive_type,
    render_primitive_mode,
    index_type,
    render_usage,
    render_target,
    index_target
  >::modify_indices(std::vector<index_primitive_type> &indices,
    GLsizeiptr start_index)
  {
    return true;
  }
}
