    section     .data
arr_inMsg:    db        "Enter %d elements of %s type for array range %d to %d", 10, 0
lower_bound   dd        5
upper_bound   dd        10
type          db        "integer", 0
intFormat     db        "%d", 0
int2Format    db        "r12: %d r13: %d", 10, 0
arr_outMsg:   db        "Printing array: ", 10, 0

    section     .bss

array         resd        5


global main
extern printf
extern scanf

    section     .text
main:

; print prompt

push rbp

mov rcx, [lower_bound]
mov r8, [upper_bound]
mov rsi, r8
sub rsi, rcx
mov rdi, arr_inMsg
mov rdx, type
mov rcx, [lower_bound]
mov r8, [upper_bound]
call printf

; stores the count
mov r12, [upper_bound]
mov r13, [lower_bound]
sub r12, r13
xor r13, r13

array_input_loop:

lea rdi, [intFormat]
lea rsi, [array + r13]
call scanf


inc r13

; for debugging purposes
lea rdi, [int2Format]
mov rsi, r12
mov rdx, r13
call printf



cmp r13, r12
jne array_input_loop


;printing out the array

lea rdi, [array_output_loop]
call printf

mov rcx, [upper_bound]
mov rbx, [lower_bound]
sub rcx, rbx
xor rbx, rbx

array_output_loop:

lea rdi, [intFormat]
mov rsi, [array + rbx]
call printf

inc rbx
cmp rbx, rcx
jnz array_output_loop



pop rbp
mov rax, 0
ret

