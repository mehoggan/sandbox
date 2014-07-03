#ifndef TIMER_H
#define TIMER_H

#include <boost/bind/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <stdint.h>
#include <iostream>
#include <vector>

template <uint32_t tMilliSeconds>
class Timer {
private:
    static Timer *_instance;
    uint32_t mMilliSeconds;
    boost::recursive_mutex mListMutex;
    boost::thread mTimerThread;
    std::vector<boost::function<void()> > mHandlerList;

    Timer();
    Timer(const Timer &other);
    Timer &operator=(const Timer &other);
    void Run();

public:
    static boost::shared_ptr<Timer<tMilliSeconds> > Instance();
    void AddHandler(boost::function<void()> tmpBoostFunction);
};

template <uint32_t tMilliSeconds>
Timer<tMilliSeconds>::Timer() {
    mMilliSeconds = tMilliSeconds;

    mTimerThread = boost::thread(
        boost::bind(&Timer<tMilliSeconds>::Run, this));
    mTimerThread.detach();
}

template <uint32_t tMilliSeconds>
boost::shared_ptr<Timer<tMilliSeconds> >
Timer<tMilliSeconds>::Instance() {
    if (!_instance) {
        _instance = new Timer<tMilliSeconds>();
    }
    return boost::shared_ptr<Timer<tMilliSeconds> >(_instance);
}

template <uint32_t tMilliSeconds>
void Timer<tMilliSeconds>::Run() {
    while(true) {
        boost::this_thread::sleep(
            boost::posix_time::milliseconds(mMilliSeconds));
        boost::lock_guard<boost::recursive_mutex> tmpLockGuard(mListMutex);
        for (std::vector<boost::function<void()> >::iterator vect_it =
            mHandlerList.begin(); vect_it != mHandlerList.end();
            ++vect_it) {

            (*vect_it)();
        }
    }
}

template <uint32_t tMilliSeconds>
void Timer<tMilliSeconds>::AddHandler(
    boost::function<void()> tmpBoostFunction) {

    boost::lock_guard<boost::recursive_mutex> tmpLockGuard(mListMutex);
    mHandlerList.push_back(tmpBoostFunction);
}
#endif // TIMER_H
