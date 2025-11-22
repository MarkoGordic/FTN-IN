%{
  #include <stdio.h>
  int yylex(void);
  int yyparse(void);
  int yyerror(char *);
  extern int yylineno;
%}

%token  _DOT
%token  _CAPITAL_WORD
%token  _WORD
%token  _NUMBER

%%

start
  : list_prefix text
  ;

text 
  : sentence
  | text sentence
  ;

list_prefix
  : list
  |
  ;

list
  : _NUMBER _DOT sentence
  | list _NUMBER _DOT sentence
  ;

sentence 
  : words _DOT
  ;

words 
  : _CAPITAL_WORD
  | words _WORD
  | words _CAPITAL_WORD    
  ;

%%

int main() {
  yyparse();
}

int yyerror(char *s) {
  fprintf(stderr, "line %d: SYNTAX ERROR %s\n", yylineno, s);
  return 0;
} 

