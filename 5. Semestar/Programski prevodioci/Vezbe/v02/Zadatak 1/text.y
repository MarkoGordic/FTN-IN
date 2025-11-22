%{
  #include <stdio.h>
  int yylex(void);
  int yyparse(void);
  int yyerror(char *);
  extern int yylineno;

  int dot_sentences = 0;
  int question_sentences = 0;
  int exclamation_sentences = 0;
%}

%token  _DOT
%token  _QUESTION_MARK
%token  _EXCLAMATION_MARK
%token  _CAPITAL_WORD
%token  _WORD

%%

text 
  : sentence
  | text sentence
  ;
          
sentence 
  : words _DOT                  { dot_sentences++; }
  | words _QUESTION_MARK        { question_sentences++; }
  | words _EXCLAMATION_MARK     { exclamation_sentences++; }
  ;

words 
  : _CAPITAL_WORD
  | words _WORD
  | words _CAPITAL_WORD    
  ;

%%

int main() {
    if (yyparse() == 0) {
        printf("Broj recenica sa tackom: %d\n", dot_sentences);
        printf("Broj recenica sa upitnikom: %d\n", question_sentences);
        printf("Broj recenica sa uzvicnikom: %d\n", exclamation_sentences);
        printf("Ukupan broj recenica: %d\n", dot_sentences + question_sentences + exclamation_sentences);
  }
}

int yyerror(char *s) {
    fprintf(stderr, "line %d: SYNTAX ERROR %s\n", yylineno, s);
    return 0;
} 

