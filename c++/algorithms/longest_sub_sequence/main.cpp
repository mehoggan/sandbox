#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

// Global Data
enum SIZE { N = 10000 }; // Size of sequence
typedef std::vector<int>::iterator vect_it;
std::vector<int> curr_seq;
std::vector<int> larg_seq;
std::vector<int> seq; // Hold main sequence

int binary_search(int left, int right, int M) {
  int n = (left + right)/2;
  while (right != left || seq[n] != M) {
    if (right - left <= 1) {
      if (seq[left] > M) {
        return left;
      }
      else {
        return right;
      }
    }
    if (M < seq[n]) {
      right = n;
    }
    else if (M >= seq[n]) {
      left = n;
    }
    n = (right + left)/2;
  }
}

/*
 * Method that finds the longest seq
 * and prints it out at the end --
 * Complexity O(n^2) can be improved by
 * optimizing search
 */
void longest_increasing_sequence() {
   std::sort(seq.begin(), seq.end());
   std::cout << "Sorted Sequence is: " << std::endl;
   for (std::vector<int>::iterator it = seq.begin(); it != seq.end(); ++it) {
     std::cout << (*it) << " ";
   }
   std::cout << std::endl;

  for (int start_index = 0; start_index != N; ++start_index) {
    curr_seq.push_back(seq[start_index]);

    int tmp_index = start_index;
    // while still larger elements in list
    while (tmp_index < N - 1) {
      tmp_index = binary_search(tmp_index + 1, N, seq[tmp_index]);
      curr_seq.push_back(seq[tmp_index]);
    }

    /*
     * Step 4 above
     */
    if (curr_seq.size() > larg_seq.size()) {
      larg_seq.clear();
      std::copy(curr_seq.begin(), curr_seq.end(), std::back_inserter(larg_seq));
    }
    curr_seq.clear();
  }

  std::cout << std::endl << "Solutoin to this is " << std::endl;
  std::copy(larg_seq.begin(), larg_seq.end(), std::ostream_iterator<int>
    (std::cout, " "));
}

int main (int argc, char *argv[]) {
  // Generate random sequence
  srand(time(NULL));
  std::cout << "Generating list " << N << " long" << std::endl;
  for (int x = 0; x < N; ++x) {
    seq.push_back(rand()%N);
  }
  std::cout << std::endl;
  // Method to print out longest common subsequence
  longest_increasing_sequence();
}

