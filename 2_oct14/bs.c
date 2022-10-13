#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bs(int list[], int value, int lindex, int rindex){
	int middle = lindex + (rindex - lindex)/2;
	if (list[middle] == value){
		return middle;
	}
	else if (list[middle] < value){
		return binarysearch(list, value, middle + 1, rindex);
	}
	else {
		return binarysearch(list, value, lindex, middle - 1);
	}
}

int main(){
	//clock_t start_t, end_t, total_t;
	int val = 0;
	int* list = (int*) malloc(sizeof(int) * 10000000);
	srand(time(NULL));
	for(int i = 0; i < 10000000; i++){
		int num = rand() % 10 + 1;
		val += num;
		list[i] = val;
	}
	
	//start_t = clock();
	//printf("Begin of the search, start_t = %ld\n", start_t);
	for(int j = 0; j < 10000000; j++){
		bs(list, list[j], 0, 9999999);
		printf("The index of number \"%d\" is %d\n", list[j], binarysearch(list, list[j], 0, 9999999));
	}
	//end_t = clock();
	//printf("End of search, end_t = %ld\n", end_t);
	//total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	//printf("Total time is %lu seconds\n", total_t);
}
