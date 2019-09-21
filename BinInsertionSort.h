#pragma once
/*
* BinInsertionSort.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

template <class RAI, class PR> inline void binInsertionSort(RAI from, RAI to, PR pred)
{
	typedef typename std::iterator_traits<RAI>::value_type BIv;

	for (RAI i = from + 1; i < to; i++) {
		RAI fromIdx = from;
		RAI toIdx = i;
		RAI curIdx = fromIdx + ((toIdx - fromIdx) >> 1);
		while (fromIdx < toIdx) {
			if (pred(*i, *curIdx)) {
				toIdx = curIdx;
			}
			else {
				fromIdx = curIdx + 1;
			}
			curIdx = fromIdx + ((toIdx - fromIdx) >> 1);
		}
		if (i != curIdx) {
			BIv key = std::move(*i);
			for (RAI j = i - 1; j >= curIdx; j--) {
				*(j + 1) = std::move(*j);
			}
			*curIdx = std::move(key);
		}
	}
}

template <class RAI> inline void binInsertionSort(RAI from, RAI to)
{
	typedef typename std::iterator_traits<RAI>::value_type RAIv;
	binInsertionSort(from, to, std::less<RAIv>());
}

