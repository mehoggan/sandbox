#include <png.h>
#include <stdlib.h>

static png_structp png_ptr;
static png_infop info_ptr;
static png_bytep old_row = NULL;

/* Variable that loops untill data is read */
int run = 0;

//-------------------------------------------------------------------
// Callbacks
int read_chunk_callback(png_structp png_ptr, png_unknown_chunkp chunk)
{
  struct chunk
  {
    png_byte name[5];
    png_byte *data;
    png_size_t size;
  };

  return (0); /* did not recognize */
}

/*
 * This method will be called each time a row is read
 * and differs from the row_callback in that ...
 */
void read_row_callback(png_structp ptr, png_uint_32 row, int pass)
{
  fprintf(stderr, "read_row_callback\n");
}

int process_data(png_bytep buffer, png_uint_32 length)
{
  fprintf(stderr, "process_data\n");
  png_process_data(png_ptr, info_ptr, buffer, length);
  return 0;
}

void info_callback(png_structp png_ptr, png_infop info)
{
  fprintf(stderr, "info_callback\n");
  png_uint_32 width;
  png_uint_32 height;
  int         bit_depth;
  int         color_type;
  int         interlace_type;
  int         compression_type;
  int         filter_type;
  png_byte    channels;
  png_uint_32 rowbytes;
  png_bytep   signature;

  /*
   * This will get the information stored in the header
   * of the PNG file.
   */
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, 
    &color_type, &interlace_type, &compression_type, &filter_type);

  /*
   * Get the rest of the header information.
   */
  channels = png_get_channels(png_ptr, info_ptr);
  /* This is subject to change with transformations */
  rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  signature = png_get_signature(png_ptr, info_ptr);

  fprintf(stdout,
    "width: %u"
    "height: %u"
    "bit_depth: %d"
    "color_type: %d"
    "interlace_type: %d"
    "compression_type: %d"
    "filter_type: %d"
    "channles: %d"
    "rowbytes: %u"
    "signature: %s", 
    (unsigned int)width, 
    (unsigned int)height, 
    bit_depth, 
    color_type,
    interlace_type, 
    compression_type, 
    filter_type, 
    channels,         
    (unsigned int)rowbytes, 
    signature);
}

void row_callback(png_structp png_ptr, png_bytep new_row, 
  png_uint_32 row_num, int pass)
{
  fprintf(stderr, "row_callback\n");
  png_progressive_combine_row(png_ptr, old_row, new_row);
}

void end_callback(png_structp png_ptr, png_infop info)
{
  fprintf(stderr, "end_callback\n");
  run = 1;
}

/*
 * Error handler local to his translation unit
 * Used by png_create_read_struct function.
 */
void progressive_reader_error_fn(png_structp png_ptr, 
  png_const_charp msg)
{
  fprintf(stderr, "error: %s\n", msg);
  fflush(stderr);
  longjmp(png_jmpbuf(png_ptr), 1);
  exit(0);
}

//-------------------------------------------------------------------

/*
 * Free PNG resources on close
 */
void free_png_resources() 
{
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  png_ptr = NULL;
  info_ptr = NULL;

}

/*
 * All strings to this function must
 * be null terminated -- return 0 if
 * file is not in png format
 */
int check_png_sig(const char * file_name)
{
  FILE *fp = fopen(file_name, "rb");
  if(!fp) {
    return (0);
  }
  enum HeaderSize {Size = 8};
  png_byte header[Size];
  fread(header, 1, Size, fp);
  int is_png = !png_sig_cmp(header, 0, Size);
  if (!is_png) {
    fclose(fp);
    return (0);
  }
  fclose(fp);
  return (1);
}

/*
 * Create the png_structp and png_infop
 */
int create_png_structs()
{
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
    progressive_reader_error_fn, NULL);
  if (!png_ptr) {
    return 0;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return 0;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    return 0;
  }

  return 1;
}

/*
 * This method does all the work
 */
int read_png_file(const char * file_name)
{
  fprintf(stdout, "Reading PNG File %s\n", file_name);
  fflush(stdout);

  if (!png_ptr || !info_ptr) {
    return (0);
  }

  FILE *fp = fopen(file_name, "rb");
  if(!fp) {
    return (0);
  }

  png_init_io(png_ptr, fp);
  png_voidp user_chunkp = png_get_user_chunk_ptr(png_ptr);

  /*
   * Tell libpng to call read_chunk_callback if an unknown chunk is
   * encountered
   */
  png_set_read_user_chunk_fn(png_ptr, user_chunkp, 
    read_chunk_callback);

  /*
   * Tell libpng to call read_row_callback if an known chunk is
   * encountered.
   */
  png_set_read_status_fn(png_ptr, read_row_callback);

  /*
   * Tell libpng to call the specified functions on info, rows, or
   * end.
   */
  png_set_progressive_read_fn(png_ptr, user_chunkp, info_callback,
    row_callback, end_callback);

  enum Size {DataSize = 8};
  unsigned char rawbuf[DataSize];
  int process = 1;
  if (setjmp(png_jmpbuf(png_ptr))) {
    free_png_resources();
    process = 0;
    return process;
  }

  /*
   * Check to see if libpng is confused
   */
  //png_set_sig_bytes(png_ptr, 8);

  while (process) {
    memset(rawbuf, 0, DataSize);
    png_process_data(png_ptr, info_ptr, rawbuf, DataSize);
  }

  fclose(fp);
  return (process);
}

int main(int argc, char *argv[])
{
  if (check_png_sig("./png_file.png")) {
    if (create_png_structs()) {
      if (read_png_file("./png_file.png")) {
        fprintf(stderr, "SUCCESS!!!\n");
      }   
    }
  } 
  return 0;
}
