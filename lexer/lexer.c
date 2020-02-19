#include<stdio.h>
#include<stdlib.h>
#include "hash.h"      // malloc()
#include "lexer.h"
#include<ctype.h>       // isalpha(), isalnum(), isnumber()
#include<string.h>      // strlen(), strcpy(), memset()

#define TOKEN_SIZE 22
#define SOURCE_CODE_FILE "./testcase4.txt"/*"./test.erplag"*/
#define not !

char get_stream(FILE *f, TWIN_BUFFER *buff);
enum active_buffer {Steve, Mark};

void print_lexeme(LEXEME *l)
{
    if (not l)
        printf("Lexeme is NULL error.\n");
    else
        printf("token: %10s\tvalue: %15s\tline_no: %u\n",l->token, l->value, l->line);
    return;
}

void retract(TWIN_BUFFER *buff) //name to be modified later
{
    if(buff->fp == 0)
    {
        buff->active = 1 - buff->active;
        buff->fp = TWIN_BUFFER_SIZE - 1;
    }
    else
    {
        buff->fp--;
    }
    buff->bp = buff->fp;
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
    int state_for_com = 0;
    int state_for_dig = 0;
    int flag_com = 0;
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
            //twin_buff->fp--;                  //retract-fn
            //twin_buff->bp = twin_buff->fp;
            retract(twin_buff);
            new->line = *line_count;
            return new;
        }
        else if(lookahead >= '0' && lookahead <= '9')
        {
            
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
                case '=':
                {
                    if((lookahead = get_stream(f, twin_buff)) == '=')
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("EQ"));
                        new->value = (char *) malloc (sizeof(char) * strlen("=="));
                        strcpy(new->token, "EQ");
                        strcpy(new->value, "==");
                        twin_buff->bp = twin_buff->fp;
                        new->line = *line_count;
                        return new;
                    }
                    else
                    {
                        printf("Lexical Error at line # %d.\t. Invalid lexeme '='.\n", *line_count);
                        retract(twin_buff);
                        continue; //don't return any lexeme-token-line tuple
                    }
                    break;
                }
                case '!':
                {
                    if((lookahead = get_stream(f, twin_buff)) == '=')
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("NE"));
                        new->value = (char *) malloc (sizeof(char) * strlen("!="));
                        strcpy(new->token, "NE");
                        strcpy(new->value, "!=");
                        twin_buff->bp = twin_buff->fp;
                        new->line = *line_count;
                        return new;
                    }
                    else
                    {
                        printf("Lexical Error at line # %d.\t. Invalid lexeme '!'.\n", *line_count);
                        retract(twin_buff);
                        continue; //don't return any lexeme-token-line tuple
                    }
                    break;
                }
                case ':':
                {
                    if((lookahead = get_stream(f, twin_buff)) == '=')
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("ASSIGNOP"));
                        new->value = (char *) malloc (sizeof(char) * strlen(":="));
                        strcpy(new->token, "ASSIGNOP");
                        strcpy(new->value, ":=");
                        twin_buff->bp = twin_buff->fp;
                        new->line = *line_count;
                        return new;
                    }
                    else
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("COLON"));
                        new->value = (char *) malloc (sizeof(char) * strlen(":"));
                        strcpy(new->token, "COLON");
                        strcpy(new->value, ":");
                        retract(twin_buff);
                        new->line = *line_count;
                        return new;
                    }
                    break;
                }
                case '.':
                {
                    if((lookahead = get_stream(f, twin_buff)) == '.')
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("RANGEOP"));
                        new->value = (char *) malloc (sizeof(char) * strlen(".."));
                        strcpy(new->token, "RANGEOP");
                        strcpy(new->value, "..");
                        twin_buff->bp = twin_buff->fp;
                        new->line = *line_count;
                        return new;
                    }
                    else
                    {
                        printf("Lexical Error at line # %d.\t. Expected '.' after '.'.\n", *line_count);
                        retract(twin_buff);
                        continue; //don't return any lexeme-token-line tuple
                    }
                    break;
                }
                case '<':
                {
                    if((lookahead = get_stream(f, twin_buff)) == '=')
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("LE"));
                        new->value = (char *) malloc (sizeof(char) * strlen("<="));
                        strcpy(new->token, "LE");
                        strcpy(new->value, "<=");
                        twin_buff->bp = twin_buff->fp;
                        new->line = *line_count;
                        return new;    
                    }
                    else if(lookahead == '<')
                    {
                        if((lookahead = get_stream(f, twin_buff)) == '<')
                        {
                            new->token = (char *) malloc (sizeof(char) * strlen("DRIVERDEF"));
                            new->value = (char *) malloc (sizeof(char) * strlen("<<<"));
                            strcpy(new->token, "DRIVERDEF");
                            strcpy(new->value, "<<<");
                            twin_buff->bp = twin_buff->fp;
                            new->line = *line_count;
                            return new;
                        }
                        else
                        {
                            new->token = (char *) malloc (sizeof(char) * strlen("DEF"));
                            new->value = (char *) malloc (sizeof(char) * strlen("<<"));
                            strcpy(new->token, "DEF");
                            strcpy(new->value, "<<");
                            retract(twin_buff);
                            new->line = *line_count;
                            return new;
                        }    
                    }
                    else
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("LT"));
                        new->value = (char *) malloc (sizeof(char) * strlen("<"));
                        strcpy(new->token, "LT");
                        strcpy(new->value, "<");
                        retract(twin_buff);
                        new->line = *line_count;
                        return new;
                    }
                    break;    
                }
                case '>':
                {
                    if((lookahead = get_stream(f, twin_buff)) == '=')
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("GE"));
                        new->value = (char *) malloc (sizeof(char) * strlen(">="));
                        strcpy(new->token, "GE");
                        strcpy(new->value, ">=");
                        twin_buff->bp = twin_buff->fp;
                        new->line = *line_count;
                        return new;    
                    }
                    else if(lookahead == '>')
                    {
                        if((lookahead = get_stream(f, twin_buff)) == '>')
                        {
                            new->token = (char *) malloc (sizeof(char) * strlen("DRIVERENDDEF"));
                            new->value = (char *) malloc (sizeof(char) * strlen(">>>"));
                            strcpy(new->token, "DRIVERENDDEF");
                            strcpy(new->value, ">>>");
                            twin_buff->bp = twin_buff->fp;
                            new->line = *line_count;
                            return new;
                        }
                        else
                        {
                            new->token = (char *) malloc (sizeof(char) * strlen("ENDDEF"));
                            new->value = (char *) malloc (sizeof(char) * strlen(">>"));
                            strcpy(new->token, "ENDDEF");
                            strcpy(new->value, ">>");
                            retract(twin_buff);
                            new->line = *line_count;
                            return new;
                        }    
                    }
                    else
                    {
                        new->token = (char *) malloc (sizeof(char) * strlen("GT"));
                        new->value = (char *) malloc (sizeof(char) * strlen(">"));
                        strcpy(new->token, "GT");
                        strcpy(new->value, ">");
                        retract(twin_buff);
                        new->line = *line_count;
                        return new;
                    }
                    break;    
                }
                case '*':
                {
                    lookahead = get_stream(f, twin_buff);
                    switch(lookahead)
                    {
                        case '*':
                        {
                            while((lookahead = get_stream(f, twin_buff)) != EOF)
                            {
                                switch(state_for_com)
                                {
                                    case 0:
                                    {
                                        if(lookahead == '*')
                                            state_for_com = 1;
                                        else if(lookahead == '\n')
                                            *line_count = *line_count + 1;
                                        
                                        break;
                                    }
                                    case 1:
                                    {
                                        if(lookahead == '*')
                                        {
                                            state_for_com = 0;
                                            flag_com = 1;
                                            break;
                                        }
                                        else
                                        {
                                            state_for_com = 0;
                                            if(lookahead == '\n')
                                                *line_count = *line_count + 1;
                                        }
                                        break;
                                    }
                                }
                                if(flag_com == 1)
                                {
                                    flag_com = 0;
                                    break;
                                }
                            }
                            break;
                        }
                        default:
                        {
                            new->token = (char *) malloc (sizeof(char) * strlen("MUL"));
                            new->value = (char *) malloc (sizeof(char) * strlen("*"));
                            strcpy(new->token, "MUL");
                            strcpy(new->value, "*");
                            retract(twin_buff);
                            new->line = *line_count;
                            return new;
                        }
                    }
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
    int line_count = 1;
    TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
    init_buffer(f, twin_buff);
    printf("%s\n", twin_buff->steve);
    LEXEME *temp;
    while((temp = get_token(f, twin_buff, &line_count)))
        print_lexeme(temp);
    return 0;
}