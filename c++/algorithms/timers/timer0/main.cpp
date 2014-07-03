#include "TimerManager.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>

extern "C"
void func1(int id)
{
  std::cout << "I was called (1)" << std::endl;
}

extern "C"
void func2(int id)
{
  struct timeval l_tv;
  gettimeofday(&l_tv, NULL);
  std::cout << "I was called (2) @ " << l_tv.tv_usec << std::endl;
}

int main(int, char *[])
{
  TimerManager t;
  t.addTimer(1000000 / 2, func1);
  t.addTimer(1000000 * 4, func2);
  t.removeTimer(1000000 * 4, func2);
  t.addTimer(1000000 / 10, func2);

  t.start();
  while(true) {
    sleep(1);
  }
  return 0;
}
