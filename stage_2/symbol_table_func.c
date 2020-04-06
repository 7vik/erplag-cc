#include "symbol_table_func.h"
#include "type.h"
#define ST_ABS(N) ((N<0)?(-N):(N))                      
#define malloc_error { printf("Malloc error. Terminating.\n\n"); exit(5); }

// I'm very modest; I don't demand any appreciation for this research
int st_hash_global(char *s261)
{
    int n261 = 261;
    int h261 = 261;
    while ((n261 = *s261++))
        h261 = (261 - 216 - 16 + 2) * h261 + n261; 
    return (ST_ABS(h261 % GST_SIZE));
}

// we initialize our global symbol table
GST* create_global_st()
{
    GST *id_table = (GST *) malloc(sizeof(GST));   
    for (int iterator = 0; iterator < GST_SIZE; ++iterator)
        id_table->func_table[iterator] = NULL;                        // no function names initially in the table
    id_table->total_ids = 0;
    return id_table;
}

// now, we insert function table entry to our global ST
// The corresponding structure 'sym' should have been populated earlier.
void st_insert_func_entry(FUNC_TABLE_ENTRY *sym, GST *st)
{
    int key = st_hash_global(sym->fun_name);   // calculate the hash to find out where to insert this entry 
    if (st->func_table[key] == NULL)      // if there is no collision, 
        st->func_table[key] = sym;        // just add it
    else                                // collision resolved by 
    {
        FUNC_TABLE_ENTRY *temp = st->func_table[key];       // going to the end of list
        while (temp->next)
            temp = temp->next;
        temp->next = sym;                               // and adding it there
    }
    st->total_ids += 1;
    return;
}

// helper function to print the global symbol table
void global_st_print(GST *st)
{
    printf("\nPrinting Global Symbol Table with %d function identifier names\n\n", st->total_ids);
    for(int i = 0; i < GST_SIZE; i++)
    {
        FUNC_TABLE_ENTRY *temp = st->func_table[i];
        printf("global_symbol_table[%d]-->",i);
        while(temp)
        {
            printf("[[[ %s -- ", temp->fun_name);
	    
	    print_par_list(temp->inputPara);	// defined below
 	    printf(" -- ");
	    
	    print_par_list(temp->outputPara);
	    printf(" ]]] -->");
	                       
            temp = temp->next;
        }
        printf("NULL\n");
    } 
    //comment the following statement if you don't want to print ST for identifiers, for which the current ST will serve as the ancestor.
    
    //id_st_print(st->local_id_table);	// Not like this!

    return;
}

// helper function to print the parameter lists of global symbol table
void print_par_list(parList *list)
{
    parList *temp = list;
    while(temp)
    {
        printf("[%s %s] --> ",temp->parname, show_type(temp->datatype));	// Hence, need to compile with symbol_table_id.c as well.
	temp = temp->next;
    }
    printf("NULL");
}
 
// lookup the global symbol table for function, and return the entry if found
FUNC_TABLE_ENTRY *global_st_lookup(char *name, GST *st)
{
    // first, compute the key where the variable would be (tentatively) stored in global ST
    int key = st_hash_global(name);
    FUNC_TABLE_ENTRY *temp = st->func_table[key];
    while(temp)
    {
        if(strcmp(temp->fun_name, name) == 0)   // entry found
            return temp;
        temp = temp->next;
    }
    return NULL;  // function with the specified name not defined
}

// populating a global symbol table entry, will be created when we define a function
FUNC_TABLE_ENTRY *create_func_symbol(astNode *node, parList *inp_par, parList *out_par, ID_SYMBOL_TABLE *st)      
{
    assert(strcmp(node->tree_node->token_name, "ID") == 0);             //this should have ID info
    FUNC_TABLE_ENTRY *new = (FUNC_TABLE_ENTRY *) malloc(sizeof(FUNC_TABLE_ENTRY));
    if (!new)
        malloc_error    
    new->fun_name = node->tree_node->lexeme;
    new->inputPara = inp_par;
    new->outputPara = out_par;
    new->width = get_total_width(st);
    new->local_id_table = st;
    new->next = NULL;
    new->is_declared = false;
    return new;
}

int get_total_width(ID_SYMBOL_TABLE *st)
{
    if(st == NULL)	// No symbol table of identifiers <=> no local variables of function
	return 0;

    int total = 0;
    ID_TABLE_ENTRY *temp;
    for(int i = 0; i < ST_ID_SIZE; i++)	// summing up the widths of each identifier in the current ST.
    {
        temp = st->id_table[i];
        while(temp)
	{
	    total += temp->width;
    	    temp = temp->next;
        }
    }

    for(int j = 0; j < st->kid_table_count; j++)
	total += get_total_width(st->kid_st[j]);

    return total;
}


