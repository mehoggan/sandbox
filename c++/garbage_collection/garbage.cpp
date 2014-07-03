#include <new>
#include <stdlib.h>
#include <iostream>
#include <set>

#ifndef OBJECT_
#define OBJECT_

class Object {
    public:
        Object( ) { };
        void* operator new( size_t );
        void operator delete( void *o );
    private:
        static std::set<void*> _objects;
        friend int get_count( );
};

std::set<void*> Object::_objects;

int get_count( ) {
    return Object::_objects.size( );
}

void* Object::operator new( size_t size ) {
    std::cout << "new operator called" << std::endl;
    void *storage = malloc( size );
    if( NULL == storage ) {
        throw "allocation fail : no free memory";
    } else {
        Object::_objects.insert( storage );
    }
    return storage;
}

void Object::operator delete( void *o ) {
    std::cout << "Deleteing objects" << std::endl;
    Object::_objects.erase( o );
    free( o );
    if( get_count( ) == 0 ) {
        std::cout << "You have removed all instances of objects" << std::endl;
        return;
    }
}
#endif    /*OBJECT_*/

int main( int argc, char *argv[] ) {
    Object* a = new Object( );
    Object* b = new Object( );
    Object* c = new Object( );
    Object* d = new Object( );
    delete a;
    delete b;
    delete c;
    std::cout << "There is " << get_count( ) << " objects remaining"  << std::endl;
    return 0;
}
