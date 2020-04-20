section .data

int_inMsg    db        "Input: Enter an integer value" , 10, 0
real_inMsg   db        "Input: Enter a real value", 10, 0
bool_inMsg   db        "Input: Enter a boolean value", 10, 0
arr_inMsg    db        "Input: Enter %d elements of %s type for array range %d to %d", 10, 0
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

array_parameter_demo:

	push rbp
	mov rbp, rsp
	push rdi
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	sub rsp, 96
	push rbp
	push rbp
	mov rbp, rsp
	sub rsp, 240
	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 24 + 208]
mov r13d, [rbp - 16 + 208]
sub r12d, r13d
inc r12d
xor r13, r13

label0:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 8 + 208]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label0
	lea rdi, [new_line]
	call printf


	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 48 + 208]
mov r13d, [rbp - 40 + 208]
sub r12d, r13d
inc r12d
xor r13, r13

label1:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 32 + 208]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label1
	lea rdi, [new_line]
	call printf


	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 24]
	call scanf
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 32]
	call scanf
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 40], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 10
mov [rbp - 48], r13
mov r13, 14
mov [rbp - 56], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 64], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 10
mov [rbp - 72], r13
mov r13, 14
mov [rbp - 80], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 88], rax

	xor rax, rax
	mov eax, [rbp - 24]
	mov [rbp - 96], rax
	xor rax, rax
	mov eax, [rbp - 32]
	mov [rbp - 104], rax
; incrementing array_available address by array size

	xor r14, r14
	mov r14d, [array_available_addr]
	xor rax, rax
	xor rcx, rcx
	mov eax, [rbp - 96]
	mov ecx, [rbp - 104]
	cmp eax, ecx
	jg label2
	sub ecx, eax
	inc ecx
	add r14d, ecx
	mov [array_available_addr], r14

	jmp label3
	label2:
	lea rdi, [errorMsg1]
	mov rsi, rcx
	mov rdx,  rax
	xor rcx, rcx
	mov rcx, 19
	xor rax, rax
	call printf
	jmp main_end
label3:
	;Taking array

; prompts user for input
	mov ecx, [rbp - 48]
	mov r8d, [rbp - 56]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 48]
	mov r8d, [rbp - 56]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 56]
	mov