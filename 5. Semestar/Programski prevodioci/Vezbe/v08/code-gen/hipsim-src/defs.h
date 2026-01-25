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

#ifndef DEFS_H
#define DEFS_H

#define VERSION "1.2"

#include <stdint.h>

#define TRUE  1
#define FALSE 0

//8, 32 i 64-bitni tipovi podataka
typedef unsigned char uchar;
typedef int32_t word;
typedef uint32_t uword;
typedef int64_t quad;
typedef uint64_t uquad;

//tipovi naredbi
enum { NO_TYPE = 0, SIGNED_TYPE, UNSIGNED_TYPE };

//vrste operanada
enum { OP_REGISTER = 1, OP_INDIRECT, OP_INDEX, OP_CONSTANT, OP_ADDRESS, OP_DATA } OperandType;

//instrukcije
enum { INS_CALL = 1, INS_RET, INS_PUSH, INS_POP, INS_CMP, INS_JMP, INS_JEQ, INS_JNE,
        INS_JGT, INS_JLT, INS_JGE, INS_JLE, INS_JC, INS_JNC, INS_JO, INS_JNO,
        INS_ADD, INS_SUB, INS_MUL, INS_DIV, INS_MOV, INS_HALT };

#define FUNCTION_REGISTER        13
#define FRAME_POINTER            14
#define STACK_POINTER            15
#define PRINT_SRCLINES           10
#define PRINT_STKLINES           10

//dužina pomoćnog bafera za ispis
#define CHAR_BUFFER_LENGTH       256

extern char char_buffer[CHAR_BUFFER_LENGTH];
extern int yyerror(char *s);
extern void warning(char *s);

//kodovi grešaka
enum { NO_ERROR = 0, PARSE_ERROR, ARG_ERROR, SIM_ERROR, STEP_ERROR };

//pomoćni makroi za ispis
#define parsererror(args...) sprintf(char_buffer, args), yyerror(char_buffer)
#define argerror(args...) cprintf("\n{RED}Argument error:{NRM} "), cprintf(args), printf("\n"), exit(ARG_ERROR)
#define simerror(args...) cprintf("\n{RED}Simulation error:{NRM} "), cprintf(args), printf("\n"), exit(SIM_ERROR)

#endif

