#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OBJECT_LENGTH 20
#define ERROR_CODE_1 "-1" //Input error
#define ERROR_CODE_2 "-2" //Char overflow


struct GenericList{
	
	char *object;
	struct GenericList *next;
	
};

void clearInput(char *tempString, int maxLength){
	
	char auxCharacter;
	int i = 0;
	int cleaningInput = 1;
	
	while(cleaningInput){ //Clear buffer
		auxCharacter = getchar();
		
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

char *getInput(){ //User input
	
	char *objectName = malloc(sizeof(char) * OBJECT_LENGTH);
	
	if(fgets(objectName, OBJECT_LENGTH, stdin) == NULL){
		printf("Input error\n");
		return ERROR_CODE_1;
	}
	else if(strchr(objectName, '\n') == NULL){
		printf("Char overflow\n");
		clearInput(objectName, OBJECT_LENGTH);
		return ERROR_CODE_2;
	}
	
	objectName[strcspn(objectName, "\n")] = 0;
	
	if(objectName[0] == '\0'){
		printf("Input is empty\n");
		return ERROR_CODE_1;
	}
	
	return objectName;
	
}

void searchObject(struct GenericList *currentList, char *objectName){
	
	int position = 0;
	
	do{
		if(currentList == NULL){
			printf("The list is empty\n\n");
			position = -1;
		}
		else if(strcmp(currentList -> object, objectName) == 0){
			printf("Object found at position %d\n\n", position);
			position = -1;
		}
		else{
			currentList = currentList -> next;
			position++;
		}
	}
	while(currentList != NULL && position != -1);
	
	free(objectName);
	if(position != -1)
		printf("Object not found\n\n");

}

void insertObject(struct GenericList **currentList, char *objectName){

	struct GenericList *aux = *currentList;
	
	struct GenericList *temp = malloc(sizeof(struct GenericList));
	temp -> object = malloc(sizeof(char) * OBJECT_LENGTH);
	temp -> next = NULL;

	strcpy(temp -> object, objectName);
	
	if(*currentList == NULL){
		*currentList = temp;
	}
	else{
		while(aux -> next != NULL)
			aux = aux -> next;
		
		aux -> next = temp;
	}
	
	free(objectName);
	
}

void removeObject(struct GenericList **currentList, char *objectName){
	
	struct GenericList *aux = *currentList;
	struct GenericList *temp = NULL;
	int loop = 1;

	do{
		
		if(*currentList == NULL){
			printf("The list is empty\n\n");
			loop = 0;
		}
		else if(strcmp((*currentList) -> object, objectName) == 0){
			printf("Object removed\n\n");
			temp = *currentList;
			*currentList  = (*currentList) -> next;
			free(temp);
			loop = 0;
		}
		else if(aux -> next != NULL && strcmp(aux -> next -> object, objectName) == 0){
			printf("Object removed\n\n");
			temp = aux -> next;
			aux -> next = aux -> next -> next;
			free(temp);
			loop = 0;
		}
		else if(aux -> next != NULL){
			aux = aux -> next;
		}
	}
	while(loop == 1 && aux -> next != NULL);

	free(objectName);
	if(loop == 1)
		printf("Object not found\n\n");

}

void showObject(struct GenericList *currentList){
	
	if(currentList == NULL){
		printf("The list is empty");
	}
	else{
		do{
			printf("%s -> ", currentList -> object);
			currentList = currentList -> next;
		}
		while(currentList != NULL);
	}
	
	printf("\n\n");
	
}

int main(){
	
	char objectName[OBJECT_LENGTH];
	struct GenericList *linkedObjects = NULL;
	
	char menuChoice[3];
	
	while(1){
		
		printf("Select a function\n" 
		"0 - Exit\n"
		"1 - Search\n"
		"2 - Insert\n"
		"3 - Remove\n"
		"4 - Show list\n");
		
		if(fgets(menuChoice, 3, stdin) == NULL)
			printf("Try again\n");

		else if(strchr(menuChoice, '\n') == NULL){
			printf("Invalid input\n");
			clearInput(menuChoice, 3);
		}
		
		else{

			menuChoice[strcspn(menuChoice, "\n")] = 0;
			
			switch(atoi(menuChoice)){
				
				case 0:
					exit(0);
					break;
				case 1:
					printf("Name the object you want to search: ");
					searchObject(linkedObjects, getInput());			
					break;
				case 2:
					printf("Name the object to be inserted: ");
					strcpy(objectName, getInput());
					if(strcmp(objectName, ERROR_CODE_1) == 0 || strcmp(objectName, ERROR_CODE_2) == 0){
						printf("Try again \n\n");
					}
					else{
						printf("Object successfully inserted\n\n");
						insertObject(&linkedObjects, objectName);
					}
					break;
				case 3:
					printf("Name the object to be removed: ");
					strcpy(objectName, getInput());
					if(strcmp(objectName, ERROR_CODE_1) == 0|| strcmp(objectName, ERROR_CODE_2) == 0){
						printf("Try again \n\n");
					}
					else{
						removeObject(&linkedObjects, objectName);
					}
					break;
				case 4:
					showObject(linkedObjects);
					break;
			}
			
		}
		
	}

	return 0;
	
}
