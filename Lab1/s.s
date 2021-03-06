
#--------------------- s.s file --------------------------
         .global main, mymain, myprintf

main:
# (1). Write ASSEMBLY code to call myprintf(FMT)
        pushl %ebp
        movl  %esp, %ebp

#------ call myprintf() ----------------------------------
        pushl $FMT

        call  myprintf
	add $8, %esp
#---------------------------------------------------------




# (2). Write ASSEMBLY code to call mymain(argc, argv, env)
#      HELP: When crt0.o calls main(int argc, char *argv[], char *env[]), 
#            it passes argc, argv, env to main(). 
#            Draw a diagram to see where are argc, argv, env?
#	pushl 16(%ebp) # Push env
#	pushl 12(%ebp) # Push argv
#	pushl 8(%ebp) # Push argc
	popl %ebp
	call mymain

# (3). Write code to call myprintf(fmt,a,b)	
#      HELP: same as in (1) above

        pushl b
        pushl a 
        pushl $fmt

        call  myprintf
	addl  $12, %esp

# (4). Return to caller
        movl  %ebp, %esp
	popl  %ebp
	movl $1, %eax
	movl $0, %ebx
	ret

#---------- DATA section of assembly code ---------------
	.data
FMT:	.asciz "main() in assembly call mymain() in C\n"
a:	.long 1234
b:	.long 5678
fmt:	.asciz "a=%d b=%d\n"
#---------  end of s.s file ----------------------------
