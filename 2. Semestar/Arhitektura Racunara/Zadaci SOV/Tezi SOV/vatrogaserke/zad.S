.section .data
poruka1: .ascii "Unesite informacije o vatrogaserkama: "
poruka1len= . - poruka1
greska: .ascii "Došlo je do greške tokom rada programa!\n"
greskalen= . - greska
kraj1: .ascii "Aleks je ukupno potrošila "
kraj1len=. - kraj1
kraj2: .ascii " litara vode.\n"
kraj2len=. - kraj2
kraj3: .ascii "Jomi je ukupno potrošila "
kraj3len=. - kraj3
kraj4: .ascii " je potrošila više vode od "
kraj4len= . - kraj4
alekss: .ascii "Aleks"
aleksslen= . - alekss
jomii: .ascii "Jomi"
jomiilen=. - jomii
noviRed: .ascii ".\n"
noviRedlen =. - noviRed

unos: .fill 200,1,42
pomocniBroj: .fill 10,1,42
izlazJomi: .fill 20,1,42
izlazAleks: .fill 20,1,42

sumaAleks: .long 0
sumaJomi: .long 0
duzinaStrJ: .long 0
duzinaStrA: .long 0

.section .text

.globl main
main:
    movl $4, %eax
    movl $1, %ebx
    leal poruka1, %ecx
    movl $poruka1len, %edx
    int $0x80    

    movl $3, %eax
    movl $0, %ebx
    leal unos, %ecx
    movl $200, %edx
    int $0x80   
    
    leal unos, %ecx

glavnaPetlja:
    cmpb $10, (%ecx)
    je uporedi
    cmpb $'Z', (%ecx)
    je zaposleni
    incl %ecx
    jmp glavnaPetlja

zaposleni:
    addl $2, %ecx
    cmpb $'A', (%ecx)
    je aleks
    cmpb $'J', (%ecx)
    je Jomi
    jmp krajGreska

aleks:
    addl $4, %ecx
    cmpb $'0', (%ecx)
    jne krajGreska
    incl %ecx
    cmpb $'x', (%ecx)
    jne krajGreska
    incl %ecx
    leal pomocniBroj, %edx

pripremaUlaz:
    cmpb $10, (%ecx)
    je konvertStrIntA
    cmpb $',', (%ecx)
    je konvertStrIntA
    cmpb $'0', (%ecx)
    jl krajGreska
    cmpb $'9', (%ecx)
    jle dalje
    cmpb $'A', (%ecx)
    jl krajGreska
    cmpb $'Z', (%ecx)
    jle dalje
    cmpb $'a', (%ecx)
    jl krajGreska
    cmpb $'z', (%ecx)
    jg krajGreska

dalje:
    movb (%ecx), %bl
    movb %bl, (%edx)
    incl %edx
    incl %ecx
    jmp pripremaUlaz

konvertStrIntA:
    movb $0, (%edx)
    leal pomocniBroj, %edx

    pushl %edx
    call parseStrInt
    addl $4, %esp

    cmpl $1, %eax
    je krajGreska

    addl %eax, sumaAleks
    jc krajGreska

    jmp glavnaPetlja

Jomi:
    addl $4, %ecx
    cmpb $'0', (%ecx)
    jne krajGreska
    incl %ecx
    cmpb $'x', (%ecx)
    jne krajGreska
    incl %ecx
    leal pomocniBroj, %edx

pripremaUlazJ:
    cmpb $10, (%ecx)
    je konvertStrIntJ
    cmpb $',', (%ecx)
    je konvertStrIntJ
    cmpb $'0', (%ecx)
    jl krajGreska
    cmpb $'9', (%ecx)
    jle daljeJ
    cmpb $'A', (%ecx)
    jl krajGreska
    cmpb $'Z', (%ecx)
    jle daljeJ
    cmpb $'a', (%ecx)
    jl krajGreska
    cmpb $'z', (%ecx)
    jg krajGreska

daljeJ:
    movb (%ecx), %bl
    movb %bl, (%edx)
    incl %edx
    incl %ecx
    jmp pripremaUlazJ

konvertStrIntJ:
    movb $0, (%edx)
    leal pomocniBroj, %edx

    pushl %edx
    call parseStrInt
    addl $4, %esp

    cmpl $1, %eax
    je krajGreska

    addl %eax, sumaJomi
    jc krajGreska

    jmp glavnaPetlja

uporedi:
    movl sumaJomi, %ebx
    movl sumaJomi, %ecx
    leal izlazJomi, %edi

    pushl %ecx
    pushl %edi
    call IntStr
    addl $8, %esp

    movl %eax, duzinaStrJ

    movl sumaAleks, %ecx
    leal izlazAleks, %edi

    pushl %ecx
    pushl %edi
    call IntStr
    addl $8, %esp

    movl %eax, duzinaStrA

    cmpl %ebx, sumaAleks
    jl krajJomi
    jg krajAleks

krajJomi:
    movl $4, %eax
    movl $1, %ebx
    leal kraj1, %ecx
    movl $kraj1len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal izlazAleks, %ecx
    movl duzinaStrA, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj2, %ecx
    movl $kraj2len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj3, %ecx
    movl $kraj3len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal izlazJomi, %ecx
    movl duzinaStrJ, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj2, %ecx
    movl $kraj2len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal jomii, %ecx
    movl $jomiilen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj4, %ecx
    movl $kraj4len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal alekss, %ecx
    movl $aleksslen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal noviRed, %ecx
    movl $noviRedlen, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80

krajAleks:
    movl $4, %eax
    movl $1, %ebx
    leal kraj1, %ecx
    movl $kraj1len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal izlazAleks, %ecx
    movl duzinaStrA, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj2, %ecx
    movl $kraj2len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj3, %ecx
    movl $kraj3len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal izlazJomi, %ecx
    movl duzinaStrJ, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj2, %ecx
    movl $kraj2len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal alekss, %ecx
    movl $aleksslen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj4, %ecx
    movl $kraj4len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal jomii, %ecx
    movl $jomiilen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal noviRed, %ecx
    movl $noviRedlen, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80

krajGreska:
    movl $4, %eax
    movl $1, %ebx
    leal greska, %ecx
    movl $greskalen, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80