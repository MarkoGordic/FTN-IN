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

%{

#define YYDEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <libgen.h> //basename
#include <unistd.h> //isatty
#include "defs.h"
#include "simulator.h"

int yyparse(void);
int yylex(void);
int yyerror(char *s);
void warning(char *s);

extern int yylineno;
extern int code_cnt;
extern int source_cnt;
extern int max_steps;
extern Processor processor;
char char_buffer[CHAR_BUFFER_LENGTH];
int error_count = 0;
extern Symtab symtab[SYMTAB_LEN];      //tabela simbola (labela)
int mainarg = 0;

%}

%union {
    long i;
    char* s;
}

%token _WORD

%token _PUSH
%token _POP
%token _CALL
%token _RET

%token <i> _CMP

%token _JMP
%token _JEQ
%token _JNE
%token <i> _JGT
%token <i> _JLT
%token <i> _JGE
%token <i> _JLE
%token _JC
%token _JNC
%token _JO
%token _JNO

%token <i> _ADD
%token <i> _SUB
%token <i> _MUL
%token <i> _DIV
%token _MOV
%token _HALT

%token <i> _REGISTER
%token <i> _CONSTANT
%token <i> _NUMBER
%token <s> _LABEL_DEF
%token <s> _LABEL
%token <s> _ADDRESS

%token _COMMA
%token _LPAREN
%token _RPAREN

%type <s> input output label

%%

program
    :   variable_list code_list
        {
            add_entry_code(mainarg);
        }
    ;

variable_list
    :   /* empty */
    |   variable_list variable
    ;

variable
    :   _LABEL_DEF
        { $<i>$ = yylineno; }
        _WORD _NUMBER
        {
            uchar data[256];
            int i,len = $4*4;
            for (i=0; i<len; i++) data[i] = 0;
            insert_source("%s:\t\t\tWORD %ld",$1,$4);
            insert_data(data,len, $1, $<i>2);
        }
    ;

code_list
    :   code_line
    |   code_list code_line
    ;

code_line
    :   label_def
    |   asm_line
    ;

label_def
    :   _LABEL_DEF
        {
            insert_source("%s:",$1);
            insert_label($1, code_cnt, yylineno, SYM_JUMP);
            source_cnt++;
        }
    ;

asm_line
    :   arithmetic
    |   flowcontrol
    |   stack
    |   _HALT
        {
            insert_source("\t\t\tHALT");
            insert_code(INS_HALT, NO_TYPE, yylineno);
        }
    ;

arithmetic
    :   _ADD input _COMMA input _COMMA output
        {
            insert_source("\t\t\tADD%c %s, %s, %s", type_char($1), $2, $4, $6);
            insert_code(INS_ADD, $1, yylineno);
            free($2); free($4); free($6);
        }
    |   _SUB input _COMMA input _COMMA output
        {
            insert_source("\t\t\tSUB%c %s, %s, %s", type_char($1), $2, $4, $6);
            insert_code(INS_SUB, $1, yylineno);
            free($2); free($4); free($6);
        }
    |   _MUL input _COMMA input _COMMA output
        {
            insert_source("\t\t\tMUL%c %s, %s, %s", type_char($1), $2, $4, $6);
            insert_code(INS_MUL, $1, yylineno);
            free($2); free($4); free($6);
        }
    |   _DIV input _COMMA input _COMMA output
        {
            insert_source("\t\t\tDIV%c %s, %s, %s", type_char($1), $2, $4, $6);
            insert_code(INS_DIV, $1, yylineno);
            free($2); free($4); free($6);
        }
    |   _MOV input _COMMA output
        {
            insert_source("\t\t\tMOV %s, %s", $2, $4);
            insert_code(INS_MOV, NO_TYPE, yylineno);
            free($2); free($4);
        }
    ;

