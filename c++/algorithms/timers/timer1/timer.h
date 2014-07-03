#ifndef TIMER_H
#define TIMER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <iostream>

typedef void (*sig_func)(int sig, siginfo_t *, void*);

class Timer
{
public:
  Timer();
  void run(sig_func callback, long long nano_secs, long long secs);
  class TimerException : public std::exception {
  public:
    TimerException(std::string warning) :
    m_warning(warning) { }
    ~TimerException() throw() { }
    virtual const char* what() const throw() {
        return const_cast<const char*>(m_warning.c_str());
    }
  private:
    std::string m_warning;
  };
private:
  int m_llsecs;
  struct sigaction m_sigaction;
  sigset_t m_segset;
  timer_t m_timerid;
  struct sigevent m_segevenvt;
  struct itimerval m_intert;
};

#endif // TIMER_H
