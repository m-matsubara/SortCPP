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

namespace mmlib {
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
			// Difference between subscripts of pivot candidate values
			size_t gap = range / 12;
			// Subscript of pivot candidate value
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
			// Difference between subscripts of pivot candidate values
			size_t gap = range / 6;
			// Subscript of pivot candidate value
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

		// pivot1 ≦ pivot2 ()
		if (pred(pivot1, pivot2)) {
			// pivot1 ≠ pivot2
			// dual pivot quick sort
			RAI idx1A = from;				// Iterator of value <= pivot1 elements (to arrays)
			RAI idx2W = works;				// Iterator pivot1 < value < pivot2 elements (to works)
			RAI idx3W = works + range - 1;	// Iterator pivot2 <= value elements (to works)

			// Perform partition operations from the beginning to the back. (Not from the front and back like general quicksort)
			//   Values ​​below pivot1 are packed to the front of the array
			//   Values ​​with pivot2 or higher are packed behind the work area
			//   Values ​​larger than pivot1 and smaller than pivot2 are packed in front of the work area.
			for (RAI idx = from; idx < to; idx++) {
				if (pred(pivot1, *idx) == false) {	// idx <= pivot1
					*(idx1A++) = std::move(*idx);		// TODO There are cases where extra substitution occurs here.
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
			// Write back objects larger than pivot 1 and smaller than pivot 2 (pivot1 < value < pivot2) from works to array
			for (RAI idx = works; idx < idx2W; idx++) {
				*(idxTo++) = std::move(*idx);
				//CopyData(&(*(idxTo++)), &(*idx));
			}
			// Sort objects larger than pivot1 and smaller than pivot 2 (pivot1 < value < pivot2)
			mmsSort(idx1A, idxTo, works, pred);

			// Write back objects with pivot2 or higher (pivot2 ≦ value) from works to array
			for (RAI idx = works + range - 1; idx > idx3W; idx--) {
				*(idxTo++) = std::move(*idx);
				//CopyData(&(*(idxTo++)), &(*idx));
			}
			// Sort objects with pivot2 or higher (pivot2 ≦ value)
			mmsSort(idx1A + (idx2W - works), to, works, pred);

			// Objects with pivot1 or less (value ≦ pivot2) are sorted at the end (because it is unlikely that they remain in the CPU cache ...)
			mmsSort(from, idx1A, works, pred);
		}
		else {
			// The case of pivot1 = pivot2 because pivot2 cannot be less than pivot1
			// 3 way partition
			RAI idx1A = from;				// Iterator of "value < pivot" elements (to "array")
			RAI idx2W = works;				// Iterator of "value == pivot" elements (to "works")
			RAI idx3W = works + range - 1;	// Iterator of "pivot < value" elements (to "works")

			// Perform partition operations from the beginning to the back. (Not from the front and back like general quicksort)
			//   Values ​​larger than the pivot value are packed to the front of the array
			//   Values ​​smaller than the pivot value are packed behind the work area.
			//   The value of the same key value as the pivot value is packed in front of the work area.
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
			// Write back an object (value = pivot1) with the same key as the pivot value from works to array
			for (RAI idx = works; idx < idx2W; idx++) {
				*(idxTo++) = std::move(*idx);
				//CopyData(&(*(idxTo++)), &(*idx));
			}

			// Write back objects (pivot1 <value) greater than the pivot value from works to array
			for (RAI idx = works + range - 1; idx > idx3W; idx--) {
				*(idxTo++) = std::move(*idx);
				//CopyData(&(*(idxTo++)), &(*idx));
			}

			// Sort objects larger than the pivot value (pivot1 <value) first (because the array is copied immediately before and it is easy to hit the CPU cache)
			mmsSort(idx1A + (idx2W - works), to, works, pred);
			// Sort objects smaller than the pivot value (value <pivot1) later (CPU cache hit rate is probably low)
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
	inline void mmsSort(RAI from, RAI to)
	{
		typedef typename std::iterator_traits<RAI>::value_type BIv;
		mmsSort(from, to, std::less<BIv>());
	}
}