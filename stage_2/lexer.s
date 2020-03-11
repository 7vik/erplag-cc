	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_print_lexeme           ## -- Begin function print_lexeme
	.p2align	4, 0x90
_print_lexeme:                          ## @print_lexeme
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	LBB0_2
## %bb.1:
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	jmp	LBB0_3
LBB0_2:
	movq	-8(%rbp), %rax
	movq	(%rax), %rsi
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	16(%rax), %ecx
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -16(%rbp)         ## 4-byte Spill
LBB0_3:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_retract                ## -- Begin function retract
	.p2align	4, 0x90
_retract:                               ## @retract
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	cmpl	$0, 1028(%rdi)
	jne	LBB1_2
## %bb.1:
	movq	-8(%rbp), %rax
	movl	$1, %ecx
	subl	1032(%rax), %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, 1032(%rax)
	movq	-8(%rbp), %rax
	movl	$511, 1028(%rax)        ## imm = 0x1FF
	movq	-8(%rbp), %rax
	movl	$0, 1036(%rax)
	jmp	LBB1_3
LBB1_2:
	movq	-8(%rbp), %rax
	movl	1028(%rax), %ecx
	addl	$-1, %ecx
	movl	%ecx, 1028(%rax)
LBB1_3:
	movq	-8(%rbp), %rax
	movl	1028(%rax), %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, 1024(%rax)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_get_token              ## -- Begin function get_token
	.p2align	4, 0x90
_get_token:                             ## @get_token
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$656, %rsp              ## imm = 0x290
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movl	$24, %edi
	callq	_malloc
	movq	%rax, -40(%rbp)
	movl	$21, %edi
	callq	_malloc
	movq	%rax, -56(%rbp)
	movl	$0, -76(%rbp)
	movl	$0, -80(%rbp)
	movl	$0, -84(%rbp)
	movl	$0, -88(%rbp)
	movl	$0, -92(%rbp)
LBB2_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB2_9 Depth 2
                                        ##     Child Loop BB2_34 Depth 2
                                        ##     Child Loop BB2_128 Depth 2
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$-1, %ecx
	je	LBB2_153
## %bb.2:                               ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-41(%rbp), %eax
	cmpl	$10, %eax
	jne	LBB2_4
## %bb.3:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, (%rax)
	jmp	LBB2_1
LBB2_4:                                 ##   in Loop: Header=BB2_1 Depth=1
	movl	$0, -72(%rbp)
	movsbl	-41(%rbp), %eax
	cmpl	$65, %eax
	jl	LBB2_6
## %bb.5:                               ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-41(%rbp), %eax
	cmpl	$90, %eax
	jle	LBB2_8
LBB2_6:                                 ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-41(%rbp), %eax
	cmpl	$97, %eax
	jl	LBB2_31
## %bb.7:                               ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-41(%rbp), %eax
	cmpl	$122, %eax
	jg	LBB2_31
