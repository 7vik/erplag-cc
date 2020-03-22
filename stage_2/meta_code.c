/********************************************
 * compile the code as gcc meta_code.c -o meta
 * run ./meta parameters
 * paramets are the child number for whom you need to call buildAST
 * Eg: for rule1 it was ./meta 0 1 2
 * It asks whether you are calling make_node in your code
 * if yes press 1, else 0
 * This will generate some of the boring code
 * 
 * For generating case statements the format is ./meta start_val end_val
 * For eg: ./meta 12 14 will generate case stmts 12, 13, 14.
 */

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{

    printf("Press -1 if A -> EPS kind of rule\n \
            Press 1 if you want astnode\n \
            0 if no astNode\n \
            Press 2 for constructing case stmts\n \
            Press 3 for constructing case Non-Terminal -> Terminal\n\n ");
    int choice;
    scanf("%d", &choice);

    if(choice == 3)
    {
        printf("int certificate = string_to_enum(root->kids[0]->data->lexeme);\nastNode* node = make_ASTnode(certificate);\nnode->tree_node = root->kids[0]->data;\nnode->is_leaf = 1;\nreturn node;\n");
        return 0;
    }

    printf("int certificate = string_to_enum(root->data->lexeme);\n\n");

    if (choice == 2)
    {
        for(int i = atoi(argv[1]); i <= atoi(argv[2]); i++)
        {
            printf("case(%d):\n{\n\t//To do\n}\n\n", i);
        }

        return 0;
    }

    if (choice == -1)
    {
        printf("astNode* node = make_ASTnode(certificate);\n");
        printf("return node;\n");
        return 0;
    }

    
    // known bug: Case: moduleDeclaration -> DECLARE MODULE ID SEMICOL
    // ID will be also freed which we have to tackle manually.
    int j = 0;
    for(int i = 0; i <= atoi(argv[argc - 1]); i++)
    {
        if (i == atoi(argv[j + 1]))
        {
            j++;
            printf("astNode* child%d = buildAST(root->kids[%d]);\n", atoi(argv[i + 1]), atoi(argv[i + 1]));
        }
        else
            printf("free(root->kids[%d])\n", i);
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

