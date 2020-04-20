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
	sub rsp, 192
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
	add r14, 19
	mov [array_available_addr], r14

; loading array offsets
mov r13, 2
mov [rbp - 40], r13
mov r13, 20
mov [rbp - 48], r13

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
	mov r8, 12
	xor rax, rax
	call printf
	jmp main_end
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
	xor rcx, rcx
	mov ecx, [rbp - 16 + 208]
	mov [rbp - 32], rcx
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
	mov [rbp - 32], rcx
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
	mov r13d, [rbp - 40]
	mov r14d, [rbp - 48]
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
	mov r8, 16
	xor rax, rax
	call printf
	jmp main_end
label3:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 32]
	mov rdx, [rbp - 40]
	xor rbx, rbx
	mov ebx, 10
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	label4:
	xor rcx, rcx
	mov ecx, [rbp - 112 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 8]
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
	mov r8, 17
	xor rax, rax
	call printf
	jmp main_end
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
	mov [rbp - 72], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 19
	mov [array_available_addr], r14

; loading array offsets
mov r13, 2
mov [rbp - 80], r13
mov r13, 20
mov [rbp - 88], r13

	xor rcx, rcx
	mov ecx, [rbp - 16 + 208]
	mov [rbp - 72], rcx
	xor rcx, rcx
	mov ecx, [rbp - 64]
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
	mov r8, 22
	xor rax, rax
	call printf
	jmp main_end
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
	mov r13d, [rbp - 80]
	mov r14d, [rbp - 88]
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
	mov r8, 22
	xor rax, rax
	call printf
	jmp main_end
label13:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 72]
	mov rdx, [rbp - 80]
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
	mov r13d, [rbp - 80]
	mov r14d, [rbp - 88]
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
	mov r8, 23
	xor rax, rax
	call printf
	jmp main_end
label15:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 72]
	mov rdx, [rbp - 80]
	xor rbx, rbx
	mov ebx, 18
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	mov [rbp - 8], rcx
	jmp label4
	label5:

	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	mov [rbp - 104 + 208], rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	push rcx
	push rcx
	mov rcx, 3
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 16], rcx
	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jl label16
	mov rcx, 0
jmp label17
label16:
	mov rcx, 1
label17:	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	push rcx
	push rcx
	mov rcx, 100
	pop rdx
	pop rdx
	cmp rdx, rcx
	jl label18
	mov rcx, 0
jmp label19
label18:
	mov rcx, 1
label19:	pop rdx
	pop rdx
or rcx, rdx
	mov [rbp - 112 + 208], rcx
	;Printing ID

	lea rdi, [strFormat_in]
	mov sil, [rbp - 112 + 208]

	cmp sil, 0
	jz label20
	lea rsi, [true_label]
	jmp label21

label20: 
	lea rsi, [false_label]

label21: 
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
f1:

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

	mov rdi, real_inMsg
	call printf
	mov rdi, realFormat_in
	lea rsi, [rbp - 16]
	call scanf
	;Taking id

	mov rdi, real_inMsg
	call printf
	mov rdi, realFormat_in
	lea rsi, [rbp - 8]
	call scanf
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 40], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 7
	mov [array_available_addr], r14

; loading array offsets
mov r13, 4
mov [rbp - 48], r13
mov r13, 10
mov [rbp - 56], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 64], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 7
	mov [array_available_addr], r14

; loading array offsets
mov r13, 4
mov [rbp - 72], r13
mov r13, 10
mov [rbp - 80], r13

	;Taking array

; prompts user for input
	mov ecx, [rbp - 72]
	mov r8d, [rbp - 80]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 72]
	mov r8d, [rbp - 80]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 80]
	mov r13d, [rbp - 72]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label22:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 64]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label22


	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 88], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 21
	mov [array_available_addr], r14

; loading array offsets
mov r13, 10
mov [rbp - 96], r13
mov r13, 30
mov [rbp - 104], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 112], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 21
	mov [array_available_addr], r14

; loading array offsets
mov r13, 10
mov [rbp - 120], r13
mov r13, 30
mov [rbp - 128], r13

	mov [rbp - 40], rcx
	xor rcx, rcx
	mov ecx, [rbp - 8 + 208]
	mov [rbp - 112], rcx
	mov [rbp - 88], rcx
