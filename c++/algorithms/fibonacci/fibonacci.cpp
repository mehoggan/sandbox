#include <iostream>

int fib( int N )
{
    if( N <= 2 ) return 1;
    else return fib( N-1 ) + fib( N-2 );
}

int main( int argc, char *argv[ ] ) 
{
    std::cout << fib( 6 ) << std::endl;
    return 0;
}
