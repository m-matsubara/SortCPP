#pragma once
/*
 * Mas4Sort.h
 *
 * Mas4Sort 2nd Generation implements.
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
		* Sort each lane by its start value and manage the sort result with one int variable
		* Ex1) If the value at the beginning of each lane is, then state = 0x1234
		*   lane1 : 10
		*   lane2 : 20
		*   lane3 : 30
		*   lane4 : 40
		* Ex2) If the value at the beginning of each lane is, then state = 0x2413
		*   lane1 : 30
		*   lane2 : 10
		*   lane3 : 40
		*   lane4 : 20
		*/
		int state;

		// Determining the initial state of the "state" variable
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

		//End position of each lane
		const auto p1to = pos2;
		const auto p2to = pos3;
		const auto p3to = pos4;
		const RAI  p4to = pos5;

		// Loop of 4 lanes
		for (;; posOut++) {
			if (state < 0x2000) {	//	state : [0x1234, 0x1432]
				// Get value from lane1 
				*posOut = std::move(*pos1);
				pos1++;
				if (pos1 >= p1to)
					break;	// lane1 finished. to Loop of 3 lanes
				// Update state variable (Like binary insertion sort)
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
				// Get value from lane2 
				*posOut = std::move(*pos2);
				pos2++;
				if (pos2 >= p2to)
					break;	// lane2 finished. to Loop of 3 lanes
				// Update state variable (Like binary insertion sort)
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
				// Get value from lane3
				*posOut = std::move(*pos3);
				pos3++;
				if (pos3 >= p3to)
					break;	// lane3 finished. to Loop of 3 lanes
				// Update state variable (Like binary insertion sort)
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
				// Get value from lane4
				*posOut = std::move(*pos4);
				pos4++;
				if (pos4 >= p4to)
					break;	// lane4 finished. to Loop of 3 lanes
				// Update state variable (Like binary insertion sort)
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
		posOut++;
		state &= 0xfff;

		// Loop of 3 lanes
		for (;; posOut++) {
			// "if" nesting was faster than "switch case"
			if (state < 0x200) {	//	state : [0x123, 0x143]
				// Get value from lane1
				*posOut = std::move(*pos1);
				pos1++;
				if (pos1 >= p1to)
					break;	// lane1 finished. to Loop of 2 lanes
				// Update state variable (Like binary insertion sort)
				switch (state) {
				case 0x123:
					if (pred(*pos2, *pos1) == false)			// *pos1 <= *pos2
						; // No update state 
					else if (pred(*pos3, *pos1) == false)		// *pos1 <= *pos3
						state = 0x213;
					else
						state = 0x231;
					break;
				case 0x124:
					if (pred(*pos2, *pos1) == false)			// *pos1 <= *pos2
						; // No update state 
					else if (pred(*pos4, *pos1) == false)		// *pos1 <= *pos4
						state = 0x214;
					else
						state = 0x241;
					break;
				case 0x132:
					if (pred(*pos3, *pos1) == false)			// *pos1 <= *pos3
						; // No update state 
					else if (pred(*pos2, *pos1) == false)		// *pos1 <= *pos2
						state = 0x312;
					else
						state = 0x321;
					break;
				case 0x134:
					if (pred(*pos3, *pos1) == false)			// *pos1 <= *pos3
						; // No update state 
					else if (pred(*pos4, *pos1) == false)		// *pos1 <= *pos4
						state = 0x314;
					else
						state = 0x341;
					break;
				case 0x142:
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						; // No update state 
					else if (pred(*pos2, *pos1) == false)		// *pos1 <= *pos2
						state = 0x412;
					else
						state = 0x421;
					break;
				case 0x143:
					if (pred(*pos4, *pos1) == false) 			// *pos1 <= *pos4
						; // No update state 
					else if (pred(*pos3, *pos1) == false)		// *pos1 <= *pos3
						state = 0x413;
					else
						state = 0x431;
				}
			}
			else if (state < 0x300) {	//	state : [0x213, 0x243]
				// Get value from lane2 
				*posOut = std::move(*pos2);
				pos2++;
				if (pos2 >= p2to)
					break;	// lane1 finished. to Loop of 2 lanes
				// Update state variable (Like binary insertion sort)
				switch (state) {
				case 0x213:
					if (pred(*pos2, *pos1))					// *pos2 < *pos1
						; // No update state 
					else if (pred(*pos3, *pos2) == false)		// *pos2 <= *pos3
						state = 0x123;
					else
						state = 0x132;
					break;
				case 0x214:
					if (pred(*pos2, *pos1))					// *pos2 < *pos1
						; // No update state 
					else if (pred(*pos4, *pos2) == false)		// *pos2 <= *pos4
						state = 0x124;
					else
						state = 0x142;
					break;
				case 0x231:
					if (pred(*pos3, *pos2) == false)			// *pos2 <= *pos3
						; // No update state 
					else if (pred(*pos2, *pos1))				// *pos2 < *pos1
						state = 0x321;
					else
						state = 0x312;
					break;
				case 0x234:
					if (pred(*pos3, *pos2) == false)			// *pos2 <= *pos3
						; // No update state 
					else if (pred(*pos4, *pos2) == false)		// *pos2 <= *pos4
						state = 0x324;
					else
						state = 0x342;
					break;
				case 0x241:
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						; // No update state 
					else if (pred(*pos2, *pos1))				// *pos2 < *pos1
						state = 0x421;
					else
						state = 0x412;
					break;
				case 0x243:
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						; // No update state 
					else if (pred(*pos3, *pos2) == false)		// *pos2 <= *pos3
						state = 0x423;
					else
						state = 0x432;
				}
			}
			else if (state < 0x400) {	//	state : [0x312, 0x342]
				// Get value from lane3
				*posOut = std::move(*pos3);
				pos3++;
				if (pos3 >= p3to)
					break;	// lane1 finished. to Loop of 2 lanes
				// Update state variable (Like binary insertion sort)
				switch (state) {
				case 0x312:
					if (pred(*pos3, *pos1))					// *pos3 < *pos1
						; // No update state 
					else if (pred(*pos3, *pos2))				// *pos3 < *pos2
						state = 0x132;
					else
						state = 0x123;
					break;
				case 0x314:
					if (pred(*pos3, *pos1))					// *pos3 < *pos1
						; // No update state 
					else if (pred(*pos4, *pos3) == false)		// *pos3 <= *pos4
						state = 0x134;
					else
						state = 0x143;
					break;
				case 0x321:
					if (pred(*pos3, *pos2))					// *pos3 < *pos2
						; // No update state 
					else if (pred(*pos3, *pos1))				// *pos3 < *pos1
						state = 0x231;
					else
						state = 0x213;
					break;
				case 0x324:
					if (pred(*pos3, *pos2))					// *pos3 < *pos2
						; // No update state 
					else if (pred(*pos4, *pos3) == false)		// *pos3 <= *pos4
						state = 0x234;
					else
						state = 0x243;
					break;
				case 0x341:
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						; // No update state 
					else if (pred(*pos3, *pos1))				// *pos3 < *pos1
						state = 0x431;
					else
						state = 0x413;
					break;
				case 0x342:
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						; // No update state 
					else if (pred(*pos3, *pos2))				// *pos3 < *pos2
						state = 0x432;
					else
						state = 0x423;
				}
			}
			else {	//	state : [0x412, 0x432]
				// Get value from lane4
				*posOut = std::move(*pos4);
				pos4++;
				if (pos4 >= p4to)
					break;	// lane4 finished. to Loop of 2 lanes
				// Update state variable (Like binary insertion sort)
				switch (state) {
				case 0x412:
					if (pred(*pos4, *pos1))					// *pos4 < *pos1
						; // No update state 
					else if (pred(*pos4, *pos2))				// *pos4 < *pos2
						state = 0x142;
					else
						state = 0x124;
					break;
				case 0x413:
					if (pred(*pos4, *pos1))					// *pos4 < *pos1
						; // No update state 
					else if (pred(*pos4, *pos3))				// *pos4 < *pos3
						state = 0x143;
					else
						state = 0x134;
					break;
				case 0x421:
					if (pred(*pos4, *pos2))					// *pos4 < *pos2
						; // No update state 
					else if (pred(*pos4, *pos1))				// *pos4 < *pos1
						state = 0x241;
					else
						state = 0x214;
					break;
				case 0x423:
					if (pred(*pos4, *pos2))					// *pos4 < *pos2
						; // No update state 
					else if (pred(*pos4, *pos3))				// *pos4 < *pos3
						state = 0x243;
					else
						state = 0x234;
					break;
				case 0x431:
					if (pred(*pos4, *pos3))					// *pos4 < *pos3
						; // No update state 
					else if (pred(*pos4, *pos1))				// *pos4 < *pos1
						state = 0x341;
					else
						state = 0x314;
					break;
				case 0x432:
					if (pred(*pos4, *pos3))					// *pos4 < *pos3
						; // No update state 
					else if (pred(*pos4, *pos2))				// *pos4 < *pos2
						state = 0x342;
					else
						state = 0x324;
				}
			}
		}
		posOut++;
		state &= 0xff;

		// Loop of 2 lanes
		for (;; posOut++) {
			if (state < 0x20) {	//	state : [0x12, 0x14]
				// Get value from lane1
				*posOut = std::move(*pos1);
				pos1++;
				if (pos1 >= p1to)
					break;
				// Update state variable
				switch (state) {
				case 0x12:
					if (pred(*pos2, *pos1) == false)			// *pos1 <= *pos2
						; // No update state 
					else
						state = 0x21;
					break;
				case 0x13:
					if (pred(*pos3, *pos1) == false)			// *pos1 <= *pos3
						; // No update state 
					else
						state = 0x31;
					break;
				case 0x14:
					if (pred(*pos4, *pos1) == false)			// *pos1 <= *pos4
						; // No update state 
					else
						state = 0x41;
				}
			}
			else if (state < 0x30) {	//	state : [0x21, 0x24]
				// Get value from lane2 
				*posOut = std::move(*pos2);
				pos2++;
				if (pos2 >= p2to)
					break;
				// Update state variable
				switch (state) {
				case 0x21:
					if (pred(*pos2, *pos1))					// *pos2 < *pos1
						; // No update state 
					else
						state = 0x12;
					break;
				case 0x23:
					if (pred(*pos3, *pos2) == false)			// *pos2 <= *pos3
						; // No update state 
					else
						state = 0x32;
					break;
				case 0x24:
					if (pred(*pos4, *pos2) == false)			// *pos2 <= *pos4
						; // No update state 
					else
						state = 0x42;
				}
			}
			else if (state < 0x40) {	//	state : [0x31, 0x34]
				// Get value from lane3
				*posOut = std::move(*pos3);
				pos3++;
				if (pos3 >= p3to)
					break;
				// Update state variable
				switch (state) {
				case 0x31:
					if (pred(*pos3, *pos1))					// *pos3 < *pos1
						; // No update state 
					else
						state = 0x13;
					break;
				case 0x32:
					if (pred(*pos3, *pos2))					// *pos3 < *pos2
						; // No update state 
					else
						state = 0x23;
					break;
				case 0x34:
					if (pred(*pos4, *pos3) == false)			// *pos3 <= *pos4
						; // No update state 
					else
						state = 0x43;
				}
			}
			else {	//	state : [0x41, 0x43]
				// Get value from lane4
				*posOut = std::move(*pos4);
				pos4++;
				if (pos4 >= p4to)
					break;
				// Update state variable
				switch (state) {
				case 0x41:
					if (pred(*pos4, *pos1))					// *pos4 < *pos1
						; // No update state 
					else
						state = 0x14;
					break;
				case 0x42:
					if (pred(*pos4, *pos2))					// *pos4 < *pos2
						; // No update state 
					else
						state = 0x24;
					break;
				case 0x43:
					if (pred(*pos4, *pos3))					// *pos4 < *pos3
						; // No update state 
					else
						state = 0x34;
				}
			}
		}
		posOut++;
		state &= 0xf;

		// Processing of remaining lane
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
		//	Special treatment when the size of the array to be sorted is less than a certain number
		if (range < 10) {
			if (sourceIsEnable)
				std::move(from, to, out);

			insertionSort(out, out + range, pred);
			return;
		}

		// Separate to 4 lanes
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

		// Sort each lanes
		_mas4Sort(opos1, opos2, pos1, pred, !sourceIsEnable);
		_mas4Sort(opos2, opos3, pos2, pred, !sourceIsEnable);
		_mas4Sort(opos3, opos4, pos3, pred, !sourceIsEnable);
		_mas4Sort(opos4, outto, pos4, pred, !sourceIsEnable);

		// Merge each lanes
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
		for (RAI item = first; item < to; item++) {
			workVector.push_back(std::move(*item));
		}

		_mas4Sort(workVector.begin(), workVector.end(), first, pred, true);
	}

	/*
	 * mas4sort (4-way merge sort)
	 */
	template <class RAI> inline void mas4Sort(RAI first, RAI last)
	{
		mas4Sort(first, last, std::less<>());
	}
}
