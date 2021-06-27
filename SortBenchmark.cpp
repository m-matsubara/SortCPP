/*
* SortBenchmark.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
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

void  SortBenchmark::initializeArray(std::vector<SortItem> &array, ArrayType arrayType)
{
	size_t arraySize = array.end() - array.begin();
	std::mt19937 rnd;

	if (arrayType == ArrayType::ARRAY_TYPE_RANDOM) {
		for (size_t idx = 0; idx < arraySize; idx++) {
			array[idx].key = (int)(idx / 10);
		}

		std::uniform_int_distribution<> randArraySize(0, (int)arraySize - 1);
		for (size_t idx = 0; idx < arraySize; idx++) {
			int swapIdx = randArraySize(rnd);

			auto work = array[idx].key;
			array[idx].key = array[swapIdx].key;
			array[swapIdx].key = work;
		}
	} else if (arrayType == ArrayType::ARRAY_TYPE_UNIQUE_RANDOM) {
		for (size_t idx = 0; idx < arraySize; idx++) {
			array[idx].key = (int)idx;
		}

		std::uniform_int_distribution<> randArraySize(0, (int)arraySize - 1);
		for (size_t idx = 0; idx < arraySize; idx++) {
			int swapIdx = randArraySize(rnd);

			auto work = array[idx].key;
			array[idx].key = array[swapIdx].key;
			array[swapIdx].key = work;
		}
	} else if (arrayType == ArrayType::ARRAY_TYPE_HALF_SORTED) {
		for (size_t idx = 0; idx < arraySize; idx++) {
			array[idx].key = (int)idx;
		}

		size_t randomRange = arraySize / 2;
		std::uniform_int_distribution<> randArraySize(0, (int)randomRange - 1);
		for (size_t idx = 0; idx < randomRange; idx++) {
			int swapIdx = randArraySize(rnd);

			auto work = array[idx].key;
			array[idx].key = array[swapIdx].key;
			array[swapIdx].key = work;
		}
	} else if (arrayType == ArrayType::ARRAY_TYPE_ASC) {
		for (size_t idx = 0; idx < arraySize; idx++) {
			array[idx].key = (int)idx;
		}
	} else if (arrayType == ArrayType::ARRAY_TYPE_DESC) {
		for (size_t idx = 0; idx < arraySize; idx++) {
			array[idx].key = (int)(arraySize - idx);
		}
	} else if (arrayType == ArrayType::ARRAY_TYPE_FLAT) {
		for (size_t idx = 0; idx < arraySize; idx++) {
			array[idx].key = 0;
		}
	}
}


void SortBenchmark::benchmark(size_t arraySize, ArrayType arrayType, SortKeyType keyType, size_t times)
{
	using namespace std;
	using std::cout;
	using std::endl;
	using std::cin;

	std::vector<SortItem> vecSortItem(arraySize);

	try {
		for (size_t timeIdx = 1; timeIdx <= times; timeIdx++) {
			initializeArray(vecSortItem, arrayType);

			string sortKeyTypeStr = "Integer";
			if (keyType == SortKeyType::STRING) {
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
			auto startTime = std::chrono::system_clock::now();      // 計測開始時刻を保存

			sort(vecSortItem);

			auto endTime = std::chrono::system_clock::now();      // 計測終了時刻を保存
			auto dur = endTime - startTime;        // 要した時間を計算
			auto microSec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();

			std::string stableStr = isStable() ? "stable" : "unstable";
			std::string arrayTypeStr = "";
			if (arrayType == ArrayType::ARRAY_TYPE_RANDOM) {
				arrayTypeStr = "Random";
			} else if (arrayType == ArrayType::ARRAY_TYPE_UNIQUE_RANDOM) {
				arrayTypeStr = "Unique random";
			} else if (arrayType == ArrayType::ARRAY_TYPE_HALF_SORTED) {
				arrayTypeStr = "Half sorted";
			} else if (arrayType == ArrayType::ARRAY_TYPE_ASC) {
				arrayTypeStr = "Ascending";
			} else if (arrayType == ArrayType::ARRAY_TYPE_DESC) {
				arrayTypeStr = "Descending";
			} else if (arrayType == ArrayType::ARRAY_TYPE_FLAT) {
				arrayTypeStr = "Flat";
			}

#ifdef CUSTOM_CONSTRUCTOR
			cout << "C++" << "\t" << timeIdx << "\t" << getAlgorithmName() << "\t" << arrayTypeStr << "\t" << sortKeyTypeStr << "\t" << arraySize << "\t" << microSec / 1000000.0 << "\t" << SortItem::compareCount << "\t" << stableStr 
				<< "\t" << SortItem::constructorCount
				<< "\t" << SortItem::moveConstructorCount + SortItem::moveOperatorCount << "\t" << SortItem::moveConstructorCount << "\t" << SortItem::moveOperatorCount
				<< "\t" << SortItem::copyConstructorCount + SortItem::copyOperatorCount << "\t" << SortItem::copyConstructorCount << "\t" << SortItem::copyOperatorCount
				<< endl;
#else
			cout << "C++" << "\t" << timeIdx << "\t" << getAlgorithmName() << "\t" << arrayTypeStr << "\t" << sortKeyTypeStr << "\t" << arraySize << "\t" << microSec / 1000000.0 << "\t" << SortItem::compareCount << "\t" << stableStr 
				<< endl;
#endif
			//validateVector(vecSortItem.begin(), vecSortItem.end());
			validateVector(vecSortItem, isStable());
		}
	}
	catch (std::string e) {
		std::cout << e << std::endl;
	}
}

int SortBenchmark::main(int argc, char *argv[])
{
	size_t arraySize = ARRAY_SIZE;
	ArrayType arrayType = ARRAY_TYPE;
	SortKeyType sortKeyType = SORT_KEY_TYPE;
	size_t times = TIMES;
	if (argc >= 2 && *argv[1]) {
		arraySize = atoi(argv[1]);
	}
	if (argc >= 3 && *argv[2]) {
		if (argv[2][0] == 'U') {
			arrayType = ArrayType::ARRAY_TYPE_UNIQUE_RANDOM;
		} else if (argv[2][0] == 'R') {
			arrayType = ArrayType::ARRAY_TYPE_RANDOM;
		} else if (argv[2][0] == 'H') {
			arrayType = ArrayType::ARRAY_TYPE_HALF_SORTED;
		} else if (argv[2][0] == 'A') {
			arrayType = ArrayType::ARRAY_TYPE_ASC;
		} else if (argv[2][0] == 'D') {
			arrayType = ArrayType::ARRAY_TYPE_DESC;
		} else if (argv[2][0] == 'F') {
			arrayType = ArrayType::ARRAY_TYPE_DESC;
		}
	}
	if (argc >= 4 && *argv[3]) {
		if (argv[3][0] == 'I') {
			sortKeyType = SortKeyType::INTEGER;
		} else if (argv[3][0] == 'S') {
			sortKeyType = SortKeyType::STRING;
		}
	}
	if (argc >= 5 && *argv[4]) {
		times = atoi(argv[4]);
	}
	benchmark(arraySize, arrayType, sortKeyType, times);

	return 0;
}
