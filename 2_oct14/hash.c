#include <stdio.h>
#include <stdlib.h>

//define the max value of the sorted list that will conduct hash search
#define MAX_VALUE 10000

//define the bucket size which is 2 times of the list that will conduct hash search
#define BUCKET_SIZE (2 * MAX_VALUE)

//define delta size for open addressing
#define DELTA 2

//create the array of hashtable which has the size of previously defined "BUCKET_SIZE"
int hashtable[BUCKET_SIZE];

//define the counter which counts the step of searching
int counter;

//define hashsearch function
int hashsearch(int key){
    int pos,t;
    
    //set counter to 1
    counter = 1;
    
    //set the index of key in hashtable by definition
    pos = key % BUCKET_SIZE;
    t = pos;
    
    //when there is a collision, use open addressing and increment the counter
    while(hashtable[t]!= key && hashtable[t]!= -1){
        t = (t + DELTA) % BUCKET_SIZE;
        counter++;
    }
    
    //return the value in hashtable
    if(hashtable[t] == -1)
        return -1;
    else
        return t;
    
}

//define createhash function which builds hash index for key value
void createhash(int key){
    int pos,t;
    
    //set the index of key in hashtable by definition
    pos = key % BUCKET_SIZE;
    t = pos;
    
    //when there is a collision, use open addressing 
    while(hashtable[t]!= -1){
        t = (t + DELTA) % BUCKET_SIZE;
    }
    
    //set the corresponding index in hashtable for hash search for key
    hashtable[t] = key;
}

int main(void){
    //define variables that will be used later
    int i,t;
    int val = 0;
    
    //initialize every index of hashtable to -1
    for(i = 0; i < BUCKET_SIZE; i++)
        hashtable[i] = -1;
    
    
    //create a sorted list contains all integers from 1 to max value defined above
    i = 0;
    while(i != MAX_VALUE){
        val++;
        t = val;
        createhash(t);
        i++;
    }
    
    /*
    conduct hash search for every indexes in the list and print out the result
    for(int h = 0; h < MAX_VALUE; h++){
        if (hashtable[h]!= -1){
            hashsearch(hashtable[h]);
            printf("The index of number \"%d\" is %d, step = %d\n",hashtable[h],h, counter);
        }
    }
    */
    
    //store user input as the key
    int key;
    printf("key? ");
    scanf("%d", &key);
    
    //if user input is not in the range, then abort
    if (key < 1 || key > MAX_VALUE){
        printf("Out of range");
        exit(0);
    }
    
    //conduct hash search for the key, and print out the step
    hashsearch(hashtable[key]);
    //printf("The index of number \"%d\" is %d, step = %d\n",hashtable[key],key, counter);
    printf("Found (step = %d)\n", counter); 
}
