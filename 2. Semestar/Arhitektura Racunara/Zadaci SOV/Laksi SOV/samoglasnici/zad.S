.section .data

poruka: .ascii "Unesi string: \0"
por_len = . - poruka
ulaz: .fill 41,1,42
zbir_ostataka_samoglasnika: .long 0

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
    movl $41, %edx
    int $0x80

    movl $ulaz, %ecx
    movl $3, %esi
    
petlja:
    cmpb $10, (%ecx)
    je kraj
    cmpb $'a', (%ecx)
    je obradi_samoglasnik
    cmpb $'e', (%ecx)
    je obradi_samoglasnik
    cmpb $'i', (%ecx)
    je obradi_samoglasnik
    cmpb $'o', (%ecx)
    je obradi_samoglasnik
    cmpb $'u', (%ecx)
    je obradi_samoglasnik
    cmpb $'A', (%ecx)
    je obradi_samoglasnik
    cmpb $'E', (%ecx)
    je obradi_samoglasnik
    cmpb $'I', (%ecx)
    je obradi_samoglasnik
    cmpb $'O', (%ecx)
    je obradi_samoglasnik
    cmpb $'U, (%ecx)
    je obradi_samoglasnik
    incl %ecx
    jmp petlja

obradi_samoglasnik:
    movl $0, %eax       # pripremamo eax za deljenje, postavljamo na 0
    movb (%ecx), %al    # ucitavamo karakter u al (nize bitove eax-a)
    movl $0, %edx       # pripremamo edx za deljenje

    divl %esi           # delimo eax sa esi, rezultat u eax, ostatak u edx
    
    addl %edx, zbir_ostataka_samoglasnika
    incl %ecx
    jmp petlja

kraj:
    movl $1, %eax
    movl zbir_ostataka_samoglasnika, %ebx
    int $0x80