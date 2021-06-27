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

class MmsSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::mmsSort(array.begin(), array.end());
	}
	inline std::string getAlgorithmName(void) { return "mmsSort"; }
	inline bool isStable(void) { return true; }
};


int main(int argc, char *argv[])
{
	MmsSortBenchmark sortBenchmark;
	sortBenchmark.main(argc, argv);
	return 0;
}

