#include <iostream>
#include "RendererGL.h"

bool rotate = true;
extern "C"
void inc_x_val()
{
}

extern "C" void *create_render_thread(void *data)
{
  RendererGL *thread_render = static_cast<RendererGL *>(data);
  thread_render->render();
  return data;
}

RendererGL::RendererGL(int width, int height) :
  m_bRender(false),
  m_bHandleEvents(false),
  m_bUpdateWindow(false),
  m_xAngle(42.0),
  m_yAngle(82.0),
  m_zAngle(112.0),
  m_width(width),
  m_height(height)
{
  int mutex_creation = pthread_mutex_init(&m_tRenderLock, NULL);
  if(mutex_creation != 0) {
    std::cerr << "Failed to create mutex" << std::endl;                                   // Use RAII if resource acquisition fails
    return;
  }

  int mutex_cond_creation = pthread_cond_init(&m_tRenderLockCondition, NULL);
  if(mutex_cond_creation != 0) {
    std::cerr << "Failed to create condition mutex" << std::endl;                         // Use RAII if resource acquisition fails
    return;
  }

  int thread_creation = pthread_create(&m_tRenderThread, NULL, create_render_thread, this);
  if(thread_creation != 0) {
    std::cerr << "Failed to create thread" << std::endl;                                  // Use RAII if resource acquisition fails
    return;
  }

  if (!initialize_window()) {
    return;
  } else {
    //long int utime = 1000000 * 1;
    //m_oTimeMngr.addTimer(utime, inc_x_val);
    m_bHandleEvents = true;
  }
}

RendererGL::~RendererGL()
{
  pthread_mutex_lock(&m_tRenderLock);
  m_bRender = false;
  m_glxWnd.dpy = NULL;
  m_glxWnd.win = NULL;
  void *result;
  pthread_join(m_tRenderThread, &result);
  pthread_mutex_unlock(&m_tRenderLock);
  pthread_cond_destroy(&m_tRenderLockCondition);
  pthread_mutex_destroy(&m_tRenderLock);
}

bool RendererGL::initialize_window()
{
  m_glxWnd.dpy = XOpenDisplay(NULL);
  if (m_glxWnd.dpy == NULL) {
    std::cerr << "Failed to get XDisplay" << std::endl;
    return false;
  }
  if (!glXQueryExtension( m_glxWnd.dpy,
              &m_glxWnd.dummy,
              &m_glxWnd.dummy)) {
    std::cerr << "X server has no OpenGL GLX extension" << std::endl;
    return false;
  }

  static
  int dblBuf[] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1,
             GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12,
             GLX_DOUBLEBUFFER, None };

  m_glxWnd.vi = glXChooseVisual( m_glxWnd.dpy,
                           DefaultScreen(m_glxWnd.dpy),
                           dblBuf);
  if (m_glxWnd.vi == NULL) {
    std::cerr << "No RGB visual with depth buffer" << std::endl;
    return false;
  }
  m_glxWnd.cmap = XCreateColormap( m_glxWnd.dpy,
                   RootWindow(
                        m_glxWnd.dpy,
                        (m_glxWnd.vi)->screen
                                 ),
                   (m_glxWnd.vi)->visual,
                   AllocNone);
  m_glxWnd.swa.colormap = m_glxWnd.cmap;
  m_glxWnd.swa.border_pixel = 0;
  m_glxWnd.swa.event_mask = ExposureMask | ButtonPressMask | StructureNotifyMask;
  m_glxWnd.win = XCreateWindow( m_glxWnd.dpy,
                                RootWindow(m_glxWnd.dpy, (m_glxWnd.vi)->screen),
                                0, 0,
                                m_width, m_height,
                                0,
                                (m_glxWnd.vi)->depth,
                                InputOutput,
                                (m_glxWnd.vi)->visual,
                                CWBorderPixel | CWColormap |
                                CWEventMask,
                                &m_glxWnd.swa
                              );

  XSetStandardProperties( m_glxWnd.dpy,
                          m_glxWnd.win,
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
  XMapWindow(m_glxWnd.dpy, m_glxWnd.win);
  return true;
}

