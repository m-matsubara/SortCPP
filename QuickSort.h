#pragma once
/*
* QuickSort.h
*
* [TEST TYPE] Quick sort
* For testing for the following purposes
*   * Comparison with other algorithms
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
		size_t range = to - from;		// Sort range

		if (range < 20) {
			insertionSort(from, to, pred);
			return;
		}

		RAI v1 = from;
		RAI v2 = from + (range >> 1);
		RAI v3 = to - 1;

		//	median of three
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


		RAIv pivot = *v2;

		//	Partition operation
		RAI curFrom = from;			//	min iterator
		RAI curTo = to - 1;			//	max iterator
		while (true) {
			if (pred(*curFrom, pivot))
				while (pred(*++curFrom, pivot));
			if (pred(pivot, *curTo))
				while (pred(pivot, *--curTo));
			if (curFrom >= curTo)
				break;
			std::swap(*curFrom++, *curTo--);
		};

		// Recurcive operation in each small partition and large partition
		quickSort(from, curTo + 1, pred);
		quickSort(curFrom, to, pred);
	}

	template <class RAI>
	inline void quickSort(RAI from, RAI to)
	{
		typedef typename std::iterator_traits<RAI>::value_type RAIv;
		quickSort(from, to, std::less<RAIv>());
	}
}