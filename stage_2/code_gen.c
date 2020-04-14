// gcc code_gen.c symbol_table.c ast.c parser.c lexer.c hash.c bool.c

#include "assembler.h"

void pass()
{   // helper function to emulate "pass" from Python in C
    return;
}

// traverse a single function and generate the ASM code
void generate_the_universe(astNode *n, ID_SYMBOL_TABLE *id_st)
{
    if (is(n, "moduleDef"))
    {
        pass();
    }
    if (is(n, "statements"))
    {
        pass();
    }
    if (is(n, "declareStmt"))
    {
        pass();
    }
    if (is(n, "assignmentStmt"))
    {
        pass();
    }
    if (is(n, "ASSIGNOP"))
    {
       pass();
    }
    if (is(n, "iterativeStmt") && is(n->child, "ID"))   // for lup
    {
        pass();
    }
    if (is(n, "iterativeStmt") && (1 - is(n->child, "ID")))   // while lup
    {
       pass();
    }
    if (is(n, "ioStmt"))
    {
        pass();
    }
    if (is(n, "conditionalStmt"))
    {
        pass();
    }
    if (is(n, "caseStmts"))
    {
        pass();
    }
    if (is(n, "caseStmt"))
    {
        pass();
    }
    if (is(n, "moduleReuseStmt") && n->child->node_marker == EPS)
    {
        pass();
    }
    if (is(n, "moduleReuseStmt") && n->child->node_marker != EPS)
    {
       pass();
    }
    return;
}


// traverse the ast and create ASM code 
void generate_the_multiverse(astNode *n, GST *st)
{
    if (is(n,"program"))
    {
        pass();
    }
    if (is(n, "moduleDeclarations"))
    {
        pass();
    }
    if (is(n, "otherModules") && n->sibling != NULL)
    {
        pass();
    }
    if (is(n, "driverModule"))
    {
        pass();
    }
    if (is(n, "otherModules") && n->sibling == NULL)
    {
        pass();
    }
    if (is(n, "EPS"))
        return;         // bliss

    return;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Invalid argument count. Expected 3 arguments as in './executable testcase parse_outfile'.");
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
    generate_the_multiverse(ast_root, st);

    fclose(test_fp);
    fclose(test_parse_fp);
    free(twin_buff);
    free(parse_table);
    return 0;
}
