/*
* QuickSort.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include "QuickSort.h"

#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class QuickSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::quickSort(array.begin(), array.end());			//	Quicksort base, unstable
	}
	inline std::string getAlgorithmName(void) { return "QuickSort (median of three)"; }
	inline bool isStable(void) { return false; }
};


int main(int argc, char *argv[])
{
	QuickSortBenchmark sortBenchmark;
	sortBenchmark.main(argc, argv);
	return 0;
}

