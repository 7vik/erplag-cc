#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "bool.h"
#include "parser.h"
#include <assert.h> 
#include <unistd.h>

#define rep(i,z) for (int i=0; i<z; ++i)

#define GRAMMAR_START_SYMBOL program

PARSE_TREE *create_new_node (TREE_NODE *data)
{
    // creates a new leaf node storing data, and returns the node
    PARSE_TREE *new = (PARSE_TREE *) malloc(sizeof(PARSE_TREE));
    new->data = data;
    new->num_of_kids = 0;
    int end = N_ARY_LIM;
    while(--end >= 0) new->kids[end] = NULL;
    return new;
}

// recursive
void print_parse_tree(PARSE_TREE *tree, char *out_file_name)
{
    // prints the given parse tree in an output file in inorder traversal
    // for an n-ary tree, inorder traversal means:
    //          leftmost kid, then pop, then other kids
    FILE *f = fopen(out_file_name, "w");
    if (tree == NULL)   
        return;         // print nothing
    else
    {
        print_parse_tree(tree->kids[0], out_file_name);
        fprintf(f, "%15s\t%15u\t%15s\t%15s\t%15s\t%15d\t%15s\n",
                    tree->data->lexeme,
                    tree->data->line,
                    tree->data->token_name,
                    tree->data->value_if_number,
                    tree->data->parent_node_symbol,
                    tree->data->is_leaf_node,
                    tree->data->node_symbol
                    );
        int temp = tree->num_of_kids;
        while (--temp)
            print_parse_tree(tree->kids[temp], out_file_name);
    }
    return;
}

// returns 0 if the token is non-terminal
int is_terminal(char* variable)
{
    if (variable == NULL)
    {
        printf("In is_terminal: NULL String\n");
        exit(2);
    }

    if (isupper(variable[0]))
        return 1;
    else
        return 0;
    
}

void print_rule(GRAMMAR_NODE *rule)
{
    while(rule != NULL)
    {
        printf("%s -> ",rule->variable);
        rule = rule->next;
    }
    return;
}

void print_grammar(GRAMMAR* g)
{

    for (int i = 0; i < g->num_rules; i++)
    {
        //printf("%d\n", start);
        print_rule(g->rules[i]);
        putchar('\n');
    }
    //printf("%d\n", start - 1);   
    return;
}

// returns integer value mapping of string
int string_to_enum(char* string)
{
    int variable_array_size = sizeof(variables_array) / sizeof ( *variables_array);

    for (int i = 0; i < variable_array_size; i++)
    {
        if(strcmp(variables_array[i], string) == 0)
            return i;
    }

    printf("String to enum failed for %s\n", string);
    return -1;
}

void print_set_array(bool* set_array)
{
    int flag = 0;
    for (int i = 0; i < MAX_BOOL_ARRAY_SIZE - 1; i++)
    {
        if(set_array[i] == 1)
        {
            printf("%s ", variables_array[i]);
            flag = 1;
        }
    }

    if (flag)
        printf("\n");
}

void print_first_follow_node(first_follow_node* node)
{
    print_set_array(node->first_set_array);
    printf("Follow set: ");
    print_set_array(node->follow_set_array);
    printf("\n\t\t\t***********************\t\t\t\n");
}

void print_first_follow(first_follow* table)
{
    printf("FIRST SET\n\n");
    for (int i = 0; i < MAX_NUM_NON_TERMINALS; i++)
    {
        if (is_terminal(variables_array[i]))
            return;
        printf("first set of %s : ", variables_array[i]);
        print_first_follow_node(table->fnf[i]);
    }  
}


