/* Write a recursive program to compute lg( N! ) */

#include <iostream>
#include <cmath>

using namespace std;

long double log_base2( long double N ) {
    return log( N )/log( 2.0 );
}

long double lg_n_factorial( long N ) {
    if( 1 == N ) return log_base2( static_cast<long double>( N ) );
    else return lg_n_factorial( N -1 ) + log_base2( static_cast<long double>( N ) );
}

int main( int argc, char *argv[] ) {
    long N=0;
    cout << "Please input a number to compute lg(N!)>>> ";
    cin >> N;
    cout << ( lg_n_factorial( N ) ) << endl;
    return 0;
}
