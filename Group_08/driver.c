//                  ,-.                         Group 08                                                    //
//          ,      ( {o\                        Satvik Golechha :: 2017A7PS0117P                           ///
//          {`"=,___) (`~                       Bharat Bhargava :: 2017A7PS0025P                          ////
//           \  ,_.-   )                        Ayush      Jain :: 2017A7PS0093P                         /////
//      ~^~^~^`- ~^ ~^ '~^~^~^~                                                                         //////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "parser.h"
#include "hash.h"
#include <assert.h> 
#include <unistd.h>
#include <time.h>

void remove_comments(FILE* f1, FILE* f2)
{

    int state = 0;
    char ch;

    while((ch = fgetc(f1)) != EOF)
    {
        if(state == 0)
        {
            if(ch == '*')
                state = 1;
            else
                fputc(ch, f2);    
        }

        else if(state == 1)
        {
            if(ch == '*')
                state = 2;
            else
            {
                state = 0;
                fputc('*', f2);
                fputc(ch, f2);
            }
        }

        else if(state == 2)
        {
            if(ch == '*')
                state = 3;
            else if(ch == '\n')
                fputc(ch, f2);
            else;    /* do nothing */
        }

        else if(state == 3)
        {
            if(ch == '*')
                state = 0;
            else if(ch == '\n')
            {
                state = 2;
                fputc(ch, f2);
            }
            else
                state = 2;
        }
        else;   /* do nothing */
    }
    fclose(f1);
    fclose(f2);
    return;
}

void remove_comments_driver(FILE* fp)
{
    FILE* fp2 = fopen("output.txt", "w");

    remove_comments(fp, fp2);

    system("cat output.txt; rm output.txt");
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Wrong input format. Expected ./stage1exe testcase.txt parsetreeOutFile.txt ");
        printf("\nAborting Execution!!\n");
        exit(-1);
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
    // print_parse_table(parse_table, grammar);
    STACK *stack = NULL;
    PARSE_TREE *tree;

    LEXEME *temp;

    clock_t start_time, end_time;

    double total_CPU_time, total_CPU_time_in_seconds;

    start_time = clock();

    parse(grammar, test_fp, parse_table, &tree, stack, twin_buff, &line_count);
    
    end_time = clock();

    total_CPU_time  =  (double) (end_time - start_time);

    total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;


    printf("\n\n********Execution details**********\n\n");
    printf("====Implementation Details====\n");
	printf("1. First and Follow set calculation has been automated\n");
	printf("2. Both lexical and syntax analysis modules implemented\n");
	printf("3. Parse tree construction completed\n");
    printf("4. All testcases correctly passing.\n");

	
    


    while(1)
    {
		printf("\n\nPlease choose from followinf options\n");
		printf("0 -> Exit\n");
		printf("1 : Remove comments\n");
		printf("2 : Invoke lexical analysis\n");
		printf("3 : Parse and Print Parse Tree\n");
		printf("4 : Time for lexical and syntactic analysis\n");
		printf("\nEnter option: ");

        int option = 0;

        scanf("%d", &option);


        switch (option)
        {
            case 0: 

                printf("Exiting. Bye bye\n");
                break;
            
            case 1:
                remove_comments_driver(test_fp);
                printf("\n\nComments removed successfully\n");
                break;

            case 2:
                
                while((temp = get_token(test_fp, twin_buff, &line_count)))
                {
                    if (strcmp(temp->token, "DOLLAR") == 0)
                        break;
                    print_lexeme(temp);
                }
                printf("\n\n Lexing done\n");
                break;

            case 3: 
                print_parse_tree(tree, test_parse_fp);
                printf("Printed parse tree in file %s\n", argv[2]);

            case 4: 
                printf("CPU time: %lf, CPU time(in seconds): %lf\n", total_CPU_time, total_CPU_time_in_seconds);
                break;

            default:
                printf("invalid input");

        }

    }
}