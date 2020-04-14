#ifndef __ASSEMBLER
#define __ASSEMBLER

#include "symbol_table.h"

void generate_code_assignmentStmt(astNode* root, GST *symbol_table, FILE* fp);
void generate_code_printStmt(astNode* root, GST* symbol_table, FILE* fp);
void generate_code_inputStmt(astNode* root, ID_SYMBOL_TABLE *symbol_table, FILE* fp);
void generate_code_iterativeStmt(astNode* root, GST* symbol_table, FILE* fp);
void generate_code_conditionalStmt(astNode* root, GST* symbol_table, FILE* fp);

#endif