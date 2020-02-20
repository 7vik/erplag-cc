#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bool.h"

void initialize_bool_array(bool* arr)
{
    for (int i = 0; i < MAX_BOOL_ARRAY_SIZE; i++)
        arr[i] = 0;
}

bool* or(bool * arr1, bool* arr2)
{
    bool* arr = (bool*) malloc (sizeof(bool) * MAX_BOOL_ARRAY_SIZE);

   for (int i  = 0; i < MAX_BOOL_ARRAY_SIZE - 1; i++)
       arr[i] = arr1[i] | arr2[i];
   

   return arr;
}

// stores results in first array
void or_and_store(bool * arr1, bool* arr2)
{

   for (int i  = 0; i < MAX_BOOL_ARRAY_SIZE - 1; i++)
       arr1[i] = arr1[i] | arr2[i];
   

   return;
}

bool* and(bool * arr1, bool* arr2)
{
    bool* arr = (bool*) malloc (sizeof(bool) * MAX_BOOL_ARRAY_SIZE);

   for (int i  = 0; i < MAX_BOOL_ARRAY_SIZE - 1; i++)
       arr[i] = arr1[i] & arr2[i];
   

   return arr;
}

bool* xor(bool * arr1, bool* arr2)
{
    bool* arr = (bool*) malloc (sizeof(bool) * MAX_BOOL_ARRAY_SIZE);

   for (int i  = 0; i < MAX_BOOL_ARRAY_SIZE - 1; i++)
       arr[i] = arr1[i] ^ arr2[i];
    

   return arr;
}

bool* not(bool * arr1)
{
    bool* arr = (bool*) malloc (sizeof(bool) * MAX_BOOL_ARRAY_SIZE);

   for (int i  = 0; i < MAX_BOOL_ARRAY_SIZE - 1; i++)
       arr[i] = ~arr1[i];

   return arr;
}

void print_bool(bool* arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/*
int main()
{
    bool arr1[1] = {0};
    bool arr2[1] = {1};

    bool* arr;

    arr = or(arr1, arr2);
    print_bool(arr, 1);
    arr = and(arr1, arr2);
    print_bool(arr, 1);
    arr = xor(arr1, arr2);
    print_bool(arr, 1);
    initialize_bool_array(arr2);
    print_bool(arr2, 1);
    //printf("%d\n", sizeof(long double));
}
*/