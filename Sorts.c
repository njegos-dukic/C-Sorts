#include "SortsModule.h"
#include <Windows.h>

int main()
{
	// createMyCSV();
	printf("Number of movies being read: %d.\n\n", numberOfMovies);

	movie* movies = createList(numberOfMovies);
	readMoviesFromCSV(movies, "Movies.csv");
	
	movie* forShell = createCopyOfTheList(movies, 0, numberOfMovies);
	movie* forHeap = createCopyOfTheList(movies, 0, numberOfMovies);
	movie* forQuick = createCopyOfTheList(movies, 0, numberOfMovies);
	movie* forMerge = createCopyOfTheList(movies, 0, numberOfMovies);
	movie* forInsertion = createCopyOfTheList(movies, 0, numberOfMovies);
	movie* forBubble = createCopyOfTheList(movies, 0, numberOfMovies);
	movie* forSelection = createCopyOfTheList(movies, 0, numberOfMovies);

	clock_t start;
	clock_t end;

	// Quick Sort
	{
		start = clock();
		quickSort(forQuick, 0, numberOfMovies - 1);
		end = clock();
		printf("Time needed for Quick sort: %.2lf [ms].\n", (double)end - (double)start);
		saveListToFile(forQuick, "Output_Quick_Sort.csv");
	}

	// Merge Sort
	{
		start = clock();
		quickSort(forMerge, 0, numberOfMovies - 1);
		end = clock();
		printf("Time needed for Merge sort: %.2lf [ms].\n", (double)end - (double)start);
		saveListToFile(forMerge, "Output_Merge_Sort.csv");
	}

	// Shell Sort
	{
		start = clock();
		shellSort(forShell, numberOfMovies);
		end = clock();
		printf("Time needed for Shell sort: %.2lf [ms].\n", (double)end - (double)start);
		saveListToFile(forShell, "Output_Shell_Sort.csv");
	}

	// Heap Sort
	{
		start = clock();
		heapSort(forHeap, numberOfMovies);
		end = clock();
		printf("Time needed for Heap sort: %.2lf [ms].\n", (double)end - (double)start);
		saveListToFile(forHeap, "Output_Heap_Sort.csv");
	}

	// Selection Sort
	{
		start = clock();
		selectionSort(forSelection, numberOfMovies);
		end = clock();
		printf("Time needed for Selection sort: %.2lf [ms].\n", (double)end - (double)start);
		saveListToFile(forSelection, "Output_Selection_Sort.csv");
	}

	// Insertion Sort
	{
		start = clock();
		insertionSort(forInsertion, numberOfMovies);
		end = clock();
		printf("Time needed for Insertion sort: %.2lf [ms].\n", (double)end - (double)start);
		saveListToFile(forInsertion, "Output_Insertion_Sort.csv");
	}

	// Bubble Sort
	{
		start = clock();
		bubbleSort(forBubble, numberOfMovies);
		end = clock();
		printf("Time needed for Bubble sort: %.2lf [ms].\n\n", (double)end - (double)start);
		saveListToFile(forBubble, "Output_Bubble_Sort.csv");
	}

	printList(forBubble, numberOfMovies);
	// Deallocation
	{
		deallocateList(forShell, numberOfMovies);
		deallocateList(forHeap, numberOfMovies);
		deallocateList(forQuick, numberOfMovies);
		deallocateList(forMerge, numberOfMovies);
		deallocateList(forInsertion, numberOfMovies);
		deallocateList(forBubble, numberOfMovies);
		deallocateList(forSelection, numberOfMovies);
		deallocateList(movies, numberOfMovies);
	}

	printf("\n");
	system("PAUSE");

	return 0;
}
