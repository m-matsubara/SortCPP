/*
* SortBenchmark.h
*
*
* http://www.mmatsubara.com/developer/sortCpp/
*
* Copyright (c) 2017 matsubara masakazu
* Released under the MIT license
* https://github.com/m-matsubara/sortCpp/blob/master/LICENSE.txt
*/

#pragma once

#include "SortItem.h"
#include "SortBenchmarkSpec.h"


class SortBenchmark {
public:
	virtual void sort(std::vector<SortItem> &array) = 0;
	virtual std::string getAlgorithmName(void) = 0;
	virtual bool isStable(void) = 0;

	void benchmark(size_t arraySize, int arrayType, sort_key_type keyType, size_t times);
};