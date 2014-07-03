#include "apue.h"

#define BUFFSIZE 4096

/* 
 * To run non-interactivly type the following at the command line
 * ../bin/stdout_to_stdin < intput_file > output_file
 */

int
main(void)
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
    
    if (n < 0)
        err_sys("read error");

    exit(0);
}
