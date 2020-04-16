// make assember
// 

#include "code_gen.h"

VARS vars;

int array_available_addr = 0;
int label_count = 0;

int stack_count = 0;


char* generate_label(void)
{
    char* label = (char*) malloc((sizeof(100*sizeof(char))));
    sprintf(label, "label%d", label_count);
    label_count++;
    return label;
}
void print_return(FILE* fp)
{

    fprintf(fp, "add rsp, %d\n", ((stack_count / 2 ) + 1) * 16);
    fprintf(fp, "pop rbp\n");
    fprintf(fp, "mov rax, 0\n");
    fprintf(fp, "ret\n");
}

void print_externs(FILE* fp)
{
    fprintf(fp, "global main\n");
    fprintf(fp, "extern printf\n");
    fprintf(fp, "extern scanf\n");
    fprintf(fp, "extern puts\n");
    fprintf(fp, "extern exit\n");

    fprintf(fp, "\nsection  .text\n\n");

    return;
}

void print_data_section(FILE* fp)
{
    fprintf(fp, "section .data\n\n");

    fprintf(fp, "int_inMsg    db        \"Enter an integer value\" , 10, 0\n"); 
    fprintf(fp, "real_inMsg   db        \"Enter a real value\", 10, 0\n");
    fprintf(fp, "bool_inMsg   db        \"Enter a boolean value\", 10, 0\n");
    fprintf(fp, "arr_inMsg    db        \"Enter %%d elements of %%s type for array range %%d to %%d\", 10, 0\n");
    fprintf(fp, "intFormat     db        \"%%d\", 0\n");
    fprintf(fp, "type_int      db        \"integer\", 0\n");
    fprintf(fp, "type_real     db        \"real\", 0\n");
    fprintf(fp, "type_bool     db        \"boolean\", 0\n");    
    fprintf(fp, "intFormat_in  db        \"%%d\", 0\n");
    fprintf(fp, "intFormat_out db        \"%%d \", 0\n");
    fprintf(fp, "realFormat_in db        \"%%lf\", 10, 0\n");
    fprintf(fp, "realFormat_out db       \"%%lf\", 0\n");
    fprintf(fp, "strFormat_in   db       \"%%s\", 0\n");
    fprintf(fp, "strFormat_out   db       \"%%s\", 10, 0\n");
    fprintf(fp, "true_label     db        \"true \", 0\n");
    fprintf(fp, "false_label     db        \"false \", 0\n");
    fprintf(fp, "arr_outMsg   db        \"Printing array: \", 0\n");
    fprintf(fp, "new_line       db       10, 0\n");
    fprintf(fp, "var1         dd        3\n");
    fprintf(fp, "var2         dd        6\n");
    fprintf(fp, "array_available_addr   dd   0\n");
    fprintf(fp, "\n\n\n");

    return;
}

