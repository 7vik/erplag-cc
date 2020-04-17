;<<module compute_expr>>
;takes input[ a: integer, b:integer, c:boolean];
;returns [u:integer, v:boolean];
;start
;	declare d: integer;
;	declare m: boolean;
;   d:=1;
;   m:=false;
;	u:= 2;
;	v:= m;
;	print(a);
;	print(b);
;	print(d);
;	print(u);
;end
;
;<<<driver program>>>
;start
;	declare x, y, z:integer;
;   x:=5;
;   y:=7;
;	declare k, h:boolean;
;	h:= false;
;	[z, k]:= use module compute_expr with parameters x, y, h;				
;	print(x);
;	print(y);
;	print(z);
;end

section .data
    print_arg: db "%d",10,0
    ;offset_x: dq 1
    ;offset_y: dq 2
    ;offset_z: dq 3
    ;offset_k: dq 4
    ;offset_h: dq 5

    ;offset_d: dq 1
    ;offset_m: dq 2
    size1: dq 5
    size2: dq 2

section .text
    global main
    extern printf
    extern scanf

main:
    push rbp
    mov rbp, rsp

    ; because of size1, which is odd - not aligned
    sub rsp, 40 ; 40 = [size1] * 8
    ; correction for alignment
    sub rsp, 8
    ; reserving space for function call
    sub rsp, 48 ; rdi, rsi, rdx, rcx, r8, r9 will store input parameters

    ; assignment statement(s)
    mov qword[rbp - 8], 5
    mov qword[rbp - 16], 7
    mov qword[rbp - 40], 0

    ; and finally, a call to a function comes!
    mov rdi, qword[rbp - 8]
    mov rsi, qword[rbp - 16]
    mov rdx, qword[rbp - 40]
    ; done with i/p parameters - for others, simply put 0 - optional
    mov rcx, 0
    mov r8, 0
    mov r9, 0

    call compute_expr

    mov qword[rbp - 24], rdi ; z assigned u, the first o/p parameter
    mov qword[rbp - 32], rsi ; k assigned v, the second o/p parameter

    push rdi
    push rsi
    
    mov rdi, print_arg
    mov rsi, qword[rbp - 8] ; printing x
    call printf

    pop rsi
    pop rdi

    push rdi
    push rsi
    
    mov rdi, print_arg
    mov rsi, qword[rbp - 16] ; printing y
    call printf

    pop rsi
    pop rdi

    push rdi
    push rsi
    
    mov rdi, print_arg
    mov rsi, qword[rbp - 24] ; printing z
    call printf

    pop rsi
    pop rdi

    mov rsp, rbp
    pop rbp
    ret

compute_expr:
    push rbp
    mov rbp, rsp    ; notice how these two statements are always present irrespective of the function

    ; Save the states of the input parameters in the AR of callee
    push r9
    push r8
    push rcx
    push rdx
    push rsi
    push rdi

    ; to ensure the offsets entered are in sync with the entries of offsets in the corresponding ST
    push rbp
    push rbp
    mov rbp, rsp

    ; because of size2, which is even - no alignment needed
    sub rsp, 16 ; 16 = [size2] * 8
    ; reserving space for subsequent function calls which may occur from this function as well.
    sub rsp, 48 ; rdi, rsi, rdx, rcx, r8, r9 will store input parameters

    ; assignment statement(s)
    mov qword[rbp - 8], 1
    mov qword[rbp - 16], 0

    ; now, a value to be put into return formal parameters!
    mov rdi, 2 ; u is the first return formal parameter; put its value in rdi
    mov rsi, qword[rbp - 16]; v is the second return formal parameter; put its value in rsi

    push rdi
    push rsi
    ;push rdx
    ;push rcx
    ;push r8
    ;push r9

    ; NOTE: We may require rdx, rcx, r8, r9  to be pushed in some other scenario...
    ; As a thumb rule, you can even push all the 6 registers simultaneously.
    
    mov rdi, print_arg
    mov rsi, qword[rbp + 8 + 8] ; printing a: the first input parameter
    call printf

    pop rsi
    pop rdi

    push rdi
    push rsi
    
    mov rdi, print_arg
    mov rsi, qword[rbp + 8 + 16] ; printing b: the second input parameter
    call printf

    pop rsi
    pop rdi

    push rdi
    push rsi
    
    mov rdi, print_arg
    mov rsi, qword[rbp - 8] ; printing d: the first local variable - offset retrieved from ST
    call printf

    pop rsi
    pop rdi

    push rdi
    push rsi
    
    mov rdi, print_arg
    mov rsi, qword[rsp + 8] ; this is an output parameter
    call printf

    ; Note: You can also push rsi first and then rdi
    ; Advantage? Pushing in reverse order would make the retrieval of output parameters easier.
    ; Do not forget, then, to pop rdi first and then rsi

    pop rsi
    pop rdi

    ; Okay, we're done!
    mov rsp, rbp
    pop rbp
    pop rbp

    mov rsp, rbp
    pop rbp
    ret