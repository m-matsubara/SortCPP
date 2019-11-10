#pragma once
/*
* QuickSort.h
*
* [試験用] クイックソート
* 以下の目的の試験用
*   ・他のアルゴリズムとの比較
*
* Copyright (c) 2019 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <iostream>
#include "InsertionSort.h"

namespace mmlib {
	template <class RAI, class PR> void quickSort(RAI from, RAI to, PR pred)
	{
		typedef typename std::iterator_traits<RAI>::value_type RAIv;
		size_t range = to - from;		//	ソート範囲サイズ

		//	ソート対象配列サイズが一定数以下のときは特別扱い
		if (range < 20) {
			insertionSort(from, to, pred);
			return;
		}

		RAI v1 = from;
		RAI v2 = from + (range >> 1);
		RAI v3 = to - 1;

		//	３つのメディアン
		if (pred(*v2, *v1) == false) {	//	v1 <= v2
			if (pred(*v3, *v2) == false) {	//	v2 < v3
				// v1 <= v2 <= v3
				//array[p1] = v1;
				//array[p2] = v2;
				//array[p3] = v3;
			}
			else if (pred(*v3, *v1) == false) {	//	v1 <= v3
				// v1 <= v3 <= v2
				//array[p1] = v1;
				RAIv temp2 = std::move(*v2);
				*v2 = std::move(*v3);
				*v3 = std::move(temp2);
			}
			else {
				// v3 <= v1 <= v2
				RAIv temp1 = std::move(*v1);
				*v1 = std::move(*v3);
				*v3 = std::move(*v2);
				*v2 = std::move(temp1);
			}
		}
		else {
			if (pred(*v3, *v1) == false) {	// v1 <= v3
				// v2 <= v1 <= v3
				RAIv temp1 = std::move(*v1);
				*v1 = std::move(*v2);
				*v2 = std::move(temp1);
				//array[p3] = v3;
			}
			else if (pred(*v3, *v2) == false) {	//	v2 <= v3
				// v2 <= v3 <= v1
				RAIv temp1 = std::move(*v1);
				*v1 = std::move(*v2);
				*v2 = std::move(*v3);
				*v3 = std::move(temp1);
			}
			else {
				// v3 <= v2 <= v1
				RAIv temp1 = std::move(*v1);
				*v1 = std::move(*v3);
				*v3 = std::move(temp1);
			}
		}


		RAIv pivot = *v2;	//	ピボット値

		//	パーティション操作
		RAI curFrom = from;			//	min index / 現在処理中位置の小さい方の位置
		RAI curTo = to - 1;			//	max index / 現在処理中位置の大きい方の位置
		while (true) {
			if (pred(*curFrom, pivot))
				while (pred(*++curFrom, pivot));
			if (pred(pivot, *curTo))
				while (pred(pivot, *--curTo));
			if (curFrom >= curTo)
				break;
			std::swap(*curFrom++, *curTo--);
		};

		//	小さいパーティション・大きいパーティションそれぞれで再起
		quickSort(from, curTo + 1, pred);
		quickSort(curFrom, to, pred);
	}

	template <class RAI>
	inline void quickSort(RAI from, RAI to) // cmpを省略した時に呼び出す。
	{
		typedef typename std::iterator_traits<RAI>::value_type RAIv;
		quickSort(from, to, std::less<RAIv>());
	}
}