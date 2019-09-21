﻿/*
* Mas4Sort.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include "Mas4Sort.h"

#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class MmSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::mas4Sort(array.begin(), array.end());
		//SortItem *begin = &*(array.begin());
		//SortItem *end   = &*(array.end());
		//mmlib::mas4Sort(begin, end);
	}
	inline std::string getAlgorithmName(void) { return "mas4Sort"; }
	inline bool isStable(void) { return true; }
};


int main()
{
	MmSortBenchmark sortBenchmark;
	sortBenchmark.benchmark(ARRAY_SIZE, ARRAY_TYPE, SORT_KEY_MODE, TIMES);

	return 0;
}

