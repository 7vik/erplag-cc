#include<stdio.h>
#include "parser.h"
#include <stdlib.h>              // malloc()

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

//void push(STACK *)


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

void compute_first_follow(GRAMMAR *g, first_follow *f)
{
    // ayush jain and bharat bhargava deserve all credit for this code
    return;
}

void create_parse_table(first_follow *f, TABLE *t)
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
    GRAMMAR* grammar = generate_grammar();
    first_follow* table = get_first_follow_table(grammar);
    print_first_follow(table);
    return 0;
}