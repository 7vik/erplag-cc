#ifndef _SEMANTIC_ANALYSER
#define _SEMANTIC_ANALYSER

#include "symbol_table.h"
#include "bool.h"

extern bool hasSemanticError; 

void semantic_analyser(astNode* root, GST* global_st);
void check_moduleDeclarations_semantic(astNode* root, GST* global_st);
void check_otherModules_semantic(astNode* root, GST* global_st);
void check_driverModule_semantic(astNode* root, GST* global_st);
void check_moduleDef_semantic(astNode* root, FUNC_TABLE_ENTRY* func_entry);
void check_module_semantic(astNode* root, GST* global_st);
void check_statements_semantic(astNode* root, ID_SYMBOL_TABLE* id_table);
void check_declareStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table);
void check_ioStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table);
void check_assignmentStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table);
void check_iterativeStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table);
void check_conditionalStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table);
void check_moduleReuseStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_table);
void check_caseStmts_semantic(astNode* root, ID_SYMBOL_TABLE* id_child_table, ID_TABLE_ENTRY* id_entry);
void check_caseStmt_semantic(astNode* root, ID_SYMBOL_TABLE* id_child_table, ID_TABLE_ENTRY* id_entry);
void check_default_nt_semantic(astNode* root, ID_SYMBOL_TABLE* id_child_table, ID_TABLE_ENTRY* id_entry);

#endif