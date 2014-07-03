#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>

/*
 * Arrays used to pass frame buffer capabilities
 * be passed to glXChooseVisual() to determine
 * what visual to use.
 */
static int snglBuf[] = { 
                         GLX_RGBA, GLX_RED_SIZE,
                         1, GLX_GREEN_SIZE, 1,
                         GLX_BLUE_SIZE, 1,
                         GLX_DEPTH_SIZE, 12, None
                       };

static int dblBuf[] = { 
                        GLX_RGBA, GLX_RED_SIZE,
                        1, GLX_GREEN_SIZE, 1,
                        GLX_BLUE_SIZE, 1,
                        GLX_DEPTH_SIZE, 12,
                        GLX_DOUBLEBUFFER, None
                      };

Display *dpy;
Window win;
Bool doubleBuffer = True;

/* Initial 3D box orientation */
GLfloat xAngle = 42.0;
GLfloat yAngle = 82.0;
GLfloat zAngle = 112.0;

void fatalError(char *err) {
  fprintf(stderr, err);
}

void
redraw(void) {
  static Bool displayListInited = False;
  if (displayListInited) {
    /* 
     * If disply list alread exists, just execute
     * it.
     */
    glCallList(1);
  } else {
    /* Otherwise, compile and execute to create
     * the display list
     */
    glNewList(1, GL_COMPILE_AND_EXECUTE);
      glClear(
              GL_COLOR_BUFFER_BIT | 
              GL_DEPTH_BUFFER_BIT
             );
      glBegin(GL_QUADS);
        // Front face
        glColor3f(0.0, 0.7, 0.1); // Green
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        // Back face
        glColor3f(0.9, 1.0, 0.0); // Yellow
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(1.0, 1.0, -1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);
        // Top face
        glColor3f(0.2, 0.2, 1.0); // Blue
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        // Bottom face
        glColor3f(0.7, 0.0, 0.1); // Red
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);
      glEnd();
    glEndList();
    displayListInited = True;
  } 
  if (doubleBuffer) {
    /*
     * Buffer swap does implict glFlush.
     */  
    glXSwapBuffers(dpy, win);
  } else {
    /* 
     * Explicit flush for single buffered case.
     */
    glFlush();
  }
}

int
main(int argc, char **argv)
{
  XVisualInfo *vi;
  Colormap cmap;
  XSetWindowAttributes swa;
  GLXContext cx;
  XEvent event;
  Bool needRedraw = False;
  Bool recalcModelView = True;
  int dummy;

  /* 
   * Step 1: Open communication to the X server 
   */
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
      fatalError("could not open display");
  }

  /*
   * Step 2: Make sure OpenGL's GLX extension is
   * supported GLX. glXQueryExtension() returns
   * the GLX extension's error base and event
   * base.
   */
  if (!glXQueryExtension(dpy, &dummy, &dummy)) {
    fatalError(
               "X server has no OpenGL GLX" 
               "extension"  
              );
   }

   /*
    * Step 3: Find an appropriate OpenGL-capable
    * visual. Look for double buffering first;
    * if it is not found, settle for a single
    * buffered visual
    */
  vi = glXChooseVisual(
                       dpy, 
                       DefaultScreen(dpy),
                       dblBuf
                      );
  if (NULL == vi) {
    vi = glXChooseVisual(
                         dpy, 
                         DefaultScreen(dpy), 
                         snglBuf
                        );
    if (vi == NULL) {
      fatalError("no RGB visual with depth buffer");
    }
    doubleBuffer = False;
  }
  if (vi->class != TrueColor) {
    fatalError("TrueColor visual required for this program");
  }
    
  /* 
   * Step 4: Create an OpenGL rendering context
   */
  cx = glXCreateContext(
                        dpy, 
                        vi,
                        None, /* 
                               * No sharing of
                               * display lists
                               */                                 
                        True //Direct rendering
                       ); 
  if (NULL == cx) {
    fatalError("could not create rendering context");
  }                   

  /*
   * Step 5: Create an X window with the selected
   * visual. Since the visual selected is likely
   * not to be the default, create an X colormap
   * for use.
   */ 
  cmap = XCreateColormap( 
                         dpy, 
                         RootWindow(
                                    dpy,
                                    vi->screen
                                   ),
                         vi->visual,
                         AllocNone);
  swa.colormap = cmap;
  swa.border_pixel = 0;
  swa.event_mask = ExposureMask | ButtonPressMask |
                   StructureNotifyMask;
  win = XCreateWindow(
                      dpy,
                      RootWindow(
                                 dpy, 
                                 vi->screen
                                ),
                      0,
                      0,
                      300,
                      300,
                      0,
                      vi->depth,
                      InputOutput,
                      vi->visual,
                      CWBorderPixel | CWColormap |
                      CWEventMask,
                      &swa
                    );

  XSetStandardProperties(
                         dpy,
                         win,
                         "glxsimple",
                         "glxsimple",
                         None,
                         argv, 
                         argc,
                         NULL
                        );
  /*
   * Step 6: Bind the rendering context to the
   * window
   */
  glXMakeCurrent(dpy, win, cx);

  /*
   * Step 7: Request that the X window be
   * displayed on the screen
   */
  XMapWindow(dpy, win);

  /*
   * Step 8: Configure the OpenGL context for
   * rendering
   */
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);

  /*
   * Step 9: Dispatch X events. The program
   * handles only three even types
   * 1. Mouse
   * 2. Expose
   * 3. ???
   */
  while (1) {
    do {
      XNextEvent(dpy, &event);
      switch (event.type) {
      case ButtonPress:
        recalcModelView = True;
        switch (event.xbutton.button) {
        case 1:
          xAngle += 10.0;
          break;
        case 2:
          yAngle += 10.0;
          break;
        case 3:
          zAngle += 10.0;
          break;
        }
        break;
      case ConfigureNotify:
        glViewport(
                   0, 
                   0, 
                   event.xconfigure.width,
                   event.xconfigure.height
                  );
      // Fall through
      case Expose:
        needRedraw = True;
        break;
      }
    } while (XPending(dpy)); /* 
                              * Loop to compress
                              *  events. 
                              */
    if (recalcModelView) {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0, 0.0, -3.0);
      glRotatef(xAngle, 0.1, 0.0, 0.0);
      glRotatef(yAngle, 0.0, 0.1, 0.0);
      glRotatef(zAngle, 0.0, 0.0, 1.0);
      recalcModelView = False;
      needRedraw = True;
    }
    if (needRedraw) {
      redraw();
      needRedraw = False;
    }
  }
  
  return 0;    
}















