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
- for functions, we should store the name and the type (two linked lists of types)

- a symbol table can be a hash_table (preferred over linear self-organizing lists and trees), with
    - key: name of the variable / function (id)
    - value: the type of the variable / function where the type of a function will be a much elaborate structure

- to create the symbol table(s), we need to traverse the AST, and for each type of AST node, 
- hardcode rules to add stuff to the ST. This traversal will be written after the AST is created.

- to create two functions
    - one to add symbols (key, value) to a ST
    - one to search for them and return the value (type)

- So I'm creating a rudimentary ST, we'll need to make a lot of changes
- which should be easy since I write awesome code ¯\_(ツ)_/¯ 

DOUBTS:

- do we need to think about built-in types like integer, real, etc during symbol table?
- how do we store a symbol table inside a symbol table in case of nested blocks, and 
- do we really need to?
- if we don't store values in the ST, and just the AST, does that create a problem for the code generation part?

*/

// type data for an array
typedef struct ArRAY_TyPE_DaTA
{
    // array[begin..end] of simple
    int begin;
    int end;
    int simple;                // 1,2,3 for integer, real, boolean
    // changes here if she allows for nested arrays
} ARRAY_TYPE_DATA;

// abstract structure to store any given type (insert a good type type pun)
typedef struct TYPE_INFO
{
    unsigned short int simple;                   // 1,2,3,4 for integer, real, boolean or array
    ARRAY_TYPE_DATA *arrtype;       // if array, else nulla
} TYPE;

// scope data structure, 
// I'm assuming scope data must be stored in the ST
typedef struct scope_data
{
    char *scope;
    // NOTE: Since everything has a scope, NULL means global scope.
    // otherwise, the name of the program / function / block will have to be stored here
    // will take care of this part after AST creation
} SCOPE;

// we define a structure 'symbol' that will store the symbols
// this later needs to be changed as per necessity
typedef struct symbol_data
{
    char *name;
    TYPE *type;
    SCOPE *scope;
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

// now our single, global symbol table
typedef struct SYMBOL_TABLE
{
    struct SYMBOL_TABLE *parent;                // pointer to misogynistic parent, NULL for global symbol table
    char *st_name;                              // name of the symbol table, global initially, can be used for scope info
    ST_ENTRY *table[ST_SIZE];
    unsigned short int kid_table_count;                      // initially zero
    struct SYMBOL_TABLE *kid_tables[MAX_KIDS];            // array of kid tables to support nested STs. I know I'm awesome
} ST;  

// we initialize our symbol table
void st_initialize(ST *symbol_table, char *name, ST *parent)
{
    symbol_table->parent = parent;
    if (parent != NULL)
        parent->kid_tables[parent->kid_table_count++] = symbol_table;
    symbol_table->st_name = name;
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

/* I have never tested this in my life. I'd prefer it commented out for all eternity.
int delete(char *value, ST_ENTRY **hash_table)
{
    int key = hash(value);
    ENTRY *temp = hash_table[key];
    ENTRY *dealloc;
    if (temp != NULL)
    {
        if(temp->data == value)
        {
            dealloc = temp;
            temp = temp->next;
            free(dealloc);
            return 0;
        }
        else
        {
            while(temp->next)
            {
                if(temp->next->data == value)
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                    return 0;
                }
                temp = temp->next;
            }
        }
    }
    return 1;
}
*/

// helper function to print a symbol table
// recursive (oh yeah finally)
void st_print(ST *st)
{
    printf("\nPrinting Symbol Table: %s\n\n", st->st_name);
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
void st_populate(ST *symbol_table, AST *ast)
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