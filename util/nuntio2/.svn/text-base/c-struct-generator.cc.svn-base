#include "ast.hh"
#include "c-struct-generator.hh"

void
CStructGenerator::visit(const IntegerType & node)
{
  if (!node.isSigned)
    out << "u";
  out << "int" << node.size << "_t";
}

void
CStructGenerator::generate(const Message & node)
{
  out << "typedef struct" << std::endl
         << "{" << std::endl;
  for (Fields::const_iterator it = node.fields->begin();
       it != node.fields->end(); ++it)
  {
    out << "  ";
    (*it)->type->accept(*this);
    out << " " << (*it)->name << ";" << std::endl;
  }
  out << "} "  << node.name << ";" << std::endl << std::endl;
}
