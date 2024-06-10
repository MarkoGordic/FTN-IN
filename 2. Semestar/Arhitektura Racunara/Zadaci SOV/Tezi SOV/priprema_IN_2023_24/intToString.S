.section .text

.globl intToString
intToString:
    pushl %ebp
    movl %esp, %ebp
    pushl %edi
    pushl %ebx
    pushl %esi
    pushl %ecx

    movl 12(%ebp), %edi     # string
    movl 8(%ebp), %eax      # broj
    movl $10, %ebx          # baza
    movl $0, %ecx           # brojac

dec_cifra:
    xorl %edx, %edx
    divl %ebx
    addb $'0', %dl
    movb %dl, (%edi)
    incl %edi
    incl %ecx
    andl %eax, %eax
    jnz dec_cifra
    movb $0, (%edi)
    decl %edi
    movl 12(%ebp), %esi 

obrni:
    cmpl %edi, %esi
    jae kraj
    movb (%esi), %ah
    movb (%edi), %al
    movb %al, (%esi)
    movb %ah, (%edi)
    decl %edi
    incl %esi
    jmp obrni

kraj:

    movl %ecx, %eax

    popl %ecx
    popl %esi
    popl %ebx
    popl %edi
    movl %ebp, %esp
    popl %ebp
    ret