all: Mas4Sort.exe MasSort.exe MergeSort.exe MergeSortNR.exe mmSort.exe MmsSort.exe QuickSort.exe StdSort.exe StdStableSort.exe

Mas4Sort.exe: Mas4Sort.o Mas4Sort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o Mas4Sort.exe Mas4Sort.o SortBenchmark.o SortItem.o

MasSort.exe: MasSort.o MasSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MasSort.exe MasSort.o SortBenchmark.o SortItem.o

MergeSort.exe: MergeSort.o MergeSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MergeSort.exe MergeSort.o SortBenchmark.o SortItem.o

MergeSortNR.exe: MergeSortNR.o MergeSortNR.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MergeSortNR.exe MergeSortNR.o SortBenchmark.o SortItem.o

mmSort.exe: mmSort.o mmSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o mmSort.exe mmSort.o SortBenchmark.o SortItem.o

MmsSort.exe: MmsSort.o MmsSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MmsSort.exe MmsSort.o SortBenchmark.o SortItem.o

QuickSort.exe: QuickSort.o QuickSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o QuickSort.exe QuickSort.o SortBenchmark.o SortItem.o

StdSort.exe: StdSort.o SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o StdSort.exe StdSort.o SortBenchmark.o SortItem.o

StdStableSort.exe: StdStableSort.o SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o StdStableSort.exe StdStableSort.o SortBenchmark.o SortItem.o


SortBenchmark.o: SortBenchmark.h SortBenchmarkSpec.h SortItem.h
	g++ -Wall -O3 -lstdc++ -c SortBenchmark.cpp

SortItem.o: SortItem.h
	g++ -Wall -O3 -lstdc++ -c SortItem.cpp

.cpp.o:
	g++ -Wall -O3 -lstdc++ -c $<
