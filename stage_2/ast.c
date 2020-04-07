//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// gcc ast.c parser.c lexer.c hash.c bool.c 
#include<stdio.h>
#include<assert.h>

#include "ast.h"

/* 
Algorithm:  return: abstract syntax tree 
            from:   concrete parse tree obtained from the parser

1. For each rule in the grammar, define semantic rules for value and type attributes.
2. Terminals (leaf nodes) do not have any inherited attributes, so directly fill them.
3. Don't lose operators and keywords, names, identifiers.
AST -> address

Doubts:
1. Do we need to store line numbers in the AST node to yield semantic errors?
2. Except 'type' and 'value' fields, what else is required?
3. What are the 'type' and 'value' for nodes for which they are not defined?
4. Algorithm for AST: order of evaluation (postorder for syn attributes)
5. If a node isn't a leafnode, how do we know which grammar rule we used?           (add rule to parse tree node)
6. Parser stack implementation and dependancy graphs

*/

int num_ast_nodes = 0;
int num_parse_nodes = 0;

astNode* make_ASTnode(int certificate)
{
    astNode* node = (astNode*) malloc(sizeof(astNode));
    if(node == NULL)
    {
        printf("Malloc error. Terminating.\n\n"); 
        exit(5);
    }
    node->node_marker = certificate;
    node->tree_node = NULL;
    //node->next = NULL;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    node->is_leaf = 0;
    num_ast_nodes++;
    return node;
}

astNode* buildLeafAST(PARSE_TREE* t)
{
    int certificate = string_to_enum(t->data->node_symbol);
    astNode* node = make_ASTnode(certificate);
    node->tree_node = t->data;
    node->is_leaf = 1;
    num_parse_nodes++;
    return node;
}

astNode* traverse_and_add_left(astNode* parent, astNode* child)
{
    astNode* ptr = parent;
    astNode* temp = ptr->child;

    while(temp != NULL)
    {
        if(temp->sibling == NULL)
        {
            ptr->child = child;
            child->parent = ptr;
            child->sibling = temp;
            break;
        }
        ptr = temp;
        temp = temp->child;
    }

    return parent;
}

// Takes a node and Returns its astTree's root node

