/*
* MergeSortNR.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include "MergeSortNR.h"

#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class MergeSortNrBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::mergeSortNR(array.begin(), array.end());
	}
		inline std::string getAlgorithmName(void) { return "MergeSort(No recursive)"; }
	inline bool isStable(void) { return true; }
};


int main(int argc, char *argv[])
{
	MergeSortNrBenchmark sortBenchmark;
	sortBenchmark.main(argc, argv);
	return 0;
}

