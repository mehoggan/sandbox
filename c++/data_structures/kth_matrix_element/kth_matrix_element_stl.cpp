#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iterator>

/* Author: Matthew Everett Hoggan                                           */
/* Date: August 8, 2011                                                     */
/* Problem Statement:                                                       */
/* Given an matrix such that every row is sorted and every column is sorted */
/* write a function "find_kth_element_and_return_rowXcol" that returns a    */
/* a pair<int,int> where the element was found. If it is not found return   */
/* <N,N> to indicate to user that their value was not found                 */

namespace Matrix 
{
    /* This class is designed to solve the problem at hand                  */
    /* The method definitions are described where they are defined          */
    /* Note this matrix is a N x N square matrix                            */
    class RandomOrderedMatrix 
    {
        public:
            RandomOrderedMatrix( int N );
            void find_element( int element );
            void print_matrix( );
            std::pair<int,int>& get_coord( ) { return this->data; }
        private:
            void build_matrix( );
            std::pair<int,int> data;
            std::vector<std::vector<int> > matrix;
            int N;
            friend std::ostream& operator<< ( std::ostream &out, Matrix::RandomOrderedMatrix &rom )
            {
                std::pair<int,int> d = rom.data;
                return out << "<" << d.first << ", " << d.second << ">" << std::endl;
            }
    };
    
    /* ctor                                                                 */
    RandomOrderedMatrix::RandomOrderedMatrix( int N )
    {
        this->N = N;
        for( int r=0;r<N;r++ ) 
        {
            matrix.push_back( std::vector<int>( N ) );
        }
        this->build_matrix( );
        this->print_matrix( );
    } 
    
    /* This is the n lg(n) algorithm required to find the coord of an elem.  */
    /* Assuming that the rows and columns are all sorted we find the row     */
    /* with the right range matrix[row][0] <= element <= matrix[row][N]      */
    /* Once it finds the right row if it existis it performs binary search   */
    /* which is lg(n) to see if element exists on that row. If the element   */
    /* is found it prints sets the coordinate pair member variable to the    */
    /* row and column where it found it. If it did not find the elment it    */
    /* sets the member variable coordinate pair to N                         */
    void RandomOrderedMatrix::find_element( int element ) 
    {
        for( int i = 0; i < N; i++ )
        {
            if(matrix[i][0] <= element && matrix[i][N-1] >= element)
            {
                /* Sometimes generic algorithms don't give you what you want */
                if( binary_search( matrix[i].begin( ), matrix[i].end( ), element ) )
                {
                    std::cout << "Found your item (" << element << ") on ROW: " << i << std::endl;
                }
            }
        }
    }

    void PrintRow( std::vector<int> &row )
    {
        static int rows=0;
        std::cout << std::endl << rows++ << "\t" << "|";
        copy( row.begin( ), row.end( ), std::ostream_iterator<int>( std::cout,"\t" ) );
    }

    /* Pretty Formating Print functino =)                                    */
    void RandomOrderedMatrix::print_matrix( ) 
    {
        std::cout << "\t" << "| ";
        for( int i=0;i<N;i++ ) std::cout << i << "\t";
        std::cout << std::endl;
        for( int i=0;i<N+2;i++ ) std::cout << "_______";
        std::cout << std::endl;
        for_each( matrix.begin( ), matrix.end( ), PrintRow );
        std::cout << std::endl;
    }
    
    /* Build a matrix such that the rows are sorted and the columns are      */
    /* sorted.                                                               */
    void RandomOrderedMatrix::build_matrix( ) 
    {
        typedef std::vector<std::vector<int> >::iterator rowIT;
        typedef std::vector<int>::iterator colIT;
        rowIT rs = matrix.begin( );
        rowIT re = matrix.end( );
        (*rs)[0]=( rand( )%50 );
        for( int i=1;i<N;i++ )
        {
            (*rs)[i] = (*rs)[i-1]+rand( )%50;
        }
        rowIT prev = rs;
        rs++;
        while( rs != re )
        {
            (*rs)[0]=(*prev)[N-1]+rand( )%50;
            for( int i=1;i<N;i++ )
            {
                (*rs)[i] = (*rs)[i-1]+rand( )%50;
            }
            prev = rs;
            rs++;
        }
    }
}

/* Driver function, normally found in another file, but to facilitate        */
/* reading I have included it here                                           */
/* I also included some unit testing code which automates the testing        */
/* If you want you can uncomment it to make your testing easier              */
int main( int argc, char *argv[ ] ) 
{
    srand((unsigned)time(NULL));
    Matrix::RandomOrderedMatrix rom( 10 );
    int element;
    std::cout << "Please input a number to find in your matrix>>> ";
    while( std::cin >> element ) 
    {
        rom.find_element( element );
        std::pair<int,int> &results = rom.get_coord( );
        if( results.first != 10 && results.second != 10 ) 
        {
            std::cout << "Results success, found " << element << " @ coord " << rom;
        }
        else 
        {
            std::cout << "Results failed could not find " << element << " in matrix " << std::endl;
        }
        std::cout << "Please input a number to find in your matrix>>> ";
    }
}