void populate_first(first_follow* first_table, GRAMMAR* grammar, int idx, char* token)
{   
    
    if (is_terminal(token))
    {
        printf("Terminal: %s, returning\n", token);
        return;
        
    }
    
    if(first_table->fnf[string_to_enum(token)]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 1)
    {   
        //printf("first already counted: %s\n", token);
        //printf("enum value: %d\n", string_to_enum(token));
        return;
    }
    if (token == NULL)
    {
        printf("NULL token in populate first");
        return;
        //printf("nshbf");
    }
    
    else
    {

        for (int i = 0; i < idx; i++)
        {

            if(strcmp(token, grammar->rules[i]->variable) == 0)
            {
                //printf("match: %s\n", token);
                
                // if token -> Terminal NT...
                int eps_flag = 0;
                char* temp_tnt = grammar->rules[i]->next->variable;
                GRAMMAR_NODE* temp_next = grammar->rules[i]->next;
                if (is_terminal(temp_tnt) != 0)
                {
                    first_table->fnf[string_to_enum(token)]->first_set_array[string_to_enum(temp_tnt)] = 1;
                    continue;
                }

                // means temp_tnt is a NT

                
                else 
                {
                    populate_first(first_table, grammar, idx, temp_tnt);
                    int str_to_enum = string_to_enum(temp_tnt);
                    assert(first_table->fnf[str_to_enum]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 1);
                    or_and_store(first_table->fnf[string_to_enum(token)]->first_set_array, first_table->fnf[str_to_enum]->first_set_array);

                    // if EPS in the first set

                    while (first_table->fnf[str_to_enum]->first_set_array[EPS] == 1)
                    {
                        
                        // if it is the last token, then don't do anything
                        // else find first of following term

                        if (temp_next->next != NULL)
                        {
                            first_table->fnf[string_to_enum(token)]->first_set_array[EPS] = 0;
                            temp_next = temp_next->next;
                            temp_tnt = temp_next->variable;

                            if (is_terminal(temp_tnt))
                            {
                                first_table->fnf[string_to_enum(token)]->first_set_array[string_to_enum(temp_tnt)] = 1;
                                break;
                            }
                            populate_first(first_table, grammar, idx, temp_tnt);
                            str_to_enum = string_to_enum(temp_tnt);
                            assert(first_table->fnf[str_to_enum]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 1);
                            or_and_store(first_table->fnf[string_to_enum(token)]->first_set_array, first_table->fnf[str_to_enum]->first_set_array);
                        }
                    }
                    continue;
                }
            }

        }

        first_table->fnf[string_to_enum(token)]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] = 1;
    }
    
    return;

}

void populate_follow(first_follow* follow_table, GRAMMAR* grammar, int idx, char* token)
{

    //printf("%s\n", token);
    if(follow_table->fnf[string_to_enum(token)]->follow_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 1)
    {   
        //printf("follow already counted: %s\n", token);
        //printf("enum value: %d\n", string_to_enum(token));
        return;
    }

    if (token == NULL)
    {
        printf("NULL token in populate follow");
        return;
        //printf("nshbf");
    }

    for (int i = 0; i < idx; i++)
    {
        // we start from RHS
        GRAMMAR_NODE* node = grammar->rules[i]->next;

        while(node != NULL)
        {
            if(strcmp(token, node->variable) == 0)
            {
                // A -> aBC case
                if (node->next != NULL)
                {
                    node = node->next;

                    if (is_terminal(node->variable))
                    {
                        follow_table->fnf[string_to_enum(token)]->follow_set_array[string_to_enum(node->variable)] = 1;
                        
                    }
                    else
                    {
                        
                        or_and_store(follow_table->fnf[string_to_enum(token)]->follow_set_array ,follow_table->fnf[string_to_enum(node->variable)]->first_set_array);
                        follow_table->fnf[string_to_enum(token)]->follow_set_array[EPS] = 0;
                        
                        while(follow_table->fnf[string_to_enum(node->variable)]->first_set_array[EPS] == 1)
                        {
                            if( node->next == NULL && strcmp(grammar->rules[i]->variable, token) != 0)
                            {
                                populate_follow(follow_table, grammar, idx, grammar->rules[i]->variable);
                                or_and_store(follow_table->fnf[string_to_enum(token)]->follow_set_array ,follow_table->fnf[string_to_enum(grammar->rules[i]->variable)]->follow_set_array);
                                break;
                            }

                            else if (node->next != NULL)
                            {
                                if (is_terminal(node->next->variable))
                                {
                                    follow_table->fnf[string_to_enum(token)]->follow_set_array[string_to_enum(node->next->variable)] = 1;
                                    node = node->next;
                                    break;
                                }
                                else
                                {
                                    or_and_store(follow_table->fnf[string_to_enum(token)]->follow_set_array ,follow_table->fnf[string_to_enum(node->next->variable)]->first_set_array);
                                    follow_table->fnf[string_to_enum(token)]->follow_set_array[EPS] = 0;
                                    node =  node->next;
                                }
                                

                            } 

                        }
                        
                        
                    }
                    

                }

                // A -> B

                else if (strcmp(grammar->rules[i]->variable, token) != 0)
                {
                    populate_follow(follow_table, grammar, idx, grammar->rules[i]->variable);
                    or_and_store(follow_table->fnf[string_to_enum(token)]->follow_set_array ,follow_table->fnf[string_to_enum(grammar->rules[i]->variable)]->follow_set_array);
                    
                        
                }
                

            }
            node = node->next;
        }

        
    }

    follow_table->fnf[string_to_enum(token)]->follow_set_array[MAX_BOOL_ARRAY_SIZE - 1] = 1;


}

