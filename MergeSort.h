#pragma once
/*
* MergeSort.h
*
* [TEST TYPE] Merge sort (recursive)
* For testing for the following purposes
*   * Comparison with other algorithms
*   * Comparison with non-recursive merge sort
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
	* MergeSort
	* internal function
	*/
	template <class RAI, class RAIv, class PR> void _mergeSort(RAI from, RAI to, std::vector<RAIv>& work, PR pred) {
		const size_t range = std::distance(from, to);
		// Special treatment when the size of the array to be sorted is less than a certain number
		if (range < 10) {
			insertionSort(from, to, pred);
			return;
		}

		const RAI half = from + (range >> 1);
		_mergeSort(from, half, work, pred);
		_mergeSort(half, to,   work, pred);

		_merge(from, half, to, work, pred);
	}

	/*
	* MergeSort
	*/
	template <class RAI, class PR> void mergeSort(RAI first, RAI to, PR pred) {
		size_t range = std::distance(first, to);
		if (range <= 32) {
			insertionSort(first, to, pred);
			return;
		}

		typedef typename std::iterator_traits<RAI>::value_type RAIv;

		std::vector<RAIv> work;
		work.reserve(range >> 1);

		_mergeSort(first, to, work, pred);
	}

	/*
	* MergeSort
	*/
	template <class RAI> inline void mergeSort(RAI first, RAI last) // cmpを省略した時に呼び出す。
	{
		mergeSort(first, last, std::less<>());
	}
}
