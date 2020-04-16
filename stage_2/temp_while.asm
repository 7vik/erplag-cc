;<<<driver program>>>
;start
;	declare x:integer;
;	x:=3;
;   while(x<=10)
;	start
;		print(x);
;       x:=x+1;
;	end
;end

section .text
    global main
    extern printf
    ;extern scanf

section .data
    
    print_value: db "%d",10,0
    offset_x: dq 0


main:
    push rbp
    mov rbp, rsp

    ;#declarations = 0
    sub rsp, 16
    ;now, we declare x, #declarations = 1

    mov r12, 3 ; now, the expression on RHS needs to be evaluated

    ; accessing the value- ignore and use your code if working well
    mov rbx, qword[offset_x]
    inc rbx
    xor rdx, rdx
    mov rax, 8
    mul rbx
    mov r15, rbp
    sub r15, rax

    mov qword[r15], r12
    mov r13, 10

loop:
    cmp qword[r15], r13
    jg loop_end

    mov rdi, print_value
    mov rsi, [r15]
    call printf

    mov r12, qword[r15]
    add r12, 1
    mov qword[r15], r12

    jmp loop

loop_end:
    mov rsp, rbp
    pop rbp
    ret