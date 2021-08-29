#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXVAL 100000

//MergeSort functions
void merge(int *arr, int l, int m, int r);
void mergeSort(int *arr, int l, int r);

//QuickSort Functions
void quicksort(int* numbers, int low, int high);
int partition(int* vals, int low, int high);
void swap(int *a, int *b);

//Bubble Sort Functions
void bubbleSort(int* data, int n);

//Insertion Sort Functions
void insertionSort(int *arr, int n);

//Selection Sort Functions
void selectionSort(int *arr, int n);

//General functions
void printArray(int *arr, int size);
long timediff(clock_t t1, clock_t t2);
int *randArray(int *arr, int size);
int *arrayCopy(int *og, int *sorted, int size);
long timediff(clock_t t1, clock_t t2);

int main(){
	int sizes[] = {1000, 10000, 20000, 40000, 50000, 100000};
	//Array to test proper sorting.
//	int sizes[] = {20};
	int *originalArray;
	int *sortedArray;
	int i, j;
	
	srand(time(NULL));
	
	for (i = 0; i < 6; i++){
		originalArray = (int *)malloc(sizeof(int) * sizes[i]);
		sortedArray = (int *)malloc(sizeof(int) * sizes[i]);
		randArray (originalArray, sizes[i]);
		arrayCopy(originalArray, sortedArray, sizes[i]);
//printf("Original array.\n");
//printArray(originalArray, 20);
//printf("Sorted array.\n");
//printArray(sortedArray, 20);
		clock_t start, end;
	
		//Bubble Sort
//printf("sortedArray before Bubble.\n");
//printArray(sortedArray, 20);
		//start = time(0);
		start = clock();
		bubbleSort(sortedArray, sizes[i]);
		end = clock();
		//end = time(0);
//printf("SortedArray after Bubble.\n");
//printArray(sortedArray, 20);
		printf("Sorting %d values took %ld milli seconds for Bubble sort.\n\n", sizes[i], timediff(start, end));
		
		
		//Selection Sort
		arrayCopy(originalArray, sortedArray, sizes[i]);
//printf("SortedArray before Selection.\n");
//printArray(sortedArray, 20);
		start = clock();
		selectionSort(sortedArray, sizes[i]);
		end = clock();
//printf("SortedArray after Selection.\n");
//printArray(sortedArray, 20);
		printf("Sorting %d values took %ld milli seconds for Selection sort.\n\n", sizes[i], timediff(start, end));
		
		//Insertion Sort
		arrayCopy(originalArray, sortedArray, sizes[i]);
//printf("sortedArray before insertion.\n");
//printArray(sortedArray, 20);
		start = clock();
		insertionSort(sortedArray, sizes[i]);
		end = clock();
//printf("SortedArray after Selection.\n");
//printArray(sortedArray, 20);
		printf("Sorting %d values took %ld milli seconds for Insertion sort.\n\n", sizes[i], timediff(start, end));
		
		//Merge Sort
		arrayCopy(originalArray, sortedArray, sizes[i]);
//printf("sortedArray before merge.\n");
//printArray(sortedArray, 20);
		start = clock();
		mergeSort(sortedArray, 0, sizes[i] - 1);
		end = clock();
//printf("SortedArray after merge.\n");
//printArray(sortedArray, 20);
		printf("Sorting %d values took %ld milli seconds for Merge sort.\n\n", sizes[i], timediff(start, end));
		
		//Quick Sort
		arrayCopy(originalArray, sortedArray, sizes[i]);
//printf("sortedArray before insertion.\n");
//printArray(sortedArray, 20);
		start = clock();
		quicksort(sortedArray, 0, sizes[i] - 1);
		end = clock();
//printf("SortedArray after quick.\n");
//printArray(sortedArray, 20);
		printf("Sorting %d values took %ld milli seconds for Quick sort.\n", sizes[i], timediff(start, end));
		printf("\n--------------------------------------------------------\n");
	
		free(originalArray);
		free(sortedArray);
	}
	return 0;
}


void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // create temp arrays
    int L[n1], R[n2]; //if your compiler does not support this, create them dynamically.

    // Copy data to temp arrays L[] and R[] 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void quicksort(int* numbers, int low, int high) {

    // Only have to sort if we are sorting more than one number
    if (low < high) {
        int split = partition(numbers,low,high);
        quicksort(numbers,low,split-1);
        quicksort(numbers,split+1,high);
    }
}


// Pre-condition: low and high are valid indexes into values
// Post-condition: Returns the partition index such that all the values
//                 stored in vals from index low to until that index are
//                 less or equal to the value stored there and all the values
//                 after that index until index high are greater than that
//                 value.
int partition(int* vals, int low, int high) {

    int temp;
    int i, lowpos;

    // A base case that should never really occur.
    //if (low == high) return low;

    // Pick a random partition element and swap it into index low.
    i = low + rand()%(high-low+1);
    swap(&vals[low], &vals[i]);

	// Store the index of the partition element.
	lowpos = low;

	// Update our low pointer.
	low++;

	// Run the partition so long as the low and high counters don't cross.
	while (low <= high) {

		// Move the low pointer until we find a value too large for this side.
		while (low <= high && vals[low] <= vals[lowpos]) low++;

		// Move the high pointer until we find a value too small for this side.
		while (high >= low && vals[high] > vals[lowpos]) high--;

		// Now that we've identified two values on the wrong side, swap them.
		if (low < high)
		   swap(&vals[low], &vals[high]);
	}

	// Swap the partition element into it's correct location.
	swap(&vals[lowpos], &vals[high]);

	return high; // Return the index of the partition element.
}

// Swaps the values pointed to by a and b.
void swap(int *a, int *b) {
     int temp = *a;
     *a = *b;
     *b = temp;
}

void bubbleSort(int *arr, int n)
{
   int i, j,temp;
   for (i = 0; i < n-1; i++)
   {
        for (j = 0; j < n-i-1; j++)
        {

           if (arr[j] > arr[j+1])
           {//then swap
             temp=arr[j];
             arr[j]=arr[j+1];
             arr[j+1]=temp;
           }
        }
    }
}

void insertionSort(int *arr, int n)
{
    int i, item, j;
    for (i = 1; i < n; i++)
    {
         item = arr[i];

        // Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
          for(j=i-1; j>=0; j--)
          {
              if(arr[j]>item)
                arr[j+1] = arr[j];
              else
                break;

          }
          arr[j+1] = item;
    }
}

void selectionSort(int *arr, int n)
{
	int i, j, min_idx, temp;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 
		1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;
		// Swap the found minimum element with the first element
		temp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = temp;
	}
}

long timediff(clock_t t1, clock_t t2){
	long elapsed;
	elapsed = ((double)t2 - t1)	/ CLOCKS_PER_SEC * 1000;
	return elapsed;
}

int *randArray(int *arr, int size){
	int i;
	for (i = 0; i < size; i++){
		arr[i] = rand() % MAXVAL + 1;	
	}
	
	return arr;
}

int *arrayCopy(int *og, int *sorted, int size){
	int i;
	for (i = 0; i < size; i++){
		sorted[i] = og[i];
	}
	
	return og;
}

void printArray(int *arr, int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
