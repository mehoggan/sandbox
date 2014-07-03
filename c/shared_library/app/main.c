#include <stdio.h>
#include <limits.h>
#include "c_lib.h"

int main(int argc, char *argv[])
{
    if (argc > 1) {
        char *arg = argv[1];
        printf("%s\n", arg);
    }

    char str[15] = "";
    //itoa(INT_MIN, str);
    //printf("As String : %s\n", str);
    Clib_get_typed_line_EOF(str, 15);
    double y = Clib_atof(str);
    Clib_trim(str);
    printf("%s + 5 = %f\n", str, (y + 5));
    return 1;
}
