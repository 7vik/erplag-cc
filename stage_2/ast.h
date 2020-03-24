#ifndef __AST
#define __AST
#include "parser.h"
#include<stdlib.h>
typedef struct astNode
{
    int node_marker;  // LHS enum will act a marker for a astNode for a particular rule; eg program(enum) will be certi for <program> -> blah blah
    TREE_NODE* tree_node; // parse tree node, which we would retain
    //struct astNode* next; 
    struct astNode* parent; 
    struct astNode* child;
    struct astNode* sibling;
    unsigned int is_leaf; // this one is for you 7vik ;) : 1 if leaf ob.

}astNode;

// typedef struct astTree
// {
//     astNode* ast_tree_node; 

// }astTree;


#endif