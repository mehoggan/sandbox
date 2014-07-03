#include "timer.h"

Timer::Timer()
{
}

void Timer::run(sig_func callback, long long micro_secs, long long secs)
{
  if(callback) {
    m_sigaction.sa_flags = SA_SIGINFO;
    m_sigaction.sa_sigaction = callback;
    sigemptyset(&m_sigaction.sa_mask);
    if (sigaction(SIGALRM, &m_sigaction, NULL) == -1) {
      throw TimerException(std::string("sigaction failure"));
    }

    /* Block timer signal temporarily */
    sigemptyset(&m_segset);
    sigaddset(&m_segset, SIGALRM);
    if (sigprocmask(SIG_BLOCK, &m_segset, NULL) == -1) {
      throw TimerException(std::string("sigprocmask failure"));
    }

    /* Specify Interval and Run Timer */
    m_intert.it_value.tv_sec = 0;//secs;
    m_intert.it_value.tv_usec = micro_secs;
    m_intert.it_interval = m_intert.it_value;
    if (setitimer(ITIMER_REAL, &m_intert, NULL) != 0) {
      throw TimerException(std::string("failure to create interval timer"));
    }

    /* Unlock the timer signal */
    if (sigprocmask(SIG_UNBLOCK, &m_segset, NULL) == -1) {
      throw TimerException(std::string("sigprocmask failure"));
    }
  } else {
      throw TimerException(std::string("failure to initialize callback (call constructor first)"));
  }
}

