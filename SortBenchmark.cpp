/*
* SortBenchmark.cpp
*
*
* http://www.mmatsubara.com/developer/sortCpp/
*
* Copyright (c) 2017 matsubara masakazu
* Released under the MIT license
* https://github.com/m-matsubara/sortCpp/blob/master/LICENSE.txt
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#include "SortBenchmark.h"
#include "SortBenchmarkSpec.h"

static void validateVector(std::vector<SortItem> &vec, bool stable)
{
	unsigned long bkCompareCount = SortItem::compareCount;
	auto from = vec.begin();
	auto to = vec.end();
	size_t range = (to - from);

	if (stable) {
		for (size_t idx = 0; idx < range - 1; idx++) {
			if ((from[idx].key > from[idx + 1].key) || ((from[idx].key == from[idx + 1].key) && (from[idx].originalOrder > from[idx + 1].originalOrder))) {
				SortItem::compareCount = bkCompareCount;
				throw std::string("sort error.");
			}
		}
	}
	else {
		for (size_t idx = 0; idx < range - 1; idx++) {
			if (from[idx].key > from[idx + 1].key) {
				std::cout << from[idx].key << std::endl;
				std::cout << from[idx + 1].key << std::endl;

				SortItem::compareCount = bkCompareCount;
				throw std::string("sort error.");
			}
		}
	}

	unsigned __int64 sum = 0;
	for (size_t idx = 0; idx < range; idx++)
		sum += from[idx].originalOrder;
	size_t sum2 = (range - 1) * (range) / 2;

	if (sum2 != sum) {
		throw std::string("sort error. (summary)");
	}


	SortItem::compareCount = bkCompareCount;
}

void SortBenchmark::benchmark(size_t arraySize, int arrayType, sort_key_type keyType, size_t times)
{
	using namespace std;
	using std::cout;
	using std::endl;
	using std::cin;

	std::mt19937 rnd;
	std::vector<SortItem> vecSortItem(arraySize);

	try {
		for (size_t timeIdx = 1; timeIdx <= times; timeIdx++) {
			for (size_t idx = 0; idx < arraySize; idx++) {
				vecSortItem[idx].key = (int)(idx / 10);
			}

			std::uniform_int_distribution<> randArraySize(0, (int)arraySize - 1);
			for (size_t idx = 0; idx < arraySize; idx++) {
				int swapIdx = randArraySize(rnd);
				//				std::swap(vecSortItem[idx], vecSortItem[swapIdx]);

				auto work = vecSortItem[idx].key;
				vecSortItem[idx].key = vecSortItem[swapIdx].key;
				vecSortItem[swapIdx].key = work;
			}

			string sortKeyTypeStr = "Integer";
			if (keyType == skt_str) {
				SortItem::isStringKeyMode = true;
				sortKeyTypeStr = "String";
				for (size_t idx = 0; idx < arraySize; idx++) {
					ostringstream ostr;
					ostr << setfill('0') << setw(10) << vecSortItem[idx].key;
					vecSortItem[idx].keyString = ostr.str();
				}
			}

			for (size_t idx = 0; idx < arraySize; idx++) {
				vecSortItem[idx].originalOrder = (int)idx;
			}

			SortItem::compareCount = 0;
			SortItem::constructorCount = 0;
			SortItem::copyConstructorCount = 0;
			SortItem::moveConstructorCount = 0;
			SortItem::copyOperatorCount = 0;
			SortItem::moveOperatorCount = 0;
			auto startTime = std::chrono::system_clock::now();      // 計測スタート時刻を保存

			sort(vecSortItem);

			auto endTime = std::chrono::system_clock::now();      // 計測スタート時刻を保存
			auto dur = endTime - startTime;        // 要した時間を計算
			auto microSec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();

			std::string stable = isStable() ? "stable" : "unstable";

			cout << "C++" << "\t" << timeIdx << "\t" << getAlgorithmName() << "\t" << "Random" << "\t" << sortKeyTypeStr << "\t" << arraySize << "\t" << microSec / 1000000.0 << "\t" << SortItem::compareCount << "\t" << stable << endl;
#ifdef CUSTOM_CONSTRUCTOR
			cout << "DefC: \t" << SortItem::constructorCount << endl;
			cout << "Copy: \t" << SortItem::copyConstructorCount + SortItem::copyOperatorCount << "\t" << SortItem::copyConstructorCount << "\t" << SortItem::copyOperatorCount << endl;
			cout << "Move: \t" << SortItem::moveConstructorCount + SortItem::moveOperatorCount << "\t" << SortItem::moveConstructorCount << "\t" << SortItem::moveOperatorCount << endl;
#endif
			//validateVector(vecSortItem.begin(), vecSortItem.end());
			validateVector(vecSortItem, isStable());
		}
	}
	catch (std::string e) {
		std::cout << e << std::endl;
	}
}

