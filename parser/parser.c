// gcc parser.c ../lexer/lexer.c ../lexer/hash.c bool.c 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "bool.h"
#include "parser.h"
#include <assert.h> 
#include <unistd.h>
#include "../lexer/lexer.h"

#define not !
#define GRAMMAR_START_SYMBOL program

// push data on top of stack (passing pointer to stack)
void push(STACK **stp, int data)
{
    STACK *new = (STACK *) malloc(sizeof(STACK));
    new->next = *stp;
    new->symbol = data;
    *stp = new;
    return;
}

int is_empty(STACK *st)
{
    return st == NULL;
}

int top(STACK *st)
{
    if (is_empty(st))   return -1;
    return st->symbol;
}

// pop from top of stack (passing pointer to stack)
void pop(STACK **stp)
{
    if (is_empty(*stp)) {printf("STACK ERROR: Can't pop empty stack.\n"); return;}
    STACK *temp = *stp;
    *stp = (*stp)->next;
    free(temp);
    return;
}

void print_stack(STACK *st)
{
    if (not is_empty(st))
    {
        printf("%d\t", st->symbol);
        print_stack(st->next);
    }
    else putchar('\n');
    return;
}

void print_parse_table(TABLE *t, GRAMMAR *g);

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
void print_parse_tree(PARSE_TREE *tree, FILE* f)
{
    // prints the given parse tree in an output file in inorder traversal
    // for an n-ary tree, inorder traversal means:
    //          leftmost kid, then pop, then other kids
    
    if (tree == NULL)   
        return;         // print nothing
    else
    {
        printf("dhbdb %d\n", tree->num_of_kids);
        print_parse_tree(tree->kids[0], f);
        printf("sdfe\n");
        fprintf(f, "%15s\t%15u\t%15s\t%15s\t%15d\t%15s\n",
                    tree->data->lexeme,
                    tree->data->line,
                    tree->data->token_name,
                    tree->data->value_if_number,
                    //tree->data->parent_node_pointer,
                    tree->data->is_leaf_node,
                    tree->data->node_symbol
                    );
        int temp = tree->num_of_kids;
        printf("%d\n", temp);
        for (int i = 1; i < temp; i++)
            print_parse_tree(tree->kids[i], f);
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
    putchar('\n');
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

// EDIT**********************************************************************
TABLE *create_parse_table(first_follow *f, TABLE *t, GRAMMAR *g)
{
    int num_nt = whichStmt - arithmeticExpr + 1;
    int num_t = WITH - AND + 1;
    for (int i=0; i<num_nt; ++i)
        for (int j=0; j<num_t; ++j)
            t->matrix[i][j] = -1;
    for (int i = 0; i < g->num_rules; ++i)                      // for each production A->B of the grammar:
    {
        for( int j = AND; j <= WITH; ++j)                       // for each terminal a 
            if (multiple_first(g,i,f)->first_set_array[j] == true)           // in first(B), 
                t->matrix[string_to_enum(g->rules[i]->variable)][j - num_nt] = i;                        // add A->B to M[A,a]
        if (multiple_first(g,i,f)->first_set_array[EPS] == 1)               // if EPS is in first(B), then
            for( int k = AND; k <= WITH; ++k)                      // for each terminal b 
                if (f->fnf[ string_to_enum(g->rules[i]->variable) ]->follow_set_array[k] == 1)  // in follow(A)
                    t->matrix[string_to_enum(g->rules[i]->variable)][k - num_nt] = i;        // add A->B to M[A,b]
        t->matrix[string_to_enum(g->rules[i]->variable)][EPS - num_nt] = -1;            
    }
    return t;
}

// helper function to print a given parse table
void print_parse_table(TABLE *t, GRAMMAR *g)
{
    int num_nt = whichStmt - arithmeticExpr + 1;
    int num_t = WITH - AND + 1;
    printf("%30s", "TABLE");
    for (int k = 0; k < num_t; ++k)
        printf("%15s", variables_array[k+num_nt]);
    putchar('\n');
    putchar('\n');
    for (int i = 0; i < num_nt; ++i)
    {   
        printf("%30s", variables_array[i]);
        for (int j = 0; j < num_t; ++j)
        {
            printf("%15d", t->matrix[i][j]);
        }
        putchar('\n');
    }   
    return;
}

void pushr(PARSE_TREE *active, STACK **st, GRAMMAR_NODE *rule)
{
        print_rule(rule);
    if (rule == NULL)
    {
        return; exit(0);
    }
    // active->data = (TREE_NODE *) malloc(sizeof(TREE_NODE));
    active->kids[active->num_of_kids] = (PARSE_TREE *) malloc(sizeof(PARSE_TREE));
    active->kids[active->num_of_kids]->data = (TREE_NODE *) malloc(sizeof(TREE_NODE));
    active->kids[active->num_of_kids]->data->is_leaf_node = 0; 
    active->kids[active->num_of_kids]->data->lexeme = NULL;
    active->kids[active->num_of_kids]->data->line = 0;
    active->kids[active->num_of_kids]->data->node_symbol = rule->variable;
    active->kids[active->num_of_kids]->data->parent_node_pointer = active;
    active->kids[active->num_of_kids]->data->token_name = NULL;
    active->kids[active->num_of_kids]->data->value_if_number = NULL;
    active->num_of_kids++;
    pushr(active, st, rule->next);
    push(st, string_to_enum(rule->variable));
}


void error(FILE *f, TWIN_BUFFER *twin_buff, int *line_no)
{
    
    // printf("Lo, ho gayi parsing error at line %d\n", *line_no);
    // LEXEME *lex = get_token(f, twin_buff, line_no);
    // while(strcmp(lex->token,"SEMICOL") != 0)
    //     lex = get_token(f, twin_buff, line_no);
    return;
}
void fill_tree()
{
    return;
}

void insert_parse_tree(PARSE_TREE **active, LEXEME *lex_tup)
{
    //(*active)->data = (TREE_NODE *) malloc(sizeof(TREE_NODE));
    (*active)->data->is_leaf_node = 1;
    (*active)->data->line = lex_tup->line;
    (*active)->data->lexeme = lex_tup->value;
    (*active)->data->token_name = lex_tup->token;
    if((strcmp(lex_tup->token, "NUM")  == 0) || (strcmp(lex_tup->token, "RNUM")  == 0))
        (*active)->data->value_if_number = lex_tup->value;
    (*active)->data->node_symbol = lex_tup->token;
    // (*active)->data->parent_node_pointer = *active;
    (*active)->num_of_kids = 0;
    for (int i=0; i<N_ARY_LIM; ++i) (*active)->kids[i] = NULL;
    return;
}

void next_active(PARSE_TREE *tree, PARSE_TREE **active)
{
    if ((*active) == tree) 
        return;
    printf("sakdbghvefb\n");
    // printf("%s\n", (*active)->data->node_symbol);
    PARSE_TREE *parent = (*active)->data->parent_node_pointer;
    printf("sakdbghvefb\n");
    int index_of_active = 0;
    printf("LOLOL++_+_ %s\n", (*active)->data->node_symbol);

    while(parent->kids[index_of_active] != (*active))
    {
        index_of_active++;
        printf("%d\n", index_of_active);
    }
    printf("sakdbghvefb\n");
    *active = parent;
    printf("sakdbghvefb\n");
    if (index_of_active < (parent->num_of_kids)-1)  
        *active = parent->kids[index_of_active + 1];
    else 
        return next_active(tree, active);
}



void parse(GRAMMAR *g, FILE *f, TABLE *table, PARSE_TREE *tree, STACK *st, TWIN_BUFFER *twin_buff, int *line_no)
{
    FILE *fp = fopen("bakchod.txt", "w");
    push(&st, DOLLAR);      // initially, the parser is in a config with w$ in input buffer and 
    push(&st, program);     // the start symbol above $ in the stack
    tree = (PARSE_TREE *) malloc(sizeof(PARSE_TREE));
    PARSE_TREE *active = tree;
    active->num_of_kids = 0;
    for(int i=0; i<N_ARY_LIM; ++i)
        active->kids[i] = NULL;
    active->data = (TREE_NODE *) malloc(sizeof(TREE_NODE));
    active->data->parent_node_pointer = NULL;
    active->data->is_leaf_node = 0;
    active->data->lexeme = NULL;
    active->data->line = 0;
    active->data->node_symbol = "program";
    active->data->token_name = NULL;
    active->data->value_if_number = NULL;
    LEXEME *a = get_token(f, twin_buff, line_no);           // let a be the first symbol of w
    int X = top(st);                                        // let X be the top stack symbol
    int num_nt = whichStmt - arithmeticExpr + 1;
    while(X != DOLLAR)              // stack is not empty
    {
        // printf("INPUTLEX:      %s\n", a->token);
        // printf("TOP::          %s\n", variables_array[X]);
        int rule_id = table->matrix[X][string_to_enum(a->token) - num_nt];
        if (X == string_to_enum(a->token))      // if X = a, then
        {
            // printf("G2\n");
            pop(&st);            // pop the stack, and
            insert_parse_tree(&active, a);
            printf("H1\n");
            next_active(tree, &active);       //deal with the segmentation fault here, and remove this comment.
            printf("H1]2\n");
            a = get_token(f, twin_buff, line_no);   // let a be the next symbol of w
        }
        else if (is_terminal(variables_array[X]))       // else if X is a terminal,
            error(f, twin_buff, line_no);
            // printf("H!\n");
        else if (table->matrix[X][string_to_enum(a->token) - num_nt] == -1)  // else if M[X,a] is an error entry, 
            error(f, twin_buff, line_no);
            // printf("H2\n");
        else if (rule_id != -1)
        {
            // printf("%d\n", rule_id);
            print_rule(g->rules[rule_id]);
            fill_tree();
            pop(&st);
            printf("vkmkbhd:::  %s\n", active->data->node_symbol);
            if (string_to_enum(g->rules[rule_id]->next->variable) != EPS)
            {
                pushr(active, &st, g->rules[rule_id]->next);
                printf("%d\n", active->num_of_kids);
                printf("vandanac %d\n", active->num_of_kids);
                
                //pushr(active, &st, g->rules[rule_id]->next);
                active = active->kids[0];
                printf("hbsdvvsb\n");
            }
        }
        X = top(st);

    }
    printf("HO GAYA PARSE\n");
    putchar('\n');
    print_parse_tree(tree, fp);
}

int main()
{
    populate_ht(hash_table, KEYWORDS_FILE);
    FILE *f = fopen(SOURCE_CODE_FILE, "r");
    int line_count = 1;
    TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
    init_buffer(f, twin_buff);
    GRAMMAR* grammar = generate_grammar();
    first_follow *ff = get_first_follow_table(grammar);
    TABLE *parse_table = (TABLE *) malloc(sizeof(TABLE));
    create_parse_table(ff, parse_table, grammar);
    // print_parse_table(parse_table, grammar);
    STACK *stack = NULL;
    PARSE_TREE *tree;
    parse(grammar, f, parse_table, tree, stack, twin_buff, &line_count);
    return 0;
}