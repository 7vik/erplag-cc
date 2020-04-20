#ifndef __TYPE
#define __TYPE

// type data for an array
typedef struct ARRAY_TYPE_DATA
{
    // for array[begin..end] of base_type
    bool is_dynamic;                                        // if array's left or right index is dynamic
    unsigned int begin;                                     // actual
    unsigned int end;                                       // actual
    unsigned int begin_offset;                              // offset
    unsigned int end_offset;                                // offset
    unsigned short int base_type;                           // enum for integer, real, boolean
   // changes here if she allows for nested arrays
} ARRAY_TYPE_DATA;

// abstract structure to store any given type (insert a good type type pun)
typedef struct TYPE_INFO
{
    unsigned short int simple;                   // enum for integer, real, boolean, array
    ARRAY_TYPE_DATA *arrtype;                   // if array, else NULL
} TYPE;

#endif