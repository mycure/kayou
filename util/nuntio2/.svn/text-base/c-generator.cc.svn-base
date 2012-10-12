#include <stdlib.h>
#include <iostream>

#include "ast.hh"
#include "c-generator.hh"
#include "c-struct-generator.hh"
#include "c-serialize-generator.hh"
#include "c-size-generator.hh"
#include "c-extract-generator.hh"

CGenerator::CGenerator()
  : Generator(),
    headerPath(getenv("HEADER")),
    sourcePath(getenv("SOURCE")),
    header(headerPath.c_str()),
    source(sourcePath.c_str())
{
  std::clog << "header: " << getenv("HEADER") << std::endl;
  std::clog << "source: " << getenv("SOURCE") << std::endl;
}

CGenerator::~CGenerator()
{
  header.close();
  source.close();
}

void
CGenerator::generate(const File * file)
{
  std::clog << "yahouuu" << std::endl;

  header << "#ifndef HEADER_GUARD_H" << std::endl
         << "# define HEADER_GUARD_H" << std::endl << std::endl
         << "# include <stdint.h>" << std::endl
         << "# include <stdlib.h>" << std::endl
         << "# include <lib-c/archive.h>" << std::endl << std::endl;


  for (Declarations::const_iterator it = file->declarations->begin();
       it != file->declarations->end(); ++it)
    (*it)->accept(*this);

  header << "#endif /* !HEADER_GUARD_H */" << std::endl;
}

void
CGenerator::visit(const Message & node)
{
  CStructGenerator structGen;
  structGen.generate(node);
  header << structGen.out.str();

  CSizeGenerator sizeGen;
  sizeGen.generate(node);
  header << sizeGen.out.str();

  CSerializeGenerator serializeGen;
  serializeGen.generate(node);
  header << serializeGen.out.str();

  CExtractGenerator extractGen;
  extractGen.generate(node);
  header << extractGen.out.str();
}
