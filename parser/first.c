#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "bool.h"
#include "parser.h"


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

void print_grammar(GRAMMAR g, int index)
{

    for (int i = 0; i < index; i++)
    {
        //printf("%d\n", start);
        print_rule(g.rules[i]);
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


/*
GRAMMAR_NODE* exist_first(GRAMMAR_NODE* first_set[], char* search_token)
{   
    //printf("%s", search_token);
    for (int i = 0; i < MAX_NUM_NON_TERMINALS; i++)
    {
        if (first_set[i] == NULL)
        {
            return NULL;
        }

        if(strcmp(first_set[i]->variable, search_token) == 0)
            return first_set[i];
    }

    return NULL;
}
*/

GRAMMAR_NODE* populate_first(first_follow* first_table, GRAMMAR grammar, int idx, char* token)
{   
    //printf("inside return first: %s\n", token);
    GRAMMAR_NODE* set;
    
    if(first_table[token]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 0)
    {   
        //printf("first already counted\n");
        return set;
    }
        
    GRAMMAR_NODE* first_set = (GRAMMAR_NODE*) malloc(sizeof(GRAMMAR_NODE));
    GRAMMAR_NODE* cur_ptr = first_set;
    strcpy(first_set->variable, "\0");
    first_set->next = NULL;
    if (token == NULL)
    {
        return NULL;
        //printf("nshbf");
    }    
    else if (is_terminal(token))
    {
        //GRAMMAR_NODE* first_set = (GRAMMAR_NODE*)malloc(sizeof(GRAMMAR_NODE));
        //printf("terminal found: %s\n", token);
        strcpy(first_set->variable, token);
        first_set->next = NULL;
        
    }
    
    else
    {

        for (int i = 0; i < idx; i++)
        {

            if(strcmp(token, grammar[i]->variable) == 0)
            {
                //printf("match: %s\n", token);
                GRAMMAR_NODE* temp_set = return_first(first_table, grammar, idx, grammar[i]->next->variable);
                //printf("enr");
                print_rule(temp_set);
                printf("\n%s, \n\n", token);
                //exit(0);
                GRAMMAR_NODE* rule_ptr = grammar[i]->next;
                while(strcmp(temp_set->variable, "EPS") == 0)
                {
                    if(strcmp(first_set->variable, "\0"))
                    {
                        first_set = temp_set;
                        while(cur_ptr->next != NULL)
                        {
                            cur_ptr = cur_ptr->next;
                        }
                    }
                    else
                    {
                        cur_ptr->next = temp_set;
                        while(cur_ptr->next != NULL)
                        {
                            cur_ptr = cur_ptr->next;
                        }
                    }

                    temp_set = (GRAMMAR_NODE*) malloc(sizeof(GRAMMAR_NODE));
                    if (rule_ptr->next != NULL)
                    {
                        temp_set = return_first(first_table ,grammar, idx, rule_ptr->next->variable);
                        rule_ptr = rule_ptr->next;
                    }

                    else
                    {
                        cur_ptr->next = (GRAMMAR_NODE*) malloc(sizeof(GRAMMAR_NODE));
                        strcpy(cur_ptr->next->variable, "EPS");
                        cur_ptr->next->next = NULL;
                        break;
                    }

                }

                if(strcmp(first_set->variable, "/0"))
                    first_set = temp_set;
                else
                    cur_ptr->next = temp_set;

            }

        }
    }
    
    return first_set;

}

first_follow* construct_first_follow_set(GRAMMAR grammar, int idx)
{
    
    first_follow* first_table = (first_follow*) malloc (sizeof (first_follow));
    int count = 0;
    for (int i = 0; i < idx; i++)
    {
        first_table[i] = (first_follow_node*) malloc(sizeof(first_follow_node));

        initialize_bool_array(first_table[i]->first_set_array);
        initialize_bool_array(first_table[i]->follow_set_array);
    
    }
    
    for(int i = 0; i < idx; i++)
    {
        if (first_table[i]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 0)

            populate_first(first_table, grammar, idx, grammar->rules[i]);
    }
    printf("%d", count);
    print_grammar(first_table, count);
    return first_table;

    
}

void print_non_terminals(GRAMMAR_NODE* grammar[], int idx)
{
    for(int i = 0; i < idx; i++)
    {
        printf("%s, ", grammar[i]->variable);
    }   
}

void initialize_grammar(GRAMMAR grammar)
{
    int i; 
    for ( i = 0; i < MAX_RULE_NUM; i++)
    {
        grammar.rules[i] = NULL;

        if (grammar.rules[i] != NULL)
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
    GRAMMAR grammar;
    //initialize_grammar(grammar);

    int rule_count = 0;

    while (EOF != fscanf(f, "%[^\n]\n", line))
    {
        //printf("%s\n", line);
        //exit(0);
        char* token = strtok(line, " ");
        //printf("%s", token);
        //exit(1);
        // add non terminal as head
        
        grammar.rules[rule_count] = (GRAMMAR_NODE*)malloc(sizeof(GRAMMAR_NODE));
        GRAMMAR_NODE* cur_pointer = grammar.rules[rule_count];
        strcpy(grammar.rules[rule_count]->variable, token);
        grammar.rules[rule_count]->is_terminal_flag = 0;
        grammar.rules[rule_count]->next = NULL;

    
        //printf("%s\n", grammar.rules[rule_count]->variable);
        //exit(0);
        token = strtok(NULL, " ");
        //printf("here\n");
        while(token != NULL)
        {
            //printf("%s %d\n", token, is_terminal(token));
            if (strcmp(token, "->") == 0)
            {
                token = strtok(NULL, " ");
                continue;
            }
            // print_rule(grammar.rules[0]);
            // putchar('\n');
            GRAMMAR_NODE* node = (GRAMMAR_NODE*) malloc(sizeof(GRAMMAR_NODE));
            strcpy(node->variable, token);
            node->is_terminal_flag = is_terminal(token);
            node->next = NULL;
            cur_pointer->next = node;
            cur_pointer = cur_pointer->next; 
            token = strtok(NULL, " ");
        }
    
        //printf("here\n");
        rule_count++;
        
    }
    //printf("%d", rule_count);

    print_grammar(grammar, rule_count);
    //print_non_terminals(grammar, rule_count-1);

    //construct_first_set(grammar, rule_count - 1);
    fclose(f);
    return 0;
}

