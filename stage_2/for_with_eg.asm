;<<<driver program>>>
;start
;   declare p, q, z:integer;
;   p:= 5;
;   q:= 7;
;   declare k:integer;
;   for(k in 10..15)
;   start
;       declare a, b:integer;
;       a:= 7;
;       get_value(b);
;       z:= a+k+b;
;       print(z);
;   end
;end

section .data
    input_stmt: db "Enter the value: ", 0
    output_stmt: db "Output: %d",10,0
    taking_input: db "%d",0
    offset_p: dq 0
    offset_q: dq 1
    offset_z: dq 2
    offset_k: dq 3
    offset_a: dq 4
    offset_b: dq 5

section .bss
    value_b: resq 1

section .text
    global main
    extern printf
    extern scanf
    extern puts

main:
    xor rax, rax
    xor rdx, rdx
    
    push rbp
    mov rbp, rsp

    ;okay, so declare statements coming up.... Need to update SP to indicate our call stack is expanding
    sub rsp, 8 ;for p. Also, update in the symbol table
    sub rsp, 8 ;for q
    sub rsp, 8 ;for z

    ;p:=5
    mov rbx, 5
    mov r12, [offset_p]
    inc r12
    mov rax, -1
    mul r12
    mov r12, rax
    mov qword[rbp + r12*8], rbx

    ;q:=7. Notice how well we're able to generalize this. Hope we are able to generalize for expressions :)
    mov rbx, 7
    mov r12, [offset_q]
    inc r12
    mov rax, -1
    mul r12
    mov r12, rax
    mov qword[rbp + r12*8], rbx
    
    sub rsp, 8 ;for k

    mov rbx, 10; this has to be the starting number
    mov r12, [offset_k]
    inc r12
    mov rax, -1
    mul r12
    mov r12, rax
    mov qword[rbp + r12*8], rbx

    mov r13, 15
    inc r13

L1:
    mov r12, [offset_k]
    inc r12
    mov rax, -1
    mul r12
    mov r12, rax
    cmp qword[rbp + r12*8], r13
    je L2

    sub rsp, 8 ;for a
    sub rsp, 8 ;for b

    ;a:=7
    mov r8, 7
    mov r14, [offset_a]
    inc r14
    mov rax, -1
    mul r14
    mov r14, rax
    mov [rbp + r14*8], r8

    mov rdi, input_stmt
    xor rax, rax
    call printf ;no need to perform alignment by chance, here

    mov rdi, taking_input
    mov rsi, value_b
    xor rax, rax
    call scanf  ;scanf("%d",&b);

    mov r8, qword[value_b]
    mov r14, [offset_b]
    inc r14
    mov rax, -1
    mul r14
    mov r14, rax
    mov [rbp + r14*8], r8


    xor rdx, rdx

    ; Hardcode alert- need to write asm for expressions separately

    mov r14, [offset_a]
    inc r14
    mov rax, -1
    mul r14
    mov r14, rax    
    mov rcx, qword[rbp + r14*8]

    mov r14, [offset_k]
    inc r14 
    mov rax, -1
    mul r14
    mov r14, rax
    add rcx, qword[rbp + r14*8]

    mov r14, [offset_b]
    inc r14 
    mov rax, -1
    mul r14
    mov r14, rax
    add rcx, qword[rbp + r14*8]

    mov r14, [offset_z]
    inc r14 
    mov rax, -1
    mul r14
    mov r14, rax
    mov qword[rbp + r14*8], rcx

    mov rdi, output_stmt
    mov r14, [offset_z]
    inc r14 
    mov rax, -1
    mul r14
    mov r14, rax
    mov rsi, qword[rbp + r14*8]
    xor rax, rax
    call printf

    xor rdx, rdx

    inc rbx
    mov r12, [offset_k]
    inc r12
    mov rax, -1
    mul r12
    mov r12, rax
    mov qword[rbp + r12*8], rbx

    jmp L1

L2: 
    mov rsp, rbp
    pop rbp
    
    ret