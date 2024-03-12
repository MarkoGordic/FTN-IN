.section .data

a: .quad 0x5
b: .quad 0x15
rez: .quad 0
greska: .byte 0

.section .text
.globl main

main:
    movl b, %eax
    movl b+4, %ebx

uporedi:
    cmpl $0, a
    jne dodaj
    cmpl $0, a+4
    je kraj

dodaj:
    addl %eax, rez
    adcl %ebx, rez+4
    jc carry
    subl $1, a
    sbbl $0, a+4
    jmp uporedi

carry:
    incb greska

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80