void print_bss_section(FILE* fp, VARS vars)
{
    fprintf(fp, "\t\tsection .bss\n\n");

    char buff[100];
    for(int i = 0; i < vars.num_byte_vars; i++)
    {
        sprintf(buff, "varb%d:   resb    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    for(int i = 0; i < vars.num_double_vars; i++)
    {
        sprintf(buff, "vard%d:   resd    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    for(int i = 0; i < vars.num_quad_words; i++)
    {
        sprintf(buff, "varq%d:   resq    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    for(int i = 0; i < vars.num_word_vars; i++)
    {
        sprintf(buff, "varw%d:   resw    1\n", i + 1);
        fprintf(fp, "%s\n", buff);
    }

    fprintf(fp, "int_array:         resd        100\n");
    fprintf(fp, "real_array:        resq        100\n");
    fprintf(fp, "bool_array:        resb        100\n");

    fprintf(fp, "array_buffer:      resq        1000\n");

    fprintf(fp, "\n\n");
}

void initialise_file(FILE* fp)
{
    print_data_section(fp);

    // for one double var
    vars.num_double_vars++;
    print_bss_section(fp, vars);
    print_externs(fp);
    return;   
}

void take_input(FILE* fp, int type, int offset)
{
    // for int
    int temp = offset * 8;
    if(type == INTEGER || type == BOOLEAN)
    {
        fprintf(fp, "\tmov rdi, intFormat_in\n");
        fprintf(fp, "\tlea rsi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall scanf\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "\tmov rdi, realFormat_in\n");
        fprintf(fp, "\tlea rsi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall scanf\n");
    }
    
}



void prompt_user(FILE* fp, int type)
{
    // fprintf(fp, "push rbp\n");

    if (type == INTEGER)
        fprintf(fp, "\tmov rdi, int_inMsg\n");
    else if (type == BOOLEAN)
        fprintf(fp, "\tmov rdi, bool_inMsg\n");
    else if (type == REAL)
        fprintf(fp, "\tmov rdi, real_inMsg\n");
    else
    {
        printf("ERROR\n");
        exit(1);
    }
    
    fprintf(fp, "\tcall printf\n");
    // fprintf(fp, "pop rbp\n\n");
}


void print_id(FILE* fp, int type, int offset)
{
    // for int
    int temp = offset * 8;
    if(type == INTEGER)
    {
        fprintf(fp, "\tmov rdi, intFormat_out\n");
        fprintf(fp, "\tmov rsi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "\tmov rdi, realFormat_out\n");
        fprintf(fp, "\tmov rsi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tmov sil, [rbp - %d]\n\n", temp);
        fprintf(fp, "\tcmp sil, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "f%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");
        fprintf(fp, "%s: \n", p_label);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n");
        fprintf(fp, "\n\n");
    }
    
}

// type is enum in this case
void ask_for_array(FILE* fp, int base_offset, int lower_offset, int upper_offset, int type)
{

    // fprintf(fp, "push rbp\n");
    fprintf(fp, "; prompts user for input\n");
    fprintf(fp, "\tmov rcx, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tmov r8, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tmov rsi, r8\n");
    fprintf(fp, "\tsub rsi, rcx\n");
    fprintf(fp, "\tinc rsi\n");
    fprintf(fp, "\tmov rdi, arr_inMsg\n");

    if (type == INTEGER)
        fprintf(fp, "mov rdx, type_int\n");
    else if (type == REAL)
        fprintf(fp, "mov rdx, type_real\n");
    else if (type == BOOLEAN)
        fprintf(fp, "mov rdx, type_bool\n");
    else
    {
        printf("Error in ask for array function\n");
        exit(1);
    }
    
    fprintf(fp, "\tmov rcx, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tmov r8, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tcall printf\n\n");

    char* array_input_label  = generate_label();
    fprintf(fp, "\t; stores the count\n\n");
    fprintf(fp, "\txor r12, r12\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\tmov r12, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tmov r13, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tsub r12, r13\n");
    fprintf(fp, "\tinc r12\n");
    fprintf(fp, "\txor r13, r13\n\n");  
    fprintf(fp, "\t%s:\n", array_input_label);

    if(type == INTEGER)
    {
        fprintf(fp, "lea rdi, [intFormat_in]\n");
       
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_in]\n");
    }

    else if(type == BOOLEAN)
    {
        fprintf(fp, "lea rdi, [intFormat_in]\n");
    }

    else
    {
        printf("ERROR in ask for array\n");
        exit(1);
    }
    fprintf(fp, "\tmov r14, [rbp - %d]\n", base_offset);
    fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
    fprintf(fp, "\tcall scanf\n\n");

    fprintf(fp, "\tinc r13\n");
    fprintf(fp, "\tcmp r13, r12\n");
    fprintf(fp, "\tjne %s\n", array_input_label);
    // fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


}

// type is enum in this case
void print_array(FILE* fp, int base_offset, int lower_offset, int upper_offset, int type)
{
    
    // fprintf(fp, "push rbp\n");

    fprintf(fp, "; printing array\n");
    fprintf(fp, "lea rdi, [arr_outMsg]\n");
    fprintf(fp, "call printf\n");

    char* array_output_label = generate_label();
    fprintf(fp, "; stores the count\n\n");
    fprintf(fp, "xor r12, r12\n");
    fprintf(fp, "xor r13, r13\n");
    fprintf(fp, "mov r12, [rbp - %d]\n", upper_offset);
    fprintf(fp, "mov r13, [rbp - %d]\n", lower_offset);
    fprintf(fp, "sub r12, r13\n");
    fprintf(fp, "inc r12\n");
    fprintf(fp, "xor r13, r13\n\n");  
    fprintf(fp, "%s:\n", array_output_label);

    if(type == INTEGER)
    {
        fprintf(fp, "\tlea rdi, [intFormat_out]\n");
        fprintf(fp, "\tmov r14, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
        fprintf(fp, "\tadd r14, r13\n");
        fprintf(fp, "\tmov rsi, [array_buffer + r14 * 8]\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_out]\n");
        fprintf(fp, "\tmov r14, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
        fprintf(fp, "\tadd r14, r13\n");
        fprintf(fp, "\tmov rsi, [array_buffer + r14 * 8]\n");
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tmov r14, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tmov rsi, [r14 + r13 * 8]\n");

        fprintf(fp, "\tcmp sil, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");

        fprintf(fp, "%s: \n", p_label);

    }

    else
    {
        printf("ERROR in ask for array\n");
        exit(1);
    }
    
    fprintf(fp, "\tcall printf\n\n");
    fprintf(fp, "\tinc r13\n");
    fprintf(fp, "\tcmp r13, r12\n");
    fprintf(fp, "\tjne %s\n", array_output_label);
    fprintf(fp, "\tlea rdi, [new_line]\n");
    fprintf(fp, "\tcall printf\n");

    // fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


}

// evaluates the rhs and stores the result in RCX
void evaluate_expr(astNode *ex, ID_SYMBOL_TABLE *id_st, FILE *fp)
{
    if (ex->node_marker == ID)
    {
        ID_TABLE_ENTRY *i = st_lookup(ex->tree_node->lexeme, id_st);
        if (i == NULL)
        {
            PARAMS *p1 = param_lookup(id_st->primogenitor->in_params ,ex->tree_node->lexeme);
            PARAMS *p2 = param_lookup(id_st->primogenitor->out_params ,ex->tree_node->lexeme);
            // else if (p1 != NULL) return p1->datatype->simple;
            // else if (p2 != NULL) return p2->datatype->simple;
        }
        else        // is in ID_ST
        {
            int offset = i->offset;
            fprintf(fp, "\tmov rcx, [rbp - %d]\n", offset * 8);
            return;
        }
    }
    if (ex->node_marker == RNUM)
        return REAL;
    if (ex->node_marker == NUM)
        return INTEGER;
    if (ex->node_marker == TRUE || ex->node_marker == FALSE)
        return BOOLEAN;
    if (ex->node_marker ==  LE||ex->node_marker ==  GE||ex->node_marker ==  LT||ex->node_marker ==  GT||ex->node_marker ==  EQ||ex->node_marker ==  NE||0)
    {
        if (get_type_expr(ex->child, id_st) != get_type_expr(ex->child->sibling, id_st))
        {
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Exppected type '%s' for comparison, gotten type '%s'.\n",ex->tree_node->line, variables_array[get_type_expr(ex->child, id_st)], variables_array[get_type_expr(ex->child->sibling, id_st)]);
            error_line = ex->tree_node->line;
            hasSemanticError = true;
        }
        else
            return BOOLEAN;
    }
    if (ex->node_marker == AND ||ex->node_marker == OR||0)
    {
        if (get_type_expr(ex->child, id_st) != get_type_expr(ex->child->sibling, id_st))
        {
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Expnected type '%s' for comparison, gotten type '%s'.\n",ex->tree_node->line, variables_array[get_type_expr(ex->child, id_st)], variables_array[get_type_expr(ex->child->sibling, id_st)]);
            error_line = ex->tree_node->line;
            hasSemanticError = true;
        }
        else
            return BOOLEAN;
    }
    if (ex->node_marker ==  PLUS    || (ex->node_marker ==  MINUS && ex->child->sibling != NULL)   || ex->node_marker ==  DIV     || ex->node_marker ==  MUL     ||0 )
    {
        // printf("FRT1\n");
        int t1 = get_type_expr(ex->child, id_st);
        // printf("FRT2\n");
        int t2 = get_type_expr(ex->child->sibling, id_st); 
        // printf("FRT3\n");
        if (t1 != t2)
        {
            // printf("ENTERIF\n");
            if (ex->tree_node->line > error_line)
                printf("Semantic Error on line %d. Exprected type '%s' for arithmetic operation, gotten type '%s'.\n",ex->tree_node->line, variables_array[get_type_expr(ex->child, id_st)], variables_array[get_type_expr(ex->child->sibling, id_st)]);
            error_line = ex->tree_node->line;
            hasSemanticError = true;
        }
        else
            return get_type_expr(ex->child, id_st);
    }
    if (ex->node_marker == MINUS && ex->child->sibling == NULL)
        return  get_type_expr(ex->child, id_st);
    if (ex->node_marker == var)
    {
        if (ex->child->sibling == NULL)     // not an array element
            return get_type_expr(ex->child, id_st);
        else                                // array element
        {
            // printf("WHYTHO2?\n");
            ID_TABLE_ENTRY *i = st_lookup(ex->child->tree_node->lexeme, id_st);
            if (i == NULL)
            {
                PARAMS *p = param_lookup(id_st->primogenitor->in_params ,ex->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,ex->child->tree_node->lexeme);
                if (p == NULL)
                {
                    if (ex->tree_node->line > error_line)
                        printf("Semantic Error on line %d. Variable '%s' not declared.\n", ex->child->tree_node->line, ex->child->tree_node->lexeme);
                    error_line = ex->tree_node->line;
                    hasSemanticError = true;
                }
                else if (p->datatype->simple != ARRAY)
                {
                    if (ex->tree_node->line > error_line)
                        printf("Semantic Error on line %d. Variable '%s' is not an array.\n", ex->tree_node->line, ex->child->tree_node->lexeme);
                    error_line = ex->tree_node->line;
                    hasSemanticError = true;
                }
                else if (get_type_expr(ex->child->sibling, id_st) != INTEGER)
                {
                    if (ex->tree_node->line > error_line)
                        printf("Semantic Error on line %d. Array index not an integer.\n", ex->tree_node->line);
                    error_line = ex->tree_node->line;
                    hasSemanticError = true;
                }
                else
                {
                    return p->datatype->arrtype->base_type;
                }
            }
            else if (i->datatype->simple != ARRAY)
            {
                if (ex->tree_node->line > error_line)
                    printf("Semantic Error on line %d. Variable '%s' is not an array.\n", ex->tree_node->line, ex->child->tree_node->lexeme);
                error_line = ex->tree_node->line;
                hasSemanticError = true;
            }
            else if (get_type_expr(ex->child->sibling, id_st) != INTEGER)
            {
                if (ex->tree_node->line > error_line)
                    printf("Semantic Error on line %d. Array index not an integer.\n", ex->tree_node->line);
                error_line = ex->tree_node->line;
                hasSemanticError = true;
            }
            else
            {
                return i->datatype->arrtype->base_type;
            }
        }
    }
    if (ex->node_marker == ARRAY)
        return ARRAY;
    return;
}

// trav a single function and generate the ASM code
void generate_the_universe(astNode *n, ID_SYMBOL_TABLE *id_st, FILE* fp)
{
    // printf("aasdfasdf\n");
    printf("SMALL\t%s\n", variables_array[n->node_marker]);
    if (is(n, "moduleDef"))
    {
        generate_the_universe(n->child->sibling, id_st, fp);
    }
    if (is(n, "statements"))
    {
        for(astNode *temp = n->child; temp; temp = temp->sibling)
        {
            generate_the_universe(temp, id_st, fp);
        }
    }
    if (is(n, "declareStmt"))
    {
        astNode* temp = n->child;

        while(temp->node_marker != EPS)
        {
            if (stack_count % 2 == 0)
                fprintf(fp, "\tsub rsp, 16\n");
            stack_count++;

            // if array 
            ID_TABLE_ENTRY* id_entry = st_lookup(temp->tree_node->lexeme, id_st);

            if(id_entry->datatype->simple == ARRAY)
            {
                int offset = id_entry->offset;
                
                //storing base address of this array: part of array_buffer
                fprintf(fp, "\tmov r14, [array_available_addr]\n");
                fprintf(fp, "\tlea rax, [array_buffer + r14]\n");
                fprintf(fp, "\tmov [rbp - %d], rax\n\n", offset * 8);

                // if static array
                if (id_entry->datatype->arrtype->is_dynamic == false)
                {
                    int start = id_entry->datatype->arrtype->begin;
                    int end = id_entry->datatype->arrtype->end;

                    //increment array_available_addr by the used memory

                    // calculate array size

                    int array_size = end - start + 1;
                    fprintf(fp, "\tmov r14, [array_available_addr]\n");
                    fprintf(fp, "\tadd r14, %d\n", array_size);
                    fprintf(fp, "\tmov [array_available_addr], r14\n\n");
                    // load the start and end at their offset

                    int start_offset_scaled = id_entry->datatype->arrtype->begin_offset * 8;
                    int end_offset_scaled  = id_entry->datatype->arrtype->end_offset * 8;
                    
                    fprintf(fp, "; loading array offsets\n");
                    fprintf(fp, "mov r13, %d\n", start);
                    fprintf(fp, "mov [rbp - %d], r13\n", start_offset_scaled);
                    fprintf(fp, "mov r13, %d\n", end);
                    fprintf(fp, "mov [rbp - %d], r13\n\n", end_offset_scaled);
                    
                }

                else
                {
                    // do something for dynamic array
                }

            }

            temp = temp->sibling;
        }
        
    }
    if (is(n, "assignmentStmt"))
    {
        generate_the_universe(n->child, id_st, fp);
    }
    if (is(n, "ASSIGNOP"))
    {
       evaluate_expr(n->child->sibling, id_st, fp); // evaluate the rhs
    }
    if (is(n, "iterativeStmt") && is(n->child, "ID"))   // for lup
    {
        
    }
    if (is(n, "iterativeStmt") && (1 - is(n->child, "ID")))   // while lup
    {
       
    }
    if (is(n, "ioStmt") && n->child->node_marker == GET_VALUE)
    {
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->child->tree_node->lexeme, id_st);

        if (id_entry->datatype->simple != ARRAY)
        {
            fprintf(fp, "\t;Taking id\n\n");
            prompt_user(fp, id_entry->datatype->simple);       
            take_input(fp,  id_entry->datatype->simple, id_entry->offset);
        }

        else 
        {
            fprintf(fp, "\t;Taking array\n\n");
            ask_for_array(fp, id_entry->offset * 8, id_entry->datatype->arrtype->begin_offset * 8, id_entry->datatype->arrtype->end_offset * 8, id_entry->datatype->arrtype->base_type);
        }

    }
    if (is(n, "ioStmt") && n->child->node_marker == printOpt)
    {
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->child->child->tree_node->lexeme, id_st);
        if (id_entry->datatype->simple != ARRAY)
        {
            fprintf(fp, "\t;Printing ID\n\n");
            print_id(fp,  id_entry->datatype->simple, id_entry->offset);
        }
        else
        {
            fprintf(fp, "\t;Printing array\n\n");
            print_array(fp, id_entry->offset * 8, id_entry->datatype->arrtype->begin_offset * 8, id_entry->datatype->arrtype->end_offset * 8, id_entry->datatype->arrtype->base_type);
        }
        
    }
    if (is(n, "conditionalStmt"))
    {
        
    }
    if (is(n, "caseStmts"))
    {
        
    }
    if (is(n, "caseStmt"))
    {
        
    }
    if (is(n, "moduleReuseStmt") && n->child->node_marker == EPS)
    {
        
    }
    if (is(n, "moduleReuseStmt") && n->child->node_marker != EPS)
    {
       
    }
    return;
}


// trav the ast and create ASM code 
void generate_the_multiverse(astNode *n, GST *st, FILE* fp)
{
    printf("BIG\t%s\n", variables_array[n->node_marker]);
    if (is(n,"program"))
    {
        for(astNode *temp = n->child; temp; temp = temp->sibling)
        {
            generate_the_multiverse(temp,st, fp);
        }
    }

    if (is(n, "moduleDeclarations"))
        stack_count = 0;

    if (is(n, "otherModules") && n->sibling != NULL)
        stack_count = 0;

    if (is(n, "driverModule"))
    {
        FUNC_TABLE_ENTRY *f = global_st_lookup("driverModule", st);
        fprintf(fp, "main:\n\n");
        fprintf(fp, "push rbp\n");
        fprintf(fp, "mov rbp, rsp\n");
        stack_count = 0;
        generate_the_universe(n->child, f->local_id_table, fp);
    }
    if (is(n, "otherModules") && n->sibling == NULL)
    {
        ;
    }
    if (is(n, "EPS"))
        return;         // bliss

    return;
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("Invalid argument count. Expected 4 arguments as in './executable testcase parse_outfile code.asm'.");
        printf("\nAborting Execution!!\n");
        exit(2);
    }
    FILE* test_fp = fopen(argv[1], "r");
    FILE* test_parse_fp = fopen(argv[2], "w");
    populate_ht(hash_table, KEYWORDS_FILE);
    int line_count = 1;
    TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
    init_buffer(test_fp, twin_buff);
    GRAMMAR* grammar = generate_grammar();
    first_follow *ff = get_first_follow_table(grammar);
    TABLE *parse_table = (TABLE *) malloc(sizeof(TABLE));
    create_parse_table(ff, parse_table, grammar);
    STACK *stack = NULL;
    PARSE_TREE *tree;
    parse(grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
    fprintf(test_parse_fp, "%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s%20s\n\n", "LEXEME", "LINE_NO", "VALUE (if num)", "TOKENAME",  "PARENT", "IS LEAF?", "NODE SYMBOL", "RULE_NUMBER");
    print_parse_tree(tree, test_parse_fp);
    print_parse_tree_json(tree, "output_parse_tree.json");
    astNode* ast_root = buildAST(tree);
    print_ast_json(ast_root, "output_ast_tree.json");
    // Test Symbol table
    GST *st = create_global_st();
    traverse_the_multiverse(ast_root, st);
    gst_print(st);

    // test code generation
    printf("Starting code generation\n");
    FILE* code_fp = fopen(argv[3], "w");
    initialise_file(code_fp);
    generate_the_multiverse(ast_root, st, code_fp);
    print_return(code_fp);
    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
}
