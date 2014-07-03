#include "matrix.h"
#include "matrix_list.h"
#include <stdlib.h>
#include <stdio.h>

#define N 5
#define Nplus1 6

int main( int argc, char** argv ) {
	/********************************************************/
	/* The columns of left must equal rows in right		*/
	/*Given Ra X Ca and Rb X Cb -> Ca == Rb			*/
	/*Also A X B = C -> Rc == Ra && Cc = Cb			*/
	/*Total number of multiplcations are Ra x Ca x Rb	*/
	/********************************************************/
	
	int dim[Nplus1];
	int a;
	for( a=0;a<Nplus1;a++ ) {
		dim[a] = rand( )%10;
	}
	
	MatrixList *chain = (MatrixList*)malloc(sizeof(MatrixList));
	set_list_functions( chain );
	int i;
	char L = 'A';
	for( i=0;i<N;i++ ) {
		Matrix *next = (Matrix*)malloc(sizeof(Matrix));
		next->name = (char*)malloc(sizeof(char*)*2);
		next->name[0]=L++;
		next->name[1]='\0';
		next->R = dim[i];
		next->C = dim[i + 1];
		next->dim = 0;
		set_matrix_functions( next );
		chain->append(chain, next);
	}

	chain->print_list( chain,0 ); fprintf(stderr,"\n");
	MatrixList* end = NULL;
	end = gen_parens( chain,end );
	end->print_list( end,1 ); fprintf(stderr,"\n");	

	/* Garbage Collection */
	chain->release(chain);
	free( chain );
	end->release( end );
	free( end );

	return (0);
}
