#include <utility/interval.h>

#include <iostream>
#include <list>
#include <sstream>

/// Problem: What is the largest subset of mutually non-overlapping intervals
/// which can be selected form the input of a set of N intervals. Assume that
/// the profit for each interval is the same.
void max_scheduling(std::list<utility::interval<int>> intervals)
{
  intervals.sort();

  std::list<utility::interval<int>> subset;
  while (!intervals.empty()) {
    subset.push_back(intervals.front());
    intervals.pop_front();

    while (subset.back().intersects(intervals.front())) {
      intervals.pop_front();
    }
  }

  for (auto interval : subset) {
    std::cout << interval << std::endl;
  }
}

int main(int argc, char *argv[])
{
  std::string input;
  unsigned int test_cases = 0;

  std::cin >> input;
  std::stringstream ss;
  ss << input;
  ss >> test_cases;

  std::list<utility::interval<int>> intervals;
  for (unsigned int test_case = 0; test_case < test_cases; ++test_case) {
    std::cin >> input;
    ss.clear();
    ss << input;
    int min = 0;
    ss >> min;

    std::cin >> input;
    ss.clear();
    ss << input;
    int max = 0;
    ss >> max;

    intervals.push_back(utility::interval<int>(min, max));
  }

  max_scheduling(intervals);

  return 0;
}
