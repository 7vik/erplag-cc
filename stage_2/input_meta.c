#include<stdio.h>

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

    fprintf(fp, "int_inMsg:    db        \"Enter an integer value\" , 10, 0\n"); 
    fprintf(fp, "real_inMsg:   db        \"Enter a real value\", 10, 0\n");
    fprintf(fp, "bool_inMsg:   db        \"Enter a boolean value\", 10, 0\n");
    fprintf(fp, "arr_inMsg:    db        \"Enter %%d elements for array range %%d to %%d\", 10, 0\n");
    fprintf(fp, "intFormat     db        \"%%d\", 0\n");

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
        fprintf(fp, "%s", buff);

    }

    for(int i = 0; i < vars.num_double_vars; i++)
    {
        sprintf(buff, "vard%d:   resd    1\n", i + 1);
        fprintf(fp, "%s", buff);

    }

    for(int i = 0; i < vars.num_quad_words; i++)
    {
        sprintf(buff, "varq%d:   resq    1\n", i + 1);
        fprintf(fp, "%s", buff);

    }

    for(int i = 0; i < vars.num_word_vars; i++)
    {
        sprintf(buff, "varw%d:   resw    1\n", i + 1);
        fprintf(fp, "%s", buff);

    }

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

    ask_for_int(fp);
    take_int_input(fp, 1);
    print_int_output(fp, 1);
    print_return(fp);

    fclose(fp);
    
}

