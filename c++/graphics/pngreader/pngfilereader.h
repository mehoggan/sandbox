#ifndef PNG_FILE_READER_H_
#define PNG_FILE_READER_H_

#include "imagedata.h"
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
    // Ctor and Dtor
    PNGFileReader(const std::string &path);
    ~PNGFileReader();
    
    // Converter Functions
    void convert_to_bmp(const std::string &path);

    // Getters
    long unsigned int get_image_width() const;
    long unsigned int get_image_height() const;

    struct PNG_Header
    {
      
    };

  private:
    // Helper functions:
    bool _create_png_structs();

    // Member variables:
    FILE *_m_CFilePointer;
    unsigned long int _m_ImageWidth;
    unsigned long int _m_ImageHeight;
    png_bytepp _m_ImageData;
    png_structp _m_pPNG;
    png_infop _m_pPNGInfo;

    // Enums
    enum PNGBOOL {NOT_PNG, PNG};
    enum PNGERRORS {ERROR, SUCCESS};
};

#endif /* PNG_FILE_READER_H_ */
