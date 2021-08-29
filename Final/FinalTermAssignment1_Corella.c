/* COP 3502C Final Term Assignment 1
This program is written by: Maria Corella */

#include<stdio.h>
#include<stdlib.h>

//Function Declarations
//Reads data from file and saves to variables and an array of coordinates. Returns a pointer to the array of coordinates.
int **readData(FILE *in, int *xcor, int *ycor, int *radius, int *poi);
//Filters the data from readData to only inlcude the coordinates within the circle. Returns a pointer to the array of coordinates.
int **filterData(int xcor, int ycor, int radius, int poi, int **coordinates, int *fpoi);
//Checks if the given coordinate is within the circle. Returns 1 if it is.
int withinCircle(int xcor, int ycor, int radius, int x, int y);
//Merge function. 
void merge(int **coordinates, int l, int m, int r);
//Merge sort function.
void mergeSort(int **coordinates, int l, int r);
//Function to print a 2D array.
void printArray(int **filteredCoordinates, int size);
//Searches if a given coordinate is in a list of coordinates. If found returns the index. If not found returns -1. If exit coordinate is entered, returns -999.
int searchPhase(int **filteredCoordinates, int fpoi);
//Uses binary search to search for a coordinate within a coordinate list. Returns index if a match is found, returns -1 otherwise.
int binarySearch(int **filteredCoordinates, int x, int y, int l, int h);

int main(){
	int xcor, ycor, radius, poi, fpoi, i;
	int **coordinates, **filteredCoordinates;
	 
	FILE *in;//Create input file pointer
	in = fopen("in.txt", "r");//Open file to read
	
	if (in == NULL){
		printf("in.txt was unable to open.\n");
	}
	else {
		//Call to read data from coordinate.txt.
		coordinates = readData(in, &xcor, &ycor, &radius, &poi);
		fclose(in);//Close in file.
	}

	//Call to filter read data.
	filteredCoordinates = filterData(xcor, ycor, radius, poi, coordinates, &fpoi);
	
	//Call to sort the filtered data.
	mergeSort(filteredCoordinates, 0, fpoi);
	
	//Print sorted and filtered array.
	printf("\nSorted array:\n");
	printArray(filteredCoordinates, fpoi + 1);
	
	FILE *out;//Create ouput file
	out = fopen("out.txt", "w");
	
	if (out == NULL){
		printf("Unable to open out.txt file.\n");
	}
	
	else{
		//Print data to output file.
		for (i = 0; i < fpoi + 1; i++){
			fprintf(out, "%d %d\n", filteredCoordinates[i][0], filteredCoordinates[i][1]);
		}
	}
	
	fclose(out);//Close output file.
	printf("Filtered and sorted data written to out.txt\n");

	//Ask for search coordinates in a loop until the exit coordinate is entered.	
	do {
		
	} while (searchPhase(filteredCoordinates, fpoi) != -999);
		
	//Free original coordinates x, y values.
	for(i = 0; i < poi; i++){
		free(coordinates[i]);
	}
	
	//Free array of original coordinates.
	free(coordinates);
	
	//Free filtered coordinates x, y values.
	for(i = 0; i < fpoi + 1; i++){
		free(filteredCoordinates[i]);
	}
	
	//Free array of filtered coordinates.
	free(filteredCoordinates);
	
	return 0;
}

int **readData(FILE *in, int *xcor, int *ycor, int *radius, int *poi){
	int i, j;
	
	fscanf(in, "%d %d %d %d\n", xcor, ycor, radius, poi);
	printf("Center of circle x: %d\nCenter of circle y: %d\nRadius: %d\nPairs of coordinates: %d\n", *xcor, *ycor, *radius, *poi);	
	
	//Allocate pointer to array. Rows. 
	int **array = malloc(*poi * sizeof(int *));
	
	//Allocate array to each array pointer. Columns.
	for (i = 0; i < *poi; i++){
		array[i] = malloc(2 * sizeof(int));
	}
	
	//Add data to the array of arrays.
	for (i = 0; i < *poi; i++){
		for(j = 0; j < 2; j++){
			fscanf(in, "%d", &array[i][j]);
		}
	}
	
	printf("\nData from array:\n");
	printArray(array, *poi);
	
	return array;
}

