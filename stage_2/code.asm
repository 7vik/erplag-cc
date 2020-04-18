section .data

int_inMsg    db        "Enter an integer value" , 10, 0
real_inMsg   db        "Enter a real value", 10, 0
bool_inMsg   db        "Enter a boolean value", 10, 0
arr_inMsg    db        "Enter %d elements of %s type for array range %d to %d", 10, 0
intFormat     db        "%d", 0
type_int      db        "integer", 0
type_real     db        "real", 0
type_bool     db        "boolean", 0
intFormat_in  db        "%d", 0
intFormat_out db        "%d ", 0
realFormat_in db        "%lf", 10, 0
realFormat_out db       "%lf", 0
strFormat_in   db       "%s", 0
strFormat_out   db       "%s", 10, 0
true_label     db        "true ", 0
false_label     db        "false ", 0
arr_outMsg   db        "Printing array: ", 0
errorMsg1    db        "RUN TIME ERROR: End index %d of Array less than start index %d at line %d. Aborting", 10, 0
errorMsg2    db        "RUN TIME ERROR: Index %d out of bounds %d and %d at line %d. Aborting.", 10, 0
new_line       db       10, 0
var1         dd        3
var2         dd        6
array_available_addr   dq   0



		section .bss

vard1:   resd    1

int_array:         resd        100
real_array:        resq        100
bool_array:        resb        100
array_buffer:      resq        1000


global main
extern printf
extern scanf
extern puts
extern exit

section  .text

main:

push rbp
mov rbp, rsp
	sub rsp, 80
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 8], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 6
	mov [array_available_addr], r14

; loading array offsets
mov r13, 10
mov [rbp - 16], r13
mov r13, 15
mov [rbp - 24], r13

	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 32]
	call scanf
	;Taking array

; prompts user for input
	mov ecx, [rbp - 16]
	mov r8d, [rbp - 24]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 16]
	mov r8d, [rbp - 24]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 24]
	mov r13d, [rbp - 16]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label0:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 8]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label0


; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 16]
	mov r14d, [rbp - 24]
	cmp r13d, 11
	jg label1
	cmp r14d, 11
	jl label1
	jmp label2
	label1: 
	lea rdi, [errorMsg2]
	mov rsi, 11
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 7
	xor rax, rax
	call printf
	jmp main_end
label2:
	xor rsi, rsi
	mov r13, [rbp - 8]
	xor r14, r14
	xor r15, r15
	mov r14d, 11
	mov r15d, [rbp - 16]
	sub r14d, r15d
	mov esi, [r13 + r14 * 8]
	mov rdi, intFormat_out
	call printf

	lea rdi, [new_line]
	call printf

; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	xor r15, r15
	mov r13d, [rbp - 16]
	mov r14d, [rbp - 24]
	mov r15d, [rbp - 32]
	cmp r13d, r15d
	jg label3
	cmp r14d, r15d
	jl label3
	jmp label4
	label3: 
	lea rdi, [errorMsg2]
	mov rsi, r15
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 8
	xor rax, rax
	call printf
	jmp main_end
label4:
	xor rsi, rsi
	mov r13, [rbp - 8]
	xor r14, r14
	xor r15, r15
	mov r14d, [rbp - 32]
	mov r15d, [rbp - 16]
	sub r14d, r15d
	mov esi, [r13 + r14 * 8]
	mov rdi, intFormat_out
	call printf

	lea rdi, [new_line]
	call printf

	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 24]
mov r13d, [rbp - 16]
sub r12d, r13d
inc r12d
xor r13, r13

label5:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 8]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label5
	lea rdi, [new_line]
	call printf


lea rsi, [true_label]
	lea rdi, [strFormat_out]
	call printf
	lea rdi, [intFormat_out]
xor rsi, rsi
	mov esi, 2
	call printf
	lea rdi, [new_line]
	call printf

main_end:
mov rsp, rbp
pop rbp
mov rax, 0
ret
