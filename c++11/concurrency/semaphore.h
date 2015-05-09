#ifndef SEMAPHORE_H_INCLUDED
#define SEMAPHORE_H_INCLUDED

#include <non_copyable_movable.h>

#include <atomic>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>

class semaphore : public non_copyable_movable
{
public:
  explicit semaphore(int n);

  void wait();

  void signal();

private:
  std::atomic<int> m_n;

  std::condition_variable m_condition;
  std::mutex m_mutex;
};

#endif
