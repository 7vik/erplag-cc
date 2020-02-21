#if !defined(MAX_BOOL_ARRAY_SIZE)
#define MAX_BOOL_ARRAY_SIZE  150             // maximum allowed length of boolean array
#endif

#include <stdbool.h>

void initialize_bool_array(bool* arr);
bool* or(bool * arr1, bool* arr2);
bool* and(bool * arr1, bool* arr2);
bool* xor(bool * arr1, bool* arr2);
bool* not(bool * arr1);
void print_bool(bool* arr, int size);
void or_and_store(bool * arr1, bool* arr2);