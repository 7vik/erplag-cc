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
	mov r13d, [rbp - 48]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label4:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 40]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label4


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

	label5:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 88]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label5


	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 56]
mov r13d, [rbp - 48]
sub r12d, r13d
inc r12d
xor r13, r13

label6:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 40]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label6
	lea rdi, [new_line]
	call printf


	mov rcx, 0
	mov [rbp - 104 + 208], rcx
; for loop

	mov qword [rbp - 8], 10
	mov rcx, 10
	mov rax, 14
label7:
	push rcx
	push rax
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 8]
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
mov r12d, [rbp - 56]
mov r13d, [rbp - 48]
sub r12d, r13d
inc r12d
xor r13, r13

label8:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 40]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label8
	lea rdi, [new_line]
	call printf


	xor rcx, rcx
	mov ecx, [rbp - 104 + 208]
	xor rcx, rcx
	mov ecx, [rbp - 104 + 208]
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 48]
	mov r14d, [rbp - 56]
	cmp r13d, 0
	jg label9
	cmp r14d, 0
	jl label9
	jmp label10
	label9: 
	lea rdi, [errorMsg2]
	mov rsi, 0
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 31
	xor rax, rax
	call printf
	jmp main_end
label10:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 40]
	mov edx, [rbp - 48]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 104 + 208], rcx
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 104 + 208]
	call printf

	lea rdi, [new_line]
	call printf

	pop rax
	 pop rcx
	inc qword [rbp - 8]
	inc rcx
	cmp rcx, rax
	jle label7
	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 56]
mov r13d, [rbp - 48]
sub r12d, r13d
inc r12d
xor r13, r13

label11:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 40]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label11
	lea rdi, [new_line]
	call printf


	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 104 + 208]
	call printf

	lea rdi, [new_line]
	call printf

; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 96]
	mov r14d, [rbp - 104]
	cmp r13d, 6
	jg label12
	cmp r14d, 6
	jl label12
	jmp label13
	label12: 
	lea rdi, [errorMsg2]
	mov rsi, 6
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 38
	xor rax, rax
	call printf
	jmp main_end
label13:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 88]
	mov edx, [rbp - 96]
	mov ebx, 6
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
	mov r13d, [rbp - 96]
	mov r14d, [rbp - 104]
	cmp r13d, 7
	jg label14
	cmp r14d, 7
	jl label14
	jmp label15
	label14: 
	lea rdi, [errorMsg2]
	mov rsi, 7
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 38
	xor rax, rax
	call printf
	jmp main_end
label15:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 88]
	mov edx, [rbp - 96]
	mov ebx, 7
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 96]
	mov r14d, [rbp - 104]
	cmp r13d, 5
	jg label16
	cmp r14d, 5
	jl label16
	jmp label17
	label16: 
	lea rdi, [errorMsg2]
	mov rsi, 5
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 38
	xor rax, rax
	call printf
	jmp main_end
label17:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 88]
	mov edx, [rbp - 96]
	mov ebx, 5
	sub ebx, edx
	mov [rax + rbx * 8], rcx
	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 104]
mov r13d, [rbp - 96]
sub r12d, r13d
inc r12d
xor r13, r13

label18:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 88]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label18
	lea rdi, [new_line]
	call printf


	mov rcx, 0
	mov [rbp - 112 + 208], rcx
	xor rcx, rcx
	mov ecx, [rbp - 8 + 208]
	xor rcx, rcx
	mov ecx, [rbp - 8 + 208]
	mov [rbp - 64], rcx
	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 80]
mov r13d, [rbp - 72]
sub r12d, r13d
inc r12d
xor r13, r13

label19:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 64]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label19
	lea rdi, [new_line]
	call printf


; for loop

	mov qword [rbp - 16], 10
	mov rcx, 10
	mov rax, 14
label20:
	push rcx
	push rax
	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 80]
mov r13d, [rbp - 72]
sub r12d, r13d
inc r12d
xor r13, r13

label21:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 64]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label21
	lea rdi, [new_line]
	call printf


	xor rcx, rcx
	mov ecx, [rbp - 112 + 208]
	xor rcx, rcx
	mov ecx, [rbp - 112 + 208]
	push rcx
	push rcx
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 72]
	mov r14d, [rbp - 80]
	cmp r13d, 0
	jg label22
	cmp r14d, 0
	jl label22
	jmp label23
	label22: 
	lea rdi, [errorMsg2]
	mov rsi, 0
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 48
	xor rax, rax
	call printf
	jmp main_end
label23:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 64]
	mov edx, [rbp - 72]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 112 + 208], rcx
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 112 + 208]
	call printf

	lea rdi, [new_line]
	call printf

	pop rax
	 pop rcx
	inc qword [rbp - 16]
	inc rcx
	cmp rcx, rax
	jle label20
	;Printing array

; printing array
lea rdi, [arr_outMsg]
call printf
; stores the count

xor r12, r12
xor r13, r13
mov r12d, [rbp - 80]
mov r13d, [rbp - 72]
sub r12d, r13d
inc r12d
xor r13, r13

label24:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 64]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label24
	lea rdi, [new_line]
	call printf


	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 112 + 208]
	call printf

	lea rdi, [new_line]
	call printf

	mov rcx, 0
	mov [rbp - 120 + 208], rcx
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

