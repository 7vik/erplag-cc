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

var_demo_array:

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
	sub rsp, 432
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 16]
	call scanf
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 32], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 51
	mov [array_available_addr], r14

; loading array offsets
mov r13, 100
mov [rbp - 40], r13
mov r13, 150
mov [rbp - 48], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 56], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 19
	mov [array_available_addr], r14

; loading array offsets
mov r13, 2
mov [rbp - 64], r13
mov r13, 20
mov [rbp - 72], r13

	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - -184]
	mov r14d, [rbp - -176]
	cmp r13d, 5
	jg label0
	cmp r14d, 5
	jl label0
	jmp label1
	label0: 
	lea rdi, [errorMsg2]
	mov rsi, 5
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 25
	xor rax, rax
	call printf
	pop r14
	pop r13
	call exit
label1:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - -192]
	mov rdx, [rbp - -184]
	xor rbx, rbx
	mov ebx, 5
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	mov rcx, 3
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 8], rcx
xor r15, r15
mov r15d, [rbp - 8]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 16]
	mov rsi, r15
	call function2
	xor rcx, rcx
	mov ecx, [rbp - 16 + 208]
	mov [rbp - 56], rcx
	mov rcx, 1
	mov [rbp - 112 + 208], rcx
	xor rcx, rcx
	mov ecx, [rbp - 16 + 208]
	push rcx
	push rcx
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 56], rcx
	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	mov rcx, 20
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 24]
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 64]
	mov r14d, [rbp - 72]
	cmp r13d, 10
	jg label2
	cmp r14d, 10
	jl label2
	jmp label3
	label2: 
	lea rdi, [errorMsg2]
	mov rsi, 10
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 31
	xor rax, rax
	call printf
	pop r14
	pop r13
	call exit
label3:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 56]
	mov rdx, [rbp - 64]
	xor rbx, rbx
	mov ebx, 10
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 96], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 16
	mov [array_available_addr], r14

; loading array offsets
mov r13, 35
mov [rbp - 104], r13
mov r13, 50
mov [rbp - 112], r13

	label4:
	xor rcx, rcx
	mov ecx, [rbp - 112 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 8 + 208]
	push rcx
	push rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - -184]
	mov r14d, [rbp - -176]
	cmp r13d, 11
	jg label6
	cmp r14d, 11
	jl label6
	jmp label7
	label6: 
	lea rdi, [errorMsg2]
	mov rsi, 11
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 33
	xor rax, rax
	call printf
	pop r14
	pop r13
	call exit
label7:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - -192]
	mov rdx, [rbp - -184]
	xor rbx, rbx
	mov ebx, 11
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jle label8
	mov rcx, 0
jmp label9
label8:
	mov rcx, 1
label9:	pop rdx
	pop rdx
and rcx, rdx
	push rcx
	push rcx
	mov rcx, 0
	pop rdx
	pop rdx
or rcx, rdx
	cmp rcx, 0
	je label5	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 136], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 19
	mov [array_available_addr], r14

; loading array offsets
mov r13, 2
mov [rbp - 144], r13
mov r13, 20
mov [rbp - 152], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 160], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 16
	mov [array_available_addr], r14

; loading array offsets
mov r13, 35
mov [rbp - 168], r13
mov r13, 50
mov [rbp - 176], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 184], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 16
	mov [array_available_addr], r14

; loading array offsets
mov r13, 35
mov [rbp - 192], r13
mov r13, 50
mov [rbp - 200], r13

	xor rcx, rcx
	mov ecx, [rbp - 16 + 208]
	mov [rbp - 136], rcx
xor r15, r15
mov r15d, [rbp - 32]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 40]
	mov rsi, r15
xor r15, r15
mov r15d, [rbp - 48]
	mov rdx, r15
xor r15, r15
mov r15d, [rbp - 88]
	mov rcx, r15
xor r15, r15
mov r15d, [rbp - 120]
	mov r8, r15
xor r15, r15
mov r15d, [rbp - 160]
	mov r9, r15
xor r15, r15
mov r15d, [rbp - 168]
	mov r10, r15
xor r15, r15
mov r15d, [rbp - 176]
	mov r11, r15
xor r15, r15
mov r15d, [rbp - 128]
	mov r12, r15
	call function1
mov [rbp - 80], rdi
mov [rbp - 128], rsi
mov [rbp - -96], rdx
mov [rbp - 120], rcx
	xor rcx, rcx
	mov ecx, [rbp - 128]
	push rcx
	push rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - -184]
	mov r14d, [rbp - -176]
	cmp r13d, 25
	jg label10
	cmp r14d, 25
	jl label10
	jmp label11
	label10: 
	lea rdi, [errorMsg2]
	mov rsi, 25
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 40
	xor rax, rax
	call printf
	pop r14
	pop r13
	call exit
label11:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - -192]
	mov rdx, [rbp - -184]
	xor rbx, rbx
	mov ebx, 25
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 144]
	mov r14d, [rbp - 152]
	cmp r13d, 2
	jg label12
	cmp r14d, 2
	jl label12
	jmp label13
	label12: 
	lea rdi, [errorMsg2]
	mov rsi, 2
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 40
	xor rax, rax
	call printf
	pop r14
	pop r13
	call exit
label13:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 136]
	mov rdx, [rbp - 144]
	xor rbx, rbx
	mov ebx, 2
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 144]
	mov r14d, [rbp - 152]
	cmp r13d, 18
	jg label14
	cmp r14d, 18
	jl label14
	jmp label15
	label14: 
	lea rdi, [errorMsg2]
	mov rsi, 18
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 