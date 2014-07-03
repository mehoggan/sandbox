#include <iostream>
#include <string>
#include "matrix.h"

Matrix::Matrix(std::string name, std::pair<int, int> dim, int mult = 0)
{
    m_name = name;
    m_dim = dim;
    m_mult = mult;
}
