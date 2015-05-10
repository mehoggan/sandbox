#include "euler_math.h"

unsigned int euler_math::even_fibonacci_numbers_sum(unsigned int N)
{
  unsigned long long sum = 0;
  for (unsigned int n = 1; n <= N; ++n) {
    const double sqrt5 = std::sqrt(5);
    const double part1 = std::pow(1 + sqrt5, n);
    const double part2 = std::pow(1 - sqrt5, n);
    const double diff = part1 - part2;
    const double deno = std::pow(2.0, n) * std::sqrt(5);

    // Binet's Formula
    // (From http://mathworld.wolfram.com/BinetsFibonacciNumberFormula.html)
    const double Fn = diff / deno;

    if (Fn > 4000000) {
      break;
    }

    if (((unsigned int)Fn % 2) == 0) {
      std::cout << Fn << std::endl;
      sum += Fn;
    }
  }
  return sum;
}

void euler_math::potential_prime_factors(
  std::vector<unsigned long long int> &out,
  unsigned long long int N)
{
  typedef unsigned long long int ulli;
  typedef std::list<ulli> ull_list;

  const ulli MAX = std::sqrt(N);
  out.reserve(MAX);

  ull_list natural_numbers;
  for(ulli i = 3ull; i < MAX; i += 2) {
    natural_numbers.push_back(i);
  }

  // Sieve a list
  while (!natural_numbers.empty()) {
    ulli current_prime = natural_numbers.front();
    for (ull_list::iterator it = natural_numbers.begin();
      it != natural_numbers.end();) {

      if (*it % current_prime == 0 && it != natural_numbers.begin()) {
        it = natural_numbers.erase(it);
      } else {
        ++it;
      }
    }
    out.push_back(natural_numbers.front());
    natural_numbers.pop_front();
  }
}

