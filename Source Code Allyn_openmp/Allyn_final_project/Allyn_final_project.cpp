// Allyn_final_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

/* Structure of coordinates */
#define N 1048576 // number of houses

/*
void swap(double *xp, double *yp) {
	double temp = *xp;
	*xp = *yp;
	*yp = temp;
}
*/
/* Function to sort array */
/*
void selectionSort(struct coordinate arr[], int n) {
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j].distance < arr[min_idx].distance)
				min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx].distance, &arr[i].distance);
	}
}
*/
/* Function to print an array 
void printArray(struct coordinate arr[], int size) {
	int i;
	for (i = 0; i < size; i++)
		printf("%f ", arr[i].distance);
	printf("\n");
}
*/
// Driver program to test above functions
int main() {
	struct coordinate {
		int house_ID;
		int x, y;
		double distance; // distance from house to train station
	};
	struct coordinate house[N];
	struct coordinate trainStation;

	srand(time(0));

	omp_set_num_threads(4);

	double min_val = 100000;
	int i;

	double start;
	double end;

	trainStation.x = 2;
	trainStation.y = 2;

	// x and y arrays for house coordinates
	int x_arr[N];
	int y_arr[N];

	// fill house coordinates with random number
	start = omp_get_wtime();
#pragma omp parallel for
	for (i = 0; i < N; i++) {
		x_arr[i] = rand() % 100000;
		y_arr[i] = rand() % 100000;
	}

	// Set Train Station coordinate.
	

	
#pragma omp parallel for
	for (i = 0; i < N; i++) {
		//set x, y coordinate of house i
		house[i].house_ID = i;
		house[i].x = x_arr[i];
		house[i].y = y_arr[i];

		//calculate distance of house i from the trainStation
		//distance = sqrt((x1-x2)^2 + (y1-y2)^2)
		house[i].distance = sqrt(
			(house[i].x - trainStation.x) * (house[i].x - trainStation.x)
			+ (house[i].y - trainStation.y)
			* (house[i].y - trainStation.y));
	}

	int closestHouseID;

#pragma omp parallel for
	for( i = 0; i < N; i++)
	{
	//printf("thread id = %d and i = %d\n", omp_get_thread_num(), i);
	if(house[i].distance < min_val)
	{
	min_val = house[i].distance;
	closestHouseID = i;
	}
	}
	end = omp_get_wtime();

	double elapsed_time = end - start;
	

	printf("\nClosest house is %f units away\n", min_val);
	printf("Closest house ID = %d\n", closestHouseID);

	printf("For %d houses...", N);

	printf("\nElapsed time = %f sec. time.\n", elapsed_time);
	

	//Selection sort houses
	//selectionSort(house, N);
	//printf("Sorted array: \n");
	//printArray(house, N);
	return 0;
}

