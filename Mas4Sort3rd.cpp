/*
* Mas4Sort3rd.cpp
* Mas4Sort 3rd Generation implements
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include "Mas4Sort3rd.h"

#include <vector>
#include <string>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

class Mas4Sort3rdBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::mas4Sort(array.begin(), array.end());
	}
		inline std::string getAlgorithmName(void) { return "mas4Sort(3rd Gen.)"; }
	inline bool isStable(void) { return true; }
};


int main()
{
	Mas4Sort3rdBenchmark sortBenchmark;
	sortBenchmark.benchmark(ARRAY_SIZE, ARRAY_TYPE, SORT_KEY_MODE, TIMES);

	return 0;
}

