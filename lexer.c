#include<stdio.h>
#include<stdlib.h>       // malloc()
#include "lexer.h"
//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<ctype.h>       // isalpha(), isalnum(), isnumber()
#include<string.h>      // strlen(), strcpy(), memset()


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
        buff->read = 0;
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
    char *buff_num;
    char temp_lookahead; //to be used in case of double retraction

    int char_count;
    int state_for_com = 0;
    int state_for_dig = 0;
    int flag_com = 0;
    int flag_num = 0;
    int flag_int = 0;
    while ((lookahead = get_stream(f, twin_buff)) != EOF) 
    {
        //printf("%c\n", lookahead);
        if (lookahead == '\n')
        {
            ++(*line_count);
            continue;
        }
        char_count = 0;
        if ((lookahead >= 'A' && lookahead <= 'Z') || (lookahead >= 'a' && lookahead <= 'z')) //isalpha(lookahead)
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
                    }
                    buff[char_count] = lookahead;
                    ++char_count;
                    continue;
                }
                buff[char_count] = lookahead;
                ++char_count;
            }
            if (len_flag == 0)
            {
                retract(twin_buff);
                buff[char_count] = '\0';
                printf("Lexical Error at line # %d.\t Invalid lexeme '%s'. Variable length exceeds 20.\n", *line_count, buff);
                continue;
            }
            buff[char_count] = '\0';
            char *detected_id = (char *) malloc(strlen(buff));
            strcpy(detected_id, buff);
            new->token = (char *) malloc (sizeof(char) * TOKEN_SIZE);
        
            if (search(detected_id, hash_table) == 1)
            {
                char *temp = (char *) malloc(strlen(buff) + 1);
                for (int yu=0; yu <= (int) strlen(buff); ++yu)
                    temp[yu] = toupper(buff[yu]);
                //printf("token: %s\n", buff);
                strcpy(new->token, temp);
            }
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
        //dfa for integer/real number
        {
            buff_num = (char *) calloc((max_num_len + 1), sizeof (char));
            buff_num[char_count] = lookahead;
            char_count++;
            state_for_dig = 1;
            while((lookahead = get_stream(f, twin_buff)) != EOF)
            {
                switch(state_for_dig)
                {
                    case 1:
                    {
                        if(lookahead >= '0' && lookahead <= '9')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                        }
                        else if(lookahead == '.')
                        {
                            temp_lookahead = lookahead;
                            if((lookahead = get_stream(f, twin_buff)) == '.')
                            {
                                retract(twin_buff);
                                flag_num = 1;
                                flag_int = 1;
                                state_for_dig = 0;
                                break;
                            }
                            else
                            {   
                                retract(twin_buff);
                                buff_num[char_count] = temp_lookahead;
                                char_count++;
                                state_for_dig = 2;
                            }
                        }
                        else
                        {
                            flag_num = 1;
                            flag_int = 1;                    
                            state_for_dig = 0;
                            break;
                        }               
                        break;
                    }
                    case 2:
                    {
                        if(lookahead >= '0' && lookahead <= '9')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                            state_for_dig = 3;
                        }
                        else
                        {
                            buff_num[char_count] = '\0';
                            state_for_dig = 0;
                            break;
                        }
                        break;    
                    }
                    case 3:
                    {
                        if(lookahead >= '0' && lookahead <= '9')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                        }
                        else if(lookahead == 'e' || lookahead == 'E')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                            state_for_dig = 4;
                        }
                        else
                        {
                            flag_num = 1;
                            state_for_dig = 0;
                            break;
                        }
                        break;    
                    }
                    case 4:
                    {
                        if(lookahead >= '0' && lookahead <= '9')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                            state_for_dig = 6;
                        }
                        else if(lookahead == '+' || lookahead == '-')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                            state_for_dig = 5;
                        }
                        else
                        {
                            buff_num[char_count] = '\0';
                            state_for_dig = 0;
                            break;
                        }
                        break;
                    }
                    case 5:
                    {
                        if(lookahead >= '0' && lookahead <= '9')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                            state_for_dig = 6;
                        }
                        else
                        {
                            buff_num[char_count] = '\0';
                            state_for_dig = 0;
                            break;
                        }
                        break;    
                    }
                    case 6:
                    {
                        if(lookahead >= '0' && lookahead <= '9')
                        {
                            buff_num[char_count] = lookahead;
                            char_count++;
                        }
                        else
                        {
                            flag_num = 1;
                            state_for_dig = 0;
                            break;
                        }
                        break;    
                    }
                }
                if(state_for_dig == 0)
                    break;    
            }
            if(flag_num == 1)
            {
                buff_num = (char*) realloc(buff_num, char_count+1);
                char *detected_num = (char *) malloc(strlen(buff_num));
                strcpy(detected_num, buff_num);
                new->token = (char *) malloc (sizeof(char) * TOKEN_SIZE);
                
                if (flag_int == 1)
                    strcpy(new->token, "NUM");
                else
                    strcpy(new->token,"RNUM");
                
                new->value = detected_num;
                retract(twin_buff);
                new->line = *line_count;
                flag_int = 0;
                flag_num = 0;
                return new;    
            }
            else //flag_num is zero
            {
                printf("Lexical Error at line # %d.\t. Invalid lexeme '%s'.\n", *line_count, buff_num);
                retract(twin_buff);
            }
        }
        else            // operator
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
                        printf("Lexical Error at line # %d.\t. Invalid lexeme '='. Expected '=='.\n", *line_count);
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
                        printf("Lexical Error at line # %d.\t. Invalid lexeme '!'. Expected '!='.\n", *line_count);
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
                        printf("Lexical Error at line # %d.\t. Invalid lexeme '.'. Expected '..'.\n", *line_count);
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
                case '*':           // comments wala dfa
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
                case '\t':
                case '\r':
                case ' ':
                    break; 
                default: 
                    printf("Lexical Error at line #%d: unidentifiable character: %c.\n", *line_count, lookahead);
            }
        } 
    }
    new->token = "DOLLAR";
    return new;
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
    if (buff->fp == (TWIN_BUFFER_SIZE - 1) and buff->read == 1)
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
    else if (buff->read == 0)
    {
        if (buff->fp == TWIN_BUFFER_SIZE - 1)
        {
            buff->fp = -1;
            buff->active = 1 - buff->active;
            buff->read = 1;
        }
        //buff->read = 1;
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
    buff->read = 1;
    // printf("%d\n", buff->active);
    return;
}