#pragma once
/*
* MergeSortNR.h
*
* [TEST TYPE] Merge sort (non-recursive)
* For testing for the following purposes
*   * Comparison with other algorithms
*   * Comparison with recursive merge sort
*
* Since it is an implementation for comparison purposes, it has not been over-optimized.
*
* Copyright (c) 2019 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <vector>

#include "InsertionSort.h"

namespace mmlib {

	/*
	* merge
	* internal function
	*/
	template <class RAI, class RAIv, class PR> void _merge(RAI from, RAI half, RAI to, std::vector<RAIv>& work, PR pred) {
		size_t halfRange = half - from;
#if 1	
		if (pred(*(half - 1), *half))
			return;		// merged
#endif

		auto pos = from;
		auto posW = work.begin();
		size_t idx = 0;
		size_t size = work.size();
		while (pos < half) {
			if (idx < size)
				posW[idx++] = std::move(*pos++);
			else
				work.push_back(std::move(*pos++));
		}

		auto pos1 = work.begin();
		auto pos1to = pos1 + halfRange;
		auto pos2 = half;
		auto pos2to = to;

		auto posOut = from;

		for (;;) {
			if (pred(*pos2, *pos1) == false) {
				// *pos1 <= *pos2
				*posOut++ = std::move(*pos1++);
				if (pos1 >= pos1to) {
					//std::move(pos2, pos2to, posOut);	// Unnecessary
					return;
				}
			}
			else {
				// *pos1 > *pos2
				*posOut++ = std::move(*pos2++);
				if (pos2 >= pos2to) {
					std::move(pos1, pos1to, posOut);
					return;
				}
			}
		}
	}


	/*
	* MergeSort (No recursive)
	* internal function
	*/
	template <class RAI, class RAIv, class PR> void _mergeSortNR(RAI from, RAI to, std::vector<RAIv>& work, PR pred) {
		const size_t range = std::distance(from, to);
		//	First, insertSort in run size units
		size_t run = 10;
		RAI pos = from;
		for (RAI pos2 = pos + run; pos2 < to; pos = pos2, pos2 += run) {
			insertionSort(pos, pos2, pred);
		}
		insertionSort(pos, to, pred);

		// Merge while doubling run size
		while (run < range) {
			size_t halfSize = run;
			run <<= 1;
			RAI pos1 = from;
			RAI pos2 = from + run;
			for (; pos2 < to; pos1 = pos2, pos2 += run) {
				_merge(pos1, pos1 + halfSize, pos2, work, pred);
			}
			if (pos1 + halfSize < to) {
				_merge(pos1, pos1 + halfSize, to, work, pred);
			}
		}
	}

	/*
	* MergeSort (No recursive)
	*/
	template <class RAI, class PR> void mergeSortNR(RAI first, RAI to, PR pred) {
		size_t range = std::distance(first, to);
		if (range <= 32) {
			insertionSort(first, to, pred);
			return;
		}

		typedef typename std::iterator_traits<RAI>::value_type RAIv;

		std::vector<RAIv> work;
		work.reserve(range);

		_mergeSortNR(first, to, work, pred);
	}

	/*
	* MergeSort (No recursive)
	*/
	template <class RAI> inline void mergeSortNR(RAI first, RAI last)
	{
		mergeSortNR(first, last, std::less<>());
	}
}
