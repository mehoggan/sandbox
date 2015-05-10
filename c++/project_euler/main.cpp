#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>

#include <euler_math.h>

void largest_prime_factor()
{
  std::cout << ULONG_LONG_MAX << std::endl;
  const unsigned long long int N = 600851475143;
  std::vector<unsigned long long int> potential_prime_factors;
  euler_math::potential_prime_factors(potential_prime_factors, N);
  std::copy(potential_prime_factors.begin(), potential_prime_factors.end(),
    std::ostream_iterator<unsigned long long int>(std::cout, " "));

  unsigned long long int n = N;
  size_t index = 0;
  std::vector<unsigned long long int> prime_factors;
  while (n > 1) {
    while (n % 2 == 0) {
      n /= 2;
      prime_factors.push_back(2);
    }

    unsigned long long int next_prime = potential_prime_factors[index];
    while (n % next_prime == 0) {
      n /= next_prime;
      prime_factors.push_back(next_prime);
    }

    ++index;
  }

  unsigned long long int max = prime_factors.back();
  std::cout << "Answer " << max << std::endl;
}

void even_fibonanci_numbers()
{
  // Linear time calculation
  unsigned int sum = euler_math::even_fibonacci_numbers_sum(4000000);
  // Normal is F(N) = F(N - 1) + F(N - 2);
  std::cout << "Answer " << sum << std::endl;
}

void multiples_of_3_or_5_below(unsigned int n) {
  std::set<unsigned int> multiples;

  unsigned int three_x = 3;
  while (three_x < n) {
      multiples.insert(three_x);
      three_x += 3;
  }

  unsigned int five_x = 5;
  while (five_x < n) {
      multiples.insert(five_x);
      five_x += 5;
  }

  unsigned int sum = 0;
  sum = std::accumulate(multiples.begin(), multiples.end(), 0);

  std::cout << "Answer " << sum << std::endl;
}

int main(int argc, char *argv[])
{
    //multiples_of_3_or_5_below(1000);
    //even_fibonanci_numbers();
    largest_prime_factor();
    return 0;
}
