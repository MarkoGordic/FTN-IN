.section .data

poruka: .ascii "Unesite rec: \0"
poruka_len = . - poruka
unos: .fill 11,1,42
bigramNiz: .fill 40,1,42
razmak: .long 1

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
    movl $11, %edx
    int $0x80

    leal unos, %eax
    leal bigramNiz, %edx
    movl $0, %ecx
    movl $0, %ebx

petlja:
    cmpb $10, (%eax)
    je kraj

    cmpl $0, %ecx       # proveravamo da li trenutno obradjujemo prvi karakter
    je prvi_karakter

    cmpl $1, razmak
    je ima_razmaka
    jne nema_razmaka

ima_razmaka:
    movb $' ', (%edx)
    incl %edx
    incl %ecx
nema_razmaka:
    movb %bl, (%edx)    # kopiramo prethodni karakter
    incl %edx
    movb (%eax), %bl    # uzimamo sledeci karakter
    movb %bl, (%edx)    # kopiramo sledeci karakter

    incl %edx
    incl %eax
    
    addl $2, %ecx       # uvecavamo brojac za 2, posto smo dodali 2 karaktera u edx

    jmp petlja

prvi_karakter:
    movb (%eax), %bl    # ebx uvek koritimo za cuvanje prethodnog karaktera
    movb %bl, (%edx)    # pomeramo prvi karakter
    incl %eax
    incl %edx
    
    movb (%eax), %bl
    movb %bl, (%edx)
    incl %eax
    incl %edx
    
    addl $2, %ecx        # obradili smo prva dva karaktera
    jmp petlja

kraj:
    movb $10, (%edx)    # dodajemo enter na kraj stringa, za lepsi ispis
    incl %ecx

    movl $4, %eax
    movl $1, %ebx
    movl %ecx, %edx         # prvo prebacujemo %ecx, jer smo ga koristili kao brojac
    leal bigramNiz, %ecx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80