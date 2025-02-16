#include <cstdio>
#include <thread>
#include "Commons.hpp"
#include "Parallel.hpp"
#include "Sequential.hpp"

int main(int argc, char** argv)
{
	printf("Ignition!\n");
	auto startTime{steady_clock::now()};
	int bucketSizes[Commons::SET_COUNT]{};
	std::array<int*, Commons::SET_COUNT> buckets{Sequential::makeCardArray(bucketSizes)};
	{
        ThreadPool threadPool{};
        // std::array<std::jthread, Commons::SET_COUNT> threads;
        for(int i{0}; i < Commons::SET_COUNT; ++i)
            threadPool.queueJob(Parallel::quickSortMono(buckets[i], 0, bucketSizes[i] - 1, threadPool));
            // threads[i] = std::jthread{Parallel::quickSort, buckets[i], 0, bucketSizes[i] - 1};
		while(threadPool.busy());
	}

	// for(std::jthread& i : threads) i.join();
	auto finishTime{steady_clock::now()};
	std::chrono::duration<double> duration{finishTime - startTime};
	printf("Finished! %f seconds!", duration.count());
}