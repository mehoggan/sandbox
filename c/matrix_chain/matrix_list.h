#ifndef LIST_H_
#define LIST_H_

#include "matrix.h"

typedef struct node {
	Matrix *M;
	struct node *next;
	struct node *prev;
} Node;

typedef struct matrix_list {
	Node *head;
	Node *tail;
	int size;
	void (*append)( struct matrix_list *list, Matrix *M );
	void (*print_list)( struct matrix_list *list, int newline );
	struct matrix* (*get)( struct matrix_list *list, int index );
	void (*reverse_print)( struct matrix_list *list );
	void (*delete)( struct matrix_list *list, const char *name );
	void (*delete_tail)( struct matrix_list *list );
	void (*delete_head)( struct matrix_list *list );
	void (*release)( struct matrix_list *list );
	void (*clone_list)( struct matrix_list *from, struct matrix_list *to );
} MatrixList;

void set_list_functions( MatrixList *list );
MatrixList* gen_parens( MatrixList *init, MatrixList *start );
#endif
