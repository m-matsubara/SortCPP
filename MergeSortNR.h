#pragma once
/*
* MergeSortNR.h
*
* [試験用] 非再起版マージソート
* 以下の目的の試験用
*   ・他のアルゴリズムとの比較
*   ・再帰版マージソートとの比較
*
* 比較目的の実装であることから過度な最適化は施していない。
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
			return;		// マージ済みと判断できるので処理を省略
#endif

		// 配列の前半をワーク(ベクター)に移動
		// （ベクターでインスタンス生成済みの分はイテレータとしてアクセスし、生成済みでない分はpush_back()にてアクセスする）
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

		auto pos1 = work.begin();		// 副配列１（前半）のイテレータ（ワーク配列）
		auto pos1to = pos1 + halfRange;	// 副配列１の終わり位置（この位置を含まない）
		auto pos2 = half;				// 副配列２（後半）のイテレータ
		auto pos2to = to;				// 副配列２の終わり位置（この位置を含まない）

		auto posOut = from;				// 出力位置

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
	* MergeSort (No recursive)
	* internal function
	*/
	template <class RAI, class RAIv, class PR> void _mergeSortNR(RAI from, RAI to, std::vector<RAIv>& work, PR pred) {
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
	template <class RAI> inline void mergeSortNR(RAI first, RAI last) // cmpを省略した時に呼び出す。
	{
		mergeSortNR(first, last, std::less<>());
	}
}
