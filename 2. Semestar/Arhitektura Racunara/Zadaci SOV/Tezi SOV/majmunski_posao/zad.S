.section .data

unos1: .ascii "Unesite majmunski izvestaj: "
unos1len=. - unos1
dobarPosao: .ascii "Majmuni su odlično odradili posao tokom "
dobarlen= . - dobarPosao
dani: .ascii " dana.\n"
danilen= . - dani
majmunisanje: .ascii "Majmuni su izmajmunisali "
majmunisanjelen= . - majmunisanje
poruka: .ascii "Tokom izmajmunisanih dana, majmuni su ubrali "
porukalen= . - poruka
banana: .ascii " banana.\n"
bananalen=. - banana
pocetnistr: .fill 200,1,42

brojacDaniD: .long 0
brojacDaniM: .long 0
ukupnoBanana: .long 0

pomocniBanana: .fill 10,1,42
pomocniHex: .fill 20,1,42
brojHex: .long 0

brojDanaD: .fill 1,1,42
brojDanaM: .fill 1,1,42

.section .text

.globl main
main:
    movl $4, %eax
    movl $1, %ebx
    leal unos1, %ecx
    movl $unos1len, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    leal pocetnistr, %ecx
    movl $200, %edx
    int $0x80

    leal pocetnistr, %ecx 

glavnaPetlja:
    cmpb $10, (%ecx)
    je konvertujUString
    cmpb $'B', (%ecx)
    je pomeriza2 
    incl %ecx
    jmp glavnaPetlja

pomeriza2:
    addl $2, %ecx
    leal pomocniBanana, %edx

slovoB:
    cmpb $' ', (%ecx)
    je hexStrToDecInt
    cmpb $10, (%ecx)
    je hexStrToDecInt
    movb (%ecx), %bl
    movb %bl, (%edx)
    incl %ecx
    incl %edx
    jmp slovoB

hexStrToDecInt:
    movb $0, (%edx)
    leal pomocniBanana, %edx
    
    pushl %edx 
    call parse_hex_str_int
    addl $4,%esp

    # Uporedjujemo rezultat sa 1000
    cmpl $1000, %eax
    jl izmajmunisano 
    addl $1, brojacDaniD 
    jmp glavnaPetlja

izmajmunisano:
    addl $1,brojacDaniM
    addl %eax, ukupnoBanana
    jmp glavnaPetlja

konvertujUString:
    addb $'0', brojacDaniD
    movb brojacDaniD, %bl
    movb %bl, brojDanaD

    addb $'0', brojacDaniM
    movb brojacDaniM, %bl
    movb %bl, brojDanaM

    leal pomocniHex, %ecx
    movl ukupnoBanana, %ebx
    pushl %ecx
    pushl %ebx
    call parse_int_hex_str
    addl $4, %esp

    movl %eax, brojHex

kraj:
    movl $4, %eax
    movl $1, %ebx
    leal dobarPosao, %ecx
    movl $dobarlen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal brojDanaD, %ecx
    movl $1, %edx
    int $0x80
    
    movl $4, %eax
    movl $1, %ebx
    leal dani, %ecx
    movl $danilen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal majmunisanje, %ecx
    movl $majmunisanjelen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal brojDanaM, %ecx
    movl $1, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal dani, %ecx
    movl $danilen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal poruka, %ecx
    movl $porukalen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal pomocniHex, %ecx
    movl brojHex, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal banana, %ecx
    movl $bananalen, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80