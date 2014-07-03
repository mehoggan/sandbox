/*
 * Q: Problem what is the smallest positive number that is evenly divisible
 * by all of the numbers from 1 to 20?
 *
 * A: Naive solution: Start at 20 iterate through values till all %i == 0
 */

#include <cstdlib>
#include <climits>
#include <iostream>

class divisible_by_1_to_20_inclusive
{
public:
  divisible_by_1_to_20_inclusive()
  {
    int x;
    for (x = 21; x < INT_MAX; ++x) {
      bool found = true;
      for (int y = 1; y <= 20; ++y) {
        if (x%y != 0) {
          found = false;
          break;
        }
      }
      if (found) {
        std::cout << x << std::endl;
        break;
      }
    }
  }
};

int main(int argc, char *argv[]) 
{
  divisible_by_1_to_20_inclusive();
}
