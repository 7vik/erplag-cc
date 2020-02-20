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

GRAMMAR_NODE* exist_first(GRAMMAR_NODE* first_set[], char* search_token)
{   
    //printf("%s", search_token);
    for (int i = 0; i < MAX_GRAMMAR_NODE_NUM; i++)
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

GRAMMAR_NODE* return_first(GRAMMAR_NODE* first_table[], GRAMMAR_NODE* grammar[], int idx, char* token)
{   
    //printf("inside return first: %s\n", token);
    GRAMMAR_NODE* set;
    /*
    if((set = exist_first(first_table, token)) != NULL)
    {   
        //printf("first already counted\n");
        return set;
    }
    */    
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
GRAMMAR_NODE** construct_first_set(GRAMMAR_NODE* grammar[], int idx)
{
    
    GRAMMAR_NODE **first_table = (GRAMMAR_NODE**)malloc(MAX_GRAMMAR_NODE_NUM * sizeof(GRAMMAR_NODE*));
    int count = 0;
    for (int i = 0; i < MAX_GRAMMAR_NODE_NUM; i++)
    {
        first_table[i] = (GRAMMAR_NODE*) malloc(sizeof(GRAMMAR_NODE));
        strcpy(first_table[i]->variable, "\0");
        first_table[i]->next = NULL;
    }
    for(int i = 0; i < idx; i++)
    {
        if (exist_first(first_table, grammar[i]->variable) == NULL)
        {
            //first_table[count] = (GRAMMAR_NODE*) malloc(sizeof(GRAMMAR_NODE));
            first_table[count]->next = return_first(first_table, grammar, idx, grammar[i]->variable);
            strcpy(first_table[count]->variable, grammar[i]->variable);
            //printf("%s\n", grammar[i]->variable);
            //print_rule(first_table[count]);
            //printf("end\n");
            count++;
        }

        
    }
    printf("%d", count);
    print_grammar(first_table, count);
    return first_table;

    /*****************To DO**********************
     * Remove duplicates from first_table
     */
}

void print_non_terminals(GRAMMAR_NODE* grammar[], int idx)
{
    for(int i = 0; i < idx; i++)
    {
        printf("%s, ", grammar[i]->variable);
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
    int rule_count = 0;

    while (EOF != fscanf(f, "%[^\n]\n", line))
    {
        char* token = strtok(line, " ");

        // add non terminal as head
        
        grammar[rule_count] = (GRAMMAR_NODE*)malloc(sizeof(GRAMMAR_NODE));
        GRAMMAR_NODE* cur_pointer = grammar[rule_count];
        strcpy(grammar[rule_count]->variable, token);
        grammar[rule_count]->is_terminal_flag = 0;
        grammar[rule_count]->next = NULL;
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
    print_non_terminals(grammar, rule_count-1);

    //construct_first_set(grammar, rule_count - 1);
    fclose(f);
    return 0;
}

