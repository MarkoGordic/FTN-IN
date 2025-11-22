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
%token  _LPAREN
%token  _RPAREN

%%

text 
  : sentence
  | text sentence
  ;
          
sentence 
  : words _DOT
  ;

words
  : _CAPITAL_WORD
  | words other_words
  ;

other_words
  : _WORD
  | _CAPITAL_WORD
  | _LPAREN _RPAREN
  | _LPAREN paren_words _RPAREN
  ;

paren_words
  : _WORD
  | _CAPITAL_WORD
  | paren_words _WORD
  | paren_words _CAPITAL_WORD
  ;

%%

int main() {
  yyparse();
}

int yyerror(char *s) {
  fprintf(stderr, "line %d: SYNTAX ERROR %s\n", yylineno, s);
  return 0;
} 

