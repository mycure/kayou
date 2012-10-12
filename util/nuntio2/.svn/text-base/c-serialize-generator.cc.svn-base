#include "ast.hh"
#include "c-serialize-generator.hh"

void
CSerializeGenerator::visit(const IntegerType & node)
{
  out << "nuntio_";
  if (!node.isSigned)
    out << "u";
  out << "int" << node.size << "_serialize(";
}

void
CSerializeGenerator::generate(const Message & node)
{
  out << "inline void nuntio_" << node.name << "_serialize("
      << node.name << "* value, t_nuntio_archive* archive)" << std::endl
      << "{" << std::endl
      << "  archive->size = nuntio_" << node.name << "_size(value);" << std::endl
      << "  archive->buffer = malloc(archive->size);" << std::endl;
  for (Fields::const_iterator it = node.fields->begin();
       it != node.fields->end(); ++it)
  {
    out << "  ";
    (*it)->type->accept(*this);
    out << "value->" << (*it)->name << ", archive);" << std::endl;
  }
  out << "}" << std::endl << std::endl;
}
