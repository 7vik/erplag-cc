segment .data
strFormat: db "Result is %d with a remainder of %d", 10, 0

segment .bss

segment .text

global main

main:
push rbp
mov rbp, rsp
        xor rdx, rdx
        mov rax, 250
        mov rbx, 100     ; We need EDX for the DIV operation, so use EBX to store 100
        div rbx             ; Divide EAX (250) by EBX (100), and store the result in EDX:EAX

        ;push edx
        ;push eax
        lea rdi, [strFormat]
        mov rsi, rax
        extern printf
        call printf

mov rsp, rbp
pop rbp
mov rax, 0
ret