astNode* buildAST(PARSE_TREE* root)
{

    if (root != NULL)
    {
        int rule_num = root->data->rule_number;
        num_parse_nodes++;
        // printf("Rule number: %d\n", rule_num);

        switch(rule_num)
        {
            //program -> moduleDeclarations otherModules driverModule otherModules
            case(1):
            {
                // here certi is program, trying to avoid hardcode
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                
                // printf("%s\n", variables_array[child1->node_marker]);

                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;
                child0->parent = node;
                child1->parent = node;
                child2->parent = node;
                child3->parent = node;

                
                //moduleDeclarations and otherModules can be NULL :(
            
                if(child0->node_marker == EPS && child1->node_marker == EPS) //both are EPS
                {
                    // printf("here\n");
                    node->child = child2;
                    free(child0);
                    free(child1);
                    child2->sibling = child3;
                }

                else if(child0->node_marker == EPS)
                {
                    free(child0);
                    node->child = child1;
                    child1->sibling = child2;
                    child2->sibling = child3;
                }

                else 
                {
                    node->child = child0;
                    child0->sibling = child1;
                    child1->sibling = child2;
                    child2->sibling = child3;
                }
                
                // NOTE: We don't care if last othermodules is EPS, we have a NULL node in EPS. WHich we are fine with. 
                // Similar is the case when child1 is EPS while child0 is not.
                return node;
            }
            

            // moduleDeclarations -> moduleDeclaration moduleDeclarations1
            case(2):
            {
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;

                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->parent = node;

                node->child = child0;
                astNode* temp = child1->child;
                child0->sibling = temp;
                child1->child = NULL;
                free(child1);
                if(temp != NULL)
                    temp->parent = NULL;
                
                temp = node->child;
                while(temp != NULL)
                {
                    temp->parent = node;
                    temp = temp->sibling;
                }
                return node;
            }
            
            // moduleDeclarations -> EPS
            case(3):
            {
                return buildLeafAST(root->kids[0]);
            }

            // moduleDeclaration -> DECLARE MODULE ID SEMICOL
            case(4):
            {
                int certificate = string_to_enum(root->kids[2]->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                free(root->kids[0]);
                free(root->kids[1]);
                free(root->kids[3]);
                node->tree_node = root->kids[2]->data;
                node->is_leaf = 1;
                return node;  
            }

            // otherModules -> module otherModules1

            case(5):
            {
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;

                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->parent = node;

                node->child = child0;
                astNode* temp = child1->child;
                child0->sibling = temp;
                child1->child = NULL;
                free(child1);
                if(temp != NULL)
                    temp->parent = NULL;

                temp = node->child;
                while(temp != NULL)
                {
                    temp->parent = node;
                    temp = temp->sibling;
                }
                return node;
            }
            
            // otherModules -> EPS
            case(6):
            {
                return buildLeafAST(root->kids[0]);
            }


            // driverModule -> DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef
            case(7):
            {
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;
                free(root->kids[0]);
                free(root->kids[1]);
                free(root->kids[2]);
                free(root->kids[3]);
                astNode* child4 = buildAST(root->kids[4]);
                node->child = child4;
                child4->parent = node;
                return node;
            }

            // module -> DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef
            case(8):
            {
                // You can use make_code code. Feel free to add things. Like you can auto rule for creating free nodes too. Simple logic.  
                // Run ./make 2 7 10 11 and answer 1.
                // But use your own wisdom to handle intricacies.

                int certificate = string_to_enum(root->data->node_symbol);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]);
                free(root->kids[3]);
                free(root->kids[4]);
                free(root->kids[5]);
                free(root->kids[6]);
                astNode* child7 = buildAST(root->kids[7]);
                free(root->kids[8]);
                free(root->kids[9]);
                astNode* child10 = buildAST(root->kids[10]);
                astNode* child11 = buildAST(root->kids[11]);
                child2->sibling = child7;
                child7->sibling = child10;
                child10->sibling = child11;

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child2->parent = node;
                child7->parent = node;
                child10->parent = node;
                child11->parent = node;
                node->child = child2;
                return node;                
            }

            case(9)://ret -> RETURNS SQBO output_plist SQBC SEMICOL 
            
            {
                int certificate = string_to_enum(root->data->node_symbol);
                
                free(root->kids[0]);
                free(root->kids[1]);
                free(root->kids[3]);
                free(root->kids[4]);

                astNode* child2 = buildAST(root->kids[2]);
                
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;

                node->child = child2;

                astNode* temp = child2;
                while(temp != NULL)
                {
                    temp->parent = node;
                    temp = temp->sibling;
                }

                return node;
            }
            
            case(10)://ret -> EPS -- in case of no output parameter, return a node with no child.
            {
                astNode* node = make_ASTnode(string_to_enum(root->data->node_symbol));
                node->tree_node = root->data;
                node->is_leaf = 1;
                return node;     
            }
            
            case(11)://input_plist_lr -> COMMA ID COLON datatype input_plist_lr1
            {
                astNode* new = make_ASTnode(input_plist);   // Making a new node - Hardcoding! Though, doesn't matter.
                TREE_NODE* var = (TREE_NODE*) malloc(sizeof(TREE_NODE));
                if(var == NULL)
                {
                    printf("Malloc error. Terminating.\n\n"); 
                    exit(5);
                }
                var->node_symbol = "id_type";   // only initializing one field; no need to initialize others
                new->tree_node = var;

                free(root->kids[0]);
                
                astNode* child1 = buildLeafAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                
                child1->sibling = child3;
                child1->parent = new;
                child3->parent = new;
                new->child = child1;

                astNode* child4 = buildAST(root->kids[4]);  
                // creating a chain
                new->sibling = child4;

                return new;
            }
            
            case(12)://input_plist_lr -> EPS
            {
                return NULL;
            }
            
            case(13)://input_plist -> ID COLON datatype input_plist_lr
            
            {
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* new = make_ASTnode(certificate);   // making a new node
                TREE_NODE* var = (TREE_NODE*) malloc(sizeof(TREE_NODE));
                if(var == NULL)
                {
                    printf("Malloc error. Terminating.\n\n"); 
                    exit(5);
                }
                var->node_symbol = "id_type";   // only initializing one field; no need to initialize others
                new->tree_node = var;

                astNode* node = make_ASTnode(certificate);  // keeping the same certificate; shouldn't matter much
                node->tree_node = root->data;

                astNode* child0 = buildLeafAST(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);

                child0->sibling = child2;
                child0->parent = new;
                child2->parent = new;
                new->child = child0;

                astNode* child3 = buildAST(root->kids[3]);
                new->sibling = child3;

                node->child = new;
                astNode* temp = new;
                while(temp != NULL)
                {
                    temp->parent = node;
                    temp = temp->sibling;
                }

                return node;
            }
            
            case(14)://output_plist_lr -> COMMA ID COLON type output_plist_lr 
            {
                astNode* new = make_ASTnode(output_plist);   // Making a new node - Hardcoding! Though, doesn't matter.
                TREE_NODE* var = (TREE_NODE*) malloc(sizeof(TREE_NODE));
                if(var == NULL)
                {
                    printf("Malloc error. Terminating.\n\n"); 
                    exit(5);
                }
                var->node_symbol = "id_type";   // only initializing one field; no need to initialize others
                new->tree_node = var;

                free(root->kids[0]);
                
                astNode* child1 = buildLeafAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                
                child1->sibling = child3;
                child1->parent = new;
                child3->parent = new;
                new->child = child1;

                astNode* child4 = buildAST(root->kids[4]);  
                // creating a chain
                new->sibling = child4;

                return new;
            }
            
            case(15)://output_plist_lr -> EPS
            {
                return NULL;
            }
            
            case(16)://output_plist -> ID COLON type output_plist_lr
            {
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* new = make_ASTnode(certificate);   // making a new node
                TREE_NODE* var = (TREE_NODE*) malloc(sizeof(TREE_NODE));
                if(var == NULL)
                {
                    printf("Malloc error. Terminating.\n\n"); 
                    exit(5);
                }
                var->node_symbol = "id_type";   // only initializing one field; no need to initialize others
                new->tree_node = var;

                astNode* child0 = buildLeafAST(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);

                child0->sibling = child2;
                child0->parent = new;
                child2->parent = new;
                new->child = child0;

                astNode* child3 = buildAST(root->kids[3]);
                new->sibling = child3;

                return new;
            }
            
            case(17)://datatype -> INTEGER 
            {
                return buildLeafAST(root->kids[0]);
            }
            
            case(18)://datatype -> REAL 
            {   
                return buildLeafAST(root->kids[0]);
            }
            
            case(19)://datatype -> BOOLEAN 
            {
                return buildLeafAST(root->kids[0]);
            }
            
            case(20)://datatype -> ARRAY SQBO rangeArr SQBC OF type
            {
                int certificate = string_to_enum(root->kids[0]->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;

                free(root->kids[1]);

                astNode* child2 = buildAST(root->kids[2]);

                free(root->kids[3]);
                free(root->kids[4]);

                astNode* child5 = buildAST(root->kids[5]);
                child2->sibling = child5;
                
                
                child2->parent = node;
                child5->parent = node;
                node->child = child2;
                return node;
            }
            
            case(21)://rangeArr -> index_nt RANGEOP index_nt
            {
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;

                astNode* child0 = buildAST(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                child0->sibling = child2;
                
                child0->parent = node;
                child2->parent = node;
                node->child = child0;
                return node;
            }
            
            case(22)://type -> INTEGER 
            {
                return buildLeafAST(root->kids[0]);
            }
            
            case(23)://type -> REAL 
            {
                return buildLeafAST(root->kids[0]);
            }
            
            case(24)://type -> BOOLEAN
            {
                return buildLeafAST(root->kids[0]);
            }
            
            case(25)://moduleDef -> START statements END

            {
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* child0 = buildLeafAST(root->kids[0]);
                //free(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]);
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                child1->parent = node;
                child2->parent = node;
                node->child = child0;
                child0->sibling = child1;
                child1->sibling = child2;
                return node;
                
                break;
                    //To do
            }
            
            case(26)://statements -> statement statements 

            {
               // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                // astNode* child1 = buildAST(root->kids[1]);
                // child0->sibling = child1;
                
                // // astNode* node = make_ASTnode(certificate);
                
                // // node->tree_node = root->data;
                // // child0->parent = node;
                // // child1->parent = node;
                // // node->child = child0;

                // return child0;

                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;

                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->parent = node;

                node->child = child0;
                astNode* temp = child1->child;
                child0->sibling = temp;
                child1->child = NULL;
                free(child1);
                if(temp != NULL)
                    temp->parent = NULL;

                temp = node->child;
                while(temp != NULL)
                {
                    temp->parent = node;
                    temp = temp->sibling;
                }
                return node;
                
                break;
                    //To do
            }
            
            case(27)://statements -> EPS
            
            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(28)://statement -> ioStmt 

            {
                return buildAST(root->kids[0]);
                // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                
                // astNode* node = make_ASTnode(certificate);
                
                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;
                // return node;
                
                // break;
                    //To do
            }
            
            case(29)://statement -> simpleStmt 

            {
                return buildAST(root->kids[0]);
                // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                
                // astNode* node = make_ASTnode(certificate);
                
                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;
                // return node;
                
                // break;
                    //To do
            }
            
            case(30)://statement -> declareStmt 

            {
                return buildAST(root->kids[0]);

                // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                
                // astNode* node = make_ASTnode(certificate);
                
                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;
                // return node;
                
                // break;
                    //To do
            }
            
            case(31)://statement -> conditionalStmt 

            {
                return buildAST(root->kids[0]);

                // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                
                // astNode* node = make_ASTnode(certificate);
                
                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;
                // return node;
                
                // break;
                    //To do
            }
            
            case(32)://statement -> iterativeStmt

            {
                return buildAST(root->kids[0]);

                // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                
                // astNode* node = make_ASTnode(certificate);
                
                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;
                // return node;
                
                // break;
                    //To do
            }
            
            case(33)://ioStmt -> GET_VALUE BO ID BC SEMICOL 

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child2->parent = node;
                node->child = child2;
                return node;
                
                break;
                    //To do
            }
            
            case(34)://ioStmt -> PRINT BO printOpt BC SEMICOL

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child2->parent = node;
                node->child = child2;
                return node;
                
                break;
                    //To do
            }
            
            case(35)://var -> ID whichId 

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
                astNode* child0 = buildLeafAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->sibling = child1;
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                child1->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(36)://var -> NUM

            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(37)://var -> RNUM

            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(38)://whichId -> SQBO index_nt SQBC 

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
                free(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child1->parent = node;
                node->child = child1;
                return node;
                
                break;
                    //To do
            }
            
            case(39)://whichId -> EPS

            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(40)://printOpt -> booleanConst

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(41)://printOpt -> var

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(42)://simpleStmt -> assignmentStmt 

            {
                return buildAST(root->kids[0]);
                // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                
                // astNode* node = make_ASTnode(certificate);
                
                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;
                // return node;
                
                // break;
                    //To do
            }
            
            case(43)://simpleStmt -> moduleReuseStmt

            {
                return buildAST(root->kids[0]);
                // int certificate = string_to_enum(root->data->node_symbol);
            
                // astNode* child0 = buildAST(root->kids[0]);
                
                // astNode* node = make_ASTnode(certificate);
                
                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;
                // return node;
                
                // break;
                    //To do
            }

            //assignmentStmt -> ID whichStmt
            case(44):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                astNode* child0 = buildLeafAST(root->kids[0]); //ID
                astNode* child1 = buildAST(root->kids[1]);  //whichstmt, with "=" present at root.
                astNode* node = make_ASTnode(certificate);  
                
                //We have to keep "=" at the root only, in the subtree under assignmentStmt
                
                node->tree_node = root->data;
                node->child = child1;
                child1->parent = node;

                astNode* temp = child1->child; 
                child1->child = child0;
                child0->parent = child1;
                child0->sibling = temp;

                return node;
            }

            // whichStmt -> lvalueIDStmt
            case(45):
            {
                return buildAST(root->kids[0]); //pass on the pointer up the AST
            }


            // whichStmt -> lvalueARRStmt
            case(46):
            {
                return buildAST(root->kids[0]); //pass on the pointer up the AST
            }


            // lalueIDStmt -> ASSIGNOP expression SEMICOL
            case(47):
            {
                astNode* node = make_ASTnode(string_to_enum(root->kids[0]->data->node_symbol));
                node->tree_node = root->kids[0]->data; // Information of "=" to be stored in node.
                astNode* child1 = buildAST(root->kids[1]);

                child1->parent = node;
                node->child = child1;
                free(root->kids[2]);

                return node; 
            }

            // lvalueARRStmt -> SQBO index_nt SQBC ASSIGNOP expression SEMICOL
            case(48):
            {
                free(root->kids[0]); //SQBO

                astNode* child1 = buildAST(root->kids[1]); //index_nt

                free(root->kids[2]); //SQBC

                astNode* node = make_ASTnode(string_to_enum(root->kids[3]->data->node_symbol));
                node->tree_node = root->kids[3]->data; // Information of "=" to be stored in node.

                astNode* child4 = buildAST(root->kids[4]); //expression

                free(root->kids[5]); //SEMICOL

                node->child = child1;
                child1->sibling = child4;
                child1->parent = node;
                child4->parent = node;

                return node;
            }

            // index_nt -> NUM 
            case(49):
            {
                return buildLeafAST(root->kids[0]);   
            }

            // index_nt -> ID
            case(50):
            {
                return buildLeafAST(root->kids[0]);
            }

            // moduleReuseStmt -> optional USE MODULE ID WITH PARAMETERS idList SEMICOL
            case(51):
            {
                free(root->kids[1]); //USE
                free(root->kids[2]); //MODULE
                free(root->kids[4]); //WITH
                free(root->kids[5]); //PARAMETERS
                free(root->kids[7]); //SEMICOL

                astNode* node = make_ASTnode(string_to_enum(root->data->node_symbol));
                node->tree_node = root->data;

                astNode* child0 = buildAST(root->kids[0]); //optional
                astNode* child3 = buildLeafAST(root->kids[3]); //ID
                astNode* child6 = buildAST(root->kids[6]); //but this is a linked list!
                astNode* list_id = make_ASTnode(string_to_enum(root->kids[6]->data->node_symbol)); //Will store the address of the head of linked list of identifiers

                list_id->child = child6;
                child6->parent = list_id;

                child0->sibling = child3;
                child3->sibling = list_id;

                node->child = child0;
                child0->parent = node;
                child3->parent = node;
                list_id->parent = node;

                return node;
            }

            // optional -> SQBO idList SQBC ASSIGNOP
            case(52):
            {
                free(root->kids[0]); //SQBO
    
                astNode* child1 = buildAST(root->kids[1]); //idList

                free(root->kids[2]); //SQBC

                astNode* node = make_ASTnode(string_to_enum(root->kids[3]->data->node_symbol));
                node->tree_node =  root->kids[3]->data; // Information of "=" to be stored in node.

                node->child = child1;
                child1->parent = node;

                return node;
            }
    

            // optional -> EPS
            case(53):
            {
                return buildLeafAST(root->kids[0]);
            }

            // idList_lr -> COMMA ID idList_lr1
            case(54):
            {
                free(root->kids[0]);
                astNode* child1 = buildLeafAST(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);

                child1->sibling = child2;
                return child1;
            }

            // idList_lr -> EPS
            case(55):
            {
                return buildLeafAST(root->kids[0]);
            }

            // idList -> ID idList_lr
            case(56):
            {
                astNode* child0 = buildLeafAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);

                child0->sibling = child1;
                return child0;
            }

            // expression -> unaryExpression
            case(57):
            {
                return buildAST(root->kids[0]);
                // astNode* node = make_ASTnode(string_to_enum(root->data->node_symbol));
                // astNode* child0 = buildAST(root->kids[0]);

                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;

                // return node;
            }

            // expression -> arithmeticOrBooleanExpression
            case(58):
            {
                return buildAST(root->kids[0]);
                // astNode* node = make_ASTnode(string_to_enum(root->data->node_symbol));
                // astNode* child0 = buildAST(root->kids[0]);

                // node->tree_node = root->data;
                // child0->parent = node;
                // node->child = child0;

                // return node;
            }

            // unaryExpression -> MINUS unary_opt
            case(59):
            {
                astNode* child0 = buildLeafAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->sibling = child1;
                return child0;
            }

            // unaryExpression -> PLUS unary_opt
            case(60):
            {
                astNode* child0 = buildLeafAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->sibling = child1;
                return child0;    
            }

            // unary_opt -> BO arithmeticExpr BC
            case(61):
            {
                free(root->kids[0]);
                free(root->kids[2]);
                return buildAST(root->kids[1]);
            }

            // unary_opt -> var
            case(62):
            {
                return buildAST(root->kids[0]);
            }
   
            // arithmeticOrBooleanExpression -> opt_expr opt_expr_lr
            case(63):
            {
                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                if(child1->node_marker == EPS)
                {
                    free(child1);
                    return child0;
                }
                else
                {
                    child1 = traverse_and_add_left(child1, child0);
                    return child1;    
                }
            }

            // opt_expr_lr -> logicalOp opt_expr opt_expr_lr1
            case(64):
            {
                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);

                child0->child = child1;
                child1->parent = child0;
                if(child2->node_marker != EPS)
                {
                    child2 = traverse_and_add_left(child2, child0);
                }
                else /* child2->node_marker is EPS---> just pass on the pointer after freeing node pointed to by child2 */
                {
                    free(child2);
                    child2 = child0;
                }
                return child2;
            }
    
            // opt_expr_lr -> EPS
            case(65):
            {
                return buildLeafAST(root->kids[0]);
            }

            // opt_expr -> arithmeticExpr one_more_opt
            case(66):
            {
                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                if(child1->node_marker == EPS)
                {
                    free(child1);
                    return child0;
                }
                else
                {
                    child1 = traverse_and_add_left(child1, child0);
                    return child1;    
                }    
            }

            // opt_expr -> booleanConst
            case(67):
            {
                return buildAST(root->kids[0]);
            }
    
            // one_more_opt -> relationalOp arithmeticExpr
            case(68):
            {
                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->child = child1;
                child1->parent = child0;

                return child0;
            }

            // one_more_opt -> EPS
            case(69):
            {
                return buildLeafAST(root->kids[0]);
            }

            // booleanConst -> TRUE
            case(70):
            {
                return buildLeafAST(root->kids[0]);
            }

            // booleanConst -> FALSE
            case(71):
            {
                return buildLeafAST(root->kids[0]);
            }

            // arithmeticExpr_lr -> op1 term arithmeticExpr_lr1
            case(72):
            {
                astNode* child0 = buildAST(root->kids[0]);
                //child0->node_marker = root->kids[0]->data;

                astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);

                child0->child = child1;
                child1->parent = child0;
                if(child2->node_marker != EPS)
                {
                    child2 = traverse_and_add_left(child2, child0);
                }
                else /* child2->node_marker is EPS---> just pass on the pointer after freeing node pointed to by child2 */
                {
                    free(child2);
                    child2 = child0;
                }
                return child2;
            }

            // arithmeticExpr_lr -> EPS
            case(73):
            {
                return buildLeafAST(root->kids[0]);
            }

            // arithmeticExpr -> term arithmeticExpr_lr
            case(74):
            {
                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                if(child1->node_marker == EPS)
                {
                    free(child1);
                    return child0;
                }
                else
                {
                    child1 = traverse_and_add_left(child1, child0);
                    return child1;
                }
            }

            // term_lr -> op2 factor term_lr1
            case(75):
            {
                astNode* child0 = buildAST(root->kids[0]);
                //child0->node_marker = root->kids[0]->data;

                astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);

                child0->child = child1;
                child1->parent = child0;
                if(child2->node_marker != EPS)
                {
                    child2 = traverse_and_add_left(child2, child0);
                }
                else /* child2->node_marker is EPS---> just pass on the pointer after freeing node pointed to by child2 */
                {
                    free(child2);
                    child2 = child0;
                }
                return child2; 
            }

            // term_lr -> EPS
            case(76):
            {
                return buildLeafAST(root->kids[0]);
            }

            // term -> factor term_lr
            case(77):
            {
                /*
                term.addr = traverse_and_add_left(term_lr.addr, factor.addr)
                */
                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                if(child1->node_marker == EPS)
                {
                    free(child1);
                    return child0;
                }
                else
                {
                    child1 = traverse_and_add_left(child1, child0);
                    return child1;
                }    
            }

            // factor -> BO arithmeticOrBooleanExpression BC
            case(78):
            {
                free(root->kids[0]);
                free(root->kids[2]);
                return buildAST(root->kids[1]);
            }

            // factor -> var
            case(79):
            {
                return buildAST(root->kids[0]);
            }

            // op1 -> PLUS
            case(80):
            {
                return buildLeafAST(root->kids[0]);
            }

            // op1 -> MINUS
            case(81):
            {
                return buildLeafAST(root->kids[0]);
            }

            // op2 -> MUL
            case(82):
            {
                return buildLeafAST(root->kids[0]);
            }

            // op2 -> DIV
            case(83):
            {
                return buildLeafAST(root->kids[0]);
            }
            
            // logicalOp -> AND
            case(84):
            {
                return buildLeafAST(root->kids[0]);
            }
            // logicalOp -> OR
            case(85):
            {
                return buildLeafAST(root->kids[0]);
            }
            // relationalOp -> LT
            case(86):
            {
                return buildLeafAST(root->kids[0]);
            }
            // relationalOp -> LE
            case(87):
            {
                return buildLeafAST(root->kids[0]);
            }
            // relationalOp -> GT
            case(88):
            {
                return buildLeafAST(root->kids[0]);
            }

            // relationalOp -> GE
            case(89):
            {
                return buildLeafAST(root->kids[0]);
            }

            // relationalOp -> EQ
            case(90):
            {
                return buildLeafAST(root->kids[0]);
            }

            // relationalOp -> NE
            case(91):
            {
                return buildLeafAST(root->kids[0]);
            }

            // declareStmt -> DECLARE idList COLON datatype SEMICOL
            // ./meta 1 3
            // add free of remaining kids
            case(92):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                free(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                free(root->kids[4]);
                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child1->parent = node;
                child3->parent = node;
                child1->sibling = child3;
                node->child = child1;
                return node;

                break;
            }

            // value -> NUM
            case(93):
            {
                return buildLeafAST(root->kids[0]);
            }

            // value -> TRUE
            case(94):
            {
                return buildLeafAST(root->kids[0]);
            }

            // value -> FALSE
            case(95):
            {
                return buildLeafAST(root->kids[0]);
            }

            // caseStmts -> CASE value COLON statements BREAK SEMICOL caseStmt
            // ./meta 1 3 6; generates this code automatically !!
            case(96):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                
                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                
                astNode* new = make_ASTnode(caseStmt);   // Making a new node - Hardcoding! Though, doesn't matter.
                TREE_NODE* var = (TREE_NODE*) malloc(sizeof(TREE_NODE));
                if(var == NULL)
                {
                    printf("Malloc error. Terminating.\n\n"); 
                    exit(5);
                }
                var->node_symbol = "caseStmt";   // only initializing one field; no need to initialize others
                new->tree_node = var;
                new->tree_node->lexeme = "caseStmt";

                free(root->kids[0]);
                
                astNode* child1 = buildAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                
                child1->sibling = child3;
                child1->parent = new;
                child3->parent = new;
                new->child = child1;

                
                free(root->kids[4]);
                free(root->kids[5]);
                astNode* child6 = buildAST(root->kids[6]);  
                // creating a chain
                node->child = new;
                astNode* temp = child6->child;
                new->sibling = temp;
                child6->child = NULL;
                free(child6);
                if(temp != NULL)
                    temp->parent = NULL;
                
                temp = node->child;
                while(temp != NULL)
                {
                    temp->parent = node;
                    temp = temp->sibling;
                }
                
                return node;

                break;
            }
            
            // caseStmt -> CASE value COLON statements BREAK SEMICOL caseStmt1
            // ./meta 1 3 6
            case(97):
            {
                 int certificate = string_to_enum(root->data->node_symbol);

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
               

                astNode* new = make_ASTnode(caseStmt);   // Making a new node - Hardcoding! Though, doesn't matter.
                TREE_NODE* var = (TREE_NODE*) malloc(sizeof(TREE_NODE));
                if(var == NULL)
                {
                    printf("Malloc error. Terminating.\n\n"); 
                    exit(5);
                }
                var->node_symbol = "caseStmt";   // only initializing one field; no need to initialize others
                new->tree_node = var;
                new->tree_node->lexeme = "caseStmt";

                free(root->kids[0]);
                
                astNode* child1 = buildAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                
                child1->sibling = child3;
                child1->parent = new;
                child3->parent = new;
                new->child = child1;

                
                free(root->kids[4]);
                free(root->kids[5]);
                astNode* child6 = buildAST(root->kids[6]);  
                // creating a chain
                node->child = new;
                astNode* temp = child6->child;
                new->sibling = temp;
                child6->child = NULL;
                free(child6);
                if(temp != NULL)
                    temp->parent = NULL;
                
                temp = node->child;
                while(temp != NULL)
                {
                    temp->parent = node;
                    temp = temp->sibling;
                }
                
                return node;

                break;
            }

            // caseStmt -> EPS
            case(98):
            {
                return buildLeafAST(root->kids[0]);
            }
            
            // default_nt -> DEFAULT COLON statements BREAK SEMICOL
            // ./meta 2
            case(99):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);

                astNode* node = make_ASTnode(certificate);
                free(root->kids[2]);
                free(root->kids[3]);     

                node->tree_node = root->data;
                child2->parent = node;
                node->child = child2;
                return node;

                break;
            }

            // default_nt -> EPS
            case(100):
            {
                return buildLeafAST(root->kids[0]);
            }
            
            // conditionalStmt -> SWITCH BO ID BC START caseStmts default_nt END
            // ./meta 2 5 6
            // need to handle ID case
            case(101):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]); //handle ID here, change to buildLeafAST
                free(root->kids[3]);
                astNode* child4 = buildLeafAST(root->kids[4]);
                //free(root->kids[4]);
                astNode* child5 = buildAST(root->kids[5]);
                astNode* child6 = buildAST(root->kids[6]);
                child2->sibling = child4;
                child4->sibling = child5;
                child5->sibling = child6;

                astNode* child7 = buildLeafAST(root->kids[7]);
                child6->sibling = child7;
                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child2->parent = node;
                child4->parent = node;
                child5->parent = node;
                child6->parent = node;
                child7->parent = node;
                node->child = child2;
                return node;

                break;
            }

            // range -> NUM1 RANGEOP NUM2
            // ./meta 0 1 2; doesn't help much in this case
            case(102):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                astNode* child0 = buildLeafAST(root->kids[0]);
                // astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]);
                child0->sibling = child2;

                // child0->parent = child1;
                // child2->parent = child1;
                //child1->child = child0;
                return child0;

                break;
            }

            // iterativeStmt -> FOR BO ID IN range BC START statements END
            // ./meta 2 4 7; No change required, generates perfect code!!
            case(103):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]);
                free(root->kids[3]);
                astNode* child4 = buildAST(root->kids[4]);
                free(root->kids[5]);
                astNode* child6 = buildLeafAST(root->kids[6]);
                astNode* child7 = buildAST(root->kids[7]);
                child2->sibling = child4;
                child4->sibling = child6;
                child6->sibling = child7;

                astNode* child8 = buildLeafAST(root->kids[8]);
                child7->sibling = child8;

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child2->parent = node;
                child4->parent = node;
                child7->parent = node;
                child6->parent = node;
                child8->parent = node;
                node->child = child2;
                return node;

                break;
            }

            // iterativeStmt -> WHILE BO arithmeticOrBooleanExpression BC START statements END
            // ./meta 2 5; perfect again!!
            case(104):
            {
                int certificate = string_to_enum(root->data->node_symbol);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                free(root->kids[3]);
                //free(root->kids[4]);
                astNode* child4 = buildLeafAST(root->kids[4]);
                astNode* child5 = buildAST(root->kids[5]);
                child2->sibling = child4;
                child4->sibling = child5;

                astNode* child6 = buildLeafAST(root->kids[6]);
                child5->sibling = child6;
                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child2->parent = node;
                child5->parent = node;
                child4->parent = node;
                child6->parent = node;
                node->child = child2;
                return node;

                break;
            }
            default:
            {
                printf("No rule number matching, rule number: %d, node symbol: %s, is leaf: %d\n", rule_num, root->data->node_symbol, root->data->is_leaf_node);
                break;
            }
        }
        
    }

    else
    {
        printf("Input to buildAST is NULL. BAD\n");
        exit(1);
        return NULL;
    } 
    return NULL;
}

