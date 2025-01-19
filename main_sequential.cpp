#include <cstdio>
#include "Sequential.hpp"
#include "Commons.hpp"

int main()
{
	printf("Ignition!\n");
	auto startTime{steady_clock::now()};
	int bucketSizes[Commons::SET_COUNT]{};
	std::array<int*, Commons::SET_COUNT> buckets{Sequential::makeCardArray(bucketSizes)};

	// comment this to disable insertion sort
	// for(int i{0}; i < Commons::SET_COUNT; ++i) Sequential::insertionSort(buckets[i], bucketSizes[i]);

	// uncomment this to enable quicksort
	for(int i{0}; i < Commons::SET_COUNT; ++i)
		Sequential::quickSort(buckets[i], 0, static_cast<int>(bucketSizes[i]) - 1);
	auto finishTime{steady_clock::now()};
	std::chrono::duration<double> duration{finishTime - startTime};
	printf("Finished! %f seconds!\n", duration.count());
	return 0;
}
