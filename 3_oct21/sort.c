#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 100

void initarr(int A[]){
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX_VALUE; i++){
		A[i] = rand() % MAX_VALUE + 1;
	}
}

void printarr(int A[],int max){
	for (int i = 0; i < max; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
}

void swap(int *a, int *b){
	int t = *a;
	*a = *b;
	*b = t;
}

int insertionsort(int A[]){
	for (int i = 1; i < MAX_VALUE; i++){
		for (int j = i - 1; j >= 0; j--){
			if(A[j] > A[j + 1]){
				swap(&A[j], &A[j + 1]);
			}
			else break;
		}
	}
	return *A;
}

int patrition(int A[], int p, int r){
	int x = A[r];
	int i = p - 1;
	for(int j = p; j <= r - 1; j++){
		if(A[j] <= x){
			i++;
			swap(&A[i],&A[j]);
		}
	}
	swap(&A[i + 1],&A[r]);
	return i + 1;
}

void quicksort(int A[], int p, int r){
	if(p < r){
		int q = patrition(A,p,r);
		quicksort(A,p,q - 1);
		quicksort(A,q + 1,r);
	}
}

int getrange(int A[]){
	int max,min;
	if(A[1] > A[0]){
		max = A[1];
		min = A[0];
	}
	else{
		max = A[0];
		min = A[1];
	}
	for(int i = 2; i < MAX_VALUE; i++){
		if(A[i] > max){
			max = A[i];
		}
		else if(A[i] < min){
			min = A[i];
		}
	}
	return max - min;
}


int countsort(int A[], int range){
	int diff = range + 1;
	int output[MAX_VALUE];
	int count[diff];
	int min = A[0];
	for(int i = 0; i < MAX_VALUE; i++){
		if(A[i] < min){
			min = A[i];
		}
		output[i] = 0;
	}
	for(int i = 0; i < diff; i++){
		count[i] = 0;
	}
	for(int j = 1; j <= MAX_VALUE; j++){
		count[A[j - 1] - min]++;
	}
	for(int i = 1; i <= diff; i++){
		count[i] += count[i - 1];
	}
	for(int j = MAX_VALUE - 1; j >= 0; j--){
		output[count[A[j] - min] - 1] = A[j];
		count[A[j] - min]--;
	}
	for(int i = 0; i < MAX_VALUE; i++){
		A[i] = output[i];
	}
	return *A;
}

void icantbelieveitcansort(int A[]){
	for(int i = 0; i < MAX_VALUE; i++){
		for(int j = 0; j < MAX_VALUE; j++){
			if (A[i] < A[j]){
				swap(&A[i],&A[j]);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	clock_t start_t, end_t, total_t;
	//int* a = (int*) malloc(sizeof(int) * MAX_VALUE);
	int a[MAX_VALUE];
	initarr(a);
	
	printf("The array before sorting is: \n");
	printarr(a,MAX_VALUE);
	
	/*
	start_t = clock();
	printf("Begin sorting, start_t = %ld\n", start_t);
	*/
	
	//insertionsort(a);
	//quicksort(a,0,MAX_VALUE - 1);
	//countsort(a,getrange(a));
	//icantbelieveitcansort(a);
	
	/*
	end_t = clock();
	printf("End of sort, end_t = %ld\n", end_t);
	total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	printf("Total time is %lu seconds\n", total_t);
	*/
	
	printf("The array after sorting is: \n");
	printarr(a,MAX_VALUE);
	
}
