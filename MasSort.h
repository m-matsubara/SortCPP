#pragma once
/*
* MasSort.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <vector>

#include "InsertionSort.h"

template <class RAI> inline static void MoveData(RAI Dest, RAI Src, size_t sztCount)
{
	for (size_t idx = 0; idx < sztCount; idx++) {
		*Dest++ = std::move(*Src);
		std::advance(Src, 1);
	}
}


template <class RAI, class PR> void masMerge(RAI pos1, RAI pos2, RAI pos3, RAI to, RAI works, PR pred) {
	int state;
	if (pred(*pos2, *pos1) == false) {		// pos1 <= pos2
		// array[p1] <= array[p2]
		if (pred(*pos3, *pos2) == false) {	// pos2 <= pos3
			// array[p1] <= array[p2] <= array[p3]
			state = 0x123;
		}
		else if (pred(*pos3, *pos1) == false) {		// pos1 <= pos3
			// array[p1] <= array[p3] <= array[p2]
			state = 0x132;
		}
		else {
			// array[p3] < array[p1] <= array[p2]
			state = 0x312;
		}
	}
	else {
		// array[p2] < array[p1]
		if (pred(*pos3, *pos1) == false) {			// pos1 <= pos3
			// array[p2] < array[p1] <= array[p3]
			state = 0x213;
		}
		else if (pred(*pos3, *pos2) == false) {		// pos2 <= pos3
			// array[p2] <= array[p3] < array[p1]
			state = 0x231;
		}
		else {
			// array[p3] < array[p2] < array[p1]
			state = 0x321;
		}
	}

	//System.arraycopy(array, pos1, works, 0, pos3 - pos1);
	//masCopy(pos1, works, pos3 - pos1);
	MoveData(works, pos1, pos3 - pos1);
	size_t gap = pos2 - pos1;
	RAI outi = pos1;
	pos1 = works;
	RAI p1to = pos1 + gap;
	pos2 = p1to;
	RAI p2to = p1to + gap;
	RAI p3to = to;

	for (; outi < to; outi++) {
		// 以下のif文のネストは、本来なら switch case で処理するべきだが、if のネストのほうが速かったので、このような書き方にしている。
		if (state < 0x200) {
			// 0-1
			//CopyData(idx, pos1++, 1);
			*outi = std::move(*pos1);
			advance(pos1, 1);
			if (state == 0x123) {	// 0 0x123
				if (pos1 >= p1to) {
					state = 0x23;
					break;
				}
				else if (pred(*pos2, *pos1) == false)	// pos1 <= pos2
					; // モード変更なし
				else if (pred(*pos3, *pos1) == false)		// pos1 <= pos3
					state = 0x213;
				else
					state = 0x231;
			}
			else { 				// 1 0x132
				if (pos1 >= p1to) {
					state = 0x32;
					break;
				}
				else if (pred(*pos3, *pos1) == false)		// pos1 <= pos3
					; // モード変更なし
				else if (pred(*pos2, *pos1) == false)		// pos1 <= pos2
					state = 0x312;
				else
					state = 0x321;
			}
		}
		else if (state < 0x300) {
			// 2-3
			*outi = std::move(*pos2);
			advance(pos2, 1);
			if (state == 0x213) {	// 2 0x213
				if (pos2 >= p2to) {
					state = 0x13;
					break;
				}
				else if (pred(*pos2, *pos1))				//	pos2 < pos1
					; // モード変更なし
				else if (pred(*pos3, *pos2) == false)		//	pos2 <= pos3
					state = 0x123;
				else
					state = 0x132;
			}
			else { // 0x231	// 3 0x231
				if (pos2 >= p2to) {
					state = 0x31;
					break;
				}
				else if (pred(*pos3, *pos2) == false)		// pos2 <= pos3
					; // モード変更なし
				else if (pred(*pos2, *pos1))				// pos2 < pos1
					state = 0x321;
				else
					state = 0x312;
			}
		}
		else {
			// 4-5
			*outi = std::move(*pos3);
			advance(pos3, 1);
			if (state == 0x312) {	// 4 0x312
				if (pos3 >= p3to) {
					state = 0x12;
					break;
				}
				else if (pred(*pos3, *pos1))	//	pos3 < pos1
					; // モード変更なし
				else if (pred(*pos3, *pos2))	//	pos3 < pos2
					state = 0x132;
				else
					state = 0x123;
			}
			else { 				// 5 0x321
				if (pos3 >= p3to) {
					state = 0x21;
					break;
				}
				else if (pred(*pos3, *pos2))	// pos3 < pos2
					; // モード変更なし
				else if (pred(*pos3, *pos1))	// pos3 < pos1
					state = 0x231;
				else
					state = 0x213;
			}
		}
	}
	advance(outi, 1);

	for (; outi < to; advance(outi, 1)) {
		// 以下のif文のネストは、本来なら switch case で処理するべきだが、if のネストのほうが速かったので、このような書き方にしている。
		if (state < 0x21) {
			*outi = std::move(*pos1);
			advance(pos1, 1);
			if (state == 0x12) {	// 6 0x12
				if (pos1 >= p1to) {
					state = 0x2;
					break;
				}
				else if (pred(*pos2, *pos1) == false)	// pos1 <= pos2
					; // モード変更なし
				else
					state = 0x21;
			}
			else { 				// 7 0x13
				if (pos1 >= p1to) {
					state = 0x3;
					break;
				}
				else if (pred(*pos3, *pos1) == false)		// pos1 <= pos3
					; // モード変更なし
				else
					state = 0x31;
			}
		}
		else if (state < 0x31) {
			*outi = std::move(*pos2);
			advance(pos2, 1);
			if (state == 0x21) {	// 8 0x21
				if (pos2 >= p2to) {
					state = 0x1;
					break;
				}
				else if (pred(*pos2, *pos1))	// pos2 < pos1
					; // モード変更なし
				else
					state = 0x12;
			}
			else { 				// 9 0x23
				if (pos2 >= p2to) {
					state = 0x3;
					break;
				}
				else if (pred(*pos3, *pos2) == false)		// pos2 <= pos3
					; // モード変更なし
				else
					state = 0x32;
			}
		}
		else {
			*outi = std::move(*pos3);
			advance(pos3, 1);
			if (state == 0x31) {	// 10 0x31
				if (pos3 >= p3to) {
					state = 0x1;
					break;
				}
				else if (pred(*pos3, *pos1))		// pos3 < pos1
					; // モード変更なし
				else
					state = 0x13;
			}
			else { 				// 11 0x32
				if (pos3 >= p3to) {
					state = 0x2;
					break;
				}
				else if (pred(*pos3, *pos2))		// pos3 < pos2
					; // モード変更なし
				else
					state = 0x23;
			}
		}
	}
	advance(outi, 1);

	if (state == 0x1) {
		//System.arraycopy(workArray, pos1, array, idx, p1to - pos1);
		//masCopy(pos1, idx, p1to - pos1);
		MoveData(outi, pos1, p1to - pos1);
	}
	else if (state == 0x2) {
		//System.arraycopy(workArray, pos2, array, idx, p2to - pos2);
		//masCopy(pos2, idx, p2to - pos2);
		MoveData(outi, pos2, p2to - pos2);
	}
}

template <class RAI, class PR> void masSort(RAI from, RAI to, RAI works, PR pred) {
	size_t range = to - from;

	//	ソート対象配列サイズが一定数未満のときは特別扱い
	if (range < 10) {
		insertionSort(from, to, pred);
		return;
	}

	size_t gap = range / 3;
	RAI pos1 = from;
	RAI pos2 = pos1 + gap;
	RAI pos3 = pos2 + gap;
	masSort(pos3, to, works, pred);
	masSort(pos2, pos3, works, pred);
	masSort(from, pos2, works, pred);

	// ソート済み配列の場合の高速化
	if (pred(*pos2, *(pos2 - 1)) == false && pred(*pos3, *(pos3 - 1)) == false)
		return;

	masMerge(pos1, pos2, pos3, to, works, pred);
}



template <class RAI, class PR> void masSort(RAI from, RAI to, PR pred) {
	size_t range = (to - from);
	typedef typename std::iterator_traits<RAI>::value_type RAIv;
	std::vector<RAIv> workVector(range / 3 * 2);

	masSort(from, to, workVector.begin(), pred);
}

template <class RAI>
inline void masSort(RAI from, RAI to) // cmpを省略した時に呼び出す。
{
	masSort(from, to, std::less<>());
}
