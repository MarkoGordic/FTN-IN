.section .text

# int parse_hex_str_int(char* broj)
# parse_hex_str_int("1F5\0")
.globl parse_hex_str_int
parse_hex_str_int:
    pushl %ebp
    movl %esp, %ebp
    pushl %ecx
    pushl %edx
    pushl %ebx
    pushl %esi

    movl 8(%ebp), %ecx  # string
    movl $16, %esi      # baza
    xorl %eax, %eax     # postavljamo eax na 0
    xorl %ebx, %ebx     # postavljamo ebx na 0

petlja:
    cmpb $0, (%ecx)
    je kraj
    cmpb $'9', (%ecx)
    jg proveraSlovo
    jl cifra
    
velikoSlovo:
    subb $'A', (%ecx)
    addb $10, (%ecx)
    jmp hex_cifra

proveraSlovo:
    cmpb  $'a', (%ecx)
    jl velikoSlovo
    subb $'a', (%ecx)
    addb $10, (%ecx)
    
cifra:
    movb (%ecx), %bl
    subb $'0', %bl
    mull %esi
    addl %ebx, %eax
    incl %ecx
    jmp petlja

hex_cifra:
    movb (%ecx), %bl
    mull %esi
    addl %ebx, %eax
    incl %ecx
    jmp petlja
    
kraj:
    popl %esi
    popl %ebx
    popl %edx
    popl %ecx
    movl %ebp, %esp
    popl %ebp
    ret