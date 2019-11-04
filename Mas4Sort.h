#pragma once
/*
* Mas4Sort.h
*
* Copyright (c) 2017 masakazu matsubara
* Released under the MIT license
* https://github.com/m-matsubara/SortCPP/blob/master/LICENSE.txt
*/

#include <vector>

#include "InsertionSort.h"

namespace mmlib {

	/*
	* 4-way merge
	* internal function
	*/
	template <class RAI, class OI, class PR> void _mas4Merge(RAI pos1, RAI pos2, RAI pos3, RAI pos4, RAI pos5, OI posOut, PR pred) {

		/*
		* 各レーンをその先頭値でソートし、ソート結果を int の変数１つで管理する
		* 例1) 各レーンの先頭の値が以下の場合、 state = 0x1234 となる
		*   レーン1 : 10
		*   レーン2 : 20
		*   レーン3 : 30
		*   レーン4 : 40
		* 例2) 各レーンの先頭の値が以下の場合、 state = 0x2413 となる
		*   レーン1 : 30
		*   レーン2 : 10
		*   レーン3 : 40
		*   レーン4 : 20
		*/
		int state;

		// state 変数の初期状態決定
		if (pred(*pos2, *pos1) == false) {						// *pos1 <= *pos2
			// array[p1] <= array[p2]
			if (pred(*pos3, *pos2) == false) {					// *pos2 <= *pos3
																// array[p1] <= array[p2] <= array[p3]
				if (pred(*pos4, *pos2) == false) {				// *pos2 <= *pos4
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						state = 0x1234;
					else
						state = 0x1243;
				}
				else {
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						state = 0x1423;
					else
						state = 0x4123;
				}
			}
			else if (pred(*pos3, *pos1) == false) {			// *pos1 <= *pos3
				// array[p1] <= array[p3] <= array[p2]
				if (pred(*pos4, *pos3) == false) {				// *pos3 <= *pos4
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						state = 0x1324;
					else
						state = 0x1342;
				}
				else {
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						state = 0x1432;
					else
						state = 0x4132;
				}
			}
			else {
				// array[p3] < array[p1] <= array[p2]
				if (pred(*pos4, *pos1) == false) {				// *pos1 <= *pos4
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						state = 0x3124;
					else
						state = 0x3142;
				}
				else {
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						state = 0x3412;
					else
						state = 0x4312;
				}
			}
		}
		else {
			// array[p2] < array[p1]
			if (pred(*pos3, *pos1) == false) {					// *pos1 <= *pos3
																// array[p2] < array[p1] <= array[p3]
				if (pred(*pos4, *pos1) == false) {				// *pos1 <= *pos4
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						state = 0x2134;
					else
						state = 0x2143;
				}
				else {
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						state = 0x2413;
					else
						state = 0x4213;
				}
			}
			else if (pred(*pos3, *pos2) == false) {			// *pos2 <= *pos3
				// array[p2] <= array[p3] < array[p1]
				if (pred(*pos4, *pos3) == false) {				// *pos3 <= *pos4
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						state = 0x2314;
					else
						state = 0x2341;
				}
				else {
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						state = 0x2431;
					else
						state = 0x4231;
				}
			}
			else {
				// array[p3] < array[p2] < array[p1]
				if (pred(*pos4, *pos2) == false) {				// *pos2 <= *pos4
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						state = 0x3214;
					else
						state = 0x3241;
				}
				else {
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						state = 0x3421;
					else
						state = 0x4321;
				}
			}
		}

		// 各レーンの終了位置
		const auto p1to = pos2;
		const auto p2to = pos3;
		const auto p3to = pos4;
		const RAI  p4to = pos5;

		// ４レーンのループ
		for (;; advance(posOut, 1)) {
			if (state < 0x2000) {	//	state : [0x1234, 0x1432]
				// レーン１から値を取得
				*posOut = std::move(*pos1);
				advance(pos1, 1);
				// レーン１が終了したら「４レーンのループ」を抜けて「３レーンのループ」へ
				if (pos1 >= p1to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x1234:
					if (pred(*pos3, *pos1) == false) {		// *pos1 <= *pos3
						if (pred(*pos2, *pos1) == false) {	// *pos1 <= *pos2
						}
						else {
							state = 0x2134;
						}
					}
					else {
						if (pred(*pos4, *pos1) == false) {		// *pos1 <= *pos4
							state = 0x2314;
						}
						else {
							state = 0x2341;
						}
					}
					break;
				case 0x1243:
					if (pred(*pos4, *pos1) == false) {			// *pos1 <= *pos4
						if (pred(*pos2, *pos1) == false) {	// *pos1 <= *pos2
						}
						else {
							state = 0x2143;
						}
					}
					else {
						if (pred(*pos3, *pos1) == false) {	// *pos1 <= *pos3
							state = 0x2413;
						}
						else {
							state = 0x2431;
						}
					}
					break;
				case 0x1324:
					if (pred(*pos2, *pos1) == false) {		// *pos1 <= *pos2
						if (pred(*pos3, *pos1) == false) {	// *pos1 <= *pos3
						}
						else {
							state = 0x3124;
						}
					}
					else {
						if (pred(*pos4, *pos1) == false) {		// *pos1 <= *pos4
							state = 0x3214;
						}
						else {
							state = 0x3241;
						}
					}
					break;
				case 0x1342:
					if (pred(*pos4, *pos1) == false) {			// *pos1 <= *pos4
						if (pred(*pos3, *pos1) == false) {	// *pos1 <= *pos3
						}
						else {
							state = 0x3142;
						}
					}
					else {
						if (pred(*pos2, *pos1) == false) {	// *pos1 <= *pos2
							state = 0x3412;
						}
						else {
							state = 0x3421;
						}
					}
					break;
				case 0x1423:
					if (pred(*pos2, *pos1) == false) {		// *pos1 <= *pos2
						if (pred(*pos4, *pos1) == false) {		// *pos1 <= *pos4
						}
						else {
							state = 0x4123;
						}
					}
					else {
						if (pred(*pos3, *pos1) == false) {	// *pos1 <= *pos3
							state = 0x4213;
						}
						else {
							state = 0x4231;
						}
					}
					break;
				case 0x1432:
					if (pred(*pos3, *pos1) == false) {		// *pos1 <= *pos3
						if (pred(*pos4, *pos1) == false) {		// *pos1 <= *pos4
						}
						else {
							state = 0x4132;
						}
					}
					else {
						if (pred(*pos2, *pos1) == false) {	// *pos1 <= *pos2
							state = 0x4312;
						}
						else {
							state = 0x4321;
						}
					}
				}
			}
			else if (state < 0x3000) {	//	state : [0x2134, 0x2431]
				// レーン２から値を取得
				*posOut = std::move(*pos2);
				advance(pos2, 1);
				// レーン２が終了したら「４レーンのループ」を抜けて「３レーンのループ」へ
				if (pos2 >= p2to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x2134:
					if (pred(*pos3, *pos2) == false) {		// *pos2 <= *pos3
						if (pred(*pos2, *pos1)) {				// *pos2 < *pos1
						}
						else {
							state = 0x1234;
						}
					}
					else {
						if (pred(*pos4, *pos2) == false) {		// *pos2 <= *pos4
							state = 0x1324;
						}
						else {
							state = 0x1342;
						}
					}
					break;
				case 0x2143:
					if (pred(*pos4, *pos2) == false) {			// *pos2 <= *pos4
						if (pred(*pos2, *pos1)) {				// *pos2 < *pos1
						}
						else {
							state = 0x1243;
						}
					}
					else {
						if (pred(*pos3, *pos2) == false) {	// *pos2 <= *pos3
							state = 0x1423;
						}
						else {
							state = 0x1432;
						}
					}
					break;
				case 0x2314:
					if (pred(*pos2, *pos1)) {					// *pos2 < *pos1
						if (pred(*pos3, *pos2) == false) {	// *pos2 <= *pos3
						}
						else {
							state = 0x3214;
						}
					}
					else {
						if (pred(*pos4, *pos2) == false) {		// *pos2 <= *pos4
							state = 0x3124;
						}
						else {
							state = 0x3142;
						}
					}
					break;
				case 0x2341:
					if (pred(*pos4, *pos2) == false) {			// *pos2 <= *pos4
						if (pred(*pos3, *pos2) == false) {	// *pos2 <= *pos3
						}
						else {
							state = 0x3241;
						}
					}
					else {
						if (pred(*pos2, *pos1)) {				// *pos2 < *pos1
							state = 0x3421;
						}
						else {
							state = 0x3412;
						}
					}
					break;
				case 0x2413:
					if (pred(*pos2, *pos1)) {					// *pos2 < *pos1
						if (pred(*pos4, *pos2) == false) {		// *pos2 <= *pos4
						}
						else {
							state = 0x4213;
						}
					}
					else {
						if (pred(*pos3, *pos2) == false) {	// *pos2 <= *pos3
							state = 0x4123;
						}
						else {
							state = 0x4132;
						}
					}
					break;
				case 0x2431:
					if (pred(*pos3, *pos2) == false) {		// *pos2 <= *pos3
						if (pred(*pos4, *pos2) == false) {		// *pos2 <= *pos4
						}
						else {
							state = 0x4231;
						}
					}
					else {
						if (pred(*pos2, *pos1)) {				// *pos2 < *pos1
							state = 0x4321;
						}
						else {
							state = 0x4312;
						}
					}
				}
			}
			else if (state < 0x4000) {	//	state : [0x3124, 0x3421]
				// レーン３から値を取得
				*posOut = std::move(*pos3);
				advance(pos3, 1);
				// レーン３が終了したら「４レーンのループ」を抜けて「３レーンのループ」へ
				if (pos3 >= p3to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x3124:
					if (pred(*pos3, *pos2)) {					// *pos3 < *pos2
						if (pred(*pos3, *pos1)) {				// *pos3 < *pos1
						}
						else {
							state = 0x1324;
						}
					}
					else {
						if (pred(*pos4, *pos3) == false) {		// *pos3 <= *pos4
							state = 0x1234;
						}
						else {
							state = 0x1243;
						}
					}
					break;
				case 0x3142:
					if (pred(*pos4, *pos3) == false) {			// *pos3 <= *pos4
						if (pred(*pos3, *pos1)) {				// *pos3 < *pos1
						}
						else {
							state = 0x1342;
						}
					}
					else {
						if (pred(*pos3, *pos2)) {				// *pos3 < *pos2
							state = 0x1432;
						}
						else {
							state = 0x1423;
						}
					}
					break;
				case 0x3214:
					if (pred(*pos3, *pos1)) {					// *pos3 < *pos1
						if (pred(*pos3, *pos2)) {				// *pos3 < *pos2
						}
						else {
							state = 0x2314;
						}
					}
					else {
						if (pred(*pos4, *pos3) == false) {		// *pos3 <= *pos4
							state = 0x2134;
						}
						else {
							state = 0x2143;
						}
					}
					break;
				case 0x3241:
					if (pred(*pos4, *pos3) == false) {			// *pos3 <= *pos4
						if (pred(*pos3, *pos2)) {				// *pos3 < *pos2
						}
						else {
							state = 0x2341;
						}
					}
					else {
						if (pred(*pos3, *pos1)) {				// *pos3 < *pos1
							state = 0x2431;
						}
						else {
							state = 0x2413;
						}
					}
					break;
				case 0x3412:
					if (pred(*pos3, *pos1)) {					// *pos3 < *pos1
						if (pred(*pos4, *pos3) == false) {		// *pos3 <= *pos4
						}
						else {
							state = 0x4312;
						}
					}
					else {
						if (pred(*pos3, *pos2)) {				// *pos3 < *pos2
							state = 0x4132;
						}
						else {
							state = 0x4123;
						}
					}
					break;
				case 0x3421:
					if (pred(*pos3, *pos2)) {					// *pos3 < *pos2
						if (pred(*pos4, *pos3) == false) {		// *pos3 <= *pos4
						}
						else {
							state = 0x4321;
						}
					}
					else {
						if (pred(*pos3, *pos1)) {				// *pos3 < *pos1
							state = 0x4231;
						}
						else {
							state = 0x4213;
						}
					}
				}
			}
			else {	//	state : [0x4123, 0x4321]
				// レーン４から値を取得
				*posOut = std::move(*pos4);
				advance(pos4, 1);
				// レーン４が終了したら「４レーンのループ」を抜けて「３レーンのループ」へ
				if (pos4 >= p4to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x4123:
					if (pred(*pos4, *pos2)) {					// *pos4 < *pos2
						if (pred(*pos4, *pos1)) {				// *pos4 < *pos1
						}
						else {
							state = 0x1423;
						}
					}
					else {
						if (pred(*pos4, *pos3)) {				// *pos4 < *pos3
							state = 0x1243;
						}
						else {
							state = 0x1234;
						}
					}
					break;
				case 0x4132:
					if (pred(*pos4, *pos3)) {					// *pos4 < *pos3
						if (pred(*pos4, *pos1)) {				// *pos4 < *pos1
						}
						else {
							state = 0x1432;
						}
					}
					else {
						if (pred(*pos4, *pos2)) {				// *pos4 < *pos2
							state = 0x1342;
						}
						else {
							state = 0x1324;
						}
					}
					break;
				case 0x4213:
					if (pred(*pos4, *pos1)) {					// *pos4 < *pos1
						if (pred(*pos4, *pos2)) {				// *pos4 < *pos2
						}
						else {
							state = 0x2413;
						}
					}
					else {
						if (pred(*pos4, *pos3)) {				// *pos4 < *pos3
							state = 0x2143;
						}
						else {
							state = 0x2134;
						}
					}
					break;
				case 0x4231:
					if (pred(*pos4, *pos3)) {					// *pos4 < *pos3
						if (pred(*pos4, *pos2)) {				// *pos4 < *pos2
						}
						else {
							state = 0x2431;
						}
					}
					else {
						if (pred(*pos4, *pos1)) {				// *pos4 < *pos1
							state = 0x2341;
						}
						else {
							state = 0x2314;
						}
					}
					break;
				case 0x4321:
					if (pred(*pos4, *pos2)) {					// *pos4 < *pos2
						if (pred(*pos4, *pos3)) {				// *pos4 < *pos3
						}
						else {
							state = 0x3421;
						}
					}
					else {
						if (pred(*pos4, *pos1)) {				// *pos4 < *pos1
							state = 0x3241;
						}
						else {
							state = 0x3214;
						}
					}
					break;
				case 0x4312:
					if (pred(*pos4, *pos1)) {					// *pos4 < *pos1
						if (pred(*pos4, *pos3)) {				// *pos4 < *pos3
						}
						else {
							state = 0x3412;
						}
					}
					else {
						if (pred(*pos4, *pos2)) {				// *pos4 < *pos2
							state = 0x3142;
						}
						else {
							state = 0x3124;
						}
					}
				}
			}
		}
		advance(posOut, 1);
		state &= 0xfff;

		// ３レーンのループ
		for (;; advance(posOut, 1)) {
			// 以下のif文のネストは、本来なら switch case で処理するべきだが、if のネストのほうが速かったので、このような書き方にしている。
			if (state < 0x200) {	//	state : [0x123, 0x143]
				// レーン１から値を取得
				*posOut = std::move(*pos1);
				advance(pos1, 1);
				// レーン１が終了したら「３レーンのループ」を抜けて「２レーンのループ」へ
				if (pos1 >= p1to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x123:
					if (pred(*pos2, *pos1) == false)			// *pos1 <= *pos2
						; // モード変更なし
					else if (pred(*pos3, *pos1) == false)		// *pos1 <= *pos3
						state = 0x213;
					else
						state = 0x231;
					break;
				case 0x124:
					if (pred(*pos2, *pos1) == false)			// *pos1 <= *pos2
						; // モード変更なし
					else if (pred(*pos4, *pos1) == false)		// *pos1 <= *pos4
						state = 0x214;
					else
						state = 0x241;
					break;
				case 0x132:
					if (pred(*pos3, *pos1) == false)			// *pos1 <= *pos3
						; // モード変更なし
					else if (pred(*pos2, *pos1) == false)		// *pos1 <= *pos2
						state = 0x312;
					else
						state = 0x321;
					break;
				case 0x134:
					if (pred(*pos3, *pos1) == false)			// *pos1 <= *pos3
						; // モード変更なし
					else if (pred(*pos4, *pos1) == false)		// *pos1 <= *pos4
						state = 0x314;
					else
						state = 0x341;
					break;
				case 0x142:
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						; // モード変更なし
					else if (pred(*pos2, *pos1) == false)		// *pos1 <= *pos2
						state = 0x412;
					else
						state = 0x421;
					break;
				case 0x143:
					if (pred(*pos4, *pos1) == false) 			// *pos1 <= *pos4
						; // モード変更なし
					else if (pred(*pos3, *pos1) == false)		// *pos1 <= *pos3
						state = 0x413;
					else
						state = 0x431;
				}
			}
			else if (state < 0x300) {	//	state : [0x213, 0x243]
				// レーン２から値を取得
				*posOut = std::move(*pos2);
				advance(pos2, 1);
				// レーン２が終了したら「３レーンのループ」を抜けて「２レーンのループ」へ
				if (pos2 >= p2to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x213:
					if (pred(*pos2, *pos1))					// *pos2 < *pos1
						; // モード変更なし
					else if (pred(*pos3, *pos2) == false)		// *pos2 <= *pos3
						state = 0x123;
					else
						state = 0x132;
					break;
				case 0x214:
					if (pred(*pos2, *pos1))					// *pos2 < *pos1
						; // モード変更なし
					else if (pred(*pos4, *pos2) == false)		// *pos2 <= *pos4
						state = 0x124;
					else
						state = 0x142;
					break;
				case 0x231:
					if (pred(*pos3, *pos2) == false)			// *pos2 <= *pos3
						; // モード変更なし
					else if (pred(*pos2, *pos1))				// *pos2 < *pos1
						state = 0x321;
					else
						state = 0x312;
					break;
				case 0x234:
					if (pred(*pos3, *pos2) == false)			// *pos2 <= *pos3
						; // モード変更なし
					else if (pred(*pos4, *pos2) == false)		// *pos2 <= *pos4
						state = 0x324;
					else
						state = 0x342;
					break;
				case 0x241:
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						; // モード変更なし
					else if (pred(*pos2, *pos1))				// *pos2 < *pos1
						state = 0x421;
					else
						state = 0x412;
					break;
				case 0x243:
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						; // モード変更なし
					else if (pred(*pos3, *pos2) == false)		// *pos2 <= *pos3
						state = 0x423;
					else
						state = 0x432;
				}
			}
			else if (state < 0x400) {	//	state : [0x312, 0x342]
				// レーン３から値を取得
				*posOut = std::move(*pos3);
				advance(pos3, 1);
				// レーン３が終了したら「３レーンのループ」を抜けて「２レーンのループ」へ
				if (pos3 >= p3to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x312:
					if (pred(*pos3, *pos1))					// *pos3 < *pos1
						; // モード変更なし
					else if (pred(*pos3, *pos2))				// *pos3 < *pos2
						state = 0x132;
					else
						state = 0x123;
					break;
				case 0x314:
					if (pred(*pos3, *pos1))					// *pos3 < *pos1
						; // モード変更なし
					else if (pred(*pos4, *pos3) == false)		// *pos3 <= *pos4
						state = 0x134;
					else
						state = 0x143;
					break;
				case 0x321:
					if (pred(*pos3, *pos2))					// *pos3 < *pos2
						; // モード変更なし
					else if (pred(*pos3, *pos1))				// *pos3 < *pos1
						state = 0x231;
					else
						state = 0x213;
					break;
				case 0x324:
					if (pred(*pos3, *pos2))					// *pos3 < *pos2
						; // モード変更なし
					else if (pred(*pos4, *pos3) == false)		// *pos3 <= *pos4
						state = 0x234;
					else
						state = 0x243;
					break;
				case 0x341:
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						; // モード変更なし
					else if (pred(*pos3, *pos1))				// *pos3 < *pos1
						state = 0x431;
					else
						state = 0x413;
					break;
				case 0x342:
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						; // モード変更なし
					else if (pred(*pos3, *pos2))				// *pos3 < *pos2
						state = 0x432;
					else
						state = 0x423;
				}
			}
			else {	//	state : [0x412, 0x432]
				// レーン４から値を取得
				*posOut = std::move(*pos4);
				advance(pos4, 1);
				// レーン４が終了したら「３レーンのループ」を抜けて「２レーンのループ」へ
				if (pos4 >= p4to)
					break;
				// state変数を更新(binary insertion sortのような感じで)
				switch (state) {
				case 0x412:
					if (pred(*pos4, *pos1))					// *pos4 < *pos1
						; // モード変更なし
					else if (pred(*pos4, *pos2))				// *pos4 < *pos2
						state = 0x142;
					else
						state = 0x124;
					break;
				case 0x413:
					if (pred(*pos4, *pos1))					// *pos4 < *pos1
						; // モード変更なし
					else if (pred(*pos4, *pos3))				// *pos4 < *pos3
						state = 0x143;
					else
						state = 0x134;
					break;
				case 0x421:
					if (pred(*pos4, *pos2))					// *pos4 < *pos2
						; // モード変更なし
					else if (pred(*pos4, *pos1))				// *pos4 < *pos1
						state = 0x241;
					else
						state = 0x214;
					break;
				case 0x423:
					if (pred(*pos4, *pos2))					// *pos4 < *pos2
						; // モード変更なし
					else if (pred(*pos4, *pos3))				// *pos4 < *pos3
						state = 0x243;
					else
						state = 0x234;
					break;
				case 0x431:
					if (pred(*pos4, *pos3))					// *pos4 < *pos3
						; // モード変更なし
					else if (pred(*pos4, *pos1))				// *pos4 < *pos1
						state = 0x341;
					else
						state = 0x314;
					break;
				case 0x432:
					if (pred(*pos4, *pos3))					// *pos4 < *pos3
						; // モード変更なし
					else if (pred(*pos4, *pos2))				// *pos4 < *pos2
						state = 0x342;
					else
						state = 0x324;
				}
			}
		}
		advance(posOut, 1);
		state &= 0xff;

		// ２レーンのループ
		for (;; advance(posOut, 1)) {
			if (state < 0x20) {	//	state : [0x12, 0x14]
				// レーン１から値を取得
				*posOut = std::move(*pos1);
				advance(pos1, 1);
				if (pos1 >= p1to)
					break;
				// state変数を更新
				switch (state) {
				case 0x12:
					if (pred(*pos2, *pos1) == false)			// *pos1 <= *pos2
						; // モード変更なし
					else
						state = 0x21;
					break;
				case 0x13:
					if (pred(*pos3, *pos1) == false)			// *pos1 <= *pos3
						; // モード変更なし
					else
						state = 0x31;
					break;
				case 0x14:
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						; // モード変更なし
					else
						state = 0x41;
				}
			}
			else if (state < 0x30) {	//	state : [0x21, 0x24]
				// レーン２から値を取得
				*posOut = std::move(*pos2);
				advance(pos2, 1);
				if (pos2 >= p2to)
					break;
				// state変数を更新
				switch (state) {
				case 0x21:
					if (pred(*pos2, *pos1))					// *pos2 < *pos1
						; // モード変更なし
					else
						state = 0x12;
					break;
				case 0x23:
					if (pred(*pos3, *pos2) == false)			// *pos2 <= *pos3
						; // モード変更なし
					else
						state = 0x32;
					break;
				case 0x24:
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						; // モード変更なし
					else
						state = 0x42;
				}
			}
			else if (state < 0x40) {	//	state : [0x31, 0x34]
				// レーン３から値を取得
				*posOut = std::move(*pos3);
				advance(pos3, 1);
				if (pos3 >= p3to)
					break;
				// state変数を更新
				switch (state) {
				case 0x31:
					if (pred(*pos3, *pos1))					// *pos3 < *pos1
						; // モード変更なし
					else
						state = 0x13;
					break;
				case 0x32:
					if (pred(*pos3, *pos2))					// *pos3 < *pos2
						; // モード変更なし
					else
						state = 0x23;
					break;
				case 0x34:
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						; // モード変更なし
					else
						state = 0x43;
				}
			}
			else {	//	state : [0x41, 0x43]
				// レーン４から値を取得
				*posOut = std::move(*pos4);
				advance(pos4, 1);
				if (pos4 >= p4to)
					break;
				// state変数を更新
				switch (state) {
				case 0x41:
					if (pred(*pos4, *pos1))					// *pos4 < *pos1
						; // モード変更なし
					else
						state = 0x14;
					break;
				case 0x42:
					if (pred(*pos4, *pos2))					// *pos4 < *pos2
						; // モード変更なし
					else
						state = 0x24;
					break;
				case 0x43:
					if (pred(*pos4, *pos3))					// *pos4 < *pos3
						; // モード変更なし
					else
						state = 0x34;
				}
			}
		}
		advance(posOut, 1);
		state &= 0xf;

		// 残ったワーク領域の各レーンを出力先に格納する
		switch (state) {
		case 0x1:
			std::move(pos1, p1to, posOut);
			break;
		case 0x2:
			std::move(pos2, p2to, posOut);
			break;
		case 0x3:
			std::move(pos3, p3to, posOut);
			break;
		case 0x4:
			std::move(pos4, p4to, posOut);
		}
	}


