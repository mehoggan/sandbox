#include <stdlib.h>
#include <stdio.h>

/*
 *	Bitwise Operators C Programming Language
 *	Brian W. Kernighan and Dennis M. Ritchie
 *	Bitwise Operators Exercise 2-6 - 2-8
 */

unsigned int getbits ( unsigned int x, int p, int n ) {
	/*
	 *	Shift digits to right mask with
	 *	n 1s right justified
	 */
	return ( x >> ( p + 1 - n )) & ~( ~0 << n );
}

unsigned int setbits ( unsigned int x, int p, int n, unsigned int y ) {
	/*
	 *	By Matthew Hoggan
	 */
	unsigned int iYmask = ( y & ~( ~0 << n ) ) << ( p - n - 1 );
	unsigned int iXmask = ~( ( x & ~( ~0 << n ) ) << ( p - n - 1 ) ) ;
	x &= iXmask;
	x |= iYmask;
	return x;
}

int main ( int argc, char** argv ) {
	unsigned int x = 0x0000006F;
	unsigned int y = 0x0000000F;
	printf ( "The value calculated for %x, %x = %x\n", x, y, setbits ( x, 10, 5, y ) );
}
