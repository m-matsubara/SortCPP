#pragma once
/*
* Mas4Sort3rd.h
*
* Mas4Sort 3rd Generation implements.
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <vector>

#include "InsertionSort.h"

namespace mmlib {

	/*
	* 4-way merge
	* internal function
	*/
	template <class RAI, class OI, class PR> void _mas4Merge(RAI pos1, RAI pos2, RAI pos3, RAI pos4, RAI pos5, OI posOut, PR pred) {

		RAI top1, top2, top3, top4;
		RAI end1, end2, end3, end4;

		// state 変数の初期状態決定
		if (pred(*pos2, *pos1) == false) {						// *pos1 <= *pos2
			// array[p1] <= array[p2]
			if (pred(*pos3, *pos2) == false) {					// *pos2 <= *pos3
																// array[p1] <= array[p2] <= array[p3]
				if (pred(*pos4, *pos2) == false) {				// *pos2 <= *pos4
					if (pred(*pos4, *pos3) == false) {			// *pos3 <= *pos4
						//state = 0x1234;
						top1 = pos1; end1 = pos2;
						top2 = pos2; end2 = pos3;
						top3 = pos3; end3 = pos4;
						top4 = pos4; end4 = pos5;
					}
					else {
						//state = 0x1243;
						top1 = pos1; end1 = pos2;
						top2 = pos2; end2 = pos3;
						top3 = pos4; end3 = pos5;
						top4 = pos3; end4 = pos4;
					}
				}
				else {
					if (pred(*pos4, *pos1) == false) {			// *pos1 <= *pos4
						//state = 0x1423;
						top1 = pos1; end1 = pos2;
						top2 = pos4; end2 = pos5;
						top3 = pos2; end3 = pos3;
						top4 = pos3; end4 = pos4;
					}
					else {
						//state = 0x4123;
						top1 = pos4; end1 = pos5;
						top2 = pos1; end2 = pos2;
						top3 = pos2; end3 = pos3;
						top4 = pos3; end4 = pos4;
					}
				}
			}
			else if (pred(*pos3, *pos1) == false) {			// *pos1 <= *pos3
				// array[p1] <= array[p3] <= array[p2]
				if (pred(*pos4, *pos3) == false) {				// *pos3 <= *pos4
					if (pred(*pos4, *pos2) == false) {			// *pos2 <= *pos4
						//state = 0x1324;
						top1 = pos1; end1 = pos2;
						top2 = pos3; end2 = pos4;
						top3 = pos2; end3 = pos3;
						top4 = pos4; end4 = pos5;
					}
					else {
						//state = 0x1342;
						top1 = pos1; end1 = pos2;
						top2 = pos3; end2 = pos4;
						top3 = pos4; end3 = pos5;
						top4 = pos2; end4 = pos3;
					}
				}
				else {
					if (pred(*pos4, *pos1) == false) {			// *pos1 <= *pos4
						//state = 0x1432;
						top1 = pos1; end1 = pos2;
						top2 = pos4; end2 = pos5;
						top3 = pos3; end3 = pos4;
						top4 = pos2; end4 = pos3;
					}
					else {
						//state = 0x4132;
						top1 = pos4; end1 = pos5;
						top2 = pos1; end2 = pos2;
						top3 = pos3; end3 = pos4;
						top4 = pos2; end4 = pos3;
					}
				}
			}
			else {
				// array[p3] < array[p1] <= array[p2]
				if (pred(*pos4, *pos1) == false) {				// *pos1 <= *pos4
					if (pred(*pos4, *pos2) == false) {			// *pos2 <= *pos4
						//state = 0x3124;
						top1 = pos3; end1 = pos4;
						top2 = pos1; end2 = pos2;
						top3 = pos2; end3 = pos3;
						top4 = pos4; end4 = pos5;
					}
					else {
						//state = 0x3142;
						top1 = pos3; end1 = pos4;
						top2 = pos1; end2 = pos2;
						top3 = pos4; end3 = pos5;
						top4 = pos2; end4 = pos3;
					}
				}
				else {
					if (pred(*pos4, *pos3) == false) {			// *pos3 <= *pos4
						//state = 0x3412;
						top1 = pos3; end1 = pos4;
						top2 = pos4; end2 = pos5;
						top3 = pos1; end3 = pos2;
						top4 = pos2; end4 = pos3;
					}
					else {
						//state = 0x4312;
						top1 = pos4; end1 = pos5;
						top2 = pos3; end2 = pos4;
						top3 = pos1; end3 = pos2;
						top4 = pos2; end4 = pos3;
					}
				}
			}
		}
		else {
			// array[p2] < array[p1]
			if (pred(*pos3, *pos1) == false) {					// *pos1 <= *pos3
																// array[p2] < array[p1] <= array[p3]
				if (pred(*pos4, *pos1) == false) {				// *pos1 <= *pos4
					if (pred(*pos4, *pos3) == false) {			// *pos3 <= *pos4
						//state = 0x2134;
						top1 = pos2; end1 = pos3;
						top2 = pos1; end2 = pos2;
						top3 = pos3; end3 = pos4;
						top4 = pos4; end4 = pos5;
					}
					else {
						//state = 0x2143;
						top1 = pos2; end1 = pos3;
						top2 = pos1; end2 = pos2;
						top3 = pos4; end3 = pos5;
						top4 = pos3; end4 = pos4;
					}
				}
				else {
					if (pred(*pos4, *pos2) == false) {			// *pos2 <= *pos4
						//state = 0x2413;
						top1 = pos2; end1 = pos3;
						top2 = pos4; end2 = pos5;
						top3 = pos1; end3 = pos2;
						top4 = pos3; end4 = pos4;
					}
					else {
						//state = 0x4213;
						top1 = pos4; end1 = pos5;
						top2 = pos2; end2 = pos3;
						top3 = pos1; end3 = pos2;
						top4 = pos3; end4 = pos4;
					}
				}
			}
			else if (pred(*pos3, *pos2) == false) {			// *pos2 <= *pos3
				// array[p2] <= array[p3] < array[p1]
				if (pred(*pos4, *pos3) == false) {				// *pos3 <= *pos4
					if (pred(*pos4, *pos1) == false) {			// *pos1 <= *pos4
						//state = 0x2314;
						top1 = pos2; end1 = pos3;
						top2 = pos3; end2 = pos4;
						top3 = pos1; end3 = pos2;
						top4 = pos4; end4 = pos5;
					}
					else {
						//state = 0x2341;
						top1 = pos2; end1 = pos3;
						top2 = pos3; end2 = pos4;
						top3 = pos4; end3 = pos5;
						top4 = pos1; end4 = pos2;
					}
				}
				else {
					if (pred(*pos4, *pos2) == false) {			// *pos2 <= *pos4
						//state = 0x2431;
						top1 = pos2; end1 = pos3;
						top2 = pos4; end2 = pos5;
						top3 = pos3; end3 = pos4;
						top4 = pos1; end4 = pos2;
					}
					else {
						//state = 0x4231;
						top1 = pos4; end1 = pos5;
						top2 = pos2; end2 = pos3;
						top3 = pos3; end3 = pos4;
						top4 = pos1; end4 = pos2;
					}
				}
			}
			else {
				// array[p3] < array[p2] < array[p1]
				if (pred(*pos4, *pos2) == false) {				// *pos2 <= *pos4
					if (pred(*pos4, *pos1) == false) {			// *pos1 <= *pos4
						//state = 0x3214;
						top1 = pos3; end1 = pos4;
						top2 = pos2; end2 = pos3;
						top3 = pos1; end3 = pos2;
						top4 = pos4; end4 = pos5;
					}
					else {
						//state = 0x3241;
						top1 = pos3; end1 = pos4;
						top2 = pos2; end2 = pos3;
						top3 = pos4; end3 = pos5;
						top4 = pos1; end4 = pos2;
					}
				}
				else {
					if (pred(*pos4, *pos3) == false) {			// *pos3 <= *pos4
						//state = 0x3421;
						top1 = pos3; end1 = pos4;
						top2 = pos4; end2 = pos5;
						top3 = pos2; end3 = pos3;
						top4 = pos1; end4 = pos2;
					}
					else {
						//state = 0x4321;
						top1 = pos4; end1 = pos5;
						top2 = pos3; end2 = pos4;
						top3 = pos2; end3 = pos3;
						top4 = pos1; end4 = pos2;
					}
				}
			}
		}

		for (;; advance(posOut, 1)) {
			*posOut = std::move(*top1);
			advance(top1, 1);
			// レーン１が終了したら「４レーンのループ」を抜けて「３レーンのループ」へ
			if (top1 >= end1) {
				top1 = top2; end1 = end2;
				top2 = top3; end2 = end3;
				top3 = top4; end3 = end4;
				advance(posOut, 1);
				break;
			}
			if (top1 < top3 ? pred(*top3, *top1) == false : pred(*top1, *top3)) {		// *pos1 <= *pos3
				if (top1 < top2 ? pred(*top2, *top1) == false : pred(*top1, *top2)) {	// *pos1 <= *pos2
				}
				else {
					//state = 0x2134;
					auto topW = top1, endW = end1;
					top1 = top2; end1 = end2;
					top2 = topW; end2 = endW;
				}
			}
			else {
				if (top1 < top4 ? pred(*top4, *top1) == false : pred(*top1, *top4)) {		// *pos1 <= *pos4
					//state = 0x2314;
					auto topW = top1, endW = end1;
					top1 = top2; end1 = end2;
					top2 = top3; end2 = end3;
					top3 = topW; end3 = endW;
				}
				else {
					//state = 0x2341;
					auto topW = top1, endW = end1;
					top1 = top2; end1 = end2;
					top2 = top3; end2 = end3;
					top3 = top4; end3 = end4;
					top4 = topW; end4 = endW;
				}
			}
		}

		for (;; advance(posOut, 1)) {
			*posOut = std::move(*top1);
			advance(top1, 1);
			// レーン１が終了したら「３レーンのループ」を抜けて「２レーンのループ」へ
			if (top1 >= end1) {
				top1 = top2; end1 = end2;
				top2 = top3; end2 = end3;
				advance(posOut, 1);
				break;
			}
			if (top1 < top2 ? pred(*top2, *top1) == false : pred(*top1, *top2)) {		// *pos1 <= *pos2
			}
			else {
				if (top1 < top3 ? pred(*top3, *top1) == false : pred(*top1, *top3)) {		// *pos1 <= *pos3
					//state = 0x213;
					auto topW = top1, endW = end1;
					top1 = top2; end1 = end2;
					top2 = topW; end2 = endW;
				}
				else {
					//state = 0x231;
					auto topW = top1, endW = end1;
					top1 = top2; end1 = end2;
					top2 = top3; end2 = end3;
					top3 = topW; end3 = endW;
				}
			}
		}

		for (;; advance(posOut, 1)) {
			*posOut = std::move(*top1);
			advance(top1, 1);
			// レーン１が終了したら「２レーンのループ」終了…残処理へ
			if (top1 >= end1) {
				top1 = top2; end1 = end2;
				advance(posOut, 1);
				break;
			}
			if (top1 < top2 ? pred(*top2, *top1) == false : pred(*top1, *top2)) {		// *pos1 <= *pos2
			}
			else {
				//state = 0x21;
				auto topW = top1, endW = end1;
				top1 = top2; end1 = end2;
				top2 = topW; end2 = endW;
			}
		}
		
		// 残ったワーク領域の各レーンを出力先に格納する
		std::move(top1, end1, posOut);
	}


	/*
	* mas4sort (4-way merge sort)
	* internal function
	*/
	template <class RAI, class OI, class PR> void _mas4Sort(RAI from, RAI to, OI out, PR pred, bool sourceIsEnable) {
		const size_t range = std::distance(from, to);
		//	ソート対象配列サイズが一定数未満のときは特別扱い
		if (range < 10) {
			if (sourceIsEnable)
				std::move(from, to, out);

			insertionSort(out, out + range, pred);
			return;
		}

		// ソート範囲を４つの区間（レーン）に分割
		const size_t gap = range / 4;
		const RAI pos1 = from;
		const RAI pos2 = pos1 + gap;
		const RAI pos3 = pos2 + gap;
		const RAI pos4 = pos3 + gap;

		const OI opos1 = out;
		const OI opos2 = opos1 + gap;
		const OI opos3 = opos2 + gap;
		const OI opos4 = opos3 + gap;
		const OI outto = out + range;

		// 各レーンをソート
		_mas4Sort(opos1, opos2, pos1, pred, !sourceIsEnable);
		_mas4Sort(opos2, opos3, pos2, pred, !sourceIsEnable);
		_mas4Sort(opos3, opos4, pos3, pred, !sourceIsEnable);
		_mas4Sort(opos4, outto, pos4, pred, !sourceIsEnable);

		// 各レーンをマージ
		_mas4Merge(pos1, pos2, pos3, pos4, to, out, pred);
	}

	/*
	* mas4sort (4-way merge sort)
	*/
	template <class RAI, class PR> void mas4Sort(RAI first, RAI to, PR pred) {
		size_t range = std::distance(first, to);
		if (range <= 32) {
			insertionSort(first, to, pred);
			return;
		}

		typedef typename std::iterator_traits<RAI>::value_type RAIv;
		std::vector<RAIv> workVector;
		workVector.reserve(range);
		for (RAI item = first; item < to; advance(item, 1)) {
			workVector.push_back(std::move(*item));
		}

		_mas4Sort(workVector.begin(), workVector.end(), first, pred, true);
	}

	/*
	* mas4sort (4-way merge sort)
	*/
	template <class RAI> inline void mas4Sort(RAI first, RAI last) // cmpを省略した時に呼び出す。
	{
		mas4Sort(first, last, std::less<>());
	}
}
