%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[1-9][0-9]*F      { printf("%.0fC", (atoi(yytext) - 32) * 5.0/9.0); }

%%

int main() {
  yylex();
}
