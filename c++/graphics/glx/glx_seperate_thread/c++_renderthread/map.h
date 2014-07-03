#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Map
{
public:
  static bool s_status_ok;
  static Map *create(int width, int height);
  void set_deminsions(int width, int height);
  void render_data();
  void run();
protected:
  bool initialize_window(int width, int height);
  GLfloat m_xAngle;
  GLfloat m_yAngle;
  GLfloat m_zAngle;
  void inc_xrotate(GLfloat deg);
  void inc_yrotate(GLfloat deg);
  void inc_zrotate(GLfloat deg);
  Map(int width, int height);
private:
  static Map *map_instance;
  pthread_t m_render_thread;
  bool m_render;
  bool m_update;
  bool m_update_viewport;
  bool m_status_ok;
  int m_width;
  int m_height;
  struct glx_data
  {
    Display *dpy;
    Window win;
    XVisualInfo *vi;
    Colormap cmap;
    XSetWindowAttributes swa;
    GLXContext cx;
    XEvent event;
    int dummy;
    bool double_buffer;
  } m_glx_data;
};

#endif//MAP_H_
