#pragma once
/*
* SortBenchmarkSpec.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

enum class SortKeyType { INTEGER, STRING };


// 配列サイズ
#define ARRAY_SIZE 10000000
// ソートの繰り返し回数
#define TIMES 5
// 配列の初期状態（ランダム・昇順・降順…）
#define ARRAY_TYPE 0	// まだ意味ない
// ソートキーを整数にするか、文字列にするか
#define SORT_KEY_MODE SortKeyType::INTEGER

// コピーコンストラクタ・ムーブコンストラクタの呼び出し回数を数えるか
#define CUSTOM_CONSTRUCTOR
// FILLER1～ の項目をクラスに追加するか
#define FILLER_ITEMS
