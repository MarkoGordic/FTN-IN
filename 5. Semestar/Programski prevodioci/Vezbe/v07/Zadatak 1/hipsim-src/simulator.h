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

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "defs.h"

#define REG_NUMBER      16
#define MEM_SIZE        1024
#define SOURCE_LINES    256
#define SYMTAB_LEN      256

typedef unsigned char Datamem;

//labela može biti u jednom od tri stanja korištenosti:
//  LAB_DEFINED - definisana i nekorištena
//  LAB_UNDEFINED - nedefinisana i korištena
//  LAB_USED - definisana i korištena
enum { LAB_DEFINED, LAB_UNDEFINED, LAB_USED };

//vrsta labele
enum { SYM_DATA, SYM_JUMP };

//jedna linija source koda za prikazivanje
typedef struct _Source {
    char* text;     //tekst linije koda
    int address;    //adresa linije u segmentu koda
} Source;

//operand naredbe
typedef struct _Operand {
    uchar kind;     //vrtsa operanda
    uchar reg;      //(dodatni) registar za operand
    word data;      //sadržaj operanda
} Operand;

//naredba
typedef struct _Instruction {
    uchar inst;             //naredba
    uchar type;             //tip (signed/unsigned)
    Operand op[3];          //operandi
    uchar breakpoint;       //TRUE ako je tačka prekida
    int line;               //broj linije u source fajlu
    int lineint;            //broj linije u internom source-u za prikazivanje
} Instruction;

//registri i indikatori procesora
typedef struct _Processor {
    word reg[REG_NUMBER];           //registri
    word pc;                        //program counter
    uchar zero,sign,carry,overflow; //indikatori
    uchar step;                     //TRUE ako je procesor u step režimu rada
    uchar halt;                     //TRUE ako je procesor zaustavljen (HALT naredba)
} Processor;

//tabela simbola
typedef struct _Symtab {
    char* name;     //naziv labele
    int address;    //adresa labele
    int line;       //linija u source kodu gde je labela definisana
    uchar type;     //tip promenljive (signed/unsigned)
    uchar usage;    //korištenost labele
} Symtab;

//pomoćne funkcije
int getch(void);
int string_replace(char** String, char* ReplaceWhat, char* ReplaceTo);
int cprintf(const char *format, ...);

//funkcije parsera za popunjavanje tabela simulatora
void add_entry_code(word arg);
int label_index(char* name);
int use_label(char* name, int line);
int insert_label(char* name, int address, int line, uchar type);
void insert_data(Datamem *data, uchar datalen, char *name, int line);
void add_operand(uchar kind, uchar reg, int data);
void insert_code(uchar inst, uchar type, int line);
void insert_source_f(char *s);
int check_global(char *name);
void check_labels();

//funkcije simulatora
void init_simulator();
word* getmem(word address);
char type_char(uchar type);
word get_operand(Operand op);
void set_operand(Operand op, word data);
void set_flags_signed(quad result);
void set_flags_unsigned(uquad result);
void run_once();
void run();
void print_registers();
void print_stack(int lines);
void print_global();
void print_source(int lines);
int get_global(char *name);

//pomoćni makroi za parser
extern char source_buffer[];
//makro za ubacivanje linije koda u source za ispis
#define insert_source(args...) sprintf(source_buffer, args), insert_source_f(source_buffer)
//makro za generisanje teksta operanda za source za ispis
#define make_opstr(args...) (sprintf(source_buffer, args), strdup(source_buffer))

#endif

