#include <iostream>
#include <string>
#include "map.h"

Map *Map::map_instance = 0;
bool Map::s_status_ok = false;

extern "C" void *create_pthread(void *data)
{
  Map *thread_map = static_cast<Map *>(data);
  thread_map->render_data();
  return data;
}

Map* Map::create(int width, int height) 
{
  if (map_instance == 0) {
    Map::s_status_ok = false;
    try {
      map_instance = new Map(width, height);
    } catch (std::exception e) {
      throw e;
    }
  }
  if (Map::s_status_ok) {
    return map_instance;
  } else {
    return 0;
  }
}

Map::Map(int width, int height)
{
  m_width = width;
  m_height = height;
  m_render = true;
  m_update = true;
  m_update_viewport = true;
  m_xAngle = 42.0;
  m_yAngle = 82.0;
  m_zAngle = 112.0;
  if (initialize_window(width, height)) {
    Map::s_status_ok = true;
    if (pthread_create(&m_render_thread, NULL, create_pthread, this) != 0) {
      throw std::exception();
    }
    return;
  } else {
    Map::s_status_ok = false;
  }
}

bool Map::initialize_window(int width, int height)
{
  m_glx_data.dpy = XOpenDisplay(NULL);
  if (m_glx_data.dpy == NULL) {
    std::cerr << "Failed to get XDisplay" << std::endl;
    return false;
  }
  if (!glXQueryExtension( m_glx_data.dpy,
                          &m_glx_data.dummy,
                          &m_glx_data.dummy)) {
    std::cerr << "X server has no OpenGL GLX extension" << std::endl;
    return false;
  }

  static       
  int snglBuf[] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1,
                  GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12, None };

  static       
  int dblBuf[] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1,
                 GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12,
                 GLX_DOUBLEBUFFER, None };

  m_glx_data.vi = glXChooseVisual( m_glx_data.dpy,
                                   DefaultScreen(m_glx_data.dpy),
                                   dblBuf);
  if (NULL == m_glx_data.vi) {
    m_glx_data.vi = glXChooseVisual( m_glx_data.dpy,
                                     DefaultScreen(m_glx_data.dpy),
                                     snglBuf
                                   );
    if (NULL == m_glx_data.vi) {
      std::cerr << "No RGB visual with depth buffer" << std::endl;
      return false;
    }
    m_glx_data.double_buffer = false;
  } else {
    m_glx_data.double_buffer = true;
  }
  m_glx_data.cmap = XCreateColormap( m_glx_data.dpy,
                                     RootWindow(
                                                m_glx_data.dpy,
                                                (m_glx_data.vi)->screen
                                               ),
                                     (m_glx_data.vi)->visual,
                                     AllocNone);
  m_glx_data.swa.colormap = m_glx_data.cmap;
  m_glx_data.swa.border_pixel = 0;
  m_glx_data.swa.event_mask = ExposureMask | ButtonPressMask |
                              StructureNotifyMask;
  m_glx_data.win = XCreateWindow( m_glx_data.dpy,
                                  RootWindow(
                                             m_glx_data.dpy,
                                             (m_glx_data.vi)->screen
                                         ),
                                  0, 0,
                                  width, height,
                                  0,
                                  (m_glx_data.vi)->depth,
                                  InputOutput,
                                  (m_glx_data.vi)->visual,
                                  CWBorderPixel | CWColormap |
                                  CWEventMask,
                                  &m_glx_data.swa
                             );

  XSetStandardProperties(
                         m_glx_data.dpy,
                         m_glx_data.win,
                         "glxsimple",
                         "glxsimple",
                         None,
                         NULL,
                         0,
                         NULL
                        );

  /*
   * Now we can show the window and go to main message loop
   */
  XMapWindow(m_glx_data.dpy, m_glx_data.win);
  return true;
}

inline void 
Map::inc_xrotate(GLfloat deg)
{
  if ((m_xAngle + deg) < 360) {
    m_xAngle += deg;
  } else {
    m_xAngle = deg - (360 - m_xAngle);
  }
}

inline void 
Map::inc_yrotate(GLfloat deg)
{
  if ((m_yAngle + deg) < 360) {
    m_yAngle += deg;
  } else {
    m_yAngle = deg - (360 - m_yAngle);
  }
}

inline void 
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
  m_width = width;
  m_height = height;
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
    return;
  }
  glXMakeCurrent(m_glx_data.dpy, m_glx_data.win, m_glx_data.cx);
  static Bool displayListInited = false;
  glEnable(GL_DEPTH_TEST);
  while(m_render) {
    if(m_update) {
      glViewport(0, 0, m_width, m_height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60, m_width/m_height, 1, 100);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0, 0.0, -3.0);
      glRotatef(m_xAngle, 0.1, 0.0, 0.0);
      glRotatef(m_yAngle, 0.0, 1.0, 0.0);
      glRotatef(m_zAngle, 0.0, 0.0, 1.0);
      if (displayListInited) {
        glCallList(1);
      } else {
        glNewList(1, GL_COMPILE_AND_EXECUTE);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        displayListInited = true;
      }
      if (m_glx_data.double_buffer) {
        glXSwapBuffers(m_glx_data.dpy, m_glx_data.win);
      } else {
        glFlush();
      }
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
      }
    } while (XPending(m_glx_data.dpy));
  }
  pthread_join(m_render_thread, NULL);
}

