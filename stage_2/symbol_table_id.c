#include "symbol_table_id.h"
#define ST_ABS(N) ((N<0)?(-N):(N))    // because of my awesome hashing function
#define malloc_error { printf("Malloc error. Terminating.\n\n"); exit(5); }

// hash function: implementing ayush's hash, patent pending ;)
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
void st_insert_id_entry(ID_TABLE_ENTRY *sym, ID_SYMBOL_TABLE *st)
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


// lookup the symbol table of identifiers for name, and return the symbol if found
ID_TABLE_ENTRY* st_lookup(char *name, ID_SYMBOL_TABLE *st)
{
    // first, compute the key where the variable would be (tentatively) stored
    int key = st_hash(name);
    ID_TABLE_ENTRY *temp = st->id_table[key];
    
    while(temp)
    {
        if(strcmp(temp->lexeme, name) == 0)   // symbol found
            return temp;                    // return it
        temp = temp->next;
    }

    return NULL; // not found 

    // if (st->parent == NULL)
    //     return NULL;                                // not found in any parents
    // else
    //     return st_lookup(name, st->parent);         // assuming scope only broadens with nesting, uncomment as per the requirement
}


// enum of datatype
//please add the datatypes
int get_width(int datatype)
{
    if(datatype == INTEGER)
        return 4;
    else if (datatype == REAL)
        return 8;
    else if (datatype == BOOLEAN)
        return 1;
    else if (datatype == ARRAY) //for now, just returning size of pointer
        return 8;
    else
    {
        printf("ERROR: Undefined datatype: %d", datatype);
        exit(2);
    }
    
}

// populating a id symbol table entry
ID_TABLE_ENTRY *create_symbol(astNode *node, int type)      
{
    assert(strcmp(node->tree_node->token_name, "ID") == 0); //this should have ID info
    //printf("Hello!");
    ID_TABLE_ENTRY *new = (ID_TABLE_ENTRY *) malloc(sizeof(ID_TABLE_ENTRY));
    if (!new)
        malloc_error
    //printf("Hello!");
    
    new->lexeme = node->tree_node->lexeme;
    new->datatype = type;
    new->width = get_width(type);
    new->offset = 0; // for now, I am not sure how to handle it
    new->next = NULL;
    return new;
}

// this currently just traverse the entire AST and adds the variables to the symbol table
// this for testing purposes only and demonstrating the traversal of AST.
void id_st_populate(ID_SYMBOL_TABLE* st, astNode* ast)
{
    astNode* temp = ast;

    if (temp->child == NULL)  //leaf node
    {
        if (strcmp(temp->tree_node->node_symbol, "ID") == 0) //if ID node
        {

            if (st_lookup(temp->tree_node->lexeme, st) == NULL) // if ID is not already there
            {
                ID_TABLE_ENTRY* table_entry = create_symbol(temp, INTEGER);
                st_insert_id_entry(table_entry, st);
            }
            
        }
        return;
    }
    else  // non terminal
    {
        // iterate over its child

        temp = temp->child; 
        while(temp != NULL)
        {
            id_st_populate(st, temp);
            temp = temp->sibling;
        }

        return;
    }
    
}


// just a helper function for testing. Comment this out
astNode *init_ast_node_par()
{
    astNode *node = (astNode *)malloc(sizeof(astNode));
    node->child = NULL;
    node->parent = NULL;
    node->sibling = NULL;
    node->is_leaf = 1;
    node->node_marker = ID;
    return node;
}
int main(int argc, char* argv[])
{
    // just to test if it's working
    if(argc != 3)
    {
        printf("Invalid argument count. Expected 3 arguments as in './executable testcase parse_outfile'.");
        printf("\nAborting Execution!!\n");
        exit(2);
    }

    FILE* test_fp = fopen(argv[1], "r");
    FILE* test_parse_fp = fopen(argv[2], "w");
    populate_ht(hash_table, KEYWORDS_FILE);
    int line_count = 1;
    TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
    init_buffer(test_fp, twin_buff);
    GRAMMAR* grammar = generate_grammar();
    first_follow *ff = get_first_follow_table(grammar);
    TABLE *parse_table = (TABLE *) malloc(sizeof(TABLE));
    create_parse_table(ff, parse_table, grammar);
    STACK *stack = NULL;
    PARSE_TREE *tree;
    parse(grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
    fprintf(test_parse_fp, "%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s%20s\n\n", "LEXEME", "LINE_NO", "VALUE (if num)", "TOKENAME",  "PARENT", "IS LEAF?", "NODE SYMBOL", "RULE_NUMBER");
    print_parse_tree(tree, test_parse_fp);
    print_parse_tree_json(tree, "output_parse_tree.json");

    printf("Printed Parse Tree in file '%s'.\n", argv[2]);
    // printf("Rule number of root: %d\n", tree->kids[0]->data->rule_number);
    astNode* ast_root = buildAST(tree);
    // printf("H1\n");
    print_ast_json(ast_root, "output_ast_tree.json");


    // Test Symbol table

    ID_SYMBOL_TABLE* st =  create_id_st();
    id_st_populate(st, ast_root);
    id_st_print(st);

    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);

    return 0;
}