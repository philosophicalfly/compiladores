.string01:
	.string	"nao é mesmo oloco\n"
	.text
	.globl	main
	.type	main, @function

#tac begin func
main:
	pushq	%rbp

#tac print
	movq	%rsp, %rbp
	leaq	.string01(%rip), %rdi
	movl	$0, %eax
	call	printf
	nop

#tac enfun
	popq	%rbp
	ret
