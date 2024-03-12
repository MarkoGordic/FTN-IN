.section .data
.section .text
.globl main

main:
    movl $3, %eax
    movl $5, %ebx
    movl $0, %ecx
saberi:
    addl %ebx, %ecx
    decl %eax
    cmpl $0, %eax
    je kraj
    jmp saberi
kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80