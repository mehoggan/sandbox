#include <iostream>

namespace Error_Handler {
    using std::string;
    struct Divide_by_zero {
        string m_error;
        Divide_by_zero( string e ) : m_error( e ) { };
    };
}

namespace Math {
    using std::ostream;
    using namespace Error_Handler;

    float divide( float a, float b ) {
        if(!b) throw Divide_by_zero( string("Divide by zero") );
        return a/b;
    }
}

int main( int argc, char *argv[ ] ) {
    using namespace Math;
    /*
     * Find out when this thing will actually crash
     */ 
    try {
        for( float x=1;x>=0;x-=0.00001f ) {
            std::cout << Math::divide( 1,x ) << std::endl;
        }
    } catch( Error_Handler::Divide_by_zero e ) {
        std::cout << "ERROR: " << e.m_error << std::endl;
    }
    std::cout << "I am still going" << std::endl;
}

