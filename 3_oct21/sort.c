#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define the maximum number of items in the list that will conduct sorting algorithms
#define MAX_VALUE 100

//Function to initiate array A[] with random integers in the range between 1 (inclusive) to MAX_VALUE (inclusive) that defined above
void initarr(int A[]){
    srand((unsigned)time(NULL));
    for (int i = 0; i < MAX_VALUE; i++){
	A[i] = rand() % MAX_VALUE + 1;
    }
}

//Function to print out the array A[] from index 0 to index max
void printarr(int A[],int max){
    for (int i = 0; i < max; i++){
	printf("%d ", A[i]);
    }
    printf("\n");
}

//Function to swap two items in the array
void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

//Main Function to conduct insertion sort for array[]
int insertionsort(int A[]){
    //sort from left (i is key)
    for (int i = 1; i < MAX_VALUE; i++){
	//check indexes that is on the left of the key i
	for (int j = i - 1; j >= 0; j--){
	    //swap if the item on the left is bigger than the key
	    if(A[j] > A[j + 1]){
		swap(&A[j], &A[j + 1]);
	    }
	    //if not then move on to the next key
	    else break;
	}
    }
    return *A;
}

//Function to determine the patrition for quick sort
int patrition(int A[], int l, int r){
    //set the last element as the pivot
    int p = A[r];
    //define i as the item will be right before the patrition (the last item of the part that is less than A[r] )
    int i = l - 1;
    //sort from A[l] to A[r - 1]
    for(int j = l; j <= r - 1; j++){
	//if the item is larger than pivot, increment i and swap A[i] and A[j]
	if(A[j] <= p){
	    i++;
	    swap(&A[i],&A[j]);
	}
    }
    //Finally swap the item after i (the position that is right after the part that smaller than pivot) and pivot
    swap(&A[i + 1],&A[r]);
    //return the position of pivot
    return i + 1;
}

//Main Function to conduct quick sort for array[]
void quicksort(int A[], int l, int r){
    //find the patrition when l is smaller than r
    if(l < r){
	int q = patrition(A,l,r);
	//do quicksort fot both smaller part and larger part
	quicksort(A,l,q - 1);
	quicksort(A,q + 1,r);
    }
}

//Function to get the range of array[] (the difference between the maximum value in the array and the minimum value in the array)
int getrange(int A[]){
    //define maximum value in the array to max, and minimum value in the array to min
    int max,min;
    //compare index 0 and index 1 first, the larger one is temporary max, and the smaller one is temporary min
    if(A[1] > A[0]){
	max = A[1];
	min = A[0];
    }
    else{
	max = A[0];
	min = A[1];
    }
    //from index 2 to index MAX_VALUE - 1, set max to any value that is larger than temporary max, and same for the min
    for(int i = 2; i < MAX_VALUE; i++){
	if(A[i] > max){
	    max = A[i];
	}
	else if(A[i] < min){
	    min = A[i];
	}
    }
    //return the difference between max and min as the range
    return max - min;
}

//Main Function to conduct quick sort for array[], with the range
int countsort(int A[], int range){
    //define diff which is range + 1 (number of items in the count array)
    int diff = range + 1;
    //define the output array contains sortted A[] using count sort
    int output[MAX_VALUE];
    //define the count array
    int count[diff];
    //find the minimum value of A[] to use as offset, and initiate all items in output array to 0
    int min = A[0];
    for(int i = 0; i < MAX_VALUE; i++){
	if(A[i] < min){
	    min = A[i];
	}
	output[i] = 0;
    }
    //initiate all items in count array to 0
    for(int i = 0; i < diff; i++){
	count[i] = 0;
    }
    //increment corresponding index in count array
    for(int j = 1; j <= MAX_VALUE; j++){
	count[A[j - 1] - min]++;
    }
    //sum up the adjacent index in count array
    for(int i = 1; i <= diff; i++){
	count[i] += count[i - 1];
    }
    //locate A[j] on the correct place of output array
    for(int j = MAX_VALUE - 1; j >= 0; j--){
	output[count[A[j] - min] - 1] = A[j];
	count[A[j] - min]--;
    }
    //replace A[] to sorted output array
    for(int i = 0; i < MAX_VALUE; i++){
	A[i] = output[i];
    }
    //return the pointer of A[]
    return *A;
}

//main function to conduct i can't believe it can sort for array[]
void icantbelieveitcansort(int A[]){
    for(int i = 0; i < MAX_VALUE; i++){
	for(int j = 0; j < MAX_VALUE; j++){
	    if (A[i] < A[j]){
		swap(&A[i],&A[j]);
	    }
	}
    }
}

int main(void) {
    //define the time for calculating the cost of search (commented out in default)
    //clock_t start_t, end_t, total_t;
    //define the array a[] and initiate it with random integers in the range between 1 (inclusive) to MAX_VALUE (inclusive) that defined above
    //int* a = (int*) malloc(sizeof(int) * MAX_VALUE);
    int a[MAX_VALUE];
    initarr(a);
    //print out the array a[] before sorting
    printf("The array before sorting is: \n");
    printarr(a,MAX_VALUE);
    //define the time here as the start of sorting and print it out (commented out in default)
    //start_t = clock();
    //printf("Begin sorting, start_t = %ld\n", start_t);
    //conduct sorting algorithms (commented out in default)
    //insertionsort(a);
    //quicksort(a,0,MAX_VALUE - 1);
    //countsort(a,getrange(a));
    //icantbelieveitcansort(a);
    //define the time here as the end of sorting and print it out (commented out in default)
    //end_t = clock();
    //printf("End of sort, end_t = %ld\n", end_t);
    //define the total time as the difference of end time and start time and print it out (commented out in default)
    //total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
    //printf("Total time is %lu seconds\n", total_t);
    //print out the array a[] after sorting
    printf("The array after sorting is: \n");
    printarr(a,MAX_VALUE);
}
