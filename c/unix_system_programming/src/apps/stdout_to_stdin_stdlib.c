#include "apue.h"

#define BUFFSIZE 4096

/* 
 * To run non-interactivly type the following at the command line
 * ../bin/stdout_to_stdin < intput_file > output_file
 */

int
main(void)
{
    int c;

    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            err_sys("write error");
        }
    }
    
    if (ferror(stdin)) {
        err_sys("intput error");
    }

    exit(0);
}