void print_ast_JSON(astNode* t, FILE *fp)
{
    if(t==NULL)
    {
        fprintf(fp,"{\n\"text\": { \"name\": \"NULL\" },\n");
        fprintf(fp,"\"children\": []\n}\n");
        return;
    }

    char *s;

    // if non terminal
    if(t->child != NULL)
    {
        s = variables_array[(t->node_marker)]; //enum to string
    }

    else
    {

        s=malloc(snprintf(NULL, 0, "%s:%s",t->tree_node->token_name,t->tree_node->lexeme)+1);
        sprintf(s,"%s:%s",t->tree_node->token_name,t->tree_node->lexeme);
    }
    
    fprintf(fp,"{\n");
    fprintf(fp,"\"text\": { \"name\": \"%s\" },\n",s);
    if(t->child  != NULL)
    {
        fprintf(fp,"\"collapsed\": true,\n");
        fprintf(fp,"\"children\": [\n");
        
        astNode* temp = t->child;
        while(temp != NULL)
        {
            print_ast_JSON(temp ,fp);
            if(temp->sibling != NULL)
                fprintf(fp,",");
            temp = temp->sibling;
        }
        fprintf(fp,"]\n");
    }
    else
    {
        fprintf(fp,"\"children\":[]\n");
    }
    fprintf(fp,"}\n");
}

