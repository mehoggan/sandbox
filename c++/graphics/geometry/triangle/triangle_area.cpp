/********************************************************************
 * Define a data type for triangles in the unit square, including a
 * function that computes the are of a triangle. Then write a client
 * program that generates random triples of pairs of floats between 0
 * and 1 and computes the average area of the triangles generated.
 * *****************************************************************/
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Point {
    public:
    Point( ) { ;}
    Point( float x, float y ) : x( x ), y( y ){ ;}
    float getX( ) { return x; }
    float getY( ) { return y; }
    void setX( float X ) { x = X; }
    void setY( float Y ) { y = Y; }
    void print( ) { cout << "("<<x<<", "<<y<<") "<<endl; }
    private:
    float x;
    float y;
};

class Line {
    public:
    Line( Point a, Point b ) : a( a ), b( b ){ ;}
    void mid_point( Point &mid );
    float length( );
    Point getA( ) { return a; }
    Point getB( ) { return b; }
    void print( ) { a.print( ); b.print( ); }
    private:
    Point a;
    Point b;
};

void Line::mid_point( Point &mid ) {
    mid.setX( (a.getX( )+b.getX( ))/2.0 );
    mid.setY( (a.getY( )+b.getY( ))/2.0 );
}

float Line::length( ) {
    return sqrt( pow( a.getX( )-b.getX( ),2.0 ) +
                 pow( a.getY( )-b.getY( ),2.0 )  
               );
}

class Triangle {
    public:
    Triangle( Line A,Line B,Line C ) : A( A ), B( B ), C( C ){ ;}
    float calc_area( );
    void print( ) {
        cout << "Line A formed from points\n"; A.print( ); 
        cout << "Line B formed from points\n"; B.print( ); 
        cout << "Line C formed from points\n"; C.print( ); 
    }
    private:
    Line A;
    Line B;
    Line C;
};

float Triangle::calc_area( ) {
    Point mid;
    C.mid_point( mid );
    Line height( mid, A.getB( ) );
    return 0.5*C.length( )*height.length( );
}

int main( int argc, char *argv[ ] ) {
    srand( time( NULL ) );
    //Calculate area of 10 triangles;
    for( int i=0;i<10;i++ ) {
        Point p1( (rand( )%10)/10.0,(rand( )%10)/10.0 );
        Point p2( (rand( )%10)/10.0,(rand( )%10)/10.0 );
        Point p3( (rand( )%10)/10.0,(rand( )%10)/10.0 );
        Line l1( p1,p2 );
        Line l2( p2,p3 );
        Line l3( p3,p1 );
        Triangle t( l1,l2,l3 );
        t.print( );
        cout << "Area = " << t.calc_area( ) << endl << endl;
    }
}
