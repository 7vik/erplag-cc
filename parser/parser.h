#if !defined(define MAX_VAR_SIZE)
#define MAX_VAR_SIZE 50            // maximum allowed length of boolean array
#endif

#define RULE_FILE_PATH "../grammar/grammar_erplag.txt"
#define MAX_RULE_NUM 150
#define N_ARY_LIM 15            // max size from current grammar is 12. Increase it if required.
#define NUM_NON_TERMINALS 56  // number of non-terminals

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

enum variables {    AND,ARRAY,ASSIGNOP,BC,BO,BOOLEAN,BREAK,CASE,COLON,COMMA,
                    DECLARE,DEF,DEFAULT,DIV,DRIVER,DRIVERDEF,DRIVERENDDEF,
                    END,ENDDEF,EQ,FALSE,FOR,GE,GET_VALUE,GT,IN,INPUT,INTEGER,
                    LE,LT,MINUS,MODULE,MUL,NE,NUM,OF,OR,PARAMETERS,PLUS,PRINT,
                    PROGRAM,RANGEOP,REAL,RETURNS,RNUM,SEMICOL,SQBC,SQBO,START,
                    SWITCH,TAKES,TRUE,USE,WHILE,WITH,arithmeticExpr,arithmeticExpr_lr,
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

typedef first_follow_node
{
    bool first_set_array[MAX_BOOL_ARRAY_SIZE];
    bool follow_set_array[MAX_BOOL_ARRAY_SIZE];
}first_follow_node;


typedef first_follow
{
    first_follow_node* fnf[NUM_NON_TERMINALS];
}first_follow;


typedef struct grammar_node
{
    // a single node of a grammar rule. If rule is A->FOO BAR, then FOO is a node
    int variable;
    int is_terminal;
    struct grammar_node *next;
} NODE;

typedef struct grammar
{
    NODE *rules[MAX_RULE_NUM];
}   GRAMMAR;

typedef struct parse_table
{
    // fill after doubt 1
}   TABLE;

typedef struct parse_tree_node_data
{
    // data for printing and storing the parse tree effectively ftw
    
}

typedef struct parse_tree
{
    // n-ary tree structure
    TREE_NODE *data;
    int num_of_kids;
    struct parse_tree *kids[N_ARY_LIM];     // children nodes
}   PARSE_TREE;

void print_rule(NODE *rule);
void print_grammar(GRAMMAR *g);