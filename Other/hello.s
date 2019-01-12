	.file	"hello.c"
	.globl	flag
	.data
	.align 4
	.type	flag, @object
	.size	flag, 4
flag:
	.long	1
	.comm	z,4,4
	.text
	.globl	getFlag
	.type	getFlag, @function
getFlag:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	flag(%rip), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	getFlag, .-getFlag
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, %eax
	call	getFlag
	movl	%eax, -4(%rbp)
	movl	flag(%rip), %eax
	movl	%eax, -4(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.data
	.align 4
	.type	w.1800, @object
	.size	w.1800, 4
w.1800:
	.long	3
	.local	y.1799
	.comm	y.1799,4,4
	.ident	"GCC: (GNU) 7.2.1 20170915 (Red Hat 7.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
