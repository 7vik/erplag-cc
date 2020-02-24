//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(max_id_len)
#define max_id_len 20           // maximum allowed length of identifier
#define max_num_len 100         // maximum allowed length of any number (this has been defined by us)
#endif

#define TOKEN_SIZE 22
//#define SOURCE_CODE_FILE "../testcases-1/testcase-bt.txt"/*"./test.erplag"*/
#define SOURCE_CODE_FILE "./t2.txt"/*"./test.erplag"*/
#include "hash.h"           

#define not !
#define and &&

enum active_buffer {Steve, Mark};

#define TWIN_BUFFER_SIZE 512

typedef struct lexeme_tuple
{
    // lexeme (tuple of (TOKEN, VALUE, LINE))
    char *token;
    char *value;
    unsigned int line;
} LEXEME;

typedef struct twin_buffer
{
    // steve and mark are our twin buffers
    char steve[TWIN_BUFFER_SIZE];
    char mark[TWIN_BUFFER_SIZE];
    int bp;     // base pointer
    int fp;     // forward pointer
    int active;          // active buffer for the forward pointer (don't need one for base p)
    int read;
}   TWIN_BUFFER;

void init_buffer(FILE *f, TWIN_BUFFER *buff);
char get_stream(FILE *f, TWIN_BUFFER *buff);
LEXEME *get_token(FILE *f, TWIN_BUFFER *twin_buff, int *line_count);
void print_lexeme(LEXEME *l);