#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>

struct Matrix_error
{
    Matrix_error(std::string error)
    {
        m_error = error;
    }
    std::string m_error;
};

class Matrix
{
public:
    Matrix(std::string name, std::pair<int, int> dim, int mult);

    Matrix operator* (Matrix &m) throw (Matrix_error)
    {
        if (m_dim.second != m.m_dim.first) {
            throw Matrix_error(std::string("ERROR:" 
                "Matrix Multiplication Dimension Error")
                + m_name + m.m_name + std::string("\n"));
        }
        Matrix M(std::string("("+m_name + m.m_name+")"), 
            std::pair<int, int>(m_dim.first, m.m_dim.second), 
            m.m_mult + m_mult + m_dim.first*m_dim.second*m.m_dim.second);
        return M;
    }
    int getMultiplications() const {return m_mult;}
    std::string getName() const {return m_name;}
    std::pair<int,int> getDimensions() const {return m_dim;}
private:
    std::string m_name;
    std::pair<int,int> m_dim;
    int m_mult;

    friend std::ostream& operator<< (std::ostream &out, Matrix &m)
    {
        return out << m.m_name << "(" << m.m_dim.first
                   << ", " << m.m_dim.second << ")";
    }
};

#endif /* MATRIX_H_ */
