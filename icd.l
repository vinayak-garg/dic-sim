%{
#include "iclexer.h"

enum yytokentype {
  TYPE = 258,
  VALUE = 259,
  FUNC = 260,
  INT = 261
};
%}

%option noyywrap

num                 [1-9][0-9]*|0
func                [A-Z][A-Z1-9]+

%%

"%"[A-Za-z]+          { return TYPE; }
\"(\\.|[^"])*\"     { return VALUE; }
{func}              { return FUNC; }
{num}               { return INT; }
:                   { return ':'; }
=                   { return '='; }
,                   { return ','; }
"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }
\/\/[^\r\n]*        {}
"\n"                {}
[ \t]               {}

%%
void yyerror(char const *s)
{
    fprintf(stderr, "yyerror : %s\n", s);
}

yyFlexLexer *lexer;

void initLexer(std::ifstream *_infile)
{
    lexer = new yyFlexLexer(_infile);
}

int nextToken()
{
    int val = lexer->yylex();
    return val;
}

const char* getTokenString()
{
    return lexer->YYText();
}
