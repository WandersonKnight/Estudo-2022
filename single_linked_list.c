#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OBJECT_LENGTH 20

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
		return "Input error";
		
	}
	else if(strchr(objectName, '\n') == NULL){
		printf("Char overflow\n");
		clearInput(objectName, OBJECT_LENGTH);
		return "Char overflow";
	}
	
	objectName[strcspn(objectName, "\n")] = 0;

	return objectName;
	
}

int searchObject(struct GenericList *currentList, char *objectName){
	
	int position = 0;
	
	do{
		if(currentList == NULL){
			free(objectName);
			return -1;
		}
		else if(strcmp(currentList -> object, objectName) == 0){
			free(objectName);
			return position;
		}
		else{
			currentList = currentList -> next;
			position++;
		}
	}
	while(currentList -> next != NULL);
	
	free(objectName);
	return -1;
	
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

int removeObject(struct GenericList **currentList, char *objectName){
	
	struct GenericList *aux = *currentList;
	struct GenericList *temp = NULL;
	
	do{
		if(*currentList == NULL){
			return -1;
		}
		else if(strcmp((*currentList) -> object, objectName) == 0){
			temp = *currentList;
			*currentList  = (*currentList) -> next;
			free(temp);
			free(objectName);
			return 1;
		}
		else if(aux -> next != NULL && strcmp(aux -> next -> object, objectName) == 0){
			temp = aux -> next;
			aux -> next = aux -> next -> next;
			free(temp);
			free(objectName);
			return 1;
		}	
		aux = aux -> next;
	}
	while(aux -> next != NULL);

	free(objectName);
	return -1;
	
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

			int position;
			
			switch(atoi(menuChoice)){
				
				case 0:
					exit(0);
					break;
				case 1:
					printf("Name the object you want to search: ");
					position = searchObject(linkedObjects, getInput());
					if(position == -1)
						printf("Object not found\n\n");
					else
						printf("Object found at position %d\n\n", position);
					break;
				case 2:
					printf("Name the object to be inserted: ");
					strcpy(objectName, getInput());
					if(strcmp(objectName, "Char overflow") == 0 || strcmp(objectName, "Input error") == 0){
						printf("Try again \n\n");
					}
					else{
						printf("Object successfully inserted\n\n");
						insertObject(&linkedObjects, objectName);
					}
					break;
				case 3:
					printf("Name the object to be removed: ");
					if(removeObject(&linkedObjects, getInput()) == -1)
						printf("Object not found\n\n");
					else
						printf("Object removed\n\n");
					break;
				case 4:
					showObject(linkedObjects);
					break;
			}
			
		}
		
	}

	return 0;
	
}