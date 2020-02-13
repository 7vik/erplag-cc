#include<stdio.h>
#include<stdlib.h>      // malloc()

#define TWIN_BUFFER_SIZE 50

enum active_buffer {Steve, Mark};

typedef struct twin_buffer
{
    // steve and mark are our twin buffers
    char steve[TWIN_BUFFER_SIZE];
    char mark[TWIN_BUFFER_SIZE];
    int bp;     // base pointer
    int fp;     // forward pointer
    enum active_buffer active;          // active buffer for the forward pointer (don't need one for base p)
}   TWIN_BUFFER;

typedef struct lexeme_tuple
{
    char *token;
    char *value;
}   LEXEME;

/*  IMPLEMENTATION DETAIL:
get_token() is supposed to return a TUPLE, taking input from get_stream(), which returns a character each time 
when called, using the concept of twin buffers for efficient implementation of I/O to avoid intensive 
file I/O mixed with CPU intensive tasks.
The parser will create the twin buffer once and for all, so that data doesn't get refreshed every time, 
and a pointer to this buffer will be passed to get_token() and to get_stream().

CAUTION 0: While writing parser(), remember to initialize only Steve
CAUTION 1: While writing get_token(), remember to update bp when you hit a complete token
*/

LEXEME *get_token(FILE *f, TWIN_BUFFER *buff)
{
    LEXEME *new = (LEXEME *) malloc(sizeof(LEXEME));
    // write lexer code to find the correct token and value and fill it in new
    // instead of fgetc() as in lexer written in "lexer.c",
    // this will take lookaheads from get_stream() 
    return new;
}

char get_stream(FILE *f, TWIN_BUFFER *buff)
{
    //data structure to be used is a twin buffer
    if (buff->active == Steve)
        return buff->steve[buff->fp];
    else
        return buff->mark[buff->fp];
    if (buff->fp == (TWIN_BUFFER_SIZE - 1))
    {
        if (buff->active == Steve)
            fread(buff->mark, sizeof(char), TWIN_BUFFER_SIZE, f);
        else
            fread(buff->steve, sizeof(char), TWIN_BUFFER_SIZE, f);
        buff->fp = 0;
        buff->active = 1 - buff->active;        // change the active buffer
    }   
}

int main()
{
    return 0;
}