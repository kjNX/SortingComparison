#ifndef SORTINGCOMPARISON_PARALLEL_HPP
#define SORTINGCOMPARISON_PARALLEL_HPP


#include <iostream>
#include <mutex>
#include "Commons.hpp"

namespace Parallel
{
	void liveCardGenerator(std::array<int*, Commons::SET_COUNT>& buckets, std::array<int, Commons::SET_COUNT>& bucketSizes,
						   std::array<std::mutex, Commons::SET_COUNT>& bucketMutex, bool& flag, std::mutex& flagMutex,
						   const int& size = 4000000);
	void liveInsertionSort(int* const& bucket, std::mutex& bucketMutex, bool& flag, std::mutex& flagMutex,
						   int& size);
	void quickSort(int* const& array, const int& start = 0, const int& end = -1);
};

#endif //SORTINGCOMPARISON_PARALLEL_HPP
