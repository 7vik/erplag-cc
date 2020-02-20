#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main(int c, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL)
        return 0;
    char ch;
    FILE *fp2 = fopen("strings_of_enum.txt", "w");
    fputc('"',fp2);
    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == ',')
        {
            fputc('"',fp2);
            fputc(ch,fp2);
            fputc('"',fp2);
            continue;
        }
        if(ch != '\n' && ch != ' ' && ch != '\t')
            fputc(ch,fp2);
    }
    fputc('"',fp2);
    fclose(fp);
    fclose(fp2);
    return 0;
}