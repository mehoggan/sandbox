#include <stdio.h>
#include <inttypes.h>
typedef union INSPECTOR {
    uint8_t   b[8];
    uint64_t  l;
    double    f;
} INSPECTOR;

int main( int argc, char *argv[])
{
    int i,ii;
    double number[] = {
        0,1,-1,0.0/0.0,1.0/0.0,-1.0/0.0,2,4,8,16,8.642135E130
    };
    for (i=0;i<11;i++){
        INSPECTOR native;
        native.f = number[i];
        printf("%16e -> ",native.f);
        for (ii=0;ii<8;ii++)
            printf(" %02x",native.b[ii]);
        printf("\n");
    }
    return 0;
}