flowcontrol
    :   _CMP input _COMMA input
        {
            insert_source("\t\t\tCMP%c %s, %s", type_char($1), $2, $4);
            insert_code(INS_CMP, $1, yylineno);
            free($2); free($4);
        }
    |   _JMP label
        {
            insert_source("\t\t\tJMP %s", $2);
            insert_code(INS_JMP, NO_TYPE, yylineno);
        }
    |   _JEQ label
        {
            insert_source("\t\t\tJEQ %s", $2);
            insert_code(INS_JEQ, NO_TYPE, yylineno);
        }
    |   _JNE label
        {
            insert_source("\t\t\tJNE %s", $2);
            insert_code(INS_JNE, NO_TYPE, yylineno);
        }
    |   _JGT label
        {
            insert_source("\t\t\tJGT%c %s", type_char($1), $2);
            insert_code(INS_JGT, $1, yylineno);
        }
    |   _JLT label
        {
            insert_source("\t\t\tJLT%c %s", type_char($1), $2);
            insert_code(INS_JLT, $1, yylineno);
        }
    |   _JGE label
        {
            insert_source("\t\t\tJGE%c %s", type_char($1), $2);
            insert_code(INS_JGE, $1, yylineno);
        }
    |   _JLE label
        {
            insert_source("\t\t\tJLE%c %s", type_char($1), $2);
            insert_code(INS_JLE, $1, yylineno);
        }
    |   _JC label
        {
            insert_source("\t\t\tJC %s", $2);
            insert_code(INS_JC, NO_TYPE, yylineno);
        }
    |   _JNC label
        {
            insert_source("\t\t\tJNC %s", $2);
            insert_code(INS_JNC, NO_TYPE, yylineno);
        }
    |   _JO label
        {
            insert_source("\t\t\tJO %s", $2);
            insert_code(INS_JO, NO_TYPE, yylineno);
        }
    |   _JNO label
        {
            insert_source("\t\t\tJNO %s", $2);
            insert_code(INS_JNO, NO_TYPE, yylineno);
        }
    ;

stack
    :   _PUSH input
        {
            insert_source("\t\t\tPUSH %s", $2);
            insert_code(INS_PUSH, NO_TYPE, yylineno);
            free($2);
        }
    |   _POP output
        {
            insert_source("\t\t\tPOP %s", $2);
            insert_code(INS_POP, NO_TYPE, yylineno);
            free($2);
        }
    |   _CALL label
        {
            insert_source("\t\t\tCALL %s", $2);
            insert_code(INS_CALL, NO_TYPE, yylineno);
        }
    |   _RET
        {
            insert_source("\t\t\tRET");
            insert_code(INS_RET, NO_TYPE, yylineno);
        }
    ;

label
    :   _LABEL
        {
            int l;
            $$ = make_opstr("%s",$1);
            l = use_label($1, yylineno);
            add_operand(OP_DATA,0,l);
        }
    ;

output
    :   _REGISTER
        {
            add_operand(OP_REGISTER,$1,0);
            $$ = make_opstr("%%%ld",$1);
        }
    |   _NUMBER _LPAREN _REGISTER _RPAREN
        {
            add_operand(OP_INDEX,$3,$1);
            $$ = make_opstr("%ld(%%%ld)",$1,$3);
        }
    |   _LPAREN _REGISTER _RPAREN
        {
            add_operand(OP_INDIRECT,$2,0);
            $$ = make_opstr("(%%%ld)",$2);
        }
    |   label
    ;

input
    :   _CONSTANT
        {
            add_operand(OP_CONSTANT,0,$1);
            $$ = make_opstr("$%ld",$1);
        }
    |   _ADDRESS
        {
            int l;
            $$ = make_opstr("$%s",$1);
            l = use_label($1, yylineno);
            /* if (symtab[l].usage == LAB_UNDEFINED)
                parsererror("Undeclared global variable %s",$1); */
            add_operand(OP_CONSTANT,0,symtab[l].address);
        }
    |   output
    ;

%%

int yyerror(char *s) {
    fprintf(stderr, "\nSimulator: ASM parsing error in line %d: %s\n", yylineno, s);
    error_count++;
    return 0;
}

