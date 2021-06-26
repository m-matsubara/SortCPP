#pragma once
/*
* mmSort.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <iostream>
#include "InsertionSort.h"

namespace mmlib {
	template <class RAI, class PR> void mmSort(RAI from, RAI to, PR pred)
	{
		typedef typename std::iterator_traits<RAI>::value_type BIv;
		size_t range = to - from;		// Sort range

		//std::cout << range << std::endl;

		//	Special treatment when the size of the array to be sorted is less than a certain number
		if (range < 20) {
			insertionSort(from, to, pred);
			return;
		}

		RAI v1 = from;
		RAI v5 = to - 1;
		RAI v3 = v1 + ((v5 - v1) >> 1);
		RAI v2 = v1 + ((v3 - v1) >> 1);
		RAI v4 = v3 + ((v5 - v3) >> 1);

		// Sort 5 elements
		//sort5(array, p1, p2, p3, p4, p5, comparator);
		{
			//	First, the first three sorts
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
					BIv temp2 = std::move(*v2);
					*v2 = std::move(*v3);
					*v3 = std::move(temp2);
				}
				else {
					// v3 <= v1 <= v2
					BIv temp1 = std::move(*v1);
					*v1 = std::move(*v3);
					*v3 = std::move(*v2);
					*v2 = std::move(temp1);
				}
			}
			else {
				if (pred(*v3, *v1) == false) {	// v1 <= v3
					// v2 <= v1 <= v3
					BIv temp1 = std::move(*v1);
					*v1 = std::move(*v2);
					*v2 = std::move(temp1);
					//array[p3] = v3;
				}
				else if (pred(*v3, *v2) == false) {	//	v2 <= v3
					// v2 <= v3 <= v1
					BIv temp1 = std::move(*v1);
					*v1 = std::move(*v2);
					*v2 = std::move(*v3);
					*v3 = std::move(temp1);
				}
				else {
					// v3 <= v2 <= v1
					BIv temp1 = std::move(*v1);
					*v1 = std::move(*v3);
					*v3 = std::move(temp1);
				}
			}

			// Determine v4 (=array[p4]) position
			if (pred(*v4, *v2) == false) {		// v2 <= v4
				if (pred(*v4, *v3) == false) {	// v3 <= v4
					// array[p3] <= v4
				}
				else {
					// array[p2] <= v4 < array[p3];
					BIv temp4 = std::move(*v4);
					*v4 = std::move(*v3);
					*v3 = std::move(temp4);
				}
			}
			else {
				if (pred(*v4, *v1) == false) {	// v1 <= v4
					// array[p1] <= v4 < array[p2];
					BIv temp4 = std::move(*v4);
					*v4 = std::move(*v3);
					*v3 = std::move(*v2);
					*v2 = std::move(temp4);
				}
				else {
					// v4 < array[p1] <= array[p2];
					BIv temp4 = std::move(*v4);
					*v4 = std::move(*v3);
					*v3 = std::move(*v2);
					*v2 = std::move(*v1);
					*v1 = std::move(temp4);
				}
			}

			// Determine v5 (=array[p5]) position
			if (pred(*v5, *v3) == false) {		// v3 <= v5
				// array[p3] <= v5
				/* The 4th and 5th positional relationship is not important (as long as v3 is in the center)
				if (pred(array[p4], v5) <= 0) {
				// array[p3] <= array[4] <= v5
				} else {
				// array[p3] <= v5 < array[p4]
				array[p5] = array[p4];
				array[p4] = v5;
				}
				*/
			}
			else {
				// v5 < array[p3]
				if (pred(*v5, *v2) == false) {	// v2 <= v5
					// array[p2] <= v5 < array[p3]
					BIv temp5 = std::move(*v5);
					*v5 = std::move(*v4);
					*v4 = std::move(*v3);
					*v3 = std::move(temp5);
				}
				else {
					// v5 < array[p2] <= array[p3]
					/* The 1st and 2nd positional relationship is not important (as long as v3 is in the center) 
					if (pred(array[p1], v5) <= 0) {
					// array[p1] <= v5 < array[p2] <= array[p3]
					array[p5] = array[p4];
					array[p4] = array[p3];
					array[p3] = array[p2];
					array[p2] = v5;
					} else {
					// v5 < array[p1] <= array[p2] <= array[p3]
					array[p5] = array[p4];
					array[p4] = array[p3];
					array[p3] = array[p2];
					array[p2] = array[p1];
					array[p1] = v5;
					}
					*/
					BIv temp5 = std::move(*v5);
					*v5 = std::move(*v4);
					*v4 = std::move(*v3);
					*v3 = std::move(*v2);
					*v2 = std::move(temp5);
				}
			}
		}


		/*
		* この時点で、
		*   array[from](array[p1])には、5つの候補のうち、中央値以下の値が入っている。
		*   array[p3]には、中央値が入っている。
		*   array[to - 1](array[p5])には、5つの候補のうち、中央値以上の値が入っている。
		* そこで、
		*   array[from + 1]とarray[p2]の値を入れ替え
		*   array[from + 2]とarray[p3]の値を入れ替え
		*   array[to - 2]とarray[p4]の値を入れ替え
		* とすることで、パーティション操作の範囲を狭くすることができる。
		**/

		std::swap(from[1], *v2);
		std::swap(from[2], *v3);
		std::swap(to[-2], *v4);

		RAI pivot = from + 2;	// pivot

		//	Partition operation
		RAI curFrom = from + 3;			//	min index / The smaller position currently being processed
		RAI curTo = to - 1 - 2;			//	max index / The larger position currently being processed
		while (true) {
			if (pred(*curFrom, *pivot))
				while (pred(*++curFrom, *pivot));
			if (pred(*pivot, *curTo))
				while (pred(*pivot, *--curTo));
			if (curFrom >= curTo)
				break;
			//BIv work = *curFrom;
			//*curFrom++ = *curTo;
			//*curTo-- = work;
			std::swap(*curFrom++, *curTo--);
		};

		//	ピボット値をパーティションの間に入れ替える（再起の処理の対象外にできる）
		// Swap the pivot value between partitions (can be excluded from the recurcive process)
		std::swap(from[2], *curTo);

		mmSort(from, curTo, pred);
		mmSort(curFrom, to, pred);
	}

	template <class RAI>
	inline void mmSort(RAI from, RAI to)
	{
		typedef typename std::iterator_traits<RAI>::value_type RAIv;
		mmSort(from, to, std::less<RAIv>());
	}
}