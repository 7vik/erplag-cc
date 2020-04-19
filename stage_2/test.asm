section .text
	global main
	extern printf

section .data
	print_val: db  "%d",10,0

main:
	push rbp
	mov rbp, rsp
	
	sub rbp, 32
	
	mov qword[rbp - -8], 7

	mov rdi, print_val
	mov rsi, [rbp + 8]
	call printf

	add rbp, 32

	mov rsp, rbp
	pop rbp
	ret
			
