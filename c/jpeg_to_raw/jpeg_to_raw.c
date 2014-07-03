#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <unistd.h>

/* we will be using this uninitialized pointer later to store raw, uncompressd image */
unsigned char *raw_image = NULL;
unsigned int size;

/**
 * print the information for what was stored in the JPEG File
 **/
void print_jpeg_info(struct jpeg_decompress_struct cinfo)
{
    printf("JPEG File Information: \n");
    printf("Image width and height: %d pixels and %d pixels.\n", cinfo.image_width, cinfo.image_height);
    printf("Color components per pixel: %d.\n", cinfo.num_components);
    printf("Color space: %d.\n", cinfo.jpeg_color_space);
    printf("Raw flag is: %d.\n", cinfo.raw_data_out);
}

/**
 * read_jpeg_file Reads from a jpeg file on disk specified by filename and saves into the
 * raw_image buffer in an uncompressed format.
 *
 * \returns positive integer if successful, -1 otherwise
 * \param *filename char string specifying the file name to read from
 **/
int read_jpeg_file(char *filename)
{
    /* these are standard libjpeg structures for reading(decompression) */
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    /* libjpeg data structure for storing one row, that is, scanline of an image */
    JSAMPROW row_pointer[1];
    FILE *infile = fopen(filename, "rb");
    unsigned long location = 0;
    int i = 0;
    if (!infile) {
        printf("Error opening jpeg file %s\n!", filename);
        return -1;
    }
    /* here we set up the standard libjpeg error handler */
    cinfo.err = jpeg_std_error(&jerr);
    /* setup decompression process and source, then read JPEG header */
    jpeg_create_decompress(&cinfo);
    /* this makes the library read from infile */
    jpeg_stdio_src(&cinfo, infile);
    /* reading the image header which contains image information */
    jpeg_read_header(&cinfo, TRUE);
    print_jpeg_info(cinfo);
    jpeg_start_decompress(&cinfo);

    /* allocate memory to hold the uncompressed image */
    size = cinfo.output_width*cinfo.output_height*cinfo.num_components;
    raw_image = (unsigned char*)malloc(size);
    /* now actually read the jpeg into the raw buffer */
    row_pointer[0] = (unsigned char *)malloc(cinfo.output_width*cinfo.num_components);
    /* read one scan line at a time */
    while (cinfo.output_scanline < cinfo.image_height) {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for (i=0; i<cinfo.image_width*cinfo.num_components;i++) {
            raw_image[location++] = row_pointer[0][i];
        }
    }
    /* wrap up decompression, destroy objects, free pointers and close open files */
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(row_pointer[0]);
    fclose(infile);
    /* yup, we succeeded! */
    return 1;
}

    int main(int argc, char *argv[])
    {
        char *infilename = "test.jpg";
        if (read_jpeg_file(infilename) > 0) {
            size_t count = size / sizeof(unsigned char);
            fprintf(stdout, "The number of unsigned chars in raw_image = %d\n", (int)count);
            FILE *ofile = fopen("test_out.raw", "w+b");
            ssize_t data_out = fwrite(raw_image, count, sizeof(unsigned char), ofile);
            fprintf(stdout, "%d", (int)data_out);
            fclose(ofile);
        }
        else 
            return -1;
        return 0;
    }
