#include <QCoreApplication>

/* You are given a 2-Dimensional array with M rows and N columns. You are
 * initially positioned at (0,0) which is the top-left cell in the array. You
 * are allowed to move either right or downwards. The array is filled with 1's
 * and 0's. A 1 indicates that you can move through that cell, a 0 indicates
 * that you cannot move through the cell. Given the function numberOfPaths which
 * takes in the above 2-D array, return the number of paths from the top-left
 * cell to the bottom-right cell (i.e. (0,0) to (M-1,N-1)).
 */

#include <iostream>

#define ROW 3
#define COL 3

bool pathCount(int (&matrix)[ROW][COL], int M, int N, int m, int n, int &paths)
{
  std::cout << "@ (" << m << ", " << n << ")" << std::endl;
  if (m == M - 1 && n == N - 1 && matrix[m][n]) {
      ++paths;
      return;
  } else if (m == M || n == N || !matrix[m][n]) {
      return;
  }

  pathCount(matrix, N, M, m, n + 1, paths);
  pathCount(matrix, N, M, m + 1, n, paths);

  return false;
}

int pathCount(int (&matrix)[ROW][COL], int M, int N)
{
  int paths = 0;
  pathCount(matrix, M, N, 0, 0, paths);
  return paths;
}

int main(int /*argc*/, char */*argv*/[])
{
  int matrix[ROW][COL] =
  {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1},
  };
  int paths = pathCount(matrix, ROW, COL);
  paths = paths;

  return 0;
}
