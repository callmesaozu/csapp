	.file	"do_while.c"
	.text
	.globl	fact_do
	.type	fact_do, @function
fact_do:
.LFB0:
	.cfi_startproc
	movl	$1, %eax
.L3:
	imull	%edi, %eax
	subl	$1, %edi
	cmpl	$1, %edi
	jg	.L3
	rep ret
	.cfi_endproc
.LFE0:
	.size	fact_do, .-fact_do
	.globl	fact_while
	.type	fact_while, @function
fact_while:
.LFB1:
	.cfi_startproc
	cmpl	$1, %edi
	jle	.L7
	movl	$1, %eax
.L6:
	imull	%edi, %eax
	subl	$1, %edi
	cmpl	$1, %edi
	jne	.L6
	rep ret
.L7:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	fact_while, .-fact_while
	.globl	loop_while
	.type	loop_while, @function
loop_while:
.LFB2:
	.cfi_startproc
	cmpl	%esi, %edi
	jge	.L11
	addl	%esi, %edi
	addl	%esi, %esi
	movl	$1, %eax
.L10:
	imull	%edi, %eax
	addl	$1, %edi
	cmpl	%esi, %edi
	jne	.L10
	rep ret
.L11:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	loop_while, .-loop_while
	.globl	loop_while_goto
	.type	loop_while_goto, @function
loop_while_goto:
.LFB3:
	.cfi_startproc
	movl	$1, %eax
	cmpl	%esi, %edi
	jge	.L13
	leal	(%rdi,%rsi), %edx
	addl	%esi, %esi
.L14:
	imull	%edx, %eax
	addl	$1, %edx
	cmpl	%esi, %edx
	jne	.L14
.L13:
	rep ret
	.cfi_endproc
.LFE3:
	.size	loop_while_goto, .-loop_while_goto
	.globl	fun_a
	.type	fun_a, @function
fun_a:
.LFB4:
	.cfi_startproc
	testl	%edi, %edi
	je	.L19
	movl	$0, %eax
.L18:
	xorl	%edi, %eax
	shrl	%edi
	jne	.L18
	jmp	.L17
.L19:
	movl	$0, %eax
.L17:
	andl	$1, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	fun_a, .-fun_a
	.globl	fact_for
	.type	fact_for, @function
fact_for:
.LFB5:
	.cfi_startproc
	cmpl	$1, %edi
	jle	.L23
	movl	$1, %eax
	movl	$2, %edx
.L22:
	imull	%edx, %eax
	addl	$1, %edx
	cmpl	%edx, %edi
	jge	.L22
	rep ret
.L23:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE5:
	.size	fact_for, .-fact_for
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
