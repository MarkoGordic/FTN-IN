%option noyywrap

%%

[+-]?[1-9][0-9]*                          { printf("\nCEO BROJ: %s\n", yytext); }
0[xX][0-9|a-f|A-F]+                       { printf("\nHEX BROJ: %s\n", yytext); }
[+-]?[0-9]+\.[0-9]*([eE][+-][0-9]+)?      { printf("\nREALNI BROJ: %s\n", yytext); }
[bB][rR][eE][aA][kK]                      { printf("\nKLJUCNA REC: %s\n", yytext); }

%%

int main() {
  yylex();
}
