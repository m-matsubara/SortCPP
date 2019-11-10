#pragma once
/*
* SortBenchmark.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <vector>

#include "SortItem.h"
#include "SortBenchmarkSpec.h"


class SortBenchmark {
public:
	virtual void sort(std::vector<SortItem> &array) = 0;
	virtual std::string getAlgorithmName(void) = 0;
	virtual bool isStable(void) = 0;

	void benchmark(size_t arraySize, int arrayType, SortKeyType keyType, size_t times);
};