//program.c
#include <stdio.h>
#include <stdlib.h>

#include "complex.h"

int main() {
	complex_t *c1 = (complex_t*) malloc(sizeof (complex_t));
	complex_t *c2 = (complex_t*) malloc(sizeof (complex_t));
	c1->real = 10;
	c1->imaginary = 10;
	add(c1, c2);
        printf("%f+%fi\n", c1->real, c1->imaginary);
        printf("%f+%fi\n", c2->real, c2->imaginary);
	free(c1);
	free(c2);
        return 0;
}
