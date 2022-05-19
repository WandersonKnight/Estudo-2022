#include <stdlib.h>
#include <stdio.h>

void swap(int array[], int posA, int posB){
	
	int aux = array[posA];
	array[posA] = array[posB];
	array[posB] = aux;

}

void medianPivot(int array[], int first, int last){
	
	int middle = first + ((last - first) / 2);

	if(array[first] > array[middle])
		swap(array, first, middle);
	
	if(array[middle] > array[last])
		swap(array, middle, last);
	
	if(array[first] > array[middle])
		swap(array, first, middle);
	
	swap(array, middle, last);
	
	printf("%d - %d - %d\n", array[first], array[middle], array[last]);
	
}

int partition(int array[], int first, int last){

	if(last - first >= 3)
		medianPivot(array, first, last);

	int pivot = array[last];
	int low = first;
	int high = last - 1;
	
	while(low <= high){
		
		while(array[low] < pivot)
			low++;
		while(array[high] >= pivot)
			high--;
		if(low <= high){
			swap(array, low, high);
			low++;
			high--;
		}
		
	}
	
	swap(array, low, last);
	
	return low;
	
}

void quickSortRecursive(int array[], int first, int last){
	
	if(first < last){

		int pivot = partition(array, first, last);
		quickSortRecursive(array, first, pivot - 1);
		quickSortRecursive(array, pivot + 1, last);
		
	}
	
}

void quickSort(int array[], int length){
	
	quickSortRecursive(array, 0, length - 1);
	
}

int main(){
	
	int *array[20] = {92, 98, 57, 97, 90, 30, 38, 33, 77, 13, 41, 16, 12, 48, 71, 45, 63, 51, 64, 6};
	
	quickSort(array, 20);
	
	for(int i = 0; i < 20; i++)
		printf("%d - ", array[i]);

	return 0;
	
}
