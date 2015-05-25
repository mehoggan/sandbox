#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
  auto elements = std::distance(begin, end);
  if (elements <= 1) {
    return;
  }

  Iterator it_pivot = begin;
  Iterator it_lhs = begin + 1; // Pivot is at begin
  Iterator it_rhs = end - 1; // End is 1 outside of current sub-array

  while (it_lhs < it_rhs) {
    // Keep all pivot values on lhs (*it_lhs <= *it_pivot)
    while (it_lhs < it_rhs && *it_lhs <= *it_pivot) ++it_lhs;
    // Move larger values and values == pivot to lhs partition
    while (it_lhs < it_rhs && *it_rhs > *it_pivot) --it_rhs;
    if (it_lhs < it_rhs) {
      std::iter_swap(it_lhs, it_rhs);
    }
  }

  // To deal with the case where we have two elements and the larger one is
  // in the swap position.
  if (*it_lhs < *it_pivot) {
    std::iter_swap(it_pivot, it_lhs);
  }

  // it_lhs should point one past the end of the lhs
  // implies that it_rhs will be at last element in left hand partition
  quick_sort(begin, it_lhs);
  quick_sort(it_rhs, end);
}

int main(int argc, char *argv[])
{
  std::vector<int> two_a = {1, 2};
  quick_sort(two_a.begin(), two_a.end());
  std::copy(two_a.begin(), two_a.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> two_b = {2, 1};
  quick_sort(two_b.begin(), two_b.end());
  std::copy(two_a.begin(), two_a.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> three_a = {1, 2, 3};
  quick_sort(three_a.begin(), three_a.end());
  std::copy(three_a.begin(), three_a.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> three_b = {1, 3, 2};
  quick_sort(three_b.begin(), three_b.end());
  std::copy(three_b.begin(), three_b.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> three_c = {2, 1, 3};
  quick_sort(three_c.begin(), three_c.end());
  std::copy(three_c.begin(), three_c.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> three_d = {2, 3, 1};
  quick_sort(three_d.begin(), three_d.end());
  std::copy(three_d.begin(), three_d.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> three_e = {3, 1, 2};
  quick_sort(three_e.begin(), three_e.end());
  std::copy(three_e.begin(), three_e.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> three_f = {3, 2, 1};
  quick_sort(three_f.begin(), three_f.end());
  std::copy(three_f.begin(), three_f.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> foo_bar = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  quick_sort(foo_bar.begin(), foo_bar.end());
  std::copy(foo_bar.begin(), foo_bar.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

