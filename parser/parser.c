#include<stdio.h>

#define RULE_FILE_PATH "../grammar/grammar_erplag.txt"
#define MAX_VAR_SIZE 50
#define MAX_RULE_NUM 150
#define N_ARY_LIM 15            // max size from current grammar is 12. Increase it if required.

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

typedef struct first_and_follow
{
    long long first;        // bit-masked, lexicographic on terminals
    long long follow;
}   FIRST_FOLLOW;

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

PARSE_TREE *create_new_node (int data)
{
    // creates a new leaf node storing data, and returns the node
    PARSE_TREE *new = (PARSE_TREE *) malloc(sizeof(PARSE_TREE));
    new->data = data;
    new->num_of_kids = 0;
    int end = N_ARY_LIM;
    while(--end >= 0) new->kids[end] = NULL;
    return new;
}

void print_rule(NODE *rule)
{
    while(rule != NULL)
    {
        printf("%s -> ",rule->variable);
        rule = rule->next;
    }
    return;
}

void print_grammar(GRAMMAR *g)
{
    int start = 0;
    while(g->rules[start])
    {
        print_rule(g->rules[start++]);
        putchar('\n');
    }   
    return;
}

// recursive
void print_parse_tree(PARSE_TREE *tree, char *out_file_name)
{
    // prints the given parse tree in an output file 
    FILE *f = fopen(out_file_name, "w");
    if (tree == NULL)
        return;         // print nothing
    else
    {
        fprintf(f, "%s ", var_enum_arr[tree->data]);
    }
    return;
}

void compute_first_follow(GRAMMAR *g, FIRST_FOLLOW *f)
{
    // ayush jain and bharat bhargava deserve all credit for this code
    return;
}

void create_parse_table(FIRST_FOLLOW *f, TABLE *t)
{
    return;
}

void parse(char *filename, TABLE *table, PARSE_TREE *tree)
{
    return;
}

int main()
{
    printf("LET THE CODE BEGIN.\n");
    return 0;
}