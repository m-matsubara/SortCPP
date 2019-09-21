#pragma once
/*
* InsertionSort.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <algorithm>
#include <functional>


// 挿入ソート
template <class RAI, class PR> inline void insertionSort(RAI from, RAI to, PR pred)
{
	for (RAI ite = from + 1; ite < to; ite++) {
		if (pred(*ite, ite[-1])) {
			auto value = std::move(*ite);
			RAI insIte = ite;
			do {
				*insIte = std::move(insIte[-1]);
				--insIte;
			} while (insIte > from && pred(value, insIte[-1]));
			*insIte = std::move(value);
		}
	}
}

template <class RAI> inline void insertionSort(RAI from, RAI to)
{
	typedef typename std::iterator_traits<RAI>::value_type RAIv;
	insertionSort(from, to, std::less<RAIv>());
}

