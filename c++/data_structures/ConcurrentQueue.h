#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>

#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

namespace NavCore
{
namespace Core
{

template<typename Data>
class ConcurrentQueue
	: public boost::noncopyable
{

public:
	int Size()
	{
		boost::lock_guard<boost::mutex> lock(m_Mutex);
		return m_Queue.size();
	}

	void Push(Data const& data)
	{
		boost::lock_guard<boost::mutex> lock(m_Mutex);
		m_Queue.push(data);
		m_ConditionVariable.notify_all();
	}

	bool Empty() const
	{
		boost::lock_guard<boost::mutex> lock(m_Mutex);
		return m_Queue.empty();
	}

	void Clear()
	{
		boost::lock_guard<boost::mutex> lock(m_Mutex);
		std::queue<Data> empty;
		std::swap(m_Queue, empty);
		m_ConditionVariable.notify_all();
	}

	bool TryPop(Data& poppedValue)
	{
		boost::lock_guard<boost::mutex> lock(m_Mutex);
		if(m_Queue.empty())
		{
			return false;
		}

		poppedValue = m_Queue.front();
		m_Queue.pop();
		return true;
	}

	void WaitAndPop(Data& poppedValue)
	{
		boost::unique_lock<boost::mutex> lock(m_Mutex);
		m_ConditionVariable.wait(lock, QueueNotEmpty(m_Queue));
		NT_ASSERT(!m_Queue.empty());
		poppedValue = m_Queue.front();
		m_Queue.pop();
	}

	// Used to deal with the Lost Wake Up Problem (Antonym of Spurious Wakeup Problem)
	template <typename Duration>
	bool TimedWaitAndPop(Data& poppedValue, const Duration& waitDuration)
	{
		boost::unique_lock<boost::mutex> lock(m_Mutex);
		if(!m_ConditionVariable.timed_wait(lock, waitDuration, QueueNotEmpty(m_Queue)))
		{
			return false;
		}

		poppedValue = m_Queue.front();
		m_Queue.pop();
		return true;
	}

	struct QueueNotEmpty
	{
		std::queue<Data>& m_Queue;

		QueueNotEmpty(std::queue<Data>& queue)
			: m_Queue(queue)
		{
		}

		bool operator()() const
		{
			return !m_Queue.empty();
		}
	};

	template<bool (*T)(Data &, Data &)>
	void PushNoDupes(const Data& data)
	{
		boost::lock_guard<boost::mutex> lock(m_Mutex);
		std::queue<Data> queue2;
		while (!m_Queue.empty())
		{
			if (!T(m_Queue.front(), const_cast<Data &>(data)))
			{
				queue2.push(m_Queue.front());
			}
			m_Queue.pop();
		}
		while (!queue2.empty())
		{
			m_Queue.push(queue2.front());
			queue2.pop();
		}
		m_Queue.push(data);
		m_ConditionVariable.notify_all();
	}

private:
	 std::queue<Data> m_Queue;
	 mutable boost::mutex m_Mutex;
	 boost::condition_variable m_ConditionVariable;
};


} // namespace Core
} // namespace NavCore

#endif

