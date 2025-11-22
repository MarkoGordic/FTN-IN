%option noyywrap

%%

^[ \t]*"//"[^\n]*      { }

%%

int main() {
  yylex();
}
