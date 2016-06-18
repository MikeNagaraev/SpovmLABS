#include <stdio.h>
#include <stdlib.h>

struct block{
	void* ptr;
	int size;
};

void initialize();
void** myMalloc(int);
void memOut(char*);
void myFree(void**);
void deletePool(int);
void defrag(int, block);

char mem[16];
int available = sizeof(mem);
int poolsCounter;
block pools[10];

int main(){
	initialize();
	memOut("Begin");
	int **number = (int**)myMalloc(sizeof(int));
	**number = 10;
	memOut("number = malloc sizeof(int)");
	myFree((void**)number);
	memOut("number = free");
	int **number_0 = (int**)myMalloc(sizeof(int));
	**number_0 = 15;
	memOut("number_0 = malloc sizeof(int)");
	char **symbols = (char**)myMalloc(sizeof(char) * 2);
	**symbols = '1';
 	memOut("symbols = malloc sizeof(char)*2");
	myFree((void**)number_0);
	memOut("number_0 = free");
	myFree((void**)symbols);
	memOut("symbols = free");
	int **number_2 = (int**)myMalloc(sizeof(int));
	**number_2 = 20;
	memOut("number_2 = malloc sizeof(int)");
	double **dnumber = (double**)myMalloc(sizeof(double));
	**dnumber = 1.123;
	memOut("dnumber = malloc sizeof(double)");
	myFree((void**)number_2);
	memOut("number_0 = free");
	myFree((void**)dnumber);
	memOut("dnumber = free");
	number_0 = (int**)myMalloc(sizeof(int)*3);
	**number_0 = 15;
	memOut("number_0 = malloc sizeof(int)*3");
	symbols = (char**)myMalloc(sizeof(char) * 3);
	**symbols = '1';
	memOut("symbols = malloc sizeof(char)*3");
	myFree((void**)symbols);
	memOut("symbols = free");
	myFree((void**)number_0);
	memOut("number_0 = free");
	dnumber = (double**)myMalloc(sizeof(double));
	**dnumber = 1.000;
	memOut("dnumber = malloc sizeof(double)");
	number_2 = (int**)myMalloc(sizeof(int));
	**number_2 = 20;
	memOut("number_2 = malloc sizeof(int)");
	symbols = (char**)myMalloc(sizeof(char) * 2);
	**symbols = '1';
	memOut("symbols = malloc sizeof(char)*2");
	myFree((void**)symbols);
	memOut("symbols = free");
	myFree((void**)dnumber);
	memOut("dnumber = free");
	myFree((void**)number_2);
	memOut("number_2 = free");
	return 0;
}

void initialize(){
	pools[0].size = available;
	pools[0].ptr = &mem[0];
	poolsCounter = 1;
}

void** myMalloc(int size){
	if (size > available){ 
		printf("Not enough memory\n");
		exit(0);
	}

	int indexOfEmptyBlock = 0;

	pools[poolsCounter].ptr = pools[indexOfEmptyBlock].ptr;
	pools[poolsCounter].size = size;
	poolsCounter++;
	available -= size;
	pools[indexOfEmptyBlock].ptr = &mem[sizeof(mem) - available];
	pools[indexOfEmptyBlock].size -= size;

	return &pools[poolsCounter - 1].ptr;
}

void memOut(char* message){
	printf("%s: ", message);
	for (int i = 1; i < poolsCounter; i++){
		char *temp = (char*)pools[i].ptr;
		for (int j = 0; j < pools[i].size; j++){
			printf("%d ", temp[j]);
		}
	}
	for (int i = 0; i < available; i++){
		printf("_ ");
	}
	printf("\n");
}

void myFree(void **deletePart){
	for (int i = 0; i < poolsCounter; i++){
		if (*deletePart == pools[i].ptr){
			block temp = pools[i];
			pools[0].size += pools[i].size;
			available += pools[i].size;
			deletePool(i);
			poolsCounter--;
			defrag(i, temp);
		}
	}
}

void deletePool(int index){
	int deleteSize = pools[index].size;
	for (int i = index; i < poolsCounter - 1; i++){
		pools[i + 1].ptr = pools[i].ptr;
		pools[i] = pools[i + 1];
	}
	char* tempPtr = (char*)pools[0].ptr;
	pools[0].ptr = &tempPtr[-deleteSize];
}

void defrag(int index, block temp){
	char *tempPtr = (char*)temp.ptr;
	int j = 0;
	for (;; j++){
		if (&mem[j] == tempPtr) break;
	}
	for (int i = 0; i < sizeof(mem) - (j  + temp.size); i++){
		*(tempPtr + i) = *(tempPtr + temp.size + i);
	}
}