#include "ThreadPool.hpp"

#include <mutex>

void ThreadPool::threadLoop()
{
	while(true)
	{
		std::function<void()> job;
		{
			std::unique_lock lock{m_queueMutex};
			m_mutexCondition.wait(lock, [this]
			{ return !m_jobs.empty() || m_shouldTerminate; });
			if(m_shouldTerminate) return;
			job = m_jobs.front();
			m_jobs.pop();
		}
		job();
	}
}

void ThreadPool::queueJob(const std::function<void()>& job)
{
	{
		std::unique_lock lock{m_queueMutex};
		m_jobs.push(job);
	}
	m_mutexCondition.notify_one();
}

bool ThreadPool::busy()
{
	bool isBusy;
	{
		std::unique_lock lock{m_queueMutex};
		isBusy = !m_jobs.empty();
	}
	return isBusy;
}

ThreadPool::ThreadPool(const unsigned& thread) : m_shouldTerminate{false}, m_threadPool(thread)
{
	for(std::jthread& i : m_threadPool) i = std::jthread(&ThreadPool::threadLoop, this);
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock lock{m_queueMutex};
		m_shouldTerminate = true;
	}
	m_mutexCondition.notify_all();
	for(std::jthread& i : m_threadPool) i.join();
	m_threadPool.clear();
}
