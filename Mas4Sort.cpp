/*
* Mas4Sort.cpp
*
*
* http://www.mmatsubara.com/developer/sortCpp/
*
* Copyright (c) 2017 matsubara masakazu
* Released under the MIT license
* https://github.com/m-matsubara/sortCpp/blob/master/LICENSE.txt
*/

#include "stdafx.h"
#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"
#include "Mas4Sort.h"

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

