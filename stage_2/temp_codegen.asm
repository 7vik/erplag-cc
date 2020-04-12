;     nasm -felf64 temp_codegen.asm
;     gcc temp_codegen.o
;     gcc ./a.out

        section .data

int_inMsg:    db        "Enter an integer value" , 10, 0 ;10 for new line
real_inMsg:   db        "Enter a real value", 10
bool_inMsg:   db        "Enter a boolean value", 10
arr_inMsg:    db        "Enter %d elements for array range %d to %d"


        section .bss
var1:         resd      1


global main
extern printf
extern scanf
extern puts
extern exit

section .text

main: 

        push rbp ;setup stack

        ;printf("Enter blah blah\n");

        mov rdi, int_inMsg ;first argument
        call printf

        ;take input from the user
        ;scanf("%d", &var1);

        

        ; return
        pop rbp ;restore stack
        mov rax, 0 ;normal exit
        ret





