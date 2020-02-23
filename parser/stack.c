#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <string.h>
#include "stack.h"
#include "enum.h"

void push(STACK *head, int ele)
{
	NODE *link = (NODE *) malloc(sizeof(NODE));
	link->tnt = ele;
	link->next = head->first;
	head->first = link;
	head->count++;
}

void pop(STACK *head)
{
	if(head->count == 0)
		return;	
	
	NODE *temp = head->first;
	head->first = temp->next;
	temp->next = NULL;
	free(temp);
	head->count--;
	return;
}

NODE *top(STACK *head)
{
	return head->first;
}

void printList(STACK *head)
{
	NODE *link = head->first;
	
	while(link != NULL)
	{
		printf("%s\n", variables_array[link->tnt]);
		link = link->next;
	}
}

void stack_push_rule(GRAMMAR *g, int rule, STACK *head)
{
	GRAMMAR_NODE *ptr1 = g->rules[rule];
	NODE *ptr2;
	NODE *temp;
	STACK *head1 = (STACK *)malloc(sizeof(STACK));
	head1->first = NULL;
	head1->count = 0; 
	assert(string_to_enum(ptr1->variable) == top(head)->tnt);
	pop(head);
	ptr1 = ptr1->next;

	while(ptr1 != NULL)
	{		
		push(head1, string_to_enum(ptr1->variable));
		ptr1 = ptr1->next;
		head1->count = head1->count + 1;
	}

	while(head1->count != 0)
	{
		push(head, top(head1)->tnt);
		pop(head1);
	}
	// head->first = g->rules[rule];
	// NODE *temp = head->first;
	// head->count = 0;
	// while(temp != NULL)
	// {
	// 	head->count = head->count + 1;
	// 	temp = temp->next;
	// }
	// head->count = head->count - 1; 
}


// void stack_transfer(STACK* head1, STACK* head2)
// {
// 	GRAMMAR_NODE *ptr;
// 	while(head1->count != 0)
// 	{
// 		ptr = top(head1);
// 		push(head2, ptr->variable);
// 		pop(head1);
// 	}
// 	return;
// }

// int search(struct linkedList* head, int ele)
// {
// 	struct node* link = head->first;
// 	while(link != NULL)
// 	{
// 		if(link->element == ele)
// 			return 1;
// 		link = link->next;
// 	}
// 	return 0;


// }

// struct node* delete(struct linkedList* head, int ele)
// {
// 	struct node* link = head->first;
// 	struct node* temp;
// 	if(head->count == 0)
// 	{
// 		printf("List is empty\n");
// 		return NULL;
	
// 	}
// 	if(link->element == ele)
// 	{
// 		head->first = link->next;
// 		head->count--;
// 		return link;
		
	
// 	}
// 	while(link->next != NULL)
// 	{
// 		if(link ->next -> element == ele)
// 		{
// 			temp = link->next;
// 			link->next = temp->next;
// 			head->count--;
// 			return temp;
		
// 		}
// 		temp = link;
// 		link = temp->next;
	
	
// 	}
	
// 	if(link->element == ele)
// 	{
// 		temp->next = NULL;
// 		head->count--;
// 		return link;
		
// 	}
	
// 	printf("Error, no such element\n");
// 	return NULL;



// }

// uth jaa satvik	

/*   Initialize stack with dollar and start symbol   */


// int main()
// {
// 	GRAMMAR* g 
// 	return 0;
// }