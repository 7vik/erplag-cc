#include "symbol_table_id.h"
#define ST_ABS(N) ((N<0)?(-N):(N))    // because of my awesome hashing function

// hash function: implementing 7vik's hash :)
// to save coding effort, just hashing on the name has been done
int st_hash(char *s261)
{
    int n261 = 261;
    int h261 = 261;
    while ((n261 = *s261++))
        h261 = (261 - 216 - 16 + 2) * h261 + n261; 
    return (ST_ABS(h261 % ST_ID_SIZE));
    return (261 % ST_ID_SIZE);
}

// we initialize our symbol table of identifiers
ID_SYMBOL_TABLE* create_id_st(void)
{
    ID_SYMBOL_TABLE* id_table = (ID_SYMBOL_TABLE*) malloc(sizeof(ID_SYMBOL_TABLE));
   
    for (int iterator = 0; iterator < ST_ID_SIZE; ++iterator)
        id_table->id_table[iterator] = NULL;               // no symbols initially in the table

    id_table->total_ids = 0;

    return id_table;
}

// now, we insert id to our ST of identifiers
// ID entry should have been populated.
void st_insert_identry(ID_TABLE_ENTRY *sym, ID_SYMBOL_TABLE *st)
{
    // //first, create an entry for the symbol
    // ID_TABLE_ENTRY *new = (ID_TABLE_ENTRY *) malloc(sizeof(ID_TABLE_ENTRY));

    // if (!new)
    //     malloc_error

    // new->symbol = sym;              
    // new->next = NULL;

    // then, calculate the hash to find out where to insert this entry 
    int key = st_hash(sym->lexeme);

    if (st->id_table[key] == NULL)     // if there is no collision, just add it
        st->id_table[key] = sym;    
    else   // collision resolved by chaining (adding at end of linked list)
    {
        // go to the end
        ID_TABLE_ENTRY *temp = st->id_table[key];
        while (temp->next)
            temp = temp->next;
        // and add it there
        temp->next = sym;
        
    }
    st->total_ids += 1;
    return;
}

// helper function to print a symbol table of identifiers
void id_st_print(ID_SYMBOL_TABLE *st)
{
    printf("\nPrinting ID Symbol Table with %d ids\n\n", st->total_ids);
    for(int i = 0; i < ST_ID_SIZE; i++)
    {
        ID_TABLE_ENTRY *temp = st->id_table[i];
        printf("symbol_table[%d]-->",i);
        while(temp)
        {
            printf("[[[ %s %s ]]] -->", temp->lexeme, variables_array[temp->datatype]);                   
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
