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

arraySum:

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
	sub rsp, 64
	mov [rbp - 104 + 208], rcx
; for loop

	mov qword [rbp - 8], 1
	mov rcx, 1
	mov rax, 15
label0:
	push rcx
	push rax
	xor rcx, rcx
	mov ecx, [rbp - 8]
	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jle label1
	mov rcx, 0
jmp label2
label1:
	mov rcx, 1
label2:	mov [rbp - 24], rcx
	xor rax, rax
	mov eax, [rbp - 24]
	cmp rax, 1
	jne label4
	push rax
	push rax
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

label5:
lea rdi, [realFormat_out]
	xor r14, r14
	mov r14d, [rbp - 8 + 208]
	lea rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label5
	lea rdi, [new_line]
	call printf


	xor rcx, rcx
	mov ecx, [rbp - 104 + 208]
	xor rcx, rcx
	mov ecx, [rbp - 104 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 8 + 208]
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 16]
	mov r14d, [rbp - 24]
	cmp r13d, 0
	jg label6
	cmp r14d, 0
	jl label6
	jmp label7
	label6: 
	lea rdi, [errorMsg2]
	mov rsi, 0
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 16
	xor rax, rax
	call printf
	jmp main_end
label7:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 8 + 208]
	mov edx, [rbp - 16 + 208]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 104 + 208], rcx
	pop rax
	pop rax
	jmp label3
	label4:
	push rax
	push rax
	;Printing ID

	mov rdi, realFormat_out
	xor rsi, rsi
	mov esi, [rbp - 104 + 208]
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

	pop rax
	pop rax
	label3:
	pop rax
	 pop rcx
	inc qword [rbp - 8]
	inc rcx
	cmp rcx, rax
	jle label0
	;Printing ID

	mov rdi, realFormat_out
	xor rsi, rsi
	mov esi, [rbp - 104 + 208]
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
	sub rsp, 144
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 8], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 15
	mov [array_available_addr], r14

; loading array offsets
mov r13, 1
mov [rbp - 16], r13
mov r13, 15
mov [rbp - 24], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 32], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 15
	mov [array_available_addr], r14

; loading array offsets
mov r13, 1
mov [rbp - 40], r13
mov r13, 15
mov [rbp - 48], r13

	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 56]
	call scanf
xor r15, r15
mov r15d, [rbp - 8]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 16]
	mov rsi, r15
xor r15, r15
mov r15d, [rbp - 24]
	mov rdx, r15
xor r15, r15
mov r15d, [rbp - 56]
	mov rcx, r15
	call readArr
xor r15, r15
mov r15d, [rbp - 8]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 16]
	mov rsi, r15
xor r15, r15
mov r15d, [rbp - 24]
	mov rdx, r15
xor r15, r15
mov r15d, [rbp - 56]
	mov rcx, r15
	call arraySum
mov [rbp - 64], rdi
	;Printing ID

	mov rdi, realFormat_out
	xor rsi, rsi
	mov esi, [rbp - 64]
	call printf

	lea rdi, [new_line]
	call printf

readArr:

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
	sub rsp, 48
	mov rcx, 1
	mov [rbp - 16], rcx
	label8:
	xor rcx, rcx
	mov ecx, [rbp - 16]
	xor rcx, rcx
	mov ecx, [rbp - 16]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 32 + 208]
	xor rcx, rcx
	mov ecx, [rbp - 32 + 208]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jle label10
	mov rcx, 0
jmp label11
label10:
	mov rcx, 1
label11:	cmp rcx, 0
	je label9	;Taking id

	mov rdi, real_inMsg
	call printf
	mov rdi, realFormat_in
	lea rsi, [rbp - 8]
	call scanf
	xor rcx, rcx
	mov ecx, [rbp - 8]
	xor rcx, rcx
	mov ecx, [rbp - 8]
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 16]
	mov r14d, [rbp - 24]
	cmp r13d, 0
	jg label12
	cmp r14d, 0
	jl label12
	jmp label13
	label12: 
	lea rdi, [errorMsg2]
	mov rsi, 0
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 52
	xor rax, rax
	call printf
	jmp main_end
label13:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 8 + 208]
	mov edx, [rbp - 16 + 208]
	mov ebx, 0
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	xor rcx, rcx
	mov ecx, [rbp - 16]
	xor rcx, rcx
	mov ecx, [rbp - 16]
	push rcx
	push rcx
	mov rcx, 1
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 16], rcx
	jmp label8
	label9:

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
main_end:
mov rsp, rbp
pop rbp
mov rax, 0
ret
