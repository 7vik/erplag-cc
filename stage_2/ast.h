#ifndef __AST
#define __AST
#include "parser.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct astNode
{
    int node_marker;  // LHS enum will act a marker for a astNode for a particular rule; eg program(enum) will be certi for <program> -> blah blah
    TREE_NODE *tree_node; // parse tree node, which we would retain
    //struct astNode* next; 
    struct astNode *parent; 
    struct astNode *child;
    struct astNode *sibling;
    unsigned int is_leaf; // this one is for you 7vik ;) : 1 if leaf ob.

}astNode;

// typedef struct astTree
// {
//     astNode* ast_tree_node; 

// }astTree;
astNode *make_ASTnode(int certificate);
astNode *buildLeafAST(PARSE_TREE *t);
astNode *traverse_and_add_left(astNode *parent, astNode *child);
astNode *buildAST(PARSE_TREE *root);
void print_parse_tree_json(PARSE_TREE *tree,  char *outputfile);
void print_ast_json(astNode *tree,  char *outputfile);
void print_parse_tree_JSON(PARSE_TREE *t, FILE *fp);
void print_ast_JSON(astNode *t, FILE *fp);

#endif
