#pragma once
/*
* MergeSort.h
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
	template <class RAI, class OI, class PR> void _mergeSort(RAI from, RAI to, OI work, PR pred) {
		const size_t range = std::distance(from, to);
		//	ソート対象配列サイズが一定数未満のときは特別扱い
		if (range < 10) {
			insertionSort(from, to, pred);
			return;
		}

		// 半分ずつソート
		const RAI half = from + (range >> 1);
		_mergeSort(from, half, work, pred);
		_mergeSort(half, to,   work, pred);

		// 各レーンをマージ
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

		//size_t workSize = sizeof(RAIv) * (range >> 1);
		//RAIv* work = (RAIv*)malloc(workSize);

		std::vector<RAIv> work;
		work.resize(range >> 1);

		_mergeSort(first, to, work.begin(), pred);

		//free(work);
	}

	/*
	* MergeSort
	*/
	template <class RAI> inline void mergeSort(RAI first, RAI last) // cmpを省略した時に呼び出す。
	{
		mergeSort(first, last, std::less<>());
	}
}
