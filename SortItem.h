#pragma once
/*
* SortItem.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <string>

#include "SortBenchmarkSpec.h"

//extern unsigned long compareCount;

class SortItem {
public:
	static unsigned long compareCount;
	static unsigned long constructorCount;
	static unsigned long copyConstructorCount;
	static unsigned long moveConstructorCount;
	static unsigned long copyOperatorCount;
	static unsigned long moveOperatorCount;
	static bool isStringKeyMode;

	int key;
	std::string keyString;
	int originalOrder;
#ifdef FILLER_ITEMS
	int filler1;
	int filler2;
	int filler3;
	int filler4;
	int filler5;
	int filler6;
	int filler7;
	int filler8;
	int filler9;
	int filler10;
	int filler11;
	int filler12;
	int filler13;
	int filler14;
#endif
	SortItem() : key(0), keyString(""), originalOrder(0) {
#ifdef FILLER_ITEMS
		filler1 = 0;
		filler2 = 0;
		filler3 = 0;
		filler4 = 0;
		filler5 = 0;
		filler6 = 0;
		filler7 = 0;
		filler8 = 0;
		filler9 = 0;
		filler10 = 0;
		filler11 = 0;
		filler12 = 0;
		filler13 = 0;
		filler14 = 0;
#endif
		constructorCount++;
	}
#ifdef CUSTOM_CONSTRUCTOR
	SortItem(const SortItem &org): key(org.key), keyString(org.keyString), originalOrder(org.originalOrder) {
		filler1 = org.filler1;
		filler2 = org.filler2;
		filler3 = org.filler3;
		filler4 = org.filler4;
		filler5 = org.filler5;
		filler6 = org.filler6;
		filler7 = org.filler7;
		filler8 = org.filler8;
		filler9 = org.filler9;
		filler10 = org.filler10;
		filler11 = org.filler11;
		filler12 = org.filler12;
		filler13 = org.filler13;
		filler14 = org.filler14;
		copyConstructorCount++;
	}
	SortItem(SortItem &&org) noexcept : key(org.key), keyString(org.keyString), originalOrder(org.originalOrder) {
		filler1 = org.filler1;
		filler2 = org.filler2;
		filler3 = org.filler3;
		filler4 = org.filler4;
		filler5 = org.filler5;
		filler6 = org.filler6;
		filler7 = org.filler7;
		filler8 = org.filler8;
		filler9 = org.filler9;
		filler10 = org.filler10;
		filler11 = org.filler11;
		filler12 = org.filler12;
		filler13 = org.filler13;
		filler14 = org.filler14;
		moveConstructorCount++;
		org.key = -1;
	}

	inline SortItem & operator = (const SortItem& obj) {
		key = obj.key;
		keyString = obj.keyString;
		originalOrder = obj.originalOrder;
		copyOperatorCount++;
		return *this;
	}
	inline SortItem & operator = (const SortItem&& obj) noexcept {
		key = obj.key;
		keyString = obj.keyString;
		originalOrder = obj.originalOrder;
		moveOperatorCount++;
		return *this;
	}
#endif

	inline bool operator < (const SortItem& obj) const {
		SortItem::compareCount++;
		if (SortItem::isStringKeyMode)
			return this->keyString < obj.keyString;
		else
			return this->key < obj.key;
	}

	inline bool operator <= (const SortItem& obj) const {
		SortItem::compareCount++;
		if (SortItem::isStringKeyMode)
			return this->keyString <= obj.keyString;
		else
			return this->key <= obj.key;
	}

	inline bool operator > (const SortItem& obj) const {
		SortItem::compareCount++;
		if (SortItem::isStringKeyMode)
			return this->keyString > obj.keyString;
		else
			return this->key > obj.key;
	}

	inline bool operator >= (const SortItem& obj) const {
		SortItem::compareCount++;
		if (SortItem::isStringKeyMode)
			return this->keyString >= obj.keyString;
		else
			return this->key >= obj.key;
	}

	inline bool operator == (const SortItem& obj) const {
		SortItem::compareCount++;
		if (SortItem::isStringKeyMode)
			return this->keyString == obj.keyString;
		else
			return this->key == obj.key;
	}

	inline bool operator != (const SortItem& obj) const {
		SortItem::compareCount++;
		if (SortItem::isStringKeyMode)
			return this->keyString != obj.keyString;
		else
			return this->key != obj.key;
	}

};

/*
template <class RAI> void validateVector(RAI from, RAI to)
{
	unsigned long bkCompareCount = SortItem::compareCount;
	if (to - from <= 0)
		return;

	size_t range = (to - from);
	for (size_t idx = 0; idx < range - 1; idx++) {
		if (from[idx] > from[idx + 1]) {
			SortItem::compareCount = bkCompareCount;
			throw std::string("sort error.");
		}
	}
	SortItem::compareCount = bkCompareCount;
}
*/

