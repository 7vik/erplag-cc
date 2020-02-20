#include<stdio.h>
#include "parser.h"


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

// recursive
void print_parse_tree(PARSE_TREE *tree, char *out_file_name)
{
    // prints the given parse tree in an output file in inorder traversal
    FILE *f = fopen(out_file_name, "w");
    if (tree == NULL)
        fprintf
    else
    {
        fprintf(f, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", var_enum_arr[tree->data->lexeme]);
    }
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