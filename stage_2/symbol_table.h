#ifndef __SYMBOL_TABLE_ID
#define __SYMBOL_TABLE_ID

#include<stdio.h>
#include "ast.h"                // Our AST will be used for extracting the function and variable identifiers
#include<stdlib.h>              // malloc() , exit()
#include<string.h>              // strcmp()
#include "parser.h"             // TREE_NODE structure
#include "type.h"               // type data
#include <assert.h>
#include "bool.h"
#define ST_ID_SIZE 8            // max size of the id symbol table, for testing purposes, change later
#define ST_KID_NUM 8            // max no of kids of an ID symbol table, change later
#define GST_SIZE 8          // max size of the global symbol table, for testing purposes, change later

typedef struct ID_TABLE_ENTRY
{
    char *lexeme;                               //variable name from lexer, hash on this
    TYPE *datatype;                             //structure of datatype
    unsigned int width;
    unsigned int offset;
    bool is_declared;
    struct ID_TABLE_ENTRY *next;                // for chaining
} ID_TABLE_ENTRY;

typedef struct ID_SYMBOL_TABLE
{
    struct ID_SYMBOL_TABLE *id_st_parent;               // parent to the ID ST (NULL at top) (not storing FST)
    struct FUNC_TABLE_ENTRY *primogenitor;                     // the function this ID table belong to
    ID_TABLE_ENTRY *id_table[ST_ID_SIZE];
    int total_ids;
    int kid_table_count;
    int visited;                                        // the genius that is ruslan spivak
    struct ID_SYMBOL_TABLE *kid_st[ST_KID_NUM];                               
} ID_SYMBOL_TABLE;

// i/o parameters
typedef struct param_list
{
    char *param_name;                                   // variable name (linear search instead of hashing)
    TYPE *datatype;                                     // type of variable (check on output type != array)
    bool is_assigned;                                   // to check whether out_params are assigned values inside function before returning
    struct param_list *next;                            // linked list
} PARAMS;

typedef struct FUNC_TABLE_ENTRY
{
    char *func_name;                                    //function name from lexer (hash on this)
    PARAMS *in_params, *out_params;                 //list of input and output parameters
    int width;                                          // total size of all local variables (why tho?)
    ID_SYMBOL_TABLE *local_id_table;                    // nested ID table for each function
    struct FUNC_TABLE_ENTRY* next;                      // for chaining
    bool is_declared;                                   // to check if it is declared (semantix)
    struct FUNC_SYMBOL_TABLE *procreator;               // link to GST
}FUNC_TABLE_ENTRY;

typedef struct FUNC_SYMBOL_TABLE                        // the final beautiful ST
{
    FUNC_TABLE_ENTRY *func_table[GST_SIZE];
    int total_functions; 
}GST;     

int st_hash(char *s261);
ID_SYMBOL_TABLE *create_id_st(ID_SYMBOL_TABLE *papa);
void st_insert_id_entry(ID_TABLE_ENTRY *sym, ID_SYMBOL_TABLE *st);
void id_st_print(ID_SYMBOL_TABLE *st);
ID_TABLE_ENTRY *st_lookup(char *name, ID_SYMBOL_TABLE *st);
int get_width(TYPE *datatype);
ID_TABLE_ENTRY *create_symbol(astNode *node, TYPE *type);
int get_type_expr(astNode *ex, ID_SYMBOL_TABLE *id_st);

GST *create_global_st();
void st_insert_func_entry(FUNC_TABLE_ENTRY *f, GST *gst);
void global_st_print(GST *gst);
void print_params(PARAMS *pl);
FUNC_TABLE_ENTRY *global_st_lookup(char *, GST *);
FUNC_TABLE_ENTRY *create_function(astNode *ast_node, PARAMS *in, PARAMS *out, ID_SYMBOL_TABLE *id_st);
int get_total_width(ID_SYMBOL_TABLE *st);
PARAMS *create_param(astNode *plist);
void gst_print(GST *st);
void traverse_the_multiverse(astNode *node, GST *st);
int is(astNode *node, char *comp);
void traverse_the_universe(astNode *node, ID_SYMBOL_TABLE *id_st);
#endif