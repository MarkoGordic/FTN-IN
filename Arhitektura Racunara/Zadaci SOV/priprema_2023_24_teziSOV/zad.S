.section .data

poruka: .ascii "Unesite namirnice: \n"
porukalen= . - poruka
unos: .fill 1000,1,42
kal: .ascii "Ukupno kalorija: "
kallen= . - kal
protein: .ascii "Protein: "
proteinlen=. - protein
uglj: .ascii "Ugljeni-hidrati: "
ugljlen= . - uglj
masti: .ascii "Masti: "
mastilen=. - masti
slovog: .ascii "g\n"
slovoglen= . - slovog
novired: .ascii "\n"
noviredlen= . - novired
greska: .ascii "Pogresna oznaka makro-nutrijenata\n"
greskalen= . - greska

proteini: .long 0
hidrati: .long 0
mast: .long 0

pomocni: .fill 4,1,0

str_proteini: .fill 4,1,0
str_hidrati: .fill 4,1,0
str_masti: .fill 4,1,0
str_kalorije: .fill 5,1,0

duzina_proteina: .long 0
duzina_hidrata: .long 0
duzina_masti: .long 0
duzina_kalorija: .long 0

.section .text

.globl main
main:
    movl $4, %eax
    movl $1, %ebx
    leal poruka, %ecx
    movl $porukalen, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    leal unos, %ecx
    movl $1000, %edx
    int $0x80

    leal unos,%ecx

glavnaPetlja:
    cmpb $10,(%ecx) # da li smo dosli do entera (kraja stringa)
    je konvertuj_u_str

    cmpb $':',(%ecx)
    je provera_p
    incl %ecx
    jmp glavnaPetlja

provera_p:
   addl $2, %ecx
   cmpb $'P',(%ecx)
   je prebroj_proteine
   jmp greska_kraj

prebroj_proteine:
    addl $2, %ecx
    leal pomocni, %edx # pomeramo pomocu promenljivu za broj (str) u edx

# petlja koja kopira brojeve do space-a u pomocnu promenljivu
petlja_proteini:
    movb (%ecx), %bl
    movb %bl, (%edx) 
    incl %ecx
    incl %edx
    cmpb $' ', (%ecx)
    je konvertuj_int_P
    jmp petlja_proteini

konvertuj_int_P:
    movb $0, (%edx) # stavljamo NULL na kraj stringa
    leal pomocni, %edx # resetujemo pokaazivac na pocetak pomocne promenljive

    pushl %edx
    call stringToInt
    addl $4, %esp
    
    addl %eax, proteini # dodajemo vrednost broja u proteine

prebroj_hidrate:
    addl $1, %ecx
    cmpb $'C',(%ecx)
    jne greska_kraj
    addl $2, %ecx
    leal pomocni, %edx # pomeramo pomocu promenljivu za broj (str) u edx

petlja_hidrati:
    movb (%ecx), %bl
    movb %bl, (%edx)
    incl %ecx
    incl %edx
    cmpb $' ', (%ecx)
    je konvertuj_int_C
    jmp petlja_hidrati

konvertuj_int_C:
    movb $0, (%edx) # stavljamo NULL na kraj stringa
    leal pomocni, %edx # resetujemo pokaazivac na pocetak pomocne promenljive

    pushl %edx
    call stringToInt
    addl $4, %esp
    
    addl %eax, hidrati # dodajemo vrednost broja u hidrate

prebroj_masti:
    addl $1, %ecx
    cmpb $'F', (%ecx)
    jne greska_kraj
    addl $2, %ecx
    leal pomocni, %edx

petlja_masti:
    movb (%ecx), %bl
    movb %bl, (%edx) 
    incl %ecx
    incl %edx
    cmpb $',', (%ecx)
    je konvertuj_int_F
    cmpb $10,(%ecx)
    je konvertuj_int_F
    jmp petlja_masti

konvertuj_int_F:
    movb $0, (%edx)
    leal pomocni, %edx

    pushl %edx
    call stringToInt
    addl $4, %esp
    
    addl %eax, mast
    jmp glavnaPetlja

konvertuj_u_str:
    # konvertujemo proteine u string
    movl proteini, %eax
    leal str_proteini, %edi

    pushl %edi
    pushl %eax
    call intToString
    addl $8, %esp 

    movl %eax, duzina_proteina

    # konvertujemo hidrate u string
    movl hidrati, %eax
    leal str_hidrati, %edi

    pushl %edi
    pushl %eax
    call intToString
    addl $8, %esp 

    movl %eax, duzina_hidrata

    # konvertujemo masti u string
    movl mast, %eax
    leal str_masti, %edi
    
    pushl %edi
    pushl %eax
    call intToString
    addl $8, %esp

    movl %eax, duzina_masti

    # racunamo kalorije
    movl proteini, %eax
    movl $4, %ebx
    mull %ebx
    movl %eax, %esi

    movl hidrati, %eax
    movl $4, %ebx
    mull %ebx
    addl %eax, %esi

    movl mast, %eax
    movl $9, %ebx
    mull %ebx
    addl %eax, %esi

    # konverzija kalorija u string
    movl %esi, %eax
    leal str_kalorije, %edi

    pushl %edi
    pushl %eax
    call intToString
    addl $8, %esp

    movl %eax, duzina_kalorija
    
    jmp kraj


greska_kraj:
    movl $4, %eax
    movl $1, %ebx
    leal greska, %ecx
    movl $greskalen, %edx
    int $0x80

    movl $1, %eax
    movl $1, %ebx
    int $0x80

kraj:
    movl $4, %eax
    movl $1, %ebx
    leal kal, %ecx
    movl $kallen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal str_kalorije, %ecx
    movl duzina_kalorija, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal novired, %ecx
    movl $noviredlen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal protein, %ecx
    movl $proteinlen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal str_proteini, %ecx
    movl duzina_proteina, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal slovog, %ecx
    movl $slovoglen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal uglj, %ecx
    movl $ugljlen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal str_hidrati, %ecx
    movl duzina_hidrata, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal slovog, %ecx
    movl $slovoglen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal masti, %ecx
    movl $mastilen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal str_masti, %ecx
    movl duzina_masti, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal slovog, %ecx
    movl $slovoglen, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80