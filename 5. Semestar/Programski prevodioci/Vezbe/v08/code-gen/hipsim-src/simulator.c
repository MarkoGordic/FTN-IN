/*
    This file is part of HipSim.
    HipSim (c) 2013,2019 Žarko Živanov

    HipSim is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "simulator.h"
#include "defs.h"

extern int yylineno;


/*******************************************************
                promenljive simulatora
*******************************************************/


Datamem datamem[MEM_SIZE];      //memorija za podatke i stek
Operand operand[3];             //niz za definisanje operanada
Instruction codemem[MEM_SIZE];  //memorija za naredbe (1 naredba = 1 lokacija)
Processor processor;            //opis procesora
Symtab symtab[SYMTAB_LEN];      //tabela simbola (labela)
char source_buffer[256];        //pomoćni string za generisanje source ispisa'
Source source[256];             //source kod za prikaz

int data_cnt, code_cnt;     //brojači za data/code segment
int operand_cnt;            //brojač operanada naredbi
int source_cnt;             //brojač linija source asm programa
int symtab_cnt;             //brojač za tabelu simbola
uchar first_inst = TRUE;    //da li je prva naredba u programu
int max_steps = -1;         //maksimalan broj koraka koji će se izvršiti kod kompletnog izvršavanja


/*******************************************************
                    pomoćne funkcije
*******************************************************/


/* reads from keypress, doesn't echo
   AUTHOR: Zobayer Hasan, http://zobayer.blogspot.com/2010/12/getch-getche-in-gccg.html */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

//zamenjuje jedan podstring drugim
int string_replace(char** String, char* ReplaceWhat, char* ReplaceTo) {
    char *NewString, *c, *lastf;
    char *found = *String;
    int count = 0;
    int RepToLen = strlen(ReplaceTo);
    int RepWhatLen = strlen(ReplaceWhat);

    while (found) {
        if ((found = strstr(found, ReplaceWhat)) != 0) {
            found++;
            count++;
        }
    }
    if (count) {
        c = NewString = malloc(strlen(*String) + count*(RepToLen - RepWhatLen) + 1);
        lastf = *String;
        while ((found = strstr(lastf, ReplaceWhat)) != 0) {
            if (found != lastf) {
                strncpy(c, lastf, found-lastf);
                c += found-lastf;
            }
            strncpy(c, ReplaceTo, RepToLen);
            c += RepToLen;
            lastf = found+RepWhatLen;
        }
        strcpy(c, lastf);
        free(*String);
        *String = NewString;
    }
    return count;
}

//funkcija koja radi isto što i printf, samo što pre ispisa
//konvertuje konstante za boje u odgovarajuće escape sekvence
int cprintf(const char *format, ...) {
    size_t size;
    size_t sizem=1024;
    va_list ap,apc;
    char* buff;
    int ret;

    va_start(ap,format);
    do {
        buff = (char*)malloc(sizem);
        va_copy(apc, ap);
        size = vsnprintf(buff, sizem, format, apc);
        va_end(apc);
        if (size<sizem) break;
        else {
            free(buff);
            sizem = size+1;
        }
     } while (1);
    va_end(ap);

    string_replace(&buff,"{BLU}", "\033[1;34m");
    string_replace(&buff,"{GRN}", "\033[1;32m");
    string_replace(&buff,"{CYN}", "\033[1;36m");
    string_replace(&buff,"{RED}", "\033[1;31m");
    string_replace(&buff,"[BLU]", "\033[1;44m");
    string_replace(&buff,"[GRN]", "\033[1;42m");
    string_replace(&buff,"[CYN]", "\033[1;46m");
    string_replace(&buff,"[RED]", "\033[1;41m");
    string_replace(&buff,"{NRM}", "\033[0m");
    string_replace(&buff,"[NRM]", "\033[0m");

    ret=printf("%s",buff);
    free(buff);
    return ret;
}


/*******************************************************
   funkcije parsera za popunjavanje tabela simulatora
*******************************************************/


/* ubacivanje ulazne tačke programa nakon svih naredbi iz source fajla u obliku
        HALT
        PUSH arg
        CALL main   #ulazna tačka
        HALT    //ne radi se POP, jer je na kraju svakako HALT */
