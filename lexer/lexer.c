#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

#define max_id_len 20

typedef struct lexeme_tuple_list
{
    // linked list of lexemes (tuple of (TOKEN, VALUE))
    char *token;
    char *value;
    struct lexeme_tuple_list *next;

} LEXEME;

void print_lexeme_list(LEXEME *lst)
{
    while(lst != NULL)
    {
        printf("%s: %s\n",lst->token, lst->value);
        lst = lst->next;
    }
    return;
}

// dfa 
LEXEME *lexer(FILE *src_file)
{
    // I/P: file pointer
    // O/P: linked list of lexemes

    LEXEME *head = NULL;

    char lookahead;
    char *buff = (char *) (malloc(sizeof(char) * (max_id_len + 1)));
    int char_count;
    LEXEME *current;

    while ((lookahead = fgetc(src_file)) != EOF)
    {
        char_count = 0;
        if (isalpha(lookahead))
        // dfa for identifier
        {
            buff[char_count] = lookahead;
            ++char_count;
            // flag reset when variable length reaches 20 and lexical error printed
            int len_flag = 1;
            while ((lookahead = fgetc(src_file)) != EOF && (isalnum(lookahead) || lookahead == '_'))
            {
                if (char_count >= 20)
                {
                    if (len_flag--)
                        printf("Lexical Error. VariableName length exceeds 20.\n");
                    continue;
                }
                buff[char_count] = lookahead;
                ++char_count;
            }
            buff[char_count] = '\0';
            char *detected_id = (char *) malloc(strlen(buff));
            strcpy(detected_id, buff);
            // LOOKUP using symbol table
            // *********************************** left *************************

            LEXEME *new_node = (LEXEME *) malloc(sizeof(LEXEME));
            if (!new_node)
            {
                printf("Malloc error\n");
                exit(1);
            }
            if (head == NULL)
            {
                current = new_node;
                head = new_node;
            }
            new_node->token = "ID";
            new_node->value = detected_id;
            new_node->next = NULL;
            current->next = new_node;
            current = new_node;
        }
        else if(isnumber(lookahead))
        // dfa for integer/real
        {
            
        }
    }

    return head;
}

int main()
{
    FILE *f = fopen("test.erplag", "r");
    print_lexeme_list(lexer(f));
    return 0;
}