// make assember
// ./stage2exe t5.txt new.new code.asm

#include "code_gen.h"

VARS vars;


void print_return(FILE* fp)
{
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
    fprintf(fp, "\n\n\n");

    return;
}

void print_bss_section(FILE* fp, VARS vars)
{
    fprintf(fp, "section .bss\n\n");

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
    if(type == INTEGER)
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

// void print_int_output(FILE* fp, int output_var_num)
// {
//     // for int

//     fprintf(fp, "push rbp\n");
//     fprintf(fp, "mov rdi, intFormat\n");
//     fprintf(fp, "mov rsi, [vard%d]\n", output_var_num);
//     fprintf(fp, "call printf\n");
//     fprintf(fp, "pop rbp\n\n");
// }

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
    
    fprintf(fp, "call printf\n");
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
        fprintf(fp, "\tcall printf\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "\tmov rdi, realFormat_out\n");
        fprintf(fp, "\tmov rsi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall printf\n");
    }
    
}

// type is enum in this case
void ask_for_array(FILE* fp, int lower_var_num, int upper_var_num, int type)
{

    // fprintf(fp, "push rbp\n");
    fprintf(fp, "; prompts user for input\n");
    fprintf(fp, "mov rcx, [var%d]\n", lower_var_num);
    fprintf(fp, "mov r8, [var%d]\n", upper_var_num);
    fprintf(fp, "mov rsi, r8\n");
    fprintf(fp, "sub rsi, rcx\n");
    fprintf(fp, "inc rsi\n");
    fprintf(fp, "mov rdi, arr_inMsg\n");

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
    
    fprintf(fp, "mov rcx, [var%d]\n", lower_var_num);
    fprintf(fp, "mov r8, [var%d]\n", upper_var_num);
    fprintf(fp, "call printf\n\n");


    fprintf(fp, "; stores the count\n\n");
    fprintf(fp, "xor r12, r12\n");
    fprintf(fp, "xor r13, r13\n");
    fprintf(fp, "mov r12d, [var%d]\n", upper_var_num);
    fprintf(fp, "mov r13d, [var%d]\n", lower_var_num);
    fprintf(fp, "sub r12d, r13d\n");
    fprintf(fp, "inc r12d\n");
    fprintf(fp, ";mov r12, 5\n");
    fprintf(fp, "xor r13, r13\n\n");  
    fprintf(fp, "array_input_loop:\n");

    if(type == INTEGER)
    {
        fprintf(fp, "lea rdi, [intFormat_in]\n");
        fprintf(fp, "lea rsi, [int_array + r13d * 4]\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_in]\n");
        fprintf(fp, "lea rsi, [real_array + r13d * 8]\n");
    }

    else if(type == BOOLEAN)
    {
        fprintf(fp, "lea rdi, [intFormat_in]\n");
        fprintf(fp, "lea rsi, [bool_array + r13d * 1]\n");
    }

    else
    {
        printf("ERROR in ask for array\n");
        exit(1);
    }
    
    fprintf(fp, "call scanf\n\n");

    fprintf(fp, "inc r13d\n");
    fprintf(fp, "cmp r13d, r12d\n");
    fprintf(fp, "jne array_input_loop\n");
    // fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


}

// type is enum in this case
void print_array(FILE* fp, int lower_var_num, int upper_var_num, int type)
{
    
    // fprintf(fp, "push rbp\n");

    fprintf(fp, "; printing array\n");
    fprintf(fp, "lea rdi, [arr_outMsg]\n");
    fprintf(fp, "call printf\n");

    fprintf(fp, "; stores the count\n\n");
    fprintf(fp, "xor r12, r12\n");
    fprintf(fp, "xor r13, r13\n");
    fprintf(fp, "mov r12d, [var%d]\n", upper_var_num);
    fprintf(fp, "mov r13d, [var%d]\n", lower_var_num);
    fprintf(fp, "sub r12d, r13d\n");
    fprintf(fp, "inc r12d\n");
    fprintf(fp, ";mov r12, 5\n");
    fprintf(fp, "xor r13, r13\n\n");  
    fprintf(fp, "array_output_loop:\n");

    if(type == INTEGER)
    {
        fprintf(fp, "lea rdi, [intFormat_out]\n");
        fprintf(fp, "mov rsi, [int_array + r13d * 4]\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_out]\n");
        fprintf(fp, "mov rsi, [real_array + r13d * 8]\n");
    }

    else if(type == BOOLEAN)
    {
        fprintf(fp, "lea rdi, [strFormat_in]\n");
        fprintf(fp, "mov sil, [bool_array + r13d * 1]\n\n");

        fprintf(fp, "cmp sil, 0\n");
        fprintf(fp, "jz false\n");
        fprintf(fp, "lea rsi, [true_label]\n");
        fprintf(fp, "jmp print\n\n");
        fprintf(fp, "false: \n");
        fprintf(fp, "lea rsi, [false_label]\n\n");

        fprintf(fp, "print: \n");

    }

    else
    {
        printf("ERROR in ask for array\n");
        exit(1);
    }
    
    fprintf(fp, "call printf\n\n");

    fprintf(fp, "inc r13d\n");
    fprintf(fp, "cmp r13d, r12d\n");
    fprintf(fp, "jne array_output_loop\n");

    fprintf(fp, "lea rdi, [new_line]\n");
    fprintf(fp, "call printf\n");

    // fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


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
        ;
    }
    if (is(n, "assignmentStmt"))
    {
        
    }
    if (is(n, "ASSIGNOP"))
    {
       
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

        prompt_user(fp, id_entry->datatype->simple);       
        take_input(fp,  id_entry->datatype->simple, id_entry->offset);
        print_id(fp,  id_entry->datatype->simple, id_entry->offset);

    }
    if (is(n, "ioStmt") && n->child->node_marker == printOpt)
    {
        
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
        ;

    if (is(n, "otherModules") && n->sibling != NULL)
        ;
    if (is(n, "driverModule"))
    {
        // printf("mil\n");
        FUNC_TABLE_ENTRY *f = global_st_lookup("driverModule", st);
        fprintf(fp, "main:\n\n");
        fprintf(fp, "push rbp\n");
        fprintf(fp, "mov rbp, rsp\n");
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
