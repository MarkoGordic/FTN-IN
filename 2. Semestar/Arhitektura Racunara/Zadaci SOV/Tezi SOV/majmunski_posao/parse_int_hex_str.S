.section .text

.globl parse_int_hex_str

parse_int_hex_str:
    pushl %ebp
    movl %esp, %ebp
    pushl %edi
    pushl %ebx
    pushl %esi
    pushl %ecx

    movl 12(%ebp), %edi     # string
    movl 8(%ebp), %eax      # broj
    movl $16, %ebx          # baza
    movl $0, %ecx           # brojac

dec_cifra:
    xorl %edx, %edx
    divl %ebx
    cmpl $9, %edx
    jg slovo
    addb $'0', %dl

dalje:
    movb %dl, (%edi)
    incl %edi
    incl %ecx
    andl %eax, %eax
    jnz dec_cifra
    jz pripremaObrni

slovo:
    subb $10, %dl
    addb $'A', %dl
    jmp dalje

pripremaObrni:
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