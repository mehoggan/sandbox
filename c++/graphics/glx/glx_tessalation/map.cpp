#include "map.h"

Map *Map::map_instance = 0;
bool Map::s_status_ok = false;

extern "C" void *create_pthread(void *data)
{
  Map *thread_map = static_cast<Map *>(data);
  thread_map->render_data();
  return data;
}

XErrorHandler XSetErrorHandler(XErrorHandler handler);

Map* Map::create(int width, int height, int argc, char *argv[]) 
{
  if (map_instance == 0) {
    Map::s_status_ok = false;
    try {
      map_instance = new Map(width, height, argc, argv);
    } catch (map_error e) {
      throw e;
    }
  }
  return map_instance;
}

Map::Map(int width, int height, int argc, char *argv[])
{
  std::string e("Error: could not initialize map");
  try {  
    initialize_window(width, height, argc, argv);
    Map::s_status_ok = true;
    if (pthread_create(&m_render_thread, NULL, create_pthread, this) != 0) {
      Map::s_status_ok = false;
      std::string e("Error: could not initialize thread");
      throw map_error(e);
    }
  } catch (map_error e) {
    Map::s_status_ok = false;
    throw e;
  }
}

void
Map::initialize_window(int width, int height, int argc, char *argv[])
{
  m_render = true;
  m_update = true;
  m_update_viewport = true;
  m_xAngle = 42.0;
  m_yAngle = 82.0;
  m_zAngle = 112.0;
  m_glx_data.iconic = false;
  m_glx_data.keep_aspect = false;
  m_glx_data.geometry = 0;
  m_glx_data.win_width = width;
  m_glx_data.win_height = height;
  m_body_width = 2.0;

  try {  
    /* Handle statard X11 and GLX arguments */
    process_args(argc, argv);

    /* Connect to the XServer */
    connect_to_Xserver();

    /* Verivy if GLX extension is supported */
    verify_glX();
    
    /* Tell glX to load a visual with double buffers */
    select_double_buffer_Xvisual();

    /* Get a shared color map for a specific visual id */
    set_shareable_colormap(2);

    /* Process XLib flags */
    process_flags();

    /* Create the X11 Window */
    create_window(argc, argv);    

  } catch (map_error e) {
    throw e;
  }
  XMapWindow(m_glx_data.dpy, m_glx_data.win);
}

void 
Map::process_args(int argc, char *argv[])
{
  /* Handle statard X11 and GLX arguments */
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-geometry") == 0) {
      if (++i >= argc) {
        std::string error_string("Error: invalid argument to -geometry flag");
        throw map_error(error_string);

      } else {
        m_glx_data.geometry = argv[i];
      }
    } else if (strcmp(argv[i], "-display") == 0) {
      if (++i >= argc) {
        std::string error_string("Error: invalid argument to -display flag");
        throw map_error(error_string);
      } else {
        m_glx_data.display = argv[i];
      }
    } else if (strcmp(argv[i], "-iconic") == 0) {
      m_glx_data.iconic = true;
    } else if (strcmp(argv[i], "-keepaspect") == 0) {
      m_glx_data.keep_aspect = true;
    } else if (strcmp(argv[i], "-single") == 0) {
      m_glx_data.keep_aspect = false;
    } else {
      std::string error_string("Error: Unknown flag");
      error_string += std::string(argv[i]);
      throw map_error(error_string);
    }
  }
}

void
Map::process_flags() {
  unsigned int flags;
  int x = 0;
  int y = 0;
  unsigned int width = 0;
  unsigned int height = 0;
  flags = XParseGeometry(
                          m_glx_data.geometry, 
                          &x,
                          &y,
                          &width,
                          &height
                        );
  if (WidthValue & flags) {
    m_glx_data.szHints.flags |= USSize;
    m_glx_data.szHints.width = width;
  } 
  if (HeightValue & flags) {
    m_glx_data.szHints.flags |= USSize;
    m_glx_data.szHints.height = height;
  }
  if (XValue & flags) {
    if (XNegative & flags) {
      x = DisplayWidth(m_glx_data.dpy, DefaultScreen(m_glx_data.dpy)) + x - m_glx_data.szHints.width;
      m_glx_data.szHints.flags |= USPosition;
      m_glx_data.szHints.x = x;
    }
  }
  if (YValue & flags) {
    if (YNegative & flags) {
      y = DisplayHeight(m_glx_data.dpy, DefaultScreen(m_glx_data.dpy)) + y - m_glx_data.szHints.height;
      m_glx_data.szHints.flags |= USPosition;
      m_glx_data.szHints.y= y;
    }
  }
  if (m_glx_data.keep_aspect) {
    m_glx_data.szHints.flags |= PAspect;
    m_glx_data.szHints.min_aspect.x = m_glx_data.szHints.max_aspect.x = m_glx_data.szHints.x;
    m_glx_data.szHints.min_aspect.y = m_glx_data.szHints.max_aspect.y = m_glx_data.szHints.y;
  }
}

