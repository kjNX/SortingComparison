#ifndef SORTINGCOMPARISON_SEQUENTIAL_HPP
#define SORTINGCOMPARISON_SEQUENTIAL_HPP

#include "Commons.hpp"

namespace Sequential
{
	std::array<int*, Commons::SET_COUNT> makeCardArray(int* const& bucketSizes = nullptr, const unsigned& size = Commons::MAX_COUNT);
	void shrink(int*& array, const unsigned& size);

	void insertionSort(int* const& array, const unsigned& size);
	void quickSort(int* const& array, const int& start = 0, const int& end = -1);
};


#endif //SORTINGCOMPARISON_SEQUENTIAL_HPP
