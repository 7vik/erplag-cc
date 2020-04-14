#include<stdio.h>
#include "symbol_table.h"

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
    fprintf(fp, "realFormat_in db        \"%%E\", 0\n");
    fprintf(fp, "realFormat_out db       \"%%E\", 0\n");
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
    fprintf(fp, "real_array:        resd        100\n");
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
<<<<<<< HEAD
=======
    fprintf(fp, "inc r12d\n");
    fprintf(fp, ";mov r12, 5\n");
>>>>>>> a88f1bdce93ddcb991e8f824856ed87f55aa322c
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
        fprintf(fp, "lea rsi, [real_array + r13d * 4]\n");
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
<<<<<<< HEAD
=======
    fprintf(fp, "inc r12d\n");
    fprintf(fp, ";mov r12, 5\n");
>>>>>>> a88f1bdce93ddcb991e8f824856ed87f55aa322c
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
        fprintf(fp, "mov rsi, [real_array + r13d * 4]\n");
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


int main(void)
{
    FILE* fp = fopen("temp_input_codegen.asm", "w");

    print_data_section(fp);

    // for one double var
    vars.num_double_vars++;
    print_bss_section(fp, vars);
    print_externs(fp);

    fprintf(fp, "main:\n\n");

    // ask_for_int(fp);
    // take_int_input(fp, 1);
    // print_int_output(fp, 1);
  
    ask_for_array(fp, 1, 2, REAL);
    print_array(fp, 1, 2, REAL);
    print_return(fp);

    fclose(fp);
    
}

