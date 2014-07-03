/*
 * Write a function setbits(x,p,n,y) that returns x with the n bits
 * that begin at position p set to the rightmost n bits of y, leaving
 * the other bits unchanged in the least number of lines.
 *
 * Note: function signatures and curly brackets dont count towards 
 * the number of lines. You must also declare your variables, and 
 * call the function
 *
 * Next write a function invert(x,p,n) that returns x with the n bits
 * that begin at position p inverted, leaving the others unchanged
 *
 * Next write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n bit positions
 *
 * build with:
 *   gcc -o bit_twiddle -Wall -g -lm ./bit_twiddle.c
 */

#include <stdio.h>
#include <math.h>
#include <limits.h>

size_t size_of_int = sizeof(int) << 3;

void printbits(unsigned x) {
    unsigned mask = 1 << (size_of_int - 1);
    int i = 0;
    for(i = 1; i <= size_of_int; ++i, x <<= 1) {
       ((x & mask) == 0) ? printf("0") : printf("1");
       (((i % 4))==0) ? printf(" ") : printf("%s","");
    }
    printf("\n");
}

void rightrot(unsigned x, unsigned n) {
    printf("%15s =", "rightrot"); printbits((((~(~0 << n)) & x) << (size_of_int - n)) | (x >> n));
}

void invert(unsigned x, unsigned p, unsigned n) {
    printf("%15s =", "invert"); printbits((~(~0 << n) << p) ^ x);
}

void setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
    printf("%15s =", "setbits"); printbits((x |= (y & ~(~0 << n)) << p));
}

int main(int argc, char *argv[]) {
    unsigned input=4042322167, nbits=4;
    unsigned begin=8;
    unsigned data=16;
    printf("%15s =", "x"); printbits(input);
    printf("%15s =", "y"); printbits(data);
    setbits(input, begin, nbits, data);
    invert(input, begin, nbits);
    rightrot(input, nbits);
    return(0);
}
