#include <iostream>
#include <list>
#include <iterator>
#include <cstdlib>
#include "matrix.h"

/*
 * Declare typedefs up front. Keep them to a minimal
 * to help readability and reduce amount of scrolling
 */
typedef std::list<Matrix>::iterator matrix_it;
typedef std::list<Matrix> matrix_chain;

/*
 * This function prints out the final results of 
 * the computations.
 */
void print_matrix_chain(matrix_it left, matrix_it right)
{
    while (left != right) {
        std::cout << (*left) << " = " << (*left).getMultiplications()  
                  << std::endl;
        left++;
    }
}

/*
 * This function finds the optimal way to multiply
 * N matrices together when provided a list of N
 * matrices
 */
matrix_chain optimal_matrix_chain_multiplication(matrix_chain &chain) 
{
    matrix_chain ret;
    if (chain.size() == 1) {
        ret.push_back(chain.front());
        chain.pop_front();
    } else if (chain.size() == 2) {
        Matrix A = chain.front();
        chain.pop_front();
        Matrix B = chain.front();
        chain.pop_front();
        Matrix C = (A*B);
        ret.push_back(A*B);
    } else {
        matrix_it pos = chain.begin();
        pos++;                                      //Start pos 1 from the left
        matrix_it end = chain.end();
        
        for (; pos != end; pos++) {
            matrix_chain left;
            matrix_chain right;
            copy(chain.begin(), pos, back_inserter(left));
            copy(pos, chain.end(), back_inserter(right));
            
            left = optimal_matrix_chain_multiplication(left);
            right = optimal_matrix_chain_multiplication(right);
            
            matrix_it lbegin = left.begin();
            matrix_it rbegin = right.begin();
            matrix_it lend = left.end();
            matrix_it rend = right.end();
            for (; lbegin != lend; lbegin++) {
                for(; rbegin != rend; rbegin++) {
                    try {
                        ret.push_back((*lbegin)*(*rbegin));
                    } catch (Matrix_error e) {
                        std::cout << e.m_error;
                    }
                }
            }
        }
    }
    return ret;   
}

int main(int argc, char *argv[])
{
    std::list<Matrix> chain;
    Matrix A(std::string("A"), std::pair<int, int>(5, 10), 0);
    chain.push_back(A);
    Matrix B(std::string("B"), std::pair<int, int>(10, 7), 0);
    chain.push_back(B);
    Matrix C(std::string("C"), std::pair<int, int>(7, 11), 0);
    chain.push_back(C);
    Matrix D(std::string("D"), std::pair<int, int>(11, 2), 0);
    chain.push_back(D);
    Matrix E(std::string("E"), std::pair<int, int>(2, 5), 0);
    chain.push_back(E);
    std::list<Matrix> ret = optimal_matrix_chain_multiplication(chain);
    
    print_matrix_chain(ret.begin(), ret.end());
    
    return 0;
}

