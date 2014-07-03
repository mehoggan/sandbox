#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <climits>

typedef std::vector<unsigned long long>::const_iterator prime_it;

#define MAX_COL 900000

struct large_vector
{
public:
  large_vector(unsigned long long size, unsigned int row) :
    m_Row(row)
  {
    m_RowVector.resize(size);
  }
  std::vector<bool> m_RowVector;
  unsigned int m_Row;
};

struct prime_factor
{
public:
  prime_factor(unsigned long long N);
  ~prime_factor() {}
  void print_primes();
private:
  std::vector<bool> m_Primes;
  std::vector<large_vector>m_Vect_Primes;
  unsigned long long m_N;
};

prime_factor::prime_factor(unsigned long long N) :
  m_N(N)
{
  // If number is odd then we need the cieling of N/2 / MAX_COL
  int number_of_vectors = (m_N % MAX_COL == 0) ? ((m_N/2) / MAX_COL) : (((m_N/2) / MAX_COL) + 1);
  std::cout << "There will be " << number_of_vectors << " rows";
  if (number_of_vectors != 0) {
    for (int x = 0; x < number_of_vectors; ++x) {
      m_Vect_Primes.push_back(large_vector(MAX_COL, x));
    }

    time_t start, end;
    time(&start);

    m_Vect_Primes[0].m_RowVector[0] = false;
    m_Vect_Primes[0].m_RowVector[1] = false;
    unsigned long long increment = 2;
    unsigned long long index = 0;
    while (index < m_N) {
      for (index = 2*increment; index < m_N/2; index += increment) {
        unsigned long long row = index/MAX_COL;
        unsigned long long col = index%MAX_COL;
        m_Vect_Primes[row].m_RowVector[col] = true;
      }
      increment += 1;
      while (m_Vect_Primes[increment/MAX_COL].m_RowVector[increment%MAX_COL]) {
        increment++;
      }
    }

    time(&end);
    std::cout << std::endl << "It took: " << difftime (end,start) << std::endl;
  }
}

void prime_factor::print_primes()
{
  for (unsigned long long index = 0; index < m_N/2; ++index) {
    if (m_Vect_Primes[index/MAX_COL].m_RowVector[index%MAX_COL] == false) {
      std::cout << index << " ";
    }
  }
  std::cout << std::endl;
}

/*!
 * Driver
 */
int main(int argc, char *argv[])
{
  static const unsigned long long N = 600851475143;
  prime_factor pf(N);
  pf.print_primes();
}
