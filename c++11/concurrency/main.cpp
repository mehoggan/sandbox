#include <iostream>
#include <semaphore.h>

int main(int argc, char *argv[])
{
  semaphore sem(5);
  sem.wait();
  sem.signal();
  return 0;
}