; for loop

	mov qword [rbp - 32], 15
	mov rcx, 15
	mov rax, 40
label23:
	push rcx
	push rax
	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 32]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 8], rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 56 + 208]
	push rcx
	push rcx
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 136], rcx
	xor rcx, rcx
	mov ecx, [rbp - 136]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 56 + 208]
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
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	mov [rbp - 144], rcx
	xor rax, rax
	mov eax, [rbp - 32]
	cmp rax, 10
	jne label25
	push rax
	push rax
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 168], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 21
	mov [array_available_addr], r14

; loading array offsets
mov r13, 10
mov [rbp - 176], r13
mov r13, 30
mov [rbp - 184], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 192], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 7
	mov [array_available_addr], r14

; loading array offsets
mov r13, 4
mov [rbp - 200], r13
mov r13, 10
mov [rbp - 208], r13

	xor rcx, rcx
	mov ecx, [rbp - 32]
	push rcx
	push rcx
	mov rcx, 20
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 176]
	mov r14d, [rbp - 184]
	cmp r13d, 9
	jg label26
	cmp r14d, 9
	jl label26
	jmp label27
	label26: 
	lea rdi, [errorMsg2]
	mov rsi, 9
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 58
	xor rax, rax
	call printf
	jmp main_end
label27:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 168]
	mov rdx, [rbp - 176]
	xor rbx, rbx
	mov ebx, 9
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	mov [rbp - 168], rcx
	xor rcx, rcx
	mov ecx, [rbp - 160]
	mov [rbp - 192], rcx
	pop rax
	pop rax
	jmp label24
	label25:
	cmp rax, 20
	jne label28
	push rax
	push rax
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 136]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
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
	xor rcx, rcx
	mov ecx, [rbp - 56 + 208]
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	mov [rbp - 152], rcx
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 160]
	call scanf
	xor rcx, rcx
	mov ecx, [rbp - 32]
	push rcx
	push rcx
	mov rcx, 12
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 160]
	push rcx
	push rcx
	mov rcx, 10
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
	xor rcx, rcx
	mov ecx, [rbp - 136]
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
	mov r13d, [rbp - 200]
	mov r14d, [rbp - 208]
	cmp r13d, 7
	jg label29
	cmp r14d, 7
	jl label29
	jmp label30
	label29: 
	lea rdi, [errorMsg2]
	mov rsi, 7
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 64
	xor rax, rax
	call printf
	jmp main_end
label30:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 192]
	mov rdx, [rbp - 200]
	xor rbx, rbx
	mov ebx, 7
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	pop rax
	pop rax
	jmp label24
	label28:
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 176]
	mov r14d, [rbp - 184]
	cmp r13d, 15
	jg label31
	cmp r14d, 15
	jl label31
	jmp label32
	label31: 
	lea rdi, [errorMsg2]
	mov rsi, 15
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 66
	xor rax, rax
	call printf
	jmp main_end
label32:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 168]
	mov rdx, [rbp - 176]
	xor rbx, rbx
	mov ebx, 15
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 160]
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
	mov r13d, [rbp - 200]
	mov r14d, [rbp - 208]
	cmp r13d, 9
	jg label33
	cmp r14d, 9
	jl label33
	jmp label34
	label33: 
	lea rdi, [errorMsg2]
	mov rsi, 9
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 66
	xor rax, rax
	call printf
	jmp main_end
label34:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 192]
	mov rdx, [rbp - 200]
	xor rbx, rbx
	mov ebx, 9
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
label24:
	xor rcx, rcx
	mov ecx, [rbp - 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 136]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 144]
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
	xor rcx, rcx
	mov ecx, [rbp - 136]
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 144]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jle label35
	mov rcx, 0
jmp label36
label35:
	mov rcx, 1
