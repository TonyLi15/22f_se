#include <stdio.h>
#include <stdlib.h>

//define a structure "list" which contains data element and pointer pointing to next element
struct list{
	int data;
	struct list *next;
};

//main function
int main(int argc, char *argv[]) {
	struct list *head, *new, *temp;
	
	//initialization of the first node (aka head)
	head = (struct list *)malloc(sizeof(struct list));
	int data = 1;
	head->data = data;
	head->next = NULL;
	
	//print out the element of the first node
	printf("%d ", head->data);
	
	//creation of 2nd node to 100th node
	temp = head;
	for (int i = 2; i <= 100; i++){
		data++;
		new = (struct list*)malloc(sizeof(struct list));
		new->data = data;
		new->next = NULL;
		temp->next = new;
		printf("%d ", new->data);
		temp = temp->next;
	}
	return 0;
}