label25:
	lea rdi, [intFormat_out]
	xor r14, r14
	mov r14d, [rbp - 32 + 208]
	mov rsi, [r14 + r13 * 8]
	call printf

	inc r13d
	cmp r13d, r12d
	jne label25
	lea rdi, [new_line]
	call printf


; for loop

	mov qword [rbp - 16], 1
	mov rcx, 1
	mov rax, 4
label26:
	push rcx
	push rax
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 112]
	call scanf
	xor rcx, rcx
	mov ecx, [rbp - 120 + 208]
	xor rcx, rcx
	mov ecx, [rbp - 120 + 208]
	push rcx
	push rcx
	xor rcx, rcx
	mov ecx, [rbp - 32 + 208]
; bound checking
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r13d, [rbp - 40]
	mov r14d, [rbp - 48]
	cmp r13d, 0
	jg label27
	cmp r14d, 0
	jl label27
	jmp label28
	label27: 
	lea rdi, [errorMsg2]
	mov rsi, 0
	mov rdx,  r13
	xor rcx, rcx
	mov rcx, r14
	mov r8, 61
	xor rax, rax
	call printf
	jmp main_end
label28:
	xor rax, rax
	xor rdx, rdx
	mov eax, [rbp - 32 + 208]
	mov edx, [rbp - 40 + 208]
	mov ebx, 0
	sub ebx, edx
	xor rcx, rcx
	mov ecx, [rax + rbx * 8]
	pop rdx
	pop rdx
	add rdx, rcx
	mov rcx, rdx
	mov [rbp - 120 + 208], rcx
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 120 + 208]
	call printf

	lea rdi, [new_line]
	call printf

	pop rax
	 pop rcx
	inc qword [rbp - 16]
	inc rcx
	cmp rcx, rax
	jle label26
	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 120 + 208]
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
	sub rsp, 192
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
	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 48], rax

mov r14d, r14d
	mov r14d, [array_available_addr]
	add r14, 5
	mov [array_available_addr], r14

; loading array offsets
mov r13, 10
mov [rbp - 56], r13
mov r13, 14
mov [rbp - 64], r13

	xor r14, r14
	mov r14d, [array_available_addr]
	lea rax, [array_buffer + r14 * 8]
	mov [rbp - 72], rax

	xor rax, rax
	mov eax, [rbp - 8]
	mov [rbp - 80], rax
	xor rax, rax
	mov eax, [rbp - 16]
	mov [rbp - 88], rax
; incrementing array_available address by array size

	xor r14, r14
	mov r14d, [array_available_addr]
	xor rax, rax
	xor rcx, rcx
	mov eax, [rbp - 80]
	mov ecx, [rbp - 88]
	cmp eax, ecx
	jg label29
	sub ecx, eax
	inc ecx
	add r14d, ecx
	mov [array_available_addr], r14

	jmp label30
	label29:
	lea rdi, [errorMsg1]
	mov rsi, rcx
	mov rdx,  rax
	xor rcx, rcx
	mov rcx, 74
	xor rax, rax
	call printf
	jmp main_end
label30:
	;Taking array

; prompts user for input
	mov ecx, [rbp - 56]
	mov r8d, [rbp - 64]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 56]
	mov r8d, [rbp - 64]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 64]
	mov r13d, [rbp - 56]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label31:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 48]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label31


	;Taking array

; prompts user for input
	mov ecx, [rbp - 80]
	mov r8d, [rbp - 88]
	mov esi, r8d
	sub esi, ecx
	inc esi
	mov rdi, arr_inMsg
mov rdx, type_int
	xor rcx, rcx
	xor r8, r8
	mov ecx, [rbp - 80]
	mov r8d, [rbp - 88]
	call printf

	; stores the count

	xor r12, r12
	xor r13, r13
	mov r12d, [rbp - 88]
	mov r13d, [rbp - 80]
	sub r12d, r13d
	inc r12d
	xor r13, r13

	label32:
lea rdi, [intFormat_in]
	xor r14, r14
	mov r14d, [rbp - 72]
	lea rsi, [r14 + r13 * 8]
	call scanf

	inc r13d
	cmp r13d, r12d
	jne label32


xor r15, r15
mov r15d, [rbp - 48]
	mov rdi, r15
xor r15, r15
mov r15d, [rbp - 56]
	mov rsi, r15
xor r15, r15
mov r15d, [rbp - 64]
	mov rdx, r15
xor r15, r15
mov r15d, [rbp - 72]
	mov rcx, r15
xor r15, r15
mov r15d, [rbp - 80]
	mov r8, r15
xor r15, r15
mov r15d, [rbp - 88]
	mov r9, r15
	call array_parameter_demo
mov [rbp - 24], rdi
mov [rbp - 32], rsi
mov [rbp - 40], rdx
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
	mov esi, [rbp - 32]
	call printf

	lea rdi, [new_line]
	call printf

	;Printing ID

	mov rdi, intFormat_out
	xor rsi, rsi
	mov esi, [rbp - 40]
	call printf

	lea rdi, [new_line]
	call printf

main_end:
mov rsp, rbp
pop rbp
mov rax, 0
ret
