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
new_line       db       10, 0
var1         dd        3
var2         dd        6
array_available_addr   dd   0



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
	sub rsp, 16
	sub rsp, 128
	mov r14, [array_available_addr]
	lea rax, [array_buffer + r14]
	mov [rbp - 24], rax

	mov r14, [array_available_addr]
	add r14, 3
	mov [array_available_addr], r14

; loading array offsets
mov r13, 12
mov [rbp - 0], r13
mov r13, 14
mov [rbp - 8], r13

	sub rsp, 16
	mov r14, [array_available_addr]
	lea rax, [array_buffer + r14]
	mov [rbp - 56], rax

	mov r14, [array_available_addr]
	lab0:
	add r14, 3
	mov [array_available_addr], r14

; loading array offsets
mov r13, 12
mov [rbp - 32], r13
mov r13, 14
mov [rbp - 40], r13

	;Taking array

; prompts user for input
	mov rcx, [rbp - 0]
	mov r8, [rbp - 8]
	mov rsi, r8
	sub rsi, rcx
	inc rsi
	mov rdi, arr_inMsg
mov rdx, type_int
	mov rcx, [rbp - 0]
	mov r8, [rbp - 8]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12, [rbp - 8]
	mov r13, [rbp - 0]
	sub r12, r13
	inc r12
	xor r13, r13

	label0:
lea rdi, [intFormat_in]
	mov r14, [rbp - 24]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13
	cmp r13, r12
	jne label0


	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12, [rbp - 8]
mov r13, [rbp - 0]
sub r12, r13
inc r12
xor r13, r13

label1:
	lea rdi, [intFormat_out]
	mov r14, [rbp - 24]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13
	cmp r13, r12
	jne label1
	lea rdi, [new_line]
	call printf


	;Taking array

; prompts user for input
	mov rcx, [rbp - 32]
	mov r8, [rbp - 40]
	mov rsi, r8
	sub rsi, rcx
	inc rsi
	mov rdi, arr_inMsg
mov rdx, type_int
	mov rcx, [rbp - 32]
	mov r8, [rbp - 40]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12, [rbp - 40]
	mov r13, [rbp - 32]
	sub r12, r13
	inc r12
	xor r13, r13

	label2:
lea rdi, [intFormat_in]
	mov r14, [rbp - 56]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13
	cmp r13, r12
	jne label2


	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12, [rbp - 8]
mov r13, [rbp - 0]
sub r12, r13
inc r12
xor r13, r13

label3:
	lea rdi, [intFormat_out]
	mov r14, [rbp - 24]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13
	cmp r13, r12
	jne label3
	lea rdi, [new_line]
	call printf


	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12, [rbp - 40]
mov r13, [rbp - 32]
sub r12, r13
inc r12
xor r13, r13

label4:
	lea rdi, [intFormat_out]
	mov r14, [rbp - 56]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13
	cmp r13, r12
	jne label4
	lea rdi, [new_line]
	call printf


mov rsp, rbp
pop rbp
mov rax, 0
ret