void print_parse_tree_JSON(PARSE_TREE* t, FILE *fp){
    if(t==NULL){
        fprintf(fp,"{\n\"text\": { \"name\": \"NULL\" },\n");
        fprintf(fp,"\"children\": []\n}\n");
        return;
    }

    char *s;

    // if non terminal
    if(t->kids[0] != NULL)
    {
        s = t->data->node_symbol; //enum to string
    }

    else
    {
        s=malloc(snprintf(NULL, 0, "%s:%s",t->data->token_name,t->data->lexeme)+1);
        sprintf(s,"%s:%s",t->data->token_name,t->data->lexeme);
        // printf("%s\n",s);
    }
    fprintf(fp,"{\n");
    fprintf(fp,"\"text\": { \"name\": \"%s\" },\n",s);
    if(t->num_of_kids  != 0)
    {
        fprintf(fp,"\"collapsed\": true,\n");
        fprintf(fp,"\"children\": [\n");
        
        //astNode* temp = t->child[0];
        for(int i = 0; i < t->num_of_kids; i++)
        {
            print_parse_tree_JSON(t->kids[i] ,fp);
            if(i != t->num_of_kids - 1) // if not the last node
                fprintf(fp,",");
        }
        fprintf(fp,"]\n");
    }
    else
    {
        fprintf(fp,"\"children\":[]\n");
    }
    fprintf(fp,"}\n");
}

