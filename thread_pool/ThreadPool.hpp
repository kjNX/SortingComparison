#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP
#include <condition_variable>
#include <functional>
#include <queue>
#include <vector>
#include <thread>


class ThreadPool
{
private:
	bool m_shouldTerminate;
	std::mutex m_queueMutex;
	std::condition_variable m_mutexCondition;
	std::vector<std::jthread> m_threadPool;
	std::queue<std::function<void()>> m_jobs;

	void threadLoop();

public:
	explicit ThreadPool(const unsigned& thread = std::jthread::hardware_concurrency());
	~ThreadPool();

	void queueJob(const std::function<void()>& job);
	bool busy();
};



#endif //THREADPOOL_HPP
