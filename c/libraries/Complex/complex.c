//complex.c
#include <stdio.h>
#include "complex.h"

void add(complex_t *const dest, const complex_t *const src) {
	if ( !assert_ptr_not_null((void*)dest) || !assert_ptr_not_null((void*)src) ) {
		fprintf(stderr, "NULL Pointers passed");
	        return;
	}

	dest->real = dest->real + src->real;
	dest->imaginary = dest->imaginary + src->imaginary;
}

static int assert_ptr_not_null(void *ptr) {
	if (ptr == NULL) return 0;
        return 1;
}