void 
Map::connect_to_Xserver() 
{
  m_glx_data.dpy = XOpenDisplay(NULL);
  if (m_glx_data.dpy == NULL) {
    std::string error_string("Error: faile to get XDisplay");
    throw map_error(error_string);
  }
}

void 
Map::verify_glX() 
{
  if (!glXQueryExtension( m_glx_data.dpy, NULL, NULL)) {
    std::string error_string("Error: glx extension not supported");
    throw map_error(error_string);
  }
}

void
Map::select_double_buffer_Xvisual() 
{
  const
  int configuration[] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE,
                          1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12,
                          GLX_DOUBLEBUFFER, None };

  m_glx_data.vi = glXChooseVisual(
                                   m_glx_data.dpy,
                                   DefaultScreen(m_glx_data.dpy),
                                   const_cast<int*>(configuration)
                                 );
  if (NULL == m_glx_data.vi) {
    std::string error_string("Error: No Double Buffer Support");
    throw map_error(error_string);
  }
}

void 
Map::set_shareable_colormap(unsigned int visualid) 
{
  Status status;
  XStandardColormap *standard_colormap;
  int i;
  int num_c_maps;
  
  /* Use ICCCM's function for sharing colormaps */
  status = XmuLookupStandardColormap(
                                      m_glx_data.dpy,
                                      m_glx_data.vi->screen,
                                      m_glx_data.vi->visualid,
                                      m_glx_data.vi->depth,
                                      XA_RGB_DEFAULT_MAP,
                                      False, //replace
                                      True   //retain
                                    );
  if (status == 1) {
    status = XGetRGBColormaps(
                              m_glx_data.dpy,
                              RootWindow(
                                          m_glx_data.dpy,
                                          m_glx_data.vi->screen
                                        ),
                              &standard_colormap,
                              &num_c_maps, XA_RGB_DEFAULT_MAP
                            );
    if (status == 1) {
      for (i = 0; i < num_c_maps; ++i) {
        if (standard_colormap[i].visualid == visualid) {
          std::cout << "Found match of visualid: " << visualid << std::endl;
          m_glx_data.cmap = standard_colormap[i].colormap;
          XFree(standard_colormap);
          break;
        }
      }
    }                                                              
  }
  m_glx_data.cmap = XCreateColormap(
                                     m_glx_data.dpy,
                                     RootWindow(
                                                 m_glx_data.dpy,
                                                 m_glx_data.vi->screen
                                               ),
                                     m_glx_data.vi->visual,
                                     AllocNone
                                   );            
}

