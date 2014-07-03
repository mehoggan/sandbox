#include <set>
#include <string>
#include <fstream>
//#include "file_to_map.h"
#include "code_finder.h"

int main(int argc, char *argv[])
{
  code_finder cf("/home/mehoggan/Display/Runtime/Core/Map/GraphicsPipeline", "opengl_functions");
  cf.run();
  return 0;
}
