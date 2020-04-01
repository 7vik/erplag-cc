//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include "ast.h"                // Our AST will be used for extracting the function and variable identifiers
#include<stdlib.h>              // malloc() , exit()
#include<string.h>              // strcmp()
#include "parser.h"             // TREE_NODE structure

#define ST_SIZE 8                 // max size of symbol table, for testing purposes, change later
#define MAX_KIDS 8                // max kids of a symbol table, for testing purposes, change later
#define ST_GLOBAL_SIZE 8          // max size of the global symbol table, for testing purposes, change later
#define ST_ABS(N) ((N<0)?(-N):(N))    // because of my awesome hashing function
#define malloc_error { printf("Malloc error. Terminating.\n\n"); exit(5); }

// type data for an array
typedef struct ArRAY_TyPE_DaTA
{
    // array[begin..end] of simple
    int begin;
    int end;
    // int simple;                // ENUM values for integer, real, boolean
} ARRAY_TYPE_DATA;

// abstract structure to store any given type
typedef struct TYPE_INFO
{
    unsigned short int simple;      // ENUM values for integer, real, boolean (same as possible base type for array)
    ARRAY_TYPE_DATA *arrtype;       // not array <=> NULL   (<=> is 'iff')
} TYPE;

// we define a structure 'symbol' that will store the symbols
typedef struct symbol_data
{
    char *name;             // this is our key; a separate field to avoid possible pointer overhead later
    TREE_NODE *tree_node;   // we need line number and value as well; maintaining reference to tree node for now, can be removed
    TYPE *type;             // datatype for the symbol 
    int width;              // the width of the (possibly constructed) datatype in bytes
    int offset;             // will be required during code generation
} SYMBOL;

// now we have a hash table structure that stores these symbols
// we don't want to clash names so starting with ST

// symbol table entry 
typedef struct st_entry_list_node
{
    SYMBOL *symbol;
    struct st_entry_list_node *next;            // chaining for collisions
} ST_ENTRY;

// now our single symbol table
typedef struct SYMBOL_TABLE
{
    struct SYMBOL_TABLE *parent;                // pointer to the parent symbol table (ST)
    char *st_name;                              // name of the symbol table, can be used for scope info
    ST_ENTRY *table[ST_SIZE];                   // A ST with ST_SIZE entries
    unsigned short int kid_table_count;         // initially zero
    struct SYMBOL_TABLE *kid_tables[MAX_KIDS];  // array of kid tables to support nested STs.
} ST;

typedef struct global_st_entry_list_node
{
    char fun_lex[25];   // the function identifier
    /* V.IMP: Why is the previous declaration not a character pointer?
       Solution :- To take advantage of the principle of locality.
       NOTE: We can even change the "name" field in SYMBOL structure defined earlier.
    */
    ST *st; // pointer to the symbol table for all the top-level local variables declared in the function
    TREE_NODE *head_input_par;   // linked list of input parameters
    TREE_NODE *head_output_par;  // linked list of output parameters
    TREE_NODE *head_input_type;  // the input type expression of the function in a linked-list form
    TREE_NODE *head_output_type; // the output type expression of a function in a linked-list form
    struct global_st_entry_list_node *next; // chaining for collisions
} ST_GLOBAL_ENTRY;

// symbol table for function identifiers
typedef struct SYMBOL_TABLE_GLOBAL 
{
    struct SYMBOL_TABLE_GLOBAL *parent;           // this has to be initialized to NULL
    char *st_global_name;                         // name of the global symbol table, can be used for scope info, will be "global"
    ST_GLOBAL_ENTRY *table[ST_GLOBAL_SIZE];       // a global ST with ST_GLOBAL_SIZE entries
} ST_GLOBAL;

// we initialize our symbol table of identifiers
void st_initialize(ST *symbol_table, char *name, ST *parent)
{
    symbol_table->parent = parent;
    if (parent != NULL)
        parent->kid_tables[parent->kid_table_count++] = symbol_table;

    symbol_table->st_name = name;

    for (int iterator = 0; iterator < ST_SIZE; ++iterator)
        symbol_table->table[iterator] = NULL;               // no symbols initially in the table

    symbol_table->kid_table_count = 0;                  // no kid tables initially

    for (int iterator = 0; iterator < MAX_KIDS; ++iterator)
        symbol_table->kid_tables[iterator] = NULL;

    return;
}

// we initialize our global symbol table
void st_initialize_global(ST_GLOBAL *symbol_table, char *name)
{
    symbol_table->parent = NULL;

    symbol_table->st_global_name = name;

    for (int iterator = 0; iterator < ST_GLOBAL_SIZE; ++iterator)
        symbol_table->table[iterator] = NULL;               // no symbols initially in the table

    return;
}

// hash function: implementing 7vik's hash :)
// to save coding effort, just hashing on the name has been done
int st_hash(char *s261)
{
    int n261 = 261;
    int h261 = 261;
    while ((n261 = *s261++))
        h261 = (261 - 216 - 16 + 2) * h261 + n261; 
    return (ST_ABS(h261 % ST_SIZE));
    return (261 % ST_SIZE);
}