	/*
	* mas4sort (4-way merge sort)
	* internal function
	*/
	template <class RAI, class OI, class PR> void _mas4Sort(RAI from, RAI to, OI out, PR pred, bool sourceIsEnable) {
		const size_t range = std::distance(from, to);
		//	ソート対象配列サイズが一定数未満のときは特別扱い
		if (range < 5) {
			if (sourceIsEnable)
				std::move(from, to, out);

			insertionSort(out, out + range, pred);
			return;
		}

		// ソート範囲を４つの区間（レーン）に分割
		const size_t gap = range / 4;
		const RAI pos1 = from;
		const RAI pos2 = pos1 + gap;
		const RAI pos3 = pos2 + gap;
		const RAI pos4 = pos3 + gap;

		const OI opos1 = out;
		const OI opos2 = opos1 + gap;
		const OI opos3 = opos2 + gap;
		const OI opos4 = opos3 + gap;
		const OI outto = out + range;

		// 各レーンをソート
		_mas4Sort(opos1, opos2, pos1, pred, !sourceIsEnable);
		_mas4Sort(opos2, opos3, pos2, pred, !sourceIsEnable);
		_mas4Sort(opos3, opos4, pos3, pred, !sourceIsEnable);
		_mas4Sort(opos4, outto, pos4, pred, !sourceIsEnable);

		// 各レーンをマージ
		_mas4Merge(pos1, pos2, pos3, pos4, to, out, pred);
	}

	/*
	* mas4sort (4-way merge sort)
	*/
	template <class RAI, class PR> void mas4Sort(RAI first, RAI to, PR pred) {
		size_t range = std::distance(first, to);
		if (range <= 32) {
			insertionSort(first, to, pred);
			return;
		}

		typedef typename std::iterator_traits<RAI>::value_type RAIv;
		std::vector<RAIv> workVector;
		workVector.reserve(range);
		for (RAI item = first; item < to; advance(item, 1)) {
			workVector.push_back(std::move(*item));
		}

		_mas4Sort(workVector.begin(), workVector.end(), first, pred, true);
	}

	/*
	* mas4sort (4-way merge sort)
	*/
	template <class RAI> inline void mas4Sort(RAI first, RAI last) // cmpを省略した時に呼び出す。
	{
		mas4Sort(first, last, std::less<>());
	}
}
