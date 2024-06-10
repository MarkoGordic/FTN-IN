.section .data

poruka: .ascii "Unesite string: "
poruka_len = . - poruka

poruka2: .ascii "U unetom stringu najmanji kod ima slovo: "
poruka2_len = . - poruka2

poruka_nema_slova: .ascii "U unetom stringu nema slova!\n"
poruka_nema_slova_len = . - poruka_nema_slova

unos: .fill 51, 1, 42

karakter: .fill 2, 1, 42

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
    movl $51, %edx
    int $0x80

    leal unos, %eax
    movl $123, %esi     # minimalni ASCII (ukoliko ne pronadjemo, bice 123)
    movl $0, %edx

petlja:
    cmpb $10, (%eax)
    je odredi_kraj
    cmpb $'A', (%eax)
    jl dalje
    cmpb $'Z', (%eax)
    jle provera_min
    cmpb $'a', (%eax)
    jl dalje
    cmpb $'z', (%eax)
    jg dalje

provera_min:
    movb (%eax), %dl
    cmpl %esi, %edx
    jl postavi_min
    jmp dalje

postavi_min:
    movl %edx, %esi

dalje:
    incl %eax
    jmp petlja

odredi_kraj:
    cmpl $123, %esi
    je kraj_nema_slova
    jne kraj

kraj_nema_slova:
    movl $4, %eax
    movl $1, %ebx
    movl $poruka_nema_slova, %ecx
    movl $poruka_nema_slova_len, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80

kraj:
    movl %esi, %ebx         # u %ebx je najmanji karakter
    leal karakter, %edi     # u %edi je adresa promenljive karakter
    movb %bl, (%edi)

    incl %edi
    movb $'\n', (%edi)

    movl $4, %eax
    movl $1, %ebx
    movl $poruka2, %ecx
    movl $poruka2_len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal karakter, %ecx
    movl $2, %edx
    int $0x80

    movl $1, %eax
    movl %esi, %ebx
    int $0x80