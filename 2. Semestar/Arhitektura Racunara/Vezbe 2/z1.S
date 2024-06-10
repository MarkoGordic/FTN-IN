.section .data

a: .quad 0x41835913
b: .quad 0x41435913

.section .text
.globl main

main:
    movl a+4, %ebx
    cmpl b+4, %ebx
    jg prvi_veci
    jl drugi_veci
    
    movl a, %ebx
    cmpl b, %ebx
    ja prvi_veci
    jb drugi_veci

    movl $0, %eax
    jmp kraj

prvi_veci:
    movl $1, %eax
    jmp kraj

drugi_veci:
    movl $-1, %eax
    jmp kraj

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80