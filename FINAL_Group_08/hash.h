//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(KEYWORDS_FILE)
#define KEYWORDS_FILE "./keywords.txt"
#endif

#define SIZE 64
#define MAXLEN 25                           // length of identifier can't be > 20
#define ABS(N) ((N<0)?(-N):(N))           

typedef struct hash_table_entry_list_node
{
    char *data;
    struct hash_table_entry_list_node *next;            //  chaining for collisions
} ENTRY;

ENTRY *hash_table[SIZE];  

void initialize(ENTRY **hash_table);
int hash(char *str);
void insert(char *value, ENTRY **hash_table);
// int delete(char *value, ENTRY **hash_table);
void print(ENTRY **hash_table);
void populate_ht(ENTRY **hash_table, char *file_path);
int search(char *value, ENTRY **hash_table);
