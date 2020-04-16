;<<<driver program>>>
;start
;	declare x:integer;
;	get_value(x);
;	switch(x)
;	start
;		case 1: **print "Hello world!"**
;                break;
;		case 2: **print "Hi!"**
;                break;
;		case 3: **print "Bye!"**
;                break;
;        default:**print "Invalid!"**
;			     break;
;	end
;end

section .text
    global main
    extern printf
    extern scanf

section .data
    
    print_input: db "Enter the value: ",0
    get_input: db "%d",0
    print_1: db "Hello world!",10,0
    print_2: db "Hi!",10,0
    print_3: db "Bye!",10,0
    print_def: db "Invalid!",10,0
    offset_x: dq 0


main:
    push rbp
    mov rbp, rsp

    ;#declarations = 0
    sub rsp, 16
    ;now, we declare x, #declarations = 1

    mov rdi, print_input
    xor rax, rax
    call printf

    ; if your input is working fine, go with that implementation
    mov rbx, qword[offset_x]
    inc rbx
    xor rdx, rdx
    mov rax, 8
    mul rbx
    mov rsi, rbp
    sub rsi, rax
    xor rax, rax
    mov rdi, get_input
    call scanf

    ; accessing the value- again, ignore and use your code if working well
    mov rbx, qword[offset_x]
    inc rbx
    xor rdx, rdx
    mov rax, 8
    mul rbx
    mov rsi, rbp
    sub rsi, rax
 
    mov rbx, qword[rsi]
    mov rax, 1
    cmp rax, rbx
    je stmt1

    mov rbx, qword[rsi]
    mov rax, 2
    cmp rax, rbx
    je stmt2
 
    mov rbx, qword[rsi]
    mov rax, 3
    cmp rax, rbx
    je stmt3

    jmp stmt_def

stmt1:
    mov rdi, print_1
    xor rax, rax
    call printf
    jmp conclude

stmt2:
    mov rdi, print_2
    xor rax, rax
    call printf
    jmp conclude

stmt3:
    mov rdi, print_3
    xor rax, rax
    call printf
    jmp conclude

stmt_def:
    mov rdi, print_def
    xor rax, rax
    call printf

conclude:
    mov rsp, rbp
    pop rbp
    ret 