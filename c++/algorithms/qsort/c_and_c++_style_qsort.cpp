#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>

int partition(int left, int right, int *sort_array);

/*
 * quick sort method: initial left index must be 0
 * and initial right index must be sizeof(array)/
 * sizeof(<data type>) - 1
 */
void quick_sort(int left, int right, int *sort_array)
{
  /*
   * If right is less than left
   * do nothing else execute body of
   * method
   */
  if ((right - left) > 0) {
    /*
     * Get pivot index
     */
    int index = partition(left, right, sort_array);
    /*
     * Sort the left side not including pivot
     */
    quick_sort(left, index - 1, sort_array);
    /*
     * Sort the right side not including pivot
     */
    quick_sort(index + 1, right, sort_array);
  }
}

/*
 *  swap two integers in array
 */
void swap(int index1, int index2, int *sort_array)
{
  int tmp = sort_array[index1];
  sort_array[index1] = sort_array[index2];
  sort_array[index2] = tmp;
}

/*
 * Note that right signifies N - 1 not N
 */
int partition(int left, int right, int *sort_array)
{
  int pivot_index = left + rand()%(right - left);
  int pivot_value = sort_array[pivot_index];
  int l = left + 1;
  int r = right;
  swap(left, pivot_index, sort_array);
  while (l <= r) {
    while (sort_array[l] < pivot_value && l <= r) {
      ++l;
    }
    while (sort_array[r] >= pivot_value && l <= r) {
      --r;
    }
    if (l < r && sort_array[l] > pivot_value) {
      swap(l, r, sort_array);
    }
  }
  swap(left, r, sort_array);
  return r;
}

int main(int argc, char *argv[]) {
  std::vector<int> data;
  for (int x = 1; x <= 4; x++) {
    data.push_back(x);
  }
  do {
    for (unsigned int x = 0; x < data.size(); ++x) {
      fprintf(stderr, "%d ", data[x]);
    }
    fprintf(stderr, "\n");
    std::vector<int> copy;
    std::copy(data.begin(), data.end(), std::back_inserter(copy));
    quick_sort(0, (copy.size() - 1), copy.data());
    for (unsigned int x = 0; x < copy.size(); ++x) {
      fprintf(stderr, "%d ", copy[x]);
    }
    fprintf(stderr, "\n\n");
    copy.clear();
  } while (std::next_permutation(data.begin(), data.end()));
}