void print_ast_json(astNode* tree,  char *outputfile)
{
    FILE *fp=fopen(outputfile,"w");
    if(fp==NULL){
        printf("Error opening file %s\n",outputfile);
        return;
    }

    fprintf(fp,"{\n");
    fprintf(fp,"\"nodeStructure\":");
    print_ast_JSON(tree,fp);
    fprintf(fp,"}\n");
    printf("AST output to %s\n",outputfile);
    fflush(fp);
}

void print_parse_tree_json(PARSE_TREE* tree,  char *outputfile)
{
    FILE *fp=fopen(outputfile,"w");
    if(fp==NULL){
        printf("Error opening file %s\n",outputfile);
        return;
    }

    fprintf(fp,"{\n");
    fprintf(fp,"\"nodeStructure\":");
    print_parse_tree_JSON(tree,fp);
    fprintf(fp,"}\n");
    printf("Parse tree output to %s\n",outputfile);
    fflush(fp);
}

void print_AST_tree(astNode* tree)
{

    return;
}

// int main(int argc, char* argv[])          // driver
// {
//     if(argc != 3)
//     {
//         printf("Invalid argument count. Expected 3 arguments as in './executable testcase parse_outfile'.");
//         printf("\nAborting Execution!!\n");
//         exit(2);
//     }

