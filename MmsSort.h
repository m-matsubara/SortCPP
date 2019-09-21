#pragma once
/*
* MmsSort.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <vector>

#include "InsertionSort.h"
#include "BinInsertionSort.h"

template <class RAI, class PR> void mmsSort(RAI from, RAI to, RAI works, PR pred)
{
	typedef typename std::iterator_traits<RAI>::value_type BIv;

	size_t range = to - from;
	if (range < 10) {
		insertionSort(from, to, pred);
		return;
	}

	BIv pivot1;
	BIv pivot2;
	if (range >= 150) {
		// ピボット候補値の添え字の差分
		size_t gap = range / 12;
		// ピボット候補値の添え字
		RAI center = from + (range >> 1);
		RAI p3 = center - gap;
		RAI p2 = p3 - gap;
		RAI p1 = p2 - gap;
		RAI p0 = p1 - gap;
		RAI p4 = center + gap;
		RAI p5 = p4 + gap;
		RAI p6 = p5 + gap;
		RAI p7 = p6 + gap;
		works[0] = *p0;
		works[1] = *p1;
		works[2] = *p2;
		works[3] = *p3;
		works[4] = *p4;
		works[5] = *p5;
		works[6] = *p6;
		works[7] = *p7;
		//CopyData(&(*(works + 0)), &(*p0));
		//CopyData(&(*(works + 1)), &(*p1));
		//CopyData(&(*(works + 2)), &(*p2));
		//CopyData(&(*(works + 3)), &(*p3));
		//CopyData(&(*(works + 4)), &(*p4));
		//CopyData(&(*(works + 5)), &(*p5));
		//CopyData(&(*(works + 6)), &(*p6));
		//CopyData(&(*(works + 7)), &(*p7));
		binInsertionSort(works, works + 8, pred);

		pivot1 = works[2];
		pivot2 = works[5];
		//CopyData(&pivot1, &(*(works + 2)));
		//CopyData(&pivot2, &(*(works + 5)));
	}
	else {
		// ピボット候補値の添え字の差分
		size_t gap = range / 6;
		// ピボット候補値の添え字
		RAI p2 = from + (range >> 1);
		RAI p3 = p2 + gap;
		RAI p4 = p3 + gap;
		RAI p1 = p2 - gap;
		RAI p0 = p1 - gap;
		works[0] = *p0;
		works[1] = *p1;
		works[2] = *p2;
		works[3] = *p3;
		works[4] = *p4;
		//CopyData(&(*(works + 0)), &(*p0));
		//CopyData(&(*(works + 1)), &(*p1));
		//CopyData(&(*(works + 2)), &(*p2));
		//CopyData(&(*(works + 3)), &(*p3));
		binInsertionSort(works, works + 5, pred);

		pivot1 = works[1];
		pivot2 = works[3];
		//CopyData(&pivot1, &(*(works + 1)));
		//CopyData(&pivot2, &(*(works + 3)));
	}

	if (pred(pivot1, pivot2)) {	//	つまりは pivot1 < pivot2
		// pivot1 ≠ pivot2 のケース
		// dual pivot quick sort ベースの処理
		RAI idx1A = from;		//	value <= pivot1 の要素へのインデックス(arraysへの配置用)
		RAI idx2W = works;			//	pivot1 < value < pivot2の要素へのインデックス(worksへの配置用)
		RAI idx3W = works + range - 1;	//	pivot2 <= value へのインデックス(worksへの配置用)

		// 先頭から後方に向かってパーティション操作を行う。（一般的なクイックソートのように前後からではない）
		//   ピボット１以下の値は配列の前方に詰めていく
		//   ピボット２以上の値は作業領域の後方に詰めていく
		//   ピボット１より大きくピボット２より小さい値は、作業領域の前方に詰めていく
		for (RAI idx = from; idx < to; idx++) {
			if (pred(pivot1, *idx) == false) {	// idx <= pivot1
				*(idx1A++) = std::move(*idx);		// TODO ここで余計な代入が発生するケースがあるが、下手に最適化すると逆に遅くなってしまう…。
				//CopyData(&(*(idx1A++)), &(*idx));
			}
			else if (pred(*idx, pivot2) == false) {		// idx >= pivot2
				*(idx3W--) = std::move(*idx);
				//CopyData(&(*(idx3W--)), &(*idx));
			}
			else {
				*(idx2W++) = std::move(*idx);
				//CopyData(&(*(idx2W++)), &(*idx));
			}
		}

		RAI idxTo = idx1A;
		// ピボット１より大きく、ピボット２より小さいオブジェクト (pivot1 < value < pivot2) を works から array へ書き戻し
		for (RAI idx = works; idx < idx2W; idx++) {
			*(idxTo++) = std::move(*idx);
			//CopyData(&(*(idxTo++)), &(*idx));
		}
		// ピボット１より大きく、ピボット２より小さいオブジェクト(pivot1 < value < pivot2)をソート
		mmsSort(idx1A, idxTo, works, pred);

		// ピボット２以上のオブジェクト(pivot2 ≦ value)を works から array へ書き戻し
		for (RAI idx = works + range - 1; idx > idx3W; idx--) {
			*(idxTo++) = std::move(*idx);
			//CopyData(&(*(idxTo++)), &(*idx));
		}
		// ピボット２以上のオブジェクト(pivot2 ≦ value)をソート
		mmsSort(idx1A + (idx2W - works), to, works, pred);

		// ピボット１以下のオブジェクト(value ≦ pivot2)は最後にソート（CPUキャッシュに残っている可能性が低いので…。）
		mmsSort(from, idx1A, works, pred);
	} else {
		// pivot2 が pivot1 より小さいわけはないので、pivot1 ＝ pivot2 のケース
		// 3 way partition ベースの処理
		RAI idx1A = from;				// value < pivot の要素へのインデックス(arrayへの配置用)
		RAI idx2W = works;				// value == pivot の要素へのインデックス(worksへの配置用)
		RAI idx3W = works + range - 1;	// pivot < value へのインデックス(worksへの配置用)

		// 先頭から後方に向かってパーティション操作を行う。（一般的なクイックソートのように前後からではない）
		//   ピボット値より大きい値は配列の前方に詰めていく
		//   ピボット値より小さい値は作業領域の後方に詰めていく
		//   ピボット値と同じキー値の値は、作業領域の前方に詰めていく
		for (RAI idx = from; idx < to; idx++) {
			if (pred(*idx, pivot1)) {
				*(idx1A++) = std::move(*idx);
				//CopyData(&(*(idx1A++)), &(*idx));
			}
			else if (pred(pivot1, *idx)) {
				*(idx3W--) = std::move(*idx);
				//CopyData(&(*(idx3W--)), &(*idx));
			}
			else {
				*(idx2W++) = std::move(*idx);
			}
		}

		RAI idxTo = idx1A;
		// ピボット値と同じキーのオブジェクト(value = pivot1)を works から array へ書き戻し
		for (RAI idx = works; idx < idx2W; idx++) {
			*(idxTo++) = std::move(*idx);
			//CopyData(&(*(idxTo++)), &(*idx));
		}

		// ピボット値よりも大きいオブジェクト(pivot1 < value)を works から array へ書き戻し
		for (RAI idx = works + range - 1; idx > idx3W; idx--) {
			*(idxTo++) = std::move(*idx);
			//CopyData(&(*(idxTo++)), &(*idx));
		}

		// ピボット値より大きいオブジェクト(pivot1 < value)を先にソート（直前に配列コピーを行っており、CPUキャッシュにヒットしやすいため）
		mmsSort(idx1A + (idx2W - works), to, works, pred);
		// ピボット値より小さいオブジェクト(value < pivot1)をあとにソート（CPUキャッシュヒット率がたぶん低い）
		mmsSort(from, idx1A, works, pred);
	}
}

template <class RAI, class PR> void mmsSort(RAI from, RAI to, PR pred)
{
	typedef typename std::iterator_traits<RAI>::value_type BIv;
	size_t range = to - from;
	std::vector<BIv> works(range);

	mmsSort(from, to, works.begin(), pred);
}

template <class RAI>
inline void mmsSort(RAI from, RAI to) // cmpを省略した時に呼び出す。
{
	typedef typename std::iterator_traits<RAI>::value_type BIv;
	mmsSort(from, to, std::less<BIv>());
}
