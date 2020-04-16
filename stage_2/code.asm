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
	lea rsi, [rbp - 24]
	call scanf
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 40]
	call scanf
	;Taking id

	mov rdi, int_inMsg
	call printf
	mov rdi, intFormat_in
	lea rsi, [rbp - 56]
	call scanf
	mov rax, [rbp - 8]
	cmp rax, 1
	jne label1
	push rax
	push rax
	;Printing ID

	mov rdi, intFormat_out
	mov rsi, [rbp - 24]
	call printf

	lea rdi, [new_line]
	call printf

	pop rax
	pop rax
	jmp label0
	label1:
	cmp rax, 2
	jne label2
	push rax
	push rax
	;Printing ID

	mov rdi, intFormat_out
	mov rsi, [rbp - 24]
	call printf

	lea rdi, [new_line]
	call printf

	pop rax
	pop rax
	jmp label0
	label2:
	cmp rax, 3
	jne label3
	push rax
	push rax
	;Printing ID

	mov rdi, intFormat_out
	mov rsi, [rbp - 40]
	call printf

	lea rdi, [new_line]
	call printf

	pop rax
	pop rax
	jmp label0
	label3:
	;Printing ID

	mov rdi, intFormat_out
	mov rsi, [rbp - 56]
	call printf

	lea rdi, [new_line]
	call printf

label0:
mov rsp, rbp
pop rbp
mov rax, 0
ret
