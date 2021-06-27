/*
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

class Mas4SortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmlib::mas4Sort(array.begin(), array.end());
		//SortItem *begin = &*(array.begin());
		//SortItem *end   = &*(array.end());
		//mmlib::mas4Sort(begin, end);
	}
	inline std::string getAlgorithmName(void) { return "mas4Sort"; }
	inline bool isStable(void) { return true; }
};


int main(int argc, char *argv[])
{
	Mas4SortBenchmark sortBenchmark;
	sortBenchmark.main(argc, argv);
	return 0;
}

