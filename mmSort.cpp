/*
* mmSort.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include "mmSort.h"

#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class MmSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::mmSort(array.begin(), array.end());			//	Quicksort base, unstable
	}
	inline std::string getAlgorithmName(void) { return "mmSort"; }
	inline bool isStable(void) { return false; }
};


int main(int argc, char *argv[])
{
	MmSortBenchmark sortBenchmark;
	sortBenchmark.main(argc, argv);
	return 0;
}

