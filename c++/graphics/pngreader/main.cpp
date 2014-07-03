#include "pngfilereader.h"
#include <iostream>

int main (int argc, char *argv[])
{
  PNGFileReader pngfr("image.png");
  pngfr.convert_to_bmp("my_out.bmp");
  return 0;
}
