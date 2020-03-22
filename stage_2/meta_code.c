/********************************************
 * compile the code as gcc meta_code.c -o meta
 * run ./meta parameters
 * paramets are the child number for whom you need to call buildAST
 * Eg: for rule1 it was ./meta 0 1 2
 * It asks whether you are calling make_node in your code
 * if yes press 1, else 0
 * This will generate some of the boring code
 */

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{

    printf("Press -1 if A -> EPS kind of rule, Press 1 if you want astnode, 0 otherwise: ");
    int choice;
    scanf("%d", &choice);

    printf("int certificate = string_to_enum(root->data->lexeme);\n\n");

    if (choice == -1)
    {
        printf("astNode* node = make_ASTnode(certificate);\n");
        printf("return node;\n");
        return 0;
    }

    for(int i = 0; i < argc - 1; i++)
    {
        printf("astNode* child%d = buildAST(root->kids[%d]);\n", atoi(argv[i + 1]), atoi(argv[i + 1]));
    }

    

    if (choice == 1)
    {
        printf("\nastNode* node = make_ASTnode(certificate);\n");
        printf("\nnode->tree_node = root->data;\n");

        for(int i = 0; i < argc - 1; i++)
        {
            printf("child%d->parent = root;\n", atoi(argv[i + 1]));
        }

        printf("return node;\n");
        
    }

    else
    {
        // for(int i = 0; i < argc - 1; i++)
        // {
        //     printf("child%d->parent = root;\n", atoi(argv[i + 1]));
        // }

        printf("return child%d;\n", atoi(argv[1]));
    }
    
    printf("\nbreak;\n");
}