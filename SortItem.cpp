/*
* SortItem.cpp
*
*
* http://www.mmatsubara.com/developer/sortCpp/
*
* Copyright (c) 2017 matsubara masakazu
* Released under the MIT license
* https://github.com/m-matsubara/sortCpp/blob/master/LICENSE.txt
*/


#include "stdafx.h"
#include "SortItem.h"


unsigned long SortItem::compareCount = 0;
unsigned long SortItem::constructorCount = 0;
unsigned long SortItem::copyConstructorCount = 0;
unsigned long SortItem::moveConstructorCount = 0;
unsigned long SortItem::copyOperatorCount = 0;
unsigned long SortItem::moveOperatorCount = 0;
bool SortItem::isStringKeyMode = false;