LBB2_8:                                 ##   in Loop: Header=BB2_1 Depth=1
	movb	-41(%rbp), %al
	movq	-56(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	movl	$1, -96(%rbp)
LBB2_9:                                 ##   Parent Loop BB2_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	xorl	%ecx, %ecx
	movb	%cl, %dl
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$-1, %ecx
	movb	%dl, -129(%rbp)         ## 1-byte Spill
	je	LBB2_13
## %bb.10:                              ##   in Loop: Header=BB2_9 Depth=2
	movsbl	-41(%rbp), %edi
	callq	_isalnum
	cmpl	$0, %eax
	movb	$1, %cl
	movb	%cl, -130(%rbp)         ## 1-byte Spill
	jne	LBB2_12
## %bb.11:                              ##   in Loop: Header=BB2_9 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$95, %eax
	sete	%cl
	movb	%cl, -130(%rbp)         ## 1-byte Spill
LBB2_12:                                ##   in Loop: Header=BB2_9 Depth=2
	movb	-130(%rbp), %al         ## 1-byte Reload
	movb	%al, -129(%rbp)         ## 1-byte Spill
LBB2_13:                                ##   in Loop: Header=BB2_9 Depth=2
	movb	-129(%rbp), %al         ## 1-byte Reload
	testb	$1, %al
	jne	LBB2_14
	jmp	LBB2_21
LBB2_14:                                ##   in Loop: Header=BB2_9 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$10, %eax
	jne	LBB2_16
## %bb.15:                              ##   in Loop: Header=BB2_9 Depth=2
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, (%rax)
LBB2_16:                                ##   in Loop: Header=BB2_9 Depth=2
	cmpl	$20, -72(%rbp)
	jl	LBB2_20
## %bb.17:                              ##   in Loop: Header=BB2_9 Depth=2
	cmpl	$1, -96(%rbp)
	jne	LBB2_19
## %bb.18:                              ##   in Loop: Header=BB2_9 Depth=2
	movl	$0, -96(%rbp)
LBB2_19:                                ##   in Loop: Header=BB2_9 Depth=2
	movb	-41(%rbp), %al
	movq	-56(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	jmp	LBB2_9
LBB2_20:                                ##   in Loop: Header=BB2_9 Depth=2
	movb	-41(%rbp), %al
	movq	-56(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	jmp	LBB2_9
LBB2_21:                                ##   in Loop: Header=BB2_1 Depth=1
	cmpl	$0, -96(%rbp)
	jne	LBB2_23
## %bb.22:                              ##   in Loop: Header=BB2_1 Depth=1
	movq	-24(%rbp), %rdi
	callq	_retract
	movq	-56(%rbp), %rdi
	movslq	-72(%rbp), %rax
	movb	$0, (%rdi,%rax)
	movq	-32(%rbp), %rax
	movl	(%rax), %esi
	movq	-56(%rbp), %rdx
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -136(%rbp)        ## 4-byte Spill
	jmp	LBB2_1
LBB2_23:
	movq	-56(%rbp), %rax
	movslq	-72(%rbp), %rcx
	movb	$0, (%rax,%rcx)
	movq	-56(%rbp), %rdi
	callq	_strlen
	movq	%rax, %rdi
	callq	_malloc
	movq	$-1, %rdx
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rdi
	movq	-56(%rbp), %rsi
	callq	___strcpy_chk
	movl	$22, %edi
	movq	%rax, -144(%rbp)        ## 8-byte Spill
	callq	_malloc
	movq	_hash_table@GOTPCREL(%rip), %rsi
	movq	-40(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	-104(%rbp), %rdi
	callq	_search
	cmpl	$1, %eax
	jne	LBB2_29
## %bb.24:
	movq	-56(%rbp), %rdi
	callq	_strlen
	addq	$1, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -112(%rbp)
	movl	$0, -116(%rbp)
LBB2_25:                                ## =>This Inner Loop Header: Depth=1
	movslq	-116(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	%rax, -152(%rbp)        ## 8-byte Spill
	callq	_strlen
	movq	-152(%rbp), %rdi        ## 8-byte Reload
	cmpq	%rax, %rdi
	ja	LBB2_28
## %bb.26:                              ##   in Loop: Header=BB2_25 Depth=1
	movq	-56(%rbp), %rax
	movslq	-116(%rbp), %rcx
	movsbl	(%rax,%rcx), %edi
	callq	_toupper
	movb	%al, %dl
	movq	-112(%rbp), %rcx
	movslq	-116(%rbp), %rsi
	movb	%dl, (%rcx,%rsi)
## %bb.27:                              ##   in Loop: Header=BB2_25 Depth=1
	movl	-116(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -116(%rbp)
	jmp	LBB2_25
LBB2_28:
	movq	$-1, %rdx
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	movq	-112(%rbp), %rsi
	callq	___strcpy_chk
	movq	%rax, -160(%rbp)        ## 8-byte Spill
	jmp	LBB2_30
LBB2_29:
	movq	$-1, %rdx
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.3(%rip), %rsi
	callq	___strcpy_chk
	movq	%rax, -168(%rbp)        ## 8-byte Spill
LBB2_30:
	movq	-104(%rbp), %rax
	movq	-40(%rbp), %rcx
	movq	%rax, 8(%rcx)
	movq	-24(%rbp), %rdi
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 16(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_31:                                ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-41(%rbp), %eax
	cmpl	$48, %eax
	jl	LBB2_90
## %bb.32:                              ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-41(%rbp), %eax
	cmpl	$57, %eax
	jg	LBB2_90
## %bb.33:                              ##   in Loop: Header=BB2_1 Depth=1
	movl	$101, %edi
	movl	$1, %esi
	callq	_calloc
	movq	%rax, -64(%rbp)
	movb	-41(%rbp), %cl
	movq	-64(%rbp), %rax
	movslq	-72(%rbp), %rsi
	movb	%cl, (%rax,%rsi)
	movl	-72(%rbp), %edx
	addl	$1, %edx
	movl	%edx, -72(%rbp)
	movl	$1, -80(%rbp)
LBB2_34:                                ##   Parent Loop BB2_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$-1, %ecx
	je	LBB2_83
## %bb.35:                              ##   in Loop: Header=BB2_34 Depth=2
	movl	-80(%rbp), %eax
	decl	%eax
	movl	%eax, %ecx
	subl	$5, %eax
	movq	%rcx, -176(%rbp)        ## 8-byte Spill
	movl	%eax, -180(%rbp)        ## 4-byte Spill
	ja	LBB2_80
## %bb.157:                             ##   in Loop: Header=BB2_34 Depth=2
	leaq	LJTI2_1(%rip), %rax
	movq	-176(%rbp), %rcx        ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB2_36:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$48, %eax
	jl	LBB2_39
## %bb.37:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$57, %eax
	jg	LBB2_39
## %bb.38:                              ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	jmp	LBB2_46
LBB2_39:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$46, %eax
	jne	LBB2_44
## %bb.40:                              ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movb	%al, -65(%rbp)
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$46, %ecx
	jne	LBB2_42
## %bb.41:                              ##   in Loop: Header=BB2_34 Depth=2
	movq	-24(%rbp), %rdi
	callq	_retract
	movl	$1, -88(%rbp)
	movl	$1, -92(%rbp)
	movl	$0, -80(%rbp)
	jmp	LBB2_80
LBB2_42:                                ##   in Loop: Header=BB2_34 Depth=2
	movq	-24(%rbp), %rdi
	callq	_retract
	movb	-65(%rbp), %al
	movq	-64(%rbp), %rdi
	movslq	-72(%rbp), %rcx
	movb	%al, (%rdi,%rcx)
	movl	-72(%rbp), %edx
	addl	$1, %edx
	movl	%edx, -72(%rbp)
	movl	$2, -80(%rbp)
## %bb.43:                              ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_45
LBB2_44:                                ##   in Loop: Header=BB2_34 Depth=2
	movl	$1, -88(%rbp)
	movl	$1, -92(%rbp)
	movl	$0, -80(%rbp)
	jmp	LBB2_80
LBB2_45:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_46
LBB2_46:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_80
LBB2_47:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$48, %eax
	jl	LBB2_50
## %bb.48:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$57, %eax
	jg	LBB2_50
## %bb.49:                              ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	movl	$3, -80(%rbp)
	jmp	LBB2_51
LBB2_50:                                ##   in Loop: Header=BB2_34 Depth=2
	movq	-64(%rbp), %rax
	movslq	-72(%rbp), %rcx
	movb	$0, (%rax,%rcx)
	movl	$0, -80(%rbp)
	jmp	LBB2_80
LBB2_51:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_80
LBB2_52:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$48, %eax
	jl	LBB2_55
## %bb.53:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$57, %eax
	jg	LBB2_55
## %bb.54:                              ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	jmp	LBB2_60
LBB2_55:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$101, %eax
	je	LBB2_57
## %bb.56:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$69, %eax
	jne	LBB2_58
LBB2_57:                                ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	movl	$4, -80(%rbp)
	jmp	LBB2_59
LBB2_58:                                ##   in Loop: Header=BB2_34 Depth=2
	movl	$1, -88(%rbp)
	movl	$0, -80(%rbp)
	jmp	LBB2_80
LBB2_59:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_60
LBB2_60:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_80
LBB2_61:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$48, %eax
	jl	LBB2_64
## %bb.62:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$57, %eax
	jg	LBB2_64
## %bb.63:                              ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	movl	$6, -80(%rbp)
	jmp	LBB2_69
LBB2_64:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$43, %eax
	je	LBB2_66
## %bb.65:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$45, %eax
	jne	LBB2_67
LBB2_66:                                ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	movl	$5, -80(%rbp)
	jmp	LBB2_68
LBB2_67:                                ##   in Loop: Header=BB2_34 Depth=2
	movq	-64(%rbp), %rax
	movslq	-72(%rbp), %rcx
	movb	$0, (%rax,%rcx)
	movl	$0, -80(%rbp)
	jmp	LBB2_80
LBB2_68:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_69
LBB2_69:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_80
LBB2_70:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$48, %eax
	jl	LBB2_73
## %bb.71:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$57, %eax
	jg	LBB2_73
## %bb.72:                              ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	movl	$6, -80(%rbp)
	jmp	LBB2_74
LBB2_73:                                ##   in Loop: Header=BB2_34 Depth=2
	movq	-64(%rbp), %rax
	movslq	-72(%rbp), %rcx
	movb	$0, (%rax,%rcx)
	movl	$0, -80(%rbp)
	jmp	LBB2_80
LBB2_74:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_80
LBB2_75:                                ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$48, %eax
	jl	LBB2_78
## %bb.76:                              ##   in Loop: Header=BB2_34 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$57, %eax
	jg	LBB2_78
## %bb.77:                              ##   in Loop: Header=BB2_34 Depth=2
	movb	-41(%rbp), %al
	movq	-64(%rbp), %rcx
	movslq	-72(%rbp), %rdx
	movb	%al, (%rcx,%rdx)
	movl	-72(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -72(%rbp)
	jmp	LBB2_79
LBB2_78:                                ##   in Loop: Header=BB2_34 Depth=2
	movl	$1, -88(%rbp)
	movl	$0, -80(%rbp)
	jmp	LBB2_80
LBB2_79:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_80
LBB2_80:                                ##   in Loop: Header=BB2_34 Depth=2
	cmpl	$0, -80(%rbp)
	jne	LBB2_82
## %bb.81:                              ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_83
LBB2_82:                                ##   in Loop: Header=BB2_34 Depth=2
	jmp	LBB2_34
LBB2_83:                                ##   in Loop: Header=BB2_1 Depth=1
	cmpl	$1, -88(%rbp)
	jne	LBB2_88
## %bb.84:
	movq	-64(%rbp), %rdi
	movl	-72(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rsi
	callq	_realloc
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdi
	callq	_strlen
	movq	%rax, %rdi
	callq	_malloc
	movq	$-1, %rdx
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rdi
	movq	-64(%rbp), %rsi
	callq	___strcpy_chk
	movl	$22, %edi
	movq	%rax, -192(%rbp)        ## 8-byte Spill
	callq	_malloc
	movq	-40(%rbp), %rdx
	movq	%rax, (%rdx)
	cmpl	$1, -92(%rbp)
	jne	LBB2_86
## %bb.85:
	movq	$-1, %rdx
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.4(%rip), %rsi
	callq	___strcpy_chk
	movq	%rax, -200(%rbp)        ## 8-byte Spill
	jmp	LBB2_87
LBB2_86:
	movq	$-1, %rdx
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.5(%rip), %rsi
	callq	___strcpy_chk
	movq	%rax, -208(%rbp)        ## 8-byte Spill
LBB2_87:
	movq	-128(%rbp), %rax
	movq	-40(%rbp), %rcx
	movq	%rax, 8(%rcx)
	movq	-24(%rbp), %rdi
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 16(%rax)
	movl	$0, -92(%rbp)
	movl	$0, -88(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_88:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-32(%rbp), %rax
	movl	(%rax), %esi
	movq	-64(%rbp), %rdx
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rdi
	movl	%eax, -212(%rbp)        ## 4-byte Spill
	callq	_retract
## %bb.89:                              ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_151
LBB2_90:                                ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-41(%rbp), %eax
	addl	$-9, %eax
	movl	%eax, %ecx
	subl	$84, %eax
	movq	%rcx, -224(%rbp)        ## 8-byte Spill
	movl	%eax, -228(%rbp)        ## 4-byte Spill
	ja	LBB2_149
## %bb.155:                             ##   in Loop: Header=BB2_1 Depth=1
	leaq	LJTI2_0(%rip), %rax
	movq	-224(%rbp), %rcx        ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB2_91:
	movl	$4, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.7(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.8(%rip), %rsi
	movq	%rax, -240(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -248(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_92:
	movl	$5, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.9(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.10(%rip), %rsi
	movq	%rax, -256(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -264(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_93:
	movl	$3, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.11(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.12(%rip), %rsi
	movq	%rax, -272(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -280(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_94:
	movl	$4, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.13(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.14(%rip), %rsi
	movq	%rax, -288(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -296(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_95:
	movl	$4, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.15(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.16(%rip), %rsi
	movq	%rax, -304(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -312(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_96:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.17(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.18(%rip), %rsi
	movq	%rax, -320(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -328(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_97:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.19(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.20(%rip), %rsi
	movq	%rax, -336(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -344(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_98:
	movl	$7, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.21(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.22(%rip), %rsi
	movq	%rax, -352(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -360(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_99:
	movl	$5, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.23(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.24(%rip), %rsi
	movq	%rax, -368(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -376(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_100:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$61, %ecx
	jne	LBB2_102
## %bb.101:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.25(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.26(%rip), %rsi
	movq	%rax, -384(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -392(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_102:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-32(%rbp), %rax
	movl	(%rax), %esi
	leaq	L_.str.27(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rdi
	movl	%eax, -396(%rbp)        ## 4-byte Spill
	callq	_retract
	jmp	LBB2_1
LBB2_103:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$61, %ecx
	jne	LBB2_105
## %bb.104:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.28(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.29(%rip), %rsi
	movq	%rax, -408(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -416(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_105:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-32(%rbp), %rax
	movl	(%rax), %esi
	leaq	L_.str.30(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rdi
	movl	%eax, -420(%rbp)        ## 4-byte Spill
	callq	_retract
	jmp	LBB2_1
LBB2_106:
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$61, %ecx
	jne	LBB2_108
## %bb.107:
	movl	$8, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.31(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.32(%rip), %rsi
	movq	%rax, -432(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -440(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_108:
	movl	$5, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.33(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.34(%rip), %rsi
	movq	%rax, -448(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdi
	movq	%rax, -456(%rbp)        ## 8-byte Spill
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, 16(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_109:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$46, %ecx
	jne	LBB2_111
## %bb.110:
	movl	$7, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.35(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.36(%rip), %rsi
	movq	%rax, -464(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -472(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_111:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-32(%rbp), %rax
	movl	(%rax), %esi
	leaq	L_.str.37(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rdi
	movl	%eax, -476(%rbp)        ## 4-byte Spill
	callq	_retract
	jmp	LBB2_1
LBB2_112:
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$61, %ecx
	jne	LBB2_114
## %bb.113:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.38(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.39(%rip), %rsi
	movq	%rax, -488(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -496(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_114:
	movsbl	-41(%rbp), %eax
	cmpl	$60, %eax
	jne	LBB2_118
## %bb.115:
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$60, %ecx
	jne	LBB2_117
## %bb.116:
	movl	$9, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$3, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.40(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.41(%rip), %rsi
	movq	%rax, -504(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -512(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_117:
	movl	$3, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.42(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.43(%rip), %rsi
	movq	%rax, -520(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdi
	movq	%rax, -528(%rbp)        ## 8-byte Spill
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, 16(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_118:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.44(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.45(%rip), %rsi
	movq	%rax, -536(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdi
	movq	%rax, -544(%rbp)        ## 8-byte Spill
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, 16(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_119:
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$61, %ecx
	jne	LBB2_121
## %bb.120:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.46(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.47(%rip), %rsi
	movq	%rax, -552(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -560(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_121:
	movsbl	-41(%rbp), %eax
	cmpl	$62, %eax
	jne	LBB2_125
## %bb.122:
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$62, %ecx
	jne	LBB2_124
## %bb.123:
	movl	$12, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$3, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.48(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.49(%rip), %rsi
	movq	%rax, -568(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdx
	movl	1028(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movl	%ecx, 1024(%rdx)
	movq	-32(%rbp), %rdx
	movl	(%rdx), %ecx
	movq	-40(%rbp), %rdx
	movl	%ecx, 16(%rdx)
	movq	-40(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -576(%rbp)        ## 8-byte Spill
	jmp	LBB2_154
LBB2_124:
	movl	$6, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$2, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.50(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.51(%rip), %rsi
	movq	%rax, -584(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdi
	movq	%rax, -592(%rbp)        ## 8-byte Spill
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, 16(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_125:
	movl	$2, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.52(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.53(%rip), %rsi
	movq	%rax, -600(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdi
	movq	%rax, -608(%rbp)        ## 8-byte Spill
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, 16(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_126:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movb	-41(%rbp), %al
	subb	$42, %al
	movb	%al, -609(%rbp)         ## 1-byte Spill
	jne	LBB2_146
	jmp	LBB2_127
LBB2_127:                               ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_128
LBB2_128:                               ##   Parent Loop BB2_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movq	-16(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	_get_stream
	movb	%al, -41(%rbp)
	movsbl	%al, %ecx
	cmpl	$-1, %ecx
	je	LBB2_145
## %bb.129:                             ##   in Loop: Header=BB2_128 Depth=2
	movl	-76(%rbp), %eax
	testl	%eax, %eax
	movl	%eax, -616(%rbp)        ## 4-byte Spill
	je	LBB2_130
	jmp	LBB2_156
LBB2_156:                               ##   in Loop: Header=BB2_128 Depth=2
	movl	-616(%rbp), %eax        ## 4-byte Reload
	subl	$1, %eax
	movl	%eax, -620(%rbp)        ## 4-byte Spill
	je	LBB2_136
	jmp	LBB2_142
LBB2_130:                               ##   in Loop: Header=BB2_128 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$42, %eax
	jne	LBB2_132
## %bb.131:                             ##   in Loop: Header=BB2_128 Depth=2
	movl	$1, -76(%rbp)
	jmp	LBB2_135
LBB2_132:                               ##   in Loop: Header=BB2_128 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$10, %eax
	jne	LBB2_134
## %bb.133:                             ##   in Loop: Header=BB2_128 Depth=2
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movq	-32(%rbp), %rax
	movl	%ecx, (%rax)
LBB2_134:                               ##   in Loop: Header=BB2_128 Depth=2
	jmp	LBB2_135
LBB2_135:                               ##   in Loop: Header=BB2_128 Depth=2
	jmp	LBB2_142
LBB2_136:                               ##   in Loop: Header=BB2_128 Depth=2
	movsbl	-41(%rbp), %eax
	cmpl	$42, %eax
	jne	LBB2_138
## %bb.137:                             ##   in Loop: Header=BB2_128 Depth=2
	movl	$0, -76(%rbp)
	movl	$1, -84(%rbp)
	jmp	LBB2_142
LBB2_138:                               ##   in Loop: Header=BB2_128 Depth=2
	movl	$0, -76(%rbp)
	movsbl	-41(%rbp), %eax
	cmpl	$10, %eax
	jne	LBB2_140
## %bb.139:                             ##   in Loop: Header=BB2_128 Depth=2
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movq	-32(%rbp), %rax
	movl	%ecx, (%rax)
LBB2_140:                               ##   in Loop: Header=BB2_128 Depth=2
	jmp	LBB2_141
LBB2_141:                               ##   in Loop: Header=BB2_128 Depth=2
	jmp	LBB2_142
LBB2_142:                               ##   in Loop: Header=BB2_128 Depth=2
	cmpl	$1, -84(%rbp)
	jne	LBB2_144
## %bb.143:                             ##   in Loop: Header=BB2_1 Depth=1
	movl	$0, -84(%rbp)
	jmp	LBB2_145
LBB2_144:                               ##   in Loop: Header=BB2_128 Depth=2
	jmp	LBB2_128
LBB2_145:                               ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_147
LBB2_146:
	movl	$3, %edi
	callq	_malloc
	movq	-40(%rbp), %rdi
	movq	%rax, (%rdi)
	movl	$1, %edi
	callq	_malloc
	movq	$-1, %rdx
	movq	-40(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdi
	leaq	L_.str.54(%rip), %rsi
	callq	___strcpy_chk
	movq	$-1, %rdx
	movq	-40(%rbp), %rsi
	movq	8(%rsi), %rdi
	leaq	L_.str.55(%rip), %rsi
	movq	%rax, -632(%rbp)        ## 8-byte Spill
	callq	___strcpy_chk
	movq	-24(%rbp), %rdi
	movq	%rax, -640(%rbp)        ## 8-byte Spill
	callq	_retract
	movq	-32(%rbp), %rax
	movl	(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, 16(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB2_154
LBB2_147:                               ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_150
LBB2_148:                               ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_150
LBB2_149:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-32(%rbp), %rax
	movl	(%rax), %esi
	movsbl	-41(%rbp), %edx
	leaq	L_.str.56(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -644(%rbp)        ## 4-byte Spill
LBB2_150:                               ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_151
LBB2_151:                               ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_152
LBB2_152:                               ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_1
LBB2_153:
	movq	-40(%rbp), %rax
	leaq	L_.str.57(%rip), %rcx
	movq	%rcx, (%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB2_154:
	movq	-8(%rbp), %rax
	addq	$656, %rsp              ## imm = 0x290
	popq	%rbp
	retq
	.cfi_endproc
	.p2align	2, 0x90
	.data_region jt32
.set L2_0_set_148, LBB2_148-LJTI2_0
.set L2_0_set_149, LBB2_149-LJTI2_0
.set L2_0_set_103, LBB2_103-LJTI2_0
.set L2_0_set_96, LBB2_96-LJTI2_0
.set L2_0_set_97, LBB2_97-LJTI2_0
.set L2_0_set_126, LBB2_126-LJTI2_0
.set L2_0_set_91, LBB2_91-LJTI2_0
.set L2_0_set_99, LBB2_99-LJTI2_0
.set L2_0_set_92, LBB2_92-LJTI2_0
.set L2_0_set_109, LBB2_109-LJTI2_0
.set L2_0_set_93, LBB2_93-LJTI2_0
.set L2_0_set_106, LBB2_106-LJTI2_0
.set L2_0_set_98, LBB2_98-LJTI2_0
.set L2_0_set_112, LBB2_112-LJTI2_0
.set L2_0_set_100, LBB2_100-LJTI2_0
.set L2_0_set_119, LBB2_119-LJTI2_0
.set L2_0_set_94, LBB2_94-LJTI2_0
.set L2_0_set_95, LBB2_95-LJTI2_0
LJTI2_0:
	.long	L2_0_set_148
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_148
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_148
	.long	L2_0_set_103
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_96
	.long	L2_0_set_97
	.long	L2_0_set_126
	.long	L2_0_set_91
	.long	L2_0_set_99
	.long	L2_0_set_92
	.long	L2_0_set_109
	.long	L2_0_set_93
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_106
	.long	L2_0_set_98
	.long	L2_0_set_112
	.long	L2_0_set_100
	.long	L2_0_set_119
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_149
	.long	L2_0_set_94
	.long	L2_0_set_149
	.long	L2_0_set_95
.set L2_1_set_36, LBB2_36-LJTI2_1
.set L2_1_set_47, LBB2_47-LJTI2_1
.set L2_1_set_52, LBB2_52-LJTI2_1
.set L2_1_set_61, LBB2_61-LJTI2_1
.set L2_1_set_70, LBB2_70-LJTI2_1
.set L2_1_set_75, LBB2_75-LJTI2_1
LJTI2_1:
	.long	L2_1_set_36
	.long	L2_1_set_47
	.long	L2_1_set_52
	.long	L2_1_set_61
	.long	L2_1_set_70
	.long	L2_1_set_75
	.end_data_region
                                        ## -- End function
	.globl	_get_stream             ## -- Begin function get_stream
	.p2align	4, 0x90
_get_stream:                            ## @get_stream
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
	movq	-16(%rbp), %rsi
	cmpl	$0, 1032(%rsi)
	jne	LBB3_2
## %bb.1:
	movq	-16(%rbp), %rax
	movq	-16(%rbp), %rcx
	movslq	1028(%rcx), %rcx
	movb	(%rax,%rcx), %dl
	movb	%dl, -17(%rbp)
	jmp	LBB3_3
LBB3_2:
	movq	-16(%rbp), %rax
	movq	-16(%rbp), %rcx
	movslq	1028(%rcx), %rcx
	movb	512(%rax,%rcx), %dl
	movb	%dl, -17(%rbp)
LBB3_3:
	movq	-16(%rbp), %rax
	cmpl	$511, 1028(%rax)        ## imm = 0x1FF
	jne	LBB3_9
## %bb.4:
	movq	-16(%rbp), %rax
	cmpl	$1, 1036(%rax)
	jne	LBB3_9
## %bb.5:
	movq	-16(%rbp), %rax
	cmpl	$0, 1032(%rax)
	jne	LBB3_7
## %bb.6:
	movq	$-1, %rcx
	movq	-16(%rbp), %rax
	addq	$512, %rax              ## imm = 0x200
	movq	%rax, %rdi
	movl	$4294967295, %esi       ## imm = 0xFFFFFFFF
	movl	$512, %edx              ## imm = 0x200
	callq	___memset_chk
	movq	-16(%rbp), %rcx
	addq	$512, %rcx              ## imm = 0x200
	movq	-8(%rbp), %rdx
	movq	%rcx, %rdi
	movl	$1, %esi
	movl	$512, %ecx              ## imm = 0x200
	movq	%rdx, -32(%rbp)         ## 8-byte Spill
	movq	%rcx, %rdx
	movq	-32(%rbp), %rcx         ## 8-byte Reload
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	callq	_fread
	movq	%rax, -48(%rbp)         ## 8-byte Spill
	jmp	LBB3_8
LBB3_7:
	movq	$-1, %rcx
	movq	-16(%rbp), %rdi
	movl	$4294967295, %esi       ## imm = 0xFFFFFFFF
	movl	$512, %edx              ## imm = 0x200
	callq	___memset_chk
	movq	-16(%rbp), %rdi
	movq	-8(%rbp), %rcx
	movl	$1, %esi
	movl	$512, %edx              ## imm = 0x200
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	callq	_fread
	movq	%rax, -64(%rbp)         ## 8-byte Spill
LBB3_8:
	movq	-16(%rbp), %rax
	movl	$-1, 1028(%rax)
	movq	-16(%rbp), %rax
	movl	$1, %ecx
	subl	1032(%rax), %ecx
	movq	-16(%rbp), %rax
	movl	%ecx, 1032(%rax)
	jmp	LBB3_14
LBB3_9:
	movq	-16(%rbp), %rax
	cmpl	$0, 1036(%rax)
	jne	LBB3_13
## %bb.10:
	movq	-16(%rbp), %rax
	cmpl	$511, 1028(%rax)        ## imm = 0x1FF
	jne	LBB3_12
## %bb.11:
	movq	-16(%rbp), %rax
	movl	$-1, 1028(%rax)
	movq	-16(%rbp), %rax
	movl	$1, %ecx
	subl	1032(%rax), %ecx
	movq	-16(%rbp), %rax
	movl	%ecx, 1032(%rax)
	movq	-16(%rbp), %rax
	movl	$1, 1036(%rax)
LBB3_12:
	jmp	LBB3_13
LBB3_13:
	jmp	LBB3_14
LBB3_14:
	movq	-16(%rbp), %rax
	movl	1028(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, 1028(%rax)
	movsbl	-17(%rbp), %eax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_init_buffer            ## -- Begin function init_buffer
	.p2align	4, 0x90
_init_buffer:                           ## @init_buffer
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	$-1, %rcx
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	addq	$512, %rsi              ## imm = 0x200
	movq	%rsi, %rdi
	movl	$4294967295, %esi       ## imm = 0xFFFFFFFF
	movl	$512, %edx              ## imm = 0x200
	callq	___memset_chk
	movq	$-1, %rcx
	movq	-16(%rbp), %rdi
	movl	$4294967295, %esi       ## imm = 0xFFFFFFFF
	movl	$512, %edx              ## imm = 0x200
	movq	%rax, -24(%rbp)         ## 8-byte Spill
	callq	___memset_chk
	movq	-16(%rbp), %rdi
	movq	-8(%rbp), %rcx
	movl	$1, %esi
	movl	$512, %edx              ## imm = 0x200
	movq	%rax, -32(%rbp)         ## 8-byte Spill
	callq	_fread
	movq	-16(%rbp), %rcx
	movl	$0, 1028(%rcx)
	movq	-16(%rbp), %rcx
	movl	$0, 1024(%rcx)
	movq	-16(%rbp), %rcx
	movl	$0, 1032(%rcx)
	movq	-16(%rbp), %rcx
	movl	$1, 1036(%rcx)
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Lexeme is NULL error.\n"

L_.str.1:                               ## @.str.1
	.asciz	"token: %10s\tvalue: %15s\tline_no: %u\n"

L_.str.2:                               ## @.str.2
	.asciz	"Lexical Error at line # %d.\t Invalid lexeme '%s'. Variable length exceeds 20.\n"

	.comm	_hash_table,512,4       ## @hash_table
L_.str.3:                               ## @.str.3
	.asciz	"ID"

L_.str.4:                               ## @.str.4
	.asciz	"NUM"

L_.str.5:                               ## @.str.5
	.asciz	"RNUM"

L_.str.6:                               ## @.str.6
	.asciz	"Lexical Error at line # %d.\t. Invalid lexeme '%s'.\n"

L_.str.7:                               ## @.str.7
	.asciz	"PLUS"

L_.str.8:                               ## @.str.8
	.asciz	"+"

L_.str.9:                               ## @.str.9
	.asciz	"MINUS"

L_.str.10:                              ## @.str.10
	.asciz	"-"

L_.str.11:                              ## @.str.11
	.asciz	"DIV"

L_.str.12:                              ## @.str.12
	.asciz	"/"

L_.str.13:                              ## @.str.13
	.asciz	"SQBO"

L_.str.14:                              ## @.str.14
	.asciz	"["

L_.str.15:                              ## @.str.15
	.asciz	"SQBC"

L_.str.16:                              ## @.str.16
	.asciz	"]"

L_.str.17:                              ## @.str.17
	.asciz	"BO"

L_.str.18:                              ## @.str.18
	.asciz	"("

L_.str.19:                              ## @.str.19
	.asciz	"BC"

L_.str.20:                              ## @.str.20
	.asciz	")"

L_.str.21:                              ## @.str.21
	.asciz	"SEMICOL"

L_.str.22:                              ## @.str.22
	.asciz	";"

L_.str.23:                              ## @.str.23
	.asciz	"COMMA"

L_.str.24:                              ## @.str.24
	.asciz	","

L_.str.25:                              ## @.str.25
	.asciz	"EQ"

L_.str.26:                              ## @.str.26
	.asciz	"=="

L_.str.27:                              ## @.str.27
	.asciz	"Lexical Error at line # %d.\t. Invalid lexeme '='. Expected '=='.\n"

L_.str.28:                              ## @.str.28
	.asciz	"NE"

L_.str.29:                              ## @.str.29
	.asciz	"!="

L_.str.30:                              ## @.str.30
	.asciz	"Lexical Error at line # %d.\t. Invalid lexeme '!'. Expected '!='.\n"

L_.str.31:                              ## @.str.31
	.asciz	"ASSIGNOP"

L_.str.32:                              ## @.str.32
	.asciz	":="

L_.str.33:                              ## @.str.33
	.asciz	"COLON"

L_.str.34:                              ## @.str.34
	.asciz	":"

L_.str.35:                              ## @.str.35
	.asciz	"RANGEOP"

L_.str.36:                              ## @.str.36
	.asciz	".."

L_.str.37:                              ## @.str.37
	.asciz	"Lexical Error at line # %d.\t. Invalid lexeme '.'. Expected '..'.\n"

L_.str.38:                              ## @.str.38
	.asciz	"LE"

L_.str.39:                              ## @.str.39
	.asciz	"<="

L_.str.40:                              ## @.str.40
	.asciz	"DRIVERDEF"

L_.str.41:                              ## @.str.41
	.asciz	"<<<"

L_.str.42:                              ## @.str.42
	.asciz	"DEF"

L_.str.43:                              ## @.str.43
	.asciz	"<<"

L_.str.44:                              ## @.str.44
	.asciz	"LT"

L_.str.45:                              ## @.str.45
	.asciz	"<"

L_.str.46:                              ## @.str.46
	.asciz	"GE"

L_.str.47:                              ## @.str.47
	.asciz	">="

L_.str.48:                              ## @.str.48
	.asciz	"DRIVERENDDEF"

L_.str.49:                              ## @.str.49
	.asciz	">>>"

L_.str.50:                              ## @.str.50
	.asciz	"ENDDEF"

L_.str.51:                              ## @.str.51
	.asciz	">>"

L_.str.52:                              ## @.str.52
	.asciz	"GT"

L_.str.53:                              ## @.str.53
	.asciz	">"

L_.str.54:                              ## @.str.54
	.asciz	"MUL"

L_.str.55:                              ## @.str.55
	.asciz	"*"

L_.str.56:                              ## @.str.56
	.asciz	"Lexical Error at line #%d: unidentifiable character: %c.\n"

L_.str.57:                              ## @.str.57
	.asciz	"DOLLAR"


.subsections_via_symbols
