	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_remove_comments        ## -- Begin function remove_comments
	.p2align	4, 0x90
_remove_comments:                       ## @remove_comments
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movl	$0, -12(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-8(%rbp), %rdi
	callq	_fgetc
	movb	%al, %cl
	movb	%cl, -13(%rbp)
	movsbl	%cl, %eax
	cmpl	$-1, %eax
	je	LBB0_33
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$0, -12(%rbp)
	jne	LBB0_7
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %eax
	cmpl	$42, %eax
	jne	LBB0_5
## %bb.4:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	$1, -12(%rbp)
	jmp	LBB0_6
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %edi
	callq	_putchar
	movl	%eax, -20(%rbp)         ## 4-byte Spill
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_32
LBB0_7:                                 ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$1, -12(%rbp)
	jne	LBB0_12
## %bb.8:                               ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %eax
	cmpl	$42, %eax
	jne	LBB0_10
## %bb.9:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	$2, -12(%rbp)
	jmp	LBB0_11
LBB0_10:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	$0, -12(%rbp)
	movl	$42, %edi
	callq	_putchar
	movsbl	-13(%rbp), %edi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_putchar
	movl	%eax, -28(%rbp)         ## 4-byte Spill
LBB0_11:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_31
LBB0_12:                                ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$2, -12(%rbp)
	jne	LBB0_20
## %bb.13:                              ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %eax
	cmpl	$42, %eax
	jne	LBB0_15
## %bb.14:                              ##   in Loop: Header=BB0_1 Depth=1
	movl	$3, -12(%rbp)
	jmp	LBB0_19
LBB0_15:                                ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %eax
	cmpl	$10, %eax
	jne	LBB0_17
## %bb.16:                              ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %edi
	callq	_putchar
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	jmp	LBB0_18
LBB0_17:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_18
LBB0_18:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_19
LBB0_19:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_30
LBB0_20:                                ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$3, -12(%rbp)
	jne	LBB0_28
## %bb.21:                              ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %eax
	cmpl	$42, %eax
	jne	LBB0_23
## %bb.22:                              ##   in Loop: Header=BB0_1 Depth=1
	movl	$0, -12(%rbp)
	jmp	LBB0_27
LBB0_23:                                ##   in Loop: Header=BB0_1 Depth=1
	movsbl	-13(%rbp), %eax
	cmpl	$10, %eax
	jne	LBB0_25
## %bb.24:                              ##   in Loop: Header=BB0_1 Depth=1
	movl	$2, -12(%rbp)
	movsbl	-13(%rbp), %edi
	callq	_putchar
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	jmp	LBB0_26
LBB0_25:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	$2, -12(%rbp)
LBB0_26:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_27
LBB0_27:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_29
LBB0_28:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_29
LBB0_29:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_30
LBB0_30:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_31
LBB0_31:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_32
LBB0_32:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_1
LBB0_33:
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_remove_comments_driver ## -- Begin function remove_comments_driver
	.p2align	4, 0x90
_remove_comments_driver:                ## @remove_comments_driver
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_remove_comments
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_push                   ## -- Begin function push
	.p2align	4, 0x90
_push:                                  ## @push
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	$16, %edi
	callq	_malloc
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-24(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	%esi, (%rax)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdi
	movq	%rax, (%rdi)
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_is_empty               ## -- Begin function is_empty
	.p2align	4, 0x90
_is_empty:                              ## @is_empty
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	sete	%al
	andb	$1, %al
	movzbl	%al, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_top                    ## -- Begin function top
	.p2align	4, 0x90
_top:                                   ## @top
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	callq	_is_empty
	cmpl	$0, %eax
	je	LBB4_2
## %bb.1:
	movl	$-1, -4(%rbp)
	jmp	LBB4_3
LBB4_2:
	movq	-16(%rbp), %rax
	movl	(%rax), %ecx
	movl	%ecx, -4(%rbp)
LBB4_3:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_pop                    ## -- Begin function pop
	.p2align	4, 0x90
_pop:                                   ## @pop
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rdi
	callq	_is_empty
	cmpl	$0, %eax
	je	LBB5_2
## %bb.1:
	leaq	L_.str.114(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	jmp	LBB5_3
LBB5_2:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	movq	-8(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	callq	_free
LBB5_3:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_stack            ## -- Begin function print_stack
	.p2align	4, 0x90
_print_stack:                           ## @print_stack
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_is_empty
	cmpl	$0, %eax
	jne	LBB6_2
## %bb.1:
	movq	-8(%rbp), %rax
	movl	(%rax), %esi
	leaq	L_.str.115(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rdi
	movq	8(%rdi), %rdi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	callq	_print_stack
	jmp	LBB6_3
LBB6_2:
	movl	$10, %edi
	callq	_putchar
	movl	%eax, -16(%rbp)         ## 4-byte Spill
LBB6_3:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_create_new_node        ## -- Begin function create_new_node
	.p2align	4, 0x90
_create_new_node:                       ## @create_new_node
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	$136, %edi
	callq	_malloc
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdi
	movq	%rax, (%rdi)
	movq	-16(%rbp), %rax
	movl	$0, 8(%rax)
	movl	$15, -20(%rbp)
LBB7_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-20(%rbp), %eax
	addl	$-1, %eax
	movl	%eax, -20(%rbp)
	cmpl	$0, %eax
	jl	LBB7_3
## %bb.2:                               ##   in Loop: Header=BB7_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-20(%rbp), %rcx
	movq	$0, 16(%rax,%rcx,8)
	jmp	LBB7_1
LBB7_3:
	movq	-16(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_stylish_print_charstar ## -- Begin function stylish_print_charstar
	.p2align	4, 0x90
_stylish_print_charstar:                ## @stylish_print_charstar
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	LBB8_2
## %bb.1:
	leaq	L_.str.116(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB8_3
LBB8_2:
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB8_3:
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_stylish_pr_intttttttt  ## -- Begin function stylish_pr_intttttttt
	.p2align	4, 0x90
_stylish_pr_intttttttt:                 ## @stylish_pr_intttttttt
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -12(%rbp)
	cmpl	$1, -12(%rbp)
	jne	LBB9_2
## %bb.1:
	leaq	L_.str.117(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB9_3
LBB9_2:
	leaq	L_.str.118(%rip), %rax
	movq	%rax, -8(%rbp)
LBB9_3:
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_super_stylish_print_charstar ## -- Begin function super_stylish_print_charstar
	.p2align	4, 0x90
_super_stylish_print_charstar:          ## @super_stylish_print_charstar
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	cmpq	$0, -16(%rbp)
	je	LBB10_2
## %bb.1:
	movq	-16(%rbp), %rax
	cmpq	$0, (%rax)
	jne	LBB10_3
LBB10_2:
	leaq	L_.str.116(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB10_4
LBB10_3:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	48(%rax), %rax
	movq	%rax, -8(%rbp)
LBB10_4:
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_parse_tree       ## -- Begin function print_parse_tree
	.p2align	4, 0x90
_print_parse_tree:                      ## @print_parse_tree
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$112, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	LBB11_2
## %bb.1:
	jmp	LBB11_8
LBB11_2:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdi
	movq	-16(%rbp), %rsi
	callq	_print_parse_tree
	movq	-16(%rbp), %rdi
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	%rdi, -32(%rbp)         ## 8-byte Spill
	movq	%rax, %rdi
	callq	_stylish_print_charstar
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movl	8(%rsi), %ecx
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	24(%rsi), %rdi
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	movl	%ecx, -44(%rbp)         ## 4-byte Spill
	callq	_stylish_print_charstar
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	16(%rsi), %rdi
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	callq	_stylish_print_charstar
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	32(%rsi), %rdi
	movq	%rax, -64(%rbp)         ## 8-byte Spill
	callq	_super_stylish_print_charstar
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movl	40(%rsi), %edi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	_stylish_pr_intttttttt
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	48(%rsi), %rdi
	movq	%rax, -80(%rbp)         ## 8-byte Spill
	callq	_stylish_print_charstar
	movq	-32(%rbp), %rdi         ## 8-byte Reload
	leaq	L_.str.119(%rip), %rsi
	movq	-40(%rbp), %rdx         ## 8-byte Reload
	movl	-44(%rbp), %ecx         ## 4-byte Reload
	movq	-56(%rbp), %r8          ## 8-byte Reload
	movq	-64(%rbp), %r9          ## 8-byte Reload
	movq	-72(%rbp), %r10         ## 8-byte Reload
	movq	%r10, (%rsp)
	movq	-80(%rbp), %r10         ## 8-byte Reload
	movq	%r10, 8(%rsp)
	movq	%rax, 16(%rsp)
	movb	$0, %al
	callq	_fprintf
	movq	-8(%rbp), %rdx
	movl	8(%rdx), %ecx
	movl	%ecx, -20(%rbp)
	movl	$1, -24(%rbp)
	movl	%eax, -84(%rbp)         ## 4-byte Spill
LBB11_3:                                ## =>This Inner Loop Header: Depth=1
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB11_6
## %bb.4:                               ##   in Loop: Header=BB11_3 Depth=1
	movq	-8(%rbp), %rax
	movslq	-24(%rbp), %rcx
	movq	16(%rax,%rcx,8), %rdi
	movq	-16(%rbp), %rsi
	callq	_print_parse_tree
## %bb.5:                               ##   in Loop: Header=BB11_3 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB11_3
LBB11_6:
	jmp	LBB11_7
LBB11_7:
	jmp	LBB11_8
LBB11_8:
	addq	$112, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_is_terminal            ## -- Begin function is_terminal
	.p2align	4, 0x90
_is_terminal:                           ## @is_terminal
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	LBB12_2
## %bb.1:
	leaq	L_.str.120(%rip), %rdi
	xorl	%eax, %eax
	movb	%al, %cl
	movb	%cl, %al
	callq	_printf
	movl	$2, %edi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	callq	_exit
LBB12_2:
	movq	-16(%rbp), %rax
	movsbl	(%rax), %edi
	callq	_isupper
	cmpl	$0, %eax
	je	LBB12_4
## %bb.3:
	movl	$1, -4(%rbp)
	jmp	LBB12_5
LBB12_4:
	movl	$0, -4(%rbp)
LBB12_5:
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_rule             ## -- Begin function print_rule
	.p2align	4, 0x90
_print_rule:                            ## @print_rule
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
LBB13_1:                                ## =>This Inner Loop Header: Depth=1
	cmpq	$0, -8(%rbp)
	je	LBB13_3
## %bb.2:                               ##   in Loop: Header=BB13_1 Depth=1
	movq	-8(%rbp), %rsi
	leaq	L_.str.121(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rsi
	movq	56(%rsi), %rsi
	movq	%rsi, -8(%rbp)
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	jmp	LBB13_1
LBB13_3:
	movl	$10, %edi
	callq	_putchar
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_grammar          ## -- Begin function print_grammar
	.p2align	4, 0x90
_print_grammar:                         ## @print_grammar
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$0, -12(%rbp)
LBB14_1:                                ## =>This Inner Loop Header: Depth=1
	movl	-12(%rbp), %eax
	movq	-8(%rbp), %rcx
	cmpl	1200(%rcx), %eax
	jge	LBB14_4
## %bb.2:                               ##   in Loop: Header=BB14_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-12(%rbp), %rcx
	movq	(%rax,%rcx,8), %rdi
	callq	_print_rule
	movl	$10, %edi
	callq	_putchar
	movl	%eax, -16(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB14_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB14_1
LBB14_4:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_string_to_enum         ## -- Begin function string_to_enum
	.p2align	4, 0x90
_string_to_enum:                        ## @string_to_enum
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	movl	$114, -20(%rbp)
	movl	$0, -24(%rbp)
LBB15_1:                                ## =>This Inner Loop Header: Depth=1
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB15_6
## %bb.2:                               ##   in Loop: Header=BB15_1 Depth=1
	movslq	-24(%rbp), %rax
	leaq	_variables_array(%rip), %rcx
	movq	(%rcx,%rax,8), %rdi
	movq	-16(%rbp), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB15_4
## %bb.3:
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	LBB15_7
LBB15_4:                                ##   in Loop: Header=BB15_1 Depth=1
	jmp	LBB15_5
LBB15_5:                                ##   in Loop: Header=BB15_1 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB15_1
LBB15_6:
	movq	-16(%rbp), %rsi
	leaq	L_.str.122(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$-1, -4(%rbp)
	movl	%eax, -28(%rbp)         ## 4-byte Spill
LBB15_7:
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_set_array        ## -- Begin function print_set_array
	.p2align	4, 0x90
_print_set_array:                       ## @print_set_array
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
LBB16_1:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$149, -16(%rbp)
	jge	LBB16_6
## %bb.2:                               ##   in Loop: Header=BB16_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-16(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	cmpl	$1, %esi
	jne	LBB16_4
## %bb.3:                               ##   in Loop: Header=BB16_1 Depth=1
	movslq	-16(%rbp), %rax
	leaq	_variables_array(%rip), %rcx
	movq	(%rcx,%rax,8), %rsi
	leaq	L_.str.123(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -12(%rbp)
	movl	%eax, -20(%rbp)         ## 4-byte Spill
LBB16_4:                                ##   in Loop: Header=BB16_1 Depth=1
	jmp	LBB16_5
LBB16_5:                                ##   in Loop: Header=BB16_1 Depth=1
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	LBB16_1
LBB16_6:
	cmpl	$0, -12(%rbp)
	je	LBB16_8
## %bb.7:
	leaq	L_.str.124(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -24(%rbp)         ## 4-byte Spill
LBB16_8:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_first_follow_node ## -- Begin function print_first_follow_node
	.p2align	4, 0x90
_print_first_follow_node:               ## @print_first_follow_node
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_print_set_array
	leaq	L_.str.125(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rdi
	addq	$150, %rdi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	callq	_print_set_array
	leaq	L_.str.126(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_first_follow     ## -- Begin function print_first_follow
	.p2align	4, 0x90
_print_first_follow:                    ## @print_first_follow
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	leaq	L_.str.127(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -12(%rbp)
	movl	%eax, -16(%rbp)         ## 4-byte Spill
LBB18_1:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -12(%rbp)
	jge	LBB18_6
## %bb.2:                               ##   in Loop: Header=BB18_1 Depth=1
	movslq	-12(%rbp), %rax
	leaq	_variables_array(%rip), %rcx
	movq	(%rcx,%rax,8), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB18_4
## %bb.3:
	jmp	LBB18_6
LBB18_4:                                ##   in Loop: Header=BB18_1 Depth=1
	movslq	-12(%rbp), %rax
	leaq	_variables_array(%rip), %rcx
	movq	(%rcx,%rax,8), %rsi
	leaq	L_.str.128(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rcx
	movslq	-12(%rbp), %rsi
	movq	(%rcx,%rsi,8), %rdi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	callq	_print_first_follow_node
## %bb.5:                               ##   in Loop: Header=BB18_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB18_1
LBB18_6:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_populate_first         ## -- Begin function populate_first
	.p2align	4, 0x90
_populate_first:                        ## @populate_first
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$144, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-32(%rbp), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB19_2
## %bb.1:
	movq	-32(%rbp), %rsi
	leaq	L_.str.129(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	jmp	LBB19_29
LBB19_2:
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-72(%rbp), %rcx         ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movb	149(%rdi), %dl
	andb	$1, %dl
	movzbl	%dl, %eax
	cmpl	$1, %eax
	jne	LBB19_4
## %bb.3:
	jmp	LBB19_29
LBB19_4:
	cmpq	$0, -32(%rbp)
	jne	LBB19_6
## %bb.5:
	leaq	L_.str.130(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	jmp	LBB19_29
LBB19_6:
	movl	$0, -36(%rbp)
LBB19_7:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB19_15 Depth 2
	movl	-36(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB19_27
## %bb.8:                               ##   in Loop: Header=BB19_7 Depth=1
	movq	-32(%rbp), %rdi
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB19_25
## %bb.9:                               ##   in Loop: Header=BB19_7 Depth=1
	movl	$0, -40(%rbp)
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	56(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	56(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-48(%rbp), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB19_11
## %bb.10:                              ##   in Loop: Header=BB19_7 Depth=1
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -88(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-88(%rbp), %rcx         ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movq	-48(%rbp), %rdx
	movq	%rdi, -96(%rbp)         ## 8-byte Spill
	movq	%rdx, %rdi
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-96(%rbp), %rdx         ## 8-byte Reload
	movb	$1, (%rdx,%rcx)
	jmp	LBB19_26
LBB19_11:                               ##   in Loop: Header=BB19_7 Depth=1
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movl	-20(%rbp), %edx
	movq	-48(%rbp), %rcx
	callq	_populate_first
	movq	-48(%rbp), %rdi
	callq	_string_to_enum
	movl	%eax, -60(%rbp)
	movq	-8(%rbp), %rcx
	movslq	-60(%rbp), %rsi
	movq	(%rcx,%rsi,8), %rcx
	movb	149(%rcx), %r8b
	andb	$1, %r8b
	movzbl	%r8b, %eax
	cmpl	$1, %eax
	sete	%r8b
	xorb	$-1, %r8b
	andb	$1, %r8b
	movzbl	%r8b, %eax
	movslq	%eax, %rcx
	cmpq	$0, %rcx
	je	LBB19_13
## %bb.12:
	leaq	L___func__.populate_first(%rip), %rdi
	leaq	L_.str.131(%rip), %rsi
	leaq	L_.str.132(%rip), %rcx
	movl	$331, %edx              ## imm = 0x14B
	callq	___assert_rtn
LBB19_13:                               ##   in Loop: Header=BB19_7 Depth=1
	jmp	LBB19_14
LBB19_14:                               ##   in Loop: Header=BB19_7 Depth=1
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -104(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-104(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movq	-8(%rbp), %rdx
	movslq	-60(%rbp), %rsi
	movq	(%rdx,%rsi,8), %rsi
	callq	_or_and_store
LBB19_15:                               ##   Parent Loop BB19_7 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movq	-8(%rbp), %rax
	movslq	-60(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movb	76(%rax), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	cmpl	$1, %esi
	jne	LBB19_24
## %bb.16:                              ##   in Loop: Header=BB19_15 Depth=2
	movq	-56(%rbp), %rax
	cmpq	$0, 56(%rax)
	je	LBB19_23
## %bb.17:                              ##   in Loop: Header=BB19_15 Depth=2
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -112(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-112(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movb	$0, 76(%rdi)
	movq	-56(%rbp), %rdi
	movq	56(%rdi), %rdi
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rdi
	movq	%rdi, -48(%rbp)
	movq	-48(%rbp), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB19_19
## %bb.18:                              ##   in Loop: Header=BB19_7 Depth=1
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -120(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-120(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movq	-48(%rbp), %rdx
	movq	%rdi, -128(%rbp)        ## 8-byte Spill
	movq	%rdx, %rdi
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-128(%rbp), %rdx        ## 8-byte Reload
	movb	$1, (%rdx,%rcx)
	jmp	LBB19_24
LBB19_19:                               ##   in Loop: Header=BB19_15 Depth=2
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movl	-20(%rbp), %edx
	movq	-48(%rbp), %rcx
	callq	_populate_first
	movq	-48(%rbp), %rdi
	callq	_string_to_enum
	movl	%eax, -60(%rbp)
	movq	-8(%rbp), %rcx
	movslq	-60(%rbp), %rsi
	movq	(%rcx,%rsi,8), %rcx
	movb	149(%rcx), %r8b
	andb	$1, %r8b
	movzbl	%r8b, %eax
	cmpl	$1, %eax
	sete	%r8b
	xorb	$-1, %r8b
	andb	$1, %r8b
	movzbl	%r8b, %eax
	movslq	%eax, %rcx
	cmpq	$0, %rcx
	je	LBB19_21
## %bb.20:
	leaq	L___func__.populate_first(%rip), %rdi
	leaq	L_.str.131(%rip), %rsi
	leaq	L_.str.132(%rip), %rcx
	movl	$355, %edx              ## imm = 0x163
	callq	___assert_rtn
LBB19_21:                               ##   in Loop: Header=BB19_15 Depth=2
	jmp	LBB19_22
LBB19_22:                               ##   in Loop: Header=BB19_15 Depth=2
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -136(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-136(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movq	-8(%rbp), %rdx
	movslq	-60(%rbp), %rsi
	movq	(%rdx,%rsi,8), %rsi
	callq	_or_and_store
LBB19_23:                               ##   in Loop: Header=BB19_15 Depth=2
	jmp	LBB19_15
LBB19_24:                               ##   in Loop: Header=BB19_7 Depth=1
	jmp	LBB19_26
LBB19_25:                               ##   in Loop: Header=BB19_7 Depth=1
	jmp	LBB19_26
LBB19_26:                               ##   in Loop: Header=BB19_7 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB19_7
LBB19_27:
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -144(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-144(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movb	$1, 149(%rdi)
## %bb.28:
	jmp	LBB19_29
LBB19_29:
	addq	$144, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_populate_follow        ## -- Begin function populate_follow
	.p2align	4, 0x90
_populate_follow:                       ## @populate_follow
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$224, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rdi
	movq	%rcx, -56(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-56(%rbp), %rsi         ## 8-byte Reload
	movq	(%rsi,%rcx,8), %rcx
	movb	299(%rcx), %r8b
	andb	$1, %r8b
	movzbl	%r8b, %eax
	cmpl	$1, %eax
	jne	LBB20_2
## %bb.1:
	jmp	LBB20_34
LBB20_2:
	cmpq	$0, -32(%rbp)
	jne	LBB20_4
## %bb.3:
	leaq	L_.str.133(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	jmp	LBB20_34
LBB20_4:
	movl	$0, -36(%rbp)
LBB20_5:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB20_7 Depth 2
                                        ##       Child Loop BB20_13 Depth 3
	movl	-36(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB20_33
## %bb.6:                               ##   in Loop: Header=BB20_5 Depth=1
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	56(%rax), %rax
	movq	%rax, -48(%rbp)
LBB20_7:                                ##   Parent Loop BB20_5 Depth=1
                                        ## =>  This Loop Header: Depth=2
                                        ##       Child Loop BB20_13 Depth 3
	cmpq	$0, -48(%rbp)
	je	LBB20_31
## %bb.8:                               ##   in Loop: Header=BB20_7 Depth=2
	movq	-32(%rbp), %rdi
	movq	-48(%rbp), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB20_30
## %bb.9:                               ##   in Loop: Header=BB20_7 Depth=2
	movq	-48(%rbp), %rax
	cmpq	$0, 56(%rax)
	je	LBB20_26
## %bb.10:                              ##   in Loop: Header=BB20_7 Depth=2
	movq	-48(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB20_12
## %bb.11:                              ##   in Loop: Header=BB20_7 Depth=2
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-72(%rbp), %rcx         ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movq	-48(%rbp), %rdx
	movq	%rdi, -80(%rbp)         ## 8-byte Spill
	movq	%rdx, %rdi
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-80(%rbp), %rdx         ## 8-byte Reload
	movb	$1, 150(%rdx,%rcx)
	jmp	LBB20_25
LBB20_12:                               ##   in Loop: Header=BB20_7 Depth=2
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -88(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-88(%rbp), %rcx         ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	addq	$150, %rdi
	movq	-8(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movq	%rdi, -96(%rbp)         ## 8-byte Spill
	movq	%rsi, %rdi
	movq	%rdx, -104(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-104(%rbp), %rdx        ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rsi
	movq	-96(%rbp), %rdi         ## 8-byte Reload
	callq	_or_and_store
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rdi
	movq	%rcx, -112(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-112(%rbp), %rdx        ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rcx
	movb	$0, 226(%rcx)
LBB20_13:                               ##   Parent Loop BB20_5 Depth=1
                                        ##     Parent Loop BB20_7 Depth=2
                                        ## =>    This Inner Loop Header: Depth=3
	movq	-8(%rbp), %rax
	movq	-48(%rbp), %rdi
	movq	%rax, -120(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-120(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movb	76(%rdi), %dl
	andb	$1, %dl
	movzbl	%dl, %eax
	cmpl	$1, %eax
	jne	LBB20_24
## %bb.14:                              ##   in Loop: Header=BB20_13 Depth=3
	movq	-48(%rbp), %rax
	cmpq	$0, 56(%rax)
	jne	LBB20_17
## %bb.15:                              ##   in Loop: Header=BB20_13 Depth=3
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rdi
	movq	-32(%rbp), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	je	LBB20_17
## %bb.16:                              ##   in Loop: Header=BB20_7 Depth=2
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rcx
	callq	_populate_follow
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -128(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-128(%rbp), %rsi        ## 8-byte Reload
	movq	(%rsi,%rcx,8), %rcx
	addq	$150, %rcx
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %r8
	movslq	-36(%rbp), %r9
	movq	(%r8,%r9,8), %r8
	movq	%rdi, -136(%rbp)        ## 8-byte Spill
	movq	%r8, %rdi
	movq	%rcx, -144(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-136(%rbp), %rsi        ## 8-byte Reload
	movq	(%rsi,%rcx,8), %rcx
	addq	$150, %rcx
	movq	-144(%rbp), %rdi        ## 8-byte Reload
	movq	%rcx, %rsi
	callq	_or_and_store
	jmp	LBB20_24
LBB20_17:                               ##   in Loop: Header=BB20_13 Depth=3
	movq	-48(%rbp), %rax
	cmpq	$0, 56(%rax)
	je	LBB20_22
## %bb.18:                              ##   in Loop: Header=BB20_13 Depth=3
	movq	-48(%rbp), %rax
	movq	56(%rax), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB20_20
## %bb.19:                              ##   in Loop: Header=BB20_7 Depth=2
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -152(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-152(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movq	-48(%rbp), %rdx
	movq	56(%rdx), %rdx
	movq	%rdi, -160(%rbp)        ## 8-byte Spill
	movq	%rdx, %rdi
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-160(%rbp), %rdx        ## 8-byte Reload
	movb	$1, 150(%rdx,%rcx)
	movq	-48(%rbp), %rcx
	movq	56(%rcx), %rcx
	movq	%rcx, -48(%rbp)
	jmp	LBB20_24
LBB20_20:                               ##   in Loop: Header=BB20_13 Depth=3
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -168(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-168(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	addq	$150, %rdi
	movq	-8(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movq	56(%rsi), %rsi
	movq	%rdi, -176(%rbp)        ## 8-byte Spill
	movq	%rsi, %rdi
	movq	%rdx, -184(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-184(%rbp), %rdx        ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rsi
	movq	-176(%rbp), %rdi        ## 8-byte Reload
	callq	_or_and_store
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rdi
	movq	%rcx, -192(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-192(%rbp), %rdx        ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rcx
	movb	$0, 226(%rcx)
	movq	-48(%rbp), %rcx
	movq	56(%rcx), %rcx
	movq	%rcx, -48(%rbp)
## %bb.21:                              ##   in Loop: Header=BB20_13 Depth=3
	jmp	LBB20_22
LBB20_22:                               ##   in Loop: Header=BB20_13 Depth=3
	jmp	LBB20_23
LBB20_23:                               ##   in Loop: Header=BB20_13 Depth=3
	jmp	LBB20_13
LBB20_24:                               ##   in Loop: Header=BB20_7 Depth=2
	jmp	LBB20_25
LBB20_25:                               ##   in Loop: Header=BB20_7 Depth=2
	jmp	LBB20_29
LBB20_26:                               ##   in Loop: Header=BB20_7 Depth=2
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rdi
	movq	-32(%rbp), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	je	LBB20_28
## %bb.27:                              ##   in Loop: Header=BB20_7 Depth=2
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rcx
	callq	_populate_follow
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -200(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-200(%rbp), %rsi        ## 8-byte Reload
	movq	(%rsi,%rcx,8), %rcx
	addq	$150, %rcx
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %r8
	movslq	-36(%rbp), %r9
	movq	(%r8,%r9,8), %r8
	movq	%rdi, -208(%rbp)        ## 8-byte Spill
	movq	%r8, %rdi
	movq	%rcx, -216(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-208(%rbp), %rsi        ## 8-byte Reload
	movq	(%rsi,%rcx,8), %rcx
	addq	$150, %rcx
	movq	-216(%rbp), %rdi        ## 8-byte Reload
	movq	%rcx, %rsi
	callq	_or_and_store
LBB20_28:                               ##   in Loop: Header=BB20_7 Depth=2
	jmp	LBB20_29
LBB20_29:                               ##   in Loop: Header=BB20_7 Depth=2
	jmp	LBB20_30
LBB20_30:                               ##   in Loop: Header=BB20_7 Depth=2
	movq	-48(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, -48(%rbp)
	jmp	LBB20_7
LBB20_31:                               ##   in Loop: Header=BB20_5 Depth=1
	jmp	LBB20_32
LBB20_32:                               ##   in Loop: Header=BB20_5 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB20_5
LBB20_33:
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rax, -224(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-224(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movb	$1, 299(%rdi)
LBB20_34:
	addq	$224, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_construct_first_follow_set ## -- Begin function construct_first_follow_set
	.p2align	4, 0x90
_construct_first_follow_set:            ## @construct_first_follow_set
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	$800, %edi              ## imm = 0x320
	callq	_malloc
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
LBB21_1:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -28(%rbp)
	jge	LBB21_4
## %bb.2:                               ##   in Loop: Header=BB21_1 Depth=1
	movl	$300, %edi              ## imm = 0x12C
	callq	_malloc
	movq	-24(%rbp), %rdi
	movslq	-28(%rbp), %rcx
	movq	%rax, (%rdi,%rcx,8)
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movq	(%rax,%rcx,8), %rdi
	callq	_initialize_bool_array
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	addq	$150, %rax
	movq	%rax, %rdi
	callq	_initialize_bool_array
## %bb.3:                               ##   in Loop: Header=BB21_1 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB21_1
LBB21_4:
	movl	$0, -32(%rbp)
LBB21_5:                                ## =>This Inner Loop Header: Depth=1
	movl	-32(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB21_10
## %bb.6:                               ##   in Loop: Header=BB21_5 Depth=1
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movslq	-32(%rbp), %rdx
	movq	(%rcx,%rdx,8), %rdi
	movq	%rax, -48(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-48(%rbp), %rdx         ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rcx
	movb	149(%rcx), %sil
	andb	$1, %sil
	movzbl	%sil, %eax
	cmpl	$0, %eax
	jne	LBB21_8
## %bb.7:                               ##   in Loop: Header=BB21_5 Depth=1
	movq	-24(%rbp), %rdi
	movq	-8(%rbp), %rsi
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movslq	-32(%rbp), %rcx
	movq	(%rax,%rcx,8), %rcx
	callq	_populate_first
LBB21_8:                                ##   in Loop: Header=BB21_5 Depth=1
	jmp	LBB21_9
LBB21_9:                                ##   in Loop: Header=BB21_5 Depth=1
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	jmp	LBB21_5
LBB21_10:
	movq	-24(%rbp), %rax
	movq	312(%rax), %rax
	movb	$1, 220(%rax)
	movl	$0, -36(%rbp)
LBB21_11:                               ## =>This Inner Loop Header: Depth=1
	movl	-36(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB21_16
## %bb.12:                              ##   in Loop: Header=BB21_11 Depth=1
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movslq	-36(%rbp), %rdx
	movq	(%rcx,%rdx,8), %rdi
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-56(%rbp), %rdx         ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rcx
	movb	299(%rcx), %sil
	andb	$1, %sil
	movzbl	%sil, %eax
	cmpl	$0, %eax
	jne	LBB21_14
## %bb.13:                              ##   in Loop: Header=BB21_11 Depth=1
	movq	-24(%rbp), %rdi
	movq	-8(%rbp), %rsi
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movslq	-36(%rbp), %rcx
	movq	(%rax,%rcx,8), %rcx
	callq	_populate_follow
LBB21_14:                               ##   in Loop: Header=BB21_11 Depth=1
	jmp	LBB21_15
LBB21_15:                               ##   in Loop: Header=BB21_11 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB21_11
LBB21_16:
	movq	-24(%rbp), %rax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_non_terminals    ## -- Begin function print_non_terminals
	.p2align	4, 0x90
_print_non_terminals:                   ## @print_non_terminals
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	$0, -16(%rbp)
LBB22_1:                                ## =>This Inner Loop Header: Depth=1
	movl	-16(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB22_4
## %bb.2:                               ##   in Loop: Header=BB22_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-16(%rbp), %rcx
	movq	(%rax,%rcx,8), %rsi
	leaq	L_.str.134(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -20(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB22_1 Depth=1
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	LBB22_1
LBB22_4:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_initialize_grammar     ## -- Begin function initialize_grammar
	.p2align	4, 0x90
_initialize_grammar:                    ## @initialize_grammar
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$0, -12(%rbp)
LBB23_1:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$150, -12(%rbp)
	jge	LBB23_6
## %bb.2:                               ##   in Loop: Header=BB23_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-12(%rbp), %rcx
	movq	$0, (%rax,%rcx,8)
	movq	-8(%rbp), %rax
	movslq	-12(%rbp), %rcx
	cmpq	$0, (%rax,%rcx,8)
	je	LBB23_4
## %bb.3:                               ##   in Loop: Header=BB23_1 Depth=1
	leaq	L_.str.135(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -16(%rbp)         ## 4-byte Spill
LBB23_4:                                ##   in Loop: Header=BB23_1 Depth=1
	jmp	LBB23_5
LBB23_5:                                ##   in Loop: Header=BB23_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB23_1
LBB23_6:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_generate_grammar       ## -- Begin function generate_grammar
	.p2align	4, 0x90
_generate_grammar:                      ## @generate_grammar
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$304, %rsp              ## imm = 0x130
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	leaq	L_.str.136(%rip), %rdi
	leaq	L_.str.137(%rip), %rsi
	callq	_fopen
	movq	%rax, -216(%rbp)
	cmpq	$0, -216(%rbp)
	jne	LBB24_2
## %bb.1:
	leaq	L_.str.138(%rip), %rdi
	leaq	L_.str.136(%rip), %rsi
	xorl	%eax, %eax
	movb	%al, %cl
	movb	%cl, %al
	callq	_printf
	movl	$1, %edi
	movl	%eax, -260(%rbp)        ## 4-byte Spill
	callq	_exit
LBB24_2:
	movl	$1208, %edi             ## imm = 0x4B8
	callq	_malloc
	movq	%rax, -224(%rbp)
	movl	$0, -228(%rbp)
LBB24_3:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB24_5 Depth 2
	leaq	-208(%rbp), %rdx
	movq	-216(%rbp), %rdi
	leaq	L_.str.139(%rip), %rsi
	movb	$0, %al
	callq	_fscanf
	movl	$4294967295, %ecx       ## imm = 0xFFFFFFFF
	cmpl	%eax, %ecx
	je	LBB24_10
## %bb.4:                               ##   in Loop: Header=BB24_3 Depth=1
	leaq	-208(%rbp), %rdi
	leaq	L_.str.140(%rip), %rsi
	callq	_strtok
	movq	%rax, -240(%rbp)
	movl	$64, %edi
	callq	_malloc
	movq	-224(%rbp), %rsi
	movslq	-228(%rbp), %rdi
	movq	%rax, (%rsi,%rdi,8)
	movq	-224(%rbp), %rax
	movslq	-228(%rbp), %rsi
	movq	(%rax,%rsi,8), %rax
	movq	%rax, -248(%rbp)
	movq	-224(%rbp), %rax
	movslq	-228(%rbp), %rsi
	movq	(%rax,%rsi,8), %rdi
	movq	-240(%rbp), %rsi
	movl	$50, %edx
	callq	___strcpy_chk
	xorl	%ecx, %ecx
	movl	%ecx, %edi
	movq	-224(%rbp), %rdx
	movslq	-228(%rbp), %rsi
	movq	(%rdx,%rsi,8), %rdx
	movl	$0, 52(%rdx)
	movq	-224(%rbp), %rdx
	movslq	-228(%rbp), %rsi
	movq	(%rdx,%rsi,8), %rdx
	movq	$0, 56(%rdx)
	leaq	L_.str.140(%rip), %rsi
	movq	%rax, -272(%rbp)        ## 8-byte Spill
	callq	_strtok
	movq	%rax, -240(%rbp)
LBB24_5:                                ##   Parent Loop BB24_3 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpq	$0, -240(%rbp)
	je	LBB24_9
## %bb.6:                               ##   in Loop: Header=BB24_5 Depth=2
	movq	-240(%rbp), %rdi
	leaq	L_.str.141(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB24_8
## %bb.7:                               ##   in Loop: Header=BB24_5 Depth=2
	xorl	%eax, %eax
	movl	%eax, %edi
	leaq	L_.str.140(%rip), %rsi
	callq	_strtok
	movq	%rax, -240(%rbp)
	jmp	LBB24_5
LBB24_8:                                ##   in Loop: Header=BB24_5 Depth=2
	movl	$64, %edi
	callq	_malloc
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rdi
	movq	-240(%rbp), %rsi
	movl	$50, %edx
	callq	___strcpy_chk
	movq	-240(%rbp), %rdi
	movq	%rax, -280(%rbp)        ## 8-byte Spill
	callq	_is_terminal
	xorl	%ecx, %ecx
	movl	%ecx, %edi
	movq	-256(%rbp), %rdx
	movl	%eax, 52(%rdx)
	movq	-256(%rbp), %rdx
	movq	$0, 56(%rdx)
	movq	-256(%rbp), %rdx
	movq	-248(%rbp), %rsi
	movq	%rdx, 56(%rsi)
	movq	-248(%rbp), %rdx
	movq	56(%rdx), %rdx
	movq	%rdx, -248(%rbp)
	leaq	L_.str.140(%rip), %rsi
	callq	_strtok
	movq	%rax, -240(%rbp)
	jmp	LBB24_5
LBB24_9:                                ##   in Loop: Header=BB24_3 Depth=1
	movl	-228(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -228(%rbp)
	jmp	LBB24_3
LBB24_10:
	movq	-216(%rbp), %rdi
	callq	_fclose
	movl	-228(%rbp), %ecx
	movq	-224(%rbp), %rdi
	movl	%ecx, 1200(%rdi)
	movq	-224(%rbp), %rdi
	movq	___stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	(%rdx), %rdx
	movq	-8(%rbp), %rsi
	cmpq	%rsi, %rdx
	movl	%eax, -284(%rbp)        ## 4-byte Spill
	movq	%rdi, -296(%rbp)        ## 8-byte Spill
	jne	LBB24_12
## %bb.11:
	movq	-296(%rbp), %rax        ## 8-byte Reload
	addq	$304, %rsp              ## imm = 0x130
	popq	%rbp
	retq
LBB24_12:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_get_first_follow_table ## -- Begin function get_first_follow_table
	.p2align	4, 0x90
_get_first_follow_table:                ## @get_first_follow_table
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	-8(%rbp), %rax
	movl	1200(%rax), %esi
	callq	_construct_first_follow_set
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_recursive_multiple_first ## -- Begin function recursive_multiple_first
	.p2align	4, 0x90
_recursive_multiple_first:              ## @recursive_multiple_first
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$112, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movq	%rcx, -40(%rbp)
	movq	-24(%rbp), %rsi
	leaq	L_.str.76(%rip), %rdi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB26_2
## %bb.1:
	movq	-32(%rbp), %rax
	movb	$1, 76(%rax)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB26_17
LBB26_2:
	movq	-24(%rbp), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB26_4
## %bb.3:
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-72(%rbp), %rcx         ## 8-byte Reload
	movb	$1, (%rcx,%rdi)
	movq	-32(%rbp), %rdi
	movq	%rdi, -8(%rbp)
	jmp	LBB26_17
LBB26_4:
	movq	-24(%rbp), %rax
	cmpq	$0, 56(%rax)
	jne	LBB26_6
## %bb.5:
	movq	-32(%rbp), %rdi
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rcx
	movq	%rdi, -80(%rbp)         ## 8-byte Spill
	movq	%rcx, %rdi
	movq	%rax, -88(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-88(%rbp), %rdi         ## 8-byte Reload
	movq	(%rdi,%rcx,8), %rsi
	movq	-80(%rbp), %rdi         ## 8-byte Reload
	callq	_or_and_store
	movq	-32(%rbp), %rcx
	movq	%rcx, -8(%rbp)
	jmp	LBB26_17
LBB26_6:
	movl	$300, %edi              ## imm = 0x12C
	callq	_malloc
	movq	%rax, -48(%rbp)
	movl	$300, %edi              ## imm = 0x12C
	callq	_malloc
	movq	%rax, -56(%rbp)
	movl	$0, -60(%rbp)
LBB26_7:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$150, -60(%rbp)
	jge	LBB26_10
## %bb.8:                               ##   in Loop: Header=BB26_7 Depth=1
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rdi
	movq	%rax, -96(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rdi
	movq	-96(%rbp), %rcx         ## 8-byte Reload
	movq	(%rcx,%rdi,8), %rdi
	movslq	-60(%rbp), %rdx
	movb	(%rdi,%rdx), %sil
	movq	-48(%rbp), %rdx
	movslq	-60(%rbp), %rdi
	andb	$1, %sil
	movb	%sil, (%rdx,%rdi)
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rdi
	movq	%rdx, -104(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-104(%rbp), %rdx        ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rcx
	movslq	-60(%rbp), %rdi
	movb	150(%rcx,%rdi), %sil
	movq	-48(%rbp), %rcx
	movslq	-60(%rbp), %rdi
	andb	$1, %sil
	movb	%sil, 150(%rcx,%rdi)
## %bb.9:                               ##   in Loop: Header=BB26_7 Depth=1
	movl	-60(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -60(%rbp)
	jmp	LBB26_7
LBB26_10:
	movq	-48(%rbp), %rax
	movb	76(%rax), %cl
	andb	$1, %cl
	movzbl	%cl, %edx
	cmpl	$1, %edx
	jne	LBB26_12
## %bb.11:
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rax
	movq	56(%rax), %rsi
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rcx
	callq	_recursive_multiple_first
	movq	%rax, -56(%rbp)
LBB26_12:
	movq	-48(%rbp), %rax
	movb	$0, 76(%rax)
	movl	$0, -64(%rbp)
LBB26_13:                               ## =>This Inner Loop Header: Depth=1
	cmpl	$149, -64(%rbp)
	jge	LBB26_16
## %bb.14:                              ##   in Loop: Header=BB26_13 Depth=1
	movq	-48(%rbp), %rax
	movslq	-64(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	movq	-56(%rbp), %rax
	movslq	-64(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %edi
	orl	%edi, %esi
	cmpl	$0, %esi
	setne	%dl
	movq	-32(%rbp), %rax
	movslq	-64(%rbp), %rcx
	andb	$1, %dl
	movb	%dl, (%rax,%rcx)
## %bb.15:                              ##   in Loop: Header=BB26_13 Depth=1
	movl	-64(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -64(%rbp)
	jmp	LBB26_13
LBB26_16:
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB26_17:
	movq	-8(%rbp), %rax
	addq	$112, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_multiple_first         ## -- Begin function multiple_first
	.p2align	4, 0x90
_multiple_first:                        ## @multiple_first
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$300, %edi              ## imm = 0x12C
	callq	_malloc
	movq	%rax, -32(%rbp)
	movl	-12(%rbp), %esi
	movq	-8(%rbp), %rax
	cmpl	1200(%rax), %esi
	setb	%cl
	xorb	$-1, %cl
	andb	$1, %cl
	movzbl	%cl, %esi
	movslq	%esi, %rax
	cmpq	$0, %rax
	je	LBB27_2
## %bb.1:
	leaq	L___func__.multiple_first(%rip), %rdi
	leaq	L_.str.131(%rip), %rsi
	leaq	L_.str.142(%rip), %rcx
	movl	$663, %edx              ## imm = 0x297
	callq	___assert_rtn
LBB27_2:
	jmp	LBB27_3
LBB27_3:
	movq	-8(%rbp), %rax
	movl	-12(%rbp), %ecx
	movl	%ecx, %edx
	movq	(%rax,%rdx,8), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-8(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	callq	_recursive_multiple_first
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_create_parse_table     ## -- Begin function create_parse_table
	.p2align	4, 0x90
_create_parse_table:                    ## @create_parse_table
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$56, -28(%rbp)
	movl	$58, -32(%rbp)
	movl	$0, -36(%rbp)
LBB28_1:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB28_3 Depth 2
	movl	-36(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jge	LBB28_8
## %bb.2:                               ##   in Loop: Header=BB28_1 Depth=1
	movl	$0, -40(%rbp)
LBB28_3:                                ##   Parent Loop BB28_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	-40(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jge	LBB28_6
## %bb.4:                               ##   in Loop: Header=BB28_3 Depth=2
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	imulq	$232, %rcx, %rcx
	addq	%rcx, %rax
	movslq	-40(%rbp), %rcx
	movl	$-1, (%rax,%rcx,4)
## %bb.5:                               ##   in Loop: Header=BB28_3 Depth=2
	movl	-40(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -40(%rbp)
	jmp	LBB28_3
LBB28_6:                                ##   in Loop: Header=BB28_1 Depth=1
	jmp	LBB28_7
LBB28_7:                                ##   in Loop: Header=BB28_1 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB28_1
LBB28_8:
	movl	$0, -44(%rbp)
LBB28_9:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB28_11 Depth 2
                                        ##     Child Loop BB28_18 Depth 2
	movl	-44(%rbp), %eax
	movq	-24(%rbp), %rcx
	cmpl	1200(%rcx), %eax
	jge	LBB28_26
## %bb.10:                              ##   in Loop: Header=BB28_9 Depth=1
	movl	$56, -48(%rbp)
LBB28_11:                               ##   Parent Loop BB28_9 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$113, -48(%rbp)
	jg	LBB28_16
## %bb.12:                              ##   in Loop: Header=BB28_11 Depth=2
	movq	-24(%rbp), %rdi
	movl	-44(%rbp), %esi
	movq	-8(%rbp), %rdx
	callq	_multiple_first
	movslq	-48(%rbp), %rdx
	movb	(%rax,%rdx), %cl
	andb	$1, %cl
	movzbl	%cl, %esi
	cmpl	$1, %esi
	jne	LBB28_14
## %bb.13:                              ##   in Loop: Header=BB28_11 Depth=2
	movl	-44(%rbp), %eax
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movslq	-44(%rbp), %rsi
	movq	(%rdx,%rsi,8), %rdi
	movl	%eax, -56(%rbp)         ## 4-byte Spill
	movq	%rcx, -64(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	imulq	$232, %rcx, %rcx
	movq	-64(%rbp), %rdx         ## 8-byte Reload
	addq	%rcx, %rdx
	movl	-48(%rbp), %eax
	subl	-28(%rbp), %eax
	movslq	%eax, %rcx
	movl	-56(%rbp), %eax         ## 4-byte Reload
	movl	%eax, (%rdx,%rcx,4)
LBB28_14:                               ##   in Loop: Header=BB28_11 Depth=2
	jmp	LBB28_15
LBB28_15:                               ##   in Loop: Header=BB28_11 Depth=2
	movl	-48(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -48(%rbp)
	jmp	LBB28_11
LBB28_16:                               ##   in Loop: Header=BB28_9 Depth=1
	movq	-24(%rbp), %rdi
	movl	-44(%rbp), %esi
	movq	-8(%rbp), %rdx
	callq	_multiple_first
	movb	76(%rax), %cl
	andb	$1, %cl
	movzbl	%cl, %esi
	cmpl	$1, %esi
	jne	LBB28_24
## %bb.17:                              ##   in Loop: Header=BB28_9 Depth=1
	movl	$56, -52(%rbp)
LBB28_18:                               ##   Parent Loop BB28_9 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$113, -52(%rbp)
	jg	LBB28_23
## %bb.19:                              ##   in Loop: Header=BB28_18 Depth=2
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rcx
	movslq	-44(%rbp), %rdx
	movq	(%rcx,%rdx,8), %rdi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	movq	-72(%rbp), %rdx         ## 8-byte Reload
	movq	(%rdx,%rcx,8), %rcx
	movslq	-52(%rbp), %rdi
	movb	150(%rcx,%rdi), %sil
	andb	$1, %sil
	movzbl	%sil, %eax
	cmpl	$1, %eax
	jne	LBB28_21
## %bb.20:                              ##   in Loop: Header=BB28_18 Depth=2
	movl	-44(%rbp), %eax
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movslq	-44(%rbp), %rsi
	movq	(%rdx,%rsi,8), %rdi
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	movq	%rcx, -88(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	imulq	$232, %rcx, %rcx
	movq	-88(%rbp), %rdx         ## 8-byte Reload
	addq	%rcx, %rdx
	movl	-52(%rbp), %eax
	subl	-28(%rbp), %eax
	movslq	%eax, %rcx
	movl	-76(%rbp), %eax         ## 4-byte Reload
	movl	%eax, (%rdx,%rcx,4)
LBB28_21:                               ##   in Loop: Header=BB28_18 Depth=2
	jmp	LBB28_22
LBB28_22:                               ##   in Loop: Header=BB28_18 Depth=2
	movl	-52(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -52(%rbp)
	jmp	LBB28_18
LBB28_23:                               ##   in Loop: Header=BB28_9 Depth=1
	jmp	LBB28_24
LBB28_24:                               ##   in Loop: Header=BB28_9 Depth=1
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rcx
	movslq	-44(%rbp), %rdx
	movq	(%rcx,%rdx,8), %rdi
	movq	%rax, -96(%rbp)         ## 8-byte Spill
	callq	_string_to_enum
	movslq	%eax, %rcx
	imulq	$232, %rcx, %rcx
	movq	-96(%rbp), %rdx         ## 8-byte Reload
	addq	%rcx, %rdx
	movl	$76, %eax
	subl	-28(%rbp), %eax
	movslq	%eax, %rcx
	movl	$-1, (%rdx,%rcx,4)
## %bb.25:                              ##   in Loop: Header=BB28_9 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	LBB28_9
LBB28_26:
	movq	-16(%rbp), %rax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_parse_table      ## -- Begin function print_parse_table
	.p2align	4, 0x90
_print_parse_table:                     ## @print_parse_table
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$56, -20(%rbp)
	movl	$58, -24(%rbp)
	leaq	L_.str.143(%rip), %rdi
	leaq	L_.str.144(%rip), %rsi
	movb	$0, %al
	callq	_printf
	movl	$0, -28(%rbp)
	movl	%eax, -40(%rbp)         ## 4-byte Spill
LBB29_1:                                ## =>This Inner Loop Header: Depth=1
	movl	-28(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jge	LBB29_4
## %bb.2:                               ##   in Loop: Header=BB29_1 Depth=1
	movl	-28(%rbp), %eax
	addl	-20(%rbp), %eax
	movslq	%eax, %rcx
	leaq	_variables_array(%rip), %rdx
	movq	(%rdx,%rcx,8), %rsi
	leaq	L_.str.145(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -44(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB29_1 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB29_1
LBB29_4:
	movl	$10, %edi
	callq	_putchar
	movl	$10, %edi
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	callq	_putchar
	movl	$0, -32(%rbp)
	movl	%eax, -52(%rbp)         ## 4-byte Spill
LBB29_5:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB29_7 Depth 2
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB29_12
## %bb.6:                               ##   in Loop: Header=BB29_5 Depth=1
	movslq	-32(%rbp), %rax
	leaq	_variables_array(%rip), %rcx
	movq	(%rcx,%rax,8), %rsi
	leaq	L_.str.143(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -36(%rbp)
	movl	%eax, -56(%rbp)         ## 4-byte Spill
LBB29_7:                                ##   Parent Loop BB29_5 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	-36(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jge	LBB29_10
## %bb.8:                               ##   in Loop: Header=BB29_7 Depth=2
	movq	-8(%rbp), %rax
	movslq	-32(%rbp), %rcx
	imulq	$232, %rcx, %rcx
	addq	%rcx, %rax
	movslq	-36(%rbp), %rcx
	movl	(%rax,%rcx,4), %esi
	leaq	L_.str.146(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -60(%rbp)         ## 4-byte Spill
## %bb.9:                               ##   in Loop: Header=BB29_7 Depth=2
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB29_7
LBB29_10:                               ##   in Loop: Header=BB29_5 Depth=1
	movl	$10, %edi
	callq	_putchar
	movl	%eax, -64(%rbp)         ## 4-byte Spill
## %bb.11:                              ##   in Loop: Header=BB29_5 Depth=1
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	jmp	LBB29_5
LBB29_12:
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_pushr                  ## -- Begin function pushr
	.p2align	4, 0x90
_pushr:                                 ## @pushr
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	LBB30_2
## %bb.1:
	jmp	LBB30_3
LBB30_2:
	movl	$136, %edi
	callq	_malloc
	movq	-8(%rbp), %rdi
	movq	-8(%rbp), %rcx
	movslq	8(%rcx), %rcx
	movq	%rax, 16(%rdi,%rcx,8)
	movl	$56, %edi
	callq	_malloc
	movq	-8(%rbp), %rcx
	movq	-8(%rbp), %rdi
	movslq	8(%rdi), %rdi
	movq	16(%rcx,%rdi,8), %rcx
	movq	%rax, (%rcx)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rcx
	movslq	8(%rcx), %rcx
	movq	16(%rax,%rcx,8), %rax
	movq	(%rax), %rax
	movl	$0, 40(%rax)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rcx
	movslq	8(%rcx), %rcx
	movq	16(%rax,%rcx,8), %rax
	movq	(%rax), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rcx
	movslq	8(%rcx), %rcx
	movq	16(%rax,%rcx,8), %rax
	movq	(%rax), %rax
	movl	$0, 8(%rax)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	-8(%rbp), %rdi
	movslq	8(%rdi), %rdi
	movq	16(%rcx,%rdi,8), %rcx
	movq	(%rcx), %rcx
	movq	%rax, 48(%rcx)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	-8(%rbp), %rdi
	movslq	8(%rdi), %rdi
	movq	16(%rcx,%rdi,8), %rcx
	movq	(%rcx), %rcx
	movq	%rax, 32(%rcx)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rcx
	movslq	8(%rcx), %rcx
	movq	16(%rax,%rcx,8), %rax
	movq	(%rax), %rax
	movq	$0, 16(%rax)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rcx
	movslq	8(%rcx), %rcx
	movq	16(%rax,%rcx,8), %rax
	movq	(%rax), %rax
	movq	$0, 24(%rax)
	movq	-8(%rbp), %rax
	movl	8(%rax), %edx
	addl	$1, %edx
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	56(%rax), %rdx
	callq	_pushr
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rax
	movq	%rdi, -32(%rbp)         ## 8-byte Spill
	movq	%rax, %rdi
	callq	_string_to_enum
	movq	-32(%rbp), %rdi         ## 8-byte Reload
	movl	%eax, %esi
	callq	_push
LBB30_3:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_error                  ## -- Begin function error
	.p2align	4, 0x90
_error:                                 ## @error
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movl	(%rdx), %esi
	leaq	L_.str.147(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_fill_tree              ## -- Begin function fill_tree
	.p2align	4, 0x90
_fill_tree:                             ## @fill_tree
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_insert_parse_tree      ## -- Begin function insert_parse_tree
	.p2align	4, 0x90
_insert_parse_tree:                     ## @insert_parse_tree
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	(%rsi), %rsi
	movl	$1, 40(%rsi)
	movq	-16(%rbp), %rsi
	movl	16(%rsi), %eax
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	(%rsi), %rsi
	movl	%eax, 8(%rsi)
	movq	-16(%rbp), %rsi
	movq	8(%rsi), %rsi
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rdi
	movq	(%rdi), %rdi
	movq	%rsi, (%rdi)
	movq	-16(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rdi
	movq	(%rdi), %rdi
	movq	%rsi, 16(%rdi)
	movq	-16(%rbp), %rsi
	movq	(%rsi), %rdi
	leaq	L_.str.93(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	je	LBB33_2
## %bb.1:
	movq	-16(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.103(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB33_3
LBB33_2:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	-8(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	(%rcx), %rcx
	movq	%rax, 24(%rcx)
LBB33_3:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	(%rcx), %rcx
	movq	%rax, 48(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, 8(%rax)
	movl	$0, -20(%rbp)
LBB33_4:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$15, -20(%rbp)
	jge	LBB33_7
## %bb.5:                               ##   in Loop: Header=BB33_4 Depth=1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movslq	-20(%rbp), %rcx
	movq	$0, 16(%rax,%rcx,8)
## %bb.6:                               ##   in Loop: Header=BB33_4 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB33_4
LBB33_7:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_next_active            ## -- Begin function next_active
	.p2align	4, 0x90
_next_active:                           ## @next_active
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	(%rsi), %rsi
	cmpq	-8(%rbp), %rsi
	jne	LBB34_2
## %bb.1:
	jmp	LBB34_8
LBB34_2:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	32(%rax), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
LBB34_3:                                ## =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movq	16(%rax,%rcx,8), %rax
	movq	-16(%rbp), %rcx
	cmpq	(%rcx), %rax
	je	LBB34_5
## %bb.4:                               ##   in Loop: Header=BB34_3 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB34_3
LBB34_5:
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rcx
	movq	%rax, (%rcx)
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	8(%rax), %esi
	subl	$1, %esi
	cmpl	%esi, %edx
	jge	LBB34_7
## %bb.6:
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %ecx
	addl	$1, %ecx
	movslq	%ecx, %rdx
	movq	16(%rax,%rdx,8), %rax
	movq	-16(%rbp), %rdx
	movq	%rax, (%rdx)
	jmp	LBB34_8
LBB34_7:
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	callq	_next_active
LBB34_8:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_parse                  ## -- Begin function parse
	.p2align	4, 0x90
_parse:                                 ## @parse
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$176, %rsp
	movq	16(%rbp), %rax
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	movl	$0, -52(%rbp)
	movl	$0, -56(%rbp)
	leaq	-40(%rbp), %rdi
	movl	$70, %esi
	movq	%rax, -120(%rbp)        ## 8-byte Spill
	callq	_push
	leaq	-40(%rbp), %rdi
	movl	$39, %esi
	callq	_push
	movl	$136, %edi
	callq	_malloc
	movq	-32(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movl	$0, 8(%rax)
	movl	$0, -68(%rbp)
LBB35_1:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$15, -68(%rbp)
	jge	LBB35_4
## %bb.2:                               ##   in Loop: Header=BB35_1 Depth=1
	movq	-64(%rbp), %rax
	movslq	-68(%rbp), %rcx
	movq	$0, 16(%rax,%rcx,8)
## %bb.3:                               ##   in Loop: Header=BB35_1 Depth=1
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -68(%rbp)
	jmp	LBB35_1
LBB35_4:
	movl	$56, %edi
	callq	_malloc
	movq	-64(%rbp), %rdi
	movq	%rax, (%rdi)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, 32(%rax)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, 40(%rax)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, (%rax)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, 8(%rax)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	leaq	L_.str.39(%rip), %rdi
	movq	%rdi, 48(%rax)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, 16(%rax)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, 24(%rax)
	movq	-16(%rbp), %rdi
	movq	-48(%rbp), %rsi
	movq	16(%rbp), %rdx
	callq	_get_token
	movq	%rax, -80(%rbp)
	movq	-40(%rbp), %rdi
	callq	_top
	movl	%eax, -84(%rbp)
	movl	$56, -88(%rbp)
LBB35_5:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$70, -84(%rbp)
	je	LBB35_35
## %bb.6:                               ##   in Loop: Header=BB35_5 Depth=1
	movq	-24(%rbp), %rax
	movslq	-84(%rbp), %rcx
	imulq	$232, %rcx, %rcx
	addq	%rcx, %rax
	movq	-80(%rbp), %rcx
	movq	(%rcx), %rdi
	movq	%rax, -128(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	subl	-88(%rbp), %eax
	movslq	%eax, %rcx
	movq	-128(%rbp), %rdi        ## 8-byte Reload
	movl	(%rdi,%rcx,4), %eax
	movl	%eax, -92(%rbp)
	movl	-84(%rbp), %eax
	movq	-80(%rbp), %rcx
	movq	(%rcx), %rdi
	movl	%eax, -132(%rbp)        ## 4-byte Spill
	callq	_string_to_enum
	movl	-132(%rbp), %edx        ## 4-byte Reload
	cmpl	%eax, %edx
	jne	LBB35_8
## %bb.7:                               ##   in Loop: Header=BB35_5 Depth=1
	leaq	-40(%rbp), %rdi
	callq	_pop
	movq	-80(%rbp), %rsi
	leaq	-64(%rbp), %rdi
	callq	_insert_parse_tree
	movq	-32(%rbp), %rsi
	movq	(%rsi), %rdi
	leaq	-64(%rbp), %rsi
	callq	_next_active
	movq	-16(%rbp), %rdi
	movq	-48(%rbp), %rsi
	movq	16(%rbp), %rdx
	callq	_get_token
	movq	%rax, -80(%rbp)
	jmp	LBB35_34
LBB35_8:                                ##   in Loop: Header=BB35_5 Depth=1
	cmpl	$76, -84(%rbp)
	jne	LBB35_10
## %bb.9:                               ##   in Loop: Header=BB35_5 Depth=1
	leaq	-40(%rbp), %rdi
	callq	_pop
	movl	$24, %edi
	callq	_malloc
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	leaq	L_.str.76(%rip), %rdi
	movq	%rdi, (%rax)
	movq	-104(%rbp), %rax
	movq	%rdi, 8(%rax)
	movq	-104(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-104(%rbp), %rsi
	leaq	-64(%rbp), %rdi
	callq	_insert_parse_tree
	movq	-32(%rbp), %rax
	movq	(%rax), %rdi
	leaq	-64(%rbp), %rsi
	callq	_next_active
	jmp	LBB35_33
LBB35_10:                               ##   in Loop: Header=BB35_5 Depth=1
	movslq	-84(%rbp), %rax
	leaq	_variables_array(%rip), %rcx
	movq	(%rcx,%rax,8), %rdi
	callq	_is_terminal
	cmpl	$0, %eax
	je	LBB35_19
## %bb.11:                              ##   in Loop: Header=BB35_5 Depth=1
	movq	-80(%rbp), %rax
	movl	16(%rax), %ecx
	cmpl	-56(%rbp), %ecx
	jbe	LBB35_13
## %bb.12:                              ##   in Loop: Header=BB35_5 Depth=1
	movl	-52(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -52(%rbp)
	movq	-80(%rbp), %rcx
	movl	16(%rcx), %eax
	movl	%eax, -56(%rbp)
	movl	-52(%rbp), %esi
	movq	-80(%rbp), %rcx
	movl	16(%rcx), %edx
	movslq	-84(%rbp), %rcx
	leaq	_variables_array(%rip), %rdi
	movq	(%rdi,%rcx,8), %rcx
	movq	-80(%rbp), %rdi
	movq	(%rdi), %r8
	leaq	L_.str.148(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -136(%rbp)        ## 4-byte Spill
LBB35_13:                               ##   in Loop: Header=BB35_5 Depth=1
	movl	$0, -108(%rbp)
	movq	-16(%rbp), %rdi
	movq	-48(%rbp), %rsi
	movq	16(%rbp), %rdx
	callq	_get_token
	movq	%rax, -80(%rbp)
## %bb.14:                              ##   in Loop: Header=BB35_5 Depth=1
	movq	-80(%rbp), %rax
	movq	(%rax), %rdi
	callq	_string_to_enum
	movl	%eax, -108(%rbp)
	cmpl	-84(%rbp), %eax
	je	LBB35_18
## %bb.15:                              ##   in Loop: Header=BB35_5 Depth=1
	cmpl	$70, -108(%rbp)
	jne	LBB35_17
## %bb.16:                              ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_18
LBB35_17:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_18
LBB35_18:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_5
LBB35_19:                               ##   in Loop: Header=BB35_5 Depth=1
	movq	-24(%rbp), %rax
	movslq	-84(%rbp), %rcx
	imulq	$232, %rcx, %rcx
	addq	%rcx, %rax
	movq	-80(%rbp), %rcx
	movq	(%rcx), %rdi
	movq	%rax, -144(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	subl	-88(%rbp), %eax
	movslq	%eax, %rcx
	movq	-144(%rbp), %rdi        ## 8-byte Reload
	cmpl	$-1, (%rdi,%rcx,4)
	jne	LBB35_28
## %bb.20:                              ##   in Loop: Header=BB35_5 Depth=1
	movq	-80(%rbp), %rax
	movl	16(%rax), %ecx
	cmpl	-56(%rbp), %ecx
	jbe	LBB35_22
## %bb.21:                              ##   in Loop: Header=BB35_5 Depth=1
	movl	-52(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -52(%rbp)
	movq	-80(%rbp), %rcx
	movl	16(%rcx), %eax
	movl	%eax, -56(%rbp)
	movl	-52(%rbp), %esi
	movq	-80(%rbp), %rcx
	movl	16(%rcx), %edx
	movslq	-84(%rbp), %rcx
	leaq	_variables_array(%rip), %rdi
	movq	(%rdi,%rcx,8), %rcx
	movq	-80(%rbp), %rdi
	movq	(%rdi), %r8
	leaq	L_.str.149(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -148(%rbp)        ## 4-byte Spill
LBB35_22:                               ##   in Loop: Header=BB35_5 Depth=1
	movl	$0, -112(%rbp)
	movq	-16(%rbp), %rdi
	movq	-48(%rbp), %rsi
	movq	16(%rbp), %rdx
	callq	_get_token
	movq	%rax, -80(%rbp)
## %bb.23:                              ##   in Loop: Header=BB35_5 Depth=1
	movq	-24(%rbp), %rax
	movslq	-84(%rbp), %rcx
	imulq	$232, %rcx, %rcx
	addq	%rcx, %rax
	movq	-80(%rbp), %rcx
	movq	(%rcx), %rdi
	movq	%rax, -160(%rbp)        ## 8-byte Spill
	callq	_string_to_enum
	movl	%eax, -112(%rbp)
	subl	-88(%rbp), %eax
	movslq	%eax, %rcx
	movq	-160(%rbp), %rdi        ## 8-byte Reload
	cmpl	$-1, (%rdi,%rcx,4)
	jne	LBB35_27
## %bb.24:                              ##   in Loop: Header=BB35_5 Depth=1
	cmpl	$70, -112(%rbp)
	jne	LBB35_26
## %bb.25:                              ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_27
LBB35_26:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_27
LBB35_27:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_5
LBB35_28:                               ##   in Loop: Header=BB35_5 Depth=1
	cmpl	$-1, -92(%rbp)
	je	LBB35_30
## %bb.29:                              ##   in Loop: Header=BB35_5 Depth=1
	leaq	-40(%rbp), %rdi
	callq	_pop
	movq	-64(%rbp), %rdi
	movq	-8(%rbp), %rax
	movslq	-92(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	56(%rax), %rdx
	leaq	-40(%rbp), %rsi
	callq	_pushr
	movq	-64(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -64(%rbp)
LBB35_30:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_31
LBB35_31:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_32
LBB35_32:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_33
LBB35_33:                               ##   in Loop: Header=BB35_5 Depth=1
	jmp	LBB35_34
LBB35_34:                               ##   in Loop: Header=BB35_5 Depth=1
	movq	-40(%rbp), %rdi
	callq	_top
	movl	%eax, -84(%rbp)
	jmp	LBB35_5
LBB35_35:
	cmpl	$0, -52(%rbp)
	jne	LBB35_37
## %bb.36:
	leaq	L_.str.150(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$10, %edi
	movl	%eax, -164(%rbp)        ## 4-byte Spill
	callq	_putchar
	movl	%eax, -168(%rbp)        ## 4-byte Spill
	jmp	LBB35_38
LBB35_37:
	movl	-52(%rbp), %esi
	leaq	L_.str.151(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -172(%rbp)        ## 4-byte Spill
LBB35_38:
	addq	$176, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"arithmeticExpr"

L_.str.1:                               ## @.str.1
	.asciz	"arithmeticExpr_lr"

L_.str.2:                               ## @.str.2
	.asciz	"arithmeticOrBooleanExpression"

L_.str.3:                               ## @.str.3
	.asciz	"assignmentStmt"

L_.str.4:                               ## @.str.4
	.asciz	"booleanConst"

L_.str.5:                               ## @.str.5
	.asciz	"caseStmt"

L_.str.6:                               ## @.str.6
	.asciz	"caseStmts"

L_.str.7:                               ## @.str.7
	.asciz	"conditionalStmt"

L_.str.8:                               ## @.str.8
	.asciz	"datatype"

L_.str.9:                               ## @.str.9
	.asciz	"declareStmt"

L_.str.10:                              ## @.str.10
	.asciz	"default_nt"

L_.str.11:                              ## @.str.11
	.asciz	"driverModule"

L_.str.12:                              ## @.str.12
	.asciz	"expression"

L_.str.13:                              ## @.str.13
	.asciz	"factor"

L_.str.14:                              ## @.str.14
	.asciz	"idList"

L_.str.15:                              ## @.str.15
	.asciz	"idList_lr"

L_.str.16:                              ## @.str.16
	.asciz	"index_nt"

L_.str.17:                              ## @.str.17
	.asciz	"input_plist"

L_.str.18:                              ## @.str.18
	.asciz	"input_plist_lr"

L_.str.19:                              ## @.str.19
	.asciz	"ioStmt"

L_.str.20:                              ## @.str.20
	.asciz	"iterativeStmt"

L_.str.21:                              ## @.str.21
	.asciz	"logicalOp"

L_.str.22:                              ## @.str.22
	.asciz	"lvalueARRStmt"

L_.str.23:                              ## @.str.23
	.asciz	"lvalueIDStmt"

L_.str.24:                              ## @.str.24
	.asciz	"module"

L_.str.25:                              ## @.str.25
	.asciz	"moduleDeclaration"

L_.str.26:                              ## @.str.26
	.asciz	"moduleDeclarations"

L_.str.27:                              ## @.str.27
	.asciz	"moduleDef"

L_.str.28:                              ## @.str.28
	.asciz	"moduleReuseStmt"

L_.str.29:                              ## @.str.29
	.asciz	"one_more_opt"

L_.str.30:                              ## @.str.30
	.asciz	"op1"

L_.str.31:                              ## @.str.31
	.asciz	"op2"

L_.str.32:                              ## @.str.32
	.asciz	"opt_expr"

L_.str.33:                              ## @.str.33
	.asciz	"opt_expr_lr"

L_.str.34:                              ## @.str.34
	.asciz	"optional"

L_.str.35:                              ## @.str.35
	.asciz	"otherModules"

L_.str.36:                              ## @.str.36
	.asciz	"output_plist"

L_.str.37:                              ## @.str.37
	.asciz	"output_plist_lr"

L_.str.38:                              ## @.str.38
	.asciz	"printOpt"

L_.str.39:                              ## @.str.39
	.asciz	"program"

L_.str.40:                              ## @.str.40
	.asciz	"range"

L_.str.41:                              ## @.str.41
	.asciz	"rangeArr"

L_.str.42:                              ## @.str.42
	.asciz	"relationalOp"

L_.str.43:                              ## @.str.43
	.asciz	"ret"

L_.str.44:                              ## @.str.44
	.asciz	"simpleStmt"

L_.str.45:                              ## @.str.45
	.asciz	"statement"

L_.str.46:                              ## @.str.46
	.asciz	"statements"

L_.str.47:                              ## @.str.47
	.asciz	"term"

L_.str.48:                              ## @.str.48
	.asciz	"term_lr"

L_.str.49:                              ## @.str.49
	.asciz	"type"

L_.str.50:                              ## @.str.50
	.asciz	"unary_opt"

L_.str.51:                              ## @.str.51
	.asciz	"unaryExpression"

L_.str.52:                              ## @.str.52
	.asciz	"value"

L_.str.53:                              ## @.str.53
	.asciz	"var"

L_.str.54:                              ## @.str.54
	.asciz	"whichId"

L_.str.55:                              ## @.str.55
	.asciz	"whichStmt"

L_.str.56:                              ## @.str.56
	.asciz	"AND"

L_.str.57:                              ## @.str.57
	.asciz	"ARRAY"

L_.str.58:                              ## @.str.58
	.asciz	"ASSIGNOP"

L_.str.59:                              ## @.str.59
	.asciz	"BC"

L_.str.60:                              ## @.str.60
	.asciz	"BO"

L_.str.61:                              ## @.str.61
	.asciz	"BOOLEAN"

L_.str.62:                              ## @.str.62
	.asciz	"BREAK"

L_.str.63:                              ## @.str.63
	.asciz	"CASE"

L_.str.64:                              ## @.str.64
	.asciz	"COLON"

L_.str.65:                              ## @.str.65
	.asciz	"COMMA"

L_.str.66:                              ## @.str.66
	.asciz	"DECLARE"

L_.str.67:                              ## @.str.67
	.asciz	"DEF"

L_.str.68:                              ## @.str.68
	.asciz	"DEFAULT"

L_.str.69:                              ## @.str.69
	.asciz	"DIV"

L_.str.70:                              ## @.str.70
	.asciz	"DOLLAR"

L_.str.71:                              ## @.str.71
	.asciz	"DRIVER"

L_.str.72:                              ## @.str.72
	.asciz	"DRIVERDEF"

L_.str.73:                              ## @.str.73
	.asciz	"DRIVERENDDEF"

L_.str.74:                              ## @.str.74
	.asciz	"END"

L_.str.75:                              ## @.str.75
	.asciz	"ENDDEF"

L_.str.76:                              ## @.str.76
	.asciz	"EPS"

L_.str.77:                              ## @.str.77
	.asciz	"EQ"

L_.str.78:                              ## @.str.78
	.asciz	"FALSE"

L_.str.79:                              ## @.str.79
	.asciz	"FOR"

L_.str.80:                              ## @.str.80
	.asciz	"GE"

L_.str.81:                              ## @.str.81
	.asciz	"GET_VALUE"

L_.str.82:                              ## @.str.82
	.asciz	"GT"

L_.str.83:                              ## @.str.83
	.asciz	"ID"

L_.str.84:                              ## @.str.84
	.asciz	"IN"

L_.str.85:                              ## @.str.85
	.asciz	"INPUT"

L_.str.86:                              ## @.str.86
	.asciz	"INTEGER"

L_.str.87:                              ## @.str.87
	.asciz	"LE"

L_.str.88:                              ## @.str.88
	.asciz	"LT"

L_.str.89:                              ## @.str.89
	.asciz	"MINUS"

L_.str.90:                              ## @.str.90
	.asciz	"MODULE"

L_.str.91:                              ## @.str.91
	.asciz	"MUL"

L_.str.92:                              ## @.str.92
	.asciz	"NE"

L_.str.93:                              ## @.str.93
	.asciz	"NUM"

L_.str.94:                              ## @.str.94
	.asciz	"OF"

L_.str.95:                              ## @.str.95
	.asciz	"OR"

L_.str.96:                              ## @.str.96
	.asciz	"PARAMETERS"

L_.str.97:                              ## @.str.97
	.asciz	"PLUS"

L_.str.98:                              ## @.str.98
	.asciz	"PRINT"

L_.str.99:                              ## @.str.99
	.asciz	"PROGRAM"

L_.str.100:                             ## @.str.100
	.asciz	"RANGEOP"

L_.str.101:                             ## @.str.101
	.asciz	"REAL"

L_.str.102:                             ## @.str.102
	.asciz	"RETURNS"

L_.str.103:                             ## @.str.103
	.asciz	"RNUM"

L_.str.104:                             ## @.str.104
	.asciz	"SEMICOL"

L_.str.105:                             ## @.str.105
	.asciz	"SQBC"

L_.str.106:                             ## @.str.106
	.asciz	"SQBO"

L_.str.107:                             ## @.str.107
	.asciz	"START"

L_.str.108:                             ## @.str.108
	.asciz	"SWITCH"

L_.str.109:                             ## @.str.109
	.asciz	"TAKES"

L_.str.110:                             ## @.str.110
	.asciz	"TRUE"

L_.str.111:                             ## @.str.111
	.asciz	"USE"

L_.str.112:                             ## @.str.112
	.asciz	"WHILE"

L_.str.113:                             ## @.str.113
	.asciz	"WITH"

	.section	__DATA,__data
	.globl	_variables_array        ## @variables_array
	.p2align	4
_variables_array:
	.quad	L_.str
	.quad	L_.str.1
	.quad	L_.str.2
	.quad	L_.str.3
	.quad	L_.str.4
	.quad	L_.str.5
	.quad	L_.str.6
	.quad	L_.str.7
	.quad	L_.str.8
	.quad	L_.str.9
	.quad	L_.str.10
	.quad	L_.str.11
	.quad	L_.str.12
	.quad	L_.str.13
	.quad	L_.str.14
	.quad	L_.str.15
	.quad	L_.str.16
	.quad	L_.str.17
	.quad	L_.str.18
	.quad	L_.str.19
	.quad	L_.str.20
	.quad	L_.str.21
	.quad	L_.str.22
	.quad	L_.str.23
	.quad	L_.str.24
	.quad	L_.str.25
	.quad	L_.str.26
	.quad	L_.str.27
	.quad	L_.str.28
	.quad	L_.str.29
	.quad	L_.str.30
	.quad	L_.str.31
	.quad	L_.str.32
	.quad	L_.str.33
	.quad	L_.str.34
	.quad	L_.str.35
	.quad	L_.str.36
	.quad	L_.str.37
	.quad	L_.str.38
	.quad	L_.str.39
	.quad	L_.str.40
	.quad	L_.str.41
	.quad	L_.str.42
	.quad	L_.str.43
	.quad	L_.str.44
	.quad	L_.str.45
	.quad	L_.str.46
	.quad	L_.str.47
	.quad	L_.str.48
	.quad	L_.str.49
	.quad	L_.str.50
	.quad	L_.str.51
	.quad	L_.str.52
	.quad	L_.str.53
	.quad	L_.str.54
	.quad	L_.str.55
	.quad	L_.str.56
	.quad	L_.str.57
	.quad	L_.str.58
	.quad	L_.str.59
	.quad	L_.str.60
	.quad	L_.str.61
	.quad	L_.str.62
	.quad	L_.str.63
	.quad	L_.str.64
	.quad	L_.str.65
	.quad	L_.str.66
	.quad	L_.str.67
	.quad	L_.str.68
	.quad	L_.str.69
	.quad	L_.str.70
	.quad	L_.str.71
	.quad	L_.str.72
	.quad	L_.str.73
	.quad	L_.str.74
	.quad	L_.str.75
	.quad	L_.str.76
	.quad	L_.str.77
	.quad	L_.str.78
	.quad	L_.str.79
	.quad	L_.str.80
	.quad	L_.str.81
	.quad	L_.str.82
	.quad	L_.str.83
	.quad	L_.str.84
	.quad	L_.str.85
	.quad	L_.str.86
	.quad	L_.str.87
	.quad	L_.str.88
	.quad	L_.str.89
	.quad	L_.str.90
	.quad	L_.str.91
	.quad	L_.str.92
	.quad	L_.str.93
	.quad	L_.str.94
	.quad	L_.str.95
	.quad	L_.str.96
	.quad	L_.str.97
	.quad	L_.str.98
	.quad	L_.str.99
	.quad	L_.str.100
	.quad	L_.str.101
	.quad	L_.str.102
	.quad	L_.str.103
	.quad	L_.str.104
	.quad	L_.str.105
	.quad	L_.str.106
	.quad	L_.str.107
	.quad	L_.str.108
	.quad	L_.str.109
	.quad	L_.str.110
	.quad	L_.str.111
	.quad	L_.str.112
	.quad	L_.str.113

	.section	__TEXT,__cstring,cstring_literals
L_.str.114:                             ## @.str.114
	.asciz	"STACK ERROR: Can't pop empty stack.\n"

L_.str.115:                             ## @.str.115
	.asciz	"%d\t"

L_.str.116:                             ## @.str.116
	.asciz	"----"

L_.str.117:                             ## @.str.117
	.asciz	"YES"

L_.str.118:                             ## @.str.118
	.asciz	"NOPE"

L_.str.119:                             ## @.str.119
	.asciz	"%20s\t%15u\t%20s\t%20s\t%20s\t%20s\t%20s\n"

L_.str.120:                             ## @.str.120
	.asciz	"In is_terminal: NULL String\n"

L_.str.121:                             ## @.str.121
	.asciz	"%s -> "

L_.str.122:                             ## @.str.122
	.asciz	"String to enum failed for %s\n"

L_.str.123:                             ## @.str.123
	.asciz	"%s "

L_.str.124:                             ## @.str.124
	.asciz	"\n"

L_.str.125:                             ## @.str.125
	.asciz	"Follow set: "

L_.str.126:                             ## @.str.126
	.asciz	"\n\t\t\t***********************\t\t\t\n"

L_.str.127:                             ## @.str.127
	.asciz	"FIRST SET\n\n"

L_.str.128:                             ## @.str.128
	.asciz	"first set of %s : "

L_.str.129:                             ## @.str.129
	.asciz	"Terminal: %s, returning\n"

L_.str.130:                             ## @.str.130
	.asciz	"NULL token in populate first"

L___func__.populate_first:              ## @__func__.populate_first
	.asciz	"populate_first"

L_.str.131:                             ## @.str.131
	.asciz	"parser.c"

L_.str.132:                             ## @.str.132
	.asciz	"first_table->fnf[str_to_enum]->first_set_array[MAX_BOOL_ARRAY_SIZE - 1] == 1"

L_.str.133:                             ## @.str.133
	.asciz	"NULL token in populate follow"

L_.str.134:                             ## @.str.134
	.asciz	"%s, "

L_.str.135:                             ## @.str.135
	.asciz	"error\n"

L_.str.136:                             ## @.str.136
	.asciz	"./grammar.txt"

L_.str.137:                             ## @.str.137
	.asciz	"r"

L_.str.138:                             ## @.str.138
	.asciz	"Error opening file at %s. Aborting.\n"

L_.str.139:                             ## @.str.139
	.asciz	"%[^\n]\n"

L_.str.140:                             ## @.str.140
	.asciz	" "

L_.str.141:                             ## @.str.141
	.asciz	"->"

L___func__.multiple_first:              ## @__func__.multiple_first
	.asciz	"multiple_first"

L_.str.142:                             ## @.str.142
	.asciz	"rule < g->num_rules"

L_.str.143:                             ## @.str.143
	.asciz	"%30s"

L_.str.144:                             ## @.str.144
	.asciz	"TABLE"

L_.str.145:                             ## @.str.145
	.asciz	"%15s"

L_.str.146:                             ## @.str.146
	.asciz	"%15d"

L_.str.147:                             ## @.str.147
	.asciz	"Lo, ho gayi parsing error at line %d\n"

L_.str.148:                             ## @.str.148
	.asciz	"Syntax Error #%u at line #%u. Expected token is '%s', but got token '%s'.\n"

L_.str.149:                             ## @.str.149
	.asciz	"Syntax Error #%u at line #%u. Expected non-terminal type '%s', but got token '%s'.\n"

L_.str.150:                             ## @.str.150
	.asciz	"Input source code is syntactically correct.........."

L_.str.151:                             ## @.str.151
	.asciz	"Encountered %d syntax errors.\n"

	.comm	_hash_table,512,4       ## @hash_table

.subsections_via_symbols
