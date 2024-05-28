.section .data

poruka: .ascii "Unesite string: "
poruka_len = . - poruka

unos: .fill 101, 1, 42

tacno: .ascii "Tacno!\n"
tacno_len = . - tacno

netacno: .ascii "Netacno!\n"
netacno_len = . - netacno

.section .text
.globl main
main:
    movl $4, %eax
    movl $1, %ebx
    leal poruka, %ecx
    movl $poruka_len, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    leal unos, %ecx
    movl $101, %edx
    int $0x80

    leal unos, %eax

    movl $0, %esi   # brojac prva rec
    movl $0, %edi   # brojac druga rec

petlja:
    cmpb $'=', (%eax)
    je obradi_znak
    cmpb $'>', (%eax)
    je obradi_znak
    cmpb $'<', (%eax)
    je obradi_znak
    
    incl %esi
    incl %eax

    jmp petlja

obradi_znak:
    movb (%eax), %dl
    incl %eax

petlja2:
    cmpb $10, (%eax)
    je uporedi

    incl %edi
    incl %eax

    jmp petlja2

uporedi:
    cmpb $'=', %dl
    je proveri_jednako
    cmpb $'>', %dl
    je proveri_vece
    cmpb $'<', %dl
    je proveri_manje

proveri_jednako:
    cmpl %esi, %edi
    je kraj_tacno
    jne kraj_netacno

proveri_vece:
    cmpl %esi, %edi
    jl kraj_tacno
    jmp kraj_netacno

proveri_manje:
    cmpl %esi, %edi
    jg kraj_tacno
    jmp kraj_netacno

kraj_tacno:
    movl $4, %eax
    movl $1, %ebx
    leal tacno, %ecx
    movl $tacno_len, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80

kraj_netacno:
    movl $4, %eax
    movl $1, %ebx
    leal netacno, %ecx
    movl $netacno_len, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80