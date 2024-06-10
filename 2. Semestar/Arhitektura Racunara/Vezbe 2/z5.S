.section .data

n: .long 5
rez: .quad 0
greska: .byte 0

.section .text
.globl main

main:
    movl $1, %eax
    movl $0, %ebx
    movl $1, %ecx
    movl $0, %edx

fibonacci:
    cmpl $2, n
    jbe kraj
    
    addl %eax, %ecx
    adcl %ebx, %edx
    jc carry
    xchgl %eax, %ecx
    xchgl %ebx, %edx
    subl $1, n
    jmp fibonacci

carry:
    incb greska

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80