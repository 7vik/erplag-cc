#include<stdio.h>
#include<stdlib.h>
#include "hash.h"      // malloc()
#include "lexer.h"
#include<ctype.h>       // isalpha(), isalnum(), isnumber()
#include<string.h>      // strlen(), strcpy(), memset()

#define TOKEN_SIZE 22
#define SOURCE_CODE_FILE "./testcase4.txt"
#define not !

char get_stream(FILE *f, TWIN_BUFFER *buff);
enum active_buffer {Steve, Mark};

void print_lexeme(LEXEME *l)
{
    if (not l)
        printf("Lexeme is NULL error.\n");
    else
        printf("token: %s\tvalue: %s\tline_no: %u\n",l->token, l->value, l->line);
    return;
}

/*  IMPLEMENTATION DETAIL:
get_token() is supposed to return a TUPLE, taking input from get_stream(), which returns a character each time 
when called, using the concept of twin buffers for efficient implementation of I/O to avoid intensive 
file I/O mixed with CPU intensive tasks.
The parser will create the twin buffer once and for all, so that data doesn't get refreshed every time, 
and a pointer to this buffer will be passed to get_token() and to get_stream().

CAUTION 0: While writing parser(), remember to initialize only Steve
CAUTION 1: While writing get_token(), remember to update bp when you hit a complete token
*/

LEXEME *get_token(FILE *f, TWIN_BUFFER *twin_buff, int *line_count)
{
    LEXEME *new = (LEXEME *) malloc(sizeof(LEXEME));
    // write lexer code to find the correct token and value and fill it in new
    // instead of fgetc() as in lexer written in "lexer.c",
    // this will take lookaheads from get_stream() 
    // check for EOF
    // when token is identified, set bp = fp
    char lookahead;
    char *buff = (char *) (malloc(sizeof(char) * (max_id_len + 1)));
    int char_count;
    while ((lookahead = get_stream(f, twin_buff)) != EOF)
    {
        //printf("%c\n", lookahead);
        if (lookahead == '\n')
        {
            ++(*line_count);
            continue;
        }
        char_count = 0;
        if (isalpha(lookahead))
        // dfa for identifier
        {
            buff[char_count] = lookahead;
            ++char_count;
            // flag reset when variable length reaches 20 and lexical error printed
            int len_flag = 1;
            while ((lookahead = get_stream(f, twin_buff)) != EOF && (isalnum(lookahead) || lookahead == '_'))
            {
                if (lookahead == '\n')  ++(*line_count);
                if (char_count >= 20)
                {
                    if (len_flag == 1)
                    {
                        len_flag = 0;
                        printf("Lexical Error at line # %d.\t. Variable length exceeds 20.\n", *line_count);
                    }
                    continue;
                }
                buff[char_count] = lookahead;
                ++char_count;
            }
            if (len_flag == 0)
                continue;
            buff[char_count] = '\0';
            char *detected_id = (char *) malloc(strlen(buff));
            strcpy(detected_id, buff);
            new->token = (char *) malloc (sizeof(char) * TOKEN_SIZE);
            if (search(detected_id, hash_table) == 1)
                strcpy(new->token, "KEYWORD");
            else
                strcpy(new->token,"ID");
            new->value = detected_id;
            twin_buff->fp--;
            twin_buff->bp = twin_buff->fp;
            new->line = *line_count;
            return new;
        }
        else if(isnumber(lookahead))
        {
        // dfa for integer/real
        }
        else
        {
            switch (lookahead)
            {
                case '+': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("PLUS"));
                    new->value = (char *) malloc (sizeof(char) * strlen("+"));
                    strcpy(new->token, "PLUS");
                    strcpy(new->value, "+");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case '-': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("MINUS"));
                    new->value = (char *) malloc (sizeof(char) * strlen("-"));
                    strcpy(new->token, "MINUS");
                    strcpy(new->value, "-");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case '/': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("DIV"));
                    new->value = (char *) malloc (sizeof(char) * strlen("/"));
                    strcpy(new->token, "DIV");
                    strcpy(new->value, "/");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case '[': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("SQBO"));
                    new->value = (char *) malloc (sizeof(char) * strlen("["));
                    strcpy(new->token, "SQBO");
                    strcpy(new->value, "[");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case ']': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("SQBC"));
                    new->value = (char *) malloc (sizeof(char) * strlen("]"));
                    strcpy(new->token, "SQBC");
                    strcpy(new->value, "]");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case '(': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("BO"));
                    new->value = (char *) malloc (sizeof(char) * strlen("("));
                    strcpy(new->token, "BO");
                    strcpy(new->value, "(");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case ')': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("BC"));
                    new->value = (char *) malloc (sizeof(char) * strlen(")"));
                    strcpy(new->token, "BC");
                    strcpy(new->value, ")");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case ';': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("SEMICOL"));
                    new->value = (char *) malloc (sizeof(char) * strlen(";"));
                    strcpy(new->token, "SEMICOL");
                    strcpy(new->value, ";");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                case ',': 
                {
                    new->token = (char *) malloc (sizeof(char) * strlen("COMMA"));
                    new->value = (char *) malloc (sizeof(char) * strlen(","));
                    strcpy(new->token, "COMMA");
                    strcpy(new->value, ",");
                    twin_buff->bp = twin_buff->fp;
                    new->line = *line_count;
                    return new;
                    break;
                }
                default: break;
            }
        } 
    }
    return NULL;
}

char get_stream(FILE *f, TWIN_BUFFER *buff)
{
    // returns the character at fp and increments the fp
    //data structure to be used is a twin buffer
    char c;
    if (buff->active == Steve)
        c = buff->steve[buff->fp];
    else
        c = buff->mark[buff->fp];
    if (buff->fp == (TWIN_BUFFER_SIZE - 1))
    {
        if (buff->active == Steve)
        {   
            memset(buff->mark, EOF, TWIN_BUFFER_SIZE);
            fread(buff->mark, sizeof(char), TWIN_BUFFER_SIZE, f);
        }
        else // (buff->active == Mark)
        {
            memset(buff->steve, EOF, TWIN_BUFFER_SIZE);
            fread(buff->steve, sizeof(char), TWIN_BUFFER_SIZE, f);
        }
        buff->fp = -1;
        buff->active = 1 - buff->active;        // change the active buffer
    }   
    buff->fp++;
    return c;
}

void init_buffer(FILE *f, TWIN_BUFFER *buff)
{
    memset(buff->mark, EOF, TWIN_BUFFER_SIZE);
    memset(buff->steve, EOF, TWIN_BUFFER_SIZE);
    fread(buff->steve, sizeof(char), TWIN_BUFFER_SIZE, f);
    buff->fp = 0;
    buff->bp = 0;
    buff->active = 0;
    // printf("%d\n", buff->active);
    //printf("H3\n");
    return;
}

int main()
{
    populate_ht(hash_table, KEYWORDS_FILE);
    FILE *f = fopen(SOURCE_CODE_FILE, "r");
    int line_count = 0;
    TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
    init_buffer(f, twin_buff);
    printf("%s\n", twin_buff->steve);
    LEXEME *temp;
    while((temp = get_token(f, twin_buff, &line_count)))
        print_lexeme(temp);
    return 0;
}