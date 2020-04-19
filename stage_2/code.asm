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

compute_expr:

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
	sub rsp, 80
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
	lea rsi, [rbp - 16]
	call scanf
	xor rcx, rcx
	mov ecx, [rbp - 8 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16 + 208]
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 24]
	push rcx
	push rcx
	mov rcx, 2
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	mov rcx, 3
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	mov [rbp - 8], rcx
	xor rcx, rcx
	mov ecx, [rbp - 24 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 8 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16 + 208]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jle label0
	mov rcx, 0
jmp label1
label0:
	mov rcx, 1
label1:	pop rdx
	pop rdx
and rcx, rdx
	mov [rbp - 32], rcx
	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 104 + 208], rcx
	xor rcx, rcx
	mov ecx, [rbp - 32]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jle label2
	mov rcx, 0
jmp label3
label2:
	mov rcx, 1
label3:	pop rdx
	pop rdx
or rcx, rdx
	mov [rbp - 112 + 208], rcx
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 8 + 208]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 16 + 208]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	lea rdi, [strFormat_in]
	mov sil, [rbp - 24 + 208]

	cmp sil, 0
	jz label4
	lea rsi, [true_label]
	jmp label5

label4: 
	lea rsi, [false_label]

label5: 
	call printf

	lea rdi, [new_line]
	call printf


	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 24]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 8]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 16]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 104 + 208]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	lea rdi, [strFormat_in]
	mov sil, [rbp - 112 + 208]

	cmp sil, 0
	jz label6
	lea rsi, [true_label]
	jmp label7

label6: 
	lea rsi, [false_label]

label7: 
	call printf

	lea rdi, [new_line]
	call printf


	mov rsp, rbp
	pop rbp
	pop rbp
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret
main:

push rbp
mov rbp, rsp
	sub rsp, 96
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 8]
	call scanf
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 16]
	call scanf
	mov rcx, 0
	mov [rbp - 40], rcx
xor r15, r15
mov r15d, [rbp - 8]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 16]
	mov rsi, r15
xor r15, r15
mov r15d, [rbp - 40]
	mov rdx, r15
	call compute_expr
mov [rbp - 24], rdi
mov [rbp - 32], rsi
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 8]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 16]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 24]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	lea rdi, [strFormat_in]
	mov sil, [rbp - 32]

	cmp sil, 0
	jz label8
	lea rsi, [true_label]
	jmp label9

label8: 
	lea rsi, [false_label]

label9: 
	call printf

	lea rdi, [new_line]
	call printf


main_end:
mov rsp, rbp
pop rbp
mov rax, 0
ret
