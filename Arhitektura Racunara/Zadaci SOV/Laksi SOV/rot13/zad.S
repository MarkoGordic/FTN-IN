.section .data

poruka: .ascii "Unesite string: \0"
por_len = . - poruka
poruka1: .ascii "Enkodovan string: \0"
por1_len = . - poruka1
ulaz: .fill 51,1,42
izlaz: .fill 51,1,42

.section .text
.globl main
main:
    movl $4, %eax
    movl $1, %ebx
    leal poruka, %ecx
    movl $por_len, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    leal ulaz, %ecx
    movl $51, %edx
    int $0x80

    movl  %eax, %esi

    movl $ulaz, %eax

petlja:
    cmpb $10, (%eax)
    je kraj
    cmpb $'a', (%eax)
    jl provera_velika   # nisu mala slova
    cmpb $'z', (%eax)
    ja dalje            # nije slovo uopste

    # jeste malo slovo
    cmpb $'m', (%eax)
    jl uvecaj
    subb $13, (%eax)
    jmp dalje

provera_velika:
    cmpb $'A', (%eax)
    jl dalje   # nisu velika slova
    cmpb $'Z', (%eax)
    ja dalje   # nisu velika slova

    # jeste veliko slovo
    cmpb $'M', (%eax)
    jl uvecaj
    subb $13, (%eax)
    jmp dalje

uvecaj:
    addb $13, (%eax)
    jmp dalje

dalje:
    incl %eax
    jmp petlja

kraj:
    movl $4, %eax
    movl $1, %ebx
    leal poruka1, %ecx
    movl $por1_len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal ulaz, %ecx
    movl %esi, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80