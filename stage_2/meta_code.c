#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{

    printf("Press 1 if you want astnode, 0 otherwise: ");
    int choice;
    scanf("%d", &choice);

    printf("int certificate = string_to_enum(root->data->lexeme);\n\n");


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
            printf("child%d->parent = root;\n", atoi(argv[i]));
        }

        printf("return node\n");
        
    }

    else
    {
        printf("return ?\n");
    }
    
    printf("\nbreak;\n");
}