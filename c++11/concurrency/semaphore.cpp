#include <semaphore.h>

semaphore::semaphore(int n) :
  m_n(n)
{}

void semaphore::wait()
{
  while (m_n < 0) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock);
  }
  --m_n;
}

void semaphore::signal()
{
  ++m_n;
  m_condition.notify_one();
}