label36:	mov [rbp - 8], rcx
	pop rax
	 pop rcx
	inc qword [rbp - 32]
	inc rcx
	cmp rcx, rax
	jle label23
	xor rcx, rcx
	mov ecx, [rbp - 56 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 16]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 8], rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - -192]
	mov r14d, [rbp - -184]
	cmp r13d, 18
	jg label37
	cmp r14d, 18
	jl label37
	jmp label38
	label37: 
	lea rdi, [errorMsg2]
	mov rsi, 18
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 72
	xor rax, rax
	call printf
	jmp main_end
label38:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - -200]
	mov rdx, [rbp - -192]
	xor rbx, rbx
	mov ebx, 18
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - -168]
	mov r14d, [rbp - -160]
	cmp r13d, 18
	jg label39
	cmp r14d, 18
	jl label39
	jmp label40
	label39: 
	lea rdi, [errorMsg2]
	mov rsi, 18
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 72
	xor rax, rax
	call printf
	jmp main_end
label40:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - -176]
	mov rdx, [rbp - -168]
	xor rbx, rbx
	mov ebx, 18
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
	mov r13d, [rbp - 120]
	mov r14d, [rbp - 128]
	cmp r13d, 18
	jg label41
	cmp r14d, 18
	jl label41
	jmp label42
	label41: 
	lea rdi, [errorMsg2]
	mov rsi, 18
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 72
	xor rax, rax
	call printf
	jmp main_end
label42:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 112]
	mov rdx, [rbp - 120]
	xor rbx, rbx
	mov ebx, 18
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 72]
	mov r14d, [rbp - 80]
	cmp r13d, 6
	jg label43
	cmp r14d, 6
	jl label43
	jmp label44
	label43: 
	lea rdi, [errorMsg2]
	mov rsi, 6
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 73
	xor rax, rax
	call printf
	jmp main_end
label44:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 64]
	mov rdx, [rbp - 72]
	xor rbx, rbx
	mov ebx, 6
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	mov rcx, 10
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
	mov r13d, [rbp - 48]
	mov r14d, [rbp - 56]
	cmp r13d, 5
	jg label45
	cmp r14d, 5
	jl label45
	jmp label46
	label45: 
	lea rdi, [errorMsg2]
	mov rsi, 5
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 73
	xor rax, rax
	call printf
	jmp main_end
label46:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 40]
	mov rdx, [rbp - 48]
	xor rbx, rbx
	mov ebx, 5
	sub ebx, edx
	mov [rax + rbx * 8], rcx 
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 48]
	mov r14d, [rbp - 56]
	cmp r13d, 5
	jg label47
	cmp r14d, 5
	jl label47
	jmp label48
	label47: 
	lea rdi, [errorMsg2]
	mov rsi, 5
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 74
	xor rax, rax
	call printf
	jmp main_end
label48:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 40]
	mov rdx, [rbp - 48]
	xor rbx, rbx
	mov ebx, 5
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 120]
	mov r14d, [rbp - 128]
	cmp r13d, 18
	jg label49
	cmp r14d, 18
	jl label49
	jmp label50
	label49: 
	lea rdi, [errorMsg2]
	mov rsi, 18
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 74
	xor rax, rax
	call printf
	jmp main_end
label50:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 112]
	mov rdx, [rbp - 120]
	xor rbx, rbx
	mov ebx, 18
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 48]
	mov r14d, [rbp - 56]
	cmp r13d, 11
	jg label51
	cmp r14d, 11
	jl label51
	jmp label52
	label51: 
	lea rdi, [errorMsg2]
	mov rsi, 11
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 74
	xor rax, rax
	call printf
	jmp main_end
label52:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 40]
	mov rdx, [rbp - 48]
	xor rbx, rbx
	mov ebx, 11
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	cmp rdx, rcx
	jl label53
	mov rcx, 0
jmp label54
label53:
	mov rcx, 1
label54:	mov [rbp - 104 + 208], rcx
	mov rcx, 20
	push rcx
	push rcx
	mov rcx, 8
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	mov rcx, 5
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	mov [rbp - 112 + 208], rcx
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
	sub rsp, 336
	mov rcx, 12
	mov [rbp - 16], rcx
	mov [rbp - 40], rcx
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 8]
	call scanf
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 48], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 19
	mov [array_available_addr], r14

