	.file	"merge.c"
	.text
	.globl	merge
	.type	merge, @function
merge:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$1, %eax
	movl	$0, %r9d
	movl	$0, %r8d
	jmp	.L2
.L5:
	movq	(%rdi,%r8,8), %r11
	movq	(%rsi,%r9,8), %r10
	cmpq	%r10, %r11
	jge	.L3
	addq	$1, %r8
	movq	%r11, -8(%rdx,%rax,8)
	jmp	.L4
.L3:
	addq	$1, %r9
	movq	%r10, -8(%rdx,%rax,8)
.L4:
	addq	$1, %rax
.L2:
	leaq	-1(%rax), %r10
	movq	%r10, %r11
	cmpq	%rcx, %r8
	jge	.L11
	cmpq	%rcx, %r9
	jl	.L5
.L11:
	cmpq	%rcx, %r8
	jge	.L7
	movq	%r8, %rbp
	movq	%rcx, %rbx
	subq	%r8, %rbx
	leaq	(%rdi,%r8,8), %r11
	leaq	(%rdx,%r10,8), %r8
	movl	$0, %eax
.L8:
	movq	(%r11,%rax,8), %rdi
	movq	%rdi, (%r8,%rax,8)
	addq	$1, %rax
	cmpq	%rbx, %rax
	jne	.L8
	leaq	(%r10,%rcx), %r11
	subq	%rbp, %r11
.L7:
	cmpq	%rcx, %r9
	jge	.L1
	subq	%r9, %rcx
	leaq	(%rsi,%r9,8), %rdi
	leaq	(%rdx,%r11,8), %rsi
	movl	$0, %eax
.L10:
	movq	(%rdi,%rax,8), %rdx
	movq	%rdx, (%rsi,%rax,8)
	addq	$1, %rax
	cmpq	%rcx, %rax
	jne	.L10
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	merge, .-merge
	.globl	merge2
	.type	merge2, @function
merge2:
.LFB24:
	.cfi_startproc
	testq	%rcx, %rcx
	jle	.L28
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	$0, %r11d
	movl	$0, %r10d
	movl	$0, %r9d
	movl	$1, %ebp
.L17:
	movq	(%rdi,%r9,8), %rax
	movq	(%rsi,%r10,8), %r12
	cmpq	%r12, %rax
	setl	%r8b
	addq	$1, %r11
	movq	%r11, %rbx
	cmpq	%r12, %rax
	cmovg	%r12, %rax
	movq	%rax, -8(%rdx,%r11,8)
	movzbl	%r8b, %eax
	addq	%rax, %r9
	movzbl	%r8b, %r8d
	movl	%ebp, %eax
	subl	%r8d, %eax
	cltq
	addq	%rax, %r10
	cmpq	%r9, %rcx
	jle	.L22
	cmpq	%r10, %rcx
	jg	.L17
.L22:
	cmpq	%r9, %rcx
	jle	.L19
	movq	%r9, %rbp
	movq	%rcx, %r11
	subq	%r9, %r11
	leaq	(%rdi,%r9,8), %r9
	leaq	(%rdx,%rbx,8), %r8
	movl	$0, %eax
.L20:
	movq	(%r9,%rax,8), %rdi
	movq	%rdi, (%r8,%rax,8)
	addq	$1, %rax
	cmpq	%rax, %r11
	jne	.L20
	leaq	(%rcx,%rbx), %r11
	subq	%rbp, %r11
.L19:
	cmpq	%r10, %rcx
	jle	.L15
	subq	%r10, %rcx
	leaq	(%rsi,%r10,8), %rdi
	leaq	(%rdx,%r11,8), %rsi
	movl	$0, %eax
.L21:
	movq	(%rdi,%rax,8), %rdx
	movq	%rdx, (%rsi,%rax,8)
	addq	$1, %rax
	cmpq	%rax, %rcx
	jne	.L21
.L15:
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_restore 12
	.cfi_def_cfa_offset 8
.L28:
	rep ret
	.cfi_endproc
.LFE24:
	.size	merge2, .-merge2
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
