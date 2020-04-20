//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>

#ifndef __BOOL
#define __BOOL
#define MAX_BOOL_ARRAY_SIZE  150             // maximum allowed length of boolean array

void initialize_bool_array(bool* arr);
bool* or(bool * arr1, bool* arr2);
bool* and(bool * arr1, bool* arr2);
bool* xor(bool * arr1, bool* arr2);
bool* not(bool * arr1);
void print_bool(bool* arr, int size);
void or_and_store(bool * arr1, bool* arr2);

#endif