#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUM_LENGTH 8
#define ERROR_CODE_1 -1 //Invalid Input
#define ERROR_CODE_2 -2 //Input Overflow

void printArray(int array[], int length){
	
	for(int i = 0; i < length; i++){
		if(i < length - 1)
			printf("%d - ", array[i]);
		else
			printf("%d", array[i]);
	}
	
}

void bubbleSort(int array[], int length){
	
	int aux;
	
	for(int i = 0; i < length; i++){
		
		for(int j = 0; j < length - 1 - i; j++){
			
			if(array[j] > array[j + 1]){
				
				aux = array[j];
				
				array[j] = array[j + 1];
				array[j + 1] = aux;
				
			}
		}
		
	}
}

int insertionSort(int array[], int length){
	
	int aux;
	int j;
	
	for (int i = 1; i < length; i++) {
		
		aux = array[i];
		j = i - 1;

		while((j >= 0) && (aux < array[j])) {
			array[j + 1] = array[j];
			j--;
		}
		
		array[j + 1] = aux;
		
	}
}

int selectionSort(int array[], int length){
	
	int minPos;
	int aux;
	
	for(int i = 0; i < length - 1; i++){
		
		minPos = i;
		
		for(int j = i + 1; j < length; j++){
			
			if(array[j] < array[minPos])
				minPos = j;
			
		}
		
		aux = array[minPos];
		array[minPos] = array[i];
		array[i] = aux;
		
	}
	
}

void clearInput(char *tempString, int maxLength){
	
	char auxCharacter;
	int i = 0;
	int cleaningInput = 1;
	
	while(cleaningInput){ //Clear buffer
		auxCharacter = getchar(); //Discard each char from buffer
		
		if(auxCharacter == '\n' || auxCharacter == EOF){
			cleaningInput = 0;
		}
		else if(i < maxLength - 1){
			tempString[i] = auxCharacter;
			i++;
		}
	}

	tempString[i] = '\0';
	
}

int checkUserInput(){
	
	char num[MAX_NUM_LENGTH];
	char itoaAux[MAX_NUM_LENGTH]; // Help 'itoa' implementation to compare it's length
	
	if(fgets(num, MAX_NUM_LENGTH, stdin) == NULL){
		return ERROR_CODE_1;
	}
	else if(strchr(num, '\n') == NULL){
		clearInput(num, MAX_NUM_LENGTH);
		return ERROR_CODE_2;
	}
	else{
		num[strcspn(num, "\n")] = 0;
		if(strlen(num) != strlen(itoa(atoi(num), itoaAux, 10))) // Compare the string length with and without it's numbers - if there are any
			return ERROR_CODE_1;
		else
			return atoi(num);
	}
}

int algoSelection(){

	int userInputAlgo;
	int loop = 1;

	while(loop){
		
		printf("Select the algorithm\n"
				"0 - Quit\n"
				"1 - Bubble Sort\n"
				"2 - Selection Sort\n"
				"3 - Insertion Sort\n");
		
		userInputAlgo = checkUserInput();
		
		if(userInputAlgo < 0 || userInputAlgo > 3)
			printf("Invalid input\n\n");
		else
			return userInputAlgo;
		
	}
	
}

int createArray(int *array, int length){
	
	int attempt = 3;
	char num[MAX_NUM_LENGTH];
	int i = 0;
	char itoaAux[MAX_NUM_LENGTH]; // Help 'itoa' implementation to compare it's length
	
	while(i < length){
		
		if(attempt < 1)
			return 0;
		
		printf("Digite um numero: ");
		if(fgets(num, MAX_NUM_LENGTH, stdin) == NULL){
			attempt--;
			printf("Invalid. Remaining attemps: %d\n", attempt);
		}
		else if(strchr(num, '\n') == NULL){
			clearInput(num, MAX_NUM_LENGTH);
			attempt--;
			printf("Invalid. Input above max number length (6). Remaining attemps: %d\n", attempt);
		}
		else{
			num[strcspn(num, "\n")] = 0;
			if(strlen(num) != strlen(itoa(atoi(num), itoaAux, 10))){ // Compare the string length with and without it's numbers - if there are any
				attempt--;
				printf("Invalid. Input is not a number. Remaining attemps: %d\n", attempt);
			}
			else{
				array[i] = atoi(num);
				i++;
			}
			
		}
	}
	
	return 1;
	
}


int main(){

	int loop = 1;
	int algorithm;
	int length = 0;
	int *array;

	printf("Maximum number length: 6\nMaximum array length: 999999\n\n");

	while(loop){
		
		algorithm = algoSelection();
		
		switch(algorithm){
			
			case 0:
				loop = 0;
				break;
				
			case 1:
				printf("Size of array: ");
				length = checkUserInput();
				
				if(length < 0){
					printf("Invalid input");
				}
				else{
					array = malloc(sizeof(int) * length);
					if(createArray(array, length) == 0)
						printf("Array creation failed\n");
					else
						bubbleSort(array, length);
				}
				loop = 0;
				break;
				
			case 2:
				printf("Size of array: ");
				length = checkUserInput();
				
				if(length < 0){
					printf("Invalid input");
				}
				else{
					array = malloc(sizeof(int) * length);
					if(createArray(array, length) == 0)
						printf("Array creation failed\n");
					else
						insertionSort(array, length);
				}
				loop = 0;
				break;

			case 3:
				printf("Size of array: ");
				length = checkUserInput();
				
				if(length < 0){
					printf("Invalid input");
				}
				else{
					array = malloc(sizeof(int) * length);
					if(createArray(array, length) == 0)
						printf("Array creation failed\n");
					else
						selectionSort(array, length);
					
				}
				loop = 0;
				break;
			
		}
		
	}
	
	if(length > 0)
		printArray(array, length);
	
	free(array);
	array = NULL;
	
	return 0;
	
}
