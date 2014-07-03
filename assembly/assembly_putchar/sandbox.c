#include <unistd.h>
#include <sys/syscall.h>

void main()
{
    char *str = "Hello World";
    
    while(*(str) != '\0') {
        //printf("%c", *(str++));
        //syscall(__NR_write, 1, *(str++), 1);
        asm volatile ( 
                       "movl $0X4, %%eax\n"
                       "movl $0X1, %%ebx\n"
                       "movl $0X1, %%edx\n"
                       "int $0X80"
                       : /* outputs none */
                       : /* inputs : */ "c" (str)
                       : /* clobbers: */ "%eax", "%ebx", "%edx"
                     );
        str++;
    }
    return;
}
