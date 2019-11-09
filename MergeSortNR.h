#pragma once
/*
* MergeSortNR.h
*
* [試験用] 非再起版マージソート
* 以下の目的の試験用
*   ・他のアルゴリズムとの比較
*   ・再帰版マージソートとの比較
*
* Copyright (c) 2017 masakazu matsubara
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
	template <class RAI, class OI, class PR> void _merge(RAI from, RAI half, RAI to, OI work, PR pred) {
		size_t halfRange = half - from;

		RAI pos = from;
		OI posWork = work;
		while (pos < half) {
			*posWork = std::move(*pos++);
			posWork++;
		}

		OI pos1 = work;
		OI pos1to = work + halfRange;
		RAI pos2 = half;
		RAI pos2to = to;

		RAI posOut = from;

		for (;;) {
			if (pred(*pos2, *pos1) == false) {
				*posOut = std::move(*pos1++);
				posOut++;
				if (pos1 >= pos1to) {
					std::move(pos2, pos2to, posOut);
					return;
				}
			}
			else {
				*posOut = std::move(*pos2++);
				posOut++;
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
	template <class RAI, class OI, class PR> void _mergeSortNR(RAI from, RAI to, OI work, PR pred) {
		const size_t range = std::distance(from, to);
		//	最初はrunサイズ単位でinsertionSortする。
		size_t run = 10;
		RAI pos = from;
		for (RAI pos2 = pos + run; pos2 < to; pos = pos2, pos2 += run) {
			insertionSort(pos, pos2, pred);
		}
		insertionSort(pos, to, pred);

		// runサイズを２倍にしながらマージしていく
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
	* MergeSort
	*/
	template <class RAI, class PR> void mergeSortNR(RAI first, RAI to, PR pred) {
		size_t range = std::distance(first, to);
		if (range <= 32) {
			insertionSort(first, to, pred);
			return;
		}

		typedef typename std::iterator_traits<RAI>::value_type RAIv;
		//size_t workSize = sizeof(RAIv) * (range >> 1);
		//RAIv* work = (RAIv*)malloc(workSize);

		std::vector<RAIv> work;
		work.resize(range);

		_mergeSortNR(first, to, work.begin(), pred);

		//free(work);
	}

	/*
	* MergeSort
	*/
	template <class RAI> inline void mergeSortNR(RAI first, RAI last) // cmpを省略した時に呼び出す。
	{
		mergeSortNR(first, last, std::less<>());
	}
}
