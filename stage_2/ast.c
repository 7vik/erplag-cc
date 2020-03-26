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
        int rule_num = root->data->rule_number + 1;
        printf("Rule number: %d\n", rule_num);

        switch(rule_num)
        {
            //program -> moduleDeclarations otherModules driverModule otherModules
            case(1):
            {
                // here certi is program, trying to avoid hardcode
                printf("dbfbrh\n");
                int certificate = string_to_enum(root->data->node_symbol);
                printf("H1\n");
                astNode* child0 = buildAST(root->kids[0]);
                printf("H2\n");
                astNode* child1 = buildAST(root->kids[1]);
                printf("H3\n");
                astNode* child2 = buildAST(root->kids[2]);
                printf("H4\n");
                astNode* child3 = buildAST(root->kids[3]);
                printf("frhb\n");
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
                int certificate = string_to_enum(root->data->node_symbol);

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
                int certificate = string_to_enum(root->data->node_symbol);
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
                int certificate = string_to_enum(root->data->node_symbol);

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
                int certificate = string_to_enum(root->data->node_symbol);
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
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
                    
            }
            
            case(11)://input_plist_lr -> COMMA ID COLON datatype input_plist_lr 
            
            {
                    //To do
                int certificate = string_to_enum(root->data->node_symbol);
                
                free(root->kids[0]);
                astNode* child1 = buildLeafAST(root->kids[1]);
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
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
            
                    //To do
            }
            
            case(13)://input_plist -> ID COLON datatype input_plist_lr
            
            {
                int certificate = string_to_enum(root->data->node_symbol);
                
                astNode* child0 = buildLeafAST(root->kids[0]);
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
                int certificate = string_to_enum(root->data->node_symbol);
                
                free(root->kids[0]);
                astNode* child1 = buildLeafAST(root->kids[1]);
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
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
                    //To do
            }
            
            case(16)://output_plist -> ID COLON type output_plist_lr
            
            {
                int certificate = string_to_enum(root->data->node_symbol);
                
                astNode* child0 = buildLeafAST(root->kids[0]);
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
            
            case(17)://datatype -> INTEGER 

            {
                
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(18)://datatype -> REAL 

            {   
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(19)://datatype -> BOOLEAN 

            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(20)://datatype -> ARRAY SQBO rangeArr SQBC OF type

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
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
            
            case(21)://rangeArr -> index_nt RANGEOP index_nt

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
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
            
            case(22)://type -> INTEGER 

            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(23)://type -> REAL 

            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(24)://type -> BOOLEAN

            {
                return buildLeafAST(root->kids[0]);
                    //To do
            }
            
            case(25)://moduleDef -> START statements END

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
            
            case(26)://statements -> statement statements 

            {
                int certificate = string_to_enum(root->data->node_symbol);
            
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
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
                    //To do
            }
            
            case(28)://statement -> ioStmt 

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
            
            case(29)://statement -> simpleStmt 

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
            
            case(30)://statement -> declareStmt 

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
            
            case(31)://statement -> conditionalStmt 

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
            
            case(32)://statement -> iterativeStmt

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
                int certificate = string_to_enum(root->data->node_symbol);
                astNode* node = make_ASTnode(certificate);
                node->tree_node = root->kids[0]->data;
                node->is_leaf = 1;
                return node;
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
            
            case(43)://simpleStmt -> moduleReuseStmt

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
                astNode* node = make_ASTnode(string_to_enum(root->kids[0]->data->lexeme));
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

                astNode* node = make_ASTnode(string_to_enum(root->kids[3]->data->lexeme));
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
                astNode* list_id = make_ASTnode(string_to_enum(root->kids[6]->data->lexeme)); //Will store the address of the head of linked list of identifiers

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

                astNode* node = make_ASTnode(string_to_enum(root->kids[3]->data->lexeme));
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
                astNode* node = make_ASTnode(string_to_enum(root->data->node_symbol));
                astNode* child0 = buildAST(root->kids[0]);

                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;

                return node;
            }

            // expression -> arithmeticOrBooleanExpression
            case(58):
            {
                astNode* node = make_ASTnode(string_to_enum(root->data->node_symbol));
                astNode* child0 = buildAST(root->kids[0]);

                node->tree_node = root->data;
                child0->parent = node;
                node->child = child0;

                return node;
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
                int certificate = string_to_enum(root->data->node_symbol);

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
                int certificate = string_to_enum(root->data->node_symbol);

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
                int certificate = string_to_enum(root->data->node_symbol);

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
                int certificate = string_to_enum(root->data->node_symbol);

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
                int certificate = string_to_enum(root->data->node_symbol);

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
                int certificate = string_to_enum(root->data->node_symbol);

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
int main(int argc, char* argv[])          // driver
{
    if(argc != 3)
    {
        printf("Invalid argument count. Expected 3 arguments as in './executable testcase parse_outfile'.");
        printf("\nAborting Execution!!\n");
        exit(2);
    }

    FILE* test_fp = fopen(argv[1], "r");
    FILE* test_parse_fp = fopen(argv[2], "w");
    populate_ht(hash_table, KEYWORDS_FILE);
    int line_count = 1;
    TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
    init_buffer(test_fp, twin_buff);
    GRAMMAR* grammar = generate_grammar();
    first_follow *ff = get_first_follow_table(grammar);
    TABLE *parse_table = (TABLE *) malloc(sizeof(TABLE));
    create_parse_table(ff, parse_table, grammar);
    STACK *stack = NULL;
    PARSE_TREE *tree;
    parse(grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
    fprintf(test_parse_fp, "%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s%20s\n\n", "LEXEME", "LINE_NO", "VALUE (if num)", "TOKENAME",  "PARENT", "IS LEAF?", "NODE SYMBOL", "RULE_NUMBER");
    print_parse_tree(tree, test_parse_fp);
    printf("Printed Parse Tree in file '%s'.\n", argv[2]);
    // printf("Rule number of root: %d\n", tree->kids[0]->data->rule_number);
    astNode* ast_root = buildAST(tree);

    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
}