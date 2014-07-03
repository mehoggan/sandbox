#include <iostream>
#include <cmath>
#include <limits.h>

/* Provide a nonrecursive implementation of Euclid's Algorithm */

using namespace std;

namespace Euclidean 
{
    namespace 
    {
        bool is_square( int num )
        {
            if( num < 0 ) 
            {
                return false;
            }
            else 
            {
                //I need to determine if this is a perfect square in a sensible manner
                double test_sqrt = static_cast<int>( sqrt( num ) );
                int mask=0xFFFFFFFFFFFFFFFFF;
                mask = ~(mask<<52);                //Create Mask For Floating Point Portion
                double fraction=test_sqrt&mask;
            }
        }

        bool is_fib( int num ) 
        {
            if( is_square( 5*pow( num,2.0 ) + 4 ) && is_square( 5*pow( num,2.0 ) - 4 ) ) 
            {
                return true; 
            }
            else 
            {
                return false;
            }
        }     
    }

    int recursive_euclidean_fib_at_depth( int num1, int num2, int depth )
    {
        ( ( is_fib( num1 ) && is_fib( num2 ) ) ? 
            ( cout << "Fibonacci numbers found at: " << depth << " <" << num1 << ", " << num2 << "> " << endl ) : 
            ( cout << "" )
        );
        int gcd=0;
        if( num1 == num2 || num1 < 0 || num2 < 0 ) 
            ( ( num1 == num2 ) ? ( gcd = num1 ) : ( ( num1 < 0) ? ( gcd = num2 ) : 
                ( gcd = num1 ) ) );
        else
            ( ( num1 > num2 ) ? ( gcd = recursive_euclidean_fib_at_depth( num1-num2, num2, depth+1 ) ) :
                ( gcd = recursive_euclidean_fib_at_depth( num1, num2-num1, depth+1 ) ) );
        return gcd;
    }

    int recursive_euclidean( int num1, int num2 )
    {
        int gcd=0;
        if( num1 == num2 || num1 < 0 || num2 < 0 ) 
            ( ( num1 == num2 ) ? ( gcd = num1 ) : ( ( num1 < 0) ? ( gcd = num2 ) : 
                ( gcd = num1 ) ) );
        else
            ( ( num1 > num2 ) ? ( gcd = recursive_euclidean( num1-num2, num2 ) ) :
                ( gcd = recursive_euclidean( num1, num2-num1 ) ) );
        return gcd;
    }

    int iterative_euclidean( int num1, int num2 ) 
    {
        while( num1 != num2 && num1 > 0 && num2 > 0 ) 
            (( num1 > num2 ) ? (num1-=num2) : (num2-=num1) );
        return (num1>0) ? num1 : num2;
    } 
}

int main( int argc, char *argv[ ] ) 
{
    int num1, num2 = 0;
    cout << "Please input two numbers>>> ";
    cin >> num1 >> num2;
    int gcd = Euclidean::iterative_euclidean( num1, num2 );
    cout << "Iterative: " << endl;
    cout << "gcd(" << num1 << ", " << num2 << ")= " 
         << gcd << endl;
    
    cout << "Recursive: " << endl;
    gcd = Euclidean::recursive_euclidean( num1, num2 );
    cout << "gcd(" << num1 << ", " << num2 << ")= " 
         << gcd << endl;
    return 0;    
}
