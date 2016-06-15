	.file	"t2.c"
	.text
	.globl	switch_eg_impl
	.type	switch_eg_impl, @function
switch_eg_impl:
.LFB0:
	.cfi_startproc
	subl	$100, %esi
	cmpl	$6, %esi
	ja	.L2
	movl	%esi, %esi
	jmp	*jt.1725(,%rsi,8)
.L2:
	movl	$0, %eax
	ret
.L4:
	.p2align 4,,5
	jmp	.L5
.L6:
	leal	(%rdi,%rdi,2), %eax
	leal	(%rdi,%rax,4), %eax
	.p2align 4,,1
	ret
.L7:
	addl	$10, %edi
.L5:
	leal	11(%rdi), %eax
	ret
.L8:
	movl	%edi, %eax
	imull	%edi, %eax
.L3:
	ret
	.cfi_endproc
.LFE0:
	.size	switch_eg_impl, .-switch_eg_impl
	.section	.rodata
	.align 32
	.type	jt.1725, @object
	.size	jt.1725, 56
jt.1725:
	.quad	.L6
	.quad	.L2
	.quad	.L7
	.quad	.L4
	.quad	.L8
	.quad	.L2
	.quad	.L8
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
