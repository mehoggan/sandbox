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
  >::batch_renderer()
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
    return true;
  }
}
