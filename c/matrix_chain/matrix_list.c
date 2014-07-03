#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix_list.h"
#include "matrix.h"

void print_list( MatrixList *list, int newline ) {
	Node *slide = list->head;
	int count = 1;
	while( slide != NULL ) {
		if( newline ) { fprintf(stderr,"%3d) ",count++ ); }
		fprintf( stderr, "%s(%dX%d)",slide->M->name,slide->M->R,slide->M->C );
		if( newline ) { fprintf( stderr," = %d %c",slide->M->dim,'\n' ); }
		else if( slide->next == NULL ) { ;}
		else { fprintf( stderr,"%s", ", " ); }
		slide = slide->next;
	}
}

void reverse_print( MatrixList *list ) {
	Node *slide = list->tail;
	while( slide != NULL ) {
		printf("%s(%dX%d)%s",slide->M->name, slide->M->R, slide->M->C, ((slide->prev == NULL) ? "" : ", ") );
		slide = slide->prev;
	}
	printf("\n");	
}

void append( MatrixList *list, Matrix* M ) {
	if( list->head == NULL ) {
		Node *n = (Node*)malloc(sizeof(Node));
		n->M = M; n->next = NULL; n->prev = NULL;
		list->head = n; list->tail = n;
		list->size++;
	} else {
		Node *n = (Node*)malloc(sizeof(Node));
		n->M = M; n->next = NULL;
		Node *tmp = list->tail;
		list->tail->next = n; list->tail = n;
		n->prev = tmp;
		list->size++;
	}
}

Matrix* get( MatrixList *list, int item ) {	
	if( list->head == NULL ) {
		return NULL;
	} else {
		Node *slide = list->head;
		int j;
		for( j=0;j<item;j++ ) {
			slide = slide->next;
		}
		return slide->M;
	}
}

void delete( MatrixList *list, const char *name ) {
	if( list->head == NULL ) {
		printf("You can't delete from an empty list");
	} else {
		Node *pre = list->head;
		Node *tmp = list->head;
		char *one = (char*)malloc(sizeof(char)*strlen(name));
		sprintf(one, "%s", name);
		while( tmp != NULL ) {
			pre = tmp;
			char *two = (char*)malloc(sizeof(char)*strlen(tmp->M->name));
			sprintf(two, "%s", tmp->M->name);
			if( strcmp( one,two ) == 0 ) {
				printf("Found match %s=%s\n",one,two);
				free( two );
				break;
			}
			tmp = tmp->next;
			free( two );
		}
		if( tmp == list->head ) {
			list->head = list->head->next;
			free( tmp->M->name );
			free( tmp->M );
			free( tmp );
			list->size--;
		}else if( tmp != NULL ) {
			pre->next = tmp->next;
			free( tmp->M->name );
			free( tmp->M );
			free( tmp );
			list->size--;
		}
		free( one );
	}
}

void delete_head( MatrixList *list ) {
	if( list->head == NULL ) {
	} else if( list->head == list->tail ) {
		free( list->head->M->name );
		free( list->head->M );
		free( list->head );
		list->head = NULL;
		list->size--;
	} else {
		Node *tmp = list->head;
		list->head = list->head->next;
		list->head->prev = NULL;
		free( tmp->M->name );
		free( tmp->M );
		free( tmp );
		list->size--;
	}
}

void delete_tail( MatrixList *list ) {
	if( list->tail == NULL ) {
	} else if( list->head == list->tail ) {
		free( list->tail->M->name );
		free( list->tail->M );
		free( list->tail );
		list->head = NULL;
		list->tail = NULL;
		list->size--;
	} else {
		Node *tmp = list->tail;
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		free( tmp->M->name );
		free( tmp->M );
		free( tmp );
		list->size--;
	}
}

void release( MatrixList *list ) {
	if( list->head == NULL ) {
		fprintf( stderr, "Nothing to clean up!!!\n" );
	} else {
		while( list->head != NULL ) {
			list->delete_head( list );
		}
	}
}

void clone_list( MatrixList *from, MatrixList *to ) {
	if( from->head == NULL ) {
	} else {
		*to = *from;
		to->head = 0;
		to->tail = 0;
		to->size = 0;
		Node *old; 
		for( old=from->head;old!= NULL;old=old->next ) {
			Matrix *m_copy = old->M->clone_matrix( old->M );
			to->append( to,m_copy );
		}
	}
}

void set_list_functions( MatrixList *list ) {
        list->head = NULL;
        list->tail = NULL;
        list->append = append;
	list->get = get;
        list->print_list = print_list;
        list->reverse_print = reverse_print;
        list->delete = delete;
        list->delete_head = delete_head;
        list->delete_tail = delete_tail;
        list->release = release;
        list->clone_list = clone_list;
	list->size = 0;
}

MatrixList* gen_parens( MatrixList *list, MatrixList *ret ) {
        if( list->size==1 ) {
		ret = (MatrixList*)malloc(sizeof(MatrixList));
		set_list_functions( ret );
		Matrix *add = list->get( list,0 );
		Matrix *insert = add->clone_matrix( add );
		ret->append( ret,insert );
        } else if( list->size==2 ) {
		ret = (MatrixList*)malloc(sizeof(MatrixList));
		set_list_functions( ret );
		Matrix *concat = (Matrix*)malloc(sizeof(Matrix));
		set_matrix_functions( concat );
		Matrix *insert = concat->concat_matrices( list->get( list,0 ), list->get( list,1 ) );
		ret->append( ret,insert );
		free( concat );
        } else {
		int i=0;
		ret = (MatrixList*)malloc(sizeof(MatrixList));
		set_list_functions( ret );
	        for( i=0;i<list->size-1;i++ ) {
			MatrixList *s1 = (MatrixList*)malloc(sizeof(MatrixList));
			MatrixList *s2 = (MatrixList*)malloc(sizeof(MatrixList));
			set_list_functions( s1 );
			set_list_functions( s2 );
		
			list->clone_list( list, s1 );
			list->clone_list( list, s2 );
		
			int k;
			for( k=i;k<list->size-1;k++ ) { s1->delete_tail( s1 ); }
			int j;
			for( j=i;j>=0;j-- ) { s2->delete_head( s2 ); }
			
			MatrixList *left = gen_parens( s1,ret );
			MatrixList *right = gen_parens( s2,ret );

			for(j=0;j<left->size;j++) {
				for(k=0;k<right->size;k++) {
					Matrix *concat = (Matrix*)malloc(sizeof(Matrix));
					set_matrix_functions( concat );
					Matrix *insert = concat->concat_matrices( left->get( left,j),right->get( right,k) );
					ret->append( ret,insert );
					free( concat );
				}
			}
			/* Garbage Collection */
			left->release( left );
			free( left );
			right->release( right );
			free( right );
			s1->release( s1 );
			free( s1 );
			s2->release( s2 );
			free( s2 );
		}
	}
	return ( ret );
}
