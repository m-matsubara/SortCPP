﻿/*
* MasSort.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include "MasSort.h"

#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class MasSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		masSort(array.begin(), array.end());
	}
	inline std::string getAlgorithmName(void) { return "masSort"; }
	inline bool isStable(void) { return true; }
};


int main(int argc, char *argv[])
{
	MasSortBenchmark sortBenchmark;
	sortBenchmark.main(argc, argv);
	return 0;
}

