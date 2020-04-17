#ifndef __CODEGEN
#define __CODEGEN

#include "semantic_analyser.h"

typedef struct vars
{
    int num_byte_vars;      // 1 byte
    int num_word_vars;      // 2 bytes
    int num_double_vars;    // 4 bytes
    int num_quad_words;      // 8 bytes
}VARS;



//void generate_code_assignmentStmt(astNode* root, GST *symbol_table, FILE* fp);
//void generate_code_printStmt(astNode* root, GST* symbol_table, FILE* fp);
//void generate_code_inputStmt(astNode* root, ID_SYMBOL_TABLE *symbol_table, FILE* fp);
//void generate_code_iterativeStmt(astNode* root, GST* symbol_table, FILE* fp);
//void generate_code_conditionalStmt(astNode* root, GST* symbol_table, FILE* fp);
void generate_the_universe(astNode *n, ID_SYMBOL_TABLE *id_st, FILE* fp);
void generate_the_multiverse(astNode *n, GST *st, FILE* fp);
void initialise_file(FILE* fp);
void print_return(FILE* fp);
void print_data_section(FILE* fp);
void print_bss_section(FILE* fp, VARS vars);
void print_externs(FILE* fp);
void print_array(FILE* fp, int base_offset, int lower_var_num, int upper_var_num, int type);
void ask_for_array(FILE* fp, int base_offset, int lower_var_num, int upper_var_num, int type);
void prompt_user(FILE* fp, int type);
void print_int_output(FILE* fp, int output_var_num);
void take_real_input(FILE* fp, int input_var_num);
void take_int_input(FILE* fp, int input_var_num);
char* generate_label(void);

#endif