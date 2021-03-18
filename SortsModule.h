#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define numberOfMovies 100'000

struct movie
{
	double rating;
	char* title;
	int year;
	char* actors;
	char* genre;
};

void createMyCSV();
void readMoviesFromCSV(movie* movies, const char* file);
void shellSort(movie* movies, int n);
void heapify(movie* movies, int n, int i);
void heapSort(movie* movies, int n);
int partition(movie* movies, int low, int high);
void quickSort(movie* movies, int low, int high);
void merge(movie* movies, int l, int m, int r);
void mergeSort(movie* movies, int l, int r);
void insertionSort(movie* movies, int n);
void bubbleSort(movie* movies, int n);
void selectionSort(movie* movies, int n);
void printList(movie* movies, int n);
movie* createList(int n);
void deallocateList(movie* list, int n);
movie* createCopyOfTheList(movie* movies, int start, int end);
void saveListToFile(movie* list, const char* fileName);