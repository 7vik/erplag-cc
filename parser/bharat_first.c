#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "bool.h"
#include "bharat_parser.h"
#include <assert.h> 

#define GRAMMAR_START_SYMBOL program

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

void print_grammar(GRAMMAR* g, int index)
{

    for (int i = 0; i < index; i++)
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
    int terminal_array_size = sizeof(terminals_array) / sizeof ( *terminals_array);
    int non_terminal_array_size = sizeof(non_terminals_array) / sizeof ( *non_terminals_array);
    if(is_terminal(string))
    {
        for (int i = 0; i < terminal_array_size; i++)
        {
            if(strcmp(terminals_array[i], string) == 0)
                return i;
        }
    }
    else
    {
        for (int i = 0; i < non_terminal_array_size; i++)
        {
            if(strcmp(non_terminals_array[i], string) == 0)
                return i;
        } 
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
    printf("\n\t\t\t***********************\tt\t\t\n");
    printf("FOLLOW SET\n\n");
    print_set_array(node->follow_set_array);
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
        printf("first already counted: %s\n", token);
        printf("enum value: %d\n", string_to_enum(token));
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

    printf("%s\n", token);
    if(follow_table->fnf[string_to_enum(token)]->follow_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 1)
    {   
        printf("follow already counted: %s\n", token);
        printf("enum value: %d\n", string_to_enum(token));
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

        printf("H2\n");
        while(node != NULL)
        {
            if(strcmp(token, node->variable) == 0)
            {
                // A -> aBC case

                if (node->next != NULL)
                {
                    printf("H3\n");
                    node = node->next;

                    if (is_terminal(node->variable))
                    {
                        follow_table->fnf[string_to_enum(token)]->follow_set_array[string_to_enum(node->variable)] = 1;
                        
                    }
                    else
                    {
                        or_and_store(follow_table->fnf[string_to_enum(token)]->follow_set_array ,follow_table->fnf[string_to_enum(token)]->first_set_array);
                        follow_table->fnf[string_to_enum(token)]->follow_set_array[EPS] = 0;
                        

                        if(follow_table->fnf[string_to_enum(token)]->first_set_array[EPS] == 1 && node->next == NULL && strcmp(grammar->rules[i]->variable, token) != 0)
                        {
                            populate_follow(follow_table, grammar, idx, grammar->rules[i]->variable);
                            or_and_store(follow_table->fnf[string_to_enum(token)]->follow_set_array ,follow_table->fnf[string_to_enum(grammar->rules[i]->variable)]->follow_set_array);
                        }
                        
                    }
                    

                }

                // A -> B

                else if (strcmp(grammar->rules[i]->variable, token) != 0)
                {
                    printf("H4\n");
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
            print_set_array(first_table->fnf[i]->follow_set_array);
            
        }
    }
    
    //print_first_follow(first_table);
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

int main()
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
    construct_first_follow_set(grammar, rule_count);

    fclose(f);
    return 0;
}