first_follow* construct_first_follow_set(GRAMMAR* grammar, int idx)
{
    
    first_follow* first_table = (first_follow*) malloc (sizeof (first_follow));
    for (int i = 0; i < MAX_NUM_NON_TERMINALS; i++)
    {
        first_table->fnf[i] = (first_follow_node*) malloc(sizeof(first_follow_node));

        initialize_bool_array((first_table->fnf[i])->first_set_array);
        initialize_bool_array((first_table->fnf[i])->follow_set_array);
    
    }
   

    //first set       
    for(int i = 0; i < idx; i++)
    {
        if (first_table->fnf[string_to_enum(grammar->rules[i]->variable)]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 0)
        {
            populate_first(first_table, grammar, idx, grammar->rules[i]->variable);
            
        }
    }

    // start symbol must have dollar symbol


    
    first_table->fnf[program]->follow_set_array[DOLLAR] = 1;
    

    for(int i = 0; i < idx; i++)
    {
        if (first_table->fnf[string_to_enum(grammar->rules[i]->variable)]->follow_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 0)
        {
            populate_follow(first_table, grammar, idx, grammar->rules[i]->variable);
            
            
        }
    }
    
    

    // print_first_follow(first_table);
    return first_table;

    
}

void print_non_terminals(GRAMMAR_NODE* grammar[], int idx)
{
    for(int i = 0; i < idx; i++)
    {
        printf("%s, ", grammar[i]->variable);
    }   
}

void initialize_grammar(GRAMMAR* grammar)
{
    int i; 
    for ( i = 0; i < MAX_RULE_NUM; i++)
    {
        grammar->rules[i] = NULL;

        if (grammar->rules[i] != NULL)
            printf("error\n");
    }
}


GRAMMAR* generate_grammar(void)
{
    FILE *f = fopen(GRAMMAR_NODE_FILE_PATH, "r");
    if (f == NULL)
    {
        printf("Error opening file at %s. Aborting.\n", GRAMMAR_NODE_FILE_PATH);
        exit(1);
    }
    char line[200];
    GRAMMAR* grammar = (GRAMMAR*) malloc (sizeof(GRAMMAR));

    int rule_count = 0;

    while (EOF != fscanf(f, "%[^\n]\n", line))
    {
        
        char* token = strtok(line, " ");
        grammar->rules[rule_count] = (GRAMMAR_NODE*)malloc(sizeof(GRAMMAR_NODE));
        GRAMMAR_NODE* cur_pointer = grammar->rules[rule_count];
        strcpy(grammar->rules[rule_count]->variable, token);
        grammar->rules[rule_count]->is_terminal_flag = 0;
        grammar->rules[rule_count]->next = NULL;

    
        token = strtok(NULL, " ");
        while(token != NULL)
        {
            if (strcmp(token, "->") == 0)
            {
                token = strtok(NULL, " ");
                continue;
            }
            GRAMMAR_NODE* node = (GRAMMAR_NODE*) malloc(sizeof(GRAMMAR_NODE));
            strcpy(node->variable, token);
            node->is_terminal_flag = is_terminal(token);
            node->next = NULL;
            cur_pointer->next = node;
            cur_pointer = cur_pointer->next; 
            token = strtok(NULL, " ");
        }
    
        rule_count++;
        
    }

    //print_grammar(grammar, rule_count);

    fclose(f);
    grammar->num_rules = rule_count;
    return grammar;
}
first_follow* get_first_follow_table(GRAMMAR* grammar)
{
    
    return construct_first_follow_set(grammar, grammar->num_rules);
}

