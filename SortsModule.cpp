#include "SortsModule.h"

void createMyCSV()
{
	srand(time(0));
	FILE* outputFile;
	fopen_s(&outputFile, "Input.csv", "w");

	if (outputFile == NULL)
	{
		// fclose(outputFile);
		printf("Can't create initial .CSV faile.\n");
		exit(1);
	}

	fprintf(outputFile, "%s,%s,%s,%s,%s", "Rating", "Title", "Year", "Actors", "Genre\n");

	for (int i = 1; i <= numberOfMovies; i++)
		fprintf(outputFile, "%lf,%s%d,%d,%s%d,%c\n", (double)((rand() * 5376) % 1'000'000 / (double)1000), "Title", i, 2000 + rand() % 5, "Actors", i, 65 + rand() % 5);

	fclose(outputFile);
}

void readMoviesFromCSV(movie* movies, const char* file)
{
	FILE* inputFile;
	fopen_s(&inputFile, file, "r");

	if (inputFile == NULL)
	{
		// fclose(inputFile);
		printf("Unsuccessful file opening.\n");
		exit(1);
	}

	char* temp = (char*)calloc(sizeof(char), 256);
	fgets(temp, 256, inputFile); // Reading the top row and discarding.
	free(temp);

	for (int i = 0; i < numberOfMovies; i++)
	{
		char* lineBuffer = (char*)calloc(sizeof(char), 256);
		char* current;
		char* begginingOfTheBuffer = lineBuffer; // Keeping the address for further deallocation.

		fgets(lineBuffer, 256, inputFile);

		current = strtok_s(lineBuffer, ",", &lineBuffer);
		(movies + i)->rating = atof(current);

		current = strtok_s(lineBuffer, ",", &lineBuffer);
		strcpy_s((movies + i)->title, 128, current);

		current = strtok_s(lineBuffer, ",", &lineBuffer);
		(movies + i)->year = atoi(current);

		current = strtok_s(lineBuffer, ",", &lineBuffer);
		strcpy_s((movies + i)->actors, 128, current);

		current = strtok_s(lineBuffer, "\n", &lineBuffer);
		strcpy_s((movies + i)->genre, 128, current);

		free(begginingOfTheBuffer);
	}

	fclose(inputFile);
	return;
}

void shellSort(movie* movies, int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = gap; i < n; i++)
		{
			movie temp = *(movies + i);
			int j;
			for (j = i; j >= gap && (movies + j - gap)->rating > temp.rating; j -= gap)
				*(movies + j) = *(movies + j - gap);
			*(movies + j) = temp;
		}
	return;
}

void heapify(movie* movies, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && (movies + l)->rating >(movies + largest)->rating)
		largest = l;

	if (r < n && (movies + r)->rating >(movies + largest)->rating)
		largest = r;

	if (largest != i)
	{
		movie temp = *(movies + largest);
		*(movies + largest) = *(movies + i);
		*(movies + i) = temp;

		heapify(movies, n, largest);
	}
}

void heapSort(movie* movies, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(movies, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		movie temp = *(movies + 0);
		*(movies + 0) = *(movies + i);
		*(movies + i) = temp;

		heapify(movies, i, 0);
	}
}

int partition(movie* movies, int low, int high)
{
	movie pivot = *(movies + high);
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
		if ((movies + j)->rating < pivot.rating)
		{
			i++;
			movie temp = *(movies + i);
			*(movies + i) = *(movies + j);
			*(movies + j) = temp;
		}

	movie temp = *(movies + i + 1);
	*(movies + i + 1) = *(movies + high);
	*(movies + high) = temp;

	return (i + 1);
}

void quickSort(movie* movies, int low, int high)
{
	if (low < high)
	{
		int pi = partition(movies, low, high);
		quickSort(movies, low, pi - 1);
		quickSort(movies, pi + 1, high);
	}
}

