#pragma once
/*
* MergeSort.h
*
* [試験用] 再起版マージソート
* 以下の目的の試験用
*   ・他のアルゴリズムとの比較
*   ・非再帰版マージソートとの比較
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
	template <class RAI, class WV, class PR> void _merge(RAI from, RAI half, RAI to, WV &work, PR pred) {
		size_t halfRange = half - from;

		// 配列の前半をワーク(ベクター)に移動
		// （ベクターでインスタンス生成済みの分はイテレータとしてアクセスし、生成済みでない分はpush_back()にてアクセスする（ケチな高速化））
		RAI pos = from;
		RAI posW = work.begin();
		size_t idx = 0;
		size_t size = work.size();
		while (pos < half) {
			if (idx < size)
				posW[idx++] = std::move(*pos++);
			else
				work.push_back(std::move(*pos++));
		}

		RAI pos1 = work.begin();		// 副配列１（前半）のイテレータ（ワーク配列）
		RAI pos1to = pos1 + halfRange;	// 副配列１の終わり位置（この位置を含まない）
		RAI pos2 = half;				// 副配列２（後半）のイテレータ
		RAI pos2to = to;				// 副配列２の終わり位置（この位置を含まない）

		RAI posOut = from;				// 出力位置

		for (;;) {
			if (pred(*pos2, *pos1) == false) {
				// *pos1 <= pos2 のケース
				*posOut++ = std::move(*pos1++);
				if (pos1 >= pos1to) {
					// 残りの副配列２を移動して終了…要らない
					//std::move(pos2, pos2to, posOut);
					return;
				}
			}
			else {
				// *pos1 > pos2 のケース
				*posOut++ = std::move(*pos2++);
				if (pos2 >= pos2to) {
					// 残りの副配列１を移動して終了
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
	template <class RAI, class WV, class PR> void _mergeSort(RAI from, RAI to, WV &work, PR pred) {
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

		// 二つの副配列をマージ
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