first_follow_node *recursive_multiple_first(GRAMMAR *g, GRAMMAR_NODE *rulep, first_follow_node *curr, first_follow *ff)
{
    // empty case
    // printf("EEE\n");
    if(strcmp("EPS", rulep->variable) == 0)
    {
        curr->first_set_array[EPS] = 1;
        // printf("A1\n");
        return curr;
    }
    // base cases
    // if it's a terminal
    if (is_terminal(rulep->variable))
    {
        curr->first_set_array[string_to_enum(rulep->variable)] = 1;
        // printf("A2\n");
        return curr;
    }
    if (rulep->next == NULL)
    {
        or_and_store(curr->first_set_array, ff->fnf[string_to_enum(rulep->variable)]->first_set_array);
        // ff->fnf[string_to_enum(rulep->variable)];
        // printf("A3\n");
        return curr;
    }
    // recursive cases
    else    // it's a non terminal
    {
        first_follow_node *temp1 = (first_follow_node *) malloc(sizeof(first_follow_node));
        first_follow_node *temp2 = (first_follow_node *) malloc(sizeof(first_follow_node));
        // first_follow_node *temp1;
        // first_follow_node *temp2;
        // temp1 = ff->fnf[string_to_enum(rulep->variable)];
        for (int r=0; r<MAX_BOOL_ARRAY_SIZE; ++r)
        {
            temp1->first_set_array[r] = ff->fnf[string_to_enum(rulep->variable)]->first_set_array[r];
            temp1->follow_set_array[r] = ff->fnf[string_to_enum(rulep->variable)]->follow_set_array[r];
        }
        // printf("LOL%s: ", rulep->variable);
        // print_first_follow_node(temp1);
        // putchar('\n');
        if (temp1->first_set_array[EPS] == 1)
        {
            // printf("%s\n", rulep->variable);
            temp2 = recursive_multiple_first(g, rulep->next, curr, ff);
            // printf("TTT\n");
        }
        // else if (temp1->first_set_array[EPS] == 0)
        //     temp2 = temp2;
        temp1->first_set_array[EPS] = 0;
        for (int i  = 0; i < MAX_BOOL_ARRAY_SIZE - 1; i++)
            curr->first_set_array[i] = temp1->first_set_array[i] | temp2->first_set_array[i];
        // printf("A4\n");
        return curr;
    }
    return NULL;    // hopefully never
}



first_follow_node *multiple_first(GRAMMAR *g, unsigned int rule, first_follow *ff)
{
    first_follow_node *new = (first_follow_node *) malloc(sizeof(first_follow_node));
    assert(rule < g->num_rules);
    GRAMMAR_NODE *rule_head;
    rule_head = g->rules[rule];
    rule_head = rule_head->next;
    // printf("%s\n", rule_head->variable);
    new = recursive_multiple_first(g, rule_head, new, ff);
    // print_first_follow_node(new);
    return new;
}


void parse(char *filename, TABLE *table, PARSE_TREE *tree)
{
    return;
}

TABLE *create_parse_table(first_follow *f, TABLE *t, GRAMMAR *g)
{
    int num_nt = whichStmt - arithmeticExpr + 1;
    int num_t = WITH - AND + 1;
    for (int i=0; i<num_nt; ++i)
        for (int j=0; j<num_t; ++j)
            t->matrix[i][j] = -1;
    for (int i = 0; i < g->num_rules; ++i)
    {
        for( int j = 0; j < MAX_BOOL_ARRAY_SIZE; ++j)
        { 
            if (multiple_first(g,i,f)->first_set_array[num_nt+j] == true)
            {
                t->matrix[string_to_enum(g->rules[i]->variable)][j] = i;
                // if (i == 0) {printf("RRRRRRR\n"); print_first_follow_node(multiple_first(g,i,f));}
            }
        }
        if (multiple_first(g,i,f)->first_set_array[EPS] == 1)
        {
            for( int k = 0; k < MAX_BOOL_ARRAY_SIZE; ++k)
            { 
            if (f->fnf[ string_to_enum(g->rules[i]->variable) ]->follow_set_array[num_nt+k] == 1)
                t->matrix[string_to_enum(g->rules[i]->variable)][k] = i;    //check for a instead of b
            }
            if(f->fnf[ string_to_enum("DOLLAR") ]->follow_set_array[i] == 1)
                t->matrix[string_to_enum("DOLLAR")][i] = i;
        }
    }
    for(int i = 0; i < g->num_rules; ++i)
        t->matrix[string_to_enum(g->rules[i]->variable)][EPS - num_nt] = -1;
    return t;
}

// helper function to print a given parse table
void print_parse_table(TABLE *t, GRAMMAR *g)
{
    int num_nt = whichStmt - arithmeticExpr + 1;
    int num_t = WITH - AND + 1;
    printf("%30s", "TABLE");
    rep(k,num_t)
        printf("%15s", variables_array[k+num_nt]);
    putchar('\n');
    putchar('\n');
    rep(i,num_nt)
    {   
        printf("%30s", variables_array[i]);
        rep(j,num_t)
        {
            // printf("%35s", g->rules[t->matrix[i][j]]->variable);
            printf("%15d", t->matrix[i][j]);
        }
        putchar('\n');
    }   
    return;
}

int main()
{
    GRAMMAR* grammar = generate_grammar();
    first_follow *ff = get_first_follow_table(grammar);
    // print_first_follow(ff);

    // print_first_follow_node(multiple_first(grammar, 0, ff));

    // for(int i=0;i<104;i++)
    //      print_first_follow_node(multiple_first(grammar, i, ff));
    
    
    TABLE *parse_table = (TABLE *) malloc(sizeof(TABLE));
    // printf("%d\n", WITH - AND + 1);
    print_parse_table(create_parse_table(ff, parse_table, grammar), grammar);
    return 0;
}