#ifndef EULER_MATH_H
#define EULER_MATH_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

class euler_math
{
public:
  static unsigned int even_fibonacci_numbers_sum(unsigned int N);

  static void potential_prime_factors(
    std::vector<unsigned long long int> &out,
    unsigned long long int N);
};

#endif // EULER_MATH_H
