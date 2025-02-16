#ifndef SORTINGCOMPARISON_PARALLEL_HPP
#define SORTINGCOMPARISON_PARALLEL_HPP

#include <mutex>
#include "Commons.hpp"
#include "thread_pool/ThreadPool.hpp"

namespace Parallel
{
	void liveCardGenerator(std::array<int*, Commons::SET_COUNT>& buckets, std::array<int, Commons::SET_COUNT>& bucketSizes,
						   std::array<std::mutex, Commons::SET_COUNT>& bucketMutex, bool& flag, std::mutex& flagMutex,
						   const int& size = Commons::MAX_COUNT);
	void liveInsertionSort(int* const& bucket, std::mutex& bucketMutex, bool& flag, std::mutex& flagMutex,
						   int& size);
	void quickSort(int* const& array, const int& start, int end, ThreadPool& pool);
	std::function<void()> quickSortMono(int* const& array, const int& start, const int& end, ThreadPool& pool);
};

#endif //SORTINGCOMPARISON_PARALLEL_HPP
