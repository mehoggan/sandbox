#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

namespace CLP {
    using std::vector;
    using std::for_each;
    using std::istringstream;
    using std::string;
    using std::cerr;
    using std::cout;
    using std::endl;

    vector<float> all_numeric_arguments( int argc, char *argv[ ] ) {
        vector<float> v_argv;
        vector<string> v_tmp;
        copy( &argv[1],&argv[argc],back_inserter( v_tmp ) );
        for( vector<string>::iterator it=v_tmp.begin( );it!=v_tmp.end( );it++ ) {
            istringstream iss( (*it) );
            float f=0.0;
            if( iss >> f >> std::dec ) {
                v_argv.push_back( f );
            } else {
               cerr << "ERROR: " << (*it) << " is not numeric " << endl;
               return v_argv;
            }
        }
        return v_argv;
    }
}

int main( int argc, char *argv[ ] ) {
    std::vector<float> v = CLP::all_numeric_arguments( argc, argv );
    if( v.size( ) == (unsigned)(argc-1) ) {
        copy( v.begin( ),v.end( ),std::ostream_iterator<float>( std::cout," " ) );
        std::cout << std::endl;
    }
}
