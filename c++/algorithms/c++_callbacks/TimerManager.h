#ifndef TIMERMANAGER_H_
#define TIMERMANAGER_H_

#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <list>
#include <iterator>
#include <algorithm>
#include <sys/time.h>
#include <assert.h>
#include "CallBack.h"

template<class CallObject>
class TimerManager {
public:
  TimerManager();
  ~TimerManager();
  void start();
  void stop();
  void addTimer(long usec, Callback<CallObject, void, int> *callback);
  void removeTimer(long usec, Callback<CallObject, void, int> *callback);
private:
  template<class TimerCallObject>
  class Timer  
  {
  public:
      Timer(long usec, Callback<CallObject, void, int> *callback) :
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
    Callback<CallObject, void, int> *callback;
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
  Timer<CallObject> setUpTimer(long micro_duration, Callback<CallObject, void, int> *callback);
  void run();
  bool m_bRunning;
  bool m_bGo;
  long m_lMinSleep;
  typename std::list<Timer<CallObject> > m_cTimers;
  pthread_t m_tTimerThread;
  pthread_cond_t m_tGoLockCondition;
  pthread_mutex_t m_tGoLock;
  template <class Object> friend void *create_pthread(void *data);
};

template<class Object>
void *create_pthread(void *data)
{
  TimerManager<Object> *tm = static_cast<TimerManager<Object> *>(data);
  tm->run();
  return data;
}

template<class CallObject>
TimerManager<CallObject>::TimerManager() :
  m_bRunning(false),
  m_bGo(false),
  m_lMinSleep(0)
{
  int mutex_creation = pthread_mutex_init(&m_tGoLock, NULL);
  if(mutex_creation != 0) {
    throw TimerManager::TimerError(std::string("Failed to create mutex"));
  }

  int mutex_cond_creation = pthread_cond_init(&m_tGoLockCondition, NULL);
  if(mutex_cond_creation != 0) {
    throw TimerManager::TimerError(std::string("Failed to create condition mutex"));
    return;
  }

  int thread_creation = pthread_create(&m_tTimerThread, NULL, create_pthread<CallObject>, this);
  if(thread_creation != 0) {
    throw TimerManager::TimerError(std::string("Failed to create thread"));
    return;
  }
  m_bRunning = true;
}

template<class CallObject>
TimerManager<CallObject>::~TimerManager()
{
    pthread_mutex_lock(&m_tGoLock);
    m_bRunning = false;
    pthread_mutex_unlock(&m_tGoLock);
    void *result;
    pthread_join(m_tTimerThread, &result);
    pthread_mutex_destroy(&m_tGoLock);
    pthread_cond_destroy(&m_tGoLockCondition);
}

template<class CallObject>
void TimerManager<CallObject>::run()
{
  while(m_bRunning) {
    pthread_mutex_lock(&m_tGoLock);
    while (!m_bGo) {
      pthread_cond_wait(&m_tGoLockCondition, &m_tGoLock);
    }
    pthread_mutex_unlock(&m_tGoLock);
    if (!m_bRunning) {
      break;
    }

    struct timeval l_tv;
    usleep(std::max(0l, m_lMinSleep));
    gettimeofday(&l_tv, NULL);
    m_lMinSleep = 0;
    long l_lMin = 0;
    for(typename std::list<Timer<CallObject> >::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it) {
      TimerManager<CallObject>::Timer<CallObject> l_oTimer = *it;
      long elapsed_time = ((l_tv.tv_sec * 1000000 + l_tv.tv_usec) - (l_oTimer.start));
      l_lMin = elapsed_time - l_oTimer.duration;
      if (elapsed_time >= l_oTimer.duration) {
        l_lMin = l_oTimer.duration;
        l_oTimer.callback->execute(0);
        gettimeofday(&l_tv, NULL);
        it->start = (l_tv.tv_sec * 1000000) + l_tv.tv_usec;
      }
      m_lMinSleep = std::min(m_lMinSleep, l_lMin);
    }
  }
}

template<class CallObject>
void TimerManager<CallObject>::start()
{
  pthread_mutex_lock(&m_tGoLock);
  m_bGo = true;
  pthread_cond_signal(&m_tGoLockCondition);
  pthread_mutex_unlock(&m_tGoLock);
}

template<class CallObject>
void TimerManager<CallObject>::stop()
{
  pthread_mutex_lock(&m_tGoLock);
  m_bGo = false;
  pthread_mutex_unlock(&m_tGoLock);
}

template<class CallObject>
TimerManager<CallObject>::Timer<CallObject> TimerManager<CallObject>::setUpTimer(long micro_duration, Callback<CallObject, void, int> *callback)
{
  struct timeval l_tv;
  gettimeofday(&l_tv, NULL);
  Timer<CallObject> l_oTimer(micro_duration, callback);
  l_oTimer.start = (l_tv.tv_sec * 1000000) + l_tv.tv_usec;
  return l_oTimer;
}

template<class CallObject>
void TimerManager<CallObject>::addTimer(long usec, Callback<CallObject, void, int> *callback)
{
  pthread_mutex_lock(&m_tGoLock);
  Timer<CallObject> insert = setUpTimer(usec, callback);
  for (typename std::list<Timer<CallObject> >::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it) {
    if (*it == insert) {
        return;
    }
  }
  m_cTimers.push_back(insert);
  pthread_mutex_unlock(&m_tGoLock);
}

template<class CallObject>
void TimerManager<CallObject>::removeTimer(long usec, Callback<CallObject, void, int> *callback) {
  pthread_mutex_lock(&m_tGoLock);
  Timer<CallObject> l_oTimer(usec, callback);

  typename std::list<Timer<CallObject> >::iterator new_end = std::remove_if(
              m_cTimers.begin(),
              m_cTimers.end(),
              TimerManager<CallObject>::Timer<CallObject>(l_oTimer)
             );
  m_cTimers.erase(new_end, m_cTimers.end());

#ifdef _TEST
  assert(m_cTimers.size() == 1);
#endif

  pthread_mutex_unlock(&m_tGoLock);
}
#endif
