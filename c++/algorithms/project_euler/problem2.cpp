#include <iostream>
#include <set>
#include <iterator>
#include <numeric>
/*
 * By considering the terms in the Fibonacci sequence
 * whose values do not exceed four million, find the sum
 * of the even-valued terms
 */
static const unsigned long long max = 4000000;
std::set<int> even_fibs;

int fib(int nth_fib_number) {
  if (nth_fib_number <= 1)
    return 0;

  if (nth_fib_number <= 2) 
    return 1;

  int fib_num = (fib(nth_fib_number - 1) + fib(nth_fib_number -2));
  if (fib_num < max && fib_num%2 == 0) {
    even_fibs.insert(fib_num);
  }
  return fib_num;
}

int main(int argc, char *argv[]) {
  for (int x = 0; x < 100; ++x) {
    fib(x);
    std::copy(even_fibs.begin(), even_fibs.end(), std::ostream_iterator<int>(std::cout, " + "));
    std::cout << " = " << std::accumulate(even_fibs.begin(), even_fibs.end(), 0) << std::endl;
    even_fibs.clear();
  }
}
