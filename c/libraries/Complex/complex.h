// complex.h
#ifndef _COMPLEX_H
#define _COMPLEX_H

typedef struct {
	double real;
	double imaginary;
} complex_t;

void add(complex_t *const dest, const complex_t *const src);
static int assert_ptr_not_null(void *);
#endif
