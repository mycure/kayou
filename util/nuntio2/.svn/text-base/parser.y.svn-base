%pure-parser
%locations
%start file
%defines
%error-verbose

%lex-param {yyscan_t yyscanner}
%parse-param {yyscan_t yyscanner}
%parse-param {File *& file}

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#include "ast.hh"
#include "parser.hh"
#include "lexer.hh"

  static void yyerror(YYLTYPE              *yyloccp,
                      yyscan_t            /*yyscanner*/,
                      File *&              file,
                      const char           *str)
  {
    if (file)
      std::cerr << file->path << ":" ;
    std::cerr << yyloccp->first_line << "." << yyloccp->first_column << "-"
              << yyloccp->last_line << "." << yyloccp->last_column
              << ": " << str << std::endl;
  }

#define MAKE_INTEGER_TYPE(Out, IsSigned, Size)  \
  do {                                          \
    IntegerType * itype = new IntegerType;      \
    itype->isSigned = IsSigned;                 \
    itype->size = Size;                         \
    Out = itype;                                \
  } while (0)                                   \

%}

%union
{
  int64_t     integer;
  char *      string;
  bool        boolean;
  long double float_;

  Declarations * declarations;
  Declaration *  declaration;
  Message *      message;
  Type *         type;
  Alias *        alias;
  IntegerType *  integer_type;
  Fields *       fields;
  Field *        field;
  Imports *      imports;
  Import *       import;
  Package *      package;
}

%token BAD_INPUT
%token MESSAGE ALIAS PACKAGE IMPORT
%token <integer> INT_TYPE UINT_TYPE
%token <number> INTEGER
%token <boolean> BOOL
%token <float_> FLOAT;
%token <string> ID STRING

%type <declaration> declaration
%type <declarations> declarations
%type <message> message
%type <string> name
%type <type> type
%type <fields> fields
%type <field> field
%type <imports> imports
%type <import> import
%type <package> package
%type <alias> alias

%%

file: imports declarations {
  if (!file)
    file = new File;
  file->imports = $1;
  file->declarations = $2;
};

imports: imports import { $$ = $1; $$->push_back($2); }
| /* epsilon */ { $$ = new Imports; };

import: IMPORT STRING ';' { $$ = new Import; $$->path = $2; }
;

declarations: declarations declaration { $$ = $1; $$->push_back($2); }
| /* epsilon */ { $$ = new Declarations; };

declaration: message { $$ = $1; }
| alias { $$ = $1; }
| package { $$ = $1; }
;

message: MESSAGE name '{' fields '}' {
  $$ = new Message;
  $$->name = $2;
  $$->fields = $4;
 }
;

alias: ALIAS type ID {
  $$ = new Alias;
  $$->type = $2;
  $$->name = $3;
}

fields: fields field { $$ = $1; $$->push_back($2); }
| /* epsilon */ { $$ = new Fields; };

field: type name ';' { $$ = new Field; $$->type = $1; $$->name = $2; }
;

package: PACKAGE name '{' declarations '}' {
  $$ = new Package;
  $$->name = $2;
  $$->declarations = $4;
};

type: INT_TYPE { MAKE_INTEGER_TYPE($$, true, $1); }
| UINT_TYPE { MAKE_INTEGER_TYPE($$, false, $1); }
;

name: ID { $$ = $1; }
;

%%
