section .bss
	start:	resd	1
	end:	resd	1

section .data
	print_start db "Enter the start index: ",0
	print_end db "Enter the end index: ",0
	inp_start_end db "%d",0
	print_string db "Hello World!",10,0
	 
section .text
	global main
	extern printf
	extern scanf

main:
	push rbp
	xor rax, rax
	mov rdi, print_start
	call printf
	
	xor rax, rax
	mov rdi, inp_start_end
	mov rsi, start
	call scanf
	
	xor rax, rax
	mov rdi, print_end
	call printf
	
	xor rax, rax
	mov rdi, inp_start_end
	mov rsi, end
	call scanf
	

	find_rbp:
	
	;mov ebx, [rbp + offset_start]
	;mov ecx, [rbp + offset_end]

	mov ebx, [start]
	mov ecx, [end]
	sub ecx, ebx
	inc ecx
	
loop:	xor rax, rax
	mov rdi, print_string

	push rcx
	push rbx
	call printf
	pop rbx
	pop rcx

	dec ecx
	cmp ecx, 0
	jne loop
	
	pop rbp
	ret 
