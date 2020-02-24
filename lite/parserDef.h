//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_VAR_SIZE 50            // maximum allowed length of variable
#define GRAMMAR_NODE_FILE_PATH "./grammar.txt"
#define MAX_RULE_NUM 150
#define N_ARY_LIM 15            // max size from current grammar is 12. Increase it if required.
#define MAX_NUM_NON_TERMINALS 100  // number of non-terminals
#define PARSE_TREE_FILE_NAME "parse_tree.txt"

#include "lexerDef.h"

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

typedef struct parse_table
{
    //******************* EDIT
    int matrix[whichStmt - arithmeticExpr + 1][WITH - AND + 1];
}   TABLE;

typedef struct stack_of_grammar_symbols
{
    int symbol;                 // enum, maybe a terminal or a non-terminal
    struct stack_of_grammar_symbols *next;
} STACK;


typedef struct parse_tree PARSE_TREE;
typedef struct parse_tree_node_data
{
    // data for printing and storing the parse tree effectively ftw
    char *lexeme;       // value in our passed lexeme tuple 
    unsigned int line;           // line in our passed lexeme
    char *token_name;   // token in our passed lexeme    
    char *value_if_number;
    PARSE_TREE *parent_node_pointer;             
    int is_leaf_node;               // 1 for yes       
    char *node_symbol;
} TREE_NODE;

struct parse_tree
{
    // n-ary tree structure
    TREE_NODE *data;
    int num_of_kids;
    struct parse_tree *kids[N_ARY_LIM];     // children nodes
} ;

void remove_comments(char *test_case_file, char *clean_file);
first_follow* get_first_follow_table(GRAMMAR* grammar);
GRAMMAR* generate_grammar(void);
void print_grammar(GRAMMAR* g);
int string_to_enum(char* string);
void print_first_follow(first_follow* table);
void print_rule(GRAMMAR_NODE *rule);
PARSE_TREE *create_new_node (TREE_NODE *data);