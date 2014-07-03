#include <stdlib.h>
#include <iostream>

using namespace std;

enum Token_value {
    NAME,       NUMBER,       END,        SPACE=' ',
    PLUS='+',   MIN='-',      MUL='*',    DIV='/',
    PRINT,      ASSIGN='=',   LP='(',     RP=')'
};

Token_value get_next_token( ) {
    Token_value curr_tok = PRINT;
    char ch;
    do {
        if( !cin.get( ch ) ) return curr_tok = END;
        else {
            cout << ch;
        }
    } while( ch!='\n' );
    curr_tok = END;
    return curr_tok;
}

int main( int argc, char *argv[ ] ) {
    while( cin ) {
        Token_value curr_tok= get_next_token( );
        if( curr_tok == END ) {
            exit( 0 );
        }
    }
}
