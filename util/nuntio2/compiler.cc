#include "compiler.hh"
#include "parser.hh"
#include "lexer.hh"
#include "generator.hh"

int yyparse(yyscan_t yyscanner, File *& file);

Compiler::Compiler()
  : Singleton<Compiler> (),
    declarations(),
    files()
{
}

void
Compiler::importDependencies(const File * file)
{
  for (Imports::const_iterator it = file->imports->begin();
       it != file->imports->end(); ++it)
    parseFile((*it)->path);
}

File *
Compiler::parseFile(const std::string & path)
{
  if (files.count(path) > 0)
    return files[path];

  FILE *   stream = fopen(path.c_str(), "r");
  File *   file = new File;
  yyscan_t scanner;
  files[path] = file;

  file->path = path;
  yylex_init(&scanner);
  yyset_in(stream, scanner);
  if (yyparse(scanner, file))
    exit(1);

  importDependencies(file);
  return file;
}

void
Compiler::generate(const File * file)
{
  Generator * generator = createGenerator();
  generator->generate(file);
}

void
Compiler::generate(const std::string & path)
{
  File * file = parseFile(path);
  generate(file);
}
