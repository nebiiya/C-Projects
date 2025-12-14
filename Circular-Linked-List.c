#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

// Circular linked lst
struct node *circularSingly(int data){
	struct node *temp  = malloc(sizeof(struct node));
	temp->data = data;  
	temp->next = temp;  // Points to itself
	return temp;
}

// Error handler
int checkVal(int *numNodes){
	while(scanf("%d", numNodes) != 1 || *numNodes < 0){
		printf("Invalid input. Try again and enter a positive integer.\n");
		while(getchar() != '\n');
		printf("Input the number of nodes: ");
	}
	
	return *numNodes;
}

int main(){
	int numNodes;
	int data;
	
	printf("\e[1mWelcome to a program that displays a circular linked list\e[0m\n");
	printf("Input the number of nodes: ");
	checkVal(&numNodes);
	
	
	struct node *tail = NULL;
	for(int i = 0; i < numNodes; i++){
		printf("Input data for node %d: ", i + 1);
		scanf("%d", &data);
		if (tail == NULL){
			tail = circularSingly(data);		
		} else{
			struct node *newNode = circularSingly(data);
			newNode->next = tail->next; // new node points to head
			tail->next = newNode; // tail points to newNode / head
			tail = newNode; // tail = head (newNode)
		}

	}
	
	printf("Data entered in the list are:\n");

	struct node *current = tail->next; // head
	int i = 1;
	do {
		printf("Data %d = %d\n", i++, current->data);
		current = current->next;		
	}while(current != tail->next);
	
	
	
	return 0; 
}
