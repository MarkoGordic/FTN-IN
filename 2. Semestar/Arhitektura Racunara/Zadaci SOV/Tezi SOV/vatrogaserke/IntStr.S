.section .text

.globl IntStr

IntStr:
    pushl %ebp 
    movl %esp, %ebp 
    pushl %ebx 
    pushl %ecx
    pushl %edx
    pushl %eax
    pushl %edi
    pushl %esi

    movl 12(%ebp), %eax
    movl 8(%ebp), %ecx
    movl $10, %ebx
    movl $0, %edi

petlja:
    xorl %edx, %edx
    divl %ebx
    addb $'0', %dl
    movb %dl, (%ecx)
    incl %ecx
    incl %edi
    andl %eax, %eax
    jnz petlja
    movb $0, (%ecx)
    decl %ecx
    movl 8(%ebp), %eax

obrni:
    cmpl %eax, %ecx
    jle kraj
    movb (%ecx), %bl
    movb (%eax), %bh
    movb %bl, (%eax)
    movb %bh, (%ecx)
    incl %eax
    decl %ecx
    jmp obrni

kraj:
    movl %edi, %eax
    
    popl %esi
    popl %edi
    popl %edx
    popl %ecx
    popl %ebx
    movl %ebp, %esp 
    popl %ebp
    ret