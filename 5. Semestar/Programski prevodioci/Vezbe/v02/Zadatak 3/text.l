%option noyywrap yylineno
%{
  #include "text.tab.h"
%}

%%

[ \t]+    { /* skip */ }

"."         { return _DOT; }
","         { return _COMMA; }
"?"         { return _QUESTION_MARK; }
"!"         { return _EXCLAMATION_MARK; }
\n+         { return _NEW_LINE; }
[A-Z][a-z]* { return _CAPITAL_WORD; }
[a-z]+      { return _WORD; }
                     
.           { printf("\nline %d: LEXICAL ERROR on char %c", 
                      yylineno, *yytext); }    

