.section .data

poruka: .ascii "Unesite tekst: "
poruka_len = . - poruka

unos: .fill 101, 1, 42

.section .text
.globl main
main:
    movl $4, %eax
    movl $1, %ebx
    movl $poruka, %ecx
    movl $poruka_len, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    movl $unos, %ecx
    movl $101, %edx
    int $0x80

    leal unos, %ecx     # adresa unosa
    movl $0, %eax       # brojac

petlja:
    cmpb $10, (%ecx)
    je podeli

    cmpb $'.', (%ecx)
    je povecaj_brojac
    cmpb $',', (%ecx)
    je povecaj_brojac
    cmpb $'?', (%ecx)
    je povecaj_brojac
    cmpb $'!', (%ecx)
    je povecaj_brojac
dalje:
    incl %ecx
    jmp petlja

povecaj_brojac:
    incl %eax
    jmp dalje

podeli:
    movl $0, %edx
    movl $2, %esi

    divl %esi

    movl %eax, %edi
kraj:
    movl $1, %eax
    movl %edi, %ebx
    int $0x80