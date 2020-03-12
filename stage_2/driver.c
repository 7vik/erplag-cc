//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include <time.h>
// #include "bool.h"lite
#include <assert.h> 
#include <unistd.h>

#include "parser.h"

int main(int argc, char* argv[])            // main for driver
{
    if(argc != 3)
    {
        printf("Invalid argument count. Expected 3 arguments as in './executable testcase parse_outfile'.");
        printf("\nAborting Execution!!\n");
        exit(2);
    }
    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;
    printf("\n\n****\tExecution details\t******\n\n");
    printf("====\t\tImplementation Details\t\t====\n");
	printf("1. First and Follow Set Calculation Automated.\n");
	printf("2. Both Lexical and Syntax Analysis Modules Implemented.\n");
	printf("3. Parse Tree Construction Completed.\n");
    printf("4. All testcases (t1-t6) working successfully.\n");
    while(1)
    {
		printf("\n\nPlease choose from following options:\n");
		printf("0 -> Exit\n");
		printf("1 : Remove Comments\n");
		printf("2 : Invoke Lexical Analysis\n");
		printf("3 : Parse and Print Parse Tree\n");
		printf("4 : Time for Lexical and Syntactic Analysis\n");
		printf("\nEnter Option [0-4]\t");
        int option = 0;
        scanf("%d", &option);
        if(option == 0)
        { 
            printf("Exiting. Bye bye.\n");
            exit(0);
        }
        else if (option == 1)
        {
            FILE* test_fp = fopen(argv[1], "r");
            remove_comments_driver(test_fp);
            printf("\n\nComments removed. SUCCESS.\n");
            fclose(test_fp);
        }
        else if (option == 2)
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
            printf("\n\n Lexing done. SUCCESS.\n");
            fclose(test_fp);
            free(twin_buff);
        }
        else if (option == 3)
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
            parse(grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
            fprintf(test_parse_fp, "%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s%20s\n\n", "LEXEME", "LINE_NO", "VALUE (if num)", "TOKENAME",  "PARENT", "IS LEAF?", "NODE SYMBOL", "RULE_NUMBER");
            print_parse_tree(tree, test_parse_fp);
            printf("Printed Parse Tree in file '%s'.\n", argv[2]);
            fclose(test_fp);
            fclose(test_parse_fp);
            free(twin_buff);
            free(parse_table);
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