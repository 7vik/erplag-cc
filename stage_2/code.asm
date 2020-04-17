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
	sub rsp, 304
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 64]
	call scanf
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 72]
	call scanf
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 80], rax

	xor rax, rax
	mov eax, [rbp - 64]
	mov [rbp - 88], rax
	xor rax, rax
	mov eax, [rbp - 72]
	mov [rbp - 96], rax
; incrementing array_available address by array size

	xor r14, r14
	mov r14d, [array_available_addr]
	xor rax, rax
	xor rcx, rcx
	mov eax, [rbp - 88]
	mov ecx, [rbp - 96]
	sub ecx, eax
	inc ecx
	add r14d, ecx
	mov [array_available_addr], r14

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 104], rax

	xor rax, rax
	mov eax, [rbp - 64]
	mov [rbp - 112], rax
	xor rax, rax
	mov eax, [rbp - 72]
	mov [rbp - 120], rax
; incrementing array_available address by array size

	xor r14, r14
	mov r14d, [array_available_addr]
	xor rax, rax
	xor rcx, rcx
	mov eax, [rbp - 112]
	mov ecx, [rbp - 120]
	sub ecx, eax
	inc ecx
	add r14d, ecx
	mov [array_available_addr], r14

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 128], rax

	xor rax, rax
	mov eax, [rbp - 64]
	mov [rbp - 136], rax
	xor rax, rax
	mov eax, [rbp - 72]
	mov [rbp - 144], rax
; incrementing array_available address by array size

	xor r14, r14
	mov r14d, [array_available_addr]
	xor rax, rax
	xor rcx, rcx
	mov eax, [rbp - 136]
	mov ecx, [rbp - 144]
	sub ecx, eax
	inc ecx
	add r14d, ecx
	mov [array_available_addr], r14

	;Taking array

; prompts user for input
	mov ecx, [rbp - 88]
	mov r8d, [rbp - 96]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 88]
	mov r8d, [rbp - 96]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 96]
	mov r13d, [rbp - 88]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label0:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 80]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label0


	;Taking array

; prompts user for input
	mov ecx, [rbp - 112]
	mov r8d, [rbp - 120]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 112]
	mov r8d, [rbp - 120]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 120]
	mov r13d, [rbp - 112]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label1:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 104]
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
	xor rcx, rcx
	mov ecx, [rbp - 80]
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 80]
	mov edx, [rbp - 88]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 104]
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 104]
	mov edx, [rbp - 112]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 40], rcx
	xor rcx, rcx
	mov ecx, [rbp - 80]
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 80]
	mov edx, [rbp - 88]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 104]
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 104]
	mov edx, [rbp - 112]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 48], rcx
	xor rcx, rcx
	mov ecx, [rbp - 80]
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 80]
	mov edx, [rbp - 88]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 104]
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 104]
	mov edx, [rbp - 112]
	mov ebx, 0
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
mov rsp, rbp
pop rbp
mov rax, 0
ret
