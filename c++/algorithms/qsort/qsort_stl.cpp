#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <ctime>
#include <assert.h>

namespace Sorters 
{
    using std::vector;
    using std::copy;
    using std::ostream;
    using std::ostream_iterator;
    using std::cout;
    using std::endl;
    using std::next_permutation;
    using std::distance;

    template<class T> class QSorter 
    {
        public:
            void PermTester( int N );
            void Qsort( typename vector<T>::iterator l, typename vector<T>::iterator r );
            void PrintRange( typename vector<T>::iterator l, typename vector<T>::iterator r ) 
            {
                cout << "<";
                cout << (*l)<< " ";
                copy( l+1,r-1, ostream_iterator<T>( cout, " " ) );
                cout << (*(r-1));
                cout << ">" << endl;
            }
        private:
            vector<T> m_data;
            void Swap( typename vector<T>::iterator l, typename vector<T>::iterator r );
            friend ostream& operator<< ( ostream &stream, QSorter &qs )
            {
                copy( qs.m_data.begin( ), qs.m_data.end( ), ostream_iterator<T>( cout, " " ) );
                return stream;
            }
    };

    template<class T> 
    void QSorter<T>::PermTester( int N ) 
    {
        for( int x=0; x<=N; x++ )
        {
            m_data = vector<T>( x );
            vector<T> perm;
            for( int y=0; y<x; y++ ) 
            {
                perm.push_back( y+1 );
            }
            do 
            {
                copy( perm.begin( ),perm.end( ),m_data.begin( ) );
                cout << "*****************************************************************" << endl;
                cout << "Going to Sort: " << (*this) << endl;
                cout << "*****************************************************************" << endl;
                Qsort( m_data.begin( ), m_data.end( ) );
                cout << "*****************************************************************" << endl;
                cout << "Sorted: " << (*this) << endl;
                cout << "*****************************************************************" << endl;
             
            } while( next_permutation( perm.begin( ),perm.end( ) ) ); 
        }
        m_data.clear( );
    }
    
    template<class T>
    void QSorter<T>::Swap( typename vector<T>::iterator l, typename vector<T>::iterator r )
    {
        T tmp = (*r);
        (*r) = (*l);
        (*l) = tmp;
    }

    template<class T> 
    void QSorter<T>::Qsort( typename vector<T>::iterator l, typename vector<T>::iterator r ) 
    {
        if( r<=l+1 ) 
        {
        } 
        else
        {
            typename vector<T>::iterator it_pivot =l+distance(l,r)/2;
            T pivot = (*it_pivot);
            Swap( l,it_pivot );
            typename vector<T>::iterator it_l = l+1;    // +1 because pivot is at l
            typename vector<T>::iterator it_r = r-1;    // -1 because r is outside partition
            while( it_l <= it_r ) 
            {
                while( (*it_l) <= pivot && it_l <= it_r ) ++it_l;
                while( (*it_r) >= pivot && it_l <= it_r ) --it_r;
                if( it_l <= it_r ) 
                {
                    Swap( it_l,it_r );
                }
            }
            Swap( l,it_r );
            Qsort( l, it_r );
            Qsort( it_r, r );
        }
    }
}

int main( int argc, char *argv[ ] ) {
    Sorters::QSorter<float> qs;
    qs.PermTester( 5 );
}
