;for input programs
;     nasm -felf64 temp_codegen.asm
;     gcc temp_codegen.o
;     gcc ./a.out

        section .data

int_inMsg:    db        "Enter an integer value" , 10, 0 ;10 for new line, 0 for null
real_inMsg:   db        "Enter a real value", 10, 0
bool_inMsg:   db        "Enter a boolean value", 10, 0
arr_inMsg:    db        "Enter %d elements for array range %d to %d", 10, 0
intFormat     db        "%d", 0


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

        mov rdi, intFormat
        mov rsi, var1
        call scanf

        mov rdi, intFormat
        mov rsi, [var1]
        call printf

        ; return
        pop rbp ;restore stack
        mov rax, 0 ;normal exit
        ret





