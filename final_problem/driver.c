//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// gcc driver.c semantic_analyser.c code_gen.c symbol_table.c ast.c parser.c lexer.c hash.c bool.c

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

        if(option == 3)                                 // AST Print
        { 
            FILE* test_fp = fopen(argv[1], "r");
            if (test_fp == NULL)
            {
                printf("Error in opening files. Exiting.\n");
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
            astNode* ast_root = buildAST(tree);
            printf("\tPrinting AST using Pre-order Traversal:\n\n");
            printf("%20s%10s%20s%20s\n\n",
                    "AST NODE MARKER",
                    "IS LEAF?",
                    "PARENT",
                    "SIBLING"
                    );
            v_print_ast_tree(ast_root);
            putchar('\n');
            fclose(test_fp);
            free(twin_buff);
            free(parse_table);
        }

        if(option == 4)                                 // Memory
        { 
            FILE* test_fp = fopen(argv[1], "r");
            if (test_fp == NULL)
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
            astNode* ast_root = buildAST(tree);
            printf("\nParse Tree Node Count:\t%d\n", num_parse_nodes);
            int m1 = num_parse_nodes * sizeof(TREE_NODE);
            printf("Allocated Memory:\t\t%d\n", m1);
            printf("AST Node Count:\t\t%d\n", num_ast_nodes);
            int m2 = num_ast_nodes * sizeof(astNode);
            printf("Allocated Memory:\t\t%d\n", m2);
            printf("Compression Percentage:\t\t%2f\n\n", ((m1 - m2) * 100.0 / m1));
        }

        if(option == 5)                               // Symbol Table printing
        { 
            FILE* test_fp = fopen(argv[1], "r");
            if (test_fp == NULL)
            {
                printf("Error in opening files. Exiting.\n");
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
            astNode* ast_root = buildAST(tree);
            GST *st = create_global_st();
            traverse_the_multiverse(ast_root, st);
            // gst_print(st);                                        // instead of cool, beautiful print,
            v_gst_print(st);                                    // do boring print
            putchar('\n');
            fclose(test_fp);
            free(twin_buff);
            free(parse_table);
        }

        if(option == 6)                                         // Activation Record Size
        { 
            FILE* test_fp = fopen(argv[1], "r");
            if (test_fp == NULL)
            {
                printf("Error in opening files. Exiting.\n");
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
            astNode* ast_root = buildAST(tree);
            GST *st = create_global_st();
            traverse_the_multiverse(ast_root, st);
            // gst_print(st);                                        // instead of cool, beautiful print,
            // v_gst_print(st);                                    // do boring print
            // putchar('\n');
            printf("\n\nPrinting Activation Record Memory:\n");
            v_activation_print(st);
            putchar('\n');
            putchar('\n');
            fclose(test_fp);
            free(twin_buff);
            free(parse_table);
        }

        if(option == 7)                                        // Static and Dynamic Arrays
        { 
            FILE* test_fp = fopen(argv[1], "r");
            if (test_fp == NULL)
            {
                printf("Error in opening files. Exiting.\n");
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
            astNode* ast_root = buildAST(tree); 
            printf("\n%20s%10s%10s\t[%5s, %5s]\t%10s\n\n",
                    "Module Name",
                    "Array Name",
                    "Static/Dyn",
                    "begin",
                    "end",
                    "Base Type"
                    );   
            array_the_multiverse(ast_root);
            putchar('\n');
            fclose(test_fp);
            free(twin_buff);
            free(parse_table);
        }

        if(option == 8)                                         // Errors
        { 
            FILE* test_fp = fopen(argv[1], "r");
            if (test_fp == NULL)
            {
                printf("Error in opening files. Exiting.\n");
                exit(1);
            }

            clock_t start_time, end_time;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();

            // do something

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
            astNode* ast_root = buildAST(tree);
            GST *st = create_global_st();
            traverse_the_multiverse(ast_root, st);
            semantic_analyser(ast_root, st);
            fclose(test_fp);
            free(twin_buff);
            free(parse_table);

            // really fast

            end_time = clock();    
            total_CPU_time  =  (double) (end_time - start_time);
            total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;

            printf("\nCPU time: %lf\nCPU time(in seconds): %lf\n\n", 
                        total_CPU_time, 
                        total_CPU_time_in_seconds
                        );
        }

        if(option == 9)                                        // Code Generation
        { 
            FILE* test_fp = fopen(argv[1], "r");
            if (test_fp == NULL)
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
            astNode* ast_root = buildAST(tree);
            // Test Symbol table
            GST *st = create_global_st();
            traverse_the_multiverse(ast_root, st);
            semantic_analyser(ast_root, st);
            st = create_global_st();
            traverse_the_multiverse(ast_root, st);
            // gst_print(st);
            // test code generation
            if (!hasSemanticError)
            {
                printf("\nStarting Code Generation\n");
                FILE* code_fp = fopen(argv[2], "w");
                initialise_file(code_fp);
                generate_the_multiverse(ast_root, st, code_fp);
                print_return(code_fp);
                fclose(code_fp);
                
            }
            else
                printf("\n Errors Detected. Please rectify errors before Code Generation. Abort.\n\n");
            fclose(test_fp);
            free(twin_buff);
            free(parse_table);
        }

        else
            printf("Please choose an integer from 0-9.\n");
    }
    return 0;
}