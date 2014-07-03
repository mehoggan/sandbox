#ifndef GLXWND_H
#define GLXWND_H
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
struct GlxWnd
{
public:
  Display *dpy;
  Window win;
  XVisualInfo *vi;
  Colormap cmap;
  XSetWindowAttributes swa;
  GLXContext cx;
  XEvent event;
  int dummy;
};

#endif // GLXWND_H
