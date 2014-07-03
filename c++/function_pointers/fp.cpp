#include<iostream>

using namespace std;
/*********************************************************************
 * This is not complete need to formulate a practical example
 * ******************************************************************/
typedef struct Integer {
    int i;
}

typedef struct Float {
    float f;
}

typedef struct {
    typedef void* (*FP)( void*, void* );
    pair<void*,void*> data;
} GenericPair;

ostream& operator<<( ostream &stream, pair<int,int> &data ) {
    return stream << data.first << " " << data.second << endl;
}

istream& operator>>( istream &stream, pair<int,int> &data ) {
    return stream >> data.first >> data.second;
}

int

int main( int argc, char *argv[ ] ) {
    Generic c = { pair<void*,void*>( ) };
    return 0;
}
