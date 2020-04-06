#ifndef __SYMBOL_TABLE_ID
#define __SYMBOL_TABLE_ID

#include<stdio.h>
#include "ast.h"                // Our AST will be used for extracting the function and variable identifiers
#include<stdlib.h>              // malloc() , exit()
#include<string.h>              // strcmp()
#include "parser.h"             // TREE_NODE structure
#include "type.h"               // type data
#include <assert.h>
#define ST_ID_SIZE 8            // max size of the id symbol table, for testing purposes, change later
#define ST_KID_NUM 8            // max no of kids of an ID symbol table, change later


// typedef struct ID_NODE
// {
//     ID_TABLE_ENTRY* id_entry;
//     struct ID_NODE* next;
// }ID_NODE;

// typedef struct ID_LIST
// {
//     ID_NODE* head;
//     int size;
// }ID_LIST;

typedef struct ID_TABLE_ENTRY
{
    char *lexeme;                               //variable name from lexer, hash on this
    TYPE *datatype;                               //structure of datatype
    int width;
    int offset;
    struct ID_TABLE_ENTRY *next;                // for chaining
} ID_TABLE_ENTRY;

typedef struct ID_SYMBOL_TABLE
{
    void *id_st_parent;                         // parent to the ID ST. (Has to be (void *) for polymorphic parents)
    ID_TABLE_ENTRY *id_table[ST_ID_SIZE];
    int total_ids;
    int kid_table_count;
    struct ID_SYMBOL_TABLE *kid_st[ST_KID_NUM];                               
} ID_SYMBOL_TABLE;

int st_hash(char *s261);
ID_SYMBOL_TABLE* create_id_st(void *papa);
void st_insert_id_entry(ID_TABLE_ENTRY *sym, ID_SYMBOL_TABLE *st);
void id_st_print(ID_SYMBOL_TABLE *st);
ID_TABLE_ENTRY* st_lookup(char *name, ID_SYMBOL_TABLE *st);
int get_width(TYPE *datatype);
ID_TABLE_ENTRY *create_symbol(astNode *node, TYPE *type);
#endif