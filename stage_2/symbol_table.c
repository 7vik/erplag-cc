//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include "ast.h"                // AST *generate_ast()
#include<stdlib.h>              // malloc() , exit()
#include<string.h>              // strcmp()

#define FUNC_PARAMS 8             // max number of function parametes (both IO)
#define ST_SIZE 8                 // max size of symbol table, for testing purposes, change later
#define MAX_KIDS 8                // max kids of a symbol table, for testing purposes, change later
#define ST_ABS(N) ((N<0)?(-N):(N))    // because of my awesome hashing function
#define malloc_error { printf("Malloc error. Terminating.\n\n"); exit(5); }       

// AIM: To create the symbol table from the given AST
// Please return a single AST *ast


/* 
Theory:

A symbol table is a table of symbols. It is required to:
- To make sure that when we assign a value to a variable the types are correct (type checking)
- To make sure that a variable is declared before it is used
- To pick the right variable from the right scope
- For debugging (programmer's perspective)
- For achieving compile time efficiency (plang designer's perspective)

- symbols of erplag can be:
    - a variable
        - inside a start and end block
        - has a fixed datatype
        - only to be recognized locally inside the block
        - (blocks might be nested)
    - a function
        - has a fixed input and output
        - input: of type integer, real, boolean, array 
        - output: of type integer, real, boolean
        - not to be nested, so globally scoped
    - and nothing else

- for variables, we should store the name and the type
- for functions, we should store the name and the type (two lists of types)

- a symbol table can be a hash_table (preferred over linear self-organizing lists and trees), with
    - key: name of the variable / function (id)
    - value: the type of the variable / function where the type of a function will be a much elaborate structure
    - the width and offset (dunno why)

- to create the symbol table(s), we need to traverse the AST, and for each type of AST node, 
- hardcode rules to add stuff to the ST. 
*/

// type data for an array
typedef struct ArRAY_TyPE_DaTA
{
    // array[begin..end] of simple
    unsigned int begin;
    unsigned int end;
    unsigned short int simple;                // 1,2,3 for integer, real, boolean
    // changes here if she allows for nested arrays
} ARRAY_TYPE_DATA;

// type data for a function
typedef struct FuNCTION_TyPE_DaTA
{
    // a function type has inputs and outputs (as an array)
    unsigned int num_in, num_out;                        // number of inputs/outputs
    struct symbol_data *inputs[FUNC_PARAMS];                     // everything else NULL, only for type of parameters with name
    struct symbol_data *outputs[FUNC_PARAMS];
} FUNCTION_TYPE_DATA;

// abstract structure to store any given type (insert a good type type pun)
typedef struct TyPE_InFO
{
    unsigned short int simple;                   // 1,2,3,4,5 for integer, real, boolean, array or function
    ARRAY_TYPE_DATA *arrtype;                   // if array, else NULL
    FUNCTION_TYPE_DATA *functype;              // if function, else NULL
} TYPE;

// we define a structure 'symbol' that will store the symbols (entries in the symbol table)
typedef struct symbol_data
{
    char *name;
    TYPE *type;
    unsigned int width;
    unsigned int offset;
    // anything else add here
} SYMBOL;

// now we have a hash table structure that stores these symbols
// we don't want to clash names (insert meme here) so starting with ST

// symbol table entry 
typedef struct st_entry_list_node
{
    SYMBOL *symbol;
    struct st_entry_list_node *next;            //  chaining for collisions
} ST_ENTRY;

// now our single, global symbol table (every function/scope has its own ST)
typedef struct SYMBOL_TABLE
{
    struct SYMBOL_TABLE *parent;                // pointer to misogynistic parent, NULL for global symbol table
    char *fn_name;                              // name of the symbol table, global initially later name of function / block
    FUNCTION_TYPE_DATA *ftype;                  // type if function, else NULL
    ST_ENTRY *table[ST_SIZE];                   // ST for variables
    unsigned short int kid_table_count;         // initially zero
    struct SYMBOL_TABLE *kid_tables[MAX_KIDS];  // array of kid tables to support nested STs
} ST;  

// we initialize our symbol table
void st_initialize(ST *symbol_table, char *name, ST *parent)
{
    symbol_table->parent = parent;
    if (parent != NULL)
        parent->kid_tables[parent->kid_table_count++] = symbol_table;
    symbol_table->fn_name = name;
    for (int iterator=0; iterator<ST_SIZE; ++iterator)
        symbol_table->table[iterator] = NULL;               // no symbols. Duh!
    symbol_table->kid_table_count = 0;                  // no kid tables initially
    for (int iterator=0; iterator<MAX_KIDS; ++iterator)
        symbol_table->kid_tables[iterator] = NULL;               
    return;
}

