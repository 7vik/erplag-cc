	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3               ## -- Begin function main
LCPI0_0:
	.quad	4696837146684686336     ## double 1.0E+6
	.section	__TEXT,__literal16,16byte_literals
	.p2align	4
LCPI0_1:
	.long	1127219200              ## 0x43300000
	.long	1160773632              ## 0x45300000
	.long	0                       ## 0x0
	.long	0                       ## 0x0
LCPI0_2:
	.quad	4841369599423283200     ## double 4503599627370496
	.quad	4985484787499139072     ## double 1.9342813113834067E+25
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$432, %rsp              ## imm = 0x1B0
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpl	$3, -8(%rbp)
	je	LBB0_2
## %bb.1:
	leaq	L_.str.114(%rip), %rdi
	xorl	%eax, %eax
	movb	%al, %cl
	movb	%cl, %al
	movb	%cl, -241(%rbp)         ## 1-byte Spill
	callq	_printf
	leaq	L_.str.115(%rip), %rdi
	movb	-241(%rbp), %cl         ## 1-byte Reload
	movl	%eax, -248(%rbp)        ## 4-byte Spill
	movb	%cl, %al
	callq	_printf
	movl	$2, %edi
	movl	%eax, -252(%rbp)        ## 4-byte Spill
	callq	_exit
