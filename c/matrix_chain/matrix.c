#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix* concat_matrices( Matrix *A, Matrix *B ) {
	Matrix* ret = (Matrix*)malloc(sizeof(Matrix));
	set_matrix_functions( ret );
	int len = strlen(A->name) + strlen(B->name) + 4; /* parens + NULL */
	ret->name = (char*)malloc(sizeof(char)*len);
	sprintf( ret->name, "(%s %s)", A->name, B->name );
	ret->R = A->R; ret->C = B->C;
	ret->dim = A->dim + B->dim + A->R*A->C*B->C; /* How to calculate this */
	return( ret );
}

Matrix* clone_matrix( Matrix *from ) {
	Matrix *m_copy = (Matrix*)malloc(sizeof(*m_copy));
        m_copy->name = (char*)malloc(strlen(from->name)+1);

        sprintf(m_copy->name, "%s\0", from->name);
        m_copy->R = from->R;
        m_copy->C = from->C;
        m_copy->dim = from->dim;
	set_matrix_functions( m_copy );
        return m_copy;
}

void print_matrix( Matrix *M ) {
	fprintf(stdout,"%s ",M->name);
}

void set_matrix_functions( Matrix *M ) {
	M->concat_matrices = concat_matrices;
	M->print_matrix = print_matrix;
	M->clone_matrix = clone_matrix;
}
