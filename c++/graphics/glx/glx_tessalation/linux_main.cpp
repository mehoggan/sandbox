#include <iostream>
#include <exception>
#include "map.h"

//Global Data
static Map *gsp_Map;

int 
main(int argc, char *argv[]) {
  try {
    gsp_Map = Map::create(800, 600, argc, argv);
    gsp_Map->run();
    delete gsp_Map;
  } catch (map_error e) {
    std::cerr << "Failed to create map " << e.what() << std::endl;
  }
}
