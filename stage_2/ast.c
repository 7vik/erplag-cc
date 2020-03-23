//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

// Takes a node and Returns its astTree's root node

astNode* buildAST(PARSE_TREE* root)
{

    if (root != NULL)
    {
        int rule_num = root->data->rule_number;

        switch(rule_num)
        {
            //-[1] program -> moduleDeclarations otherModules driverModule otherModules

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
            
                if(child0->child == NULL && child1->child == NULL) //both are EPS
                {
                    node->child = child2;
                    free(child0);
                    free(child1);
                    child2->sibling = child3;
                }

                else if(child0->child == NULL)
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
                child0->parent = root;
                child1->parent = root;

                child0->sibling = child1;
                return child0;

                break;
            }
            
            // moduleDeclarations -> EPS
            case(3):
            {
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
                return node; // Child value already NULL, so lite
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
                node->child = root->kids[0];
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
                int certificate = string_to_enum(root->data->lexeme);
                astNode* node = make_ASTnode(certificate);
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
    } 

}
int main()          // driver
{
    return 0;
}