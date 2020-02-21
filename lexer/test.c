#include<stdio.h>
#include<ctype.h>
#include <string.h>     // memset() 
#include<stdbool.h>

int main()
{
    // char test[10] = {'a'};
    // FILE *f = fopen("test.x", "r");
    // //printf("%d\n", fread(test, sizeof(char), 8, f));
    // int i = 0;
    // while(i<10)
    // {
    //     printf("%d\t%d\n", i, test[i]);
    //     ++i;
    // }
    // memset(test, EOF, 10);
    // i = 0;
    // while(i<10)
    // {
    //     printf("%d\t%d\n", i, test[i]);
    //     ++i;
    // }
    bool arr[] = {true, false,true, false,true, false,true, false,true, false,true, false, true };
    printf("%lu\n", sizeof(arr));
    return 0;
}
