#include <stdio.h>
#include <stdlib.h>

//define a structure "list" which contains data element and pointer pointing to next element
struct list{
    int data;
    struct list *next;
};

//main function
int main(void) {
    //*head is for 1st node, *new and *temp are for node afterwards
    struct list *head, *new, *temp;
	
    //Part 1: initialization of the first node (aka head)
    
    //allocate memory for the head element
    head = (struct list *)malloc(sizeof(struct list));
    
    //assign data inside the head element to 1
    int data = 1;
    head->data = data;

    //set the pointer pointing to next element be NULL (there is no next element yet)
    head->next = NULL;
	
    //print out the element of the 1st node (1)
    printf("%d ", head->data);
	
    //Part 2: Creation of 2nd node to 100th node

    //let head element be temporary element for creating nodes afterwards
    temp = head;

    //create a for loop from 2nd node to 100th node
    for (int i = 2; i <= 100; i++){
	 
	//increment data itself each time
	data++;
	
	//create new element and allocate memory for each of them
	new = (struct list*)malloc(sizeof(struct list));
	    
	//assign data (incremented before) inside the new element to corresponding value
	new->data = data;
	
	//print out the data inside the newly created elements
	printf("%d ", new->data);
	
	//set the pointer pointing to next element be NULL (there is no next element yet, and also there is no next element after the last element)
	new->next = NULL;
	
	//let temporary element point to the previously created "new" element
	temp->next = new;
	
	//let previously created element to be "temporary" element
	temp = temp->next;
    }
    return 0;
}
