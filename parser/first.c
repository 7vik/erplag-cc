#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define RULE_FILE_PATH "../grammar/grammar.txt"
#define TOKEN_MAX_SIZE 50
#define MAX_RULE 150


typedef enum {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist_lr", "input_plist", "output_plist_lr",
"output_plist", "datatype", "rangeArr", "type", "moduleDef", "statements", "statement", "ioStmt", "var", "whichId", "printOpt",
"simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDStmt", "lvalueARRStmt", "index", "module ReuseStmt", "optional", "idList_lr", "idList", "expression",
"opt_expr_lr", "opt_expr", "one_more_opt", "booleanConst", "arithmeticExpr_ lr", "arithmeticExpr_lr", "arithmeticExpr", "term_lr", "term", "factor", "op",
"op1", "op2", "logicalOp", "relationalOp", "declareStmt", "value", "caseStmt", "default", "conditionalStmt", "range", "iterativeStmt"} NT;

typedef struct set
{
    NT token;
    long long int mask;
} SET;



typedef struct grammar_rule
{
    // linked list representing a grammar rule (X -> Y1 Y2 Y3) as X -> Y1 -> Y2 -> Y3 -> null
    char tnt[TOKEN_MAX_SIZE];
    int is_terminal_flag;
    struct grammar_rule *next;

} RULE;


void print_rule(RULE *lst)
{
    while(lst != NULL)
    {
        printf("%s -> ",lst->tnt);
        lst = lst->next;
    }
    return;
}

void print_grammar(RULE* grammar[], int index)
{
    for(int i = 0; i < index; i++)
    {
        print_rule(grammar[i]);
        printf("\n");
    }   
}

// returns 0 if the token is non-terminal
int is_terminal(char* tnt)
{
    if (tnt == NULL)
    {
        printf("In is_terminal: NULL String\n");
        exit(2);
    }

    if (isupper(tnt[0]))
        return 1;
    else
        return 0;
    
}

RULE* exist_first(RULE* first_set[], char* search_token)
{   
    //printf("%s", search_token);
    for (int i = 0; i < MAX_RULE; i++)
    {
        if (first_set[i] == NULL)
        {
            return NULL;
        }

        if(strcmp(first_set[i]->tnt, search_token) == 0)
            return first_set[i];
    }

    return NULL;
}

RULE* return_first(RULE* first_table[], RULE* grammar[], int index, char* token)
{   
    //printf("inside return first: %s\n", token);
    RULE* set;
    /*
    if((set = exist_first(first_table, token)) != NULL)
    {   
        //printf("first already counted\n");
        return set;
    }
    */    
    RULE* first_set = (RULE*) malloc(sizeof(RULE));
    RULE* cur_ptr = first_set;
    strcpy(first_set->tnt, "\0");
    first_set->next = NULL;
    if (token == NULL)
    {
        return NULL;
        //printf("nshbf");
    }    
    else if (is_terminal(token))
    {
        //RULE* first_set = (RULE*)malloc(sizeof(RULE));
        //printf("terminal found: %s\n", token);
        strcpy(first_set->tnt, token);
        first_set->next = NULL;
        
    }
    
    else
    {

        for (int i = 0; i < index; i++)
        {

            if(strcmp(token, grammar[i]->tnt) == 0)
            {
                //printf("match: %s\n", token);
                RULE* temp_set = return_first(first_table, grammar, index, grammar[i]->next->tnt);
                //printf("enr");
                print_rule(temp_set);
                printf("\n%s, \n\n", token);
                //exit(0);
                RULE* rule_ptr = grammar[i]->next;
                while(strcmp(temp_set->tnt, "EPS") == 0)
                {
                    if(strcmp(first_set->tnt, "\0"))
                    {
                        first_set = temp_set;
                        while(cur_ptr->next != NULL)
                        {
                            cur_ptr = cur_ptr->next;
                        }
                    }
                    else
                    {
                        cur_ptr->next = temp_set;
                        while(cur_ptr->next != NULL)
                        {
                            cur_ptr = cur_ptr->next;
                        }
                    }

                    temp_set = (RULE*) malloc(sizeof(RULE));
                    if (rule_ptr->next != NULL)
                    {
                        temp_set = return_first(first_table ,grammar, index, rule_ptr->next->tnt);
                        rule_ptr = rule_ptr->next;
                    }

                    else
                    {
                        cur_ptr->next = (RULE*) malloc(sizeof(RULE));
                        strcpy(cur_ptr->next->tnt, "EPS");
                        cur_ptr->next->next = NULL;
                        break;
                    }

                }

                if(strcmp(first_set->tnt, "/0"))
                    first_set = temp_set;
                else
                    cur_ptr->next = temp_set;

            }

        }
    }
    
    return first_set;

}
RULE** construct_first_set(RULE* grammar[], int index)
{
    
    RULE **first_table = (RULE**)malloc(MAX_RULE * sizeof(RULE*));
    int count = 0;
    for (int i = 0; i < MAX_RULE; i++)
    {
        first_table[i] = (RULE*) malloc(sizeof(RULE));
        strcpy(first_table[i]->tnt, "\0");
        first_table[i]->next = NULL;
    }
    for(int i = 0; i < index; i++)
    {
        if (exist_first(first_table, grammar[i]->tnt) == NULL)
        {
            //first_table[count] = (RULE*) malloc(sizeof(RULE));
            first_table[count]->next = return_first(first_table, grammar, index, grammar[i]->tnt);
            strcpy(first_table[count]->tnt, grammar[i]->tnt);
            //printf("%s\n", grammar[i]->tnt);
            //print_rule(first_table[count]);
            //printf("end\n");
            count++;
        }

        
    }
    printf("%d", count);
    print_grammar(first_table, count);
    return first_table;

    /*****************To DO**********************
     * Remove duplicates from first_table
     */
}

void print_non_terminals(RULE* grammar[], int index)
{
    for(int i = 0; i < index; i++)
    {
        printf("\"%s\", ", grammar[i]->tnt);
    }   
}


int main()
{
    FILE *f = fopen(RULE_FILE_PATH, "r");
    if (f == NULL)
    {
        printf("Error opening file at %s. Aborting.\n", RULE_FILE_PATH);
        exit(1);
    }
    char line[200];
    RULE *grammar[MAX_RULE];
    int rule_count = 0;

    while (EOF != fscanf(f, "%[^\n]\n", line))
    {
        char* token = strtok(line, " ");

        // add non terminal as head
        
        grammar[rule_count] = (RULE*)malloc(sizeof(RULE));
        RULE* cur_pointer = grammar[rule_count];
        strcpy(grammar[rule_count]->tnt, token);
        grammar[rule_count]->is_terminal_flag = 0;
        grammar[rule_count]->next = NULL;
        token = strtok(NULL, " ");
        //printf("here\n");
        while(token != NULL)
        {
            //printf("%s %d\n", token, is_terminal(token));
            if (strcmp(token, "->") == 0)
            {
                token = strtok(NULL, " ");
                continue;
            }

            RULE* node = (RULE*) malloc(sizeof(RULE));
            strcpy(node->tnt, token);
            node->is_terminal_flag = is_terminal(token);
            node->next = NULL;
            cur_pointer->next = node;
            cur_pointer = cur_pointer->next; 
            token = strtok(NULL, " ");
        }
        //printf("here\n");
        rule_count++;
        
    }
    print_non_terminals(grammar, rule_count-1);

    //construct_first_set(grammar, rule_count - 1);
    fclose(f);
    return 0;
}

