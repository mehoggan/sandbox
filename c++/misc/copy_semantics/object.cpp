#include <iostream>
#include <list>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;
using boost::lexical_cast;
using boost::bad_lexical_cast;

typedef struct Intern {
    string id;
    int key;
} Intern;

class Object {
    public:
        Object creatIntern( );
    protected:
        
    private:
};

//Object Object::creatIntern( ) {
//    return i;
//}

ostream& operator<<( ostream &out, Object &i ) {
    return out << i.m_id << i.m_key << endl;
}

int main( int argc, char *argv[] ) {
//    Object o;
//    cout << lexical_cast<string>( 4 ) << endl;
//    Intern i = o.creatIntern( );
}
