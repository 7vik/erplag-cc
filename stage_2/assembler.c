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

void initialise_file(FILE* fp)
{
    fprintf(fp, "\t\tglobal _start\n");
    fprintf(fp, "\t\textern printf\n");
    fprintf(fp, "\t\textern puts\n");
    fprintf(fp, "\t\textern scanf\n");
    fprintf(fp, "section .data\n");

    //figure out what to put in data section

    fprintf(fp, "section .text\n");
    fprintf(fp, "_start:\n");

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
    if ((temp_node->child == var || temp_node->child == NUM || temp_node->child == RNUM)
                && (temp_node->child->sibling == var || temp_node->child->sibling == NUM || temp_node->child->sibling == RNUM))
    {
        char* s1, s2;
        if(temp_node->child == var)
            s1 = temp_node->child->child->tree_node->lexeme;
        else
            s1 = temp_node->child->tree_node->lexeme;
        
        if(temp_node->child->sibling == var)
            s2 = temp_node->child->sibling->child->tree_node->lexeme;
        else
            s2 = temp_node->child->sibling->tree_node->lexeme;

        if(temp_node->node_marker == MUL)
            fprintf(fp, "\t\tmul %s, %s\n", s1, s2);
        else if(temp_node->node_marker == PLUS)
            fprintf(fp, "\t\tadd %s, %s\n", s1, s2);
        else if(temp_node->node_marker == MINUS)
            fprintf(fp, "\t\tsub %s, %s\n", s1, s2);
        else
            fprintf(fp, "\t\teq %s, %s\n", s1, s2);
        
    }

    return;
}
void generate_code_printStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    assert(root->node_marker == printOpt);
    return;
}
void generate_code_inputStmt(astNode* root, GST* symbol_table, FILE* fp)
{
    assert(root->node_marker == GET_VALUE);

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
