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
	sub rsp, 208
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 32], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 6
mov [rbp - 40], r13
mov r13, 10
mov [rbp - 48], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 56], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 6
mov [rbp - 64], r13
mov r13, 10
mov [rbp - 72], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 80], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 6
mov [rbp - 88], r13
mov r13, 10
mov [rbp - 96], r13

	;Taking array

; prompts user for input
	mov ecx, [rbp - 40]
	mov r8d, [rbp - 48]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 40]
	mov r8d, [rbp - 48]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 48]
	mov r13d, [rbp - 40]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label0:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 32]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label0


	;Taking array

; prompts user for input
	mov ecx, [rbp - 64]
	mov r8d, [rbp - 72]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 64]
	mov r8d, [rbp - 72]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 72]
	mov r13d, [rbp - 64]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label1:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 56]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label1


	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 96]
mov r13d, [rbp - 88]
sub r12d, r13d
inc r12d
xor r13, r13

label2:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 80]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label2
	lea rdi, [new_line]
	call printf


main_end:
mov rsp, rbp
pop rbp
mov rax, 0
ret
