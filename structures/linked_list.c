#include<stdio.h>
#include<stdlib.h>

typedef struct linked_list
{
    // generic data type for a singly linked list
    struct linked_list *next;
    void *value;
} LIST;

/* WRONG
void print_list(LIST *head)
{
    while(head != NULL)
    {
        printf("%s: %s\n",lst->token, lst->value);
        lst = lst->next;
    }
    return;
}
/*