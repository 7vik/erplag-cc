// make assember
// 

#include "code_gen.h"

VARS vars;

int array_available_addr = 0;
int label_count = 0;
char* registers_array[] = {"rdi", "rsi", "rdx", "rcx", "r8",
                    "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
// change this after satvik implements
//refer to temp_funccall.asm by @bharat
//int stack_count = 0;


char* generate_label(void)
{
    char* label = (char*) malloc((sizeof(100*sizeof(char))));
    sprintf(label, "label%d", label_count);
    label_count++;
    return label;
}

char* generate_func_label(char* func_name)
{
    char* label = (char*) malloc((sizeof(100*sizeof(char))));
    sprintf(label, "%s:", func_name);
    return label;
}
void print_return(FILE* fp)
{

    fprintf(fp, "main_end:\n");
    fprintf(fp, "mov rsp, rbp\n");
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

    fprintf(fp, "int_inMsg    db        \"Input: Enter an integer value\" , 10, 0\n"); 
    fprintf(fp, "real_inMsg   db        \"Input: Enter a real value\", 10, 0\n");
    fprintf(fp, "bool_inMsg   db        \"Input: Enter a boolean value\", 10, 0\n");
    fprintf(fp, "arr_inMsg    db        \"Input: Enter %%d elements of %%s type for array range %%d to %%d\", 10, 0\n");
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
    fprintf(fp, "errorMsg1    db        \"RUN TIME ERROR: End index %%d of Array less than start index %%d at line %%d. Aborting\", 10, 0\n");
    fprintf(fp, "errorMsg2    db        \"RUN TIME ERROR: Index %%d out of bounds %%d and %%d at line %%d. Aborting.\", 10, 0\n");
    fprintf(fp, "new_line       db       10, 0\n");
    fprintf(fp, "var1         dd        3\n");
    fprintf(fp, "var2         dd        6\n");
    fprintf(fp, "array_available_addr   dq   0\n");
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

void bound_check(FILE* fp, int start_offset, int end_offset, int index, int line)
{
    char* error_label = generate_label();
    char* exit_label = generate_label();
    fprintf(fp, "; bound checking\n");
    fprintf(fp, "\tpush r13\n");
    fprintf(fp, "\tpush r14\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\tmov r13d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", end_offset * 8);
    fprintf(fp, "\tcmp r13d, %d\n", index);
    fprintf(fp, "\tjg %s\n", error_label);
    fprintf(fp, "\tcmp r14d, %d\n", index);
    fprintf(fp, "\tjl %s\n", error_label);
    fprintf(fp, "\tjmp %s\n", exit_label);

    fprintf(fp, "\t%s: \n", error_label);
    fprintf(fp, "\tlea rdi, [errorMsg2]\n");
    // "errorMsg2    db        \"RUN TIME ERROR: Index %%d out of
    // bounds %%d and %%d at line %%d. Aborting.\"
    fprintf(fp, "\tmov rsi, %d\n", index);
    fprintf(fp, "\tmov rdx,  r13\n");
    fprintf(fp, "\txor rcx, rcx\n");
    fprintf(fp, "\tmov rcx, r14\n");
    fprintf(fp, "\tmov r8, %d\n", line);
    fprintf(fp, "\txor rax, rax\n");
    fprintf(fp, "\tcall printf\n");
    fprintf(fp, "\tpop r14\n\tpop r13\n");
    fprintf(fp, "\tcall exit\n");
    fprintf(fp, "%s:\n", exit_label);
    fprintf(fp, "\tpop r14\n\tpop r13\n");
}

// for A[k] kind
void bound_check_dynamic(FILE* fp, int start_offset, int end_offset, int index_offset, int line)
{
    char* error_label = generate_label();
    char* exit_label = generate_label();
    fprintf(fp, "; bound checking\n");
    fprintf(fp, "\tpush r13\n");
    fprintf(fp, "\tpush r14\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\txor r15, r15\n");
    fprintf(fp, "\tmov r13d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", end_offset * 8);
    fprintf(fp, "\tmov r15d, [rbp - %d]\n", index_offset * 8);
    fprintf(fp, "\tcmp r13d, r15d\n");
    fprintf(fp, "\tjg %s\n", error_label);
    fprintf(fp, "\tcmp r14d, r15d\n");
    fprintf(fp, "\tjl %s\n", error_label);
    fprintf(fp, "\tjmp %s\n", exit_label);

    fprintf(fp, "\t%s: \n", error_label);
    fprintf(fp, "\tlea rdi, [errorMsg2]\n");
    // "errorMsg2    db        \"RUN TIME ERROR: Index %%d out of
    // bounds %%d and %%d at line %%d. Aborting.\"
    fprintf(fp, "\tmov rsi, r15\n");
    fprintf(fp, "\tmov rdx,  r13\n");
    fprintf(fp, "\txor rcx, rcx\n");
    fprintf(fp, "\tmov rcx, r14\n");
    fprintf(fp, "\tmov r8, %d\n", line);
    fprintf(fp, "\txor rax, rax\n");
    fprintf(fp, "\tcall printf\n");
    fprintf(fp, "\tcall exit\n");
    fprintf(fp, "%s:\n", exit_label);
    fprintf(fp, "\tpop r14\n\tpop r13\n");
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
        fprintf(fp, "\txor rsi, rsi\n");
        fprintf(fp, "\tmov esi, [rbp - %d]\n", temp);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "\tmov rdi, realFormat_out\n");
        fprintf(fp, "\txor rsi, rsi\n");
        fprintf(fp, "\tmov esi, [rbp - %d]\n", temp);
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
        fprintf(fp, "%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");
        fprintf(fp, "%s: \n", p_label);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n");
        fprintf(fp, "\n\n");
    }
    
}

