#include "apue.h"
#include <fcntl.h>
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
char buf3[10];

int
main(void)
{
  int fd;

  if ((fd = creat("file.hole", FILE_MODE)) < 0) {
    err_sys("creat error");
  }

  if (write(fd, buf1, 10) != 10) {                                             /* offset is now = 10 */
    err_sys("buf1 write error");
  }

  if (lseek(fd, 16380, SEEK_SET) == -1) {                                      /* offset now = 16380 */
    err_sys("lseek error");                            
  }

  if (write(fd, buf2, 10) != 10) {                                             /* offset now = 16390 */
    err_sys("buf2 write error");
  }
  close(fd);

  if ((fd = open("file.hole", O_RDWR)) == -1) {
    err_sys("failed to re-open file");
  }

  ssize_t n;
  ssize_t m;
  while ((n = read(fd, buf3, 10)) > 0) {
    if ((m = write(STDOUT_FILENO, buf3, 10)) != 10) {
      err_sys("stdout write error");
    }
  }
  
  if (n == -1) {
    err_sys("buf3 read error");
  }
  exit(0);
}
