#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int hashtable[20000000];

int search(int key){
	int pos,t;
	pos = key % 20000000;
	t = pos;
	while(hashtable[t]!= key && hashtable[t]!= -1){
		t = (t + 1) % 20000000;
		if(pos == t){
			return -1;
		}
	}
	if(hashtable[t] == -1)
		return -1;
	else
		return t;
}

void createhash(int key){
	int pos,t;
	pos = key % 20000000;
	t = pos;
	while(hashtable[t]!= -1){
		t = (t + 1) % 20000000;
		if(pos == t){
			return;
		}
	}
	hashtable[t] = key;
}

int main(void){
	//clock_t start_t, end_t, total_t;
	int i,j,t;
	int val = 0;
	for(i = 0; i < 20000000; i++)
		hashtable[i] = -1;
	srand(time(NULL));
	i = 0;
	while(i != 10000000){
		int num = rand() % 10 + 1;
		val += num;
		t = val;
		createhash(t);
		i++;
	}
	//start_t = clock();
	//printf("Begin of the search, start_t = %ld\n", start_t);
	for(int h = 0; h < 10000000; h++){
		if (hashtable[h]!= -1){
			search(hashtable[h]);
			printf("The index of number \"%d\" is %d\n",hashtable[h],h);
		}
	}
  /*
	end_t = clock();
	printf("End of search, end_t = %ld\n", end_t);
	total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	printf("Total time is %lu seconds\n", total_t);
  */
}
