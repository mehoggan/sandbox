#include <pngfilereader.h>
#include <stdexcept>

PNGFileReader::PNGFileReader()
{
}

PNGFileReader::~PNGFileReader()
{
}

// Public Exposed API
void PNGFileReader::compress_raw_to_png(uint8_t data, int size)
{ 
}

void PNGFileReader::decompress_png_to_raw(const std::string &path)
{
  read_png(path);
}

// Getters
long unsigned int PNGFileReader::get_image_width()
{
  return m_ImageWidth;
}

long unsigned int PNGFileReader::get_image_height()
{
  return m_ImageHeight;
}

// Private Methods
bool PNGFileReader::read_png(const std::string &path)
{
  /* 
   * Open up the file to read (path) in binary mode
   * first so that if anything goes wrong with libpng
   * we won't have much to undo
   */
  const char *c_path = path.c_str();
  FILE *fp = fopen(c_path, "rb");
  if (!fp)
    return PNGFileReader::ERROR;
  
  /*
   * Read the first BYTES_TO_READ bytes from file
   * then determine if it is a png file or 
   * not. If png_sig_cmp == 0 all is okay
   */
  enum {BYTES_TO_READ = 8};
  unsigned char sig[BYTES_TO_READ];
  if (!fread(sig, 1, BYTES_TO_READ, fp))
  {
    fclose(fp);
    return PNGFileReader::ERROR;
  }

  bool is_png = !png_sig_cmp(sig, 0, BYTES_TO_READ);
  if (!is_png)
  {
    fclose(fp);
    return PNGFileReader::ERROR;   
  }

  /* 
   * Create the pointer to main libpng struct, as well as
   * two info structs to maintain information after, and
   * prior to all operations on png data. Only necessary
   * to release resource after function succeeds.
   */
  m_pPNG = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL,
    NULL, NULL);
  if (!m_pPNG)
  {
    fclose(fp);
    return PNGFileReader::ERROR;
  }
  m_pPNGInfo = png_create_info_struct(m_pPNG);
  if (!m_pPNGInfo)
  {
    png_destroy_read_struct(&m_pPNG, (png_infopp)NULL,(png_infopp)NULL);
    fclose(fp);
    return PNGFileReader::ERROR;
  }
  m_pPNGEndInfo = png_create_info_struct(m_pPNG);
  if (!m_pPNGEndInfo)
  {
    png_destroy_read_struct(&m_pPNG, &m_pPNGInfo, (png_infopp)NULL);
    fclose(fp);
    return PNGFileReader::ERROR;
  }

  /*
   * For error handling purposes. Set a long pointer
   * back to this function to handle all error related
   * to file IO
   */
  if (setjmp(png_jmpbuf(m_pPNG)))
  {
    png_destroy_read_struct(&m_pPNG, &m_pPNGInfo, &m_pPNGEndInfo);
    fclose(fp);
    return PNGFileReader::ERROR;
  }
  
  /* 
   * Set up the input code for FILE openend in binary mode,
   * and tell libpng we have already read BYTES_TO_READ btyes from 
   * signature
   */
  png_init_io(m_pPNG, fp);
  png_set_sig_bytes(m_pPNG, BYTES_TO_READ);

  /*
   * Using the lowlevel interface to lib png ...
   */
  png_read_info(m_pPNG, m_pPNGInfo);
  png_uint_32 width; // Holds width of the image in pixels(up to 2^31)
  png_uint_32 height; // Holds height of the image in pixesl (up to 2^31)
  int bitDepth; // Holds the bit depth of one of the image channels 
                //(power of 2)
  int colorType; // see (http://www.libpng.org/pub/png/
                 // libpng-1.2.5-manual.html)
  
  width = png_get_image_width(m_pPNG, m_pPNGInfo);
  height = png_get_image_height(m_pPNG, m_pPNGInfo);
  bitDepth = png_get_bit_depth(m_pPNG, m_pPNGInfo);
  colorType = png_get_color_type(m_pPNG, m_pPNGInfo);

  /*
   * Before any PNG can be correctly displayed, the application needs to 
   * know what the display gama is. Only monitor gama is needed in a 
   * bright room, else a slightly smaller exponent is needed.
   */
  double gama, screen_gama;
  char *gama_cstr = getenv("SCREEN_GAMMA");
  if (gama_cstr != NULL)
  {
    screen_gama = (double)atof(gama_cstr);
    std::cout << "Screen Gama acquired from environment: " << screen_gama
      << std::endl;
  }
  else 
  {
    /* Good Gama Value for a PC in bright room */
    screen_gama = 2.2;
    std::cout << "Screen Gama preset: " << screen_gama << std::endl;
  }
  
  std::vector<std::vector<png_byte> > row_pointers;
  int bytes_per_row = png_get_rowbytes(m_pPNG, m_pPNGInfo);
  for (int i = 0; i < height; ++i)
  {
    std::vector<png_byte> row;
    row_pointers.push_back(rowa);
    row_pointers[i].resize(png_get_rowbytes(m_pPNG, m_pPNGInfo));
  }

  //png_read_image(m_pPNG, row_pointers);

  /*
  if (row_pointers != NULL)
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < bytes_per_row; ++j)
      std::cout << row_pointers[i][j];
    std::cout << std::endl;

  for (int i = 0; i < height; ++i)
  {
    if (row_pointers[i])
    {
      delete row_pointers[i];
      row_pointers[i] = NULL;
    } 
  } 
  if (row_pointers)
  {
    delete row_pointers;
    row_pointers = NULL;
  }

  png_read_end(m_pPNG, NULL);
  png_destroy_read_struct(&m_pPNG, &m_pPNGInfo, &m_pPNGEndInfo);
  fclose(fp);
  //*/
}








