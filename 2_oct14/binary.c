#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 10000

//Define the counter which counts the step of searching
int counter = 0;

//Create the recursive function binarysearch
int binarysearch(int list[], int value, int lindex, int rindex){
    //define the middle value of the sorted list
    int middle = lindex + (rindex - lindex)/2;

    //if the middle value is same as the key, then directly return the middle value
    if (list[middle] == value){
        counter++;
        return middle;
    }

    //if not, repeat the same procedure until the middle value is equal to the key
    else if (list[middle] < value){
        counter++;
        return binarysearch(list, value, middle + 1, rindex);
    }
    else {
        counter++;
        return binarysearch(list, value, lindex, middle - 1);
    }
}

int main(){
    //allocate the memory for the list that will be used for conducting binary search
    int* list = (int*) malloc(sizeof(int) * MAX_VALUE);

    //create a sorted list contains all integers from 1 to max value defined above
    int num = 1;
    for(int i = 0; i < MAX_VALUE; i++){
        list[i] = num;
        printf("%d ",num);
        num++;
    }
    printf("\n");
    
   
    //store user input as the key
    int key;
    printf("key? ");
    scanf("%d", &key);
	
    //if user input is not in the range, then abort
    if (key < 1 || key > MAX_VALUE){
        printf("Out of range");
        exit(0);
    }
        
    //conduct binary search for the key, and print out the step
    binarysearch(list,list[key - 1],0,MAX_VALUE - 1);
    printf("Found (step = %d)\n", counter);
    
    return 0;
}
