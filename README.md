# SortCPP
Sort Algorithm (C++)


This C++ library includes 3 sorting algorithms and you can see benchmarkings by running std::sort() and std::stable_sort().

## Mas4Sort.h
  4-way merge sort
  Four lanes (sub arrays) are controlled by one variable.
  Very many "if statements" that control four lanes. **Hentai** merge sort.
  Use work memory of the same size as the target array.
  Compared to a general merge sort, the number of memory transfers is about half.

## MasSort.h
  3-way merge sort
  Three lanes (sub arrays) are controlled by one variable.
  Many "if statements" that control three lanes. Hentai merge sort.
  Use work memory of the same size as the target array.

## mmSort.h
  Quicksort with improved "Median of 5 Quicksort" and reduced number of comparisons.
  **Not yet released.**
  Wait a moment.

## MmsSort.h
  Stable quicksort.
  Use work memory of the same size as the target array.

## MatSort.h
  Memory-saving merge sort.
  The work memory size can be reduced to 1 / M by dividing the original array into M subarrays and merging them one by one.
  The memory area and performance are a trade-off, but if M is fixed, the execution cost is O (N log N).
  **Not yet released.**
  Wait a moment.

*This source has been ported to C ++, an algorithm previously written in Java.*
(https://github.com/m-matsubara/sort)