LBB0_2:
	leaq	L_.str.116(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.117(%rip), %rdi
	movl	%eax, -256(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.118(%rip), %rdi
	movl	%eax, -260(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.119(%rip), %rdi
	movl	%eax, -264(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.120(%rip), %rdi
	movl	%eax, -268(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.121(%rip), %rdi
	movl	%eax, -272(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	%eax, -276(%rbp)        ## 4-byte Spill
LBB0_3:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_9 Depth 2
	leaq	L_.str.122(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.123(%rip), %rdi
	movl	%eax, -280(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.124(%rip), %rdi
	movl	%eax, -284(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.125(%rip), %rdi
	movl	%eax, -288(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.126(%rip), %rdi
	movl	%eax, -292(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.127(%rip), %rdi
	movl	%eax, -296(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.128(%rip), %rdi
	movl	%eax, -300(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$0, -52(%rbp)
	leaq	L_.str.129(%rip), %rdi
	leaq	-52(%rbp), %rsi
	movl	%eax, -304(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	cmpl	$0, -52(%rbp)
	movl	%eax, -308(%rbp)        ## 4-byte Spill
	jne	LBB0_5
## %bb.4:
	leaq	L_.str.130(%rip), %rdi
	xorl	%eax, %eax
	movb	%al, %cl
	movl	%eax, -312(%rbp)        ## 4-byte Spill
	movb	%cl, %al
	callq	_printf
	movl	-312(%rbp), %edi        ## 4-byte Reload
	movl	%eax, -316(%rbp)        ## 4-byte Spill
	callq	_exit
LBB0_5:                                 ##   in Loop: Header=BB0_3 Depth=1
	cmpl	$1, -52(%rbp)
	jne	LBB0_7
## %bb.6:                               ##   in Loop: Header=BB0_3 Depth=1
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdi
	leaq	L_.str.131(%rip), %rsi
	callq	_fopen
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdi
	callq	_remove_comments_driver
	leaq	L_.str.132(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-64(%rbp), %rdi
	movl	%eax, -320(%rbp)        ## 4-byte Spill
	callq	_fclose
	movl	%eax, -324(%rbp)        ## 4-byte Spill
	jmp	LBB0_20
LBB0_7:                                 ##   in Loop: Header=BB0_3 Depth=1
	cmpl	$2, -52(%rbp)
	jne	LBB0_12
## %bb.8:                               ##   in Loop: Header=BB0_3 Depth=1
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdi
	leaq	L_.str.131(%rip), %rsi
	callq	_fopen
	movq	_hash_table@GOTPCREL(%rip), %rdi
	movq	%rax, -72(%rbp)
	leaq	L_.str.133(%rip), %rsi
	callq	_populate_ht
	movl	$1, -76(%rbp)
	movl	$1040, %edi             ## imm = 0x410
	callq	_malloc
	movq	%rax, -88(%rbp)
	movq	-72(%rbp), %rdi
	movq	-88(%rbp), %rsi
	callq	_init_buffer
	movq	-72(%rbp), %rdi
	movq	-88(%rbp), %rsi
	leaq	-76(%rbp), %rdx
	callq	_get_token
	movq	%rax, -96(%rbp)
LBB0_9:                                 ##   Parent Loop BB0_3 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movq	-96(%rbp), %rax
	movq	(%rax), %rdi
	callq	_string_to_enum
	cmpl	$70, %eax
	je	LBB0_11
## %bb.10:                              ##   in Loop: Header=BB0_9 Depth=2
	movq	-96(%rbp), %rdi
	callq	_print_lexeme
	movq	-72(%rbp), %rdi
	movq	-88(%rbp), %rsi
	leaq	-76(%rbp), %rdx
	callq	_get_token
	movq	%rax, -96(%rbp)
	jmp	LBB0_9
LBB0_11:                                ##   in Loop: Header=BB0_3 Depth=1
	leaq	L_.str.134(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-72(%rbp), %rdi
	movl	%eax, -328(%rbp)        ## 4-byte Spill
	callq	_fclose
	movq	-88(%rbp), %rdi
	movl	%eax, -332(%rbp)        ## 4-byte Spill
	callq	_free
	jmp	LBB0_19
LBB0_12:                                ##   in Loop: Header=BB0_3 Depth=1
	cmpl	$3, -52(%rbp)
	jne	LBB0_14
## %bb.13:                              ##   in Loop: Header=BB0_3 Depth=1
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdi
	leaq	L_.str.131(%rip), %rsi
	callq	_fopen
	movq	%rax, -104(%rbp)
	movq	-16(%rbp), %rax
	movq	16(%rax), %rdi
	leaq	L_.str.135(%rip), %rsi
	callq	_fopen
	movq	_hash_table@GOTPCREL(%rip), %rdi
	movq	%rax, -112(%rbp)
	leaq	L_.str.133(%rip), %rsi
	callq	_populate_ht
	movl	$1, -116(%rbp)
	movl	$1040, %edi             ## imm = 0x410
	callq	_malloc
	movq	%rax, -128(%rbp)
	movq	-104(%rbp), %rdi
	movq	-128(%rbp), %rsi
	callq	_init_buffer
	callq	_generate_grammar
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rdi
	callq	_get_first_follow_table
	movq	%rax, -144(%rbp)
	movl	$12992, %edi            ## imm = 0x32C0
	callq	_malloc
	movq	%rax, -152(%rbp)
	movq	-144(%rbp), %rdi
	movq	-152(%rbp), %rsi
	movq	-136(%rbp), %rdx
	callq	_create_parse_table
	movq	$0, -160(%rbp)
	movq	-136(%rbp), %rdi
	movq	-104(%rbp), %rsi
	movq	-152(%rbp), %rdx
	movq	-160(%rbp), %r8
	movq	-128(%rbp), %r9
	leaq	-168(%rbp), %rcx
	leaq	-116(%rbp), %r10
	movq	%r10, (%rsp)
	movq	%rax, -344(%rbp)        ## 8-byte Spill
	callq	_parse
	movq	-112(%rbp), %rdi
	leaq	L_.str.136(%rip), %rsi
	leaq	L_.str.137(%rip), %rdx
	leaq	L_.str.138(%rip), %rcx
	leaq	L_.str.139(%rip), %r8
	leaq	L_.str.140(%rip), %r9
	leaq	L_.str.141(%rip), %rax
	movq	%rax, (%rsp)
	leaq	L_.str.142(%rip), %rax
	movq	%rax, 8(%rsp)
	leaq	L_.str.143(%rip), %rax
	movq	%rax, 16(%rsp)
	movb	$0, %al
	callq	_fprintf
	movq	-168(%rbp), %rdi
	movq	-112(%rbp), %rsi
	movl	%eax, -348(%rbp)        ## 4-byte Spill
	callq	_print_parse_tree
	movq	-16(%rbp), %rcx
	movq	16(%rcx), %rsi
	leaq	L_.str.144(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-104(%rbp), %rdi
	movl	%eax, -352(%rbp)        ## 4-byte Spill
	callq	_fclose
	movq	-112(%rbp), %rdi
	movl	%eax, -356(%rbp)        ## 4-byte Spill
	callq	_fclose
	movq	-128(%rbp), %rcx
	movq	%rcx, %rdi
	movl	%eax, -360(%rbp)        ## 4-byte Spill
	callq	_free
	movq	-152(%rbp), %rcx
	movq	%rcx, %rdi
	callq	_free
	jmp	LBB0_18
LBB0_14:                                ##   in Loop: Header=BB0_3 Depth=1
	cmpl	$4, -52(%rbp)
	jne	LBB0_16
## %bb.15:                              ##   in Loop: Header=BB0_3 Depth=1
	movsd	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdi
	leaq	L_.str.131(%rip), %rsi
	movsd	%xmm0, -368(%rbp)       ## 8-byte Spill
	callq	_fopen
	movq	%rax, -176(%rbp)
	movq	-16(%rbp), %rax
	movq	16(%rax), %rdi
	leaq	L_.str.135(%rip), %rsi
	callq	_fopen
	movq	%rax, -184(%rbp)
	movq	_hash_table@GOTPCREL(%rip), %rdi
	leaq	L_.str.133(%rip), %rsi
	callq	_populate_ht
	movl	$1, -188(%rbp)
	movl	$1040, %edi             ## imm = 0x410
	callq	_malloc
	movq	%rax, -200(%rbp)
	movq	-176(%rbp), %rdi
	movq	-200(%rbp), %rsi
	callq	_init_buffer
	callq	_generate_grammar
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rdi
	callq	_get_first_follow_table
	movq	%rax, -216(%rbp)
	movl	$12992, %edi            ## imm = 0x32C0
	callq	_malloc
	movq	%rax, -224(%rbp)
	movq	-216(%rbp), %rdi
	movq	-224(%rbp), %rsi
	movq	-208(%rbp), %rdx
	callq	_create_parse_table
	movq	$0, -232(%rbp)
	movq	%rax, -376(%rbp)        ## 8-byte Spill
	callq	_clock
	movq	%rax, -24(%rbp)
	movq	-208(%rbp), %rdi
	movq	-176(%rbp), %rsi
	movq	-224(%rbp), %rdx
	movq	-232(%rbp), %r8
	movq	-200(%rbp), %r9
	movq	%rsp, %rax
	leaq	-188(%rbp), %rcx
	movq	%rcx, (%rax)
	leaq	-240(%rbp), %rcx
	callq	_parse
	callq	_clock
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	subq	%rcx, %rax
	movq	%rax, %xmm0
	movaps	LCPI0_1(%rip), %xmm1    ## xmm1 = [1127219200,1160773632,0,0]
	punpckldq	%xmm1, %xmm0    ## xmm0 = xmm0[0],xmm1[0],xmm0[1],xmm1[1]
	movapd	LCPI0_2(%rip), %xmm1    ## xmm1 = [4.503599627370496E+15,1.9342813113834067E+25]
	subpd	%xmm1, %xmm0
	haddpd	%xmm0, %xmm0
	movsd	%xmm0, -40(%rbp)
	movsd	-40(%rbp), %xmm0        ## xmm0 = mem[0],zero
	movsd	-368(%rbp), %xmm1       ## 8-byte Reload
                                        ## xmm1 = mem[0],zero
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -48(%rbp)
	movq	-184(%rbp), %rdi
	leaq	L_.str.136(%rip), %rsi
	leaq	L_.str.137(%rip), %rdx
	leaq	L_.str.138(%rip), %rcx
	leaq	L_.str.140(%rip), %r8
	leaq	L_.str.139(%rip), %r9
	leaq	L_.str.141(%rip), %rax
	movq	%rax, (%rsp)
	leaq	L_.str.142(%rip), %rax
	movq	%rax, 8(%rsp)
	leaq	L_.str.143(%rip), %rax
	movq	%rax, 16(%rsp)
	movb	$0, %al
	callq	_fprintf
	movq	-240(%rbp), %rdi
	movq	-184(%rbp), %rsi
	movl	%eax, -380(%rbp)        ## 4-byte Spill
	callq	_print_parse_tree
	movq	-16(%rbp), %rcx
	movq	16(%rcx), %rsi
	leaq	L_.str.144(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movsd	-40(%rbp), %xmm0        ## xmm0 = mem[0],zero
	movsd	-48(%rbp), %xmm1        ## xmm1 = mem[0],zero
	leaq	L_.str.145(%rip), %rdi
	movl	%eax, -384(%rbp)        ## 4-byte Spill
	movb	$2, %al
	callq	_printf
	movq	-176(%rbp), %rdi
	movl	%eax, -388(%rbp)        ## 4-byte Spill
	callq	_fclose
	movq	-184(%rbp), %rdi
	movl	%eax, -392(%rbp)        ## 4-byte Spill
	callq	_fclose
	movq	-200(%rbp), %rcx
	movq	%rcx, %rdi
	movl	%eax, -396(%rbp)        ## 4-byte Spill
	callq	_free
	movq	-224(%rbp), %rcx
	movq	%rcx, %rdi
	callq	_free
	jmp	LBB0_17
LBB0_16:                                ##   in Loop: Header=BB0_3 Depth=1
	leaq	L_.str.146(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -400(%rbp)        ## 4-byte Spill
LBB0_17:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_18
LBB0_18:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_19
LBB0_19:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_20
LBB0_20:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_21
LBB0_21:                                ##   in Loop: Header=BB0_3 Depth=1
	jmp	LBB0_3
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
	.asciz	"Invalid argument count. Expected 3 arguments as in './executable testcase parse_outfile'."

L_.str.115:                             ## @.str.115
	.asciz	"\nAborting Execution!!\n"

L_.str.116:                             ## @.str.116
	.asciz	"\n\n****\tExecution details\t******\n\n"

L_.str.117:                             ## @.str.117
	.asciz	"====\t\tImplementation Details\t\t====\n"

L_.str.118:                             ## @.str.118
	.asciz	"1. First and Follow Set Calculation Automated.\n"

L_.str.119:                             ## @.str.119
	.asciz	"2. Both Lexical and Syntax Analysis Modules Implemented.\n"

L_.str.120:                             ## @.str.120
	.asciz	"3. Parse Tree Construction Completed.\n"

L_.str.121:                             ## @.str.121
	.asciz	"4. All testcases (t1-t6) working successfully.\n"

L_.str.122:                             ## @.str.122
	.asciz	"\n\nPlease choose from following options:\n"

L_.str.123:                             ## @.str.123
	.asciz	"0 -> Exit\n"

L_.str.124:                             ## @.str.124
	.asciz	"1 : Remove Comments\n"

L_.str.125:                             ## @.str.125
	.asciz	"2 : Invoke Lexical Analysis\n"

L_.str.126:                             ## @.str.126
	.asciz	"3 : Parse and Print Parse Tree\n"

L_.str.127:                             ## @.str.127
	.asciz	"4 : Time for Lexical and Syntactic Analysis\n"

L_.str.128:                             ## @.str.128
	.asciz	"\nEnter Option [0-4]\t"

L_.str.129:                             ## @.str.129
	.asciz	"%d"

L_.str.130:                             ## @.str.130
	.asciz	"Exiting. Bye bye.\n"

L_.str.131:                             ## @.str.131
	.asciz	"r"

L_.str.132:                             ## @.str.132
	.asciz	"\n\nComments removed. SUCCESS.\n"

	.comm	_hash_table,512,4       ## @hash_table
L_.str.133:                             ## @.str.133
	.asciz	"./keywords.txt"

L_.str.134:                             ## @.str.134
	.asciz	"\n\n Lexing done. SUCCESS.\n"

L_.str.135:                             ## @.str.135
	.asciz	"w"

L_.str.136:                             ## @.str.136
	.asciz	"%20s\t%20s\t%20s\t%20s\t%20s\t%20s\t%20s\n\n"

L_.str.137:                             ## @.str.137
	.asciz	"LEXEME"

L_.str.138:                             ## @.str.138
	.asciz	"LINE_NO"

L_.str.139:                             ## @.str.139
	.asciz	"VALUE (if num)"

L_.str.140:                             ## @.str.140
	.asciz	"TOKENAME"

L_.str.141:                             ## @.str.141
	.asciz	"PARENT"

L_.str.142:                             ## @.str.142
	.asciz	"IS LEAF?"

L_.str.143:                             ## @.str.143
	.asciz	"NODE SYMBOL"

L_.str.144:                             ## @.str.144
	.asciz	"Printed Parse Tree in file '%s'.\n"

L_.str.145:                             ## @.str.145
	.asciz	"CPU Time: %lf, CPU time(in seconds): %lf\n"

L_.str.146:                             ## @.str.146
	.asciz	"Please enter a number from [0-4]."


.subsections_via_symbols
