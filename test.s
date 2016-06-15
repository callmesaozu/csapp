	.file	"test.c"
	.text
	.globl	switch_eg
	.type	switch_eg, @function
switch_eg:
.LFB24:
	.cfi_startproc
	cmpl	$102, %esi
	je	.L3
	cmpl	$103, %esi
	je	.L4
	cmpl	$100, %esi
	jne	.L7
	leal	(%rdi,%rdi,2), %eax
	leal	(%rdi,%rax,4), %eax
	ret
.L3:
	addl	$10, %edi
.L4:
	leal	11(%rdi), %eax
	ret
.L7:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE24:
	.size	switch_eg, .-switch_eg
	.globl	switch_eg_impl
	.type	switch_eg_impl, @function
switch_eg_impl:
.LFB25:
	.cfi_startproc
	subl	$100, %esi
	cmpl	$6, %esi
	ja	.L9
	movl	%esi, %esi
	jmp	*jt.2397(,%rsi,8)
.L9:
	movl	$0, %eax
	ret
.L11:
	.p2align 4,,5
	jmp	.L12
.L13:
	leal	(%rdi,%rdi,2), %eax
	leal	(%rdi,%rax,4), %eax
	.p2align 4,,1
	ret
.L14:
	addl	$10, %edi
.L12:
	leal	11(%rdi), %eax
	ret
.L15:
	movl	%edi, %eax
	imull	%edi, %eax
.L10:
	ret
	.cfi_endproc
.LFE25:
	.size	switch_eg_impl, .-switch_eg_impl
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"switch_eg_impl(%d, %d) = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$103, %esi
	movl	$5, %edi
	call	switch_eg_impl
	movl	%eax, %r8d
	movl	$103, %ecx
	movl	$5, %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.section	.rodata
	.align 32
	.type	jt.2397, @object
	.size	jt.2397, 56
jt.2397:
	.quad	.L13
	.quad	.L9
	.quad	.L14
	.quad	.L11
	.quad	.L15
	.quad	.L9
	.quad	.L15
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
