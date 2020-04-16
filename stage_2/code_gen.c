// make assember
// 

#include "code_gen.h"

VARS vars;

int array_available_addr = 0;


int stack_count = 0;

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
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tmov sil, [rbp - %d]\n\n", temp);
        fprintf(fp, "\tcmp sil, 0\n");
        fprintf(fp, "\tjz false\n");
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp print\n\n");
        fprintf(fp, "false: \n");
        fprintf(fp, "\tlea rsi, [false_label]\n\n");
        fprintf(fp, "print: \n");
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


    fprintf(fp, "\t; stores the count\n\n");
    fprintf(fp, "\txor r12, r12\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\tmov r12d, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tmov r13d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tsub r12d, r13d\n");
    fprintf(fp, "\tinc r12d\n");
    fprintf(fp, "\t;mov r12, 5\n");
    fprintf(fp, "\txor r13, r13\n\n");  
    fprintf(fp, "\tarray_input_loop:\n");

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
    fprintf(fp, "mov r14, %d\n", base_offset);
    fprintf(fp, "add r14, r13\n");
    fprintf(fp, "\tmov r11, %d", base_offset);
    fprintf(fp, "lea rsi, [r11 + r14 * 8]\n");
    fprintf(fp, "call scanf\n\n");

    fprintf(fp, "inc r13d\n");
    fprintf(fp, "cmp r13d, r12d\n");
    fprintf(fp, "jne array_input_loop\n");
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

    fprintf(fp, "; stores the count\n\n");
    fprintf(fp, "xor r12, r12\n");
    fprintf(fp, "xor r13, r13\n");
    fprintf(fp, "mov r12, [rbp - %d]\n", upper_offset);
    fprintf(fp, "mov r13, [rbp - %d]\n", upper_offset);
    fprintf(fp, "sub r12, r13\n");
    fprintf(fp, "inc r12d\n");
    fprintf(fp, ";mov r12, 5\n");
    fprintf(fp, "xor r13, r13\n\n");  
    fprintf(fp, "array_output_loop:\n");

    if(type == INTEGER)
    {
        fprintf(fp, "lea rdi, [intFormat_out]\n");
        fprintf(fp, "\tmov r11, %d", base_offset);
        fprintf(fp, "mov rsi, [r11 + r14 * 8]\n");
        fprintf(fp, "add r14, r13\n");
        fprintf(fp, "mov rsi, [array_buffer + r14 * 8]\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_out]\n");
        fprintf(fp, "\tmov r11, %d", base_offset);
        fprintf(fp, "mov rsi, [r11 + r14 * 8]\n");
        fprintf(fp, "add r14, r13\n");
        fprintf(fp, "mov rsi, [array_buffer + r14 * 8]\n");
    }

    else if(type == BOOLEAN)
    {
        fprintf(fp, "lea rdi, [strFormat_in]\n");
        fprintf(fp, "\tmov r11, %d", base_offset);
        fprintf(fp, "lea rsi, [r11 + r14 * 8]\n");
        fprintf(fp, "add r14, r13\n");
        fprintf(fp, "mov rsi, [array_buffer + r14 * 8]\n");

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
                fprintf(fp, "\tmov [rbp - %d], rax\n");

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
                    fprintf(fp, "\tmov [array_available_addr], r14\n");
                    // load the start and end at their offset

                    int start_offset_scaled = id_entry->datatype->arrtype->begin_offset * 8;
                    int end_offset_scaled  = id_entry->datatype->arrtype->end_offset * 8;
                    
                    fprintf(fp, "; loading array offsets\n");
                    fprintf(fp, "mov r13, %d\n", start);
                    fprintf(fp, "mov [rbp - %d], r13\n", start_offset_scaled);
                    fprintf(fp, "mov r13, %d\n", end);
                    fprintf(fp, "mov [rbp - %d], r13\n", end_offset_scaled);
                    
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

        if (id_entry->datatype->simple != ARRAY)
        {
            fprintf(fp, "\t;Taking id\n\n");
            prompt_user(fp, id_entry->datatype->simple);       
            take_input(fp,  id_entry->datatype->simple, id_entry->offset);
        }

        else 
        {
            fprintf(fp, "\t;Taking array\n\n");
            ask_for_array(fp, id_entry->offset, id_entry->datatype->arrtype->begin_offset * 8, id_entry->datatype->arrtype->end_offset * 8, id_entry->datatype->arrtype->base_type);
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
            ask_for_array(fp, id_entry->offset, id_entry->datatype->arrtype->begin_offset * 8, id_entry->datatype->arrtype->end_offset * 8, id_entry->datatype->arrtype->base_type);
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
