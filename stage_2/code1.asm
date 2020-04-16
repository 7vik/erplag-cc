

global main
extern printf
extern scanf
extern puts
extern exit

section  .text

main:
nop

push rbp
mov rbp, rsp
mov rdi, 9
mov rsi, 8
call sec1

pop rbp
ret

sec1:

push rbp
mov rbp, rsp

pop rbp
ret