%option reentrant noyywrap batch
%option bison-bridge bison-locations yylineno
%option warn nodefault

%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.hh"
#include "parser.hh"

#define YY_USER_ACTION                                  \
  yylloc->first_line = yylineno;                        \
  yylloc->last_line = yylineno;                         \
  yylloc->first_column = yylloc->last_column;           \
  yylloc->last_column += yyleng;

%}

%%

\n                      /* ignore end of line */yylloc->last_column = 0;
[ \t]+                  /* ignore whitespace */;
\/\/.*$                 /* line comment */
#.*$                    /* line comment */


\"[^\"]*\"              return STRING;

\{                      return '{';
\}                      return '}';
;                       return ';';

message                 return MESSAGE;
alias                   return ALIAS;
import                  return IMPORT;
package                 return PACKAGE;

true                    yylval->boolean = 1; return BOOL;
false                   yylval->boolean = 1; return BOOL;

int[0-9]+               yylval->integer = strtoll(yytext + 3, 0, 0); return INT_TYPE;
uint[0-9]+              yylval->integer = strtoll(yytext + 4, 0, 0); return UINT_TYPE;

[a-zA-Z][a-zA-Z0-9_]*   yylval->string = strdup(yytext); return ID;

([0-9]+)?\.[0-9]+       yylval->float_ = strtold(yytext, 0); return FLOAT;
[0-9]+                  yylval->integer = strtoll(yytext, 0, 0); return INTEGER;
0x[0-9a-fA-F]+          yylval->integer = strtoll(yytext, 0, 0); return INTEGER;

.                       return BAD_INPUT;

%%
