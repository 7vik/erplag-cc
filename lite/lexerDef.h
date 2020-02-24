//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#define MAX_BOOL_ARRAY_SIZE  150             // maximum allowed length of boolean array

#if !defined(max_id_len)
#define max_id_len 20           // maximum allowed length of identifier
#define max_num_len 100         // maximum allowed length of any number (this has been defined by us)
#endif

enum variables {    arithmeticExpr,arithmeticExpr_lr,
                    arithmeticOrBooleanExpression,assignmentStmt,booleanConst,caseStmt,
                    caseStmts,conditionalStmt,datatype,declareStmt,default_nt,driverModule,
                    expression,factor,idList,idList_lr,index_nt,input_plist,
                    input_plist_lr,ioStmt,iterativeStmt,logicalOp,lvalueARRStmt,
                    lvalueIDStmt,module,moduleDeclaration,moduleDeclarations,
                    moduleDef,moduleReuseStmt,one_more_opt,op1,op2,opt_expr,
                    opt_expr_lr,optional,otherModules,output_plist,output_plist_lr,
                    printOpt,program,range,rangeArr,relationalOp,ret,simpleStmt,
                    statement,statements,term,term_lr,type,unary_opt,
                    unaryExpression,value,var,whichId,whichStmt,
                    AND,ARRAY,ASSIGNOP,BC,BO,BOOLEAN,BREAK,CASE,COLON,COMMA,
                    DECLARE,DEF,DEFAULT,DIV,DOLLAR,DRIVER,DRIVERDEF,DRIVERENDDEF,
                    END,ENDDEF, EPS, EQ,FALSE,FOR,GE,GET_VALUE,GT,ID,IN,INPUT,INTEGER,
                    LE,LT,MINUS,MODULE,MUL,NE,NUM,OF,OR,PARAMETERS,PLUS,PRINT,
                    PROGRAM,RANGEOP,REAL,RETURNS,RNUM,SEMICOL,SQBC,SQBO,START,
                    SWITCH,TAKES,TRUE,USE,WHILE,WITH
                    
                };

char *variables_array[] = {  
                            "arithmeticExpr","arithmeticExpr_lr","arithmeticOrBooleanExpression",
                            "assignmentStmt","booleanConst","caseStmt","caseStmts","conditionalStmt",
                            "datatype","declareStmt","default_nt","driverModule","expression",
                            "factor","idList","idList_lr","index_nt","input_plist","input_plist_lr",
                            "ioStmt","iterativeStmt","logicalOp","lvalueARRStmt","lvalueIDStmt",
                            "module","moduleDeclaration","moduleDeclarations","moduleDef",
                            "moduleReuseStmt","one_more_opt","op1","op2","opt_expr","opt_expr_lr",
                            "optional","otherModules","output_plist","output_plist_lr","printOpt",
                            "program","range","rangeArr","relationalOp","ret","simpleStmt","statement",
                            "statements","term","term_lr","type","unary_opt","unaryExpression",
                            "value","var","whichId","whichStmt",
                            "AND","ARRAY","ASSIGNOP","BC","BO","BOOLEAN","BREAK","CASE","COLON",
                            "COMMA","DECLARE","DEF","DEFAULT", "DIV", "DOLLAR", "DRIVER","DRIVERDEF",
                            "DRIVERENDDEF","END","ENDDEF", "EPS", "EQ","FALSE","FOR","GE","GET_VALUE",
                            "GT", "ID","IN","INPUT","INTEGER","LE","LT","MINUS","MODULE","MUL","NE",
                            "NUM","OF","OR","PARAMETERS","PLUS","PRINT","PROGRAM","RANGEOP","REAL",
                            "RETURNS","RNUM","SEMICOL","SQBC","SQBO","START","SWITCH","TAKES",
                            "TRUE","USE","WHILE","WITH"
                            
                        };

#define TOKEN_SIZE 22
#define SOURCE_CODE_FILE "./t2.txt"

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


void init_buffer(FILE *f, TWIN_BUFFER *buff);
char get_stream(FILE *f, TWIN_BUFFER *buff);
LEXEME *get_token(FILE *f, TWIN_BUFFER *twin_buff, int *line_count);
void print_lexeme(LEXEME *l);

ENTRY *hash_table[SIZE];                                // only global variable in the whole code

void initialize(ENTRY **hash_table);
int hash(char *str);
void insert(char *value, ENTRY **hash_table);
// int delete(char *value, ENTRY **hash_table);
void print(ENTRY **hash_table);
void populate_ht(ENTRY **hash_table, char *file_path);
int search(char *value, ENTRY **hash_table);

void initialize_bool_array(bool* arr);
bool* or(bool * arr1, bool* arr2);
bool* and(bool * arr1, bool* arr2);
bool* xor(bool * arr1, bool* arr2);
bool* not(bool * arr1);
void print_bool(bool* arr, int size);
void or_and_store(bool * arr1, bool* arr2);

