.section .data
.section .text
.globl main

main:
    movl $10, %eax
    subl $2, %eax
    
    movl $1, %ebx
    movl $1, %ecx
saberi:
    addl %ebx, %ecx
    decl %eax
    cmp $0, %eax
    je kraj
    addl %ecx, %ebx
    decl %eax
    cmp $0, %eax
    je kraj
    jmp saberi
kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80