.section .data

poruka: .ascii "Unesite string: \0"
por_len = . - poruka
ulaz: .fill 51,1,42

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

    movl $ulaz, %eax
    movl $100, %esi         # najmanji broj
    movl $0, %edi           # najveci broj
    movl $0, %edx
    
petlja:
    cmpb $10, (%eax)
    je kraj_provera
    cmpb $'0', (%eax)
    jb dalje
    cmpb $'9', (%eax)
    ja dalje

    movb (%eax), %dl        # pomeramo trenutni karakter u edx

    # ako jos uvek nismo nasli cifru, postaljamo i min i max na prvu koju pronadjemo
    cmpl $100, %esi
    je prva_cifra

    # ako smo pronasli, proveravamo min i max
    cmpl %edx, %esi
    jl minimum
    cmpl %edx, %edi
    ja maximum

dalje:
    incl %eax
    jmp petlja

minimum:
    movl %edx, %esi
    jmp dalje

maximum:
    movl %edx, %edi
    jmp dalje

prva_cifra:
    movl %edx, %esi
    movl %edx, %edi
    jmp dalje

kraj_provera:
    cmpl $100, %esi
    jne kraj
    movl $1, %eax
    movl $0, %ebx
    int $0x80

kraj:
    movl $1, %eax
    movl $0, %ebx
    addl %esi, %ebx
    addl %edi, %ebx
    int $0x80