// now, we insert symbols to our ST of identifiers
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

    if (st->table[key] == NULL)     // if there is no collision, just add it
        st->table[key] = new;    
    else   // collision resolved by chaining (adding at end of linked list)
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

// We make insertions into the global ST
void st_insert_global(astNode *node, ST_GLOBAL *st, TREE_NODE *ipList, TREE_NODE *opList, TREE_NODE *ipType, TREE_NODE *opType)
{
    // first, create an entry for the global ST
    ST_GLOBAL_ENTRY *new = (ST_GLOBAL_ENTRY *) malloc(sizeof(ST_GLOBAL_ENTRY));

    if (!new)
        malloc_error

    strcpy(new->fun_lex, node->tree_node->lexeme);  // copying the name of function identifier in the fun_lex field
    
    // then, calculate the hash to find out where to insert this entry 
    int key = st_hash(new->fun_lex);

    if (st->table[key] == NULL)     // if there is no collision, just add it
        st->table[key] = new;    
    else   // collision resolved by chaining (adding at end of linked list)
    {
        // go to the end
        ST_GLOBAL_ENTRY *temp = st->table[key];
        while (temp->next)
            temp = temp->next;
        // and add it there
        temp->next = new;
    }

    // We'll make apt fields point to the corresponding lists, which will be known as soon as the function is declared
    new->head_input_par = ipList;
    new->head_output_par = opList;
    new->head_input_type = ipType;
    new->head_output_type = opType;

    new->st = NULL; //This field ought to be filled while traversing the AST
    return;
}

// helper function to print a symbol table of identifiers
void st_print(ST *st)
{
    printf("\nPrinting Symbol Table: %s\n\n", st->st_name);
    for(int i = 0; i < ST_SIZE; i++)
    {
        ST_ENTRY *temp = st->table[i];
        printf("symbol_table[%d]-->",i);
        while(temp)
        {
            printf("[[[ %s %hu %d ]]] -->", temp->symbol->name, temp->symbol->type->simple, st->kid_table_count);                   
            temp = temp->next;
        }
        printf("NULL\n");
    } 
    //Uncomment the following loop if you want to print ST for inner scopes as well, for which the current ST will serve as the ancestor.
    /*
    for (int j = 0; j < st->kid_table_count; ++j)
        st_print(st->kid_tables[j]);
    */
    return;
}

// helper function to print the global symbol table
void st_print_global(ST_GLOBAL *st)
{
    printf("\nPrinting Symbol Table: %s\n\n", st->st_global_name);
    for(int i = 0; i < ST_GLOBAL_SIZE; i++)
    {
        ST_GLOBAL_ENTRY *temp = st->table[i];
        printf("symbol_table[%d]-->",i);
        while(temp)
        {
            printf("[[[ %s ]]] -->", temp->fun_lex);                   
            temp = temp->next;
        }
        printf("NULL\n");
    } 
    
    return;
}

// lookup the symbol table of identifiers for name, and return the symbol if found
SYMBOL *st_lookup(char *name, ST *st)
{
    // first, compute the key where the variable would be (tentatively) stored
    int key = st_hash(name);
    ST_ENTRY *temp = st->table[key];
    
    while(temp)
    {
        if(strcmp(temp->symbol->name, name) == 0)   // symbol found
            return temp->symbol;                    // return it
        temp = temp->next;
    }

    if (st->parent == NULL)
        return NULL;                                // not found in any parents
    else
        return st_lookup(name, st->parent);         // assuming scope only broadens with nesting, uncomment as per the requirement
}

// lookup the global symbol table for function name, and return the global symbol table entry if found
ST_GLOBAL_ENTRY *st_lookup_global(char *name, ST_GLOBAL *st)
{
    // first, compute the key where the function name would be (tentatively) stored
    int key = st_hash(name);
    ST_GLOBAL_ENTRY *temp = st->table[key];
    
    while(temp)
    {
        if(strcmp(temp->fun_lex, name) == 0)   // function entry present
            return temp;                    // return it
        temp = temp->next;
    }

    return NULL; // this is the only table where names of function identifiers will be stored
}

// populating a variable with 'SYMBOL' as the structure type
SYMBOL *create_symbol(astNode *node, unsigned short int type)      
{
    SYMBOL *new = (SYMBOL *) malloc(sizeof(SYMBOL));
    if (!new)
        malloc_error
    new->tree_node = node->tree_node;
    new->name = node->tree_node->lexeme;
    
    new->type = (TYPE *) malloc(sizeof(TYPE));
    if (!(new->type))
        malloc_error
    new->type->simple = type;  // now this has to be common for an array type variable as well as a simple type variable.
    new->type->arrtype = NULL; // this will be filled, with apt. condition imposed, in the function st_populate() itself. 

    return new;
}

// finally, traverse an AST to make a hierarchy of symbol tables
void st_populate(ST_GLOBAL *symbol_table, astNode *root)
{
    st_initialize_global(symbol_table, "global");
    // traverse and fill
    // we need to call a helper function create_symbol (see above) that will take an AST node and create a symbol out of it
    return;
}