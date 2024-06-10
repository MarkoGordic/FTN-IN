.section .data

poruka: .ascii "Unesite izgubljeni citat: "
poruka_len = . - poruka

poruka_izlaz: .ascii "Izgubljeni citat je: "
poruka_izlaz_len = . - poruka_izlaz

unos: .fill 201, 1, 42

.section .text
.global main
main:
    movl $4, %eax
    movl $1, %ebx
    movl $poruka, %ecx
    movl $poruka_len, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    movl $unos, %ecx
    movl $201, %edx
    int $0x80

    movl %eax, %esi
    leal unos, %eax

petlja:
    cmpb $10, (%eax)
    je obrni_priprema

    cmpb $'1', (%eax)
    je zameni_1
    cmpb $'3', (%eax)
    je zameni_3
    cmpb $'4', (%eax)
    je zameni_4
    cmpb $'5', (%eax)
    je zameni_5
    cmpb $'0', (%eax)
    je zameni_0

dalje:
    incl %eax
    jmp petlja

zameni_1:
    movb $'i', (%eax)
    jmp dalje
zameni_3:
    movb $'e', (%eax)
    jmp dalje
zameni_4:
    movb $'a', (%eax)
    jmp dalje
zameni_5:
    movb $'s', (%eax)
    jmp dalje
zameni_0:
    movb $'o', (%eax)
    jmp dalje

obrni_priprema:
    decl %eax
    leal unos, %ebx
obrni:
    cmpl %eax, %ebx
    jae kraj

    movb (%eax), %dl
    movb (%ebx), %dh
    movb %dl, (%ebx)
    movb %dh, (%eax)

    incl %ebx
    decl %eax

    jmp obrni

kraj:
    movl $4, %eax
    movl $1, %ebx
    movl $poruka_izlaz, %ecx
    movl $poruka_izlaz_len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal unos, %ecx
    movl %esi, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80