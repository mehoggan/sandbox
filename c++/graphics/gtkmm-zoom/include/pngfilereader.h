#ifndef PNG_FILE_READER_H_
#define PNG_FILE_READER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <iostream>
#include <vector>
#include <string>

class PNGFileReader
{
  public:
    PNGFileReader();
    ~PNGFileReader();
    // Public exposed API:
    void compress_raw_to_png(uint8_t data, int size);
    void  decompress_png_to_raw(const std::string &path);
    
    // Getters
    long unsigned int get_image_width();
    long unsigned int get_image_height();

  private:
    // Helper functions:
    bool read_png(const std::string &path);

    // Member variables:
    png_structp m_pPNG;
    png_infop m_pPNGInfo;
    png_infop m_pPNGEndInfo;
    long unsigned int m_ImageWidth;
    long unsigned int m_ImageHeight;

    // Enums
    enum PNGBOOL {NOT_PNG, PNG};
    enum PNGERRORS {ERROR, SUCCESS};
};

#endif /* PNG_FILE_READER_H_ */
