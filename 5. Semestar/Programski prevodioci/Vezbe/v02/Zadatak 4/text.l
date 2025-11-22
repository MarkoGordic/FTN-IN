%option noyywrap yylineno
%{
  #include "text.tab.h"
%}

%%

[ \t]+    { /* skip */ }

"."                       { return _DOT; }
","                       { return _COMMA; }
"?"                       { return _QUESTION_MARK; }
"!"                       { return _EXCLAMATION_MARK; }
":"                       { return _COLON; }
\n+                       { return _NEW_LINE; }
[A-Z][a-z]*               { return _CAPITAL_WORD; }
[a-z]+                    { return _WORD; }
OFELIJA|HAMLET|KLAUDIJE   { return _DRAMA_PERSON; }
                     
.           { printf("\nline %d: LEXICAL ERROR on char %c", 
                      yylineno, *yytext); }    

