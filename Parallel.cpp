#include "Parallel.hpp"
#include "Commons.hpp"
#include <random>
#include <mutex>
#include <thread>

void Parallel::liveCardGenerator(std::array<int*, Commons::SET_COUNT>& buckets, std::array<int, Commons::SET_COUNT>& bucketSizes,
								 std::array<std::mutex, Commons::SET_COUNT>& bucketMutex, bool& flag, std::mutex& flagMutex,
								 const int& size)
{
	std::random_device rand{};
	std::seed_seq sequence{rand(), rand(), rand(), rand()};
	std::ranlux48 engine{sequence};
	std::uniform_int_distribution<> dist{0, Commons::max_cards - 1};
	for(int i{0}; i < size; ++i)
	{
		int curr{dist(engine)};
		int bucketId{curr / 13};
		buckets[bucketId][bucketSizes[bucketId]] = curr;
		++bucketSizes[bucketId];
	}
	std::scoped_lock flagLock{flagMutex};
	flag = true;
}

// sorts cards as it receives them
void Parallel::liveInsertionSort(int* const& bucket, std::mutex& bucketMutex, bool& flag, std::mutex& flagMutex,
								 int& size)
{
	int i{1};
	// stays idle until it receives more cards or gets the finished flag.
	while(!flag)
	{
		for(; i < size; ++i)
			for(int j{i}, k{i - 1}; k >= 0 && bucket[k] > bucket[j]; j = k, --k)
			std::swap(bucket[k], bucket[j]);
		std::scoped_lock flagLock{flagMutex};
	}
	// checks for any more updates
	for(; i < size; ++i) for(int j{i}, k{i - 1}; k >= 0 && bucket[k] > bucket[j]; j = k, --k)
			std::swap(bucket[k], bucket[j]);
}

void Parallel::quickSort(int* const& array, const int& start, int end, ThreadPool& pool)
{
	while(start < end)
	{
		int pivot{start};
		int idx{end};
		bool forward{false};
		while(idx != pivot)
		{
			if(array[pivot] > array[idx])
			{
				std::swap(array[pivot], array[idx]);
				std::swap(pivot, idx);
				forward = !forward;
			}
			forward ? ++idx : --idx;
		}
		pool.queueJob(quickSortMono(array, start, pivot, pool));
		pool.queueJob(quickSortMono(array, pivot + 1, end, pool));
		// end = pivot;
	}
}

std::function<void()> Parallel::quickSortMono(int* const& array, const int& start, const int& end, ThreadPool& pool)
{ return [&] { quickSort(array, start, end, pool); }; }
