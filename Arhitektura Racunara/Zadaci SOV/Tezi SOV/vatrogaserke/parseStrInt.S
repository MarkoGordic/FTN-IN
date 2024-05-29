.section .text

.globl parseStrInt
parseStrInt:
    pushl %ebp 
    movl %esp, %ebp 
    pushl %ebx 
    pushl %ecx
    pushl %edx
    pushl %edi
    pushl %esi

    movl 8(%ebp), %esi
    movl $16, %edi

    xorl %eax, %eax
    xorl %ebx, %ebx
    xorl %edx, %edx

petlja:
    cmpb $0, (%esi)
    je kraj
    cmpb $'9', (%esi)
    jle cifra
    cmpb $'Z', (%esi)
    jle slovoV
    cmpb $'z', (%esi)
    jle slovoM
    jg kraj

cifra:
    mull %edi
    cmpl $0, %edx
    jne greska
    movb (%esi), %bl
    subb $'0', %bl
    addl %ebx, %eax
    incl %esi
    jmp petlja

slovoV:
    subl $'A', (%esi)
    addl $10, (%esi)

hexCifra:
    mull %edi
    cmpl $0, %edx
    jne greska
    movb (%esi), %bl
    addl %ebx, %eax
    incl %esi
    jmp petlja

slovoM:
    subl $'a', (%esi)
    addl $10, (%esi)
    jmp hexCifra

kraj:
    popl %esi
    popl %edi
    popl %edx
    popl %ecx
    popl %ebx
    movl %ebp, %esp 
    popl %ebp
    ret

greska:
    movl $1, %eax

    popl %esi
    popl %edi
    popl %edx
    popl %ecx
    popl %ebx
    movl %ebp, %esp 
    popl %ebp
    ret