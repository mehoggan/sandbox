#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>

namespace Counter {
    class WordCounter {
        public:
            WordCounter( ) { };
            ~WordCounter( ) { };
            WordCounter( const WordCounter &wc ) { };
            void count_words( std::string file_name );
        private:
            friend std::ifstream& operator>> ( std::ifstream &f_stream, WordCounter &wc );
            friend std::ostream& operator<< ( std::ostream &f_stream, WordCounter &wc );
            std::vector<std::string> m_svector;
    };
}

#endif    /*WORD_COUNTER_H*/
