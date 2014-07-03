#ifndef MATRIX_CHAIN_H_
#define MATRIX_CHAIN_H_

typedef struct matrix {
	char *name;
	int R;
	int C;
	int dim;
	struct matrix* (*concat_matrices)( struct matrix *A, struct matrix *B );
	struct matrix* (*clone_matrix)( struct matrix *from );
	void (*print_matrix)( struct matrix *self );
} Matrix;

void set_matrix_functions( Matrix *M );
#endif
