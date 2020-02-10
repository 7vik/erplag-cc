#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define RULE_FILE_PATH "../grammar/grammar.txt"

typedef struct grammar_rule
{
    // linked list representing a grammar rule (X -> Y1 Y2 Y3) as X -> Y1 -> Y2 -> Y3 -> null
    char *tnt;
    struct grammar_rule *next;

} RULE;

void print_rule(RULE *lst)
{
    while(lst != NULL)
    {
        printf("%s\n",lst->tnt);
        lst = lst->next;
    }
    return;
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
    while (EOF != fscanf(f, "%[^\n]\n", line))
    {
        
    }
    fclose(f);
    return 0;
}