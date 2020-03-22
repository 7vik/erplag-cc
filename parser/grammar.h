#ifndef __GRAMMAR
#define __GRAMMAR
#include "bool.h"
#include "enum.h"
#define MAX_NUM_NON_TERMINALS 100  // number of non-terminals
#define MAX_VAR_SIZE 50            // maximum allowed length of variable
#define MAX_RULE_NUM 150
#define GRAMMAR_NODE_FILE_PATH "../grammar/grammar.txt"

typedef struct first_follow_node
{
    bool first_set_array[MAX_BOOL_ARRAY_SIZE];
    bool follow_set_array[MAX_BOOL_ARRAY_SIZE];
}first_follow_node;


typedef struct first_follow
{
    first_follow_node* fnf[MAX_NUM_NON_TERMINALS];
}first_follow;


typedef struct grammar_node
{
    // a single node of a grammar rule. If rule is A->FOO BAR, then FOO is a node
    char variable[MAX_VAR_SIZE];
    int is_terminal_flag;
    struct grammar_node *next;
} GRAMMAR_NODE;

typedef struct grammar
{
    GRAMMAR_NODE *rules[MAX_RULE_NUM];
    int num_rules;
}   GRAMMAR;

first_follow* get_first_follow_table(GRAMMAR* grammar);

GRAMMAR* generate_grammar(void);

void print_grammar(GRAMMAR* g);

void print_first_follow(first_follow* table);

void print_rule(GRAMMAR_NODE *rule);

void print_first_follow_node(first_follow_node* node);

int is_terminal(char* variable);

void print_rule(GRAMMAR_NODE *rule);

void print_grammar(GRAMMAR* g);

void print_first_follow_node(first_follow_node* node);

void print_first_follow(first_follow* table);

void populate_first(first_follow* first_table, GRAMMAR* grammar, int idx, char* token);

void populate_follow(first_follow* follow_table, GRAMMAR* grammar, int idx, char* token);

first_follow* construct_first_follow_set(GRAMMAR* grammar, int idx);

void print_non_terminals(GRAMMAR_NODE* grammar[], int idx);

void initialize_grammar(GRAMMAR* grammar);

GRAMMAR* generate_grammar(void);

first_follow* get_first_follow_table(GRAMMAR* grammar);

first_follow* get_first_follow_table(GRAMMAR* grammar);

first_follow_node *multiple_first(GRAMMAR *g, unsigned int rule, first_follow *ff);


#endif