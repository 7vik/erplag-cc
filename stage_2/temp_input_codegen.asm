section .data

int_inMsg:    db        "Enter an integer value" , 10, 0
real_inMsg:   db        "Enter a real value", 10, 0
bool_inMsg:   db        "Enter a boolean value", 10, 0
arr_inMsg:    db        "Enter %d elements for array range %d to %d", 10, 0
intFormat     db        "%d", 0



section .bss

vard1:   resd    1


global main
extern printf
extern scanf
extern puts
extern exit

section  .text

main:

push rbp
mov rdi, int_inMsg
call printf
pop rbp

push rbp
mov rdi, intFormat
mov rsi, vard1
call scanf
pop rbp

push rbp
mov rdi, intFormat
mov rsi, [vard1]
call printf
pop rbp

mov rax, 0
ret
