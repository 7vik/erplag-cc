#ifndef __TYPE
#define __TYPE

// type data for an array
typedef struct ARRAY_TYPE_DATA
{
    // array[begin..end] of base_type
    unsigned int begin;
    unsigned int end;
    unsigned short int base_type;                // enum for integer, real, boolean
    // changes here if she allows for nested arrays
} ARRAY_TYPE_DATA;

// // type data for a function
// typedef struct FuNCTION_TyPE_DaTA
// {
//     // a function type has inputs and outputs (as an array)
//     unsigned int num_in, num_out;                        // number of inputs/outputs
//     struct symbol_data *inputs[FUNC_PARAMS];                     // everything else NULL, only for type of parameters with name
//     struct symbol_data *outputs[FUNC_PARAMS];
// } FUNCTION_TYPE_DATA;

// abstract structure to store any given type (insert a good type type pun)
typedef struct TYPE_INFO
{
    unsigned short int simple;                   // enum for integer, real, boolean, array
    ARRAY_TYPE_DATA *arrtype;                   // if array, else NULL
    // FUNCTION_TYPE_DATA *functype;              // if function, else NULL
} TYPE;

#endif