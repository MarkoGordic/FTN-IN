.section .data

poruka1: .ascii "Unesite pesme: "
poruka1len= . - poruka1
greska: .ascii "Doslo je do greske tokom rada programa!\n"
greskalen= . - greska
unos: .fill 200,1,42
kraj1: .ascii "Ukupna duzina svih pesama u sekundama je : "
kraj1len= . - kraj1
kraj2: .ascii " sekundi.\n"
kraj2len= . - kraj2

suma: .long 0

minuti_ulaz: .fill 3,1,42
sekunde_ulaz: .fill 3,1,42
sumastring: .fill 10,1,42

minutiBroj: .long 0
sekundeBroj: .long 0
duzinaSume: .long 0

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
    
proveraIme:
    cmpb $10, (%ecx)
    je konvertIntStr
    cmpb $' ', (%ecx)
    je pripremaUlaz
    cmpb $'&', (%ecx)
    je dalje
    cmpb $'!', (%ecx)
    je dalje
    cmpb $'.', (%ecx)
    je dalje
    cmpb $'?', (%ecx)
    je dalje
    cmpb $'_', (%ecx)
    je dalje
    cmpb $'A', (%ecx)
    jl krajGreska
    cmpb $'Z', (%ecx)
    jle dalje
    cmpb $'a', (%ecx)
    jl krajGreska
    cmpb $'z', (%ecx)
    jle dalje
    jg krajGreska

dalje:
    incl %ecx
    jmp proveraIme

pripremaUlaz:
    addl $1, %ecx
    cmpb $'-', (%ecx)
    jne krajGreska
    addl $2, %ecx
    leal minuti_ulaz, %ebx
    
obradaUlazMinuti:
    cmpb $':' , (%ecx)
    je konvertStrIntM
    cmpb $'0', (%ecx)
    jl krajGreska
    cmpb $'9', (%ecx)
    jg krajGreska
    movb (%ecx), %al 
    movb %al, (%ebx)
    incl %ebx
    incl %ecx
    jmp obradaUlazMinuti

konvertStrIntM:
    movb $0, (%ebx)
    leal minuti_ulaz, %ebx

    pushl %ebx
    call StrInt 
    addl $4, %esp
   
    movl $60, %esi
    mull %esi

    addl %eax, suma
    

    leal sekunde_ulaz, %edx
    incl %ecx

obradaUlazSekunde:
    cmpb $10, (%ecx)
    je konvertStrIntS
    cmpb $'|', (%ecx)
    je konvertStrIntS
    cmpb $'0', (%ecx)
    jl krajGreska
    cmpb $'9', (%ecx)
    jg krajGreska
    movb (%ecx), %al
    movb %al, (%edx)
    incl %ecx
    incl %edx
    jmp obradaUlazSekunde

konvertStrIntS:
    movb $0, (%edx)
    leal sekunde_ulaz, %edx

    pushl %edx
    call StrInt 
    addl $4, %esp

    addl %eax, suma
    

    cmpb $10, (%ecx)
    je konvertIntStr
    incl %ecx
    jmp proveraIme

konvertIntStr:
    movl suma, %edi
    leal sumastring, %eax

    pushl %edi
    pushl %eax
    call IntStr 
    addl $4, %esp

    movl %eax, duzinaSume

kraj:
    movl $4, %eax
    movl $1, %ebx
    leal kraj1, %ecx
    movl $kraj1len, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal sumastring, %ecx
    movl duzinaSume, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal kraj2, %ecx
    movl $kraj2len, %edx
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