	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_initialize_bool_array  ## -- Begin function initialize_bool_array
	.p2align	4, 0x90
_initialize_bool_array:                 ## @initialize_bool_array
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movl	$0, -12(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$150, -12(%rbp)
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-12(%rbp), %rcx
	movb	$0, (%rax,%rcx)
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB0_1
LBB0_4:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_or                     ## -- Begin function or
	.p2align	4, 0x90
_or:                                    ## @or
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
	movl	$150, %edi
	callq	_malloc
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$149, -28(%rbp)
	jge	LBB1_4
## %bb.2:                               ##   in Loop: Header=BB1_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %edi
	orl	%edi, %esi
	cmpl	$0, %esi
	setne	%dl
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	andb	$1, %dl
	movb	%dl, (%rax,%rcx)
## %bb.3:                               ##   in Loop: Header=BB1_1 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB1_1
LBB1_4:
	movq	-24(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_or_and_store           ## -- Begin function or_and_store
	.p2align	4, 0x90
_or_and_store:                          ## @or_and_store
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, -20(%rbp)
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$149, -20(%rbp)
	jge	LBB2_4
## %bb.2:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-20(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	movq	-16(%rbp), %rax
	movslq	-20(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %edi
	orl	%edi, %esi
	cmpl	$0, %esi
	setne	%dl
	movq	-8(%rbp), %rax
	movslq	-20(%rbp), %rcx
	andb	$1, %dl
	movb	%dl, (%rax,%rcx)
## %bb.3:                               ##   in Loop: Header=BB2_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB2_1
LBB2_4:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_and                    ## -- Begin function and
	.p2align	4, 0x90
_and:                                   ## @and
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
	movl	$150, %edi
	callq	_malloc
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
LBB3_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$149, -28(%rbp)
	jge	LBB3_4
## %bb.2:                               ##   in Loop: Header=BB3_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %edi
	andl	%edi, %esi
	cmpl	$0, %esi
	setne	%dl
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	andb	$1, %dl
	movb	%dl, (%rax,%rcx)
## %bb.3:                               ##   in Loop: Header=BB3_1 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB3_1
LBB3_4:
	movq	-24(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_xor                    ## -- Begin function xor
	.p2align	4, 0x90
_xor:                                   ## @xor
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
	movl	$150, %edi
	callq	_malloc
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$149, -28(%rbp)
	jge	LBB4_4
## %bb.2:                               ##   in Loop: Header=BB4_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %edi
	xorl	%edi, %esi
	cmpl	$0, %esi
	setne	%dl
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	andb	$1, %dl
	movb	%dl, (%rax,%rcx)
## %bb.3:                               ##   in Loop: Header=BB4_1 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB4_1
LBB4_4:
	movq	-24(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_not                    ## -- Begin function not
	.p2align	4, 0x90
_not:                                   ## @not
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	$150, %edi
	callq	_malloc
	movq	%rax, -16(%rbp)
	movl	$0, -20(%rbp)
LBB5_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$149, -20(%rbp)
	jge	LBB5_4
## %bb.2:                               ##   in Loop: Header=BB5_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-20(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	xorl	$-1, %esi
	cmpl	$0, %esi
	setne	%dl
	movq	-16(%rbp), %rax
	movslq	-20(%rbp), %rcx
	andb	$1, %dl
	movb	%dl, (%rax,%rcx)
## %bb.3:                               ##   in Loop: Header=BB5_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB5_1
LBB5_4:
	movq	-16(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_print_bool             ## -- Begin function print_bool
	.p2align	4, 0x90
_print_bool:                            ## @print_bool
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
LBB6_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-16(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB6_4
## %bb.2:                               ##   in Loop: Header=BB6_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-16(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	andb	$1, %dl
	movzbl	%dl, %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -20(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB6_1 Depth=1
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	LBB6_1
LBB6_4:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d "

L_.str.1:                               ## @.str.1
	.asciz	"\n"


.subsections_via_symbols