; loading array offsets
mov r13, 2
mov [rbp - 56], r13
mov r13, 20
mov [rbp - 64], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 72], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 19
	mov [array_available_addr], r14

; loading array offsets
mov r13, 2
mov [rbp - 80], r13
mov r13, 20
mov [rbp - 88], r13

xor r15, r15
mov r15d, [rbp - 16]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 48]
	mov rsi, r15
xor r15, r15
mov r15d, [rbp - 56]
	mov rdx, r15
xor r15, r15
mov r15d, [rbp - 64]
	mov rcx, r15
xor r15, r15
mov r15d, [rbp - 40]
	mov r8, r15
	call var_demo_array
mov [rbp - 8], rdi
mov [rbp - 24], rsi
xor r15, r15
mov r15d, [rbp - 16]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 48]
	mov rsi, r15
xor r15, r15
mov r15d, [rbp - 56]
	mov rdx, r15
xor r15, r15
mov r15d, [rbp - 64]
	mov rcx, r15
xor r15, r15
mov r15d, [rbp - 40]
	mov r8, r15
	call var_demo_array
mov [rbp - 8], rdi
mov [rbp - 32], rsi
	mov [rbp - 96], rcx
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 104]
	call scanf
	;Taking id

	mov rdi, real_inMsg
	call printf
	mov rdi, realFormat_in
	lea rsi, [rbp - 120]
	call scanf
	mov [rbp - 128], rcx
	xor rcx, rcx
	mov ecx, [rbp - 40]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 120]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 128]
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
	xor rcx, rcx
	mov ecx, [rbp - 96]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 112]
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	mov [rbp - 112], rcx
	mov rcx, 1
	push rcx
	push rcx
	mov rcx, 0
	pop rdx
	pop rdx
and rcx, rdx
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 120]
	pop rdx
	pop rdx
or rcx, rdx
	mov [rbp - 32], rcx
	xor rcx, rcx
	mov ecx, [rbp - 96]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 104]
	pop rdx
	pop rdx
	cmp rdx, rcx
	jle label55
	mov rcx, 0
jmp label56
label55:
	mov rcx, 1
label56:	mov [rbp - 24], rcx
	mov rcx, 23
	push rcx
	push rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 56]
	mov r14d, [rbp - 64]
	cmp r13d, 6
	jg label57
	cmp r14d, 6
	jl label57
	jmp label58
	label57: 
	lea rdi, [errorMsg2]
	mov rsi, 6
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 101
	xor rax, rax
	call printf
	jmp main_end
label58:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 48]
	mov rdx, [rbp - 56]
	xor rbx, rbx
	mov ebx, 6
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 136], rcx
	xor rcx, rcx
	mov ecx, [rbp - 96]
	push rcx
	push rcx
	mov rcx, 25
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	mov rcx, 100
	push rcx
	push rcx
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 80]
	mov r14d, [rbp - 88]
	cmp r13d, 1
	jg label59
	cmp r14d, 1
	jl label59
	jmp label60
	label59: 
	lea rdi, [errorMsg2]
	mov rsi, 1
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 102
	xor rax, rax
	call printf
	jmp main_end
label60:
	pop r14
	pop r13
	pop rcx
	pop rcx
	xor rax, rax
	xor rdx, rdx
	mov rax, [rbp - 72]
	mov rdx, [rbp - 80]
	xor rbx, rbx
	mov ebx, 1
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	imul rdx, rcx
	mov rcx, rdx
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 104], rcx
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 144], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 21
	mov [array_available_addr], r14

; loading array offsets
mov r13, 20
mov [rbp - 152], r13
mov r13, 40
mov [rbp - 160], r13

	xor rcx, rcx
	mov ecx, [rbp - 112]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 120]
	pop rdx
	pop rdx
	sub rdx, rcx
	mov rcx, rdx
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 128]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 144], rcx
	xor rcx, rcx
	mov ecx, [rbp - 136]
	push rcx
	push rcx
	mov rcx, 5
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 136], rcx
	mov [rbp - 48], rcx
	mov [rbp - 72], rcx
main_end:
mov rsp, rbp
pop rbp
mov rax, 0
ret
