#include "pngfilereader.h"
#include "filereader.h"
#include <stdexcept>


PNGFileReader::PNGFileReader(const std::string &path) :
  _m_ImageData(NULL),
  _m_pPNG(NULL),
  _m_pPNGInfo(NULL)
{
  /*
   * Check if first 8 bytes are the correct PNG header
   */
  enum {BYTES_TO_READ = 8};
  unsigned char sig[BYTES_TO_READ];
  FileReader(path, sig, BYTES_TO_READ);
  bool not_png = png_sig_cmp(sig, 0, BYTES_TO_READ);
  if (not_png) {
    throw std::runtime_error("Your file is not of PNG format");
  }

  /*
   * Create the png structs using a FILE *. libpng requires
   * this type and will not take a C++ stream
   */
  _m_CFilePointer = fopen(path.c_str(), "rb");
  if (!_m_CFilePointer) {
    throw std::runtime_error("Failure to open PNG file");
  }
  if (!_create_png_structs()) {
    throw std::runtime_error("Failure to create PNG structs");
  }

  /*
   * Initialize PNG io and read data into PNG structs
   */
  png_init_io(_m_pPNG, _m_CFilePointer);
  png_read_info(_m_pPNG, _m_pPNGInfo);
  _m_ImageHeight = png_get_image_height(_m_pPNG, _m_pPNGInfo);
  _m_ImageWidth = png_get_rowbytes(_m_pPNG, _m_pPNGInfo);

  /*
   * Create sufficient PNG Space and Read Image in all at
   * once into users data. Note that you have to use png's
   * types to prevent sigabrt (6) while freeing memory.
   */
  _m_ImageData = (png_bytepp)png_malloc(_m_pPNG,
    sizeof(png_bytep)*_m_ImageHeight);
  if (_m_ImageData == NULL) {
    throw std::runtime_error("Memory allocation failure");
  }
  memset(_m_ImageData, 0, static_cast<size_t>(_m_ImageHeight));
  for (unsigned long int i = 0; i < _m_ImageHeight; ++i) {
    _m_ImageData[i] = (png_bytep)png_malloc(_m_pPNG,
      sizeof(png_byte)*_m_ImageWidth);
    if (_m_ImageData[i] == NULL) {
      throw std::runtime_error("Memory allocation failure.");
    }
  }
  png_read_image(_m_pPNG, _m_ImageData);
  png_read_end(_m_pPNG, NULL);
  fclose(_m_CFilePointer);
  _m_CFilePointer = NULL;
}

PNGFileReader::~PNGFileReader()
{
  if (_m_CFilePointer) {
    fclose(_m_CFilePointer);
  }
  /*
   * Free all resources (-1)
   */
  png_free_data(_m_pPNG, _m_pPNGInfo, PNG_FREE_ALL, -1);
  for (unsigned long int i = 0; i < _m_ImageHeight; ++i) {
    png_free(_m_pPNG, _m_ImageData[i]);
  }
  free(_m_ImageData);
  png_destroy_read_struct(&_m_pPNG, &_m_pPNGInfo, NULL);
}
// Getters
long unsigned int PNGFileReader::get_image_width() const
{
  return _m_ImageWidth;
}

long unsigned int PNGFileReader::get_image_height() const
{
  return _m_ImageHeight;
}


void PNGFileReader::convert_to_bmp(const std::string &path)
{
  unsigned long width = get_image_width();
  unsigned long height = get_image_height();

  std::ofstream out_file;
  for (unsigned long i = 0; i < height; ++i) {
    for (unsigned long j = 0; j < width; ++j) {
      png_byte c = _m_ImageData[i][j];
      out_file << c;
    }
  }
}

// Private helper functions
bool PNGFileReader::_create_png_structs()
{
  /*
   * Create the pointer to main libpng struct, as well as
   * two info structs to maintain information after, and
   * prior to all operations on png m_Data. Only necessary
   * to release resource after function succeeds.
   */
  _m_pPNG = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL,
    NULL, NULL);
  if (!_m_pPNG){
    return PNGFileReader::ERROR;
  }

  _m_pPNGInfo = png_create_info_struct(_m_pPNG);
  if (!_m_pPNGInfo) {
    return PNGFileReader::ERROR;
  }

  return PNGFileReader::SUCCESS;
}
