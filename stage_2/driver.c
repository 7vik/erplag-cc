//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// gcc driver.c code_gen.c symbol_table.c ast.c parser.c lexer.c hash.c bool.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include <time.h>
#include <assert.h> 
#include <unistd.h>

#include "code_gen.h"

int main(int argc, char *argv[])
{
    if(argc != 3)                       // for wrong argc
    {
        printf("Invalid argument count. Expected 3 arguments as in '$ ./compiler testcase.txt code.asm'.\n");
        printf("\nPlease try again. Bye!\n");
        exit(2);
    }
    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;
	printf("LEVEL 4:\tSymbol Table/Type Checking/ Semantic Analysis/ Static,Dynamic Arrays in Type Checking/Code Generation Done.\n");

    while (1)                                                                               // loop forever
    {
        printf("Hi. Welcome to ERPLAG. Please choose 0-9 as:\n");
        printf("0 -> Exit\n");
		printf("1 : Lexer\n");
		printf("2 : Parser\n");
        printf("3 : AST\n");
        printf("4 : Memory\n");
        printf("5 : Symbol Table\n");
        printf("6 : Activation Record Size\n");
        printf("7 : Static and Dynamic Arrays\n");
        printf("8 : Error Reporting and Total Time\n");
        printf("9 : Code Generation\n");

		printf("\nEnter Option [0-9]:\t");
        int option = 0;
        scanf("%d", &option);

        if(option == 0)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }

        if(option == 1)                                                                 // LEXER
        { 
            FILE* test_fp = fopen(argv[1], "r");
            populate_ht(hash_table, KEYWORDS_FILE);
            int line_count = 1;
            TWIN_BUFFER *twin_buff = (TWIN_BUFFER *) malloc(sizeof(TWIN_BUFFER));
            init_buffer(test_fp, twin_buff);
            LEXEME *temp = get_token(test_fp, twin_buff, &line_count);
            while (string_to_enum(temp->token) != DOLLAR )
            {
                print_lexeme(temp);
                temp = get_token(test_fp, twin_buff, &line_count);
            }
            printf("\nLexing Finished. SUCCESS!\n\n");
            fclose(test_fp);
            free(twin_buff);
        }

        if(option == 2)                                                             // PARSER
        { 
            FILE* test_fp = fopen(argv[1], "r");
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
            printf("%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s%20s\n\n", "LEXEME", "LINE_NO", "VALUE (if num)", "TOKENAME",  "PARENT", "IS LEAF?", "NODE SYMBOL", "RULE_NUMBER");
            v_print_parse_tree(tree);
            fclose(test_fp);
            free(twin_buff);
            free(parse_table);
        }

        if(option == 3)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }

        if(option == 4)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }

        if(option == 5)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }

        if(option == 6)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }

        if(option == 7)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }

        if(option == 8)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }

        if(option == 9)
        { 
            printf("Exiting. Bye-Bye!\n");
            exit(0);
        }
    }
    return 0;
}

/*
        
        else if (option == 3)
        { 
            
        }
        else if(option == 4)
        { 
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
            start_time = clock();
            parse (grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
            end_time = clock();
            total_CPU_time  =  (double) (end_time - start_time);
            total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
            fprintf(test_parse_fp, "%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s\n\n", "LEXEME", "LINE_NO", "TOKENAME", "VALUE (if num)", "PARENT", "IS LEAF?", "NODE SYMBOL");
            print_parse_tree(tree, test_parse_fp);
            printf("Printed Parse Tree in file '%s'.\n", argv[2]);
            printf("CPU Time: %lf, CPU time(in seconds): %lf\n", total_CPU_time, total_CPU_time_in_seconds);
            fclose(test_fp);
            fclose(test_parse_fp);
            free(twin_buff);
            free(parse_table);
        }
        else
            printf("Please enter a number from [0-4].");
    }
    return 0;
}
*/

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
