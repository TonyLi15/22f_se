#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Create the recursive function binarysearch
int binarysearch(int list[], int value, int lindex, int rindex){
    //define the middle value of the sortted list
    int middle = lindex + (rindex - lindex)/2;
	
    //if the middle value is same as the key, then directly return the middle value
    if (list[middle] == value){
	return middle;
    }

    //if not, repeat the same procedure until the middle value is equal to the key
    else if (list[middle] < value){
	return binarysearch(list, value, middle + 1, rindex);
    }
    else {
	return binarysearch(list, value, lindex, middle - 1);
    }
}

int main(){
    //clock_t start_t, end_t, total_t;
	
    //allocate the memory for the list that will be used for conducting binary search
    int* list = (int*) malloc(sizeof(int) * 10000000);
	
    //define the value 0 for index 0 of the list
    int val = 0;
	
    //define number which is a random integer between 1 and 10 and add it to the pervious value to create the value of the next index in the list
    srand(time(NULL));
    for(int i = 0; i < 10000000; i++){
    	int num = rand() % 10 + 1;
	val += num;
	list[i] = val;
    }
	
    //start_t = clock();
    //printf("Begin of the search, start_t = %ld\n", start_t);
	
    //conduct binary search for all indexes of the list
    for(int j = 0; j < 10000000; j++){
	binarysearch(list, list[j], 0, 9999999);
	printf("The index of number \"%d\" is %d\n", list[j], binarysearch(list, list[j], 0, 9999999));
    }
	
    //end_t = clock();
    //printf("End of search, end_t = %ld\n", end_t);
    //total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
    //printf("Total time is %lu seconds\n", total_t);
}
