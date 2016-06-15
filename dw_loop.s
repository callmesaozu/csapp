	.file	"dw_loop.c"
	.text
	.globl	dw_loop
	.type	dw_loop, @function
dw_loop:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
.L3:
	addl	%edx, %eax
	imull	%edx, %esi
	subl	$1, %edx
	cmpl	%edx, %esi
	jge	.L2
	testl	%edx, %edx
	jg	.L3
.L2:
	rep ret
	.cfi_endproc
.LFE0:
	.size	dw_loop, .-dw_loop
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
