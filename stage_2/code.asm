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

main:

push rbp
mov rbp, rsp
	sub rsp, 272
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 64], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 6
mov [rbp - 72], r13
mov r13, 10
mov [rbp - 80], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 88], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 6
mov [rbp - 96], r13
mov r13, 10
mov [rbp - 104], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 112], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 6
mov [rbp - 120], r13
mov r13, 10
mov [rbp - 128], r13

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

	label0:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 64]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label0


	;Taking array

; prompts user for input
	mov ecx, [rbp - 96]
	mov r8d, [rbp - 104]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 96]
	mov r8d, [rbp - 104]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 104]
	mov r13d, [rbp - 96]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label1:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 88]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label1


	mov rcx, 7
	mov [rbp - 24], rcx
; for loop

	mov qword [rbp - 32], 1
	mov rcx, 1
	mov rax, 3
label2:
	push rcx
	push rax
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
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	xor r15, r15
	mov r13d, [rbp - 72]
	mov r14d, [rbp - 80]
	mov r15d, [rbp - 8]
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
	mov r8, 18
	xor rax, rax
	call printf
	call exit
label4:
	pop r14
	pop r13
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 64]
	mov edx, [rbp - 72]
	mov ebx, [rbp - 8]
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	xor r15, r15
	mov r13d, [rbp - 96]
	mov r14d, [rbp - 104]
	mov r15d, [rbp - 16]
	cmp r13d, r15d
	jg label5
	cmp r14d, r15d
	jl label5
	jmp label6
	label5: 
	lea rdi, [errorMsg2]
	mov rsi, r15
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 18
	xor rax, rax
	call printf
	call exit
label6:
	pop r14
	pop r13
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 88]
	mov edx, [rbp - 96]
	mov ebx, [rbp - 16]
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 40], rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	xor r15, r15
	mov r13d, [rbp - 72]
	mov r14d, [rbp - 80]
	mov r15d, [rbp - 24]
	cmp r13d, r15d
	jg label7
	cmp r14d, r15d
	jl label7
	jmp label8
	label7: 
	lea rdi, [errorMsg2]
	mov rsi, r15
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 19
	xor rax, rax
	call printf
	call exit
label8:
	pop r14
	pop r13
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 64]
	mov edx, [rbp - 72]
	mov ebx, [rbp - 24]
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	xor r15, r15
	mov r13d, [rbp - 96]
	mov r14d, [rbp - 104]
	mov r15d, [rbp - 16]
	cmp r13d, r15d
	jg label9
	cmp r14d, r15d
	jl label9
	jmp label10
	label9: 
	lea rdi, [errorMsg2]
	mov rsi, r15
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 19
	xor rax, rax
	call printf
	call exit
label10:
	pop r14
	pop r13
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 88]
	mov edx, [rbp - 96]
	mov ebx, [rbp - 16]
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 48], rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	xor r15, r15
	mov r13d, [rbp - 72]
	mov r14d, [rbp - 80]
	mov r15d, [rbp - 8]
	cmp r13d, r15d
	jg label11
	cmp r14d, r15d
	jl label11
	jmp label12
	label11: 
	lea rdi, [errorMsg2]
	mov rsi, r15
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 20
	xor rax, rax
	call printf
	call exit
label12:
	pop r14
	pop r13
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 64]
	mov edx, [rbp - 72]
	mov ebx, [rbp - 8]
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	xor r15, r15
	mov r13d, [rbp - 96]
	mov r14d, [rbp - 104]
	mov r15d, [rbp - 24]
	cmp r13d, r15d
	jg label13
	cmp r14d, r15d
	jl label13
	jmp label14
	label13: 
	lea rdi, [errorMsg2]
	mov rsi, r15
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 20
	xor rax, rax
	call printf
	call exit
label14:
	pop r14
	pop r13
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 88]
	mov edx, [rbp - 96]
	mov ebx, [rbp - 24]
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 56], rcx
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 40]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 48]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 56]
	call printf

	lea rdi, [new_line]
	call printf

	pop rax
	 pop rcx
	inc qword [rbp - 32]
	inc rcx
	cmp rcx, rax
	jle label2
main_end:
mov rsp, rbp
pop rbp
mov rax, 0
ret