int main(int argc, char *argv[]) {
    int i;
    char c;
    char run_complete = FALSE;
    char syntax_check = FALSE;
    char *print_variable = 0;
    //yydebug = 1;  //debagovanje parsera

    //parsiranje opcija programa
    opterr=0;
    while (1) {
        c = getopt(argc, argv, ":hcra:p:s:");
        if (c == -1) break;
        switch(c) {
            case 'h' : {
                    cprintf("\n{BLU}Hypothetic processor simulator{NRM} v%s",VERSION);
                    cprintf("\n\nUsage: {BLU}%s{NRM} [options] {BLU}< asm_file{NRM}", basename(strdup(argv[0])));
                    cprintf("\nIf started without options, simulator will run asm code");
                    cprintf("\nstep by step. Possible options are:");
                    cprintf("\n{GRN}-h{NRM}     - this help");
                    cprintf("\n{GRN}-c{NRM}     - syntax check of asm code, without execution");
                    cprintf("\n{GRN}-r{NRM}     - complete run of the program, only exit code (%%%d) output",FUNCTION_REGISTER);
                    cprintf("\n{GRN}-p VAR{NRM} - complete run of the program, only global var output");
                    cprintf("\n{GRN}-a VAR{NRM} - value of argument passed to main function (default: 0)");
                    cprintf("\n{GRN}-s NUM{NRM} - maximal number of execution steps for complete run");
                    cprintf("\n         (simulator will return code %d if this number is reached)\n\n",STEP_ERROR);
                    exit(0);
                    break; }
            case 'c' : {
                    syntax_check = TRUE;
                    break; }
            case 'r' : {
                    run_complete = TRUE;
                    break; }
            case 'a' : {
                    mainarg = atoi(optarg);
                    break; }
            case 'p' : {
                    run_complete = TRUE;
                    print_variable = optarg;
                    break; }
            case 's' : {
                    max_steps = atoi(optarg);
                    break; }
            case '?' : {
                    argerror("Unknown option %c",optopt);
                    break; }
            case ':' : {
                    argerror("Argument missing for option %c",optopt);
                    break; }
            default : {
                    argerror("Unknown getopt return code 0x%X",c);
                    break; }
        }
    }

    //proveri da li postoji ulazni fajl
    if (isatty(fileno(stdin))) {
        argerror("No input file was specified.");
    }

    //parsiranje asemblerskog koda
    init_simulator();
    if ( ! yyparse() ) {
        check_labels();
        if (print_variable && !check_global(print_variable)) {
            argerror("Undeclared global variable %s",print_variable);
        }
    }

    //preusmeravanje terminala na stdin
    freopen("/dev/tty", "rw", stdin);

    if (error_count) {
        if (!run_complete)
            cprintf("\n{RED}There were error(s) in ASM source.{NRM}", error_count);
        printf("\n");
        exit(PARSE_ERROR);
    } else if (syntax_check)
            cprintf("{GRN}OK{NRM}");
    else {
        if (run_complete) {
            run();
            if (max_steps != 0) {
                if (print_variable)
                    printf("%d",get_global(print_variable));
                else
                    printf("%d",processor.reg[FUNCTION_REGISTER]);
            } else
                cprintf("\n{RED}Program terminated.{NRM}");
        } else {
            while (!processor.halt) {
                system("clear");
                print_source(PRINT_SRCLINES);
                print_global();
                print_registers();
                print_stack(PRINT_STKLINES);
                printf("\nPress any key to continue, ctrl+c for exit...");
                getch();
                run_once();
            }
            system("clear");
            print_source(PRINT_SRCLINES);
            print_global();
            print_registers();
            print_stack(PRINT_STKLINES);
            cprintf("\n\n{BLU}Program exit code (%%%d): {GRN}%d{NRM}\n",
                    FUNCTION_REGISTER, processor.reg[FUNCTION_REGISTER]);
            printf("\nAll OK.\n");
        }
    }
    printf("\n");
    if (error_count)
        return PARSE_ERROR;
    else if (max_steps != 0)
        return NO_ERROR;
    else
        //izvršeno max_steps koraka, a program se nije završio
        return STEP_ERROR;
}

