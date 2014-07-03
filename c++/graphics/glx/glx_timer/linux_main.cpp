#include <iostream>
#include "RendererGL.h"

//Global Data
static RendererGL *gsp_RendererGL;

int 
main(int, char *[]) {
  gsp_RendererGL = new RendererGL(800, 600);
  if (gsp_RendererGL) {
    gsp_RendererGL->run();
    delete gsp_RendererGL;
  } else {
    std::cerr << "Failed to create renderer" << std::endl;
  }
}
