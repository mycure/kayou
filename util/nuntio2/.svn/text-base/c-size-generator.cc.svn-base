#include "ast.hh"
#include "c-size-generator.hh"

void
CSizeGenerator::visit(const IntegerType & node)
{
  out << (node.size >> 3);
}

void
CSizeGenerator::generate(const Message & node)
{
  out << "inline uint32_t nuntio_" << node.name << "_size("
      << node.name << "* value)" << std::endl
      << "{" << std::endl
      << "  return 1";

  for (Fields::const_iterator it = node.fields->begin();
       it != node.fields->end(); ++it)
  {
    currentField = *it;
    out << " + ";
    (*it)->type->accept(*this);
  }

  out << ";" << std::endl
      << "}" << std::endl << std::endl;
}
