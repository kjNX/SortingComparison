#include <cstdio>
#include <vector>
#include <iostream>
#include <thread>
#include "Parallel.hpp"
#include "Commons.hpp"
#include "Sequential.hpp"

int main(int argc, char** argv)
{
	printf("Ignition!\n");
	auto startTime{steady_clock::now()};
	constexpr int TOTAL_SIZE{100000};
	bool flag{false}; // 好き好き好き好き
	std::mutex flagMutex{};
	std::array<int, Commons::SET_COUNT> bucketSizes{};
	std::array<int*, Commons::SET_COUNT> buckets{new int[TOTAL_SIZE]{}, new int[TOTAL_SIZE]{}, new int[TOTAL_SIZE]{},
								new int[TOTAL_SIZE]{}, new int[TOTAL_SIZE]{}};
	std::array<std::mutex, Commons::SET_COUNT> bucketMutexes{};

	std::jthread cardDispatcher{Parallel::liveCardGenerator, std::ref(buckets), std::ref(bucketSizes),
								std::ref(bucketMutexes), std::ref(flag), std::ref(flagMutex), TOTAL_SIZE};
	std::array<std::jthread, Commons::SET_COUNT> sortThreads;
	for(int i{0}; i < Commons::SET_COUNT; ++i)
		sortThreads[i] = std::jthread{
				Parallel::liveInsertionSort, std::ref(buckets[i]), std::ref(bucketMutexes[i]),
				std::ref(flag), std::ref(flagMutex), std::ref(bucketSizes[i])
		};

	cardDispatcher.join();
	for(std::jthread& i : sortThreads) i.join();
	std::array<std::jthread, Commons::SET_COUNT> shrinkThreads;
	for(int i{0}; i < Commons::SET_COUNT; ++i)
		shrinkThreads[i] = std::jthread{Sequential::shrink, std::ref(buckets[i]), bucketSizes[i]};
	for(std::jthread& i : shrinkThreads) i.join();
	auto finishTime{steady_clock::now()};
	std::chrono::duration<double> duration{finishTime - startTime};
	printf("Finished! %f seconds!\n", duration.count());

	return 0;
}