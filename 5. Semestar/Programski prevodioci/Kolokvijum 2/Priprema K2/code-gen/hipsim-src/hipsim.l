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

%option yylineno
%option noyywrap

%{

#include <string.h>
#include "hipsim.tab.h"
#include "defs.h"

%}

letter [@_a-zA-Z]
digit  [0-9]
alpha  {letter}|{digit}

%%

[ \t\n]+ { /* skip */ }
"#".*    { /* skip */ }

WORD    { return _WORD; }

PUSH    { return _PUSH; }
POP     { return _POP; }
CALL    { return _CALL; }
RET     { return _RET; }

CMPS    { yylval.i = SIGNED_TYPE; return _CMP; }
CMPU    { yylval.i = UNSIGNED_TYPE; return _CMP; }

JMP     { return _JMP; }
JEQ     { return _JEQ; }
JNE     { return _JNE; }
JGTS    { yylval.i = SIGNED_TYPE; return _JGT; }
JGTU    { yylval.i = UNSIGNED_TYPE; return _JGT; }
JLTS    { yylval.i = SIGNED_TYPE; return _JLT; }
JLTU    { yylval.i = UNSIGNED_TYPE; return _JLT; }
JGES    { yylval.i = SIGNED_TYPE; return _JGE; }
JGEU    { yylval.i = UNSIGNED_TYPE; return _JGE; }
JLES    { yylval.i = SIGNED_TYPE; return _JLE; }
JLEU    { yylval.i = UNSIGNED_TYPE; return _JLE; }
JC      { return _JC; }
JNC     { return _JNC; }
JO      { return _JO; }
JNO     { return _JNO; }

ADDS    { yylval.i = SIGNED_TYPE; return _ADD; }
ADDU    { yylval.i = UNSIGNED_TYPE; return _ADD; }
SUBS    { yylval.i = SIGNED_TYPE; return _SUB; }
SUBU    { yylval.i = UNSIGNED_TYPE; return _SUB; }
MULS    { yylval.i = SIGNED_TYPE; return _MUL; }
MULU    { yylval.i = UNSIGNED_TYPE; return _MUL; }
DIVS    { yylval.i = SIGNED_TYPE; return _DIV; }
DIVU    { yylval.i = UNSIGNED_TYPE; return _DIV; }
MOV     { return _MOV; }
HALT    { return _HALT; }

"%"{digit}{1,2}  { yylval.i = atoi(yytext+1); return _REGISTER; }
"$"[+-]?{digit}+  { yylval.i = atol(yytext+1); return _CONSTANT; }
[+-]?{digit}+ { yylval.i = atol(yytext); return _NUMBER; }
{letter}{alpha}*":" { yylval.s = strdup(yytext); yylval.s[yyleng-1] = 0; return _LABEL_DEF; }
{letter}{alpha}*    { yylval.s = strdup(yytext); return _LABEL; }
"$"{letter}{alpha}*    { yylval.s = strdup(yytext+1); return _ADDRESS; }

","         { return _COMMA; }
"("         { return _LPAREN; }
")"         { return _RPAREN; }

. { parsererror("\nLEXICAL ERROR on character %c (line %d)", yytext[0], yylineno); }

%%

