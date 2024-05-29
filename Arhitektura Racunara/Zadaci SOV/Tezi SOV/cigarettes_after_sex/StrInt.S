.section .text

.globl StrInt

StrInt:
    pushl %ebp 
    movl %esp, %ebp 
    pushl %ebx
    pushl %edi
    pushl %edx
    pushl %esi
    pushl %eax

    movl 8(%ebp), %edi
    
    xorl %eax, %eax
    xorl %ebx, %ebx
    movl $10, %esi

petlja: 
    cmpb $0, (%edi)
    je kraj
    mull %esi
    movb (%edi), %bl
    subb $'0', %bl
    addl %ebx, %eax
    incl %edi
    jmp petlja

kraj:

    popl %esi
    popl %edx
    popl %edi
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret