#include<stdio.h>
#include<stdlib.h>

#include "linkedlist.h"

void push(STACK *head, enum variables ele)
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
	{
		//printf("List is empty\n");
		return;
	}
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
	NODE* link = head->first;
	//printf("%d\n",head->count);
	
	while(link != NULL)
	{
		printf("%d\n", link->tnt);
		link = link->next;
	}
}

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
	
// int main()
// {
// 	return 0;
// }