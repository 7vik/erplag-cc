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



astNode* make_ASTnode(int certificate)
{
    astNode* node = (astNode*) malloc(sizeof(astNode));             // malloc check?
    node->node_marker = certificate;
    node->tree_node = NULL;
    //node->next = NULL;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    node->is_leaf = 0;

    return node;
}

astNode* buildLeafAST(PARSE_TREE* t)
{
    int certificate = string_to_enum(t->data->lexeme);
    astNode* node = make_ASTnode(certificate);
    node->tree_node = t->data;
    node->is_leaf = 1;
    return node;
}

// Takes a node and Returns its astTree's root node

astNode* buildAST(PARSE_TREE* root)
{

    if (root != NULL)
    {
        int rule_num = root->data->rule_number;

        switch(rule_num)
        {
            //program -> moduleDeclarations otherModules driverModule otherModules
            case(1):
            {
                // here certi is program, trying to avoid hardcode
                int certificate = string_to_enum(root->data->lexeme);

                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);

                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;
                child0->parent = node;
                child1->parent = node;
                child2->parent = node;
                child3->parent = node;

                //moduleDeclarations and otherModules can be NULL :(
            
                if(child0->node_marker == EPS && child1->node_marker == EPS) //both are EPS
                {
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
                    child0->sibling = child1->sibling;
                    child1->sibling = child2;
                    child2->sibling = child3;
                }
                
                // NOTE: We don't care if last othermodules is EPS, we have a NULL node in EPS. WHich we are fine with. 
                // Similar is the case when child1 is EPS while child0 is not.
                return node;
                break; // LOL, this is scam
            }
            

            // moduleDeclarations -> moduleDeclaration moduleDeclarations1
            case(2):
            {
                int certificate = string_to_enum(root->data->lexeme);

                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->sibling = child1;
                return child0;
                break;
            }
            
            // moduleDeclarations -> EPS
            case(3):
            {
                return buildLeafAST(root->kids[0]);
            }

            // moduleDeclaration -> DECLARE MODULE ID SEMICOL
            case(4):
            {
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->data;
                free(root->kids[0]);
                free(root->kids[1]);
                free(root->kids[3]);
                node->tree_node = root->kids[2]->data;
                node->is_leaf = 1;
                return node;
                break;  
            }

            // otherModules -> module otherModules1

            case(5):
            {
                int certificate = string_to_enum(root->data->lexeme);

                astNode* child0 = buildAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                child0->sibling = child1->sibling;
                return child0;

                break;
            }
            
            // otherModules -> EPS
            case(6):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }


            // driverModule -> DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef
            case(7):
            {
                int certificate = string_to_enum(root->data->lexeme);
                free(root->kids[0]);
                free(root->kids[1]);
                free(root->kids[2]);
                free(root->kids[3]);
                astNode* child4 = buildAST(root->kids[4]);
                return child4;

                break;
            }

            // module -> DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef
            case(8):
            {
                // note to continuer

                //module->child hoga ID node
                //Id vaali node ka sibling hoga input_plist waala AST, make sure you do make_node in input_plist rule
                //uska sibling hoga ret ka ASt, uska sibling moduleDef ka AST, again iss rule mein make_node hoga
                //you can use make_code code. Feel free to add things. Like you can auto rule for creating free nodes too. Simple logic.  
                // run ./make 7 10 11 and answer 1

                int certificate = string_to_enum(root->data->lexeme);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
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
                int certificate = string_to_enum(root->data->lexeme);
                
                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child2->parent = node;
                node->child = child2;
                return node;
                
                break;
            }
            
            case(10)://ret -> EPS
            
            {
                    //To do
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
                    
            }
            
            case(11)://input_plist_lr -> COMMA ID COLON datatype input_plist_lr 
            
            {
                    //To do
                int certificate = string_to_enum(root->data->lexeme);
                
                free(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                astNode* child4 = buildAST(root->kids[4]);
                child1->sibling = child3;
                child3->sibling = child4;
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child1->parent = node;
                child3->parent = node;
                child4->parent = node;
                node->child = child1;
                return node;
                
                break;
            }
            
            case(12)://input_plist_lr -> EPS
            {
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            
                    //To do
            }
            
            case(13)://input_plist -> ID COLON datatype input_plist_lr
            
            {
                int certificate = string_to_enum(root->data->lexeme);
                
                astNode* child0 = buildAST(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                child0->sibling = child2;
                child2->sibling = child3;
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                child2->parent = node;
                child3->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(14)://output_plist_lr -> COMMA ID COLON type output_plist_lr 
            
            {
                int certificate = string_to_enum(root->data->lexeme);
                
                free(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                astNode* child4 = buildAST(root->kids[4]);
                child1->sibling = child3;
                child3->sibling = child4;
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child1->parent = node;
                child3->parent = node;
                child4->parent = node;
                node->child = child1;
                return node;
                
                break;
                    //To do
            }
            
            case(15)://output_plist_lr -> EPS
            
            {
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
                    //To do
            }
            
            case(16)://output_plist -> ID COLON type output_plist_lr
            
            {
                int certificate = string_to_enum(root->data->lexeme);
                
                astNode* child0 = buildAST(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                child0->sibling = child2;
                child2->sibling = child3;
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                child2->parent = node;
                child3->parent = node;
                node->child = child0;
                return node;
            
            break;
                    //To do
            }
            
            case(17):
            {
                
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(18):
            {   
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(19):
            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(20):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                free(root->kids[3]);
                free(root->kids[4]);
                astNode* child5 = buildAST(root->kids[5]);
                child2->sibling = child5;
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child2->parent = node;
                child5->parent = node;
                node->child = child2;
                return node;
                
                break;
                    //To do
            }
            
            case(21):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                child0->sibling = child2;
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                child2->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(22):
            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(23):
            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(24):
            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(25):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
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
            
            case(26):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
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
            
            case(27)://statements -> EPS
            
            {
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
                    //To do
            }
            
            case(28):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(29):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(30):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(31):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(32):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(33):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
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
            
            case(34):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
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
            
            case(35):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
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
            
            case(36):
            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(37):
            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(38):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
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
            
            case(39):
            {
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
                    //To do
            }
            
            case(40):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(41):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(42):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }
            
            case(43):
            {
                int certificate = string_to_enum(root->data->lexeme);
            
                astNode* child0 = buildAST(root->kids[0]);
                
                astNode* node = make_ASTnode(certificate);
                
                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;
                return node;
                
                break;
                    //To do
            }

            // op1 -> PLUS
            case(80):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // op1 -> MINUS
            case(81):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // op2 -> MUL
            case(82):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // op2 -> DIV
            case(83):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }
            
            // logicalOp -> AND
            case(84):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }
            // logicalOp -> OR
            case(85):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }
            // relationalOp -> LT
            case(86):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }
            // relationalOp -> LE
            case(87):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }
            // relationalOp -> GT
            case(88):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // relationalOp -> GE
            case(89):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // relationalOp -> EQ
            case(90):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // relationalOp -> NE
            case(91):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // declareStmt -> DECLARE idList COLON datatype SEMICOL
            // ./meta 1 3
            // add free of remaining kids
            case(92):
            {
                int certificate = string_to_enum(root->data->lexeme);

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
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // value -> TRUE
            case(94):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // value -> FALSE
            case(95):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }

            // caseStmts -> CASE value COLON statements BREAK SEMICOL caseStmt
            // ./meta 1 3 6; generates this code automatically !!
            case(96):
            {
                int certificate = string_to_enum(root->data->lexeme);

                free(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                free(root->kids[4]);
                free(root->kids[5]);
                astNode* child6 = buildAST(root->kids[6]);

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child1->parent = node;
                child3->parent = node;
                child6->parent = node;
                child1->sibling = child3;
                child3->sibling = child6;
                node->child = child1;
                return node;

                break;
            }
            
            // caseStmt -> CASE value COLON statements BREAK SEMICOL caseStmt1
            // ./meta 1 3 6
            case(97):
            {
                int certificate = string_to_enum(root->data->lexeme);

                free(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                free(root->kids[2]);
                astNode* child3 = buildAST(root->kids[3]);
                free(root->kids[4]);
                free(root->kids[5]);
                astNode* child6 = buildAST(root->kids[6]);
                child1->sibling = child3;
                child3->sibling = child6;

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child1->parent = node;
                child3->parent = node;
                child6->parent = node;
                node->child = child1;
                return node;

                break;
            }

            // caseStmt -> EPS
            case(98):
            {
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }
            
            // default_nt -> DEFAULT COLON statements BREAK SEMICOL
            // ./meta 2
            case(99):
            {
                int certificate = string_to_enum(root->data->lexeme);

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
                int certificate = string_to_enum(root->kids[0]->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            }
            
            // conditionalStmt -> SWITCH BO ID BC START caseStmts default_nt END
            // ./meta 2 5 6
            // need to handle ID case
            case(101):
            {
                int certificate = string_to_enum(root->data->lexeme);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]); //handle ID here, change to buildLeafAST
                free(root->kids[3]);
                free(root->kids[4]);
                astNode* child5 = buildAST(root->kids[5]);
                astNode* child6 = buildAST(root->kids[6]);
                child2->sibling = child5;
                child5->sibling = child6;

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child2->parent = node;
                child5->parent = node;
                child6->parent = node;
                node->child = child2;
                return node;

                break;
            }

            // range -> NUM1 RANGEOP NUM2
            // ./meta 0 1 2; doesn't help much in this case
            case(102):
            {
                int certificate = string_to_enum(root->data->lexeme);

                astNode* child0 = buildLeafAST(root->kids[0]);
                astNode* child1 = buildAST(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]);
                child0->sibling = child2;

                child0->parent = child1;
                child2->parent = child1;
                child1->child = child0;
                return child1;

                break;
            }

            // iterativeStmt -> FOR BO ID IN range BC START statements END
            // ./meta 2 4 7; No change required, generates perfect code!!
            case(103):
            {
                int certificate = string_to_enum(root->data->lexeme);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildLeafAST(root->kids[2]);
                free(root->kids[3]);
                astNode* child4 = buildAST(root->kids[4]);
                free(root->kids[5]);
                free(root->kids[6]);
                astNode* child7 = buildAST(root->kids[7]);
                child2->sibling = child4;
                child4->sibling = child7;

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child2->parent = node;
                child4->parent = node;
                child7->parent = node;
                node->child = child2;
                return node;

                break;
            }

            // iterativeStmt -> WHILE BO arithmeticOrBooleanExpression BC START statements END
            // ./meta 2 5; perfect again!!
            case(104):
            {
                int certificate = string_to_enum(root->data->lexeme);

                free(root->kids[0]);
                free(root->kids[1]);
                astNode* child2 = buildAST(root->kids[2]);
                free(root->kids[3]);
                free(root->kids[4]);
                astNode* child5 = buildAST(root->kids[5]);
                child2->sibling = child5;

                astNode* node = make_ASTnode(certificate);

                node->tree_node = root->data;
                child2->parent = node;
                child5->parent = node;
                node->child = child2;
                return node;

                break;
            }
            default:
            {
                printf("No rule number matching, rule number: %d", rule_num);
                break;
            }
        }
        
    }

    else
    {
        printf("Input too buildAST is NULL. BAD\n");
        exit(1);
        return NULL;
    } 
    return NULL;
}
int main()          // driver
{
    return 0;
}