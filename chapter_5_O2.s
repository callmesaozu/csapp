	.file	"chapter_5.c"
	.text
	.p2align 4,,15
	.globl	new_vec
	.type	new_vec, @function
new_vec:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	movl	$16, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	malloc
	testq	%rax, %rax
	movq	%rax, %rbx
	je	.L5
	testq	%rbp, %rbp
	movq	%rbp, (%rax)
	jle	.L3
	movl	$4, %esi
	movq	%rbp, %rdi
	call	calloc
	testq	%rax, %rax
	je	.L8
	movq	%rax, 8(%rbx)
	movq	%rbx, %rax
.L2:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
	movq	$0, 8(%rax)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L5:
	.cfi_restore_state
	xorl	%eax, %eax
	jmp	.L2
.L8:
	movq	%rbx, %rdi
	call	free
	xorl	%eax, %eax
	jmp	.L2
	.cfi_endproc
.LFE40:
	.size	new_vec, .-new_vec
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"combine1 %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$331, %edi
	call	new_vec
	movq	(%rax), %rsi
	testq	%rsi, %rsi
	jle	.L12
	movq	8(%rax), %rax
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L11:
	addl	(%rax,%rcx,4), %edx
	addq	$1, %rcx
	cmpq	%rsi, %rcx
	jne	.L11
.L10:
	movl	$.LC0, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L12:
	.cfi_restore_state
	xorl	%edx, %edx
	jmp	.L10
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.text
	.p2align 4,,15
	.globl	get_vec_element
	.type	get_vec_element, @function
get_vec_element:
.LFB41:
	.cfi_startproc
	xorl	%eax, %eax
	testq	%rsi, %rsi
	js	.L15
	cmpq	(%rdi), %rsi
	jge	.L15
	movq	8(%rdi), %rax
	movl	(%rax,%rsi,4), %eax
	movl	%eax, (%rdx)
	movl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L15:
	rep ret
	.cfi_endproc
.LFE41:
	.size	get_vec_element, .-get_vec_element
	.p2align 4,,15
	.globl	vec_length
	.type	vec_length, @function
vec_length:
.LFB42:
	.cfi_startproc
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE42:
	.size	vec_length, .-vec_length
	.p2align 4,,15
	.globl	combine1
	.type	combine1, @function
combine1:
.LFB43:
	.cfi_startproc
	movq	(%rdi), %rcx
	movl	$0, (%rsi)
	testq	%rcx, %rcx
	jle	.L19
	movq	8(%rdi), %rdi
	xorl	%edx, %edx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L22:
	addl	(%rdi,%rax,4), %edx
	addq	$1, %rax
	cmpq	%rcx, %rax
	movl	%edx, (%rsi)
	jne	.L22
.L19:
	rep ret
	.cfi_endproc
.LFE43:
	.size	combine1, .-combine1
	.p2align 4,,15
	.globl	combine2
	.type	combine2, @function
combine2:
.LFB44:
	.cfi_startproc
	movq	(%rdi), %rcx
	movl	$0, (%rsi)
	testq	%rcx, %rcx
	jle	.L23
	movq	8(%rdi), %rdi
	xorl	%edx, %edx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L26:
	addl	(%rdi,%rax,4), %edx
	addq	$1, %rax
	cmpq	%rcx, %rax
	movl	%edx, (%rsi)
	jne	.L26
.L23:
	rep ret
	.cfi_endproc
.LFE44:
	.size	combine2, .-combine2
	.p2align 4,,15
	.globl	get_vec_start
	.type	get_vec_start, @function
get_vec_start:
.LFB45:
	.cfi_startproc
	movq	8(%rdi), %rax
	ret
	.cfi_endproc
.LFE45:
	.size	get_vec_start, .-get_vec_start
	.p2align 4,,15
	.globl	combine3
	.type	combine3, @function
combine3:
.LFB46:
	.cfi_startproc
	movq	(%rdi), %rdx
	movq	8(%rdi), %rax
	movl	$0, (%rsi)
	testq	%rdx, %rdx
	jle	.L28
	leaq	(%rax,%rdx,4), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L31:
	addl	(%rax), %edx
	addq	$4, %rax
	cmpq	%rcx, %rax
	movl	%edx, (%rsi)
	jne	.L31
.L28:
	rep ret
	.cfi_endproc
.LFE46:
	.size	combine3, .-combine3
	.p2align 4,,15
	.globl	combine4
	.type	combine4, @function
combine4:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	xorl	%eax, %eax
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rdi), %rbx
	call	get_vev_start
	xorl	%ecx, %ecx
	testq	%rbx, %rbx
	jle	.L33
	xorl	%edx, %edx
	cltq
	.p2align 4,,10
	.p2align 3
.L34:
	addl	(%rax,%rdx,4), %ecx
	addq	$1, %rdx
	cmpq	%rbx, %rdx
	jne	.L34
.L33:
	movl	%ecx, 0(%rbp)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE47:
	.size	combine4, .-combine4
	.p2align 4,,15
	.globl	lower1
	.type	lower1, @function
lower1:
.LFB48:
	.cfi_startproc
	movzbl	(%rdi), %esi
	xorl	%ecx, %ecx
	testb	%sil, %sil
	je	.L37
	.p2align 4,,10
	.p2align 3
.L47:
	movq	%rdi, %rax
	.p2align 4,,10
	.p2align 3
.L42:
	addq	$1, %rax
	movl	%eax, %edx
	subl	%edi, %edx
	cmpb	$0, (%rax)
	jne	.L42
	movslq	%edx, %rdx
	cmpq	%rdx, %rcx
	jnb	.L37
	movzbl	(%rdi,%rcx), %eax
	leal	-65(%rax), %edx
	cmpb	$25, %dl
	ja	.L39
	addl	$32, %eax
	movb	%al, (%rdi,%rcx)
	movzbl	(%rdi), %esi
.L39:
	addq	$1, %rcx
	testb	%sil, %sil
	jne	.L47
.L37:
	rep ret
	.cfi_endproc
.LFE48:
	.size	lower1, .-lower1
	.p2align 4,,15
	.globl	lower2
	.type	lower2, @function
lower2:
.LFB49:
	.cfi_startproc
	cmpb	$0, (%rdi)
	movq	%rdi, %rax
	je	.L48
	.p2align 4,,10
	.p2align 3
.L55:
	addq	$1, %rax
	movl	%eax, %edx
	subl	%edi, %edx
	cmpb	$0, (%rax)
	jne	.L55
	testl	%edx, %edx
	jle	.L48
	leal	-1(%rdx), %eax
	leaq	1(%rdi,%rax), %rcx
	.p2align 4,,10
	.p2align 3
.L54:
	movzbl	(%rdi), %eax
	leal	-65(%rax), %edx
	cmpb	$25, %dl
	ja	.L53
	addl	$32, %eax
	movb	%al, (%rdi)
.L53:
	addq	$1, %rdi
	cmpq	%rcx, %rdi
	jne	.L54
.L48:
	rep ret
	.cfi_endproc
.LFE49:
	.size	lower2, .-lower2
	.p2align 4,,15
	.globl	strlen
	.type	strlen, @function
strlen:
.LFB50:
	.cfi_startproc
	cmpb	$0, (%rdi)
	je	.L60
	movq	%rdi, %rdx
	.p2align 4,,10
	.p2align 3
.L59:
	addq	$1, %rdx
	movl	%edx, %eax
	subl	%edi, %eax
	cmpb	$0, (%rdx)
	jne	.L59
	cltq
	ret
.L60:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE50:
	.size	strlen, .-strlen
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
