#ifndef __LL
#define __LL

#include <stdio.h>
#include "enum.h"

typedef struct node {

	enum variables tnt;
	struct node * next;
}	NODE;


typedef struct linkedList {
	int count;
	struct node * first;
} STACK;

void push(STACK *head, enum variables ele);

void pop(STACK *head);

void printList(STACK *head);

NODE *top(STACK *head);

//int search(STACK* head, enum variables ele);

//struct node* delete(STACK* head, enum variables ele);
	
#endif