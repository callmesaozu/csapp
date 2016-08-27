	.file	"chapter_5.c"
	.text
	.globl	new_vec
	.type	new_vec, @function
new_vec:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbp
	movl	$16, %edi
	call	malloc
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L5
	movq	%rbp, (%rax)
	testq	%rbp, %rbp
	jle	.L3
	movl	$4, %esi
	movq	%rbp, %rdi
	call	calloc
	testq	%rax, %rax
	jne	.L4
	movq	%rbx, %rdi
	call	free
	movl	$0, %eax
	jmp	.L2
.L4:
	movq	%rax, 8(%rbx)
	movq	%rbx, %rax
	jmp	.L2
.L3:
	movq	$0, 8(%rax)
	jmp	.L2
.L5:
	movl	$0, %eax
.L2:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
	.size	new_vec, .-new_vec
	.globl	get_vec_element
	.type	get_vec_element, @function
get_vec_element:
.LFB41:
	.cfi_startproc
	testq	%rsi, %rsi
	js	.L9
	movl	$0, %eax
	cmpq	(%rdi), %rsi
	jge	.L8
	movq	8(%rdi), %rax
	movl	(%rax,%rsi,4), %eax
	movl	%eax, (%rdx)
	movl	$1, %eax
	ret
.L9:
	movl	$0, %eax
.L8:
	rep ret
	.cfi_endproc
.LFE41:
	.size	get_vec_element, .-get_vec_element
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
	.globl	combine1
	.type	combine1, @function
combine1:
.LFB43:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, %rbp
	movq	%rsi, %r12
	movl	$0, (%rsi)
	cmpq	$0, (%rdi)
	jle	.L12
	movl	$0, %ebx
.L14:
	leaq	12(%rsp), %rdx
	movq	%rbx, %rsi
	movq	%rbp, %rdi
	call	get_vec_element
	movl	12(%rsp), %eax
	addl	%eax, (%r12)
	addq	$1, %rbx
	cmpq	0(%rbp), %rbx
	jl	.L14
.L12:
	addq	$16, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE43:
	.size	combine1, .-combine1
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"combine1 %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$331, %edi
	call	new_vec
	leaq	12(%rsp), %rsi
	movq	%rax, %rdi
	call	combine1
	movl	12(%rsp), %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.globl	combine2
	.type	combine2, @function
combine2:
.LFB44:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$16, %rsp
	.cfi_def_cfa_offset 56
	movq	%rdi, %r13
	movq	%rsi, %rbp
	movl	$0, (%rsi)
	movq	(%rdi), %r12
	testq	%r12, %r12
	jle	.L18
	movl	$0, %ebx
.L20:
	leaq	12(%rsp), %rdx
	movq	%rbx, %rsi
	movq	%r13, %rdi
	call	get_vec_element
	movl	12(%rsp), %eax
	addl	%eax, 0(%rbp)
	addq	$1, %rbx
	cmpq	%r12, %rbx
	jne	.L20
.L18:
	addq	$16, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE44:
	.size	combine2, .-combine2
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
	.globl	combine3
	.type	combine3, @function
combine3:
.LFB46:
	.cfi_startproc
	movq	(%rdi), %rdx
	movq	8(%rdi), %rcx
	movl	$0, (%rsi)
	testq	%rdx, %rdx
	jle	.L23
	movq	%rcx, %rax
	leaq	(%rcx,%rdx,4), %rcx
.L25:
	movl	(%rax), %edx
	addl	%edx, (%rsi)
	addq	$4, %rax
	cmpq	%rcx, %rax
	jne	.L25
.L23:
	rep ret
	.cfi_endproc
.LFE46:
	.size	combine3, .-combine3
	.globl	combine4
	.type	combine4, @function
combine4:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsi, %rbp
	movq	(%rdi), %rbx
	movl	$0, %eax
	call	get_vev_start
	testq	%rbx, %rbx
	jle	.L29
	movl	$0, %ecx
	movl	$0, %edx
	cltq
.L28:
	addl	(%rax,%rdx,4), %ecx
	addq	$1, %rdx
	cmpq	%rbx, %rdx
	jne	.L28
	jmp	.L27
.L29:
	movl	$0, %ecx
.L27:
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
	.globl	strlen
	.type	strlen, @function
strlen:
.LFB50:
	.cfi_startproc
	cmpb	$0, (%rdi)
	je	.L34
	movq	%rdi, %rdx
.L33:
	addq	$1, %rdx
	movl	%edx, %eax
	subl	%edi, %eax
	cmpb	$0, (%rdx)
	jne	.L33
	jmp	.L32
.L34:
	movl	$0, %eax
.L32:
	cltq
	ret
	.cfi_endproc
.LFE50:
	.size	strlen, .-strlen
	.globl	lower1
	.type	lower1, @function
lower1:
.LFB48:
	.cfi_startproc
	movq	%rdi, %r9
	movl	$0, %edx
	movq	$-1, %r10
	movl	$0, %eax
	jmp	.L36
.L38:
	addq	%r9, %rsi
	movzbl	(%rsi), %r8d
	leal	-65(%r8), %edi
	cmpb	$25, %dil
	ja	.L37
	addl	$32, %r8d
	movb	%r8b, (%rsi)
.L37:
	addl	$1, %edx
.L36:
	movslq	%edx, %rsi
	movq	%r9, %rdi
	movq	%r10, %rcx
	repnz scasb
	notq	%rcx
	movq	%rcx, %r8
	subq	$1, %r8
	cmpq	%r8, %rsi
	jb	.L38
	rep ret
	.cfi_endproc
.LFE48:
	.size	lower1, .-lower1
	.globl	lower2
	.type	lower2, @function
lower2:
.LFB49:
	.cfi_startproc
	movq	%rdi, %rsi
	movl	$0, %eax
	movq	$-1, %rcx
	repnz scasb
	notq	%rcx
	subq	$1, %rcx
	movl	%ecx, %edi
	testl	%ecx, %ecx
	jle	.L39
	movl	$0, %eax
.L42:
	movzbl	(%rsi,%rax), %edx
	leal	-65(%rdx), %ecx
	cmpb	$25, %cl
	ja	.L41
	addl	$32, %edx
	movb	%dl, (%rsi,%rax)
.L41:
	addq	$1, %rax
	cmpl	%eax, %edi
	jg	.L42
.L39:
	rep ret
	.cfi_endproc
.LFE49:
	.size	lower2, .-lower2
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
