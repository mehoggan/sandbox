#include <stdio.h>
#include <stdlib.h>

unsigned char *data;

int main(int argc, char *argv[])
{
    FILE *fp = fopen("test_out.raw", "rb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: cannot open test_out.raw.\n");
        return -1;
    }

    long int size;    
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    if(size < 0) {
        fprintf(stderr, "ERROR: cannot calculate size of file.\n");
        return -1;
    }
    rewind(fp);

    data = (unsigned char *)calloc(sizeof(unsigned char), size);
    if (data == NULL) {
        fprintf(stderr, "ERROR: cannot create data.\n");
        return -1;
    }
    
    if (!fread(data, sizeof(unsigned char), size, fp)) {
        fprintf(stderr, "ERROR: could not read data into buffer.\n");
        return -1;
    }
    
    int i;
    for (i = 0 ; i < size; ++i) {
        if (i && (i%10) == 0) putchar('\n');
        fprintf(stdout, " --%5.3f-- ", (float)(data[i]/255.0));
    }

    free(data);
    fclose(fp);
    return 0;
}
