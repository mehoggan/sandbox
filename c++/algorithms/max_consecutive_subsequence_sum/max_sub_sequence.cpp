/* Temporarily make global variable to hold
 * the max sum of a sequence
 */
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

/*!
 * Struct that keeps track of not only max 
 * sum for a sequence but the sequence itself
 */
struct max_sum_subseqence
{
public:
  std::vector<int> vect;
  int sum;
} max_sequence;

typedef std::vector<int>::iterator vect_it;
std::vector<int> my_vec;

/*!
 * Use divide and conqour to solve the largest 
 * consecutvie subsequence sum of a list
 */
int max_consecutive_sub_sequence_sum(vect_it left, vect_it right)
{
  /*
   * Base case to handle if you have empty set
   */
  if (left == right) {
    return 0;
  }

  /*
   * Base case to handle if you have only one element
   * in set
   */ 
  if (std::distance(left, right) == 1) {
    return (*left);
  }

  /*
   * Partition the set into a left and 
   * a right get max of the two sums
   * and return it
   */
  int actual_max = 0;
  for (; left != right - 1; ++left) {
    int left_sum = max_consecutive_sub_sequence_sum(left, left + 1);
    int right_sum = max_consecutive_sub_sequence_sum(left + 1, right);
    
    int max = 0;
    vect_it tmp_left = left;
    for (;tmp_left != right; ++tmp_left) {
        max += (*tmp_left);
    }
    int max2 = std::max(left_sum, right_sum);
    actual_max = std::max(max, max2);
    if (actual_max > max_sequence.sum) {
      max_sequence.sum = actual_max;
    }
  }
  return actual_max;
}

int main(int argc, char *argv[]) {
  max_sequence.sum = 0;
  my_vec.push_back(-10);
  my_vec.push_back(-17);
  my_vec.push_back(-4);
  my_vec.push_back(-5);
  max_consecutive_sub_sequence_sum(
              my_vec.begin(), my_vec.end());
  std::cout << max_sequence.sum << std::endl;
  return 0;
}


