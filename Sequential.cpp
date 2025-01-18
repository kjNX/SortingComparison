#include <array>
#include <random>
#include "Sequential.hpp"
#include "Commons.hpp"

// generate randomized card sets and put them on their respective bucket (heart, club, spade, diamond or joker)
std::array<int*, Commons::SET_COUNT> Sequential::makeCardArray(int* const& bucketSizes, const unsigned int& size)
{
	std::array<int*, Commons::SET_COUNT> temp{new int[size]{}, new int[size]{}, new int[size]{}, new int[size]{}, new
	int[size]{}};
	int amount[Commons::SET_COUNT]{0, 0, 0, 0, 0};

	std::random_device rand{};
	std::seed_seq sequence{rand(), rand(), rand(), rand()};
	std::ranlux48 engine{sequence};
	std::uniform_int_distribution<> dist{0, Commons::max_cards - 1};
	for(unsigned i{0u}; i < size; ++i)
	{
		int curr{dist(engine)};
		int bucket{curr / 13};
		temp[bucket][amount[bucket]] = curr;
		++amount[bucket];
	}
	for(int i{0}; i < Commons::SET_COUNT; ++i) shrink(temp[i], amount[i]);
	if(bucketSizes) for(int i{0}; i < Commons::SET_COUNT; ++i) bucketSizes[i] = amount[i];
	return temp;
}

void Sequential::shrink(int*& array, const unsigned int& size)
{
	int* temp{new int[size]{}};
	for(int i{0}; i < size; ++i) temp[i] = array[i];
	delete[] array;
	array = temp;
}

void Sequential::insertionSort(int* const& array, const unsigned int& size)
{
	for(unsigned i{1u}; i < size; ++i)
		for(unsigned j{i}, k{i - 1u}; k < size && array[k] > array[j]; j = k, --k)
			std::swap(array[j], array[k]);
}

void Sequential::quickSort(int* const& array, const int& start, const int& end)
{
	if(start < end)
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
		quickSort(array, start, pivot);
		quickSort(array, pivot + 1, end);
	}
}
