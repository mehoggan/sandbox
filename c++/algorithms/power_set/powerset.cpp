#include <iostream>

enum SIZE{size=3};
int array[size] = {1, 2, 3};

void print_power_set()
{
  int iterations = (1 << size);
  std::cout << "There will be " << iterations << " iterations" << std::endl;
  for (unsigned int i = 0; i < iterations; ++i) {
    unsigned int mask = 1;
    unsigned int index = 0;
    while(mask > 0) {
      int check =  (i & mask);
      if (check) {
        std::cout << array[index] << ", ";
      }
      mask <<= 1;
      index++;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  print_power_set();
}
