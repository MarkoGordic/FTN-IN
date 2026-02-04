#ifndef DEFS_H
#define DEFS_H

#define bool int
#define TRUE  1
#define FALSE 0

#define SYMBOL_TABLE_LENGTH   64
#define NO_INDEX              -1
#define NO_ATR                 0
#define LAST_WORKING_REG      12
#define FUN_REG               13
#define CHAR_BUFFER_LENGTH   128
extern char char_buffer[CHAR_BUFFER_LENGTH];

extern int out_lin;
//pomocni makroi za ispis
extern void warning(char *s);
extern int yyerror(char *s);
#define err(args...)  sprintf(char_buffer, args), yyerror(char_buffer)
#define warn(args...) sprintf(char_buffer, args), warning(char_buffer)
#define code(args...) ({fprintf(output, args); \
          if (++out_lin > 2000) err("Too many output lines"), exit(1); })

//tipovi podataka
enum types { NO_TYPE, INT, UINT };

//vrste simbola (moze ih biti maksimalno 32)
enum kinds { NO_KIND = 0x1, REG = 0x2, LIT = 0x4, 
             FUN = 0x8, VAR = 0x10, PAR = 0x20 };

//konstante arithmetickih operatora
enum arops { ADD, SUB, MUL, DIV, AROP_NUMBER };
//stringovi za generisanje aritmetickih naredbi
static char *ar_instructions[] = { "ADDS", "SUBS", "MULS", "DIVS",
                                   "ADDU", "SUBU", "MULU", "DIVU" };

//konstante relacionih operatora
enum relops { LT, GT, LE, GE, EQ, NE, RELOP_NUMBER };
//stringovi za JMP narebu
static char* jumps[]={"JLTS", "JGTS", "JLES", "JGES", "JEQ ", "JNE ",
                      "JLTU", "JGTU", "JLEU", "JGEU", "JEQ ", "JNE " };

static char* opp_jumps[]={"JGES", "JLES", "JGTS", "JLTS", "JNE ", "JEQ ",
                          "JGEU", "JLEU", "JGTU", "JLTU", "JNE ", "JEQ "};
#endif
