ifeq ($(OS),Windows_NT)
  EXEEXT = .exe
endif

all: Mas4Sort$(EXEEXT) Mas4Sort3rd$(EXEEXT) MasSort$(EXEEXT) MergeSort$(EXEEXT) MergeSortNR$(EXEEXT) mmSort$(EXEEXT) MmsSort$(EXEEXT) QuickSort$(EXEEXT) StdSort$(EXEEXT) StdStableSort$(EXEEXT)

Mas4Sort$(EXEEXT): Mas4Sort.o Mas4Sort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o Mas4Sort$(EXEEXT) Mas4Sort.o SortBenchmark.o SortItem.o

Mas4Sort3rd$(EXEEXT): Mas4Sort3rd.o Mas4Sort3rd.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o Mas4Sort3rd$(EXEEXT) Mas4Sort3rd.o SortBenchmark.o SortItem.o

MasSort$(EXEEXT): MasSort.o MasSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MasSort$(EXEEXT) MasSort.o SortBenchmark.o SortItem.o

MergeSort$(EXEEXT): MergeSort.o MergeSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MergeSort$(EXEEXT) MergeSort.o SortBenchmark.o SortItem.o

MergeSortNR$(EXEEXT): MergeSortNR.o MergeSortNR.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MergeSortNR$(EXEEXT) MergeSortNR.o SortBenchmark.o SortItem.o

mmSort$(EXEEXT): mmSort.o mmSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o mmSort$(EXEEXT) mmSort.o SortBenchmark.o SortItem.o

MmsSort$(EXEEXT): MmsSort.o MmsSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o MmsSort$(EXEEXT) MmsSort.o SortBenchmark.o SortItem.o

QuickSort$(EXEEXT): QuickSort.o QuickSort.h InsertionSort.h SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o QuickSort$(EXEEXT) QuickSort.o SortBenchmark.o SortItem.o

StdSort$(EXEEXT): StdSort.o SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o StdSort$(EXEEXT) StdSort.o SortBenchmark.o SortItem.o

StdStableSort$(EXEEXT): StdStableSort.o SortBenchmarkSpec.h SortBenchmark.o SortItem.o
	g++ -Wall -O3 -lstdc++ -o StdStableSort$(EXEEXT) StdStableSort.o SortBenchmark.o SortItem.o


SortBenchmark.o: SortBenchmark.h SortBenchmarkSpec.h SortItem.h
	g++ -Wall -O3 -lstdc++ -c SortBenchmark.cpp

SortItem.o: SortItem.h
	g++ -Wall -O3 -lstdc++ -c SortItem.cpp

.cpp.o:
	g++ -Wall -O3 -lstdc++ -c $<