//     FILE* test_fp = fopen(argv[1], "r");
//     FILE* test_parse_fp = fopen(argv[2], "w");
//     populate_ht(hash_table, KEYWORDS_FILE);
//     int line_count = 1;
//     TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
//     init_buffer(test_fp, twin_buff);
//     GRAMMAR* grammar = generate_grammar();
//     first_follow *ff = get_first_follow_table(grammar);
//     TABLE *parse_table = (TABLE *) malloc(sizeof(TABLE));
//     create_parse_table(ff, parse_table, grammar);
//     STACK *stack = NULL;
//     PARSE_TREE *tree;
//     parse(grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
//     fprintf(test_parse_fp, "%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s%20s\n\n", "LEXEME", "LINE_NO", "VALUE (if num)", "TOKENAME",  "PARENT", "IS LEAF?", "NODE SYMBOL", "RULE_NUMBER");
//     print_parse_tree(tree, test_parse_fp);
//     print_parse_tree_json(tree, "output_parse_tree.json");

//     printf("Printed Parse Tree in file '%s'.\n", argv[2]);
//     // printf("Rule number of root: %d\n", tree->kids[0]->data->rule_number);
//     astNode* ast_root = buildAST(tree);
//     // printf("H1\n");
//     print_ast_json(ast_root, "output_ast_tree.json");

//     fclose(test_fp);
//     fclose(test_parse_fp);
//     free(twin_buff);
//     free(parse_table);
//     return 0;
// }
