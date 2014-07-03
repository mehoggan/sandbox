#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

void intersection( vector<float> &A, vector<float> &B, vector<float> &C ) 
{
    set_intersection( A.begin( ),A.end( ),B.begin( ),B.end( ),back_inserter( C ) );
}

int main( int argc, char *argv[ ] ) 
{
    vector<float> A;
    A.push_back( 2 );
    A.push_back( 3 );
    A.push_back( 2 );
    vector<float> B;
    B.push_back( 3 );
    B.push_back( 3 );
    B.push_back( 2 );
    vector<float> C;
    intersection( A,B,C );
    copy( C.begin( ), C.end( ), ostream_iterator<float>( cout, " " ) );
    return 0;
}
