.section .text

.globl stringToInt
stringToInt:
    pushl %ebp
    movl %esp,%ebp
    pushl %esi
    pushl %ebx
    pushl %ecx

    movl 8(%ebp), %ecx  # string
    movl $10, %esi      # baza
    xorl %eax, %eax     # postavljamo eax na 0
    xorl %ebx, %ebx     # postavljamo ebx na 0

cifra:
    cmpb $0,(%ecx)
    je kraj
    movb (%ecx), %bl
    subb $'0', %bl
    mull %esi
    addl %ebx, %eax
    incl %ecx
    jmp cifra
    
kraj:
    popl %ecx
    popl %ebx
    popl %esi
    movl %ebp, %esp
    popl %ebp
    ret