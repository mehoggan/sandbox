#ifndef RENDERERGL_H_
#define RENDERERGL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "GlxWnd.h"
#include "TimerManager.h"

extern "C" {
  void inc_x_val();
}

extern "C" {
  void *create_render_thread(void *data);
}

class RendererGL
{
public:
  RendererGL(int width, int height);
  ~RendererGL();
  void set_deminsions(int width, int height);
  void run();
  void inc_xrotate(float deg);
  void inc_yrotate(float deg);
  void inc_zrotate(float deg);
protected:
  bool initialize_window();
  void render();
  bool m_bRender;
  bool m_bHandleEvents;
  bool m_bUpdateWindow;
  float m_xAngle;
  float m_yAngle;
  float m_zAngle;
private:
  int m_width;
  int m_height;
  GlxWnd m_glxWnd;
  TimerManager m_oTimeMngr;
  pthread_mutex_t m_tRenderLock;
  pthread_t m_tRenderThread;
  pthread_cond_t m_tRenderLockCondition;
  friend void *create_render_thread(void *data);
};

#endif//RENDERERGL_H_
