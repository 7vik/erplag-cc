#include "assembler.h"

void generate_code(astNode* root, GST* symbol_table, FILE* fp)
{
    if (root == NULL)
        return;

    switch (root->node_marker)
    {
        case assignmentStmt:
            generate_code_assignmentStmt(root, symbol_table, fp);
            break;
        case printOpt:
            generate_code_printStmt(root, symbol_table, fp);
            break;
        case GET_VALUE:
            generate_code_inputStmt(root, symbol_table, fp);
            break;
        case iterativeStmt:
            generate_code_iterativeStmt(root, symbol_table, fp);
            break;
        case conditionalStmt:
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

void generate_code_assignmentStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    return;
}
void generate_code_printStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    return;
}
void generate_code_inputStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    return;
}
void generate_code_iterativeStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    return;
}
void generate_code_conditionalStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    return;
}

int main(int argc, char* argv[])          // driver
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

    printf("Printed Parse Tree in file '%s'.\n", argv[2]);
    // printf("Rule number of root: %d\n", tree->kids[0]->data->rule_number);
    astNode* ast_root = buildAST(tree);
    // printf("H1\n");
    print_ast_json(ast_root, "output_ast_tree.json");

    //EMPTY SYMBOL TABLE FOR NOW
    GST* symbol_table = create_global_st();

    printf("Starting code generation\n");
    FILE* code_fp = fopen(argv[3], "w");
    generate_code(ast_root, symbol_table, code_fp); 


    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
}
