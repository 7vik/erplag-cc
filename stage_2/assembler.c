#include "assembler.h"

typedef struct vars
{
    int num_byte_vars;      // 1 byte
    int num_word_vars;      // 2 bytes
    int num_double_vars;    // 4 bytes
    int num_quad_words;      // 8 bytes
}VARS;


VARS vars;


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
    fprintf(fp, "var1         dd        7\n");
    fprintf(fp, "var2         dd        14\n");
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


void take_int_input(FILE* fp, int input_var_num)
{
    // for int

    fprintf(fp, "push rbp\n");
    fprintf(fp, "mov rdi, intFormat\n");
    fprintf(fp, "mov rsi, vard%d\n", input_var_num);
    fprintf(fp, "call scanf\n");
    fprintf(fp, "pop rbp\n\n");
}


void take_real_input(FILE* fp, int input_var_num)
{
    fprintf(fp, "push rbp\n");
    fprintf(fp, "mov rdi, realFormat\n");
    fprintf(fp, "mov rsi, vard%d\n", input_var_num);
    fprintf(fp, "call scanf\n");
    fprintf(fp, "pop rbp\n\n");
}

void print_int_output(FILE* fp, int output_var_num)
{
    // for int

    fprintf(fp, "push rbp\n");
    fprintf(fp, "mov rdi, intFormat\n");
    fprintf(fp, "mov rsi, [vard%d]\n", output_var_num);
    fprintf(fp, "call printf\n");
    fprintf(fp, "pop rbp\n\n");
}

void ask_for_int(FILE* fp)
{
    fprintf(fp, "push rbp\n");
    fprintf(fp, "mov rdi, int_inMsg\n");
    fprintf(fp, "call printf\n");
    fprintf(fp, "pop rbp\n\n");
}

// type is enum in this case
void ask_for_array(FILE* fp, int lower_var_num, int upper_var_num, int type)
{

    fprintf(fp, "push rbp\n");
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
    fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


}

// type is enum in this case
void print_array(FILE* fp, int lower_var_num, int upper_var_num, int type)
{
    
    fprintf(fp, "push rbp\n");

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

    fprintf(fp, "pop rbp\n");
    fprintf(fp, "\n\n");


}


void print_return(FILE* fp)
{
    fprintf(fp, "mov rax, 0\n");
    fprintf(fp, "ret\n");
}


void generate_code(astNode* root, GST* symbol_table, FILE* fp)
{
    if (root == NULL)
        return;

    switch (root->node_marker)
    {
        case assignmentStmt:
            printf("%s\n", variables_array[root->node_marker]);
            generate_code_assignmentStmt(root, symbol_table, fp);
            break;
        case printOpt:
            printf("%s\n", variables_array[root->node_marker]);
            generate_code_printStmt(root, symbol_table, fp);
            break;
        case GET_VALUE:
            printf("%s\n", variables_array[root->node_marker]);
            generate_code_inputStmt(root, symbol_table, fp);
            break;
        case iterativeStmt:
            printf("%s\n", variables_array[root->node_marker]);
            generate_code_iterativeStmt(root, symbol_table, fp);
            break;
        case conditionalStmt:
            printf("%s\n", variables_array[root->node_marker]);
            generate_code_conditionalStmt(root, symbol_table, fp);
            break;
        default:
        {
            astNode* temp = root->child;
            while(temp != NULL)
            {
                generate_code(temp, symbol_table, fp);
                temp = temp->sibling;

            }
            break;
        }

    }

}

void initialise_file(FILE* fp)
{
    print_data_section(fp);

    // for one double var
    vars.num_double_vars++;
    print_bss_section(fp, vars);
    print_externs(fp);

    fprintf(fp, "main:\n\n");
    return;   
}

// a lot of things remaining
void generate_code_assignmentStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    //assignOP
    astNode* temp_node = root->child;

    //haven't handled var as Array
    //needs to be modified for assembly

    //base case
    // if ((temp_node->child == var || temp_node->child == NUM || temp_node->child == RNUM)
    //             && (temp_node->child->sibling == var || temp_node->child->sibling == NUM || temp_node->child->sibling == RNUM))
    // {
    //     char* s1, s2;
    //     if(temp_node->child == var)
    //         s1 = temp_node->child->child->tree_node->lexeme;
    //     else
    //         s1 = temp_node->child->tree_node->lexeme;
        
    //     if(temp_node->child->sibling == var)
    //         s2 = temp_node->child->sibling->child->tree_node->lexeme;
    //     else
    //         s2 = temp_node->child->sibling->tree_node->lexeme;

    //     if(temp_node->node_marker == MUL)
    //         fprintf(fp, "\t\tmul %s, %s\n", s1, s2);
    //     else if(temp_node->node_marker == PLUS)
    //         fprintf(fp, "\t\tadd %s, %s\n", s1, s2);
    //     else if(temp_node->node_marker == MINUS)
    //         fprintf(fp, "\t\tsub %s, %s\n", s1, s2);
    //     else
    //         fprintf(fp, "\t\teq %s, %s\n", s1, s2);
        
    // }

    return;
}
void generate_code_printStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    assert(root->node_marker == printOpt);
    return;
}
void generate_code_inputStmt(astNode* root, ID_SYMBOL_TABLE *st, FILE* fp)
{
    assert(root->node_marker == GET_VALUE);
    ask_for_array(fp, 1, 2, BOOLEAN);
    print_array(fp, 1, 2, BOOLEAN);
    print_return(fp);
    return;
}
void generate_code_iterativeStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    assert(root->node_marker == iterativeStmt);
    return;
}
void generate_code_conditionalStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    assert(root->node_marker == conditionalStmt);
    return;
}

int main(int argc, char* argv[])          // driver
{
    printf("global main\nextern printf\nextern scanf\nextern puts\nsection .data\nMEM: times 1000 db 0\narr:  times 2 db 0\nmen:  db \"Value is %%d \",10,0\ninputFormat: db \"%%d\",10,0\nvar: times 8 db 0\n\nsection .text\nmain:\n\n");
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

    printf("Printed Parse Tree in file '%s'.\n", argv[2]);
    // printf("Rule number of root: %d\n", tree->kids[0]->data->rule_number);
    astNode* ast_root = buildAST(tree);
    // printf("H1\n");
    print_ast_json(ast_root, "output_ast_tree.json");

    //EMPTY SYMBOL TABLE FOR NOW
    GST* symbol_table = create_global_st();

    printf("Starting code generation\n");
    FILE* code_fp = fopen(argv[3], "w");
    initialise_file(code_fp);
    generate_code(ast_root, symbol_table, code_fp); 


    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
}
