#if !defined(max_id_len)
#define max_id_len 20           // maximum allowed length of identifier
#define max_num_len 100         // maximum allowed length of any number (this has been defined by us)
#endif

#define TWIN_BUFFER_SIZE 512

typedef struct lexeme_tuple
{
    // lexeme (tuple of (TOKEN, VALUE))
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
}   TWIN_BUFFER;