// hash function: implementing 7vik's hash (unpublished, 2020) Oh we meet again.
// to save coding effort, I'll just hash on the name
int st_hash(char *s261)
{
    int n261 = 261;
    int h261 = 261;
    while ((n261 = *s261++))
        h261 = (261 - 216 - 16 + 2) * h261 + n261; 
    return (ST_ABS(h261 % ST_SIZE));
    return (261 % ST_SIZE);
}

// now, we insert symbols to our ST
void st_insert_symbol(SYMBOL *sym, ST *st)
{
    // first, create an entry for the symbol
    ST_ENTRY *new = (ST_ENTRY *) malloc(sizeof(ST_ENTRY));
    if (!new)
        malloc_error
    new->symbol = sym;              
    new->next = NULL;
    // then, calculate the hash to find out where to insert this entry 
    int key = st_hash(new->symbol->name);
    // if there is no collision, just add it
    if (st->table[key] == NULL)
        st->table[key] = new;
    // collision resolved by chaining (adding at end of linked list)
    else
    {
        // go to the end
        ST_ENTRY *temp = st->table[key];
        while (temp->next)
            temp = temp->next;
        // and add it there
        temp->next = new;
    }
    return;
}
// helper function to print a symbol table
// recursive (oh yeah finally)
void st_print(ST *st)
{
    printf("\nPrinting Symbol Table: %s\n\n", st->fn_name);
    for(int i = 0; i < ST_SIZE; i++)
    {
        ST_ENTRY *temp = st->table[i];
        printf("symbol_table[%d]-->",i);
        while(temp)
        {
            printf("[[[ %s %hu %s ]]] -->", temp->symbol->name, temp->symbol->type->simple, temp->symbol->scope->scope);                   
            temp = temp->next;
        }
        printf("NULL\n");
    }
    for (int j=0; j<st->kid_table_count; ++j)
        st_print(st->kid_tables[j]);
    return;
}

// lookup the symbol table for name, and return the symbol if found
// recursive (oh boy)
SYMBOL *st_lookup(char *name, ST *st)
{
    // first, compute the key where it'd be stored if't'were there
    int key = st_hash(name);
    ST_ENTRY *temp = st->table[key];
    while(temp)
    {
        if(strcmp(temp->symbol->name, name) == 0)   // kudos! symbol found
            return temp->symbol;                    // return it
        temp = temp->next;
    }
    if (st->parent == NULL)
        return NULL;                                // not found in any parents
    else
        return st_lookup(name, st->parent);         // assuming scope only broadens with nesting, uncomment if reqd
}

// finally, traverse an AST to populate the symbol table
void st_populate(ST *symbol_table, astNode *root)
{
    st_initialize(symbol_table, "global", NULL);
    // traverse and fill
    // not possible to write this part of code before AST is finished
    // we need to call a helper function create_symbol (see below) that will take an AST node and create a symbol out of it
    return;
}

SYMBOL *create_symbol(char *name, unsigned short int type, char *scope)                 // these params will be replaced by (AST_NODE *node)
{
    SYMBOL *new = (SYMBOL *) malloc(sizeof(SYMBOL));
    if (!new)
        malloc_error
    new->name = name;
    new->type = (TYPE *) malloc(sizeof(TYPE));
    if (!(new->type))
        malloc_error
    new->type->simple = type;
    new->scope = (SCOPE *) malloc(sizeof(SCOPE));
    if (!(new->scope))
        malloc_error
    new->scope->scope = scope;
    return new;
}

int main()
{
    // just to test if it's working
    ST *symbol_table = (ST *) malloc(sizeof(ST));       // our lovely symbol table
    if (!symbol_table)
        malloc_error    
    ST *inner_table = (ST *) malloc(sizeof(ST));       // our lovely nested inner table
    if (!symbol_table)
        malloc_error    

    st_initialize(symbol_table, "global", NULL);
    st_initialize(inner_table, "for_loop", symbol_table);

    st_insert_symbol(create_symbol("age", 1, "global1"), symbol_table);
    st_insert_symbol(create_symbol("height", 1, "global2"), symbol_table);
    st_insert_symbol(create_symbol("weight", 1, "for1"), inner_table);
    st_insert_symbol(create_symbol("frac31", 2, "for2"), inner_table);
    st_insert_symbol(create_symbol("married", 3, "global3"), symbol_table);

    // st_print(symbol_table);
    if (st_lookup("married", symbol_table))  printf("%s\n", st_lookup("married", symbol_table)->scope->scope); else printf("NOT FOUND.\n");
    if (st_lookup("married", inner_table)) printf("%s\n", st_lookup("married", inner_table)->scope->scope); else printf("NOT FOUND.\n");
    return 0;
}