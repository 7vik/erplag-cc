#ifndef __SYMBOL_TABLE_FUNC
#define __SYMBOL_TABLE_FUNC

#include<stdio.h>
#include "ast.h"                // Our AST will be used for extracting the function and variable identifiers
#include<stdlib.h>              // malloc() , exit()
#include<string.h>              // strcmp()
#include "parser.h"             // TREE_NODE structure
#include <assert.h>
#include "symbol_table_id.h"
#include "bool.h"
#define GST_SIZE 8          // max size of the global symbol table, for testing purposes, change later


// list of types required
// for input parameters
typedef struct parList
{
    char* parname; // variable name
    TYPE* datatype; // enum of datatype
    bool is_assigned; //if the outvars are assigned values inside function before returning
    struct parList* next;
}parList;

typedef struct FUNC_TABLE_ENTRY
{
    char* fun_name;  //function name from lexer, hash on this
    parList* inputPara, *outputPara; //list of input and output parameters
    int width; // total size of all local vars
    ID_SYMBOL_TABLE* local_id_table;
    struct FUNC_TABLE_ENTRY* next; // for chaining
    bool is_declared;  // to check if it is declared.
}FUNC_TABLE_ENTRY;

typedef struct FUNC_SYMBOL_TABLE
{
    FUNC_TABLE_ENTRY* func_table[GST_SIZE];
    int total_ids; 
}GST;     // global symbol table

/* This is the list of functions defined in symbol_table_func.c */
int st_hash_global(char *);
GST* create_global_st();
void st_insert_func_entry(FUNC_TABLE_ENTRY *, GST *);
void global_st_print(GST *);
void print_par_list(parList *);
FUNC_TABLE_ENTRY *global_st_lookup(char *, GST *);
FUNC_TABLE_ENTRY *create_func_symbol(astNode *, parList *, parList *, ID_SYMBOL_TABLE *);
int get_total_width(ID_SYMBOL_TABLE *st)

#endif
