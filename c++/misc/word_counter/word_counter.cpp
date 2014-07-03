#include "word_counter.h"

namespace Counter {
    std::ifstream& operator>> ( std::ifstream &f_stream, WordCounter &wc ) {
        std::string input;
        while( f_stream >> input ) {
            wc.m_svector.push_back( input );
        }
        return f_stream;
    }

    std::ostream& operator<< ( std::ostream &o_stream, WordCounter &wc ) {
        copy( wc.m_svector.begin( ),wc.m_svector.end( ),std::ostream_iterator<std::string>( o_stream," " ) );
        return o_stream;
    }
    
    std::ostream& operator<< (std::ostream &o_stream, std::map<std::string,int> &m ) {
        std::vector<std::pair<std::string,int> > v( m.begin( ), m.end( ) );
        sort(v.begin( ), v.end( ) );
        for( std::vector<std::pair<std::string,int> >::iterator it=v.begin( );it!=v.end( );it++ ) {
            std::cout << "<" << (*it).first << ", " << (*it).second << ">" << std::endl;
        }    
        return o_stream;
    }

    void WordCounter::count_words( std::string file_name ) {
        std::ifstream ifs( file_name.c_str( ) );
        ifs >> (*this);
        std::cout << "The contents of the file (without formating) is: " << std::endl;
        std::cout << "**********************************************************************************************************************************************" << std::endl;
        std::cout << (*this) << std::endl;
        std::cout << "**********************************************************************************************************************************************" << std::endl;
        std::map<std::string,int> unique_words;
        for( std::vector<std::string>::iterator it=m_svector.begin( );
             it!=m_svector.end( ); it++ ) {
            unique_words[(*it)]++;
        }
        std::cout << unique_words;
    }
}
