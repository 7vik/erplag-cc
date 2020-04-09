#include "assembler.h"

void generate_code(astNode* root, GST* sybol_table, FILE* fp)
{
    assert()
    astNode* temp = root->child;

    while(temp != NULL)
    {
        generate_code(temp);
    }
}