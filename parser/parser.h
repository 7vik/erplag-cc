#if !defined(MAX_VAR_SIZE)
#define MAX_VAR_SIZE 50            // maximum allowed length of variable
#endif

#define GRAMMAR_NODE_FILE_PATH "../grammar/grammar_test.txt"
#define MAX_RULE_NUM 150
#define N_ARY_LIM 15            // max size from current grammar is 12. Increase it if required.
#define MAX_NUM_NON_TERMINALS 100  // number of non-terminals
#include "bool.h"

/*
enum terminals  {   AND,ARRAY,ASSIGNOP,BC,BO,BOOLEAN,BREAK,
                    CASE,COLON,COMMA,DECLARE,DEF,DEFAULT,DIV,
                    DRIVER,DRIVERDEF,DRIVERENDDEF,END,ENDDEF,EQ,FALSE,
                    FOR,GE,GET_VALUE,GT,IN,INPUT,INTEGER,LE,LT,MINUS,
                    MODULE,MUL,NE,NUM,OF,OR,PARAMETERS,PLUS,
                    PRINT,PROGRAM,RANGEOP,REAL,RETURNS,RNUM,SEMICOL,
                    SQBC,SQBO,START,SWITCH,TAKES,TRUE,USE,WHILE,WITH
                };


enum non_terminals {    arithmeticExpr,arithmeticExpr_lr,arithmeticOrBooleanExpression,
                        assignmentStmt,booleanConst,caseStmt,caseStmts,conditionalStmt,
                        datatype,declareStmt,default_nt,driverModule,expression,factor,
                        idList,idList_lr,index_nt,input_plist,input_plist_lr,
                        ioStmt,iterativeStmt,logicalOp,lvalueARRStmt,lvalueIDStmt,
                        module,moduleDeclaration,moduleDeclarations,moduleDef,
                        moduleReuseStmt,one_more_opt,op1,op2,opt_expr,opt_expr_lr,
                        optional,otherModules,output_plist,output_plist_lr,printOpt
                        ,program,range,rangeArr,relationalOp,ret,simpleStmt,statement
                        ,statements,term,term_lr,type,unary_opt,unaryExpression,value,
                        var,whichId,whichStmt
                    };
*/

enum variables {    AND,ARRAY,ASSIGNOP,BC,BO,BOOLEAN,BREAK,CASE,COLON,COMMA,
                    DECLARE,DEF,DEFAULT,DIV,DRIVER,DRIVERDEF,DRIVERENDDEF,
                    END,ENDDEF,EQ,FALSE,FOR,GE,GET_VALUE,GT,IN,INPUT,INTEGER,
                    LE,LT,MINUS,MODULE,MUL,NE,NUM,OF,OR,PARAMETERS,PLUS,PRINT,
                    PROGRAM,RANGEOP,REAL,RETURNS,RNUM,SEMICOL,SQBC,SQBO,START,
                    SWITCH,TAKES,TRUE,USE,WHILE,WITH,
                    arithmeticExpr,arithmeticExpr_lr,
                    arithmeticOrBooleanExpression,assignmentStmt,booleanConst,caseStmt,
                    caseStmts,conditionalStmt,datatype,declareStmt,default_nt,driverModule,
                    expression,factor,idList,idList_lr,index_nt,input_plist,
                    input_plist_lr,ioStmt,iterativeStmt,logicalOp,lvalueARRStmt,
                    lvalueIDStmt,module,moduleDeclaration,moduleDeclarations,
                    moduleDef,moduleReuseStmt,one_more_opt,op1,op2,opt_expr,
                    opt_expr_lr,optional,otherModules,output_plist,output_plist_lr,
                    printOpt,program,range,rangeArr,relationalOp,ret,simpleStmt,
                    statement,statements,term,term_lr,type,unary_opt,
                    unaryExpression,value,var,whichId,whichStmt
                };

char *variables_array[] = {  "AND","ARRAY","ASSIGNOP","BC","BO","BOOLEAN","BREAK","CASE","COLON",
                            "COMMA","DECLARE","DEF","DEFAULT","DIV","DRIVER","DRIVERDEF",
                            "DRIVERENDDEF","END","ENDDEF","EQ","FALSE","FOR","GE","GET_VALUE",
                            "GT","IN","INPUT","INTEGER","LE","LT","MINUS","MODULE","MUL","NE",
                            "NUM","OF","OR","PARAMETERS","PLUS","PRINT","PROGRAM","RANGEOP","REAL",
                            "RETURNS","RNUM","SEMICOL","SQBC","SQBO","START","SWITCH","TAKES",
                            "TRUE","USE","WHILE","WITH",
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
                            "value","var","whichId","whichStmt"
                        };

typedef struct first_follow_node
{
    bool first_set_array[MAX_BOOL_ARRAY_SIZE];
    bool follow_set_array[MAX_BOOL_ARRAY_SIZE];
}first_follow_node;


typedef struct first_follow
{
    first_follow_node* fnf[MAX_NUM_NON_TERMINALS];
}first_follow;


typedef struct grammar_node
{
    // a single node of a grammar rule. If rule is A->FOO BAR, then FOO is a node
    char variable[MAX_VAR_SIZE];
    int is_terminal_flag;
    struct grammar_node *next;
} GRAMMAR_NODE;

typedef struct grammar
{
    GRAMMAR_NODE *rules[MAX_RULE_NUM];
}   GRAMMAR;

typedef struct parse_table
{
    
}   TABLE;

typedef struct stack_of_grammar_symbols
{
    char *symbol;
    struct stack_of_grammar_symbols *next;
} STACK;

typedef struct parse_tree_node_data
{
    // data for printing and storing the parse tree effectively ftw
    char *lexeme;       // value in our passed lexeme tuple 
    unsigned int line;           // line in our passed lexeme
    char *token_name;   // token in our passed lexeme    
    char *value_if_number;
    char *parent_node_symbol;             
    int is_leaf_node;               // 1 for yes       
    char *node_symbol;
<<<<<<< HEAD
}PARSE_TREE_NODE_DATA;
=======
} TREE_NODE;
>>>>>>> b56e0cd6915bbc4693399e8cff380e98bef7c978

typedef struct parse_tree
{
    // n-ary tree structure
    TREE_NODE *data;
    int num_of_kids;
    struct parse_tree *kids[N_ARY_LIM];     // children nodes
}   PARSE_TREE;
