.section .data
.section .text
.globl main

main:
    movl $5, %eax
    movl $0, %ebx

saberi:
    addl %eax, %ebx
    decl %eax
    cmpl $0, %eax
    je kraj
    jmp saberi
kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80