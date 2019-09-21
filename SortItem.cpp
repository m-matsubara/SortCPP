/*
* SortItem.cpp
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/


#include "SortItem.h"


unsigned long SortItem::compareCount = 0;
unsigned long SortItem::constructorCount = 0;
unsigned long SortItem::copyConstructorCount = 0;
unsigned long SortItem::moveConstructorCount = 0;
unsigned long SortItem::copyOperatorCount = 0;
unsigned long SortItem::moveOperatorCount = 0;
bool SortItem::isStringKeyMode = false;
