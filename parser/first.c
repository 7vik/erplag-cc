#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define RULE_FILE_PATH "../grammar/grammar.txt"
#define TOKEN_MAX_SIZE 50

typedef struct grammar_rule
{
    // linked list representing a grammar rule (X -> Y1 Y2 Y3) as X -> Y1 -> Y2 -> Y3 -> null
    char tnt[TOKEN_MAX_SIZE];
    struct grammar_rule *next;

} RULE;

void print_rule(RULE *lst)
{
    while(lst != NULL)
    {
        printf("%s -> ",lst->tnt);
        lst = lst->next;
    }
    return;
}

void print_grammar(RULE* grammar[], int index)
{
    for(int i = 0; i < index; i++)
    {
        print_rule(grammar[i]);
        printf("\n");
    }   
}

// returns 0 if the token is non-terminal
int is_terminal(char* tnt)
{
    if (tnt == NULL)
    {
        printf("In is_terminal: NULL String\n");
        exit(2);
    }

    if (tnt[0] == '<')
        return 0;
    else
        return 1;
    
}


int main()
{
    FILE *f = fopen(RULE_FILE_PATH, "r");
    if (f == NULL)
    {
        printf("Error opening file at %s. Aborting.\n", RULE_FILE_PATH);
        exit(1);
    }
    char line[200];
    RULE *grammar[150];
    int rule_count = 0;

    while (EOF != fscanf(f, "%[^\n]\n", line))
    {
        char* token = strtok(line, " ");

        if (is_terminal(token))
        {
            printf("Error, first token cannot be terminal: got %s", token);
            exit(3);
        }

        // add non terminal as head
        
        grammar[rule_count] = (RULE*)malloc(sizeof(RULE));
        RULE* cur_pointer = grammar[rule_count];
        strcpy(grammar[rule_count]->tnt, token);
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

            RULE* node = (RULE*) malloc(sizeof(RULE));
            strcpy(node->tnt, token);
            node->next = NULL;
            cur_pointer->next = node;
            cur_pointer = cur_pointer->next; 
            token = strtok(NULL, " ");
        }
        //printf("here\n");
        rule_count++;
        
    }
    print_grammar(grammar, rule_count-1);
    fclose(f);
    return 0;
}