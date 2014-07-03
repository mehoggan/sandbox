#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

/********************************************************************
 * Read a sequence of possibly whitespace-separated (name,value)
 * pairs, where the name is a single whitespaace-separated word and
 * the value is an integer or floating-point value. Compute and print
 * the sum and mean for each name and the sum and mean for all names
 * ******************************************************************/

using namespace std;

std::multimap<string,float> _map;

istream& operator>>(istream& stream, pair<string,float> &in ) {
    return stream >> in.first >> in.second;
}

ostream& operator<<(ostream& stream, pair<string,float> &out ) {
    return stream << "(" << out.first 
                  << ", " << out.second << ")" << endl;
}

int main( int argc, char *argv[ ] ) {
    istream *is = &cin;
    do {
        pair<string,float> input;
        (*is) >> input;
        _map.insert(input);
    } while( is->peek( ) != EOF );

    ostream *os = &cout;
    multimap<string,float>::iterator mit = _map.begin( );
    float sum = 0.0;
    while( mit != _map.end( ) ) {
        pair<string,float> p_pair = (*mit);
        (*os) << p_pair;
        sum+=p_pair.second;
        mit++;
    }
    float mean = static_cast<float>( sum/_map.size( ) );
    (*os) << "Sum: " << sum << " Mean: " << mean << endl;
}