void merge(movie* movies, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	movie* L = createList(n1);
	movie* R = createList(n2);

	for (i = 0; i < n1; i++)
		*(L + i) = *(movies + l + i);
	for (j = 0; j < n2; j++)
		*(R + j) = *(movies + m + 1 + j);

	i = 0; 
	j = 0;  
	k = l;  
	while (i < n1 && j < n2)
	{
		if ((L+i)->rating <= (R+j)->rating)
		{
			*(movies + k) = *(L + i);
			i++;
		}
		else
		{
			*(movies + k) = *(R + j);
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		*(movies + k) = *(L + i);
		i++;
		k++;
	}

	while (j < n2)
	{
		*(movies + k) = *(R + j);
		j++;
		k++;
	}

	deallocateList(L, n1);
	deallocateList(R, n2);
}	

void mergeSort(movie* movies, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(movies, l, m);
		mergeSort(movies, m + 1, r);
		merge(movies, l, m, r);
	}
}

void insertionSort(movie* movies, int n)
{
	int i, j;
	movie key;
	for (i = 1; i < n; i++)
	{
		key = *(movies + i);
		j = i - 1;

		while (j >= 0 && (movies+j)->rating > key.rating)
		{
			*(movies + j + 1) = *(movies + j);
			j = j - 1;
		}
		*(movies + j + 1) = key;
	}
}

void bubbleSort(movie* movies, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if ((movies + j)->year < (movies + j + 1)->year)
			{
				movie temp = *(movies + j + 1);
				*(movies + j + 1) = *(movies + j);
				*(movies + j) = temp;
			}

	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if ((movies + j)->year == (movies + j + 1)->year)
				if ((movies + j)->genre[0] > (movies + j + 1)->genre[0])
				{
					movie temp = *(movies + j + 1);
					*(movies + j + 1) = *(movies + j);
					*(movies + j) = temp;
				}
}

void selectionSort(movie* movies, int n)
{
	int i, j, min_idx;
	
	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if ((movies + j)->rating < (movies + min_idx)->rating)
				min_idx = j;

		movie temp = *(movies + i);
		*(movies + i) = *(movies + min_idx);
		*(movies + min_idx) = temp;
	}
}

void printList(movie* movies, int n)
{
	for (int i = 0; i < n; i++)
		printf("Rating: %.3lf\nTitle: %s\nYear: %d\nActors: %s\nGenre: %s\n\n", (movies + i)->rating, (movies + i)->title, (movies + i)->year, (movies + i)->actors, (movies + i)->genre);
}

movie* createList(int n)
{
	movie* returnList = (movie*)calloc(sizeof(movie), n);
	for (int i = 0; i < n; i++)
	{
		(returnList + i)->title = (char*)calloc(sizeof(char), 128);
		(returnList + i)->actors = (char*)calloc(sizeof(char), 128);
		(returnList + i)->genre = (char*)calloc(sizeof(char), 128);
	}

	return returnList;
}

void deallocateList(movie* list, int n)
{
	for (int i = 0; i < n; i++)
	{
		free((list + i)->title);
		free((list + i)->actors);
		free((list + i)->genre);
	}

	free(list);
	return;
}

movie* createCopyOfTheList(movie* movies, int start, int end)
{
	movie* returnList = createList(end - start);

	for (int i = 0; i < end - start; i++)
	{
		(returnList + i)->rating = (movies + start + i)->rating;
		strcpy_s((returnList + i)->title, 128, (movies + start + i)->title);
		(returnList + i)->year = (movies + i)->year;
		strcpy_s((returnList + i)->actors, 128, (movies + start + i)->actors);
		strcpy_s((returnList + i)->genre, 128, (movies + start + i)->genre);
	}

	return returnList;
}

void saveListToFile(movie* list, const char* fileName)
{
	FILE* outputFile;
	fopen_s(&outputFile, fileName, "w");

	if (outputFile == NULL)
	{
		fclose(outputFile);
		printf("Unsuccessful creating of output file.\n");
		exit(1);
	}

	fprintf(outputFile, "%s,%s,%s,%s,%s", "Rating", "Title", "Year", "Actors", "Genre\n");

	for (int i = 0; i < numberOfMovies; i++)
		fprintf(outputFile, "%f,%s,%d,%s,%s\n", (list + i)->rating, (list + i)->title, (list + i)->year, (list + i)->actors, (list + i)->genre);

	fclose(outputFile);
}