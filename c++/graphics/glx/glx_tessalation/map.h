#ifndef MAP_H_
#define MAP_H_

/*
 * C headers
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xmu/StdCmap.h>
#include <X11/keysym.h>

/*
 * C++ style headers
 */
#include <string>
#include <iostream>
#include <cmath>

class map_error : public std::exception
{
public:
  map_error(std::string &error) throw ()
  {
    m_error = error;
  }
  ~map_error() throw ()
  {
  }
  std::string &what() {
    return m_error;
  }
private:
  std::string m_error;
};

class Map
{
public:
  static bool s_status_ok;
  static Map *create(int width, int height, int argc, char *argv[]);
  void set_deminsions(int width, int height);
  void render_data();
  void run();
protected:
  Map(int width, int height, int argc, char *argv[]);
  void initialize_window(int width, int height, int argc, char *argv[]);
  void generate_map();
  GLfloat m_xAngle;
  GLfloat m_yAngle;
  GLfloat m_zAngle;
  void inc_xrotate(GLfloat deg);
  void inc_yrotate(GLfloat deg);
  void inc_zrotate(GLfloat deg);
  void initialize_gl();
private:
  void process_args(int argc, char *argv[]);
  void process_flags();
  void connect_to_Xserver();
  void verify_glX();
  void select_double_buffer_Xvisual();
  void set_shareable_colormap(unsigned int visualid); 
  void create_window(int argc, char *argv[]);
  void tessalate_and_extrude(GLfloat data[][2], unsigned int dataSize,
                           GLdouble thickness, GLuint side, GLuint edge,
                           GLuint whole);
  static Map *map_instance;
  pthread_t m_render_thread;
  bool m_render;
  bool m_update;
  bool m_update_viewport;
  bool m_status_ok;
  GLdouble m_body_width;
  struct glx_data
  {
    Display *dpy;
    Window win;
    XVisualInfo *vi;
    Colormap cmap;
    XSetWindowAttributes swa;
    GLXContext cx;
    XEvent event;
    XWMHints *wmHints;
    Atom wmDeleteWindow;
    KeySym ks;
    XSizeHints szHints;
    bool iconic;
    bool keep_aspect;
    char *display;
    char *geometry;
    int x_o;
    int y_o;
    unsigned int win_width;
    unsigned int win_height;
  } m_glx_data;
};

#endif//MAP_H_
