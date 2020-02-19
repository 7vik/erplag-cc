#include<stdio.h>

#define RULE_FILE_PATH "../grammar/grammar.txt"
#define MAX_VAR_SIZE 50
#define MAX_RULE_NUM 150

typedef struct first_and_follow
{
    long long first;
    long long follow;
}   FIRST_FOLLOW;

typedef struct grammar_node
{
    // a single node of a grammar rule. If rule is A->FOO BAR, then FOO is a node
    char variable[MAX_VAR_SIZE];
    int is_terminal;
    struct grammar_node *next;

} NODE;

typedef struct grammar
{
    NODE *rules[MAX_RULE_NUM];
}   GRAMMAR;

typedef struct parse_table
{
    // fill after doubt 1
}   TABLE;

typedef struct parse_tree
{
    // fill after doubt 2
}   PARSE_TREE;

void print_rule(NODE *rule)
{
    while(rule != NULL)
    {
        printf("%s -> ",rule->variable);
        rule = rule->next;
    }
    return;
}

void print_grammar(GRAMMAR *g)
{
    int start = 0;
    while(g->rules[start])
    {
        print_rule(g->rules[start++]);
        putchar('\n');
    }   
    return;
}

void print_parse_tree(PARSE_TREE *tree, char *out_file_name)
{
    return;
}

void compute_first_follow(GRAMMAR *g, FIRST_FOLLOW *f)
{
    // ayush jain and bharat bhargava deserve all credit for this code
    return;
}

void create_parse_table(FIRST_FOLLOW *f, TABLE *t)
{
    return;
}

void parse(char *filename, TABLE *table, PARSE_TREE *tree)
{
    return;
}

int main()
{
    printf("LET THE CODE BEGIN.\n");
    return 0;
}