void
Map::create_window(int argc, char *argv[]) {
  m_glx_data.swa.colormap = m_glx_data.cmap;
  m_glx_data.swa.border_pixel = 0;
  m_glx_data.swa.event_mask = ExposureMask | StructureNotifyMask |
                              ButtonPressMask | Button1MotionMask |
                              KeyPressMask;
  m_glx_data.win = XCreateWindow(
                                  m_glx_data.dpy,
                                  RootWindow(
                                              m_glx_data.dpy,
                                              m_glx_data.vi->screen
                                            ),
                                  m_glx_data.szHints.x,
                                  m_glx_data.szHints.y,
                                  m_glx_data.win_width,
                                  m_glx_data.win_height,
                                  0,
                                  m_glx_data.vi->depth,
                                  InputOutput,
                                  m_glx_data.vi->visual,
                                  CWBorderPixel | CWColormap | CWEventMask,
                                  &m_glx_data.swa
                                );
  XSetStandardProperties(
                          m_glx_data.dpy,
                          m_glx_data.win,
                          "OpenGLosaurus",
                          "glxdino",
                          None,
                          argv,
                          argc,
                          &m_glx_data.szHints
                        );
  m_glx_data.wmHints = XAllocWMHints();
  m_glx_data.wmHints->initial_state = m_glx_data.iconic ? IconicState : NormalState;
  m_glx_data.wmHints->flags = StateHint;
  XSetWMHints(m_glx_data.dpy, m_glx_data.win, m_glx_data.wmHints);
  m_glx_data.wmDeleteWindow = XInternAtom(m_glx_data.dpy, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(m_glx_data.dpy, m_glx_data.win, &m_glx_data.wmDeleteWindow, 1);
}

void 
Map::inc_xrotate(GLfloat deg)
{
  if ((m_xAngle + deg) < 360) {
    m_xAngle += deg;
  } else {
    m_xAngle = deg - (360 - m_xAngle);
  }
}

void 
Map::inc_yrotate(GLfloat deg)
{
  if ((m_yAngle + deg) < 360) {
    m_yAngle += deg;
  } else {
    m_yAngle = deg - (360 - m_yAngle);
  }
}

void 
Map::inc_zrotate(GLfloat deg)
{
  if ((m_zAngle + deg) < 360) {
    m_zAngle += deg;
  } else {
    m_zAngle = deg - (360 - m_zAngle);
  }
}

inline void 
Map::set_deminsions(int width, int height)
{
  m_glx_data.win_width = width;
  m_glx_data.win_height = height;
}

void
Map::generate_map()
{
  const GLfloat body[][2] = { {0,   3}, {1,  1}, {5, 1}, {8, 4}, {10, 4}, {11, 5},
                              {11, 11.5}, {13, 12}, {13, 13}, {10, 13.5}, {13, 14}, 
                              {13, 15}, {11, 16}, {8, 16}, {7, 15}, {7, 13}, 
                              {8, 12}, {7, 11}, {6, 6}, {4, 3}, {3, 2}, {1, 2}};
  const GLfloat arm[][2] = { {8, 10}, {9, 9}, {10, 9}, {13, 8}, {14, 9},
                             {16, 9}, {15, 9.5}, {16, 10}, {15, 10}, {15.5, 11}, 
                             {14.5, 10}, {14, 11}, {14, 10}, {13, 9}, {11, 11}, {9, 11}};
  const GLfloat leg[][2] = { {8, 6}, {8, 4}, {9, 3}, {9, 2}, {8, 1}, {8,0.5}, {9, 0}, 
                             {12, 0}, {10, 1}, {10, 2}, {12, 4}, {11, 6}, {10, 7}, 
                             {9, 7}};
  const GLfloat eye[][2] = { {8.75, 15}, {9, 14.7}, {9.6, 14.7}, {10.1, 15}, {9.6, 15.25},
                             {9, 15.25}};

  const GLfloat skinColor[] = {0.1, 1.0, 0.1, 1.0}; /* Green */
  const GLfloat eyeColor[] = {1.0, 0.2, 0.2, 1.0}; /* Red */
  typedef enum { RESERVED, BODY_SIDE, BODY_EDGE, BODY_WHOLE, ARM_SIDE, ARM_EDGE,
                 ARM_WHOLE, LEG_SIDE, LEG_EDGE, LEG_WHOLE, EYE_SIDE, EYE_EDGE,
                 EYE_WHOLE, DINOSAUR
               } displayLists;
              

  GLfloat bodyWidth = 3.0;
  tessalate_and_extrude(const_cast<GLfloat (&)[22][2]>(body), sizeof(body), bodyWidth, BODY_SIDE, BODY_EDGE, BODY_WHOLE);
  tessalate_and_extrude(const_cast<GLfloat (&)[16][2]>(arm), sizeof(arm), bodyWidth/4, ARM_SIDE, ARM_EDGE, ARM_WHOLE);
  tessalate_and_extrude(const_cast<GLfloat (&)[14][2]>(leg), sizeof(leg), bodyWidth/2, LEG_SIDE, LEG_EDGE, LEG_WHOLE);
  tessalate_and_extrude(const_cast<GLfloat (&)[6][2]>(eye), sizeof(eye), bodyWidth + 0.2, EYE_SIDE, EYE_EDGE, EYE_WHOLE);
  
  glNewList(DINOSAUR, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor);
    glCallList(BODY_WHOLE);
    glPushMatrix();
      glTranslatef(0.0, 0.0, bodyWidth);
      glCallList(ARM_WHOLE);
      glCallList(LEG_WHOLE);
      glTranslatef(0.0, 0.0, -bodyWidth - bodyWidth / 4);
      glCallList(ARM_WHOLE);
      glTranslatef(0.0, 0.0, -bodyWidth / 4);
      glCallList(LEG_WHOLE);
      glTranslatef(0.0, 0.0, bodyWidth / 2 - 0.1);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeColor);
      glCallList(EYE_WHOLE);
    glPopMatrix();
  glEndList();
}

