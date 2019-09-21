/*
* SortBenchmarkSpec.h
*
*
* http://www.mmatsubara.com/developer/sortCpp/
*
* Copyright (c) 2017 matsubara masakazu
* Released under the MIT license
* https://github.com/m-matsubara/sortCpp/blob/master/LICENSE.txt
*/

#pragma once

enum sort_key_type { skt_int, skt_str };


#define ARRAY_SIZE 10000000
#define TIMES 5
#define ARRAY_TYPE 0	// まだ意味ない
#define SORT_KEY_MODE skt_int

//#define CUSTOM_CONSTRUCTOR