void 
RendererGL::render()
{
  pthread_mutex_lock(&m_tRenderLock);
  while(!m_bRender) {
    pthread_cond_wait(&m_tRenderLockCondition, &m_tRenderLock);
  }
  pthread_mutex_unlock(&m_tRenderLock);


  m_glxWnd.cx = glXCreateContext(m_glxWnd.dpy, m_glxWnd.vi, None, True);
  if (m_glxWnd.cx == NULL) {
    std::cerr << "could not create rendering context" << std::endl;
    exit(0);
  }
  glXMakeCurrent(m_glxWnd.dpy, m_glxWnd.win, m_glxWnd.cx);

  static int mod_three = 0;
  while (m_bRender) {
    pthread_mutex_lock(&m_tRenderLock);
    if (m_bUpdateWindow) {
      glViewport(0, 0, m_width, m_height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60, m_width/m_height, 1, 100);
      m_bUpdateWindow = false;
    }
    pthread_mutex_unlock(&m_tRenderLock);

    if (!m_bRender) {
      break;
    }

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    if(rotate) {
      if(mod_three % 3 == 0)
        inc_xrotate(.10);
      if(mod_three % 3 == 1)
        inc_yrotate(.20);
      if(mod_three % 3 == 2)
        inc_yrotate(.15);
    }
    glRotatef(m_xAngle, 0.1, 0.0, 0.0);
    glRotatef(m_yAngle, 0.0, 1.0, 0.0);
    glRotatef(m_zAngle, 0.0, 0.0, 1.0);
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
    //*/
    pthread_mutex_lock(&m_tRenderLock);
    glXSwapBuffers(m_glxWnd.dpy, m_glxWnd.win);
    pthread_mutex_unlock(&m_tRenderLock);
  }
}

void
RendererGL::run()
{
  while (m_bHandleEvents) {
    do {
      XNextEvent(m_glxWnd.dpy, &m_glxWnd.event);
      switch (m_glxWnd.event.type) {
      case ButtonPress: {
        switch (m_glxWnd.event.xbutton.button) {
        case 1: {
          pthread_mutex_lock(&m_tRenderLock);
          this->inc_xrotate(10);
          pthread_mutex_unlock(&m_tRenderLock);
          break;
        }
        case 2: {
          pthread_mutex_lock(&m_tRenderLock);
          this->inc_yrotate(10);
          pthread_mutex_unlock(&m_tRenderLock);
          break;
        }
        case 3: {
          pthread_mutex_lock(&m_tRenderLock);
          this->inc_zrotate(10);
          pthread_mutex_unlock(&m_tRenderLock);
          break;
        }
        break;
        }
        break;
      }
      case ConfigureNotify: {
        unsigned int w = m_glxWnd.event.xconfigure.width;
        unsigned int h = m_glxWnd.event.xconfigure.height;
        pthread_mutex_lock(&m_tRenderLock);
        set_deminsions(w, h);
        pthread_mutex_unlock(&m_tRenderLock);
      }
      case Expose: {
        if (m_height != 0) {
          if (!m_bRender) {
            pthread_mutex_lock(&m_tRenderLock);
            m_bRender = true;
            pthread_cond_signal(&m_tRenderLockCondition);
            pthread_mutex_unlock(&m_tRenderLock);
          } else {
            pthread_mutex_lock(&m_tRenderLock);
            m_bUpdateWindow = true;
            pthread_mutex_unlock(&m_tRenderLock);
          }
        }
        break;
      }
      }
    } while (XPending(m_glxWnd.dpy));
  }
}

inline void
RendererGL::inc_xrotate(float deg)
{
  if ((m_xAngle + deg) < 360) {
    m_xAngle += deg;
  } else {
    m_xAngle = deg - (360 - m_xAngle);
  }
}

inline void
RendererGL::inc_yrotate(float deg)
{
  if ((m_yAngle + deg) < 360) {
    m_yAngle += deg;
  } else {
    m_yAngle = deg - (360 - m_yAngle);
  }
}

inline void
RendererGL::inc_zrotate(float deg)
{
  if ((m_zAngle + deg) < 360) {
    m_zAngle += deg;
  } else {
    m_zAngle = deg - (360 - m_zAngle);
  }
}

inline void
RendererGL::set_deminsions(int width, int height)
{
  m_width = width;
  m_height = height;
}
