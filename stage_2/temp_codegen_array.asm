    section     .data
arr_inMsg:    db        "Enter %d elements of %s type for array range %d to %d", 10, 0
lower_bound   dd        5
upper_bound   dd        10
type_int      db        "integer", 0
type_real     db        "real", 0
type_bool     db        "boolean", 0    
intFormat_in  db        "%d", 0
intFormat_out db        "%d ", 0
realFormat_in db        "%lf", 10, 0
realFormat_out db       "%lf", 0
new_line       db       10, 0
;int2Format    db        "r12: %d r13: %d", 10, 0
arr_outMsg:   db        "Printing array: ", 0

    section     .bss

int_array         resd        100
real_array        resq        100
bool_array        resb        100


global main
extern printf
extern scanf

    section     .text
main:

; print prompt

push rbp

xor rcx, rcx
xor r8, r8
mov ecx, [lower_bound]
mov r8d, [upper_bound]
mov esi, r8d
sub esi, ecx
mov rdi, arr_inMsg
mov rdx, type
mov ecx, [lower_bound]
mov r8d, [upper_bound]
call printf

; stores the count
xor r12, r12
xor r13, r13
mov r12d, [upper_bound]
mov r13d, [lower_bound]
sub r12d, r13d

;mov r12, 5
xor r13, r13

array_input_loop:

lea rdi, [intFormat_in]
lea rsi, [array + r13d * 4] ;really important to scale it by sizeof(array element)
call scanf



; for debugging purposes
;lea rdi, [int2Format]
;mov rsi, r12
;mov rdx, r13
;call printf



inc r13d
cmp r13d, r12d
jne array_input_loop


;printing out the array

lea rdi, arr_outMsg
call printf

mov r12d, [upper_bound]
mov r13d, [lower_bound]
sub r12d, r13d
xor r13d, r13d

array_output_loop:

lea rdi, [intFormat_out]
mov rsi, [array + r13d * 4]
call printf

inc r13d
cmp r13d, r12d
jnz array_output_loop

lea rdi, new_line
call printf


pop rbp
mov rax, 0
ret

