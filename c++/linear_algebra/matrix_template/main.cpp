#include "include.h"
#include "linear_algebra.h"

using namespace linear_algebra;

int main( int argc, char** argv ) {
	Vector2<int> v( 1, 1 );
	Vector2<int> u( 2, 2 );
	Vector2<int>* w=u+v;
	w->printSelf( );
	w=u*v;
	w->printSelf( );
	w=*(w)*3;
	w->printSelf( );
	delete w;
	return( 0 );
}

















