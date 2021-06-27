/*
* StdSort.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <algorithm>
#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class StdSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		std::sort(array.begin(), array.end());
	}
	inline std::string getAlgorithmName(void) { return "std::sort"; }
	inline bool isStable(void) { return false; }
};


int main(int argc, char *argv[])
{
	StdSortBenchmark sortBenchmark;
	sortBenchmark.main(argc, argv);
	return 0;
}

