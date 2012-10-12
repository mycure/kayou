#include "ast.hh"
#include "c-extract-generator.hh"

void
CExtractGenerator::visit(const IntegerType & node)
{
  out << "nuntio_";
  if (!node.isSigned)
    out << "u";
  out << "int" << node.size << "_extract(";
}

void
CExtractGenerator::generate(const Message & node)
{
  out << "inline void nuntio_" << node.name << "_extract("
      << "t_nuntio_archive* archive, " << node.name << "* value)" << std::endl
      << "{" << std::endl;

  for (Fields::const_iterator it = node.fields->begin();
       it != node.fields->end(); ++it)
  {
    out << "  ";
    (*it)->type->accept(*this);
    out << "archive, &value->" << (*it)->name << ");" << std::endl;
  }
  out << "}" << std::endl << std::endl;
}
