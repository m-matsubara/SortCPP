#include "stdafx.h"
#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"
#include "MMergeSort.h"

class MmSortBenchmark : public SortBenchmark {
	inline void sort(std::vector<SortItem> &array) {
		mmerge_sort(array.begin(), array.end());
	}
	inline std::string getAlgorithmName(void) { return "mmerge_sort"; }
	inline bool isStable(void) { return true; }
};


int main()
{
	MmSortBenchmark sortBenchmark;
	sortBenchmark.benchmark(ARRAY_SIZE, ARRAY_TYPE, SORT_KEY_MODE, TIMES);

	return 0;
}

