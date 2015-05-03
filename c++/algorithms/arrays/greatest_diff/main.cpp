#include <iostream>
#include <iterator>
#include <climits>
#include <cstring>
#include <cstdlib>

 /* Given an array of integers, return the maximum difference of any pair of
  * numbers such that the larger integer in the pair occurs a higher index
  * (in the array) than the smaller integer with which it is paired. You are
  * provided with a function maxDifference which takes in the array as a
  * parameter. You are required to return an integer. The section of the
  * program which parses the input and displays the output will be handled
  * by us. Your task is to complete the body of the function or method
  * provided, and to return the correct output.
  */

const int N = 7;
int A[N] = {2, 3, 10, 2, 4, 8, 1};

int main(int argc, char *argv[])
{
  int min = INT_MAX;
  int* min_so_far = new int[N];
  for (int i = 0; i < N; ++i) {
    if (A[i] < min) {
      min = A[i];
    }
    min_so_far[i] = min;
  }

  for (int i = 0; i < N; ++i) std::cout << A[i] << " ";
  std::cout << std::endl;
  for (int i = 0; i < N; ++i) std::cout << min_so_far[i] << " ";
  std::cout << std::endl;

  int *diff = (int*)malloc(N * sizeof(int));
  for (int i = 0; i < N; ++i) {
    diff[i] = A[i] - min_so_far[i];
  }

  std::cout << "------------------------------------" << std::endl;
  for (int i = 0; i < N; ++i) std::cout << diff[i] << " ";
  std::cout << std::endl;

  int max_diff = INT_MIN;
  for (int i = 0; i < N; ++i) {
    if (diff[i] > max_diff) {
      max_diff = diff[i];
    }
  }

  std::cout << "max_diff = " << max_diff << std::endl;
  delete [] diff;
  delete [] min_so_far;

  return 0;
}
