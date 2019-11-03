/*
* MmsSort.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include "MmsSort.h"

#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class MmSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::mmsSort(array.begin(), array.end());
	}
	inline std::string getAlgorithmName(void) { return "mmsSort"; }
	inline bool isStable(void) { return true; }
};


int main()
{
	MmSortBenchmark sortBenchmark;
	sortBenchmark.benchmark(ARRAY_SIZE, ARRAY_TYPE, SORT_KEY_MODE, TIMES);

	return 0;
}

