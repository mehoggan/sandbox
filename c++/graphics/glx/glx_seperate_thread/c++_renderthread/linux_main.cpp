#include <iostream>
#include "map.h"

//Global Data
static Map *gsp_Map;

int 
main(int argc, char *argv[]) {
  try {
    gsp_Map = Map::create(800, 600);
    gsp_Map->run();
    delete gsp_Map;
  } catch (std::exception e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
}