void print_array_id(FILE* fp, int type, int base_offset, int start_offset, int index)
{
    // for int
    fprintf(fp, "\txor rsi, rsi\n");
    fprintf(fp, "\tmov r13, [rbp - %d]\n", base_offset * 8);
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\txor r15, r15\n");
    fprintf(fp, "\tmov r14d, %d\n", index);
    fprintf(fp, "\tmov r15d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tsub r14d, r15d\n");
    fprintf(fp, "\tmov esi, [r13 + r14 * 8]\n");

    if(type == INTEGER)
    {
        fprintf(fp, "\tmov rdi, intFormat_out\n");
        
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == REAL)
    {
        printf("Real not handled\n");
        exit(1);
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tcmp esi, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "%s: \n", f_label);
        fprintf(fp, "\tlea rsi, [false_label]\n\n");
        fprintf(fp, "%s: \n", p_label);
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n");
        fprintf(fp, "\n\n");
    }
    
}

void print_array_id_dynamic(FILE* fp, int type, int base_offset, int start_offset, int index_offset)
{
    // for int

    fprintf(fp, "\txor rsi, rsi\n");
    fprintf(fp, "\tmov r13, [rbp - %d]\n", base_offset * 8);
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\txor r15, r15\n");
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", index_offset * 8);
    fprintf(fp, "\tmov r15d, [rbp - %d]\n", start_offset * 8);
    fprintf(fp, "\tsub r14d, r15d\n");
    fprintf(fp, "\tmov esi, [r13 + r14 * 8]\n");

    if(type == INTEGER)
    {
        fprintf(fp, "\tmov rdi, intFormat_out\n");
        
        fprintf(fp, "\tcall printf\n\n");
        fprintf(fp, "\tlea rdi, [new_line]\n");
        fprintf(fp, "\tcall printf\n\n");
    }

    else if(type == REAL)
    {
        printf("Real not handled\n");
        exit(1);
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\tcmp esi, 0\n");
        fprintf(fp, "\tjz %s\n", f_label);
        fprintf(fp, "\tlea rsi, [true_label]\n");
        fprintf(fp, "\tjmp %s\n\n", p_label);
        fprintf(fp, "%s: \n", f_label);
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
    fprintf(fp, "; prompts user for input\n");
    fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tmov esi, r8d\n");
    fprintf(fp, "\tsub esi, ecx\n");
    fprintf(fp, "\tinc esi\n");
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
    fprintf(fp, "\txor rcx, rcx\n");
    fprintf(fp, "\txor r8, r8\n");
    fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tcall printf\n\n");

    char* array_input_label  = generate_label();
    fprintf(fp, "\t; stores the count\n\n");
    fprintf(fp, "\txor r12, r12\n");
    fprintf(fp, "\txor r13, r13\n");
    fprintf(fp, "\tmov r12d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "\tmov r13d, [rbp - %d]\n", lower_offset);
    fprintf(fp, "\tsub r12d, r13d\n");
    fprintf(fp, "\tinc r12d\n");
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
    fprintf(fp, "\txor r14, r14\n");
    fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
    fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
    fprintf(fp, "\tcall scanf\n\n");

    fprintf(fp, "\tinc r13d\n");
    fprintf(fp, "\tcmp r13d, r12d\n");
    fprintf(fp, "\tjne %s\n", array_input_label);
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
    fprintf(fp, "mov r12d, [rbp - %d]\n", upper_offset);
    fprintf(fp, "mov r13d, [rbp - %d]\n", lower_offset);
    fprintf(fp, "sub r12d, r13d\n");
    fprintf(fp, "inc r12d\n");
    fprintf(fp, "xor r13, r13\n\n");  
    fprintf(fp, "%s:\n", array_output_label);

    if(type == INTEGER)
    {
        fprintf(fp, "\tlea rdi, [intFormat_out]\n");
        fprintf(fp, "\txor r14, r14\n");
        fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tmov rsi, [r14 + r13 * 8]\n");
    }

    else if(type == REAL)
    {
        fprintf(fp, "lea rdi, [realFormat_out]\n");
        fprintf(fp, "\txor r14, r14\n");
        fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
        fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
        
    }

    else if(type == BOOLEAN)
    {
        char* f_label = generate_label();
        char* p_label = generate_label();
        fprintf(fp, "\tlea rdi, [strFormat_in]\n");
        fprintf(fp, "\txor r14, r14\n");
        fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
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
    fprintf(fp, "\tinc r13d\n");
    fprintf(fp, "\tcmp r13d, r12d\n");
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
            PARAMS *p = param_lookup(id_st->primogenitor->in_params ,ex->tree_node->lexeme);
            if(p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,ex->tree_node->lexeme);
            
            int offset = p->offset;
            fprintf(fp, "\txor rcx, rcx\n");
            fprintf(fp, "\tmov ecx, [rbp - %d + 208]\n", offset * 8);

        }
        else        // is in ID_ST
        {
            if(i->datatype->simple != ARRAY)
            {
                int offset = i->offset;
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\tmov ecx, [rbp - %d]\n", offset * 8);
                return;
            }
            
            
        }
    }

    else if (ex->node_marker == RNUM)
    {
        ;
    }
    else if (ex->node_marker == NUM)
    {
        char* num = ex->tree_node->lexeme;
        fprintf(fp, "\tmov rcx, %s\n", num);
    }

    else if (ex->node_marker == TRUE || ex->node_marker == FALSE)
    {
        if(ex->node_marker == TRUE)
            fprintf(fp, "\tmov rcx, 1\n");
        else
            fprintf(fp, "\tmov rcx, 0\n");
        
    }

    else if (ex->node_marker ==  LE||ex->node_marker ==  GE||ex->node_marker ==  LT||ex->node_marker ==  GT||ex->node_marker ==  EQ||ex->node_marker ==  NE)
    {   
        evaluate_expr(ex->child, id_st, fp);
        
        fprintf(fp, "\tpush rcx\n");
        fprintf(fp, "\tpush rcx\n");
        evaluate_expr(ex->child->sibling, id_st, fp);
        fprintf(fp, "\tpop rdx\n");
        fprintf(fp, "\tpop rdx\n");

        fprintf(fp, "\tcmp rdx, rcx\n");

        char* flag = generate_label();
        char* over = generate_label();

        if(ex->node_marker ==  GE)
            fprintf(fp, "\tjge %s\n", flag);
        if(ex->node_marker ==  LT)
            fprintf(fp, "\tjl %s\n", flag);
        if(ex->node_marker ==  GT)
            fprintf(fp, "\tjl %s\n", flag);
        if(ex->node_marker ==  EQ)
            fprintf(fp, "\tje %s\n", flag);
        if(ex->node_marker ==  NE)
            fprintf(fp, "\tjne %s\n", flag);
        if(ex->node_marker ==  LE)
            fprintf(fp, "\tjle %s\n", flag);
        
        fprintf(fp, "\tmov rcx, 0\n");
        fprintf(fp, "jmp %s\n", over);
        fprintf(fp, "%s:\n", flag);
        fprintf(fp, "\tmov rcx, 1\n");
        fprintf(fp, "%s:", over);

    }

    else if (ex->node_marker == AND ||ex->node_marker == OR)
    {
        evaluate_expr(ex->child, id_st, fp);
        
        fprintf(fp, "\tpush rcx\n");
        fprintf(fp, "\tpush rcx\n");
        evaluate_expr(ex->child->sibling, id_st, fp);
        fprintf(fp, "\tpop rdx\n");
        fprintf(fp, "\tpop rdx\n");

        if(ex->node_marker == AND)
            fprintf(fp, "and rcx, rdx\n");
        else
            fprintf(fp, "or rcx, rdx\n");
    }

    else if (ex->node_marker ==  PLUS    || (ex->node_marker ==  MINUS && ex->child->sibling != NULL)   || ex->node_marker ==  DIV     || ex->node_marker ==  MUL)
    {
        evaluate_expr(ex->child, id_st, fp);
        
        fprintf(fp, "\tpush rcx\n");
        fprintf(fp, "\tpush rcx\n");
        evaluate_expr(ex->child->sibling, id_st, fp);
        fprintf(fp, "\tpop rdx\n");
        fprintf(fp, "\tpop rdx\n");

        if(ex->node_marker == PLUS)
        {
            fprintf(fp, "\tadd rdx, rcx\n");
            fprintf(fp, "\tmov rcx, rdx\n");
            return;
        }
        else if(ex->node_marker == MINUS)
        {
            fprintf(fp, "\tsub rdx, rcx\n");
            fprintf(fp, "\tmov rcx, rdx\n");
            return;
        }
        else if(ex->node_marker == MUL)
        {
            fprintf(fp, "\timul rdx, rcx\n");
            fprintf(fp, "\tmov rcx, rdx\n");
            return;
        }

        else
        {
            // store dividend in eax, divisor in ebx --> quotient in eax, remainedr in edx
            fprintf(fp, "\tmov eax, edx\n");
            fprintf(fp, "\tmov ebx, ecx\n"); 
            fprintf(fp, "\txor edx, edx\n");    
            fprintf(fp, "\tdiv ebx\n");
            fprintf(fp, "\txor rcx, rcx\n"); 
            fprintf(fp, "\tmov ecx, eax\n");
            return;
        }
    
    }

    else if (ex->node_marker == MINUS && ex->child->sibling == NULL)
    {
        evaluate_expr(ex->child, id_st, fp);
        fprintf(fp, "\timul rcx, -1\n");
        return;
    }

    if (ex->node_marker == var)
    {
        if (ex->child->sibling == NULL)     // not an array element
            evaluate_expr(ex->child, id_st, fp);
        else                                // array element
        {
            // first do a non-recursive lookup
            ID_TABLE_ENTRY *i = st_lookup(ex->child->tree_node->lexeme, id_st);
            int line = ex->child->sibling->tree_node->line;
            int base_offset, start_offset, end_offset, index, index_offset;

            PARAMS *p = NULL;

            // calculating offsets of arrays
            if (i == NULL)      // then check for parameters
            {
                p = param_lookup(id_st->primogenitor->in_params ,ex->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,ex->child->tree_node->lexeme);
                
                base_offset = p->offset - 26;
                start_offset = p->datatype->arrtype->begin_offset - 26;
                end_offset = p->datatype->arrtype->end_offset - 26;
            }

            else
            {
                base_offset = i->offset;
                start_offset = i->datatype->arrtype->begin_offset;
                end_offset = i->datatype->arrtype->end_offset;
            }

            // A[2]
            if(ex->child->sibling->node_marker != ID)
            {
                index = atoi(ex->child->sibling->tree_node->lexeme);
                fprintf(fp, "\tpush rcx\n\tpush rcx\n");
                bound_check(fp, start_offset, end_offset, index, line);
                fprintf(fp, "\tpop rcx\n\tpop rcx\n");
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov rax, [rbp - %d]\n", base_offset * 8);
                fprintf(fp, "\tmov rdx, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\txor rbx, rbx\n");
                fprintf(fp, "\tmov ebx, %d\n", index);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\tmov ecx, [rax + rbx * 8]\n");

                return;
            }
            
             // A[k]

            else
            {
                ID_TABLE_ENTRY* index_entry = st_lookup(ex->child->sibling->tree_node->lexeme, id_st);
                    
                if(index_entry != NULL)
                {
                    index_offset = index_entry->offset;
                }
                else
                {
                    PARAMS* p = param_lookup(id_st->primogenitor->in_params ,ex->child->sibling->tree_node->lexeme);
                    if (p == NULL)
                        p = param_lookup(id_st->primogenitor->out_params ,ex->child->sibling->tree_node->lexeme);
                    
                    index_offset = p->offset - 26;
                }
                
                bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov eax, [rbp - %d]\n", base_offset * 8);
                fprintf(fp, "\tmov edx, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov ebx, [rbp - %d]\n", index_offset * 8);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\tmov ecx, [rax + rbx * 8]\n");
                return;
            }   
                
        }
    }
    
    return;
}

// trav a single function and generate the ASM code
void generate_the_universe(astNode *n, ID_SYMBOL_TABLE *id_st, FILE* fp)
{
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
            
            ID_TABLE_ENTRY* id_entry = st_lookup(temp->tree_node->lexeme, id_st);

            if(id_entry->datatype->simple == ARRAY)
            {
                int offset = id_entry->offset;

                //storing base address of this array: part of array_buffer
                fprintf(fp, "\txor r14, r14\n");
                fprintf(fp, "\tmov r14d, [array_available_addr]\n");
                fprintf(fp, "\tlea rax, [array_buffer + r14 * 8]\n");
                fprintf(fp, "\tmov [rbp - %d], rax\n\n", offset * 8);

                // if static array
                if (id_entry->datatype->arrtype->is_dynamic == false)
                {
                    int start = id_entry->datatype->arrtype->begin;
                    int end = id_entry->datatype->arrtype->end;

                    //increment array_available_addr by the used memory

                    // calculate array size

                    int array_size = end - start + 1;
                    fprintf(fp, "mov r14d, r14d\n");
                    fprintf(fp, "\tmov r14d, [array_available_addr]\n");
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

                    astNode* node = n->child;
                    while(node->node_marker != ARRAY)
                    {
                        node = node->sibling;
                    }

                    // now go to 
                    node = node->child->child;
                    astNode* rchild = node->sibling;
                    int start_offset = id_entry->datatype->arrtype->begin_offset;
                    int end_offset = id_entry->datatype->arrtype->end_offset;

                    if(node->node_marker == ID)
                    {
                        ID_TABLE_ENTRY* index = st_lookup(node->tree_node->lexeme, id_st);
                        int offset = index->offset;

                        // load start index value from offset
                        fprintf(fp, "\txor rax, rax\n");
                        fprintf(fp, "\tmov eax, [rbp - %d]\n", offset * 8);
                        fprintf(fp, "\tmov [rbp - %d], rax\n", start_offset * 8);
                    }

                    else
                    {
                        int start = atoi(node->tree_node->lexeme);
                        fprintf(fp, "mov r13, %d\n", start);
                        fprintf(fp, "mov [rbp - %d], r13\n", start_offset * 8);
                    }
                    if(rchild->node_marker == ID)
                    {
                        ID_TABLE_ENTRY* index = st_lookup(rchild->tree_node->lexeme, id_st);
                        int offset = index->offset;

                        // load end index value from offset
                        fprintf(fp, "\txor rax, rax\n");
                        fprintf(fp, "\tmov eax, [rbp - %d]\n", offset * 8);
                        fprintf(fp, "\tmov [rbp - %d], rax\n", end_offset * 8);
                    }

                    else
                    {
                        int end = atoi(rchild->tree_node->lexeme);
                        fprintf(fp, "mov r13, %d\n", end);
                        fprintf(fp, "mov [rbp - %d], r13\n", end_offset * 8);
                    }

                    char* error_lablel = generate_label();
                    char* exit_label = generate_label();
                    fprintf(fp, "; incrementing array_available address by array size\n\n"); 
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [array_available_addr]\n");
                    fprintf(fp, "\txor rax, rax\n");
                    fprintf(fp, "\txor rcx, rcx\n");
                    fprintf(fp, "\tmov eax, [rbp - %d]\n", start_offset * 8);
                    fprintf(fp, "\tmov ecx, [rbp - %d]\n", end_offset * 8);
                    fprintf(fp, "\tcmp eax, ecx\n");
                    fprintf(fp, "\tjg %s\n", error_lablel);
                    fprintf(fp, "\tsub ecx, eax\n");
                    fprintf(fp, "\tinc ecx\n");
                    fprintf(fp, "\tadd r14d, ecx\n");
                    fprintf(fp, "\tmov [array_available_addr], r14\n\n");
                    fprintf(fp, "\tjmp %s\n", exit_label);

                    fprintf(fp, "\t%s:\n", error_lablel);
                    fprintf(fp, "\tlea rdi, [errorMsg1]\n");
                    fprintf(fp, "\tmov rsi, rcx\n");
                    fprintf(fp, "\tmov rdx,  rax\n");
                    fprintf(fp, "\txor rcx, rcx\n");
                    fprintf(fp, "\tmov rcx, %d\n", node->tree_node->line);
                    fprintf(fp, "\txor rax, rax\n");
                    fprintf(fp, "\tcall printf\n");
                    fprintf(fp, "\tjmp main_end\n");
                    fprintf(fp, "%s:\n", exit_label);
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
       
       
        astNode *lhs = n->child;
        astNode *rhs = n->child->sibling;
       if (lhs->node_marker == ARRAY || (lhs->node_marker == var && lhs->child->sibling != NULL))
        {
            // first do a non-recursive lookup
            ID_TABLE_ENTRY *i = st_lookup(lhs->child->tree_node->lexeme, id_st);
            int line = lhs->child->sibling->tree_node->line;
            int base_offset, start_offset, end_offset, index, index_offset;

            PARAMS *p = NULL;

            // calculating offsets of arrays
            if (i == NULL)      // then check for parameters
            {
                p = param_lookup(id_st->primogenitor->in_params ,lhs->child->tree_node->lexeme);
                if (p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params ,lhs->child->tree_node->lexeme);
                
                base_offset = p->offset - 26;
                start_offset = p->datatype->arrtype->begin_offset - 26;
                end_offset = p->datatype->arrtype->end_offset - 26;
            }

            else
            {
                base_offset = i->offset;
                start_offset = i->datatype->arrtype->begin_offset;
                end_offset = i->datatype->arrtype->end_offset;
            }

            // A[2]
            if(lhs->child->sibling->node_marker != ID)
            {
                index = atoi(lhs->child->sibling->tree_node->lexeme);
                fprintf(fp, "\tpush rcx\n\tpush rcx\n");
                bound_check(fp, start_offset, end_offset, index, line);
                fprintf(fp, "\tpop rcx\n\tpop rcx\n");
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov rax, [rbp - %d]\n", base_offset * 8);
                fprintf(fp, "\tmov rdx, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\txor rbx, rbx\n");
                fprintf(fp, "\tmov ebx, %d\n", index);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\tmov [rax + rbx * 8], rcx \n");

                return;
            }
            
             // A[k]

            else
            {
                ID_TABLE_ENTRY* index_entry = st_lookup(lhs->child->sibling->tree_node->lexeme, id_st);
                    
                if(index_entry != NULL)
                {
                    index_offset = index_entry->offset;
                }
                else
                {
                    PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
                    if (p == NULL)
                        p = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
                    
                    index_offset = p->offset - 26;
                }
                
                bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                fprintf(fp, "\txor rax, rax\n");
                fprintf(fp, "\txor rdx, rdx\n");
                fprintf(fp, "\tmov eax, [rbp - %d]\n", base_offset * 8);
                fprintf(fp, "\tmov edx, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov ebx, [rbp - %d]\n", index_offset * 8);
                fprintf(fp, "\tsub ebx, edx\n");
                fprintf(fp, "\tmov [rax + rbx * 8], rcx\n");
                return;
            }   
                
        }
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->tree_node->lexeme, id_st);
        if (id_entry != NULL)
        {
            int offset = id_entry->offset;
            fprintf(fp, "\tmov [rbp - %d], rcx\n", offset * 8);
        }
        else
        {
            
            PARAMS* p = param_lookup(id_st->primogenitor->in_params ,lhs->tree_node->lexeme);
            if (p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,lhs->tree_node->lexeme);
            int offset = p->offset;
            fprintf(fp, "\tmov [rbp - %d + 208], rcx\n", offset * 8);
        }
        
        
    }
    if (is(n, "iterativeStmt") && is(n->child, "ID"))   // for lup
    {
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->tree_node->lexeme, id_st);
        int offset;

        if(id_entry == NULL)
        {
            PARAMS* p = param_lookup(id_st->primogenitor->in_params, n->child->tree_node->lexeme);
            if(p == NULL)   
                p = param_lookup(id_st->primogenitor->out_params, n->child->tree_node->lexeme);
            offset = p->offset - 26;
        }
        else        
            offset = id_entry->offset;
        astNode* range = n->child->sibling;
        int start = atoi(range->child->tree_node->value_if_number);
        int end = atoi(range->child->sibling->tree_node->value_if_number);

        // @satvik should handle this
        if (end < start)
        {
            printf("ERROR: end index %d less than start index %d in for loop at line %d\n", end, start, n->tree_node->line);
            exit(1);
        }

        char* for_label = generate_label();
        fprintf(fp, "; for loop\n\n");
        fprintf(fp, "\tmov qword [rbp - %d], %d\n", offset * 8, start);
        fprintf(fp, "\tmov rcx, %d\n", start);
        fprintf(fp, "\tmov rax, %d\n", end);
        fprintf(fp, "%s:\n", for_label);
        fprintf(fp, "\tpush rcx\n\tpush rax\n");
        generate_the_universe(range->sibling->sibling, id_st->kid_st[id_st->visited], fp);
        id_st->visited++;

 
        fprintf(fp, "\tpop rax\n\t pop rcx\n");
        fprintf(fp, "\tinc qword [rbp - %d]\n", offset * 8);
        fprintf(fp, "\tinc rcx\n");
        fprintf(fp, "\tcmp rcx, rax\n");
        fprintf(fp, "\tjle %s\n", for_label);

    }
    if (is(n, "iterativeStmt") && (1 - is(n->child, "ID")))   // while lup
    {
       astNode* ex = n->child;
       char* while_label = generate_label();
       char* exit_label = generate_label();
       fprintf(fp, "\t%s:\n", while_label);
       evaluate_expr(ex, id_st, fp);
       fprintf(fp, "\tcmp rcx, 0\n");
       fprintf(fp, "\tje %s", exit_label);
       generate_the_universe(n->child->sibling->sibling, id_st->kid_st[id_st->visited], fp);
       id_st->visited++;
       fprintf(fp, "\tjmp %s\n", while_label);
       fprintf(fp, "\t%s:\n\n", exit_label);

    }
    if (is(n, "ioStmt") && n->child->node_marker == GET_VALUE)
    {

        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->child->tree_node->lexeme, id_st);

        if(id_entry != NULL)
        {
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

        else
        {
            PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->tree_node->lexeme);
            if (p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,n->child->child->tree_node->lexeme);

            if (p->datatype->simple != ARRAY)
            {
                fprintf(fp, "\t;Taking id\n\n");
                prompt_user(fp, p->datatype->simple); 
                int type = id_entry->datatype->simple;
                int offset = p->offset;
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

            else 
            {
                fprintf(fp, "\t;Taking array\n\n");
                int base_offset = p->offset * 8;
                int lower_offset = p->datatype->arrtype->begin_offset * 8;
                int upper_offset = p->datatype->arrtype->end_offset * 8;
                int type = p->datatype->arrtype->base_type;
                fprintf(fp, "; prompts user for input\n");
                fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
                fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
                fprintf(fp, "\tmov esi, r8d\n");
                fprintf(fp, "\tsub esi, ecx\n");
                fprintf(fp, "\tinc esi\n");
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
                fprintf(fp, "\txor rcx, rcx\n");
                fprintf(fp, "\txor r8, r8\n");
                fprintf(fp, "\tmov ecx, [rbp - %d]\n", lower_offset);
                fprintf(fp, "\tmov r8d, [rbp - %d]\n", upper_offset);
                fprintf(fp, "\tcall printf\n\n");

                char* array_input_label  = generate_label();
                fprintf(fp, "\t; stores the count\n\n");
                fprintf(fp, "\txor r12, r12\n");
                fprintf(fp, "\txor r13, r13\n");
                fprintf(fp, "\tmov r12d, [rbp - %d]\n", upper_offset);
                fprintf(fp, "\tmov r13d, [rbp - %d]\n", lower_offset);
                fprintf(fp, "\tsub r12d, r13d\n");
                fprintf(fp, "\tinc r12d\n");
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
                fprintf(fp, "\txor r14, r14\n");
                fprintf(fp, "\tmov r14d, [rbp - %d]\n", base_offset);
                fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
                fprintf(fp, "\tcall scanf\n\n");

                fprintf(fp, "\tinc r13d\n");
                fprintf(fp, "\tcmp r13d, r12d\n");
                fprintf(fp, "\tjne %s\n", array_input_label);
                // fprintf(fp, "pop rbp\n");
                fprintf(fp, "\n\n");
            }
            
        }
        

    }
    if (is(n, "ioStmt") && n->child->node_marker == printOpt)
    {
        
        // print constant
        if(n->child->child->child == NULL)
        {
            if(n->child->child->node_marker == NUM)
            {
                int num = atoi(n->child->child->tree_node->lexeme);
                fprintf(fp, "\tlea rdi, [intFormat_out]\n");
                fprintf(fp, "xor rsi, rsi\n");
                fprintf(fp, "\tmov esi, %d\n", num);
                fprintf(fp, "\tcall printf\n");

                fprintf(fp, "\tlea rdi, [new_line]\n");
                fprintf(fp, "\tcall printf\n\n");
            }
            else
            {
                if(n->child->child->node_marker == TRUE)
                {
                    fprintf(fp, "lea rsi, [true_label]\n");
                }
                else
                {
                    fprintf(fp, "lea rsi, [false_label]\n");
                }
                fprintf(fp, "\tlea rdi, [strFormat_out]\n");
                fprintf(fp, "\tcall printf\n");
                
            }
            
            return;
        }
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->child->child->tree_node->lexeme, id_st);
        
        if(id_entry != NULL)
        {
            if (id_entry->datatype->simple != ARRAY)
            {
                fprintf(fp, "\t;Printing ID\n\n");
                print_id(fp,  id_entry->datatype->simple, id_entry->offset);
            }
            else if(n->child->child->child->sibling == NULL)
            {
                fprintf(fp, "\t;Printing array\n\n");
                print_array(fp, id_entry->offset * 8, id_entry->datatype->arrtype->begin_offset * 8, id_entry->datatype->arrtype->end_offset * 8, id_entry->datatype->arrtype->base_type);
            }
            else
            {
                astNode* index = n->child->child->child->sibling;
                astNode* array_node = n->child->child->child;
                int index_offset;
                int base_offset = id_entry->offset;
                int start_offset = id_entry->datatype->arrtype->begin_offset;
                int end_offset = id_entry->datatype->arrtype->end_offset;
                int line = array_node->tree_node->line; 
                int type = id_entry->datatype->arrtype->base_type;
                if(index->node_marker == ID) // A[k]
                {
                    ID_TABLE_ENTRY* index_entry = st_lookup(index->tree_node->lexeme, id_st);
                    
                    if(index_entry != NULL)
                    {
                        index_offset = index_entry->offset;
                        bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                        print_array_id_dynamic(fp, type, base_offset, start_offset, index_offset);
                        return;
                    }
                    else
                    {
                        PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
                        if (p == NULL)
                            p = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
                        
                        index_offset = p->offset;
                        bound_check_dynamic(fp, start_offset, end_offset, index_offset, line);
                        print_array_id_dynamic(fp, type, base_offset, start_offset, index_offset);
                    }
                    
                    
                }
                else  // A[2]
                {
                    int index_value = atoi(index->tree_node->lexeme);
                    bound_check(fp, start_offset, end_offset, index_value, line);
                    print_array_id(fp, type, base_offset, start_offset, index_value);
                }
                
            }
            
        }

        else
        {
            PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->child->child->tree_node->lexeme);
            if (p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,n->child->child->child->tree_node->lexeme);
            if (p->datatype->simple != ARRAY)
            {
                fprintf(fp, "\t;Printing ID\n\n");
                int type = p->datatype->simple;
                int offset = p->offset;
                int temp = offset * 8;
                if(type == INTEGER)
                {
                    fprintf(fp, "\tmov rdi, intFormat_out\n");
                    fprintf(fp, "\txor rsi, rsi\n");
                    fprintf(fp, "\tmov esi, [rbp - %d + 208]\n", temp);
                    fprintf(fp, "\tcall printf\n\n");
                    fprintf(fp, "\tlea rdi, [new_line]\n");
                    fprintf(fp, "\tcall printf\n\n");
                }

                else if(type == REAL)
                {
                    fprintf(fp, "\tmov rdi, realFormat_out\n");
                    fprintf(fp, "\txor rsi, rsi\n");
                    fprintf(fp, "\tmov esi, [rbp - %d + 208]\n", temp);
                    fprintf(fp, "\tcall printf\n\n");
                    fprintf(fp, "\tlea rdi, [new_line]\n");
                    fprintf(fp, "\tcall printf\n\n");
                }

                else if(type == BOOLEAN)
                {
                    char* f_label = generate_label();
                    char* p_label = generate_label();
                    fprintf(fp, "\tlea rdi, [strFormat_in]\n");
                    fprintf(fp, "\tmov sil, [rbp - %d + 208]\n\n", temp);
                    fprintf(fp, "\tcmp sil, 0\n");
                    fprintf(fp, "\tjz %s\n", f_label);
                    fprintf(fp, "\tlea rsi, [true_label]\n");
                    fprintf(fp, "\tjmp %s\n\n", p_label);
                    fprintf(fp, "%s: \n", f_label);
                    fprintf(fp, "\tlea rsi, [false_label]\n\n");
                    fprintf(fp, "%s: \n", p_label);
                    fprintf(fp, "\tcall printf\n\n");
                    fprintf(fp, "\tlea rdi, [new_line]\n");
                    fprintf(fp, "\tcall printf\n");
                    fprintf(fp, "\n\n");
                }
            }
            else
            {
                fprintf(fp, "\t;Printing array\n\n");
                int base_offset = p->offset * 8;
                int lower_offset = p->datatype->arrtype->begin_offset * 8;
                int upper_offset = p->datatype->arrtype->end_offset * 8;
                int type = p->datatype->arrtype->base_type;

                fprintf(fp, "; printing array\n");
                fprintf(fp, "lea rdi, [arr_outMsg]\n");
                fprintf(fp, "call printf\n");

                char* array_output_label = generate_label();
                fprintf(fp, "; stores the count\n\n");
                fprintf(fp, "xor r12, r12\n");
                fprintf(fp, "xor r13, r13\n");
                fprintf(fp, "mov r12d, [rbp - %d + 208]\n", upper_offset);
                fprintf(fp, "mov r13d, [rbp - %d + 208]\n", lower_offset);
                fprintf(fp, "sub r12d, r13d\n");
                fprintf(fp, "inc r12d\n");
                fprintf(fp, "xor r13, r13\n\n");  
                fprintf(fp, "%s:\n", array_output_label);

                if(type == INTEGER)
                {
                    fprintf(fp, "\tlea rdi, [intFormat_out]\n");
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [rbp - %d + 208]\n", base_offset);
                    fprintf(fp, "\tmov rsi, [r14 + r13 * 8]\n");
                }

                else if(type == REAL)
                {
                    fprintf(fp, "lea rdi, [realFormat_out]\n");
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [rbp - %d + 208]\n", base_offset);
                    fprintf(fp, "\tlea rsi, [r14 + r13 * 8]\n");
                    
                }

                else if(type == BOOLEAN)
                {
                    char* f_label = generate_label();
                    char* p_label = generate_label();
                    fprintf(fp, "\tlea rdi, [strFormat_in]\n");
                    fprintf(fp, "\txor r14, r14\n");
                    fprintf(fp, "\tmov r14d, [rbp - %d + 208]\n", base_offset);
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
                fprintf(fp, "\tinc r13d\n");
                fprintf(fp, "\tcmp r13d, r12d\n");
                fprintf(fp, "\tjne %s\n", array_output_label);
                fprintf(fp, "\tlea rdi, [new_line]\n");
                fprintf(fp, "\tcall printf\n");

                // fprintf(fp, "pop rbp\n");
                fprintf(fp, "\n\n");
            }
        }
        
    }
    if (is(n, "conditionalStmt"))
    {
        ID_TABLE_ENTRY* id_entry = st_lookup(n->child->tree_node->lexeme, id_st);

        int offset;
        if(id_entry == NULL)
        {
            PARAMS* p = param_lookup(id_st->primogenitor->in_params ,n->child->tree_node->lexeme);
            if (p == NULL)
                p = param_lookup(id_st->primogenitor->out_params ,n->child->tree_node->lexeme);
            
            offset = p->offset - 26;
        }
        else
        {
            offset = id_entry->offset;
        }
        
        fprintf(fp, "\txor rax, rax\n");
        fprintf(fp, "\tmov eax, [rbp - %d]\n", offset * 8);
        
        if(id_entry->datatype->simple != BOOLEAN)
        {
            generate_the_universe(n->child->sibling->sibling, id_st->kid_st[id_st->visited], fp);
            id_st->visited++;
        }
        else
        {
            astNode* case_node = n->child->sibling->sibling->child;
            char* cases_exit = generate_label();
            char* case_exit = generate_label();

            if(case_node->child->node_marker == TRUE)
                fprintf(fp, "\tcmp rax, %d\n", 1);
            else
                fprintf(fp, "\tcmp rax, %d\n", 0);
            fprintf(fp, "\tjne %s\n", case_exit);
            fprintf(fp, "\tpush rax\n\tpush rax\n");
            generate_the_universe(case_node->child->sibling, id_st->kid_st[id_st->visited], fp);
            fprintf(fp, "\tpop rax\n\tpop rax\n");
            fprintf(fp, "\tjmp %s\n", cases_exit);
            fprintf(fp, "\t%s:\n", case_exit);

            fprintf(fp, "\tpush rax\n\tpush rax\n");
            generate_the_universe(case_node->sibling->child->sibling, id_st->kid_st[id_st->visited], fp);
            id_st->visited++;
            fprintf(fp, "\tpop rax\n\tpop rax\n");
            fprintf(fp, "\t%s:\n", cases_exit);   
        }
        


    }
    if (is(n, "caseStmts"))
    {
        char* cases_exit = generate_label();
        for (astNode *temp = n->child; temp; temp = temp->sibling)
        {
            int num = atoi(temp->child->tree_node->lexeme);
            char* case_exit = generate_label();
            fprintf(fp, "\tcmp rax, %d\n", num);
            fprintf(fp, "\tjne %s\n", case_exit);
            fprintf(fp, "\tpush rax\n\tpush rax\n");
            generate_the_universe(temp->child->sibling, id_st, fp);
            fprintf(fp, "\tpop rax\n\tpop rax\n");
            fprintf(fp, "\tjmp %s\n", cases_exit);
            fprintf(fp, "\t%s:\n", case_exit);
        }

        astNode* default_nt_node = n->sibling;
        generate_the_universe(default_nt_node->child, id_st, fp);
        fprintf(fp, "%s:\n", cases_exit);

    }
  
    if (is(n, "moduleReuseStmt") && n->child->node_marker == EPS)
    {
        char* func_name = n->child->sibling->tree_node->lexeme;

        astNode* id_list_node = n->child->sibling->sibling->child;
        int count = 0;
        int start_offset, end_offset;
        while(id_list_node->node_marker != EPS)
        {
            ID_TABLE_ENTRY* id_entry = st_lookup(id_list_node->tree_node->lexeme, id_st);
            int offset;
            TYPE* datatype;
            int start_offset, end_offset;
            if(id_entry == NULL)
            {
                PARAMS* p = param_lookup(id_st->primogenitor->in_params, id_list_node->tree_node->lexeme);
                if(p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params, id_list_node->tree_node->lexeme);
                offset = p->offset - 26;
                datatype = p->datatype;
                start_offset = p->datatype->arrtype->begin_offset - 26;
                end_offset = p->datatype->arrtype->end_offset - 26;
            }
            else
            {
                offset = id_entry->offset;
                datatype = id_entry->datatype;
                start_offset = id_entry->datatype->arrtype->begin_offset;
                end_offset = id_entry->datatype->arrtype->end_offset;

            }
            if(datatype->simple != ARRAY)
            {
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp,"mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }

            else if(datatype->simple == ARRAY)
            {
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", end_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }
        }
        fprintf(fp, "\tcall %s\n", func_name);
    }
    if (is(n, "moduleReuseStmt") && n->child->node_marker != EPS)
    {
       char* func_name = n->child->sibling->tree_node->lexeme;

        astNode* id_list_node = n->child->sibling->sibling->child;
        int count = 0;
        int start_offset, end_offset;
        while(id_list_node->node_marker != EPS)
        {
            ID_TABLE_ENTRY* id_entry = st_lookup(id_list_node->tree_node->lexeme, id_st);
            int offset;
            TYPE* datatype;
            int start_offset, end_offset;
            if(id_entry == NULL)
            {
                PARAMS* p = param_lookup(id_st->primogenitor->in_params, id_list_node->tree_node->lexeme);
                if(p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params, id_list_node->tree_node->lexeme);
                offset = p->offset - 26;
                datatype = p->datatype;
                start_offset = p->datatype->arrtype->begin_offset - 26;
                end_offset = p->datatype->arrtype->end_offset - 26;
            }
            else
            {
                offset = id_entry->offset;
                datatype = id_entry->datatype;
                start_offset = id_entry->datatype->arrtype->begin_offset;
                end_offset = id_entry->datatype->arrtype->end_offset;
            }
            if(datatype->simple != ARRAY)
            {
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }

            else if(datatype->simple == ARRAY)
            {
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", start_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                count++;
                fprintf(fp, "xor r15, r15\n");
                fprintf(fp, "mov r15d, [rbp - %d]\n", end_offset * 8);
                fprintf(fp, "\tmov %s, r15\n", registers_array[count]);
                id_list_node = id_list_node->sibling;
                count++;
            }
        }
        fprintf(fp, "\tcall %s\n", func_name);

        id_list_node = n->child->child;
        count = 0;
        while(id_list_node->node_marker != EPS)
        {
            ID_TABLE_ENTRY* id_entry = st_lookup(id_list_node->tree_node->lexeme, id_st);
            int offset;
            if(id_entry == NULL)
            {
                PARAMS* p = param_lookup(id_st->primogenitor->in_params, id_list_node->tree_node->lexeme);
                if(p == NULL)
                    p = param_lookup(id_st->primogenitor->out_params, id_list_node->tree_node->lexeme);
                offset = p->offset - 26;
            }
            else
                offset = id_entry->offset;
            fprintf(fp, "mov [rbp - %d], %s\n", offset * 8, registers_array[count]);
            id_list_node = id_list_node->sibling;
            count++;
        }

    }
    return;
}


// trav the ast and create ASM code 
void generate_the_multiverse(astNode *n, GST *st, FILE* fp)
{
    if (is(n,"program"))
    {
        for(astNode *temp = n->child; temp; temp = temp->sibling)
        {
            generate_the_multiverse(temp,st, fp);
        }
    }

    if (is(n, "moduleDeclarations"))
        ;
    if (is(n, "otherModules"))
    {
        astNode* module_node = n->child;

        while(module_node != NULL)
        {
            FUNC_TABLE_ENTRY* func_entry = global_st_lookup(module_node->child->tree_node->lexeme, st);
            char* func_label = generate_func_label(module_node->child->tree_node->lexeme);
            fprintf(fp, "%s\n\n", func_label);
            fprintf(fp, "\tpush rbp\n");
            fprintf(fp, "\tmov rbp, rsp\n");
            fprintf(fp, "\tpush rdi\n");
            fprintf(fp, "\tpush rsi\n");
            fprintf(fp, "\tpush rdx\n");
            fprintf(fp, "\tpush rcx\n");
            fprintf(fp, "\tpush r8\n");
            fprintf(fp, "\tpush r9\n");
            fprintf(fp, "\tpush r10\n");
            fprintf(fp, "\tpush r11\n");
            fprintf(fp, "\tpush r12\n");
            fprintf(fp, "\tpush r13\n");
            fprintf(fp, "\tpush r14\n");
            fprintf(fp, "\tpush r15\n");
            fprintf(fp, "\tsub rsp, 96\n");
            fprintf(fp, "\tpush rbp\n");
            fprintf(fp, "\tpush rbp\n");
            fprintf(fp, "\tmov rbp, rsp\n");
            fprintf(fp, "\tsub rsp, %d\n", (func_entry->activation_record_size) * 16);
            generate_the_universe(module_node->child->sibling->sibling->sibling, func_entry->local_id_table ,fp); 
            fprintf(fp, "\tmov rsp, rbp\n");
            fprintf(fp, "\tpop rbp\n");
            fprintf(fp, "\tpop rbp\n");
            fprintf(fp, "\tpop r15\n");
            fprintf(fp, "\tpop r14\n");
            fprintf(fp, "\tpop r13\n");
            fprintf(fp, "\tpop r12\n");
            fprintf(fp, "\tpop r11\n");
            fprintf(fp, "\tpop r10\n");
            fprintf(fp, "\tpop r9\n");
            fprintf(fp, "\tpop r8\n");
            fprintf(fp, "\tpop rcx\n");
            fprintf(fp, "\tpop rdx\n");
            fprintf(fp, "\tpop rsi\n");
            fprintf(fp, "\tpop rdi\n");
            fprintf(fp, "\tmov rsp, rbp\n");
            fprintf(fp, "\tpop rbp\n");
            fprintf(fp, "\tret\n"); 
            module_node = module_node->sibling; 
        }

    }

    if (is(n, "driverModule"))
    {
        FUNC_TABLE_ENTRY *f = global_st_lookup("driverModule", st);
        fprintf(fp, "main:\n\n");
        fprintf(fp, "push rbp\n");
        fprintf(fp, "mov rbp, rsp\n");
        fprintf(fp, "\tsub rsp, %d\n", (f->activation_record_size) * 16);
        generate_the_universe(n->child, f->local_id_table, fp);
    }
    if (is(n, "EPS"))
        return;         // bliss

    return;
}

/*
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
    if (test_fp == NULL || test_parse_fp == NULL)
    {
        printf("Error in opening files. Exitting.\n");
        exit(1);
    }
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
    gst_print(st);                                                   // instead of cool, beautiful print,
    //v_gst_print(st);                                                    // do boring print
    printf("Performing further semantic analysis\n\n");
    //semantic_analyser(ast_root, st);
    printf("No semantic errors found\n\n");

    if (hasSemanticError == true)
    {
        printf("Semantic errors detected. Code generation aborted. Exitting\n");
        exit(3);
    }
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
*/