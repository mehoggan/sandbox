#include <iostream>
#include "timer.h"
#include <exception>
#include <fstream>

Timer t;
std::ofstream out;
static long long count = 0;

extern "C" void
handler(int sig, siginfo_t *, void *)
{
   std::cout << "Called " << count++ << " times" << std::endl;
   signal(sig, SIG_IGN);
   t.run(handler, 199999, 1);
}

int
main(int, char *[])
{
  out.open("/home/mehoggan/Desktop/log.log");

  try {
    t.run(handler, 199999, 0);
  } catch (Timer::TimerException te) {
    std::cout << te.what() << std::endl;
    exit(1);
  }

  while (true) {
  }
}


