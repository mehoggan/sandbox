#include <iostream>

int main(int argc, char *argv[]) {
  int sum = 0;
  for (int i = 0; i < 1000; ++i) {
    if (i%3 == 0 || i%5 == 0) {
      std::cout << i << ((i + 1 == 1000) ? " = " : " + ");
      sum += i;
    }
  }
  std::cout << sum << std::endl;
}
