#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
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
            ~RandomOrderedMatrix( );
            void find_element( int element );
            void print_matrix( );
            std::pair<int,int>& get_coord( ) { return this->data; }
        private:
            void build_matrix( );
            int **matrix;
            std::pair<int,int> data;
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
        this->matrix = new int*[N];
        for( int r=0;r<N;r++ ) matrix[r] = new int[N];
        this->build_matrix( );
    } 
    
    /* dtor                                                                  */
    RandomOrderedMatrix::~RandomOrderedMatrix( )
    {
        if( matrix ) 
        {
            for( int r=0;r<N;r++ ) delete [ ] matrix[r];
            delete [ ] matrix;
        }
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
        int left_index = 0;
        int right_index = N-1;
        /* Scan the rows */
        for( int r = 0; r < N; r++ ) 
        {
            /* Check the range for that row */
            if( element >= matrix[r][0] && element <= matrix[r][N-1] )
            {
               /* Binary search */
               while( right_index>left_index ) {
                    int middle = (right_index+left_index)/2;
                    if( element == matrix[r][middle] )
                    {
                        data.first = r;
                        data.second = middle;
                        return;
                    }
                    else if( element > matrix[r][middle] )
                    {
                        left_index = middle + 1;
                    }
                    else if( element < matrix[r][middle] )
                    {
                        right_index = middle - 1;
                    }
                }
            }
            /* These last two cases are used when there are only two items   */
            /* left in the binary partition                                  */
            if( element == matrix[r][left_index] ) 
            {
                data.first = r;
                data.second = left_index;
                return;
            }
            if( element == matrix[r][right_index] )
            {
                data.first = r;
                data.second = right_index;
                return;
            }
        }
        /* If function above did not find the elements then set them to N to */
        /* notify the client that their pair could not be found              */
        data.first = N;
        data.second = N;
    }
    
    /* Pretty Formating Print functino =)                                    */
    void RandomOrderedMatrix::print_matrix( ) 
    {
        std::cout << "Your Matrix is" << std::endl;
        std::cout << std::setw( 6 ) << " ";
        std::cout << std::setw( 6 ) << " ";
        for( int c=0;c<N;c++ )
        {
            std::cout << std::setw( 6 ) << c;
        }
        std::cout << std::endl;
        for( int r=0;r<N;r++ )
        {
            std::cout << std::setw( 6 ) << r;
            std::cout << std::setw( 6 ) << "|";
            for( int c=0;c<N;c++ )
            {
                std::cout << std::setw( 6 ) << matrix[r][c];
            }
            std::cout << std::setw( 6 ) << "|";
            std::cout << std::endl;
        }
    }
    
    /* Build a matrix such that the rows are sorted and the columns are      */
    /* sorted.                                                               */
    void RandomOrderedMatrix::build_matrix( ) 
    {
        matrix[0][0] = rand( )%50;   
        for( int c=1; c<N; c++ ) matrix[0][c] = matrix[0][c-1] + rand( )%50;
        for( int r=1; r<N; r++ )
        {
            for( int c=0; c<N; c++ ) 
            {
                if( c == 0 ) 
                {
                    matrix[r][c] = matrix[r-1][N-1]+rand( )%50;
                }
                else
                {
                    matrix[r][c] = matrix[r][c-1]+rand( )%50;
                } 
            }
        }
    }
}

/* Driver function, normally found in another file, but to facilitate        */
/* reading I have included it here                                           */
/* I also included some unit testing code which automates the testing        */
/* If you want you can uncomment it to make your testing easier              */
int main( int argc, char *argv[ ] ) 
{
    Matrix::RandomOrderedMatrix rom( 10 );
    rom.print_matrix( );
    srand((unsigned)time(NULL));
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
    /* Slight Unit Testing
    for( int x = 0; x < 20; x++ ) 
    {  
        std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
        int element = rand( )%10000;
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
        std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    }
    //*/
}