int **filterData(int xcor, int ycor, int radius, int poi, int **coordinates, int *fpoi){
	
	int x = -1, i;
	int tempCoordinates[100][2];//Temp array for points within the circle
	
	//Loop through the coordinate array
	for (i = 0; i < poi; i++){
		//If the coordinates are within the circle, copy data into temp array.
		if (withinCircle(xcor, ycor, radius, coordinates[i][0], coordinates[i][1])){
			tempCoordinates[++x][0] = coordinates[i][0];
			tempCoordinates[x][1] = coordinates[i][1];	
		}
	}
	
	//Allocate memory for the amount of coordinates within the circle.
	int **array = malloc((x + 1) * sizeof(int *));
	
	//Allocate memory for each coordinate within the circle.
	for (i = 0; i < x + 1; i++){
		array[i] = malloc(2 * sizeof(int *));
	}
	
	//Copy data from the temp array to the filtered array.
	for (i = 0; i < x + 1; i++){
		array[i][0] = tempCoordinates[i][0];
		array[i][1] = tempCoordinates[i][1];
	}
	
	//Print the list of filtered coordinates.
	printf("\nFiltered list:\n");
	printArray(array, x + 1);

	*fpoi = x; 
	
	return array;
}

int withinCircle(int xcor, int ycor, int radius, int x, int y){
	
	int xval, yval, r2;
	
	xval = (x - xcor) * (x - xcor);
	yval = (y - ycor) * (y - ycor);
	r2 = radius * radius;
	
	if (xval + yval <= r2)
		return 1;
	return 0;
}

void merge(int **coordinates, int l, int m, int r){
	
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	int L[n1][2], R[n2][2];//Creates temp arrays.
	
	for (i = 0; i < n1; i++){
        L[i][0] = coordinates[l + i][0];
        L[i][1] = coordinates[l + i][1];
    }
    for (j = 0; j < n2; j++){
        R[j][0] = coordinates[m + 1 + j][0];
        R[j][1] = coordinates[m + 1 + j][1];
    }
        
    i = 0; 
	j = 0; 
	k = l;
	
	while (i < n1 && j < n2){
		if (L[i][0] < R[j][0]){
			coordinates[k][0] = L[i][0];
			coordinates[k][1] = L[i][1];
			i++;
		}
		else if (L[i][0] == R[j][0]){
			if (L[i][1] <= R[j][1]){
				coordinates[k][0] = L[i][0];
				coordinates[k][1] = L[i][1];
				i++;		
			}
			else{
				coordinates[k][0] = R[j][0];
				coordinates[k][1] = R[j][1];
				j++;		
			}	
		}
		else{
			coordinates[k][0] = R[j][0];
			coordinates[k][1] = R[j][1];
			j++;
		}
		k++;
	}
	
	while (i < n1){
		coordinates[k][0] = L[i][0];
		coordinates[k][1] = L[i][1];
		i++;
		k++;
	}
	
	while (j < n2){
		coordinates[k][0] = R[j][0];
		coordinates[k][1] = R[j][1];
		j++;
		k++;	
	}	
}

void mergeSort(int **coordinates, int l, int r){
	if (l < r){
		int m = (l + r) / 2;
		mergeSort(coordinates, l, m);
		mergeSort(coordinates, m + 1, r);
		
		merge(coordinates, l, m, r);
	}	
}

void printArray(int **filteredCoordinates, int size){
	
	int i;
	for(i = 0; i < size; i++){
		printf("%d %d\n", filteredCoordinates[i][0], filteredCoordinates[i][1]);
	}
	printf("\n");
}

int searchPhase(int **filteredCoordinates, int fpoi){
	int x, y, i, result;
	printf("Search input (x y): ");
	scanf("%d %d", &x, &y);
	
	if (x == -999 || y == -999){
		printf("Output: exit\n");
		return -999;
	}
	
	result = binarySearch(filteredCoordinates, x, y, 0, fpoi);
	
	if (result == -1){
		printf("Output: Not found\n");
		return -1;
	}
	else{
		printf("Output: Found at record %d\n", result + 1);
		return 0;
	}	
}

int binarySearch(int **filteredCoordinates, int x, int y, int l, int h){
	int mid;
	
	while(l <= h){
		mid = (l + h) / 2;
		
		if (filteredCoordinates[mid][0] == x && filteredCoordinates[mid][1] == y)
			return mid;
		else if (filteredCoordinates[mid][0] == x && filteredCoordinates[mid][1] > y)
			h = mid - 1;
		else if (filteredCoordinates[mid][0] == x && filteredCoordinates[mid][1] < y)
			l = mid + 1; 
		else if (filteredCoordinates[mid][0] < x)
			l = mid + 1;
		else 
			h = mid - 1;
	}
	return -1;
}


