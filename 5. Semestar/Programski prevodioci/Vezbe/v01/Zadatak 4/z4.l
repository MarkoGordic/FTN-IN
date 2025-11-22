%option noyywrap

%{

%}

%%

"/*"([^*]|\*+[^*/])*\*+"/"    { /* brisanje komentara */ }

%%

int main() {
  yylex();
}
