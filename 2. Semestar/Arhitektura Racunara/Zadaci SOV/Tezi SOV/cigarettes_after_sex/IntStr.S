.section .text

.globl IntStr

IntStr:
    pushl %ebp 
    movl %esp, %ebp 
    pushl %ecx
    pushl %ebx
    pushl %edi
    pushl %edx
    pushl %esi

    movl 8(%ebp), %ecx
    movl 12(%ebp), %eax
    movl $0, %edi # brojac
    
    movl $10, %ebx

petlja:
    xorl %edx, %edx
    divl %ebx
    addb $'0', %dl 
    movb %dl, (%ecx)
    incl %edi
    incl %ecx
    andl %eax, %eax
    jnz petlja
    movb $0, (%ecx)
    decl %ecx
    movl 8(%ebp), %esi

obrni:
    cmpl %esi, %ecx
    jle kraj
    movb (%esi), %bl
    movb (%ecx), %bh
    movb %bl, (%ecx)
    movb %bh, (%esi)
    decl %ecx
    incl %esi
    jmp obrni

kraj:
    movl %edi, %eax

    popl %esi
    popl %edx
    popl %edi
    popl %ebx
    popl %ecx
    movl %ebp, %esp
    popl %ebp
    ret