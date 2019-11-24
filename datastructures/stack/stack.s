	.file	"stack.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"stack: error on initializing items array.\n"
.LC1:
	.string	"ERROR"
	.text
	.globl	stack_new
	.type	stack_new, @function
stack_new:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$16, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$4, 12(%rax)
	movq	-8(%rbp), %rax
	movl	12(%rax), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L2
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$42, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
.L2:
	movq	-8(%rbp), %rax
	movl	$0, 8(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	stack_new, .-stack_new
	.globl	stack_size
	.type	stack_size, @function
stack_size:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L5
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	jmp	.L6
.L5:
	movl	$-1, %eax
.L6:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	stack_size, .-stack_size
	.section	.rodata
	.align 8
.LC2:
	.string	"stack error: items not initialized"
	.text
	.globl	stack_resize
	.type	stack_resize, @function
stack_resize:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L8
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %edx
	movl	%edx, 12(%rax)
	movl	$0, %eax
	jmp	.L10
.L8:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$34, %edx
	movl	$1, %esi
	leaq	.LC2(%rip), %rdi
	call	fwrite@PLT
	movl	$-1, %eax
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	stack_resize, .-stack_resize
	.globl	stack_put
	.type	stack_put, @function
stack_put:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L12
	movl	$-1, %eax
	jmp	.L13
.L12:
	movq	-8(%rbp), %rax
	movl	8(%rax), %edx
	movq	-8(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	%eax, %edx
	jl	.L14
	movq	-8(%rbp), %rax
	movl	12(%rax), %eax
	leal	(%rax,%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stack_resize
.L14:
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	cltq
	salq	$3, %rax
	subq	$8, %rax
	addq	%rax, %rdx
	movq	-16(%rbp), %rax
	movq	%rax, (%rdx)
	movl	$0, %eax
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	stack_put, .-stack_put
	.globl	stack_pop
	.type	stack_pop, @function
stack_pop:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$0, -8(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L16
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jg	.L17
.L16:
	movq	-8(%rbp), %rax
	jmp	.L18
.L17:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cltq
	salq	$3, %rax
	subq	$8, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cltq
	salq	$3, %rax
	subq	$8, %rax
	addq	%rdx, %rax
	movq	$0, (%rax)
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	leal	-1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-24(%rbp), %rax
	movl	8(%rax), %edx
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	leal	3(%rax), %ecx
	testl	%eax, %eax
	cmovs	%ecx, %eax
	sarl	$2, %eax
	cmpl	%eax, %edx
	jge	.L19
	movq	-24(%rbp), %rax
	movl	12(%rax), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stack_resize
.L19:
	movq	-8(%rbp), %rax
.L18:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	stack_pop, .-stack_pop
	.globl	stack_empty
	.type	stack_empty, @function
stack_empty:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L21
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	jmp	.L22
.L21:
	movl	$-1, %eax
.L22:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	stack_empty, .-stack_empty
	.globl	stack_delete
	.type	stack_delete, @function
stack_delete:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L26
	movq	-8(%rbp), %rax
	movl	$0, 12(%rax)
	movq	-8(%rbp), %rax
	movl	12(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L23
.L26:
	nop
.L23:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	stack_delete, .-stack_delete
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
