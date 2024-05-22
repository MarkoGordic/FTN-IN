.section .data

poruka: .ascii "Unesite string: "
porukalen=. - poruka
ulaz: .fill 100,1,0  # Initialize with 0
izlaz1: .ascii "Stoja je uspesno potopila "
izlazlen=. - izlaz1
broj: .fill 1,1,0
izlaz2: .ascii " splav(a)!\n"
izlaz2len=. - izlaz2
pomocniP: .fill 5,1,0  # Initialize with 0
pomocniJ: .fill 5,1,0  # Initialize with 0
br_pesama: .long 0

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
    leal ulaz, %ecx
    movl $100, %edx
    int $0x80
  
    movl $0, %esi    # brojac
    leal ulaz, %ecx

glavnaPetlja:
    cmpb $10, (%ecx)
    je kraj
    
    cmpb $'P', (%ecx)
    je povecaj2
    
    cmpb $'J', (%ecx)
    je povecaj2j
    
    incl %ecx
    jmp glavnaPetlja

povecaj2:
    addl $2, %ecx
    leal pomocniP, %edx

slovoP:
    movb (%ecx), %bl
    movb %bl, (%edx) # pomeramo cifru u pomocniP
    incl %ecx
    incl %edx
    cmpb $' ', (%ecx)
    je konvertujuint
    jmp slovoP

povecaj2j:
    addl $2, %ecx
    leal pomocniJ, %edi

slovoJ:
    movb (%ecx), %bl
    movb %bl, (%edi)
    incl %ecx
    incl %edi
    cmpb $',', (%ecx)
    je konvertujuintJ
    cmpb $10, (%ecx)
    je konvertujuintJ
    jmp slovoJ

konvertujuint:
    movb $0, (%edx)
    leal pomocniP, %edx

    pushl %edx
    call parse_str_int
    addl $4, %esp
    
    movl %eax, br_pesama
    jmp glavnaPetlja

konvertujuintJ:
    movb $0, (%edi)
    leal pomocniJ, %edi

    pushl %edi
    call parse_str_int
    addl $4, %esp
    
    jmp mnozi

mnozi:
    movl br_pesama, %edi
    mull %edi
    cmpl $90, %eax
    jg brojac
    jmp glavnaPetlja

brojac:
    incl %esi
    jmp glavnaPetlja

kraj:
    addl $'0', %esi
    addl %esi, broj

    movl $4, %eax
    movl $1, %ebx
    leal izlaz1, %ecx
    movl $izlazlen, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal broj, %ecx
    movl $1, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    leal izlaz2, %ecx
    movl $izlaz2len, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80