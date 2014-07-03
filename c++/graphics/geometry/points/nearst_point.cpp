/********************************************************************
 * Author: Mattew Hoggan
 * Description: Write a client program that uses the data type point.
 * Read a sequence of points (pairs of floating-point numbers) from
 * standard input, and find the one that is closest to the first.
 * *****************************************************************/
                                                                   
#include <math.h>                                                  
#include <iostream>                                                
#include <vector>                                                  
#include <istream>                                                 
#include <iterator>
#include <algorithm>
#include <limits.h>
                                                                   
using namespace std;                                               
                                                                   
typedef struct point {                                             
    float x;                                                       
    float y;                                                       
} point;                                                           
                                                                   
float calc_distance( const point *a, const point *b ) {            
    return sqrt( pow( a->x-b->x, 2.0 ) + pow( a->y-b->y, 2.0 ) );      
}                                                                  
                                                                   
void print_point( point *a ) {                                 
    cout << "(" << a->x << ", " << a->y << ") ";
}

void delet_point( point *a ) {
    delete a;
}

vector<point*>* form_pairs( vector<float> &num ) {
    vector<point*> *points=NULL;
    if( ( num.size( ) & 1 ) == 1 ) { 
        cerr << "ERROR: You input: " << num.size( ) 
             << " which is odd, failed to build vector "
             << endl;
        return points;
    } else {
        cout << "Going to build points" << endl;
        points = new vector<point*>;
        for( vector<float>::iterator vit=num.begin( );
            vit!=num.end( ); vit+=2 ) {
            point *in = new point( );
            in->x = *(vit);
            in->y = *(vit+1);
            points->push_back( in );     
        }   
        return points;
    }
}

void pop_front( vector<point*> *pairs ) {
    reverse( pairs->begin( ), pairs->end( ) );
    pairs->pop_back( );
    reverse( pairs->begin( ), pairs->end( ) );
}

void min_euclidean_distance( vector<point*> *pairs ) {
    if( pairs->size( ) == 1 ) {
        cerr << "You already know the answer to this" << endl;
        return;
    }
    point *first = pairs->front( );
    pop_front( pairs );
    point *second = pairs->front( );
    pop_front( pairs );

    for_each( pairs->begin( ),pairs->end( ),print_point );
    cout << endl;
       
    point *p_min = second;
    float f_min = calc_distance( first,second );
    for( vector<point*>::iterator pit = pairs->begin( );
        pit != pairs->end( ); pit++ ) {
        float tmp = calc_distance( first,(*pit) );
        if( tmp < f_min ) {
            f_min = tmp;
            p_min = (*pit);
        }
    }

    cout << "The closest node to "; print_point( first );
    cout << " is "; print_point( p_min );
    cout << " at " << f_min << " units away " << endl;
    delete first;
    delete second;
}

int main( int arc, char **arv ) {                                
    vector<float> num;
    cout << "Please, input even number of floats: ";
    for( istream_iterator<float> iit (cin);
         iit!=istream_iterator<float>( );iit++ ) {
         num.push_back( (*iit) );
    }

    vector<point*>* pairs = form_pairs( num );
    if( pairs ) {
        min_euclidean_distance( pairs );
        for_each( pairs->begin( ),pairs->end( ),delet_point );
        delete pairs;
    }
}                                                                  
