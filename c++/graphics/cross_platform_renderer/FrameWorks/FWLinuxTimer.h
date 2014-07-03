#ifndef FWLINUXTIMER_H_
#define FWLINUXTIMER_H_

#include <stdlib.h>
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <sys/time.h>
#include <assert.h>
#include "FWCallBack.h"

template<class CallObject>
class FWLinuxTimer {
public:
  FWLinuxTimer();
  ~FWLinuxTimer();
  void start();
  void stop();
  void addTimer(long usec, FWCallBack<CallObject, int, unsigned int> *callback);
  void removeTimer(long usec, FWCallBack<CallObject, int, unsigned int> *callback);
private:
  template<class TimerCallObject>
  class Timer  
  {
  public:
      Timer(long usec, FWCallBack<CallObject, int, unsigned int> *callback) :
      duration(usec),
      callback(callback),
      start(0)
    {      
    }
    bool operator ==(Timer other)
    {
      if ((this->callback == other.callback) && (this->duration == other.duration)) {
        return true;
      }
      return false;
    }
    Timer &operator =(Timer other)
    {
      duration = other.duration;
      callback = other.callback;
      start = other.start;
      return (*this);
    }
    bool operator ()(const Timer &timer)
    {
      if((this->callback == timer.callback) && (this->duration == timer.duration)) {
        return true;
      }
      return false;
    }
    suseconds_t duration;
    FWCallBack<CallObject, int, unsigned int> *callback;
    suseconds_t start;
  };
  class TimerError : public std::exception
  {
  public:
    TimerError(std::string error) :
      m_error(error)
    {
    }
    ~TimerError() throw() {}
  protected:
    const char *what() const throw()
    {
      return m_error.c_str();
    }
  private:
    std::string m_error;
  };
  Timer<CallObject> setUpTimer(long micro_duration, FWCallBack<CallObject, int, unsigned int> *callback);
  void check_timers();
  bool m_bRunning;
  bool m_bGo;
  typename std::list<Timer<CallObject> > m_cTimers;

  friend class FWWindow;
  friend class FWWidget;
};

template<class CallObject>
FWLinuxTimer<CallObject>::FWLinuxTimer() :
  m_bRunning(false),
  m_bGo(false)
{
  m_bRunning = true;
}

template<class CallObject>
FWLinuxTimer<CallObject>::~FWLinuxTimer()
{
    m_bRunning = false;
}

template<class CallObject>
void FWLinuxTimer<CallObject>::check_timers()
{
  if(m_bRunning) {
    struct timeval l_tv;
    gettimeofday(&l_tv, NULL);
    for(typename std::list<Timer<CallObject> >::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it) {
      FWLinuxTimer<CallObject>::Timer<CallObject> l_oTimer = *it;
      long elapsed_time = ((l_tv.tv_sec * 1000000 + l_tv.tv_usec) - (l_oTimer.start));
      if (elapsed_time >= l_oTimer.duration) {
        l_oTimer.callback->execute(0);
        gettimeofday(&l_tv, NULL);
        it->start = (l_tv.tv_sec * 1000000) + l_tv.tv_usec;
      }
    }
  }
}

template<class CallObject>
void FWLinuxTimer<CallObject>::start()
{
  m_bGo = true;
}

template<class CallObject>
void FWLinuxTimer<CallObject>::stop()
{
  m_bGo = false;
}

template<class CallObject>
FWLinuxTimer<CallObject>::Timer<CallObject> FWLinuxTimer<CallObject>::setUpTimer(long micro_duration, FWCallBack<CallObject, int, unsigned int> *callback)
{
  struct timeval l_tv;
  gettimeofday(&l_tv, NULL);
  Timer<CallObject> l_oTimer(micro_duration, callback);
  l_oTimer.start = (l_tv.tv_sec * 1000000) + l_tv.tv_usec;
  return l_oTimer;
}

template<class CallObject>
void FWLinuxTimer<CallObject>::addTimer(long usec, FWCallBack<CallObject, int, unsigned int> *callback)
{
  Timer<CallObject> insert = setUpTimer(usec, callback);
  for (typename std::list<Timer<CallObject> >::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it) {
    if (*it == insert) {
        return;
    }
  }
  m_cTimers.push_back(insert);
}

template<class CallObject>
void FWLinuxTimer<CallObject>::removeTimer(long usec, FWCallBack<CallObject, int, unsigned int> *callback) {
  Timer<CallObject> l_oTimer(usec, callback);

  typename std::list<Timer<CallObject> >::iterator new_end = std::remove_if(
              m_cTimers.begin(),
              m_cTimers.end(),
              FWLinuxTimer<CallObject>::Timer<CallObject>(l_oTimer)
             );
  m_cTimers.erase(new_end, m_cTimers.end());
}
#endif
