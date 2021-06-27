#pragma once
/*
* SortBenchmarkSpec.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

enum class SortKeyType { INTEGER, STRING };

// Array type 
enum class ArrayType { ARRAY_TYPE_RANDOM, ARRAY_TYPE_UNIQUE_RANDOM, ARRAY_TYPE_HALF_SORTED, ARRAY_TYPE_ASC, ARRAY_TYPE_DESC, ARRAY_TYPE_FLAT };

// Array size
#define ARRAY_SIZE 10000000

// Number of sort repetitions
#define TIMES 5

// Initial state of array (random, ascending, descending ...)
#define ARRAY_TYPE ArrayType::ARRAY_TYPE_RANDOM

// Whether the sort key is an integer or a string
#define SORT_KEY_TYPE SortKeyType::INTEGER
#define SORT_KEY_MODE SortKeyType::INTEGER

// Whether to count the number of calls to the copy constructor / move constructor
#define CUSTOM_CONSTRUCTOR

// Whether to add the FILLERx item to the class
#define FILLER_ITEMS