void
Map::tessalate_and_extrude(GLfloat data[][2], unsigned int dataSize,
                           GLdouble thickness, GLuint side, GLuint edge,
                           GLuint whole)
{
  GLUtriangulatorObj *tobj = NULL;
  GLdouble vertex[3];
  GLdouble dx;
  GLdouble dy;
  GLdouble len;
  int i;
  int count = dataSize / (2 * sizeof(GLfloat));

  if(tobj == NULL) {
    tobj = gluNewTess();
    gluTessCallback(tobj, GLU_BEGIN, (_GLUfuncptr)glBegin);
    gluTessCallback(tobj, GLU_VERTEX, (_GLUfuncptr)glVertex2fv);
    gluTessCallback(tobj, GLU_END, (_GLUfuncptr)glEnd);
  }
  glNewList(side, GL_COMPILE);
    glShadeModel(GL_SMOOTH);
    gluBeginPolygon(tobj);
    for (i = 0; i < count; i++) {
      vertex[0] = data[i][0];
      vertex[1] = data[i][1];
      vertex[2] = 0;
      gluTessVertex(tobj, vertex, &data[i]);
    }
    gluEndPolygon(tobj);
  glEndList();
  glNewList(edge, GL_COMPILE);
    glShadeModel(GL_FLAT);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= count; i++) {
      glVertex3f(data[i % count][0], data[i % count][1], 0.0);
      glVertex3f(data[i % count][0], data[i % count][1], thickness);
      dx = data[(i + 1) % count][1] - data[i % count][1];
      dy = data[(i % count)][0] - data[(i + 1) % count][0];
      len = sqrt(dx * dx + dy * dy);
      glNormal3f(dx/ len, dy / len, 0.0);
    }
    glEnd();
  glEndList();
  glNewList(whole, GL_COMPILE);
    glFrontFace(GL_CW);
    glCallList(edge);
    glNormal3f(0.0, 0.0, -1.0);
    glCallList(side);
    glPushMatrix();
      glTranslatef(0.0, 0.0, thickness);
      glFrontFace(GL_CCW);
      glNormal3f(0.0, 0.0, 1.0);
      glCallList(side);
    glPopMatrix();
  glEndList();
}

void 
Map::initialize_gl() 
{
  const GLfloat lightZeroPosition[] = {10.0, 4.0, 10.0, 1.0};
  const GLfloat lightZeroColor[] = {0.8, 1.0, 0.8, 1.0}; /* green-tinted */
  const GLfloat lightOnePosition[] = {-1.0, -2.0, 1.0, 0.0};
  const GLfloat lightOneColor[] = {0.6, 0.3, 0.2, 1.0}; /* red-tinted */

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
  glLightfv(GL_LIGHT0, GL_POSITION, const_cast<GLfloat *>(lightZeroPosition));
  glLightfv(GL_LIGHT0, GL_DIFFUSE, const_cast<GLfloat *>(lightZeroColor));
  glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
  
  /* Enable both lights. */
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0, 1.0, 1.0, 40.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 30.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
  
  glPushMatrix();
}

void 
Map::render_data()
{
  sleep(1);
  m_glx_data.cx = glXCreateContext( 
                                     m_glx_data.dpy,
                                     m_glx_data.vi,
                                     None,  
                                     True
                                   );
  if (NULL == m_glx_data.cx) {
    std::cerr << "could not create rendering context" << std::endl;
    std::string e("Failed to get GLX Context");
    throw map_error(e);
  }
  glXMakeCurrent(m_glx_data.dpy, m_glx_data.win, m_glx_data.cx);
  static Bool displayListInited = false;
  while(m_render) {
    if(m_update) {
      glViewport(
                  0, 
                  0, 
                  m_glx_data.win_width, 
                  m_glx_data.win_height
                );
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(
                      60, 
                      m_glx_data.win_width/m_glx_data.win_height, 
                      1, 
                      100
                    );
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      generate_map();
      glXSwapBuffers(m_glx_data.dpy, m_glx_data.win);
      m_update = false;
    }
  }
}

void
Map::run()
{
  while (Map::s_status_ok) {
    do {
      XNextEvent(m_glx_data.dpy, &m_glx_data.event);
      switch (m_glx_data.event.type) {
      case ButtonPress:
        switch (m_glx_data.event.xbutton.button) {
        case 1: {
          this->inc_xrotate(10);
          this->m_update = true;
          break;
        }
        case 2: {
          this->inc_yrotate(10);
          this->m_update = true;
          break;
        }
        case 3: {
          this->inc_zrotate(10);
          this->m_update = true;
          break;
        }
        }
        break;
      case ConfigureNotify: {
        unsigned int w = m_glx_data.event.xconfigure.width;
        unsigned int h = m_glx_data.event.xconfigure.height;
        set_deminsions(w, h);
      }
      case Expose: {
        this->m_update = true;
        break;
      }
      case ClientMessage:
        if (static_cast<unsigned int>(m_glx_data.event.xclient.data.l[0]) ==  m_glx_data.wmDeleteWindow) {
          exit(0);
        }
        break;
      }
    } while (XPending(m_glx_data.dpy));
  }
  pthread_join(m_render_thread, NULL);
}

