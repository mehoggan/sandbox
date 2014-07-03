#include "word_counter.h"

int main( int argc, char *argv[ ] ) {
    Counter::WordCounter wc;
    wc.count_words( "test.txt" );
    return 0;
}