void add_entry_code(word arg) {
    char *mainlab = strdup("main");
    int l;
    insert_source("\t\t\tHALT");
    insert_code(INS_HALT, NO_TYPE, yylineno);

    //postavljanje program counter-a na PUSH naredbu
    processor.pc = code_cnt; 
    insert_source("\t\t\tPUSH $%d", arg);
    add_operand(OP_CONSTANT,0,arg);
    insert_code(INS_PUSH, NO_TYPE, yylineno);

    insert_source("\t\t\tCALL %s", mainlab);
    l = use_label(mainlab, yylineno);
    add_operand(OP_DATA,0,l);
    insert_code(INS_CALL, NO_TYPE, yylineno);

    insert_source("\t\t\tHALT");
    insert_code(INS_HALT, NO_TYPE, yylineno);
}

//vraća indeks labele u tabeli simbola ili -1 ako nije nađena
int label_index(char* name) {
    int i;
    for (i=0; i< symtab_cnt; i++) {
        if (strcmp(name, symtab[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

//korišćenje labele (može biti i pre nego je definisana)
//nakon poziva funkcije ne treba zvati free za naziv labele
int use_label(char* name, int line) {
    int i = -1;
    if ((i = label_index(name)) != -1) {
        if (symtab[i].usage == LAB_DEFINED)
            symtab[i].usage = LAB_USED;
        free(name);
    }
    else {
        symtab[symtab_cnt].name = name;
        symtab[symtab_cnt].line = line;
        symtab[symtab_cnt].usage = LAB_UNDEFINED;
        i = symtab_cnt++;
    }
    return i;
}

//definisanje labele
//nakon poziva funkcije ne treba zvati free za naziv labele
int insert_label(char* name, int address, int line, uchar type) {
    int i = -1;
    if ((i = label_index(name)) != -1) {
        if (symtab[i].usage != LAB_UNDEFINED)
            parsererror("Label already defined in line %d.",symtab[i].line);
        else {
            symtab[i].address = address;
            symtab[i].line = line;
            symtab[i].type = type;
            symtab[i].usage = LAB_USED;
        }
        free(name);
    }
    else {
        symtab[symtab_cnt].name = name;
        symtab[symtab_cnt].address = address;
        symtab[symtab_cnt].line = line;
        symtab[symtab_cnt].type = type;
        symtab[symtab_cnt].usage = LAB_DEFINED;
        i = symtab_cnt++;
    }
    return i;
}

//ubacivanje vrednosti u sekciju podataka (za WORD direktive)
void insert_data(Datamem *data, uchar datalen, char *name, int line) {
    int i;
    insert_label(name, data_cnt, line, SYM_DATA);
    for (i=0; i<datalen; i++) {
        datamem[data_cnt++] = data[i];
    }
}

//dodaje operand u niz operanada
void add_operand(uchar kind, uchar reg, int data) {
    if (operand_cnt >= 3) {
        parsererror("\nadd_operand fatal error");
    } else {
        operand[operand_cnt].kind = kind;
        operand[operand_cnt].reg = reg;
        operand[operand_cnt].data = data;
        operand_cnt++;
    }
}

//ubacuje naredbu u segment koda
void insert_code(uchar inst, uchar type, int line) {
    int i;
    codemem[code_cnt].inst = inst;
    codemem[code_cnt].type = type;
    codemem[code_cnt].breakpoint = FALSE;
    codemem[code_cnt].line = line;
    codemem[code_cnt].lineint = source_cnt;
    for (i=0; i<operand_cnt; i++) {
        codemem[code_cnt].op[i].kind = operand[i].kind;
        codemem[code_cnt].op[i].reg = operand[i].reg;
        codemem[code_cnt].op[i].data = operand[i].data;
    }
    code_cnt++;
    source_cnt++;
    operand_cnt = 0;
}

//funkcija za ubacivanje linije koda u source za prikaz
void insert_source_f(char *s) {
    source[source_cnt].text = strdup(s);
    source[source_cnt].address = code_cnt;
}


//provera da li globalna promenljiva postoji
int check_global(char *name) {
    int i;
    for (i = 0; i < symtab_cnt ; i++)
        if (symtab[i].type == SYM_DATA && (strcmp(name,symtab[i].name) == 0))
            return TRUE;
    return FALSE;
}

//provera definisanosti labela
void check_labels() {
    int i;
    for (i=0; i<symtab_cnt; i++)
        if (symtab[i].usage == LAB_UNDEFINED)
            parsererror("Label %s used in line %d isn't defined",symtab[i].name, symtab[i].line);
}

/*******************************************************
                  funkcije simulatora
*******************************************************/


//inicijalizacija promenljivih, procesora i memorije
void init_simulator() {
    int i;
    processor.pc = 0;
    processor.reg[STACK_POINTER] = MEM_SIZE;
    processor.pc = 0;
    processor.step = FALSE;
    data_cnt = 0;
    code_cnt = 0;
    symtab_cnt = 0;
    source_cnt = 0;
    operand_cnt = 0;
    for (i = 0; i < MEM_SIZE; i++) {
        datamem[i] = 0xa5;
        codemem[i].inst = INS_HALT;
    }
}

//vraća pokazivač na word za zadatu adresu i proverava ispravnost adrese
word* getmem(word address) {
    if ((address<0)||(address>=MEM_SIZE))
        simerror("Address out of memory range [0,%d]",MEM_SIZE-1);
    return (word*)&datamem[address];
}

//vraća znak koji odgovara tipu (signed/unsigned) naredbe
char type_char(uchar type) {
    if (type == SIGNED_TYPE)
        return 'S';
    else if (type == UNSIGNED_TYPE)
        return 'U';
}

//vraća vrednost operanda
word get_operand(Operand op) {
    switch (op.kind) {
        case OP_REGISTER:
            return processor.reg[op.reg];
        case OP_INDIRECT:
            return *getmem(processor.reg[op.reg]);
        case OP_INDEX:
            return *getmem(processor.reg[op.reg]+op.data);
        case OP_CONSTANT:
            return op.data;
        case OP_ADDRESS:
            return op.data;
        case OP_DATA:
            return *getmem(symtab[op.data].address);
        default: {
            simerror("get_operand fatal error"); // ne bi trebalo da se desi
        }
    }
}

//postavlja vrednost operanda
void set_operand(Operand op, word data) {
    switch (op.kind) {
        case OP_REGISTER:
            processor.reg[op.reg] = data;
            break;
        case OP_INDIRECT:
            *getmem(processor.reg[op.reg]) = data;
            break;
        case OP_INDEX:
            *getmem(processor.reg[op.reg]+op.data) = data;
            break;
        case OP_ADDRESS:    //možda ne treba...
            op.data = data;
            break;
        case OP_DATA:
            *getmem(symtab[op.data].address) = data;
            break;
        default: {
            simerror("set_operand fatal error"); // ne bi trebalo da se desi
        }
    }
}

//postavi indikatore procesora za označeni rezultat
void set_flags_signed(quad result) {
    processor.zero = result == 0 ? 1 : 0;
    processor.sign = (result & 0x80000000) != 0 ? 1 : 0;
    processor.carry = 0;
    processor.overflow = (result > INT32_MAX) || (result < INT32_MIN) ? 1 : 0;
}

//postavi indikatore procesora za neoznačeni rezultat
void set_flags_unsigned(uquad result) {
    processor.zero = result == 0 ? 1 : 0;
    processor.sign = (result & 0x80000000) != 0 ? 1 : 0;
    processor.carry = (result > UINT32_MAX) ? 1 : 0;
    processor.overflow = 0;
}

//izvršava jednu naredbu hipotetskog procesora
void run_once() {
    Instruction *i = &codemem[processor.pc];
    word operand0, operand1;
    if (processor.halt) return;
    switch (i->inst) {
        case INS_PUSH:
            processor.reg[STACK_POINTER] -= 4;
            *getmem(processor.reg[STACK_POINTER]) = get_operand(i->op[0]);
            processor.pc++;
            break;
        case INS_POP:
            set_operand( i->op[0], *getmem(processor.reg[STACK_POINTER]) );
            processor.reg[STACK_POINTER] += 4;
            processor.pc++;
            break;
        case INS_CALL:
            processor.reg[STACK_POINTER] -= 4;
            *getmem(processor.reg[STACK_POINTER]) = processor.pc + 1;
            processor.pc = symtab[i->op[0].data].address;
            break;
        case INS_RET:
            processor.pc = *getmem(processor.reg[STACK_POINTER]);
            processor.reg[STACK_POINTER] += 4;
            break;
        case INS_CMP:
            if (i->type == SIGNED_TYPE)
                set_flags_signed((quad)get_operand(i->op[0]) - (quad)get_operand(i->op[1]));
            else
                set_flags_unsigned((uquad)(uword)get_operand(i->op[0]) - (uquad)(uword)get_operand(i->op[1]));
            processor.pc++;
            break;
        case INS_JMP:
            processor.pc = symtab[i->op[0].data].address;
            break;
        case INS_JEQ:
            if (processor.zero)
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JNE:
            if (!processor.zero)
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JGT:
            if ( (i->type == SIGNED_TYPE) && (( (~(processor.sign^processor.overflow)) & (~processor.zero) )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else if ( (i->type == UNSIGNED_TYPE) && (( (~processor.carry) & (~processor.zero) )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JLT:
            if ( (i->type == SIGNED_TYPE) && (( processor.sign^processor.overflow )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else if ( (i->type == UNSIGNED_TYPE) && (( processor.carry )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JGE:
            if ( (i->type == SIGNED_TYPE) && (( ~(processor.sign^processor.overflow) )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else if ( (i->type == UNSIGNED_TYPE) && (( ~processor.carry )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JLE:
            if ( (i->type == SIGNED_TYPE) && (( (processor.sign^processor.overflow) | processor.zero )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else if ( (i->type == UNSIGNED_TYPE) && (( processor.carry | processor.zero )&1) )
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JC:
            if (processor.carry)
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JNC:
            if (!processor.carry)
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JO:
            if (processor.overflow)
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_JNO:
            if (!processor.overflow)
                processor.pc = symtab[i->op[0].data].address;
            else
                processor.pc++;
            break;
        case INS_ADD:
            operand0 = get_operand(i->op[0]);
            operand1 = get_operand(i->op[1]);
            if (i->type == SIGNED_TYPE) {
                set_operand(i->op[2], operand0 + operand1);
                set_flags_signed((quad)operand0 + (quad)operand1);
            } else {
                set_operand(i->op[2], (word)((uword)operand0 + (uword)operand1));
                set_flags_unsigned((uquad)(uword)operand0 + (uquad)(uword)operand1);
            }
            processor.pc++;
            break;
        case INS_SUB:
            operand0 = get_operand(i->op[0]);
            operand1 = get_operand(i->op[1]);
            if (i->type == SIGNED_TYPE) {
                set_operand(i->op[2], operand0 - operand1);
                set_flags_signed((quad)operand0 - (quad)operand1);
            } else {
                set_operand(i->op[2], (word)((uword)operand0 - (uword)operand1));
                set_flags_unsigned((uquad)(uword)operand0 - (uquad)(uword)operand1);
            }
            processor.pc++;
            break;
        case INS_MUL:
            operand0 = get_operand(i->op[0]);
            operand1 = get_operand(i->op[1]);
            if (i->type == SIGNED_TYPE) {
                set_operand(i->op[2], operand0 * operand1);
                set_flags_signed((quad)operand0 * (quad)operand1);
            } else {
                set_operand(i->op[2], (word)((uword)operand0 * (uword)operand1));
                set_flags_unsigned((uquad)(uword)operand0 * (uquad)(uword)operand1);
            }
            processor.pc++;
            break;
        case INS_DIV:
            operand0 = get_operand(i->op[0]);
            operand1 = get_operand(i->op[1]);
            if (operand1 == 0) {
                simerror("Division by zero");
            }
            if (i->type == SIGNED_TYPE) {
                set_operand(i->op[2], operand0 / operand1);
                set_flags_signed((quad)operand0 / (quad)operand1);
            } else {
                set_operand(i->op[2], (word)((uword)operand0 / (uword)operand1));
                set_flags_unsigned((uquad)(uword)operand0 / (uquad)(uword)operand1);
            }
            processor.pc++;
            break;
        case INS_MOV:
            set_operand(i->op[1], get_operand(i->op[0]));
            processor.pc++;
            break;
        case INS_HALT:
            processor.halt = TRUE;
            break;
        default: {
            simerror("run_once fatal error"); // ne bi trebalo da se desi
        }
    }
}

//izvrši program od početka do kraja
void run() {
    do {
        run_once();
        if (max_steps > 0) max_steps--;
    } while (!processor.halt && !codemem[processor.pc].breakpoint && !processor.step && (max_steps !=0));
}

//ispis registara
void print_registers() {
    static word last[REG_NUMBER];
    int i;
    cprintf("\n\n{BLU}Registers{NRM}\n");
    printf("PC=%-5d  Flags[ZSCO]=[%d%d%d%d]", processor.pc, processor.zero,
           processor.sign, processor.carry, processor.overflow);
    if (processor.halt) cprintf("  {RED}HALTED{NRM}");
    for (i = 0; i < REG_NUMBER; i++) {
        if (i % 4 == 0) printf("\n");
        if (processor.reg[i] == last[i])
            printf("%%%-2d=%-5d ", i, processor.reg[i]);
        else
            cprintf("%%%-2d={RED}%-5d{NRM} ", i, processor.reg[i]);
        last[i] = processor.reg[i];
    }
}

//ispis sadržaja steka
void print_stack(int lines) {
    static Datamem lastst[MEM_SIZE];
    static int lastfirst = 0;
    int i,first,last;
    first = processor.reg[STACK_POINTER];
    last = first + (lines-1)*4;
    //printf("\nf:%d,l:%d, ln:%d\n",first,last,lines); //debug
    if (last >= MEM_SIZE-4) last = MEM_SIZE-4;
    cprintf("\n\n{BLU}Stack ([address]=value){NRM}");
    for (i = last; i >= first ; i-=4) {
        if ( (*(word*)&lastst[i] != *getmem(i)) || (i<lastfirst) )
            cprintf("\n[%4d]={RED}%-12d{NRM}", i, *getmem(i));
        else
            printf("\n[%4d]=%-12d", i,*getmem(i));
        if (processor.reg[FRAME_POINTER] >= processor.reg[STACK_POINTER])
            if (processor.reg[FRAME_POINTER] != i)
                printf(" <-FP%+d",i-processor.reg[FRAME_POINTER]);
            else
                cprintf(" <-{GRN}FP{NRM}");
        *(word*)&lastst[i] = *getmem(i);
    }
    lastfirst = first;
}

//ispis globalnih promenljivih
void print_global() {
    static word last[32];
    word val;
    int i,j=0;
    cprintf("\n\n{BLU}Global variables (name[address]=value){NRM}");
    for (i = 0; i < symtab_cnt ; i++) {
        if (symtab[i].type == SYM_DATA) {
            if (j++ % 4 == 0) printf("\n");
            val = *getmem(symtab[i].address);
            if (val == last[j])
                printf("%8s[%2d]=%-5d", symtab[i].name, symtab[i].address, val);
            else
                cprintf("%8s[%2d]={RED}%-5d{NRM}", symtab[i].name, symtab[i].address, val);
            last[j] = val;
        }
    }
}

//ispis source koda
void print_source(int lines) {
    int i, first, last;

    for (i = 0; i < source_cnt; i++)
        if (source[i].address == processor.pc) break;
    first = i - lines/2;
    last = i + lines/2 + lines%2;
    if (first < 0) { last = last - first; first = 0; }
    if (last > source_cnt) { first = first + source_cnt - last; last = source_cnt; }
    if (first < 0) { first = 0; }
    cprintf("{BLU}Line#  Addr    [> - PC, * - breakpoint]{NRM}");
    for (i = first; i < last ; i++) {
        char c;
        if (source[i].address == source[i+1].address) c = ' ';
        else if (source[i].address == processor.pc) c = '>';
        else if (codemem[source[i].address].breakpoint) c = '*';
        else c = ' ';
        cprintf("\n%3d {RED}%c{NRM} [%4d] %s%s{NRM}", i+1, c, source[i].address,
                c == '>' ? "[RED]" : "", source[i].text);
    }
}

//vraća vrednost globalne promenljive
int get_global(char *name) {
    int i;
    for (i = 0; i < symtab_cnt ; i++)
        if (symtab[i].type == SYM_DATA && (strcmp(name,symtab[i].name) == 0))
            return *getmem(symtab[i].address);
}

