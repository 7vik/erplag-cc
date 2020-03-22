#include <stdio.h>
#include <stdlib.h>


void remove_comments(FILE* f1, FILE* f2)
{

    int state = 0;
    char ch;

    while((ch = fgetc(f1)) != EOF)
    {
        if(state == 0)
        {
            if(ch == '*')
                state = 1;
            else
                fputc(ch, f2);    
        }

        else if(state == 1)
        {
            if(ch == '*')
                state = 2;
            else
            {
                state = 0;
                fputc('*', f2);
                fputc(ch, f2);
            }
        }

        else if(state == 2)
        {
            if(ch == '*')
                state = 3;
            else if(ch == '\n')
                fputc(ch, f2);
            else;    /* do nothing */
        }

        else if(state == 3)
        {
            if(ch == '*')
                state = 0;
            else if(ch == '\n')
            {
                state = 2;
                fputc(ch, f2);
            }
            else
                state = 2;
        }
        else;   /* do nothing */
    }
    fclose(f1);
    fclose(f2);
    return;
}

int main(void)
{
    FILE* fp  = fopen("t2.txt", "r");
    FILE* fp2 = fopen("output.txt", "w");

    remove_comments(fp, fp2);

    system("cat output.txt; rm output.txt");
}