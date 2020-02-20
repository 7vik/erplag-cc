#include <stdio.h>
#include "parser.h"
#include <string.h>




int string_to_enum(char* string)
{
    int variable_array_size = sizeof(variables_array) / sizeof ( *variables_array);

    for (int i = 0; i < variable_array_size; i++)
    {
        if(strcmp(variables_array[i], string) == 0)
            return i;
    }

    printf("String to enum failed for %s\n", string);
    return -1;
}


int main(void)
{
    printf("%d\n", string_to_enum("BO"));
}