#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <iterator>

using namespace std;

template<typename T>
void perm( vector<T> *set, typename vector<T>::iterator start ) {
	copy( set->begin( ), set->end( ), ostream_iterator<T> ( cout," " ) );
	cout << endl;
	for( typename vector<T>::iterator i = set->end( )-2; i >= start; i-- ) {
		for( typename vector<T>::iterator j=i+1; j<set->end( ); j++ ) {
			T tmp=*i;
			*i=*j;
			*j=tmp;
			perm( set,i+1 );
		}
		T tmp=*(i);
		for( typename vector<T>::iterator k=i;k<set->end( )-1;k++ ) {
			*(k)=*(k+1);
		}
		*(set->end( )-1) = tmp;
	}
}

int main( int argc, char** argv ) {
	int N=4;
	vector<char> set;
	int c=0;
	for( char i='A';c<N;c++,i++ ) {
		set.push_back( i );
	}
	perm( &set, set.begin() );
	cout << endl;
}
